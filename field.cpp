#include "field.h"
#include "helper.h"
#include <QGridLayout>
#include <QSet>
#include <QMessageBox>
#include <ctime>

Field::Field(QWidget* parent) : QWidget(parent)
{
	m_isInit = false;
	m_openCells = 0;
}

void Field::fieldCreate(State t_state,
						int t_cellWidth,
						int t_cellHeight,
						int t_bombCount)
{
	switch (t_state) {
		case State::BEGINNER:
			m_fieldWidth = BEGINNER_WIDTH;
			m_fieldHeight = BEGINNER_HEIGHT;
			m_cellsCount = BEGINNER_WIDTH * BEGINNER_HEIGHT;
			m_bombCount = BEGINNER_BOMB_COUNT;
			break;
		case State::AMATEUR:
			m_fieldWidth = AMATEUR_WIDTH;
			m_fieldHeight = AMATEUR_HEIGHT;
			m_cellsCount = AMATEUR_WIDTH * AMATEUR_HEIGHT;
			m_bombCount = AMATEUR_BOMB_COUNT;
			break;
		case State::PROFESSIONAL:
			m_fieldWidth = PROFESSIONAL_WIDTH;
			m_fieldHeight = PROFESSIONAL_HEIGHT;
			m_cellsCount = PROFESSIONAL_WIDTH * PROFESSIONAL_HEIGHT;
			m_bombCount = PROFESSIONAL_BOMB_COUNT;
			break;
		case State::USER_MODE:
			m_fieldWidth = t_cellWidth;
			m_fieldHeight = t_cellHeight;
			m_cellsCount = t_cellWidth * t_cellHeight;
			m_bombCount = t_bombCount;
		default:
			break;
	}

	m_cells.reserve(m_cellsCount);

	QGridLayout* glayout = new QGridLayout(this);
	glayout->setHorizontalSpacing(0);
	glayout->setVerticalSpacing(0);
	setLayout(glayout);

	for (int row = 0; row < m_fieldHeight; ++row) {
		for (int col = 0; col < m_fieldWidth; ++col) {
			FieldCell* cell = new FieldCell(row * m_fieldWidth + col, this);
			m_cells.append(cell);

			glayout->addWidget(cell, row, col);

			connect(cell, &FieldCell::sigClick, this, &Field::slotClick);
		}
	}
}

void Field::initField(int t_fieldCellPos) {

	srand(time(NULL));

	while(m_bombPos.size() < m_bombCount) {
		int randomBombPos = rand() % (m_cellsCount);
		if (randomBombPos != t_fieldCellPos) {
			m_bombPos.insert(randomBombPos);
		}
	}

	for (int pos : m_bombPos) {
		m_cells[pos]->setBomb();
		QVector<int> cellsAround = findCellsAround(pos);

		for (int pos : cellsAround) {
			if (!m_bombPos.contains(pos)) {
				m_cells[pos]->incrementBombsAround();
			}
		}

	}

	m_isInit = true;
}

void Field::slotClick(int t_fieldCellPos)
{
	if (!m_isInit) {
		initField(t_fieldCellPos);
	}

	if (m_cells[t_fieldCellPos]->isBomb()) {
		explosion(t_fieldCellPos);
		QMessageBox::information(this, "Поражение!", "Игра окончена!", QMessageBox::Ok);
		setEnabled(false);
		return;
	}

	if (!m_cells[t_fieldCellPos]->isOpen()) {
		openCell(t_fieldCellPos);
	} else {
		openArea(t_fieldCellPos);
	}

	if (m_openCells == m_cellsCount - m_bombCount) {
		QMessageBox::information(this, "Победа!", "Игра окончена!", QMessageBox::Ok);
		setEnabled(false);
	}
}

QVector<int> Field::findCellsAround(int t_cellPos)
{
	QVector<int> cellsAround;
	int row = t_cellPos / m_fieldWidth;
	int col = t_cellPos % m_fieldWidth;

	if (row != 0) {
		cellsAround.push_back(t_cellPos - m_fieldWidth);
	}
	if (row != m_fieldHeight - 1) {
		cellsAround.push_back(t_cellPos + m_fieldWidth);
	}
	if (col != 0) {
		cellsAround.push_back(t_cellPos - 1);
	}
	if (col != m_fieldWidth - 1) {
		cellsAround.push_back(t_cellPos + 1);
	}
	if (row != 0 && col != 0) {
		cellsAround.push_back(t_cellPos - m_fieldWidth - 1);
	}
	if (row != 0 && col != m_fieldWidth - 1) {
		cellsAround.push_back(t_cellPos - m_fieldWidth + 1);
	}
	if (row != m_fieldHeight - 1 && col != 0) {
		cellsAround.push_back(t_cellPos + m_fieldWidth - 1);
	}
	if (row != m_fieldHeight - 1 && col != m_fieldWidth - 1) {
		cellsAround.push_back(t_cellPos + m_fieldWidth + 1);
	}

	return cellsAround;
}

void Field::openCell(int t_fieldCellPos)
{
	if (!m_cells[t_fieldCellPos]->isOpen()) {
		m_cells[t_fieldCellPos]->open();
		m_cells[t_fieldCellPos]->setStyleSheet("QPushButton {background-color: #BEBEBE; color: black}");

		int bombsAround = m_cells[t_fieldCellPos]->getBombsAround();

		if (!bombsAround) {
			m_cells[t_fieldCellPos]->setText("");
			QVector<int> cellsPosAround = findCellsAround(t_fieldCellPos);
			for (int cellPos : cellsPosAround) {
				openCell(cellPos);
			}
		} else {
			m_cells[t_fieldCellPos]->setText(QString::number(bombsAround));
		}
		m_openCells++;
	}
}

void Field::openArea(int t_fieldCellPos)
{
	int bombsAround = m_cells[t_fieldCellPos]->getBombsAround();
	QVector<int> cellsAround = findCellsAround(t_fieldCellPos);
	int flagsAround = 0;
	for (int cell : cellsAround) {
		if (m_cells[cell]->getClickCount() == 1) {
			flagsAround++;
		}
	}

	if (flagsAround == bombsAround) {
		for (int cell : cellsAround) {
			if (m_cells[cell]->getClickCount() != 1) {
				if (!m_cells[cell]->isBomb()) {
					openCell(cell);
				} else {
					explosion(cell);
				}
			}
		}
	}
}


void Field::explosion(int t_fieldCellPos)
{
	for (int bomb : m_bombPos) {
		m_cells[bomb]->setText("*");
		m_cells[bomb]->setStyleSheet("QPushButton {background-color: #BEBEBE; color: black}");
	}

	m_cells[t_fieldCellPos]->setStyleSheet("QPushButton {background-color: red; color: black}");
	setEnabled(false);
}

