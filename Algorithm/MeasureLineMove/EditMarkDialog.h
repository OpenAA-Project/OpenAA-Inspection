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

#ifndef EDITMARKDIALOG_H
#define EDITMARKDIALOG_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"

namespace Ui {
class EditMarkDialog;
}

class EditMarkDialog : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    int HistgramPage;
public:
    explicit EditMarkDialog(LayersBase *Base,QWidget *parent = 0);
    ~EditMarkDialog();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_pushButtonChangeLib_clicked();
    void on_pushButtonTest_clicked();
    void on_ButtonClose_clicked();

    void on_EditSearchDot_valueChanged(int arg1);

    void on_doubleSpinBoxSearchDot_valueChanged(double arg1);

    void on_doubleSpinBoxThresholdM_valueChanged(double arg1);

    void on_doubleSpinBoxThresholdM_2_valueChanged(double arg1);

    void on_doubleSpinBoxThresholdP_valueChanged(double arg1);

    void on_doubleSpinBoxThresholdP_2_valueChanged(double arg1);

    void on_pushButtonChangeItemID_clicked();

private:
    Ui::EditMarkDialog *ui;

	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	bool	OnChanging;

	HistgramTypeListInAlgoContainer	HContainer;
	void	ShowHistgramList(void);
	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
	void	ShowThreshold(void);
};

#endif // EDITMARKDIALOG_H