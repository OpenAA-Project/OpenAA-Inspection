/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\ChangeCreateBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CHANGECREATEBLOCKFORM_H
#define CHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_ChangeCreateBlockForm.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class ChangeCreateBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	ChangeCreateBlockForm(BlockBase *base ,int Layer ,QWidget *parent);
	~ChangeCreateBlockForm();

	BlockBase		*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	BlockItem				ResultBlock;
	GeneralLibFolderForm	*pLibFolderForm;
	int						PastedLayer;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(BlockItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
private:
	Ui::ChangeCreateBlockFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CHANGECREATEBLOCKFORM_H
