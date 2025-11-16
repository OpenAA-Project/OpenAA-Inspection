#include "RealtimeGraphMeasure1Resource.h"
#include "RealtimeGraphMeasure1Form.h"
#include "XExecuteInspectBase.h"
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XGeneralFunc.h"
#include "XRealtimeGraphThread.h"
#include "XPropertyRealtimeGraphCommon.h"
#include "XEntryPoint.h"

//---------------------------------------------------

RealtimeGraphMeasure1Form::RealtimeGraphMeasure1Form(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	Calclating	=false;
	for(int Row=0;Row<3;Row++){
		for(int Column=0;Column<3;Column++){
			ThreadDim[Row][Column]=NULL;
		}
	}
	connect(this,SIGNAL(SignalResize())			,this,SLOT(ResizeAction()));
}

RealtimeGraphMeasure1Form::~RealtimeGraphMeasure1Form()
{
	for(int Row=0;Row<3;Row++){
		for(int Column=0;Column<3;Column++){
			if(ThreadDim[Row][Column]!=NULL){
				delete	ThreadDim[Row][Column];
			}
		}
	}
}

void	RealtimeGraphMeasure1Form::AfterStartSequence(void)
{
	if(GetLayersBase()->IsLocalCamera()==true
	&& GetLayersBase()->GetEntryPoint()!=NULL){
		ExecuteInspectBase	*Ev=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(Ev!=NULL){
			Calclating	=false;
			for(int Row=0;Row<3;Row++){
				for(int Column=0;Column<3;Column++){
					ThreadDim[Row][Column]=new ThreadFocus(GetLayersBase(),this);
				}
			}
		}
	}
	PropertyRealtimeGraphPointer=GetLayersBase()->FindByName(/**/"RealtimeGraph",/**/"PropertyRealtimeGraph",/**/"");
}

void	RealtimeGraphMeasure1Form::ResizeAction()
{
	int	w=width()/2;
	ui.label				->resize(w-4,ui.label->height());
	ui.tableWidget			->resize(w-4,height()-ui.tableWidget->geometry().top());
	ui.tableWidget			->move(0,ui.tableWidget	->geometry().top());
	ui.label_2				->setGeometry(w+4,0,w-4,ui.label_2->height());
	ui.tableWidgetBrightness->resize(w-4,height()-ui.tableWidgetBrightness->geometry().top());
	ui.tableWidgetBrightness->move(w+4,ui.tableWidgetBrightness	->geometry().top());

	ui.tableWidget->setColumnWidth(0,(w-64)/3);
	ui.tableWidget->setColumnWidth(1,(w-64)/3);
	ui.tableWidget->setColumnWidth(2,(w-64)/3);

	ui.tableWidgetBrightness->setColumnWidth(0,(w-64)/3);
	ui.tableWidgetBrightness->setColumnWidth(1,(w-64)/3);
	ui.tableWidgetBrightness->setColumnWidth(2,(w-64)/3);
}

void	RealtimeGraphMeasure1Form::ShowInPlayer(int64 shownInspectionID)
{
	if(GetStackedViewPlayerCount()<2){
		CamNo=0;
		CmdReqRealtimeGraphCamera	RCmd(GetLayersBase());
		if(PropertyRealtimeGraphPointer!=NULL){
			PropertyRealtimeGraphPointer->TransmitDirectly(&RCmd);
			CamNo		=RCmd.CamNo;
			Calclating	=RCmd.Capturing;
		}
		if(CamNo<0)
			return;
		IntList	PageList;
		GetParamGlobal()->GetPageListFromCameraNo(CamNo,PageList);
		if(PageList.GetCount()!=0){
			int	Page=PageList.GetFirst()->GetValue();
			DataInPage	*Dp=GetLayersBase()->GetPageData(Page);
			int	DivX=Dp->GetDotPerLine()/3;
			int	DivY=Dp->GetMaxLines()/3;
			for(int Row=0;Row<3;Row++){
				for(int Column=0;Column<3;Column++){
					ThreadDim[Row][Column]->CalcDone=false;
					ThreadDim[Row][Column]->XPos=Column*DivX;
					ThreadDim[Row][Column]->YPos=Column*DivY;
					ThreadDim[Row][Column]->XLen=DivX;
					ThreadDim[Row][Column]->YLen=DivY;
				}
			}
			CalcFocus();

			ui.tableWidget->setUpdatesEnabled(false);
			ui.tableWidgetBrightness->setUpdatesEnabled(false);
			for(int Row=0;Row<3;Row++){
				for(int Column=0;Column<3;Column++){
					QString	Sf;
					QString	Bf;
					for(int layer=0;layer<GetLayerNumb(Page);layer++){
						double	d=ThreadDim[Row][Column]->FocusValue[layer];
						Sf+=QString::number(d,'f',1);
						if(layer<GetLayerNumb(Page)-1){
							Sf+="/";
						}
						double	b=ThreadDim[Row][Column]->Brightness[layer];
						Bf+=QString::number(b,'f',1);
						if(layer<GetLayerNumb(Page)-1){
							Bf+="/";
						}
					}
					::SetDataToTable(ui.tableWidget			 , Column, Row, Sf);
					::SetDataToTable(ui.tableWidgetBrightness, Column, Row, Bf);
				}
			}
			ui.tableWidget->setUpdatesEnabled(true);
			ui.tableWidgetBrightness->setUpdatesEnabled(true);
		}
	}
}
void	RealtimeGraphMeasure1Form::ShowInScanning(int64 shownInspectionID)
{
	ShowInPlayer(shownInspectionID);
}

void	RealtimeGraphMeasure1Form::CalcFocus(void)
{
	GetLayersBase()->LockRChangingDataStructure();
	for(int Row=0;Row<3;Row++){
		for(int Column=0;Column<3;Column++){
			ThreadDim[Row][Column]->CalcDone=false;
		}
	}
	
	#pragma omp parallel
	{
		#pragma omp for	
		for(int i=0;i<9;i++){
			int	Row=i/3;
			int	Column=i%3;
	//for(int Row=0;Row<3;Row++){
	//	for(int Column=0;Column<3;Column++){
			ThreadDim[Row][Column]->Calculate();
		}
	}

	GetLayersBase()->UnlockChangingDataStructure();
}
