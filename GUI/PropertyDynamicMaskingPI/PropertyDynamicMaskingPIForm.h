/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicMaskingPI\PropertyDynamicMaskingPIForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYDYNAMICMASKINGPIFORM_H
#define PROPERTYDYNAMICMASKINGPIFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyDynamicMaskingPIForm.h"
#include "XGUIPacketForDLL.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDynamicMaskingPI.h"

class PropertyDynamicMaskingPIForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyDynamicMaskingPIForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyDynamicMaskingPIForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	ShowRGBSpace	MaskingColor;
	DynamicMaskingPIInfoListContainer	List;

private:
	Ui::PropertyDynamicMaskingPIFormClass ui;

	DynamicMaskingPIBase	*GetDynamicMaskingPIBase(void);
	void	ShowInfoList(void);
	bool	ShowItemProperty(int ShownRow);
	void	SetLayersFromLib(IntList &LayerList);

private slots:
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
    void on_pushButtonSet_clicked();
    void on_radioButtonPickupMask_clicked();
    void on_radioButtonDrawMask_clicked();
};

#endif // PROPERTYDYNAMICMASKINGPIFORM_H
