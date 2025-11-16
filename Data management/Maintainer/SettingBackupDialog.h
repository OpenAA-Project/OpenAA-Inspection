#ifndef SETTINGBACKUPDIALOG_H
#define SETTINGBACKUPDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class SettingBackupDialog;
}
class Maintainer;

class SettingBackupDialog : public QDialog
{
    Q_OBJECT
    Maintainer	*Parent;
public:
    explicit SettingBackupDialog(Maintainer *p ,QWidget *parent = 0);
    ~SettingBackupDialog();
    
private slots:
    void on_checkBoxImageKeepDays_clicked();

    void on_checkBoxImageKeepMonths_clicked();

    void on_listWidgetImageFileNames_doubleClicked(const QModelIndex &index);

    void on_pushButtonImageAddFileName_clicked();

    void on_pushButtonImageSubLine_clicked();

    void on_pushButtonSelectDestinationPath_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::SettingBackupDialog *ui;
};

#endif // SETTINGBACKUPDIALOG_H
