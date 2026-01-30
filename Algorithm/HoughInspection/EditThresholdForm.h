/*
 * Copyright (C) 2024
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

#ifndef EDITTHRESHOLDFORM_H
#define EDITTHRESHOLDFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class EditThresholdForm;
}

class EditThresholdForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    int		HistgramPage;
public:
    explicit EditThresholdForm(LayersBase *Base,QWidget *parent = 0);
    ~EditThresholdForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_toolButtonSimShowBright_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditZoneWidth_valueChanged(int arg1);
    void on_EditMaxIsolation_valueChanged(int arg1);
    void on_EditNGLength_valueChanged(int arg1);
    void on_EditMinPixels_valueChanged(int arg1);
    void on_EditMinNGWidth_valueChanged(double arg1);
    void on_EditMaxNGWidth_valueChanged(double arg1);

    void on_EditMinAverageContinuous_valueChanged(int arg1);

private:
    Ui::EditThresholdForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;
	DisplaySimPanel		SimPanel;

	void	ShowThreshold(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	CreateThreshld(void);

	void	SetMMFromPixel(void);
};

#endif // EDITTHRESHOLDFORM_H