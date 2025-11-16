#ifndef SETTINGSHRINKHIGHLOWDIALOG_H
#define SETTINGSHRINKHIGHLOWDIALOG_H

#include <QDialog>

namespace Ui {
class SettingShrinkHighLowDialog;
}

class ShrinkLowHigh;


class SettingShrinkHighLowDialog : public QDialog
{
    Q_OBJECT
    
	ShrinkLowHigh	*Handle;
public:
    explicit SettingShrinkHighLowDialog(ShrinkLowHigh *handle,QWidget *parent = 0);
    ~SettingShrinkHighLowDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingShrinkHighLowDialog *ui;
};

#endif // SETTINGSHRINKHIGHLOWDIALOG_H
