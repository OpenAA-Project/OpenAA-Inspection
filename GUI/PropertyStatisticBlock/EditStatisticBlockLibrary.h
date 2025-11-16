/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\EditStatisticBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef EDITSTATISTICBLOCKLIBRARY_H
#define EDITSTATISTICBLOCKLIBRARY_H

#include <QDialog>
#include "ui_EditStatisticBlockLibrary.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class EditStatisticBlockLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditStatisticBlockLibrary(LayersBase *base ,QWidget *parent);
	~EditStatisticBlockLibrary();

private:
	Ui::EditStatisticBlockLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//StatisticBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	StatisticBlockBase	*GetStatisticBlockBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_checkUseMorphology_toggled(bool checked);
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITSTATISTICBLOCKLIBRARY_H
