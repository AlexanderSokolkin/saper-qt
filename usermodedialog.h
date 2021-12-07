#ifndef USERMODEDIALOG_H
#define USERMODEDIALOG_H

#include <QDialog>

namespace Ui {
class UserModeDialog;
}

class UserModeDialog : public QDialog
{
	Q_OBJECT

public:
	explicit UserModeDialog(int t_cellsWidth,
							int t_cellsHeight,
							int t_bombCount,
							QWidget *parent = nullptr);
	~UserModeDialog();

	int userFieldWidth;
	int userFieldHeigth;
	int userBombCount;

private:
	void slotSaveParam();
	Ui::UserModeDialog *ui;
};

#endif // USERMODEDIALOG_H
