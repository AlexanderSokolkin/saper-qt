#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	m_state = State::BEGINNER;
	m_pbStart.setFixedSize(40, 40);
	m_field = new Field();
	m_field->fieldCreate(m_state);
	m_layout = new QVBoxLayout(this);
	m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	QWidget* wd = new QWidget(this);
	wd->setLayout(m_layout);
	m_layout->addWidget(&m_pbStart);
	m_layout->addWidget(m_field);
	setCentralWidget(wd);

	connect(&m_pbStart, &QPushButton::clicked, this, &MainWindow::slotRestartButtonClick);

	QMenu* game;
	game = menuBar()->addMenu("Игра");

	m_beginner		=	new QAction(tr("Новичок"), game);
	m_amateur		=	new QAction(tr("Любитель"), game);
	m_professional	=	new QAction(tr("Новичок"), game);

	m_beginner->setCheckable(true);
	m_amateur->setCheckable(true);
	m_professional->setCheckable(true);

	m_beginner->setChecked(true);

	connect(m_beginner, &QAction::triggered, this, MainWindow::slotOnBeginnerTriggered);
	connect(m_amateur, &QAction::triggered, this, MainWindow::slotOnAmateurTriggered);
	connect(m_professional, &QAction::triggered, this, MainWindow::slotOnProfessionalTriggered);

	game->addAction(m_beginner);
	game->addAction(m_amateur);
	game->addAction(m_professional);
}

MainWindow::~MainWindow()
{
}

void MainWindow::slotRestartButtonClick()
{
	recreateField();
}

void MainWindow::slotOnBeginnerTriggered()
{
	m_beginner->setChecked(true);
	m_amateur->setChecked(false);
	m_professional->setChecked(false);
	m_state = State::BEGINNER;
	recreateField();
}

void MainWindow::slotOnAmateurTriggered()
{
	m_beginner->setChecked(false);
	m_amateur->setChecked(true);
	m_professional->setChecked(false);
	m_state = State::AMATEUR;
	recreateField();
}

void MainWindow::slotOnProfessionalTriggered()
{
	m_beginner->setChecked(false);
	m_amateur->setChecked(false);
	m_professional->setChecked(true);
	m_state = State::PROFESSIONAL;
	recreateField();
}

void MainWindow::recreateField()
{
	delete m_field;
	m_field = new Field();
	m_field->fieldCreate(m_state);
	m_layout->addWidget(m_field);
}
