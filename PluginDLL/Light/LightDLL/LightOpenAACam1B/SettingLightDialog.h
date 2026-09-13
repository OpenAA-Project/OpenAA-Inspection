#ifndef SETTINGLIGHTDIALOG_H
#define SETTINGLIGHTDIALOG_H

#include <QDialog>
#include "XSocket.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingLightDialog;
}

class SettingLightDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
public:
    int32		LightID;
	struct  SocketPacket	DataPacket;

public:
    explicit SettingLightDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~SettingLightDialog();

	void Initial(int32 LightID,struct  SocketPacket &DataPacket);
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingLightDialog *ui;
};

#endif // SETTINGLIGHTDIALOG_H
