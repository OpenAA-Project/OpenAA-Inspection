/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\StartCaptureButtonForDesktop\StartCaptureButtonForDesktop.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTCAPTUREBUTTONFORDESKTOP_H
#define STARTCAPTUREBUTTONFORDESKTOP_H

#include "startcapturebuttonfordesktop_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButtonColored.h"
#include "NextMasterForm.h"
#include "EditLibraryForm.h"

class	StartCaptureButtonForDesktop : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButtonColored	Button;

	int		ClickOn;
	QTimer	BlickTimer;
	bool	BlinkingMode;
	int		CurrentMasterCounter;
	bool	NextMasterFlag;
	int		ImageReadStateCounter;

	NextMasterForm	DUp;			//ダイアログ画面
	EditLibraryForm	EditLibForm;	//

	enum	_ExecuteType{
		_None						=0
		,_OnMasterScanning1			=1
		,_OnMasterScanning2			=2
		,_AfterMasterScanning		=3
		,_OnTargetScanning			=7
		,_AfterTargetScanning		=8
	}ExecuteType;

	bool	ReTeachingFlag;		//再学習フラグ
	bool	EditLibFormEnable;	//EditLibForm表示フラグ
	bool	StartResister;		//学習スタートフラグ

	virtual void	BuildForShow(void);

	void	SetHoleGerberButton(int LibID,int Index)	{	EditLibForm.SetHoleGerberButton(LibID,Index);	}

public:
	QString	ImageType;	//"Master" "Target"
	QColor	PushedColor;
	bool	DebugMode;

	bool	MasterImageMode;

	StartCaptureButtonForDesktop(LayersBase *Base ,QWidget *parent);
	~StartCaptureButtonForDesktop(void);
	
	virtual void	Prepare(void)	override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void OnIdle(void)	override;

public slots:
	void	SlotClicked (bool checked);
	void	NextMasterFormFinished(int result);
	void	EditLibFormFinished(int result);
	void	ResizeAction();

private slots:
	void	SlotBlickTimer();
};

//================================================================================================================

class	GUICmdReqExecuteInitialAfterEdit : public GUICmdPacketBase
{
public:
	int	CurrentMasterCounter;

	GUICmdReqExecuteInitialAfterEdit(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){	CurrentMasterCounter=0;	}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendExecuteInitialAfterEdit : public GUICmdPacketBase
{
public:

	GUICmdSendExecuteInitialAfterEdit(LayersBase *base,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){}

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//============================================================================================================================
class	GUICmdReqGenerateAutoMaskForDesktop : public GUICmdPacketBase
{
public:
//	int	CurrentMasterCounter;

	GUICmdReqGenerateAutoMaskForDesktop(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendGenerateAutoMaskForDesktop : public GUICmdPacketBase
{
public:

	GUICmdSendGenerateAutoMaskForDesktop(LayersBase *base,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){}

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//============================================================================================================================
class	GUICmdReqExecuteInitialAlloc : public GUICmdPacketBase
{
public:
	int	CurrentMasterCounter;

	GUICmdReqExecuteInitialAlloc(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){}

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendExecuteInitialAlloc : public GUICmdPacketBase
{
public:

	GUICmdSendExecuteInitialAlloc(LayersBase *base,QString EmitterRoot,QString EmitterName ,int globalPage=-1)
		:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage){}

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // STARTCAPTUREBUTTONFORDESKTOP_H
