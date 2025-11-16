/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\EditColorBlockLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef EDITCOLORBLOCKLIBRARY_H
#define EDITCOLORBLOCKLIBRARY_H

#include <QDialog>
#include "ui_EditColorBlockLibrary.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	GeneralLibFolderForm;

class EditColorBlockLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;
public:
	EditColorBlockLibrary(LayersBase *base ,QWidget *parent);
	~EditColorBlockLibrary();

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;

private:
	Ui::EditColorBlockLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//ColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	ColorBlockBase	*GetColorBlockBase(void);
	void		ShowSubtractList(ColorBlockLibrary &data);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_toolButtonB_clicked();
	void on_toolButtonG_clicked();
	void on_toolButtonR_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_ButtonDelSubtractLib_3_clicked();
	void on_ButtonAddSubtractLib_3_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
	void on_ToolButton_clicked();
	void	MListSectionClicked ( int logicalIndex );
};

#endif // EDITCOLORBLOCKLIBRARY_H
