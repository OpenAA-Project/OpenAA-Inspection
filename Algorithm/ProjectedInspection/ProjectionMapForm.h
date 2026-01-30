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

#ifndef PROJECTIONMAPFORM_H
#define PROJECTIONMAPFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtTBarGraph.h"
#include "mtGraph.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"

namespace Ui {
class ProjectionMapForm;
}

class ProjectionMapForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ProjectionMapForm(LayersBase *Base,QWidget *parent = 0);
    ~ProjectionMapForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private slots:
    void on_pushButtonChangeLib_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_EditOKWidthDifferece_valueChanged(int arg1);
    void on_EditTransitWidth_valueChanged(int arg1);

private:
    Ui::ProjectionMapForm *ui;

	AlgorithmLibraryListContainer	LibIDList;
	HistgramTypeListInAlgoContainer	HContainer;

	mtLineGraph						LGraph;
	mtGStick						GraphColTarget;
	mtGLine							GraphNG;
	AlgorithmItemIndependentPack	*IData;
	double							YMax;

	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;
	int32	OKWidthDiffereceL;
	int32	OKWidthDiffereceH;
	bool	UseAbsolute;		//�P�x�l�����Βl���g�����H
	int32	EvenLength;			//���ϒl�Z�o�̃o���h����
	double	PartialSwingAngle;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	ShowHistgramList(void);
	bool	OnChanging;
signals:
	void	SignalStartCalc();
private slots:
	void	SlotStartCalc();
    void on_ButtonCalc_clicked();
};

#endif // PROJECTIONMAPFORM_H