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



#ifndef SELECTEXPANDABLEALGORITHMFORM_H
#define SELECTEXPANDABLEALGORITHMFORM_H

#include <QDialog>
#include "ui_SelectExpandableAlgorithmForm.h"
#include "XServiceForLayers.h"
#include "XPieceArrange.h"
#include "WMultiGrid.h"

class	ReflectionAttrPack;

class	SelectExpandableAlgorithmGrid : public WMultiGrid ,public ServiceForLayers
{
    Q_OBJECT
public:
	SelectExpandableAlgorithmGrid(LayersBase *Base,QWidget *parent = 0);
	virtual	void	ChangeValue(int row ,int col,const QVariant &value);
	virtual	void	GetValue(int row ,int col,QVariant &value);

	void	ShowGrid(void);
};

class SelectExpandableAlgorithmForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	SelectExpandableAlgorithmGrid	Grid;
public:
	SelectExpandableAlgorithmForm(ReflectionAttrPack *data,LayersBase *base ,QWidget *parent = 0);
	~SelectExpandableAlgorithmForm();

	ReflectionAttrPack	ReflectionAttrData;
private:
	Ui::SelectExpandableAlgorithmFormClass ui;

private slots:
	void on_pushButtonOK_clicked();
};

#endif // SELECTEXPANDABLEALGORITHMFORM_H