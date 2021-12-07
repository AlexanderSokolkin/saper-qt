#ifndef FIELDCELL_H
#define FIELDCELL_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

class FieldCell : public QPushButton
{
	Q_OBJECT
public:
	FieldCell(int t_position, QWidget* parent = nullptr);

	void mouseReleaseEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);

	void incrementBombsAround();
	void setBomb();
	void open();

	bool isBomb();
	bool isOpen();
	int getBombsAround();
	int getClickCount();

signals:
	void sigClick(int t_fieldCellPos);

private:
	bool	m_isBomb;
	bool	m_isOpen;
	int		m_clickCount;	// количество кликов ПКМ (если 1 - флажок, если 2 - вопрос)
	int		m_bombsAround;	// количество бомб вокруг
	int		m_position;		// позиция кнопки

};

#endif // FIELDCELL_H
