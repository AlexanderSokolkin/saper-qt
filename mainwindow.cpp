#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QDebug>
#include <QCoreApplication>
#include "helper.h"
#include "usermodedialog.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_cellsWidth = 10;
	m_cellsHeight = 10;
	m_bombCount = 10;

	m_state = State::BEGINNER;
	m_pbStart.setFixedSize(100, 40);
	m_field = new Field();
	m_field->fieldCreate(m_state);
	m_layout = new QVBoxLayout();
	m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	QWidget* wd = new QWidget(this);
	wd->setLayout(m_layout);
	m_layout->addWidget(&m_pbStart);
	m_layout->addWidget(m_field);
	m_layout->setAlignment(&m_pbStart,Qt::AlignCenter);

	m_pbStart.setText("Новая игра");
	setCentralWidget(wd);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	connect(&m_pbStart, &QPushButton::clicked, this, &MainWindow::slotRestartButtonClick);
	wd->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	QMenu* game;
	game = menuBar()->addMenu("Сложность");

	m_beginner		=	new QAction(tr("Новичок"), game);
	m_amateur		=	new QAction(tr("Любитель"), game);
	m_professional	=	new QAction(tr("Профессионал"), game);
	m_userMode		=	new QAction(tr("Пользовательсксий режим"), game);

	m_beginner->setCheckable(true);
	m_amateur->setCheckable(true);
	m_professional->setCheckable(true);
	m_userMode->setCheckable(true);

	m_beginner->setChecked(true);

	connect(m_beginner, &QAction::triggered, this, &MainWindow::slotOnBeginnerTriggered);
	connect(m_amateur, &QAction::triggered, this, &MainWindow::slotOnAmateurTriggered);
	connect(m_professional, &QAction::triggered, this, &MainWindow::slotOnProfessionalTriggered);
	connect(m_userMode, &QAction::triggered, this, &MainWindow::slotOnUserModeTriggered);

	game->addAction(m_beginner);
	game->addAction(m_amateur);
	game->addAction(m_professional);
	game->addAction(m_userMode);
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
	m_userMode->setChecked(false);
	m_state = State::BEGINNER;
	recreateField();
}

void MainWindow::slotOnAmateurTriggered()
{
	m_beginner->setChecked(false);
	m_amateur->setChecked(true);
	m_professional->setChecked(false);
	m_userMode->setChecked(false);
	m_state = State::AMATEUR;
	recreateField();
}

void MainWindow::slotOnProfessionalTriggered()
{
	m_beginner->setChecked(false);
	m_amateur->setChecked(false);
	m_professional->setChecked(true);
	m_userMode->setChecked(false);
	m_state = State::PROFESSIONAL;
	recreateField();
}

void MainWindow::slotOnUserModeTriggered()
{
	UserModeDialog* dialog = new UserModeDialog(m_cellsWidth, m_cellsHeight, m_bombCount, this);
	if(dialog->exec() == QDialog::Accepted) {
		m_beginner->setChecked(false);
		m_amateur->setChecked(false);
		m_professional->setChecked(false);
		m_userMode->setChecked(true);
		m_state = State::USER_MODE;
		m_cellsWidth = dialog->userFieldWidth;
		m_cellsHeight = dialog->userFieldHeigth;
		m_bombCount = dialog->userBombCount;
		recreateField();
	}
}

void MainWindow::recreateField()
{
	delete m_field;
	m_field = nullptr;
	m_field = new Field();
	m_field->fieldCreate(m_state, m_cellsWidth, m_cellsHeight, m_bombCount);
	m_layout->addWidget(m_field);
	switch(m_state){
		case State::BEGINNER:
			setFixedSize(BEGINNER_FIELD_WIDTH, BEGINNER_FIELD_HEIGHT);
			break;
		case State::AMATEUR:
			setFixedSize(AMATEUR_FIELD_WIDTH, AMATEUR_FIELD_HEIGHT);
			break;
		case State::PROFESSIONAL:
			setFixedSize(PROFESSIONAL_FIELD_WIDTH, PROFESSIONAL_FIELD_HEIGHT);
			break;
		case State::USER_MODE:
			setFixedSize(USER_MODE_FIELD_WIDTH(m_cellsWidth), USER_MODE_FIELD_HEIGHT(m_cellsHeight));
			break;
		default:
			break;
	}
}
