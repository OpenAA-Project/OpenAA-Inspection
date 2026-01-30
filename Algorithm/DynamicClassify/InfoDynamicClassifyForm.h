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

#ifndef INFODYNAMICCLASSIFYFORM_H
#define INFODYNAMICCLASSIFYFORM_H

#include <QWidget>
#include "ui_InfoDynamicClassifyForm.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "mtColorFrame.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "ShowRGBSamples.h"
#include "XDynamicClassify.h"


class	DisplayImage;

class InfoDynamicClassifyForm : public QWidget,public ServiceForLayers
{
	Q_OBJECT

	DisplayImage	*Display;
public:
	InfoDynamicClassifyForm(ShowAndSetItemsBaseClass *Something ,LayersBase *Base,QWidget *parent = 0);
	~InfoDynamicClassifyForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private:
	Ui::InfoDynamicClassifyFormClass ui;
	AlgorithmLibraryListContainer	LibIDList;

	AlgorithmItemIndependentPack	*IData;

	ShowRGBSpace		ColorThre;
	SelectColorSample	ColorSamples;
	ShowRGBSamples		RGBPanel;
	QColor PickupColor;
	mtColorFrame	PickupColorFrame;

	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	ShowColorMap(void);

private slots:
	void on_toolButtonInside_clicked();
	void on_toolButtonBareArea_clicked();
	void on_pushButtonReCalc_clicked();
	void on_toolButtonOutlineOArea_clicked();
	void on_toolButtonOutlineTArea_clicked();
	void on_toolButtonOutlineIArea_clicked();
	void on_toolButtonMaxZone_clicked();
	void on_toolButtonMinZone_clicked();
	void on_toolButtonCoreArea_clicked();
	void on_pushButtonEliminateColorArea_clicked();
	void on_pushButtonAddColorArea_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_pushButtonSubPickupColor_clicked();
	void on_pushButtonAddPickupColor_clicked();
	void on_ButtonRelrectSaveParts_clicked();
	void on_ButtonClose_clicked();
	void on_ButtonLoadFromLibrary_clicked();
	void on_ButtonSaveToLibrary_clicked();
	void on_ButtonReflectAllBlocks_clicked();
	void on_ButtonRelrectOnlyBlock_clicked();
	void on_listWidgetEliminatedColor_doubleClicked(QModelIndex);
	void on_listWidgetBaseColor_doubleClicked(QModelIndex);
	void on_pushButtonChangeLib_clicked();

	void	SlotColorSampleBeforeSave();
	void	SlotColorSampleSelectOne();
	void	SlotAddEliminated(void);
	void	SlotDelEliminated(void);
};

#endif // INFODYNAMICCLASSIFYFORM_H