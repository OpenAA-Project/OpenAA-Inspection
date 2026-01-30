/*
 * Copyright (C) 2016
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

#ifndef THRESHOLDSTEPLINEENHANCERLFORM_H
#define THRESHOLDSTEPLINEENHANCERLFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class ThresholdStepLineEnhancerLForm;
}

class ThresholdStepLineEnhancerLForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ThresholdStepLineEnhancerLForm(QWidget *parent = 0);
    ~ThresholdStepLineEnhancerLForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_pushButtonChangeLib_clicked();
    void on_ButtonReflectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_ButtonReflectSaveParts_clicked();

private:
    Ui::ThresholdStepLineEnhancerLForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

	double	EmphasizeRate;
	int32	MaxLineWidth;
	int		StepDot;
	int32	SelfSearch;
	int		StartAngle;
	int		EndAngle;
	bool	ExcludeDynamicMask;

	void	CreateThreshld(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
};

#endif // THRESHOLDSTEPLINEENHANCERLFORM_H