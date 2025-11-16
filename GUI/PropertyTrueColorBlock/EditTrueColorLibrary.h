/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\EditTrueColorLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef EDITTRUECOLORLIBRARY_H
#define EDITTRUECOLORLIBRARY_H

#include <QDialog>
#include "ui_EditTrueColorLibrary.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class EditTrueColorLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditTrueColorLibrary(LayersBase *base ,QWidget *parent);
	~EditTrueColorLibrary();

private:
	Ui::EditTrueColorLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//TrueColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	TrueColorBlockBase	*GetTrueColorBlockBase(void);
	void		ShowSubtractList(TrueColorBlockLibrary &data);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	ColorGenerator;
	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

private slots:
	void on_pushButtonGColor_clicked();
	void on_ButtonDelSubtractLib_3_clicked();
	void on_ButtonAddSubtractLib_3_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_pushButtonBColor_clicked();
	void on_pushButtonNColor_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();

	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITTRUECOLORLIBRARY_H
