#ifndef CARTONMENUFORM_H
#define CARTONMENUFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XParamCustomized.h"

namespace Ui {
class CartonMenuForm;
}

class CartonMenuForm : public GUIFormBase
{
    Q_OBJECT
    friend	class EachSettingDialog;
	friend	class OthersDialog;

	QWidget	*MenuButtons[100];
public:
	QString	StackInstName;
	bool	ShowBlade;
	QStringList	ButtonNameList;

	ParamCustomized		Param;
	ParamForEachMaster	ParamInMaster;

    explicit CartonMenuForm(LayersBase *Base ,QWidget *parent = 0);
    ~CartonMenuForm();
    
	virtual void	ReadyParam(void)	override;
	virtual void	BuildForShow(void)	override;
	ParamCustomized	*GetParam(void)	{	return &Param;	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	void	ExecuteAutoGenerate(void);
	void	SetRun(bool StateRun);
	void	SetInspectionRunOnly(bool StateRun);
	void	OpenRun(void);
	void	OpenSwitchPhase(void);
	void	OpenMask(int n);
	void	OpenAlignment(void);
	void	OpenInspection(void);
	void	OpenBlade(void);
	void	OpenMakeAverage(void);
	void	OpenExposure(void);
	void	MoveForAlignment(void);
	void	CalcFinalize(void);
	void	BuildAlignment(void);
	void	ResetSlaves(void);
	void	AdjustTrigger(void);

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

	void	DeliverTimeoutValue(int timeoutvalue);
	bool	SendTriggerInfo(void);
private slots:
    void on_PushButtonMask_clicked();
    void on_PushButtonAlignment_clicked();
    void on_PushButtonInspection_clicked();
    void on_PushButtonBlade_clicked();
    void on_horizontalSliderLevel_valueChanged(int value);
    void on_PushButtonCheck_clicked();
	void	ResizeAction();
	
    void on_PushButtonRun_clicked();
    void on_PushButtonAutoGenerate_clicked();
    void on_PushButtonSetting_clicked();
    void on_pushButtonSetLevel_clicked();
    void on_horizontalSliderLevel2_valueChanged(int value);
    void on_PushButtonThresholdTop_clicked();
    void on_PushButtonThresholdBottom_clicked();
    void on_PushButtonSwitchPhase_clicked();

    void on_PushButtonEachSetting_clicked();
    void on_PushButtonLotList_clicked();
    void on_PushButtonOther_clicked();
    void on_PushButtonTopDetail_clicked();
    void on_PushButtonBottomDetail_clicked();

    void on_PushButtonColorDifference_clicked();
    void on_PushButtonTopDetail3_clicked();
    void on_PushButtonBottomDetail3_clicked();
    void on_PushButtonMonoDetail3_clicked();
    void on_PushButtonBCode_clicked();
	void	SlotAliveProgress(void);
    void on_PushButtonLotList2_clicked();

signals:
	void	SignalRun(bool pushed);
private:
    Ui::CartonMenuForm *ui;
};

class	IntegrationCartonMenuAutoGen: public IntegrationCmdPacketBase
{
public:
	QString	TargetGUIRoot;
	QString	TargetGUIName;
	QString	TargetGUIInst;

	IntegrationCartonMenuAutoGen(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationSendInsectionLevel: public IntegrationCmdPacketBase
{
public:
	double	Level;	//1.0=Same as origin
	int		Type;	//0:Character Brightness ,1:Charanter Size	2:falt area Brightness ,3:flat area Size

	IntegrationSendInsectionLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationGenerateAutomatically : public GUIDirectMessage
{
public:
	IntegrationGenerateAutomatically(LayersBase *base):GUIDirectMessage(base){}
	IntegrationGenerateAutomatically(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCartonSaveParameter : public GUIDirectMessage
{
public:
	IntegrationCartonSaveParameter(LayersBase *base):GUIDirectMessage(base){}
	IntegrationCartonSaveParameter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationSetRun: public IntegrationCmdPacketBase
{
public:
	bool	RunMode;

	IntegrationSetRun(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationDeliverTimeoutValue: public IntegrationCmdPacketBase
{
public:
	int		TimeoutValue;

	IntegrationDeliverTimeoutValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationDeliverMoveForAlignment: public IntegrationCmdPacketBase
{
public:
	bool	ResetSwitchPhase	;
	bool	ResetMakeAverage	;
	bool	EnableChangeImage	;
	bool	EnableReGenerate	;
	bool	EnableKeepMark		;

	IntegrationDeliverMoveForAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationBuildAlignment: public IntegrationCmdPacketBase
{
public:
	IntList	CadLibID;
	IntegrationBuildAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationResetSlaves: public IntegrationCmdPacketBase
{
public:
	IntegrationResetSlaves(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdSaveParamInMaster : public GUIDirectMessage
{
public:
	CmdSaveParamInMaster(LayersBase *base):GUIDirectMessage(base){}
	CmdSaveParamInMaster(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdRequestCounter : public GUIDirectMessage
{
public:
	int32	TotalCount;
	int32	OKCount;
	int32	NGCount;
	int32	TMCount;	//TimeOut
	bool	Mismatch;
	bool	Ret;

	CmdRequestCounter(LayersBase *base):GUIDirectMessage(base){	Mismatch=false;	}
	CmdRequestCounter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Mismatch=false;	}
};

class	CmdResetCounter : public GUIDirectMessage
{
public:
	bool	Ret;
	CmdResetCounter(LayersBase *base):GUIDirectMessage(base){}
	CmdResetCounter(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationGenerateAlignmentMark : public GUIDirectMessage
{
public:
	IntegrationGenerateAlignmentMark(LayersBase *base):GUIDirectMessage(base){}
	IntegrationGenerateAlignmentMark(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // CARTONMENUFORM_H
