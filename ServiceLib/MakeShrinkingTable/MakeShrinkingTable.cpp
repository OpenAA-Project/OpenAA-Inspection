#include "MakeShrinkingTable.h"
#include <omp.h>

MakeShrinkingTable::MakeShrinkingTable(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ShrinkingPackContainerInstance.LoadDefault();
}

MakeShrinkingTable::~MakeShrinkingTable()
{

}

void MakeShrinkingTable::on_pushButtonStart_clicked()
{
	int	Numb=ui.spinBoxNumb->value();
	QString	FileName	=ui.lineEditFileName->text();
	ShrinkingPackContainerInstance.Clear();

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<Numb;i++){
			ShrinkingPackContainerInstance.GetPack(i);
		}
	}
	ShrinkingPackContainerInstance.SaveDefault(FileName);
}
