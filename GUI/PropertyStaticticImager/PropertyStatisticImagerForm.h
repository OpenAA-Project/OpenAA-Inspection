/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStaticticImager\PropertyStatisticImagerForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYSTATISTICIMAGERFORM_H
#define PROPERTYSTATISTICIMAGERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyStatisticImagerForm.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XStatisticImager.h"

class PropertyStatisticImagerForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyStatisticImagerForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyStatisticImagerForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private:
	Ui::PropertyStatisticImagerFormClass ui;

private slots:
	void on_toolButtonDisorder_clicked();
	void on_toolButtonLight_clicked();
	void on_toolButtonDark_clicked();
	void on_toolButtonAverage_clicked();
	void on_toolButtonMaster_clicked();
};

//=====================================================

class	CmdGetDrawModeStatistic : public GUIDirectMessage
{
public:
	StatisticImagerDrawAttr::_DrawMode	DrawMode;
	CmdGetDrawModeStatistic(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdReqMakeAverageImage : public GUICmdPacketBase
{
public:

	GUICmdReqMakeAverageImage(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif // PROPERTYSTATISTICIMAGERFORM_H
