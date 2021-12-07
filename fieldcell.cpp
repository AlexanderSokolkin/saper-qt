#include "fieldcell.h"
#include "helper.h"
#include <QSizePolicy>
#include <QDebug>

FieldCell::FieldCell(int t_position, QWidget* parent) :
	QPushButton(parent)
{
	m_isBomb = false;
	m_isOpen = false;
	m_bombsAround = 0;
	m_clickCount = 0;
	m_position = t_position;
	setStyleSheet("QPushButton {background-color: #9090e8; color: black}");
	setFixedSize(BUTTONS_SIZE, BUTTONS_SIZE);
}
void FieldCell::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::RightButton && !m_isOpen) {
		m_clickCount++;
		switch (m_clickCount) {
			case 1:
				setText("M");
				break;
			case 2:
				setText("?");
				break;
			case 3:
				setText("");
				m_clickCount = 0;
				break;
		}
	}

	if (event->button() == Qt::MouseButton::LeftButton && !m_clickCount) {
		setDown(false);
		emit sigClick(m_position);
	}

}

void FieldCell::mousePressEvent(QMouseEvent* event)
{
	if (!m_isOpen && event->button() == Qt::MouseButton::LeftButton && !m_clickCount) {
		setDown(true);
	}
}

void FieldCell::incrementBombsAround()
{
	m_bombsAround++;
}

void FieldCell::setBomb()
{
	m_isBomb = true;
}


bool FieldCell::isBomb()
{
	return m_isBomb;
}

bool FieldCell::isOpen()
{
	return m_isOpen;
}

int FieldCell::getBombsAround()
{
	return m_bombsAround;
}

int FieldCell::getClickCount()
{
	return m_clickCount;
}

void FieldCell::open()
{
	m_isOpen = true;
}
