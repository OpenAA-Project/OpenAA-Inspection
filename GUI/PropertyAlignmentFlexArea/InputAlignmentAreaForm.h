/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentAreaForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTALIGNMENTAREAFORM_H
#define INPUTALIGNMENTAREAFORM_H

#include <QDialog>
#include "ui_InputAlignmentAreaForm.h"
#include "XAlgorithmLibrary.h"
#include "SelectLibrariesForAnyType.h"
#include "XServiceForLayers.h"
#include "XAlignmentFlexArea.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include <QModelIndex>

class	GeneralLibFolderForm;

class InputAlignmentAreaForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent);
	~InputAlignmentAreaForm();

	QString	AreaName;
	SelectLibrariesForAnyType		Libs;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	bool	DeleteMode;
	void	Reflect(AlignmentFlexAreaAreaList *a);
	void	Reflect(void);

	AlgorithmLibraryListContainer	LibToCreateItems;

private:
	Ui::InputAlignmentAreaFormClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	AlignmentFlexAreaLibrary	*TempLib;
	int		LibType;
	void	ShowLibrary(AlignmentFlexAreaLibrary &data);
	void	GetLibraryFromWindow(AlignmentFlexAreaLibrary &data);

	AlgorithmLibraryListContainer	LibList;
	AlignmentFlexAreaBase	*GetAlignmentFlexAreaBase(void);
	void	ShowGenList(void);

private slots:
	void on_ButtonDelete_clicked();
	void on_ButtonOK_clicked();
	void on_ButtonCancel_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetLibListGen_doubleClicked(const QModelIndex &index);
    void on_pushButtonToGenList_clicked();
    void on_pushButtonFromGenList_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_radioButtonPriorityLGlobal_clicked();
    void on_radioButtonPriorityHigh_clicked();
    void on_radioButtonPriorityMiddle_clicked();
    void on_radioButtonPriorityLow_clicked();
};

#endif // INPUTALIGNMENTAREAFORM_H
