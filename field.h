#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QVector>
#include "statefields.h"
#include "fieldcell.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = nullptr);

	void fieldCreate(State t_state);

signals:
	void sigBoom();

public slots:
	void slotClick(int t_fieldCellPos);

private:
	void initField(int t_fieldCellPos);
	QVector<int> findCellsAround(int t_cellPos);
	void openCell(int t_fieldCellPos);
	void openArea(int t_fieldCellPos);
	void explosion(int t_fieldCellPos);


	int		m_bombCount;
	int		m_cellsCount;
	int		m_fieldWidth;
	int		m_fieldHeight;
	bool	m_isInit;

	int		m_openCells;

	QVector<FieldCell*> m_cells;
	QSet<int> m_bombPos;
};

#endif // FIELD_H
