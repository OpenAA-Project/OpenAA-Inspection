#ifndef INTEGRATIONOUTPUTCONTROLBUTTONFORM_H
#define INTEGRATIONOUTPUTCONTROLBUTTONFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationPacketComm.h"
#include "..\ResultKidaOutput\ResultKidaOutput.h"

namespace Ui {
class IntegrationOutputControlButtonForm;
};


class IntegrationOutputControlButtonForm : public GUIFormBase
{
    Q_OBJECT
    
	bool	ReEntrant;
public:
	_OutputControlMode	CurrentMode;

    explicit IntegrationOutputControlButtonForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationOutputControlButtonForm();
	virtual void	ReadyParam(void)	override;
private slots:
	void	ResizeAction();

private:
    Ui::IntegrationOutputControlButtonForm *ui;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
};

class	GUICmdIntegrationSetControlOutput: public IntegrationCmdPacketBase
{
public:
	_OutputControlMode		ControlMode;

	GUICmdIntegrationSetControlOutput(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONOUTPUTCONTROLBUTTONFORM_H
