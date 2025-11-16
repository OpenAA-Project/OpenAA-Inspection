#ifndef EASYPROPERTYSWITCHPHASEFORM_H
#define EASYPROPERTYSWITCHPHASEFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class EasyPropertySwitchPhaseForm;
}

class EasyPropertySwitchPhaseForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int	SlaveNo;
	int	StartPhaseNo;

    explicit EasyPropertySwitchPhaseForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertySwitchPhaseForm();

    virtual void	ReadyParam(void)	override;
	virtual void	LeavePage	(void)	override;

	void	ExeLoadPhaseImage(int Phase);
	void	DeleteAllAdditionalPhases(void);

private slots:
    void on_PushButtonSetPhaseCount_clicked();
    void on_toolButtonCaptureFrom1_clicked();

	void	SlotSwitchedImage(int PhaseNo);
	void	SlotLoadPhaseImage(int Phase);
	void	SlotChangePhase(int phasecode);
    void on_toolButtonFinishCalc_clicked();
    void on_toolButtonDeleteAllAddition_clicked();
    void on_PushButtonAutoGeneration_clicked();

signals:
	void	SignalLoadPhaseImage(int Phase);
	void	SignalBusy();
	void	SignalIdle();
private:
    Ui::EasyPropertySwitchPhaseForm *ui;
};

class	IntegrationCmdScanFrom1 : public IntegrationCmdPacketBase
{
public:
	int	StartPhaseNo;

	IntegrationCmdScanFrom1(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdCancelScan : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdCancelScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	CmdSignalLoadMasterImage : public QObject ,public IntegrationCmdPacketBase
{
public:
	int	Phase;

	CmdSignalLoadMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdMakeAutoGeneration : public QObject ,public IntegrationCmdPacketBase
{
public:
	IntegrationCmdMakeAutoGeneration(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdDeleteAllPhases : public QObject ,public IntegrationCmdPacketBase
{
public:
	IntegrationCmdDeleteAllPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // EASYPROPERTYSWITCHPHASEFORM_H
