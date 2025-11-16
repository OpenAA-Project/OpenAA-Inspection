#ifndef WIZARDMENUDIALOG_H
#define WIZARDMENUDIALOG_H

#include <QDialog>

namespace Ui {
class WIzardMenuDialog;
}

class WIzardMenuDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit WIzardMenuDialog(QWidget *parent = 0);
    ~WIzardMenuDialog();
    
private:
    Ui::WIzardMenuDialog *ui;
};

#endif // WIZARDMENUDIALOG_H
