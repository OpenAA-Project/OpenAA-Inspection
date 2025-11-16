/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\PropertyAlignmentForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYALIGNMENTFORM_H
#define PROPERTYALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAlignmentForm.h"
#include "WMultiGrid.h"
#include "PropertyAlignmentPacket.h"

class PropertyAlignmentForm : public GUIFormBase
{
    Q_OBJECT

public:
    PropertyAlignmentForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyAlignmentForm();

	ReqAlignmentAreaListPack	AreaListFromMaster;
	AlignmentAreaListPack	AreaList;
	AlignmentPointListPack	PointList;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)		override;
	void	CreateAndShowPointGrid(void);
	virtual void	StartPage	(void)		override;

	void	CreateAlignmentArea(FlexArea &area);
	void	CreateAlignmentPoint(FlexArea &area ,int MoveDot ,int Threshold ,bool AlignmentOnOutline);

private:
    Ui::PropertyAlignmentFormClass ui;
	void	ShowAreaGrid(void);
	void	ShowPointGrid(AlignmentAreaList *A);
	void	ShowPointGridRaw(void);
	void	CreatePointList(AlignmentAreaList *A);
	GUIFormBase	*GetImageControlToolsPointer(void);

private slots:
	void on_toolButtonGroup_clicked();
	void on_toolButtonPoint_clicked();
	void on_toolButtonArea_clicked();
	void on_tableWidgetPoint_itemDoubleClicked(QTableWidgetItem*);
	void on_tableWidgetArea_doubleClicked(QModelIndex);
	void on_tableWidgetArea_clicked(const QModelIndex &);
};
//===========================================================================

#endif // PROPERTYALIGNMENTFORM_H
