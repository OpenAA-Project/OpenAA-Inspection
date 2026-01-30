/*
 * Copyright (C) 2020
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

#ifndef SETTINGALIGNMENTPROJECTIONFORM_H
#define SETTINGALIGNMENTPROJECTIONFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentProjection.h"
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtTBarGraph.h"
#include "mtGraph.h"

namespace Ui {
class SettingAlignmentProjectionForm;
}

class	LayersBase;

class SettingAlignmentProjectionForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
public:
    explicit SettingAlignmentProjectionForm(LayersBase *Base,QWidget *parent = 0);
    ~SettingAlignmentProjectionForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SettingAlignmentProjectionForm *ui;

	bool	OnChanging;

	double			YMax;
	mtLineGraph		LGraph;
	mtGStick		GraphMapTarget;
	mtGStick		GraphMapMaster;
	mtGStick		GraphPeakMaster;
	mtGStick		GraphPeakTarget;

	void	ShowGraph(void);
};

#endif // SETTINGALIGNMENTPROJECTIONFORM_H