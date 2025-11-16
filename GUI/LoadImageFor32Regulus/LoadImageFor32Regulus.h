/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadImageFor32Regulus\LoadImageFor32Regulus.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LOADIMAGEFOR32REGULUS_H
#define LOADIMAGEFOR32REGULUS_H

#include <QLabel>
#include <QTranslator>
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	LoadImageFor32Regulus : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	LoadImageFor32Regulus(LayersBase *Base ,QWidget *parent);
	~LoadImageFor32Regulus(void);
	
	virtual void	Prepare(void)	override;

private:
	bool LoadImageToMaster(FILE *file);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


#endif // LOADIMAGEFOR32REGULUS_H
