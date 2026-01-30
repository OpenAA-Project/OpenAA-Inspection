/*
 * Copyright (C) 2014
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

#ifndef THRESHOLDSETTINGFORM_H
#define THRESHOLDSETTINGFORM_H

#include <QDialog>
#include "ui_ThresholdSettingForm.h"
#include "mtImageToolButton.h"
#include "mtImageSlider.h"
#include "XPixelInspection.h"
#include "ChoicePhaseDialog.h"

class ThresholdSettingForm : public QDialog
{
	Q_OBJECT

	mtImageToolButton	*BtnDecision;
	mtImageToolButton	*BtnDetailSetting;
	mtImageToolButton	*BtnCancel;

	mtImageSlider		*ImageSlider;

	ChosenPhase *chosenPhase;

public:
	//ThresholdSettingForm(QWidget *parent=0,GUIFormBase *Base=0,PixelInspectionBase *PBase=0);
	ThresholdSettingForm(QWidget *parent=0,GUIFormBase *Base=0,PixelInspectionBase *PBase=0,ChosenPhase *chosenPhase=0);
	~ThresholdSettingForm();

	void	SetImageSlider			 (int Value)	{	ImageSlider->setValue(Value);	InspectionLevel=Value;	}
	void	SetInspectionLevel		 (int Value);
	int		GetInspectionLevel		 ()				{	return InspectionLevel;			}
	//void	SetNGThresholdP			 (double Value)	{	NGThresholdP			=Value;	}
	//void	SetNGThresholdR			 (double Value)	{	NGThresholdR			=Value;	}
	void	SetMinimumNGSizeP		 (int Value)	{	MinimumNGSizeP			=Value;	}
	void	SetDoneResistIns		 (bool Check)	{	DoneResistIns			=Check;	}
	//void	SetNGThresholdForResist	 (int Value)	{	NGThresholdForResist	=Value;	}
	void	SetMinimumNGSizeForResist(int Value)	{	MinimumNGSizeForResist	=Value;	}
	void	SetDonePadIns			 (bool Check)	{	DonePadIns				=Check;	}
	//void	SetNGThresholdForPad	 (int Value)	{	NGThresholdForPad		=Value;	}
	void	SetMinimumNGSizeForPad	 (int Value)	{	MinimumNGSizeForPad		=Value;	}

	GUIFormBase			*GUIBase;
	QString DecisionImageBmpFile[5];
	QString CancelImageBmpFile[5];

	ChosenPhase *getChosenPhase(void){ return chosenPhase;}
	//int getChosenPhaseNumber(){return chosenPhase->getPhaseNumber();}

private slots:
	void	SlotBtnDecisionClicked		();
	void	SlotBtnDetailSettingClicked	();
	void	SlotBtnCancelClicked		();

private:
	Ui::ThresholdSettingFormClass ui;

	PixelInspectionBase	*PixelBase;

	

	int		InspectionLevel;
	double	NGThresholdP_B,NGThresholdP_D;
	double	NGThresholdR_B,NGThresholdR_D;
	int		MinimumNGSizeP;
	bool	DoneResistIns;
	int		NGThresholdForResist;
	int		MinimumNGSizeForResist;
	bool	DonePadIns;
	int		NGThresholdForPad;
	int		MinimumNGSizeForPad;
};

#endif // THRESHOLDSETTINGFORM_H