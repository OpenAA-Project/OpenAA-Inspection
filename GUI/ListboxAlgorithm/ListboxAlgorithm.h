/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithm\ListboxAlgorithm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTBOXALGORITHM_H
#define LISTBOXALGORITHM_H

#include "listboxalgorithm_global.h"

#include <QTabWidget>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

class	AlgorithmList : public WMultiGrid ,public ServiceForLayers
{
    Q_OBJECT
public:
	AlgorithmList(LayersBase *Base,QWidget *parent = 0);
	
	virtual	void	ChangeValue(int row ,int col,const QVariant &value)	override;
	virtual	void	GetValue(int row ,int col,QVariant &value)			override;

	void	ShowGrid(void);
};

class	ListboxAlgorithm : public GUIFormBase
{
	Q_OBJECT

	AlgorithmList	MainList;
public:
	bool	IsShowOrganization;
	bool	IsShowPath;
	bool	IsShowRoot;
	bool	IsShowName;

	ListboxAlgorithm(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithm(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};
#endif // LISTBOXALGORITHM_H
