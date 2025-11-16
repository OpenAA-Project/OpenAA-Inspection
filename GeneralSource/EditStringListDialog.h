#ifndef EDITSTRINGLISTDIALOG_H
#define EDITSTRINGLISTDIALOG_H

#include <QDialog>
#include <QStringList>
#include "XServiceForLayers.h"

namespace Ui {
class EditStringListDialog;
}

class EditStringListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStringListDialog(const QStringList &str,QWidget *parent = 0);
    ~EditStringListDialog();
	
	QStringList	Str;

private slots:
    void on_buttonBox_accepted();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();

private:
    Ui::EditStringListDialog *ui;
};

#endif // EDITSTRINGLISTDIALOG_H
