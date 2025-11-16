/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorCreateManualBlockForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef COLORCREATEMANUALBLOCKFORM_H
#define COLORCREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_ColorCreateManualBlockForm.h"
#include "XColorBlockInspection.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	GeneralLibFolderForm;

class ColorCreateManualBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;
public:
	ColorCreateManualBlockForm(LayersBase *Base,QWidget *parent);
	~ColorCreateManualBlockForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	ColorBlockItem			*BItem;

	void	Reflect(void);
private:
	Ui::ColorCreateManualBlockFormClass ui;

	void	GetDataFromWindow(ColorBlockItem &data);
	//ColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					BlockLibID;

	void ShowLibrary(AlgorithmLibraryLevelContainer	*tempLib);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_ToolButton_clicked();
};

#endif // CREATEMANUALBLOCKFORM_H
