/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\TrueColorCreateManualBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef TRUECOLORCREATEMANUALBLOCKFORM_H
#define TRUECOLORCREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_TrueColorCreateManualBlockForm.h"
#include "XTrueColorBlock.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class TrueColorCreateManualBlockForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	TrueColorCreateManualBlockForm(LayersBase *Base,QWidget *parent);
	~TrueColorCreateManualBlockForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	TrueColorBlockItem			*BItem;

	void	Reflect(void);

private:
	Ui::TrueColorCreateManualBlockFormClass ui;
	//TrueColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int						BlockLibID;

	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

	void	GetDataFromWindow(TrueColorBlockItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // TRUECOLORCREATEMANUALBLOCKFORM_H
