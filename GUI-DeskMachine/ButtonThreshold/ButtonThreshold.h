/*
 * Copyright (C) 2022
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

#ifndef BUTTONTHRESHOLD_H
#define BUTTONTHRESHOLD_H

#include "buttonthreshold_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"
#include "XPixelInspection.h"
#include "ChoicePhaseDialog.h"

class	ButtonThreshold : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;

	bool	FlgLoadParamFilePath;
	QString LoadParamFilePath;
	void	Execute(PixelInspectionBase *PBase);
	void	Execute(PixelInspectionBase *PBase,ChosenPhase *chosenPhase);

public:
	ButtonThreshold(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

	int	LanguageCode;
	QString	Password;
	QString	DefaultDirectory;
	bool	AutoSelectFile;

	int		wInspectionLevel;
	double 	wNGThresholdP_B			,wNGThresholdS_B,wNGThresholdR_B,wNGThresholdH_B;
	double 	wNGThresholdP_D			,wNGThresholdS_D,wNGThresholdR_D,wNGThresholdH_D;
	int		wMinimumNGSizeP			,wMinimumNGSizeS,wMinimumNGSizeR,wMinimumNGSizeH;
	bool	wCheckPadIns			,wCheckSilkIns	,wCheckResistIns,wCheckHoleIns;
	bool	wDonePadIns				,wDoneSilkIns	,wDoneResistIns	,wDoneHoleIns;
	int		wNGThresholdForPad_B	,wNGThresholdForPad_D	,wMinimumNGSizeForPad;
	int		wNGThresholdForSilk_B	,wNGThresholdForSilk_D	,wMinimumNGSizeForSilk;
	int		wNGThresholdForResist_B	,wNGThresholdForResist_D,wMinimumNGSizeForResist;
	int		wNGThresholdForHole_B	,wNGThresholdForHole_D	,wMinimumNGSizeForHole;
	bool	wIsCalcPixelInterPoration;

	void	SetFlgLoadParamFilePath(bool Flg)	{	FlgLoadParamFilePath=Flg;		}
	bool	GetFlgLoadParamFilePath()			{	return FlgLoadParamFilePath;	}
	void	SetLoadParamFilePath(QString Path)	{	LoadParamFilePath	=Path;		}
	QString	GetLoadParamFilePath()				{	return LoadParamFilePath;		}

	bool	CheckInspectionLevel(int Level);
	void	ExecCmdShowThresholdFileName();

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

#endif // BUTTONTHRESHOLD_H