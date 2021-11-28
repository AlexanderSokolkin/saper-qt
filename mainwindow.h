#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QVBoxLayout>

#include "field.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
	Field*				m_field;
	State				m_state;
	QVBoxLayout*		m_layout;
	QPushButton			m_pbStart;

	QAction*			m_beginner;
	QAction*			m_amateur;
	QAction*			m_professional;

private slots:
	void slotRestartButtonClick();
	void slotOnBeginnerTriggered();
	void slotOnAmateurTriggered();
	void slotOnProfessionalTriggered();
	void recreateField();
};
#endif // MAINWINDOW_H
