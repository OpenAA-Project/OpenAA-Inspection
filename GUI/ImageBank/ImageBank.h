#ifndef IMAGEBANK_H
#define IMAGEBANK_H

#include "imagebank_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMainSchemeMemory.h"
#include <QToolButton>
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QFont>

class	ImageBankListForm;
class	StartProcessAgainButton;

class	ImageBankInPage : public NPList<ImageBankInPage>
{
public:
	ImageBufferListContainer	ImageInLayers;

	ImageBankInPage(void){}
};

class	ImageBankInPhase : public NPList<ImageBankInPhase>
{
public:
	NPListPack<ImageBankInPage>	ImageInPages;

	ImageBankInPhase(void){}

};

class	ImageInInspection : public NPList<ImageInInspection>
{
public:
	NPListPack<ImageBankInPhase>	ImageInPhases;
	XDateTime		Time;
	int64			InspectionID;
	bool			ResultOK;
	int64			LoadedID;
	int32			LotAutoCount;
	int32			ProcessMSec;

	ImageInInspection(void){	InspectionID=-1;	ResultOK=true;	}

	QString	MakeFileName(void);
};


class	ImageBank : public GUIFormBase
{
    Q_OBJECT

	ButtonRightClickEnabler	*RButton;
	QToolButton	*Button;
	ImageBankListForm	*Form;
	int64				LastInspectionID;
	int64				LoadedID;
public:
	NPListPack<ImageInInspection>	Bank;
	int		WPoint;
	bool	BootON;
	bool	StoreOnlyOK;
	bool	StoreOnlyNG;
    GUIFormBase     *StartProcessAgainDim[100];
    int             CountOfStartProcessAgain;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	ListCount;
	QString	LastPath;
	bool	Pushed;

	ImageBank(LayersBase *Base ,QWidget *parent = 0);
	~ImageBank();

	void	AllocateImages(void);
	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)				override;
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)override;
	bool	RestoreToTarget(int row);
	bool	RestoreToTarget(ImageInInspection *a);
	void	CloseFowm(void);
	void	ClearBank(void);
	void	RetryBank(void);

	void	SaveAll(const QString &Path);

	virtual ExeResult	ExecutePostProcessing(void)	override;

private:
	bool	ExecuteOne(void);
	int		GetIndexFromRow(int Row);
	bool	IsProcessAgain(void);
signals:
	void	SignalUpdateList();

private slots:
	void	SlotClicked();
	void	SlotRClicked(QAbstractButton *obj);
	void	ResizeAction();
	void	SlotUpdateList();
};

class	GUICmdReqResult : public GUICmdPacketBase
{
public:
	int64		ShownInspectionID;

	GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResult : public GUICmdPacketBase
{
public:
	bool	ResultOK;

	GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdPushed : public GUICmdPacketBase
{
public:
	int64	InspectionID;
	int32	MaxInspectMilisec;

	GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckPushed : public GUICmdPacketBase
{
public:
	bool	Ok;
	int		NGCount;

	GUIAckPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	CmdInspectionAgainReplied : public GUICmdPacketBase
{
public:
	enum	__Result
	{
		_OK			=1
		,_NG		=2
		,_Nothing	=3
	}Result;
	int64		NGCounts;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	int			ExecuterID;

	CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdSetStateImageBank : public GUIDirectMessage
{
public:
	bool	ONMode;
	bool	StoreOnlyOK;
	bool	StoreOnlyNG;
	int32	ListCount;
	CmdSetStateImageBank(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetClearImageBank : public GUIDirectMessage
{
public:
	CmdSetClearImageBank(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdSwitchImageBank : public GUIDirectMessage
{
public:
	int64			LoadedID;

	CmdSwitchImageBank(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdRetryImageBank : public GUIDirectMessage
{
public:
	CmdRetryImageBank(LayersBase *base):GUIDirectMessage(base){}
};

#endif // IMAGEBANK_H
