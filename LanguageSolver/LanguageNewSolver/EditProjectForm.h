#ifndef EDITPROJECTFORM_H
#define EDITPROJECTFORM_H

#include <QDialog>
#include "XLSProjectNew.h"

namespace Ui {
    class EditProjectForm;
}

class EditProjectForm : public QDialog
{
    Q_OBJECT
	LSProjectItem	*Project;

public:
    explicit EditProjectForm(LSProjectItem *a,QWidget *parent = 0);
    ~EditProjectForm();

private slots:
    void on_pushButtonFolderReference_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditProjectForm *ui;
};

#endif // EDITPROJECTFORM_H
