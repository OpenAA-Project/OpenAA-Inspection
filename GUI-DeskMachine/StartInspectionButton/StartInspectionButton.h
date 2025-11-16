/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionButton\StartInspectionButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTINSPECTIONBUTTON_H
#define STARTINSPECTIONBUTTON_H

#include "startinspectionbutton_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
//#include "mtImageToolButtonColored.h"
#include "mtImageButtonColored.h"
#include "XGUIFormBase.h"

class	StartInspectionButton : public GUIFormBase
{
	Q_OBJECT

//	mtImageToolButtonColored	Button;
	mtImageButtonColored	Button;
	bool	Started;
public:
	QColor	PushedColor;
	bool	IsNecessaryLot;

	StartInspectionButton(LayersBase *Base ,QWidget *parent);
	~StartInspectionButton(void);
	
	virtual void	Prepare(void)						override;
	virtual	void keyPressEvent ( QKeyEvent * event )	override;
protected:
	virtual	bool OnIdle(void)	override;
public slots:
//	void SlotClicked (bool checked);
	void SlotClicked ();
private slots:
	void	ResizeAction();
};

//==============================================================
class	GUICmdStartInspect : public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		Layer;
	int32		StrategicNumber;

	GUICmdStartInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdStartInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyInspect : public GUICmdPacketBase
{
public:

	GUICmdReplyInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdReplyInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif // STARTINSPECTIONBUTTON_H
