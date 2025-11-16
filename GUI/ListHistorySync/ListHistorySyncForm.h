/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistorySync\ListHistorySyncForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTHISTORYSYNCFORM_H
#define LISTHISTORYSYNCFORM_H

#include "XGUIFormBase.h"
#include "ui_ListHistorySyncForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XResult.h"

class	ResultsList : public NPList<ResultsList>,public ServiceForLayers
{
public:
	int32					MachineCode;
	ResultHistryContainer	List;
	
	ResultsList(LayersBase *base);
	void	Set(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ResultsList	&operator=(ResultsList &src);
};

class ListHistorySyncForm : public GUIFormBase
{
	Q_OBJECT
	
	NPListPack<ResultsList>		RList;

public:
	ListHistorySyncForm(LayersBase *Base ,QWidget *parent = 0);
	~ListHistorySyncForm();

	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ListHistorySyncFormClass ui;


	virtual	void	RxSync(QByteArray &f)	override;

private slots:
	void on_ButtonReset_clicked();
	void	ResizeAction();
};

#endif // LISTHISTORYSYNCFORM_H
