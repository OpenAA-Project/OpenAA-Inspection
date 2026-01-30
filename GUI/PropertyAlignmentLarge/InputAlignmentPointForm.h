/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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