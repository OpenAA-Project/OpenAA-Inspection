/*
 * Copyright (C) 2012
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

#pragma once

#include "ui_ReviewSettingFormBase.h"

//#include "XGUIFormBase.h"

class LayersBase;
class GUIFormBase;
class AlgorithmBase;

class ReviewSettingFormBase : public QDialog
{
	Q_OBJECT

public:
	ReviewSettingFormBase(LayersBase *layer, QWidget *parent=NULL);

private slots:
	void on_pbReviewStructure_clicked();
	void on_pbButtonToShowTotalNGMap_clicked();
	void on_pbListMasterDataAndLoad_clicked();
	void on_pbLiveCameraAlgoNTSC_clicked();
	void on_pbNGImageForReview_clicked();
	void on_pbNGImageListForReview_clicked();
	void on_pbSelectLotForReview_clicked();
	void on_pbShowHistoryListForReview_clicked();
	void on_pbShowThumbnail_clicked();
	void on_pbShowVRSOperation_clicked();
	void on_pbWholeImageForReview_clicked();

private:
	void execPropertyDialog(AlgorithmBase *ABase);
	void execPropertyDialog(GUIFormBase *GBase);
	bool checkPropertyEnable(GUIFormBase *gui);
	bool checkPropertyEnable(AlgorithmBase *algorithm);

private:
	void setButtonState(QAbstractButton *button, GUIFormBase *Base, const QString &text);

public:
	inline const LayersBase *GetLayersBase() const { return m_layer; };
	inline LayersBase *GetLayersBase(){ return m_layer; };

private:
	Ui::ReviewSettingClass ui;
	LayersBase *m_layer;
};