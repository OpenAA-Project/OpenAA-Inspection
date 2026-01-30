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

#ifndef ADJUSTALIGNMENTBLOCKFORM_H
#define ADJUSTALIGNMENTBLOCKFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentBlock.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class AdjustAlignmentBlockForm;
}

class AdjustAlignmentBlockForm;

class	DisplaySimPanelAlignmentBlock	: public DisplaySimPanel
{
	AdjustAlignmentBlockForm	*ParentWidget;

public:
	DisplaySimPanelAlignmentBlock(LayersBase *base ,AdjustAlignmentBlockForm *parentw ,QWidget *parent = 0);
};

class AdjustAlignmentBlockForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit AdjustAlignmentBlockForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustAlignmentBlockForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);
    void	ShowDataToWindow(void);

	AlgorithmItemIndependentPack	*IData;
    int                             GlobalPage;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxMaxDegree_valueChanged(double arg1);
    void on_spinBoxLineLength_valueChanged(int arg1);
    void on_doubleSpinBoxMinVar_valueChanged(double arg1);

    void on_pushButtonCalc_clicked();

private:
    Ui::AdjustAlignmentBlockForm *ui;

    bool	OnChanging;
    bool    Preparing;
	DisplaySimPanelAlignmentBlock		SimPanel;
    bool	ModeShowItem;

    virtual	void	showEvent (QShowEvent * event)	override;
    void ShowCalc(void);
};

#endif // ADJUSTALIGNMENTBLOCKFORM_H