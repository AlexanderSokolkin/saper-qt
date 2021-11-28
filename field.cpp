#include <QGridLayout>
#include <QSet>
#include <QMessageBox>
#include <ctime>
#include "field.h"

Field::Field(QWidget* parent) : QWidget(parent)
{
	m_isInit = false;
	m_openCells = 0;
}

void Field::fieldCreate(State t_state)
{
	switch (t_state) {
		case State::BEGINNER:
			m_fieldWidth = 10;
			m_fieldHeight = 10;
			m_cellsCount = 100;
			m_bombCount = 10;
			break;
		case State::AMATEUR:
			m_fieldWidth = 15;
			m_fieldHeight = 20;
			m_cellsCount = 300;
			m_bombCount = 30;
			break;
		case State::PROFESSIONAL:
			m_fieldWidth = 30;
			m_fieldHeight = 20;
			m_cellsCount = 600;
			m_bombCount = 100;
			break;
		default:
			break;
	}

	m_cells.reserve(m_cellsCount);

	QGridLayout* glayout = new QGridLayout(this);
	glayout->setHorizontalSpacing(0);
	glayout->setVerticalSpacing(0);
	glayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(glayout);

	for (int row = 0; row < m_fieldHeight; ++row) {
		for (int col = 0; col < m_fieldWidth; ++col) {
			FieldCell* cell = new FieldCell(row * m_fieldWidth + col, this);
			m_cells.append(cell);

			glayout->addWidget(cell, row, col);

			connect(cell, &FieldCell::sigClick, this, &Field::slotClick);
		}
	}

//	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

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
		return;
	}

	if (!m_cells[t_fieldCellPos]->isOpen()) {
		openCell(t_fieldCellPos);
	} else {
		openArea(t_fieldCellPos);
	}

	if (m_openCells == m_cellsCount - m_bombCount) {
		QMessageBox::information(this, "Победа!", "Потраченное время - **", QMessageBox::Ok);
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

