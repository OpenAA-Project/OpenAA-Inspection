#ifndef INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H
#define INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
//#include "mtPushButtonColored.h"
#include "XCameraCommon.h"

namespace Ui {
class IntegrationCameraChangeQuickPropertyForm;
}

class IntegrationCameraChangeQuickPropertyForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
    CameraQuickProperty Attr;
    int                 VValue;
public:
    int		MachineCode;
    QString CameraQuickPropertyStr;

    explicit IntegrationCameraChangeQuickPropertyForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationCameraChangeQuickPropertyForm();
     virtual	void	ReadyParam(void)	override;

private slots:
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();

private:
    Ui::IntegrationCameraChangeQuickPropertyForm *ui;
};
//===========================================================================

class	IntegrationCmdCameraChangeQuickProperty: public IntegrationCmdPacketBase
{
public:
    CameraQuickProperty Attr;
    int                 VValue;

	IntegrationCmdCameraChangeQuickProperty(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONCAMERACHANGEQUICKPROPERTYFORM_H
