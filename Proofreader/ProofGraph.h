/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Proofreader\ProofGraph.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef PROOFGRAPH_H
#define PROOFGRAPH_H

#include <QDialog>
#include "ui_ProofGraph.h"

class mtLineGraph;

class ProofGraph : public QDialog
{
	Q_OBJECT

public:
//	ProofGraph(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	ProofGraph(QList<double> XYDataList,int Line);
	~ProofGraph();

private slots:
	void pbSave_clicked();
	void pbClose_clicked();

private:
	Ui::ProofGraphClass ui;
	QString			OutputString(double output);
	mtLineGraph		*LineGraph;
	QList<double>	wXYDataList;
	int				DotPerLine;
};

#endif // PROOFGRAPH_H
