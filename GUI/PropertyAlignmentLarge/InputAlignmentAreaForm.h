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
#include "XAlignmentLarge.h"
#include "PropertyAlignmentLargePacket.h"

class AlignmentLargeAreaList;

class InputAlignmentAreaForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent);
	~InputAlignmentAreaForm();

	QString	AreaName;
	int		MasterNo;
	SelectLibrariesForAnyType		Libs;
	XAlignmentLargeArea::_EnumPriority	Priority;
	bool	DeleteMode;
	void	Reflect(AlignmentLargeAreaList *a);
	void	Reflect(void);
private:
	Ui::InputAlignmentAreaFormClass ui;

private slots:
	void on_ButtonDelete_clicked();
	void on_ButtonOK_clicked();
	void on_ButtonCancel_clicked();
};

#endif // INPUTALIGNMENTAREAFORM_H
