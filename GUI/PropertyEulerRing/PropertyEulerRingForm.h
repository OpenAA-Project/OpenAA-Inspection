/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\PropertyEulerRingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYEULERRINGFORM_H
#define PROPERTYEULERRINGFORM_H

#include "ui_PropertyEulerRingForm.h"
#include "XGUIFormBase.h"
#include "XEulerRing.h"
#include "XEulerRingLibrary.h"
#include "ShowRGBCube.h"
#include "XStandardPropertyForm.h"

class PropertyEulerRingForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyEulerRingForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyEulerRingForm();


	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;


private:
	//EulerRingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowSelectedLibList(void);
	void	ShowLibList(void);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	EulerRingBase	*GetEulerRingBase(void);
	QTabBar	TabBarBlockOnMouse;

	ShowRGBSpace	ColorGeneratorH;
	ShowRGBSpace	ColorGeneratorC;
	ShowRGBSpace	ColorInspection;

	struct	BlockItemWithPageLayer{
		EulerRingItem	*EulerRingInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	BlockItemWithPageLayer	BInfo[100];

	NPListPack<EulerRingInfoList>	EulerRingInfos;

	void		ShowBlockInfoList(void);
	void		ShowTab(void);

private:
	Ui::PropertyEulerRingFormClass ui;

private slots:
	void on_pushButtonGetBackAll_clicked();
	void on_pushButtonSetFromAll_clicked();
	void on_pushButtonCColor_clicked();
	void on_tableWidgetBlockInfo_clicked(const QModelIndex &);
	void on_pushButtonGColor_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonGenerateLibs_clicked();
	void on_ButtonPickupClearTest_clicked();
	void on_ButtonPickupTest_clicked();
	void on_pushButtonEditLibrary_clicked();
	void on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex);
	void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &);
	void on_pushButtonGetBack_clicked();
	void on_pushButtonSetFrom_clicked();
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonEditLibFolder_clicked();
	void on_toolButtonCreateBlock_clicked();
	void on_toolButtonLibrary_clicked();
	void	TabBarBlockOnMouseChanged(int);
};

#endif // PROPERTYEULERRINGFORM_H
