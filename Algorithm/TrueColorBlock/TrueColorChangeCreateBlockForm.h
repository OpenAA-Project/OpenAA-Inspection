/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\TrueColorChangeCreateBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef TRUECOLORCHANGECREATEBLOCKFORM_H
#define TRUECOLORCHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_TrueColorChangeCreateBlockForm.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class GeneralLibFolderForm;

class TrueColorChangeCreateBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	TrueColorChangeCreateBlockForm(TrueColorBlockBase *base ,QWidget *parent = 0);
	~TrueColorChangeCreateBlockForm();

	TrueColorBlockBase		*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	TrueColorBlockItem		ResultBlock;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(TrueColorBlockItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

private:
	Ui::TrueColorChangeCreateBlockFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // TRUECOLORCHANGECREATEBLOCKFORM_H
