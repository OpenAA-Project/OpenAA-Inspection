/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\ColorChangeCreateBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef COLORCHANGECREATEBLOCKFORM_H
#define COLORCHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_ColorChangeCreateBlockForm.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	GeneralLibFolderForm;

class ColorChangeCreateBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;

public:
	ColorChangeCreateBlockForm(ColorBlockBase *base ,QWidget *parent = 0);
	~ColorChangeCreateBlockForm();

	ColorBlockBase			*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	ColorBlockItem			ResultBlock;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(ColorBlockItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
private:
	Ui::ColorChangeCreateBlockFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_ToolButton_clicked();
};

#endif // ColorCHANGECREATEBLOCKFORM_H
