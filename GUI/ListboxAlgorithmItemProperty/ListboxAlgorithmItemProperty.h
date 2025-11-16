/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxAlgorithmItemProperty\ListboxAlgorithmItemProperty.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTBOXALGORITHMITEMPROPERTY_H
#define LISTBOXALGORITHMITEMPROPERTY_H

#include "listboxalgorithmitemproperty_global.h"
#include <QTabWidget>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WMultiGrid.h"

#include "AlgorithmItemPropertyGrid.h"


class	ListboxAlgorithmItemProperty : public GUIFormBase
{
	Q_OBJECT

public:
	AlgorithmItemPropertyGrid	MainList;
	AlgorithmItemPropertyContainer AlgorithmItemPropertyData;

	ListboxAlgorithmItemProperty(LayersBase *Base ,QWidget *parent);
	~ListboxAlgorithmItemProperty(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};
#endif // LISTBOXALGORITHMITEMPROPERTY_H
