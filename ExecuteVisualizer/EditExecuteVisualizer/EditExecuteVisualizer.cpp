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