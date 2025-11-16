/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\PropertyHalconForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYHALCONFORM_H
#define PROPERTYHALCONFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyHalconForm.h"
#include "XGUIPacketForDLL.h"
#include "XPropertyHalconInspectionPacket.h"

class	GeneralLibFolderForm;

class PropertyHalconForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyHalconForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyHalconForm();

	HalconSampleList		*TempSample;
	HalconInspectionLibrary	*TempLib;

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	QString	ImagePanelName;

private:
	Ui::PropertyHalconFormClass ui;

	GeneralLibFolderForm	*pLibFolderForm;

	int		LibType;
	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	HalconInspectionBase	*GetHalconInspectionBase(void);
	void ShowSampleList(void);

private slots:
	void SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void tableViewSampleListDoubleClicked(const QModelIndex &CIndex);
	void on_pushButtonDelete_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonRegist_2_clicked();
	void on_pushButtonDeleteLib_clicked();
	void on_pushButtonUpdateLib_clicked();
	void on_pushButtonRegistLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
};

#endif // PROPERTYHALCONFORM_H
