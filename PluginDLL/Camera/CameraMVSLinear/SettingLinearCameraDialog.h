#ifndef SETTINGLINEARCAMERADIALOG_H
#define SETTINGLINEARCAMERADIALOG_H

#include <QDialog>

namespace Ui {
class SettingLinearCameraDialog;
}

class SettingLinearCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingLinearCameraDialog(QWidget *parent = nullptr);
    ~SettingLinearCameraDialog();

private:
    Ui::SettingLinearCameraDialog *ui;
};

#endif // SETTINGLINEARCAMERADIALOG_H
