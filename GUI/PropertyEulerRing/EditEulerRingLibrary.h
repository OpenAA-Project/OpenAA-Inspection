/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\EditEulerRingLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef EDITEULERRINGLIBRARY_H
#define EDITEULERRINGLIBRARY_H

#include <QDialog>
#include "ui_EditEulerRingLibrary.h"
#include "XEulerRing.h"
#include "XEulerRingLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class EditEulerRingLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditEulerRingLibrary(LayersBase *base ,QWidget *parent);
	~EditEulerRingLibrary();

private:
	Ui::EditEulerRingLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//EulerRingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	EulerRingBase	*GetEulerRingBase(void);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	ColorGeneratorH;
	ShowRGBSpace	ColorGeneratorC;
	ShowRGBSpace	ColorInspection;

private slots:
	void on_pushButtonCColor_clicked();
	void on_pushButtonNColor_clicked();
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_pushButtonGColor_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITEULERRINGLIBRARY_H
