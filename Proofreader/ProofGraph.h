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