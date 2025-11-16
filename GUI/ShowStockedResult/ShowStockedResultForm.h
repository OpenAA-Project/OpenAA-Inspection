/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowStockedResult\ShowStockedResultForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWSTOCKEDRESULTFORM_H
#define SHOWSTOCKEDRESULTFORM_H


#include "XGUIFormBase.h"
#include "ui_ShowStockedResultForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowStockedResultForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowStockedResultForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowStockedResultForm();

	virtual void	Prepare(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowStockedResultFormClass ui;

private slots:
	void on_pushButtonCast_clicked();
	void on_pushButtonForceWrite_clicked();
};

//---------------------------------------------------------------------

class	GUICmdReqStockedResultCount : public GUICmdPacketBase
{
public:
	GUICmdReqStockedResultCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendStockedResultCount : public GUICmdPacketBase
{
public:
	int		StockedResultCount;

	GUICmdSendStockedResultCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqCastStockedResult : public GUICmdPacketBase
{
public:
	GUICmdReqCastStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWSTOCKEDRESULTFORM_H
