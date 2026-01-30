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


#ifndef CERAMICSURFACEMENUPROPERTY_H
#define CERAMICSURFACEMENUPROPERTY_H

#include "ui_CeramicSurfaceMenuProperty.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

#include "StartInspectionButton.h"

class CeramicSurfaceMenuProperty : public GUIFormBase
{
	Q_OBJECT

	StartInspectionButton		InspectButton;

public:
	CeramicSurfaceMenuProperty(LayersBase *Base ,QWidget *parent = 0);
	~CeramicSurfaceMenuProperty();
	QFont	CFont;

	mtToolButtonColored		ToolButtonTarget;

private:
	Ui::CeramicSurfaceMenuPropertyClass ui;
	QTimer	BlickTimer;

	enum	_ExecuteType{
		_None						=0
//		,_OnMasterScanning1			=1
//		,_OnMasterScanning2			=2
//		,_AfterMasterScanning		=3
		,_OnTargetScanning			=7
		,_AfterTargetScanning		=8
	}ExecuteType;

	QColor	NormalColor;
	QColor	WaitingColor;
	QColor	ScanningColor;
	QColor	DoneColor;
	bool	BlinkingMode;
	int		CurrentMasterCounter;

	void	ChangeButtonType(mtToolButtonColored *Dest ,QToolButton *Src);
	void	SetButtonColor(mtToolButtonColored *Btn ,QColor &Col);
	
	virtual	void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonDetail_clicked();
	void on_toolButtonScanTarget_clicked();
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

#endif // CERAMICSURFACEMENUPROPERTYFORMMC_H