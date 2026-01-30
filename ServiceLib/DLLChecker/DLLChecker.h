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

#ifndef DLLCHECKER_H
#define DLLCHECKER_H

#include <QMainWindow>
#include "ui_DLLChecker.h"
#include "XServiceForLayers.h"
#include "XGUI.h"

class DLLChecker : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	GUIInstancePack	GUIPack;
public:
	DLLChecker(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DLLChecker();

private:
	Ui::DLLCheckerClass ui;

private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonCheckDLL_clicked();
	void on_pushButtonEditAlgorithm_clicked();
        void on_pushButtonDLLVersionList_clicked();
};

#endif // DLLCHECKER_H