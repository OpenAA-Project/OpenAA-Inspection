/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\SelectBlockLibraryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTBLOCKLIBRARYFORM_H
#define SELECTBLOCKLIBRARYFORM_H

#include <QDialog>
#include "ui_SelectBlockLibraryForm.h"
#include "XBlockInspection.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class SelectBlockLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectBlockLibraryForm(LayersBase *,QWidget *parent);
	~SelectBlockLibraryForm();

	int	SelectedLibID;

private:
	Ui::SelectBlockLibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // SELECTBLOCKLIBRARYFORM_H
