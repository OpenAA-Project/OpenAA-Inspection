/*
 * Copyright (C) 2021
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

#ifndef OUTLINEHISTGRAM_H
#define OUTLINEHISTGRAM_H

#include <QWidget>
#include <QStackedWidget>
#include "ui_OutlineHistgram.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "ShowRGBSamples.h"
#include "XOutlineInspect.h"
#include "XPasswordQWidget.h"

class	OutlineBase;

class OutlineHistgram : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
	Q_OBJECT

public:
	OutlineHistgram(LayersBase *Base,QWidget *parent = 0);
	~OutlineHistgram();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::OutlineHistgramClass ui;

	AlgorithmItemIndependentPack	*IData;
	ShowRGBSpace		ColorThre;
	SelectColorSample	ColorSamples;
	ShowRGBSamples		RGBPanel;
	QColor PickupColor;
	mtColorFrame	PickupColorFrame;

	ShowRGBSpace	ColorInside;
	ShowRGBSpace	TrColorInside;
	ShowRGBSpace	ColorOutside;
	ShowRGBSpace	TrColorOutside;

	ShowRGBSpace	ColorBInside;
	ShowRGBSpace	TrColorBInside;
	ShowRGBSpace	ColorBOutside;
	ShowRGBSpace	TrColorBOutside;

	OutlineBase	*GetOutlineBase(void);
	AlgorithmLibraryListContainer	LibIDList;
	OutlineThreshold	TmpThreshold;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);


private slots:
	void on_pushButtonInsideColor_clicked();
	void on_radioButtonOutsideBTrans_toggled(bool);
	void on_radioButtonOutsideBStable_toggled(bool);
	void on_radioButtonInsideBTrans_toggled(bool);
	void on_radioButtonInsideBStable_toggled(bool);
	void on_radioButtonOutsideTrans_toggled(bool);
	void on_radioButtonOutsideStable_toggled(bool);
	void on_radioButtonInsideTrans_toggled(bool);
	void on_radioButtonInsideStable_toggled(bool);
	void on_pushButtonClose_clicked();
	void on_ButtonRelrectSaveParts_clicked();
	void on_pushButtonEliminateColorAreaOutside_clicked();
	void on_pushButtonAddColorAreaOutside_clicked();
	void on_pushButtonEliminateColorAreaInside_clicked();
	void on_pushButtonAddColorAreaInside_clicked();
	void on_pushButtonSubPickupColorOutside_clicked();
	void on_pushButtonSubPickupColorInside_clicked();
	void on_pushButtonAddPickupColorOutside_clicked();
	void on_pushButtonAddPickupColorInside_clicked();
	void on_pushButtonEliminateColorOutside_clicked();
	void on_pushButtonAddColorOutside_clicked();
	void on_pushButtonEliminateColorInside_clicked();
	void on_pushButtonAddColorInside_clicked();
	void on_ButtonCalc_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_ButtonRefrectOnlyBlock_clicked();
	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);
};

#endif // OUTLINEHISTGRAM_H