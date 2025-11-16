/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowAlignmentGap\ShowAlignmentGapForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWALIGNMENTGAPFORM_H
#define SHOWALIGNMENTGAPFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowAlignmentGapForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAutoAlignment.h"

class ShowAlignmentGapForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowAlignmentGapForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowAlignmentGapForm();

	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowAlignmentGapFormClass ui;

private slots:
	void	ResizeAction();
};

class	GUICmdReqAlignGap : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignGap : public GUICmdPacketBase
{
public:
	GUICmdSendAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
/*
	struct GapXY{
		int	X,Y;
		int	GapX,GapY;
	};
	struct GapXY FirstPoint,SecondPoint,ThirdPoint;
*/
	int	FirstX,FirstY;
	int	FirstGapX,FirstGapY;
	int	SecondX,SecondY;
	int	SecondGapX,SecondGapY;
	int	ThirdX,ThirdY;
	int	ThirdGapX,ThirdGapY;
};

#endif // SHOWALIGNMENTGAPFORM_H
