#ifndef CREATECLASSFORMDIALOG_H
#define CREATECLASSFORMDIALOG_H

#include <QDialog>

namespace Ui {
class CreateClassFormDialog;
}

class CreateClassFormDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateClassFormDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::Widget);
    ~CreateClassFormDialog();
    
	QString	GetLiedClassName(void);
	QString	GetLiedPassword(void);
public slots:
    void checkEnableOk();
public:
    Ui::CreateClassFormDialog *ui;
};

#endif // CREATECLASSFORMDIALOG_H
