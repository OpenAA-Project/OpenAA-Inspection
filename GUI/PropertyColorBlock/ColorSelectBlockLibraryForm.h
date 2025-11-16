/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorSelectBlockLibraryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef COLORSELECTBLOCKLIBRARYFORM_H
#define COLORSELECTBLOCKLIBRARYFORM_H

#include <QDialog>
#include "ui_ColorSelectBlockLibraryForm.h"
#include "XColorBlockInspection.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class ColorSelectBlockLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	ColorSelectBlockLibraryForm(LayersBase *,QWidget *parent);
	~ColorSelectBlockLibraryForm();

	int	SelectedLibID;

private:
	Ui::ColorSelectBlockLibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // COLORSELECTBLOCKLIBRARYFORM_H
