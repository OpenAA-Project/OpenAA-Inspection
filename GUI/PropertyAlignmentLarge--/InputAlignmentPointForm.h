/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\InputAlignmentPointForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTALIGNMENTPOINTFORM_H
#define INPUTALIGNMENTPOINTFORM_H

#include <QDialog>
#include "ui_InputAlignmentPointForm.h"
#include "XTypeDef.h"
#include "XServiceForLayers.h"

class	LayersBase;

class InputAlignmentPointForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	InputAlignmentPointForm(LayersBase *,QWidget *parent);
	~InputAlignmentPointForm();

	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		GroupID;	
	bool		UsageGlobal;
    WORD		Threshold;
	bool		AlignmentOnOutline;	//ó÷äsÇ≈à íuçáÇÌÇπÇ∑ÇÈÇ∆Ç´true

	void		UpdateData(void);
private:
	Ui::InputAlignmentPointFormClass ui;

private slots:
	void on_ButtonDefault_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // INPUTALIGNMENTPOINTFORM_H	