#ifndef INTEGRATIONSHOWMEMORYFORM_H
#define INTEGRATIONSHOWMEMORYFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "ShowMemoryForm.h"

namespace Ui {
class IntegrationShowMemoryForm;
}

class IntegrationShowMemoryForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
    
    QTimer	TM;
public:
	QFont	CFont;

	struct	__MachineMemory
	{
		struct	__ShowMemoryStruct	ShowMemoryStruct;
		struct	__ShowMemoryStruct	*ShowMemoryStructInSlave;
		int		SlavePageNumb;

		__MachineMemory(void){
			ShowMemoryStructInSlave=NULL;
		}
	}MachineMemory[10];

	explicit IntegrationShowMemoryForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowMemoryForm();
    
    virtual void	Prepare(void)	override;

	void	ShowGrid(void);
private:
    Ui::IntegrationShowMemoryForm *ui;

signals:
	void	SignalShowMemory();
private slots:
	void	SlotTimeout();
	void	ResizeAction();
};

//=================================================================================================

class	CmdReqMemoryInfoToMaster : public IntegrationCmdPacketBase
{
public:
	CmdReqMemoryInfoToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdSendMemoryInfoToMaster : public IntegrationCmdPacketBase
{
public:
	struct	__ShowMemoryStruct	ShowMemoryStruct;
	struct	__ShowMemoryStruct	ShowMemoryStructInSlave[10];
	int		SlavePageNumb;

	CmdSendMemoryInfoToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif // INTEGRATIONSHOWMEMORYFORM_H
