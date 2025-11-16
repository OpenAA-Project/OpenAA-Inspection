/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabWizardNext\GeneralTabWizardNext.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALTABWIZARDNEXT_H
#define GENERALTABWIZARDNEXT_H

#include "generaltabwizardnext_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GeneralTabWizardNext : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QTranslator Translator;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	TagWizardName;

	GeneralTabWizardNext(LayersBase *Base ,QWidget *parent);
	~GeneralTabWizardNext(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // GENERALTABWIZARDNEXT_H
