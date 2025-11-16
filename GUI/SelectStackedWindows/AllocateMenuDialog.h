#ifndef ALLOCATEMENUDIALOG_H
#define ALLOCATEMENUDIALOG_H

#include <QDialog>
#include "SelectStackedWindows.h"

namespace Ui {
class AllocateMenuDialog;
}

class AllocateMenuDialog : public QDialog
{
    Q_OBJECT
    QByteArray	*MenuData;
	AllocationListContainer	MContainer;
public:
    explicit AllocateMenuDialog(QByteArray *_MenuData ,QWidget *parent = 0);
    ~AllocateMenuDialog();

private slots:
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AllocateMenuDialog *ui;

	void	ShowList(void);
	void	GetListFromWindow(void);
	
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // ALLOCATEMENUDIALOG_H
