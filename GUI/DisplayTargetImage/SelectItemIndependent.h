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


#ifndef SELECTITEMINDEPENDENT_H
#define SELECTITEMINDEPENDENT_H

#include <QDialog>
#include "ui_SelectItemIndependent.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"

class	SelectItemIndependent;
class	ResultAnalizerItemBase;

class	ItemIndependentList : public NPList<ItemIndependentList>
{
public:
	int							Page;
	int							Layer;
	int							ID;
	int							LibID;
	QString						TypeInNoLib;
	int							ItemClassType;
	AlgorithmItemIndependent	*Point;
	bool						Selected;
	QString						LibName;
	int32						Error;

	ItemIndependentList(void){	Selected=false;	}
};

class	AlgorithmIndependentList : public NPList<AlgorithmIndependentList>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	NPListPack<ItemIndependentList>	ItemList;
};

class	ResultAnalizerButton : public QPushButton
{
	Q_OBJECT

	int						Row;
public:
	ResultAnalizerButton (int row, SelectItemIndependent *Parent,QWidget * parent = 0 );

signals:
	void	SignalClicked(int d);
	
private slots:
	void	SlotClicked();
};

class SelectItemIndependent : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectItemIndependent(LayersBase *Base,QWidget *parent);
	~SelectItemIndependent();

	NPListPack<AlgorithmIndependentList>	List;
	AlgorithmIndependentList	*SelectedList;

	void	AddItem(AlgorithmItemIndependent *p);
	void	Show(void);

private:
	Ui::SelectItemIndependentClass ui;
	void	ShowResultAnalizer(AlgorithmIndependentList *a,ItemIndependentList *c
												,ResultAnalizerItemBase *R);
public slots:
	void	SlotResultAnalizerClicked(int row);

private slots:
	void	on_tableWidgetAlgorithm_clicked(const QModelIndex &);
	void	OKButtonClicked();
	void	CancelButtonClicked();
    void on_tableWidgetItems_doubleClicked(const QModelIndex &index);
};

#endif // SELECTITEMINDEPENDENT_H