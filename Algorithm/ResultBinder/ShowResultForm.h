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

#ifndef SHOWRESULTFORM_H
#define SHOWRESULTFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowResultForm;
}

class ShowResultForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ShowResultForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowResultForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	AlgorithmItemIndependentPack	*IData;
	int		ItemID;
	QString	ItemName;

	QString	RuleName;
	QString	RuleRemark;

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ShowResultForm *ui;
};

#endif // SHOWRESULTFORM_H