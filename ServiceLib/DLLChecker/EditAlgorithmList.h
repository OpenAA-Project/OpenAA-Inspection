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

#ifndef EDITALGORITHMLIST_H
#define EDITALGORITHMLIST_H

#include <QWidget>
#include "ui_EditAlgorithmList.h"
#include "XServiceForLayers.h"
#include "WMultiGrid.h"
#include "XBoolList.h"

class	EditAlgorithmList;
class	AlgoGrid : public WMultiGrid,public ServiceForLayers
{
	EditAlgorithmList	*MParent;
public:
	AlgoGrid(LayersBase *Base,EditAlgorithmList *mParent,QWidget * parent=0)
		:WMultiGrid(parent),ServiceForLayers(Base),MParent(mParent){}

	virtual	void	ChangeValue(int row ,int col,const QVariant &value);
	virtual	void	GetValue(int row ,int col,QVariant &value);
};


class EditAlgorithmList : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	EditAlgorithmList(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditAlgorithmList();

	BoolList	EffectiveList;

private:
	Ui::EditAlgorithmListClass ui;

	AlgoGrid	WTable;

signals:
	void	SignalClose();

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonSave_clicked();

};

#endif // EDITALGORITHMLIST_H