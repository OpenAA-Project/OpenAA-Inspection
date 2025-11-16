#include "DisplayPointingFormResource.h"
#include "DisplayPointingForm.h"
#include "XGeneralFunc.h"
#include "swap.h"

DisplayPointingForm::DisplayPointingForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

DisplayPointingForm::~DisplayPointingForm()
{

}


void	DisplayPointingForm::Prepare(void)
{
}
void	DisplayPointingForm::showEvent ( QShowEvent * event )
{
	GUIFormBase	*f=GetLayersBase()->FindByName(RelatedPanel);
	if(f!=NULL){
		connect(f,SIGNAL(SignalDrawMessage(const QStringList &,const QStringList &))	,this,SLOT(SlotDrawMessage(const QStringList &,const QStringList &)));
		connect(this,SIGNAL(SignalDrawFromOutside(QStringList &))	,f,SLOT(SlotDrawFromOutside(QStringList &)));
	}
}
void	DisplayPointingForm::ResizeAction()
{
	ui.tableWidget->resize(width(),height());
}

void	DisplayPointingForm::SlotDrawMessage(const QStringList &title ,const QStringList &msg)
{
	int	N=max(title.count(),msg.count());
	ui.tableWidget->setColumnCount(N);
	int	CellWidth=(width()-30)/N;
	for(int i=0;i<N;i++){
		ui.tableWidget->setColumnWidth(i,CellWidth);
	}
	ui.tableWidget->setHorizontalHeaderLabels (title);
	//for(int i=0;i<title.count();i++){
	//	ui.tableWidget->horizontalHeaderItem(i)->setText(title[i]);
	//}
	for(int i=0;i<msg.count();i++){
		SetDataToTable(ui.tableWidget,i,0,msg[i]);
	}
}
