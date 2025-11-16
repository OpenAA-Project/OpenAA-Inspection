/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HalconNGList\HalconNGList.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef HALCONNGLIST_H
#define HALCONNGLIST_H

#include <QTableWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XAlgorithmLibrary.h"
#include "XHalconInspection.h"

class	HalconNGList :public GUIFormBase
{
    Q_OBJECT
public:
	int32	WidthLineNumber;
	int32	WidthPageNumber;
	int32	WidthPosition;
	int32	WidthAttribute;

	HalconNGDataListContainer	NGData;
	AlgorithmLibraryListContainer	LibList;
	QTableWidget	NGList;
	
	QString			TargetImagePanelName;

	HalconNGList(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)							override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

private slots:
	void	ResizeAction();
	void	ListItemClicked ( QTableWidgetItem * item );
	void	ListItemSelectionChanged ();
};


class	GUICmdReqNGList : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGList : public GUICmdPacketBase
{
public:
	HalconNGDataListContainer	NGData;

	GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // HALCONNGLIST_H
