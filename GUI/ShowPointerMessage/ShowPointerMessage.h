/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowPointerMessage\ShowPointerMessage.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWPOINTERMESSAGE_H
#define SHOWPOINTERMESSAGE_H

#include "showpointermessage_global.h"
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtColorFrame.h"

class	ShowPointerMessage : public GUIFormBase
{
	Q_OBJECT

	QLabel			Label;

	class	LayerInfoList : public NPList<LayerInfoList>
	{
	public:
		mtColorFrame	*Panel;
		QLabel			Label;
	};
	NPListPack<LayerInfoList>	LayerDatas;

public:
	QFont		MessageFont;
	QStringList	RelatedPanels;
	bool		ShowRealPosition;

	ShowPointerMessage(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
private slots:
	void	ResizeAction();
	void	SlotPointColor(int meterX, int meterY ,QColor &Ret);
};


#endif // SHOWPOINTERMESSAGE_H
