/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\PieceArchitect\SelectExpandableAlgorithmForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
