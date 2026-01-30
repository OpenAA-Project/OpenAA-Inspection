/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
	bool	SyncMode;

	NextMasterForm	DUp;			//�_�C�A���O����
	EditLibraryForm	EditLibForm;	//

	enum	_ExecuteType{
		_None						=0
		,_OnMasterScanning1			=1
		,_OnMasterScanning2			=2
		,_AfterMasterScanning		=3
		,_OnTargetScanning			=7
		,_AfterTargetScanning		=8
	}ExecuteType;

	bool	ReTeachingFlag;		//�Ċw�K�t���O
	bool	EditLibFormEnable;	//EditLibForm�\���t���O
	bool	StartResister;		//�w�K�X�^�[�g�t���O

	virtual void	BuildForShow(void)	override;

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
	virtual	void	RxSync(QByteArray &f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	bool OnIdle(void)	override;

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