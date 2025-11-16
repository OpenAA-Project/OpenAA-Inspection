/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoMaskingPI\PropertyAutoMaskingPIForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYAUTOMASKINGPIFORM_H
#define PROPERTYAUTOMASKINGPIFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoMaskingPIForm.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPropertyAutoMaskingPIPacket.h"

class	GeneralLibFolderForm;

class PropertyAutoMaskingPIForm : public GUIFormBase
{
	Q_OBJECT
	AutoMaskingPIListForPacketPack	MaskInfo;
public:
	PropertyAutoMaskingPIForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAutoMaskingPIForm();
	
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

private:
	Ui::PropertyAutoMaskingPIFormClass ui;
	void	ShowAreaGrid(void);

	AutoMaskingPIBase	*GetAutoMaskingPIBase(void);

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//AutoMaskingPILibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_toolButtonCompositeMask_clicked();
	void on_toolButtonIneffectiveMask_clicked();
	void on_toolButtonAutoMask_clicked();
	void on_pushButtonGenerateDefault_clicked();
	void on_pushButtonGenerateLib_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_toolButtonEffectiveMask_clicked();
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // PROPERTYAUTOMASKINGPIFORM_H
