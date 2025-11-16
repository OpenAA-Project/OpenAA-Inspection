/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\SelectMaskingLibraryForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SELECTMaskingLIBRARYFORM_H
#define SELECTMaskingLIBRARYFORM_H

#include <QDialog>
#include "ui_SelectMaskingLibraryForm.h"
#include "XMasking.h"
#include "XServiceForLayers.h"

class	AlgorithmLibraryLevelContainer;
class	GeneralLibFolderForm;

class SelectMaskingLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectMaskingLibraryForm(LayersBase *,QWidget *parent);
	~SelectMaskingLibraryForm();

	int	SelectedLibID;

private:
	Ui::SelectMaskingLibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // SELECTMaskingLIBRARYFORM_H
