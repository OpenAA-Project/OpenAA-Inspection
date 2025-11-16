#ifndef SETTINGCATEGORYDIALOG_H
#define SETTINGCATEGORYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "ResultCategorizer.h"

namespace Ui {
class SettingCategoryDialog;
}
class  ResultCategorizer;

class SettingCategoryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ResultCategorizer	*Parent;
	ResultCatShapeContainer	ResultCat;
public:
    explicit SettingCategoryDialog(LayersBase *base ,ResultCategorizer *p,QWidget *parent = 0);
    ~SettingCategoryDialog();
    
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonAddList_clicked();
    void on_pushButtonDelList_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::SettingCategoryDialog *ui;

	void	ShowList(void);
	void	LoadFromWindow(void);
};

#endif // SETTINGCATEGORYDIALOG_H
