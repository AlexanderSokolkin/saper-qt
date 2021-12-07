#include "usermodedialog.h"
#include "ui_usermodedialog.h"
#include <QPushButton>
#include <QMessageBox>
#include <QValidator>
#include <QRegExp>

UserModeDialog::UserModeDialog(int t_cellsWidth,
							   int t_cellsHeight,
							   int t_bombCount,
							   QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UserModeDialog)
{
	ui->setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	QIntValidator *cellValidator = new QIntValidator(1, 200, this);
	QIntValidator *bombValidator = new QIntValidator(1, 20000, this);
	ui->cellsWidth->setValidator(cellValidator);
	ui->cellsHeight->setValidator(cellValidator);
	ui->bombCount->setValidator(bombValidator);

	ui->cellsWidth->setText(QString::number(t_cellsWidth));
	ui->cellsHeight->setText(QString::number(t_cellsHeight));
	ui->bombCount->setText(QString::number(t_bombCount));

	connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &UserModeDialog::slotSaveParam);
}

UserModeDialog::~UserModeDialog()
{
	delete ui;
}

void UserModeDialog::slotSaveParam()
{
	if (ui->cellsWidth->text().isEmpty() ||
		ui->cellsHeight->text().isEmpty() ||
		ui->bombCount->text().isEmpty())
	{
		QMessageBox::critical(this,
							  tr("Ошибка!"),
							  tr("Заполните все поля!"),
							  QMessageBox::Ok);
		return;
	}

	if (ui->bombCount->text().toInt() >= ui->cellsWidth->text().toInt() * ui->cellsHeight->text().toInt()) {
		QMessageBox::critical(this,
							  tr("Ошибка!"),
							  tr("Слишком много бомб!"),
							  QMessageBox::Ok);
		ui->bombCount->setFocus();
		return;
	}

	userFieldWidth = ui->cellsWidth->text().toInt();
	userFieldHeigth = ui->cellsHeight->text().toInt();
	userBombCount = ui->bombCount->text().toInt();
	accept();
}
