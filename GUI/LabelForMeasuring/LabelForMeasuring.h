/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LabelForMeasuring\LabelForMeasuring.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LABELFORMEASURING_H
#define LABELFORMEASURING_H

#include "labelformeasuring_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	LabelForMeasuring : public GUIFormBase
{
	Q_OBJECT

	QLabel		MsgLabel;

public:
	QTranslator Translator;
	QStringList	DisplayPanels;
	QFont		LabelFont;
	QString		MsgAlignment;
	QString		FrameShape;
	QString		FrameShadow;
	int32		Precise;
	QColor		MsgColor;

	LabelForMeasuring(LayersBase *Base ,QWidget *parent);
	~LabelForMeasuring(void);
	
	virtual void	Prepare(void)	override;
private slots:
	void	ResizeAction();
	void	SlotMeasure(double L);
private:
};
#endif // LABELFORMEASURING_H
