/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralLabel\GeneralLabel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALLABEL_H
#define GENERALLABEL_H

#include "generallabel_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GeneralLabel : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;

public:
	QTranslator Translator;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlignAttr;

	enum	CAlignment{
		AlignLeft
		,AlignCenter
	};

	GeneralLabel(LayersBase *Base ,QWidget *parent);
	~GeneralLabel(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
};

#endif // GENERALLABEL_H
