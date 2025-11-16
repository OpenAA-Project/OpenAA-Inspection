/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRingL1\SelectEulerRingL1LibraryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTEulerRingL1LIBRARYFORM_H
#define SELECTEulerRingL1LIBRARYFORM_H

#include <QDialog>
#include "ui_SelectEulerRingL1LibraryForm.h"
#include "XEulerRingL1.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class SelectEulerRingL1LibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectEulerRingL1LibraryForm(LayersBase *,QWidget *parent);
	~SelectEulerRingL1LibraryForm();

	int	SelectedLibID;

private:
	Ui::SelectEulerRingL1LibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // SELECTEulerRingL1LIBRARYFORM_H
