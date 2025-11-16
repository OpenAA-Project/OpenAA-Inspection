/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayTargetImage\SelectItemIndependent.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
