/*
 * Copyright (C) 2023
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

#ifndef ADJUSTITEMFORM_H
#define ADJUSTITEMFORM_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include <QSpinBox>
#include <QString>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketForDLL.h"
#include "XRasterInspection.h"

namespace Ui {
class AdjustItemForm;
}

class AdjustItemForm;

class	DisplayAdjustPanel : public DisplaySimPanel
{
	AdjustItemForm	*Parent;
public:
	DisplayAdjustPanel (LayersBase *base ,AdjustItemForm *p ,QWidget *parent = 0);

	virtual	void	GetDrawInformation(QByteArray &Something);
};

class AdjustItemForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    DisplayAdjustPanel  DPanel;
public:
    explicit AdjustItemForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustItemForm();

    void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
    int     GetItemID(void);
    void	GetDrawInformation(QByteArray &Something);
	void	ShowResult(double ResultMaxD ,double ResultWaveLen);

private slots:
    void on_pushButtonReferencePDF_clicked();
    void on_ButtonRelrectOnlyItem_clicked();
    void on_ButtonReflectAllItems_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_spinBoxSearchAreaDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchWaveDiv_valueChanged(double arg1);
    void on_doubleSpinBoxWaveDistance_valueChanged(double arg1);
    void on_spinBoxOKDot_valueChanged(int arg1);
    void on_toolButtonSimShowBlock_clicked();
    void on_toolButtonShowResult_clicked();
    void on_doubleSpinBoxGenColorDistance_valueChanged(double arg1);
    void	SlotStartCalc();

private:
    Ui::AdjustItemForm *ui;

	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	AlgorithmBase *InstBase;
	bool	OnChanging;
	int		OldLibID;
	int		NewLibID;

	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
};

#endif // ADJUSTITEMFORM_H