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

#ifndef SHOWMARKFORM_H
#define SHOWMARKFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XSwitchPhase.h"

namespace Ui {
class ShowMarkForm;
}

class ShowMarkForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ShowMarkForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowMarkForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_tableWidgetPhaseList_clicked(const QModelIndex &index);
    void on_ButtonReflectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonClose_clicked();

private:
    Ui::ShowMarkForm *ui;

	bool	OnChanging;
};

#endif // SHOWMARKFORM_H