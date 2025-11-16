/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\CreateManualMeasureHoleForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef CREATEMANUALMEASUREHOLEFORM_H
#define CREATEMANUALMEASUREHOLEFORM_H

#include <QDialog>
#include "ui_CreateManualMeasureHoleForm.h"
#include "XMeasureHole.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDLLOnly.h"
#include "SelectColorSample.h"

class	GeneralLibFolderForm;

class CreateManualMeasureHoleForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	CreateManualMeasureHoleForm(LayersBase *Base, QWidget *parent);
	~CreateManualMeasureHoleForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	MeasureHoleItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualMeasureHoleFormClass ui;

	//MeasureHoleLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					LibID;

	ShowRGBSpace		ColorGenerator;
	SelectColorSample	ColorSamples;

	void	GetDataFromWindow(MeasureHoleItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALMEASUREHOLEFORM_H
