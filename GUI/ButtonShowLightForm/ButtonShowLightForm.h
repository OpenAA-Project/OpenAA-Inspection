/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShowLightForm\ButtonShowLightForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSHOWLIGHTFORM_H
#define BUTTONSHOWLIGHTFORM_H

#include "buttonshowlightform_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonShowLightForm : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

	bool	Once;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int		LightNumber;

	ButtonShowLightForm(LayersBase *Base ,QWidget *parent);
	~ButtonShowLightForm(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
};

#endif // BUTTONSHOWLIGHTFORM_H
