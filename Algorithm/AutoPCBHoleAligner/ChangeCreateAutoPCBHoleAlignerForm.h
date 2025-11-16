/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoPCBHoleAligner\ChangeCreateAutoPCBHoleAlignerForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CHANGECREATEBLOCKFORM_H
#define CHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_ChangeCreateAutoPCBHoleAlignerForm.h"
#include "XAutoPCBHoleAligner.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class ChangeCreateAutoPCBHoleAlignerForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	ChangeCreateAutoPCBHoleAlignerForm(AutoPCBHoleAlignerBase *base ,QWidget *parent);
	~ChangeCreateAutoPCBHoleAlignerForm();

	AutoPCBHoleAlignerBase		*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	AutoPCBHoleAlignerHole		ResultAutoPCBHoleAligner;
	GeneralLibFolderForm		*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(AutoPCBHoleAlignerHole &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
private:
	Ui::ChangeCreateAutoPCBHoleAlignerFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CHANGECREATEBLOCKFORM_H
