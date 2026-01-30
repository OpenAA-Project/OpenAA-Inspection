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

#ifndef EDITEXECUTEVISUALIZER_H
#define EDITEXECUTEVISUALIZER_H

#include <QMainWindow>
#include "ui_EditExecuteVisualizer.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"

class	EVDLLListForm;

class EditExecuteVisualizer : public QMainWindow
{
	Q_OBJECT

	RunnerMap	RMap;
	EVDLLListForm	*DLLListForm;

public:
	EditExecuteVisualizer(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditExecuteVisualizer();

private:
	
	virtual void closeEvent ( QCloseEvent * event )	override;


private slots:
        void on_actionLoad_EV_File_triggered();
        void on_actionSave_EV_File_triggered();
        void on_actionExfit_triggered();

	void	SlotLDoubleClick(int x ,int y);

private:
	Ui::EditExecuteVisualizerClass ui;
};

#endif // EDITEXECUTEVISUALIZER_H