#include "ChronologicalGraphForm.h"
#include "ui_ChronologicalGraphForm.h"
#include "NGCountForm.h"

ChronologicalGraphForm::ChronologicalGraphForm(NGCountForm *p,QWidget *parent) :
    QWidget(parent)
	,Parent(p)
    ,ui(new Ui::ChronologicalGraphForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	GraphWidget.setParent(ui->frame);
	GraphWidget.SetScaleTypeY(mtLineGraph::mtConstant);

	GraphData.SetLineColor(Qt::green);
	GraphData.SetLineWidth(1);
	GraphData.SetOffsetX(0);

	GraphMain	.SetLineColor(Qt::red);
	GraphMain	.SetLineWidth(1);
	GraphMain	.SetOffsetX(0);

	GraphWidget.AddGraph(&GraphData);
	GraphWidget.AddGraph(&GraphMain);

	Dim=NULL;
	SetGraph();
}

ChronologicalGraphForm::~ChronologicalGraphForm()
{
    delete ui;
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
}
void	ChronologicalGraphForm::resizeEvent(QResizeEvent *event)
{
	ui->frame->resize(width(),height()-ui->frame->geometry().top());
	GraphWidget.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	GraphWidget.repaint();
}

void	ChronologicalGraphForm::SetGraph(void)
{
	GraphData.DeleteXY();
	GraphMain.DeleteXY();

	if(ui->comboBoxTimeSpan->currentIndex()==0){
		XDateTime	OldestTime;
		XDateTime	LatestTime;
		for(NGResultList *a=Parent->ResultList.GetFirst();a!=NULL;a=a->GetNext()){
			if(OldestTime.IsAvailable()){
				if(OldestTime>a->InspectionTime){
					OldestTime=a->InspectionTime;
				}
			}
			else{
				OldestTime=a->InspectionTime;
			}
			if(LatestTime.IsAvailable()){
				if(LatestTime<a->InspectionTime){
					LatestTime=a->InspectionTime;
				}
			}
			else{
				LatestTime=a->InspectionTime;
			}
		}
		int64	DifTime=OldestTime.secsTo(LatestTime);
		DimCount=DifTime/3600+2;
		if(Dim!=NULL){
			delete	[]Dim;
		}
		Dim=new int[DimCount];
		memset(Dim,0,sizeof(int)*DimCount);
		for(NGResultList *a=Parent->ResultList.GetFirst();a!=NULL;a=a->GetNext()){
			DifTime=OldestTime.secsTo(a->InspectionTime);
			int	HourPoint=DifTime/3600;
			Dim[HourPoint]++;
		}
		for(int i=0;i<DimCount;i++){
			GraphData.AddXY(i,Dim[i]);
		}
	}
	else
	if(ui->comboBoxTimeSpan->currentIndex()==1){
	}
	else
	if(ui->comboBoxTimeSpan->currentIndex()==2){
	}
	GraphWidget.repaint();
}
