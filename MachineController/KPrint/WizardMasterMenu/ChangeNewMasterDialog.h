#ifndef CHANGENEWMASTERDIALOG_H
#define CHANGENEWMASTERDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeNewMasterDialog;
}

class ChangeNewMasterDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChangeNewMasterDialog(QWidget *parent = 0);
    ~ChangeNewMasterDialog();
    
private slots:
    void on_PushButtonCreateNewMaster_clicked();
    void on_PushButtonOnlyImage_clicked();

private:
    Ui::ChangeNewMasterDialog *ui;
};

#endif // CHANGENEWMASTERDIALOG_H
