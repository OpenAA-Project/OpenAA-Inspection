/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\CreateManualBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef CREATEMANUALBLOCKFORM_H
#define CREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_CreateManualBlockForm.h"
#include "XBlockInspection.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CreateManualBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;
	int	PastedLayer;
public:
	CreateManualBlockForm(LayersBase *Base,int Layer,QWidget *parent);
	~CreateManualBlockForm();
	
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	BlockItem			*BItem;

	void	Reflect(void);
private:
	Ui::CreateManualBlockFormClass ui;

	void	GetDataFromWindow(BlockItem &data);
	//BlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int				BlockLibID;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
};

#endif // CREATEMANUALBLOCKFORM_H
