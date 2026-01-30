/*
 * Copyright (C) 2021
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

#include "EditExecuteVisualizer.h"
#include "XDataInLayer.h"
#include "EVDLLListForm.h"
#include "XExecuteVisualizerInterface.h"

EditExecuteVisualizer::EditExecuteVisualizer(LayersBase *base, QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),RMap(base,true,NULL)
{
	ui.setupUi(this);

	RMap.LoadDLL(/**/"ExecuteVisualizer");
	DLLListForm=new EVDLLListForm(RMap,NULL);
	DLLListForm->show();
	RMap.show();

	connect(&RMap,SIGNAL(SignalLDoubleClick(int ,int)),this,SLOT(SlotLDoubleClick(int,int)));
}

EditExecuteVisualizer::~EditExecuteVisualizer()
{

}

void EditExecuteVisualizer::closeEvent ( QCloseEvent * event )
{
	RMap.close();

	DLLListForm->close();
	DLLListForm->deleteLater();
	DLLListForm=NULL;
}

void EditExecuteVisualizer::on_actionLoad_EV_File_triggered()
{
	QString FileName=QFileDialog::getOpenFileName ( 0,QString("Load EV file"), QString()
													,tr(/**/"Execute Visualizer file(*.evf)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(RMap.Load(&File)==true){
				RMap.show();
			}
		}
	}
}

void EditExecuteVisualizer::on_actionSave_EV_File_triggered()
{
	QString FileName=QFileDialog::getSaveFileName ( 0,QString("Save EV file"), QString()
													,tr(/**/"Execute Visualizer file(*.evf)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			RMap.Save(&File);
		}
	}
}

void EditExecuteVisualizer::on_actionExfit_triggered()
{
	close();
}

void	EditExecuteVisualizer::SlotLDoubleClick(int x ,int y)
{
	RunnerObjDLL	*DLL=DLLListForm->GetCurrentDLL();
	if(DLL!=NULL){
		RunnerObject	*Obj=DLL->CreateInstance(&RMap);
		Obj->move(x,y);
		RMap.AppendRunnerObject(Obj,DLL);
		Obj->show();
	}
}