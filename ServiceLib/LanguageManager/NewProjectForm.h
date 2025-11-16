#ifndef NEWPROJECTFORM_H
#define NEWPROJECTFORM_H

#include <QDialog>

namespace Ui {
    class NewProjectForm;
}

class NewProjectForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectForm(const QString &ProjName ,QWidget *parent = 0);
    ~NewProjectForm();

	QString	ProjectName;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::NewProjectForm *ui;
};

#endif // NEWPROJECTFORM_H
