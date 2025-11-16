/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNaming\PropertyNamingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYNAMINGFORM_H
#define PROPERTYNAMINGFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyNamingForm.h"
#include "XGUIPacketForDLL.h"
#include "XPropertyNamingPacket.h"

class PropertyNamingForm : public GUIFormBase
{
    Q_OBJECT
	NamingListForPacketPack	NamingInfo;
	NamingGroupContainer	NamingGroupData;
public:
    PropertyNamingForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyNamingForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	void	ShowGrid(void);
	void	ShowGroupGrid(void);
	void	CreateArea(const QString &AreaName,FlexArea &Area
						,int Column ,int Row
						,int Expand);
private:
    Ui::PropertyNamingFormClass ui;
private slots:
	void on_pushButton_CreateItemFromItsCoordinate_clicked();
	void on_tableWidgetNamingList_clicked(const QModelIndex &);
	void on_pushButtonExecute_clicked();
	void on_tableWidget_cellDoubleClicked(int,int);
    void on_toolButtonAutoCount_clicked();
    void on_toolButtonMakeGroup_clicked();
    void on_listWidgetGroup_clicked(const QModelIndex &index);
    void on_pushButtonClearSelectedGroup_clicked();
	void on_pushButtonGenerateIndex_clicked();
};


#endif // PROPERTYNAMINGFORM_H
