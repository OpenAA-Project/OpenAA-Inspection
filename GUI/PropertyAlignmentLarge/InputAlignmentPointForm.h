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
#include "XAlignmentLarge.h"

class	LayersBase;

class InputAlignmentPointForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	XAlignmentLargeArea::_EnumPriority AreaPriority;
public:
	InputAlignmentPointForm(bool EditMode ,XAlignmentLargeArea::_EnumPriority _AreaPriority ,LayersBase *,QWidget *parent);
	~InputAlignmentPointForm();

	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		SearchAround;
	WORD		GroupNumber;	
	bool		UsageGlobal;
    WORD		Threshold;
	bool		AlignmentOnOutline;	
	bool		DeleteMode;
	bool		JudgeWithBrDif;
	bool		CharacterMode;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness

	void		UpdateData(void);
private:
	Ui::InputAlignmentPointFormClass ui;

private slots:
	void on_ButtonDefault_clicked();
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
    void on_pushButtonDelete_clicked();
};

#endif // INPUTALIGNMENTPOINTFORM_H	
