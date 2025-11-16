/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAreaFilter\PropertyAreaFilterForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PROPERTYAREASHADERFORM_H
#define PROPERTYAREASHADERFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyAreaShaderForm.h"
#include "XAreaShader.h"
#include "XStandardPropertyForm.h"

//===========================================================================

class PropertyAreaShaderForm : public GUIFormBase,public StandardPropertyForm
{
	Q_OBJECT

public:
	PropertyAreaShaderForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyAreaShaderForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyAreaShaderFormClass ui;

	AreaShaderBase	*GetAreaShaderBase(void);
	void	ShowAreaGrid(void);

	AreaShaderListForPacketPack	AreaShaderInfo;

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);

	//AreaShaderLibrary		*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

private slots:
	void on_tableWidgetAreaShader_clicked(const QModelIndex &);
        void on_pushButtonEditLibFolder_clicked();
        void on_tableWidgetLibList_clicked(const QModelIndex &index);
        void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
        void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
        void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
        void on_pushButtonSetFrom_clicked();
        void on_pushButtonGetBack_clicked();
        void on_pushButtonSetFromAll_clicked();
        void on_pushButtonGetBackAll_clicked();
        void on_ButtonPickupTest_clicked();
        void on_ButtonPickupClearTest_clicked();
        void on_pushButtonEditLibrary_clicked();
        void on_ButtonGenerateLibs_clicked();
        void on_ButtonLibSave_clicked();
        void on_tabWidget_currentChanged(int index);
};

//===========================================================================


#endif // PROPERTYAREASHADERFORM_H
