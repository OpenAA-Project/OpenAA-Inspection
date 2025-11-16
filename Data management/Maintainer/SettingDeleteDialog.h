#ifndef SETTINGDELETEDIALOG_H
#define SETTINGDELETEDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class SettingDeleteDialog;
}

class Maintainer;

class SettingDeleteDialog : public QDialog
{
    Q_OBJECT
    Maintainer	*Parent;
public:
    explicit SettingDeleteDialog(Maintainer *p ,QWidget *parent = 0);
    ~SettingDeleteDialog();
    
private slots:
    void on_checkBoxImageKeepDays_clicked();
    void on_checkBoxImageKeepMonths_clicked();
    void on_listWidgetImageFileNames_doubleClicked(const QModelIndex &index);
    void on_pushButtonImageAddFileName_clicked();
    void on_pushButtonImageSubLine_clicked();
    void on_pushButtonImageAddFolderName_clicked();
    void on_pushButtonImageSubFolder_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::SettingDeleteDialog *ui;
};

#endif // SETTINGDELETEDIALOG_H
