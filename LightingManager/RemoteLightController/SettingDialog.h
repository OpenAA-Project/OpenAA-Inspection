#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XRemoteLightController.h"
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
	RemoteLightContainer	RemoteLightData;

	explicit SettingDialog(LayersBase *Base ,RemoteLightContainer &src ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_listWidgetLightDLL_clicked(const QModelIndex &index);
    void on_listWidgetRegisteredItemList_clicked(const QModelIndex &index);
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowRegisteredItemList(void);
};

#endif // SETTINGDIALOG_H
