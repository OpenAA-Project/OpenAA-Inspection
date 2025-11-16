/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonToShowOtherGUI\ButtonToShowOtherGUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONTOSHOWOTHERGUI_H
#define BUTTONTOSHOWOTHERGUI_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QColor>
#include <QFont>

class	ButtonToShowOtherGUI : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	GUIFileName;
	GUIFormBase	*CurrentGUI;

	ButtonToShowOtherGUI(LayersBase *Base ,QWidget *parent);
	~ButtonToShowOtherGUI(void);
	
	virtual void	Prepare(void)	override;
	//virtual	void	AssociateComponent(ComponentListContainer &List)	override;
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
	void	SlotClicked( bool checked );
	void	ResizeAction();
};


#endif // BUTTONTOSHOWOTHERGUI_H
