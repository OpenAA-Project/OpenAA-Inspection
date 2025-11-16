#ifndef EDITPROGRAMBOOTERDIALOG_H
#define EDITPROGRAMBOOTERDIALOG_H

#include <QDialog>
#include "XBooter.h"

namespace Ui {
class EditProgramBooterDialog;
}

class EditProgramBooterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditProgramBooterDialog(QWidget *parent = 0);
    ~EditProgramBooterDialog();

	void	Initial(ExecuteApplicationList &src);

	QString		Program;
	QString		Parameter;

private slots:
    void on_pushButtonFile_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonEdit_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditProgramBooterDialog *ui;
};

#endif // EDITPROGRAMBOOTERDIALOG_H
