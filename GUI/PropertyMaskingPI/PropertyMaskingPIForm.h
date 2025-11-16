/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMaskingPI\PropertyMaskingPIForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYMASKINGPIFORM_H
#define PROPERTYMASKINGPIFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMaskingPIForm.h"
#include "XGUIPacketForDLL.h"
#include "XPropertyMaskingPIPacket.h"

class PropertyMaskingPIForm : public GUIFormBase
{
	Q_OBJECT
	MaskingPIListForPacketPack	MaskInfo;
public:
	PropertyMaskingPIForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMaskingPIForm();
	
	virtual	void	BuildForShow(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)		override;

private:
	Ui::PropertyMaskingPIFormClass ui;
	void	ShowAreaGrid(void);

private slots:
	void on_toolButtonIneffective_clicked();
	void on_toolButtonEffective_clicked();
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
};

#endif // PROPERTYMASKINGPIFORM_H
