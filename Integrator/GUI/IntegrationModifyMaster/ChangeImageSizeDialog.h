#ifndef CHANGEIMAGESIZEDIALOG_H
#define CHANGEIMAGESIZEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XIntClass.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "NListComp.h"

namespace Ui {
class ChangeImageSizeDialog;
}

class ChangeImageSizeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ChangeImageSizeDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ChangeImageSizeDialog();

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ChangeImageSizeDialog *ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;
};
//===================================================================================================

class	IntegrationReqXYPixels : public IntegrationCmdPacketBase
{
public:
	IntegrationReqXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckXYPixels : public IntegrationCmdPacketBase
{
public:
    int32	XLen,YLen;
	int32	NanoMeterPerDotX;
	int32	NanoMeterPerDotY;

	IntegrationAckXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationSetXYPixels : public IntegrationCmdPacketBase
{
public:
	int32 XLen,YLen;

	IntegrationSetXYPixels(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // CHANGEIMAGESIZEDIALOG_H
