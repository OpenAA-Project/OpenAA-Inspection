/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\EditBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef EDITBLOCKLIBRARY_H
#define EDITBLOCKLIBRARY_H

#include <QDialog>
#include "ui_EditBlockLibrary.h"
#include "XBlockInspection.h"
#include "XBlockLibrary.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	GeneralLibFolderForm;

class EditBlockLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditBlockLibrary(LayersBase *base ,QWidget *parent);
	~EditBlockLibrary();

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private:
	Ui::EditBlockLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//BlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	BlockBase	*GetBlockBase(void);
	void		ShowSubtractList(BlockLibrary &data);
	AlgorithmLibraryListContainer	LibList;
	QList<QToolButton *>	LayerPickButtons;
	QList<QToolButton *>	LayerGenButtons;

private slots:
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_ButtonDelSubtractLib_clicked();
	void on_ButtonAddSubtractLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
	void	MListSectionClicked ( int logicalIndex );
    void on_checkBoxGenerateMultiLayer_clicked();
    void on_checkBoxPickupMultiLayer_clicked();
};

#endif // EDITBLOCKLIBRARY_H
