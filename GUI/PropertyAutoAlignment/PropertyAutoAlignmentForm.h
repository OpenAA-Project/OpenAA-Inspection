/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoAlignment\PropertyAutoAlignmentForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYAUTOALIGNMENTFORM_H
#define PROPERTYAUTOALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAutoAlignmentForm.h"
#include "XAutoAlignment.h"
#include "XAutoAlignmentCommon.h"
#include "XStandardPropertyForm.h"

class PropertyAutoAlignmentForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyAutoAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAutoAlignmentForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	GenerateBlocks(void);
private:
	Ui::PropertyAutoAlignmentFormClass ui;
	AutoAlignmentBase	*GetAutoAlignmentBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	void	ShowAreaList(void);
	virtual void	BuildForShow(void)	override;

	//AutoAlignmentLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int						LibType;
	AASheetInfos			AAInfos;
	IntList					SheetLevels;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	void SendState(void);

private slots:
	void on_comboBoxMonoLevel_textChanged(const QString &);
	void on_radioButtonSheetPickup_toggled(bool);
	void on_radioButtonSheetArea_toggled(bool);
	void on_radioButtonSheetNone_toggled(bool);
	void on_checkBoxPicoInfo_stateChanged(int);
	void on_checkBoxFringeArea_stateChanged(int);
	void on_checkBoxPicoOtherView_stateChanged(int);
	void on_checkBoxPicoPickupView_stateChanged(int);
	void on_checkBoxPicoTransView_stateChanged(int);
	void on_checkBoxMonoView_stateChanged(int);
	void on_groupBox_toggled(bool);
	void on_tableWidgetAreaList_clicked(const QModelIndex &);
	void on_pushButtonUpdateView_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_pushButtonEditLibFolder_clicked();
	void on_pushButtonEditLibrary_clicked();
	void ButtonPickupTestClicked();
	void radioButtonSheetPickupTestToggled(bool);
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
};

//======================================================================================================

#endif // PROPERTYAUTOALIGNMENTFORM_H
