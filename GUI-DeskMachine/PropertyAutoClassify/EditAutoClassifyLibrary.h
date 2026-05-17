/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\PropertyAutoClassify\EditAutoClassifyLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef EDITAUTOCLASSIFYLIBRARY_H
#define EDITAUTOCLASSIFYLIBRARY_H

#include <QDialog>
#include <QModelIndex>
#include "ui_EditAutoClassifyLibrary.h"
#include "LibFolderForm.h"
#include "XAutoClassify.h"
#include "XServiceForLayers.h"

class GeneralLibFolderForm;

class EditAutoClassifyLibrary : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditAutoClassifyLibrary(LayersBase *base ,QWidget *parent = 0);
	~EditAutoClassifyLibrary();

private:
	Ui::EditAutoClassifyLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AutoClassifyBase	*GetAutoClassifyBase(void);
	AlgorithmLibraryListContainer	LibList;


private slots:
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITAUTOCLASSIFYLIBRARY_H
