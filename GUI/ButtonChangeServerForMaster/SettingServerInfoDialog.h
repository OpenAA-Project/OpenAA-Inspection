#ifndef SETTINGSERVERINFODIALOG_H
#define SETTINGSERVERINFODIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XChangeServerInfo.h"

namespace Ui {
class SettingServerInfoDialog;
}

class SettingServerInfoDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	ChangeServerContainer	ServerList;
public:
    explicit SettingServerInfoDialog(LayersBase *base,QWidget *parent = 0);
    ~SettingServerInfoDialog();
    
private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_listWidgetServer_clicked(const QModelIndex &index);

private:
    Ui::SettingServerInfoDialog *ui;

	void	DrawList(void);
};

#endif // SETTINGSERVERINFODIALOG_H
