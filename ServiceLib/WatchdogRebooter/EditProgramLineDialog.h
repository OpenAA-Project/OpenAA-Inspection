#ifndef EDITPROGRAMLINEDIALOG_H
#define EDITPROGRAMLINEDIALOG_H

#include <QDialog>
#include "XWatchdogRebooter.h"

namespace Ui {
class EditProgramLineDialog;
}

class EditProgramLineDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditProgramLineDialog(QWidget *parent = 0);
    ~EditProgramLineDialog();
    
	WatchdogTarget	Current;

protected:
	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSelectPathFile_clicked();
    void on_pushButtonSelectWorkingPath_clicked();

private:
    Ui::EditProgramLineDialog *ui;
};

#endif // EDITPROGRAMLINEDIALOG_H
