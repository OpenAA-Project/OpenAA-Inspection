/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAreaFilter\SelectAreaFilterLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTAREAFILTERLIBRARY_H
#define SELECTAREAFILTERLIBRARY_H

#include <QDialog>
#include "ui_SelectAreaFilterLibrary.h"
#include "XServiceForLayers.h"
#include "XAreaFilter.h"

class	GeneralLibFolderForm;

class SelectAreaFilterLibrary : public QDialog , public ServiceForLayers
{
	Q_OBJECT

public:
	SelectAreaFilterLibrary(LayersBase *base ,QWidget *parent);
	~SelectAreaFilterLibrary();

	int	SelectedLibID;

private:
	Ui::SelectAreaFilterLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_itemDoubleClicked(QTableWidgetItem*);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // SELECTAREAFILTERLIBRARY_H
