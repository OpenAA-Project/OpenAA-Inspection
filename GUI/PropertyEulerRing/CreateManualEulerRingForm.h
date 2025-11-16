/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\CreateManualEulerRingForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef CREATEMANUALEULERRINGFORM_H
#define CREATEMANUALEULERRINGFORM_H

#include <QDialog>
#include "ui_CreateManualEulerRingForm.h"
#include "XEulerRing.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class CreateManualEulerRingForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	CreateManualEulerRingForm(LayersBase *Base,QWidget *parent);
	~CreateManualEulerRingForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	EulerRingItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualEulerRingFormClass ui;
	//EulerRingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int						BlockLibID;

	ShowRGBSpace	ColorInspection;

	void	GetDataFromWindow(EulerRingItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALEULERRINGFORM_H
