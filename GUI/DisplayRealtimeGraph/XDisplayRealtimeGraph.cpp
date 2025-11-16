#include "XDisplayRealtimeGraph.h"
#include "XDataInLayer.h"
#include "XPropertyRealtimeGraphCommon.h"
#include "XGUIFormBase.h"
#include "DisplayRealtimeGraph.h"
#include "XDisplayImage.h"

DisplayRealtimeGraphBrightness::DisplayRealtimeGraphBrightness(LayersBase *Base 
															  ,DisplayRealtimeGraph *p
															  ,QWidget *parent)
	:ServiceForLayers(Base),Parent(p)
{
	Page=0;
	AllocLayerNumb=GetLayerNumb(Page);
	AllocXLen	=GetDotPerLine(0);

	LineData	=new double*[GetLayerNumb(Page)];
	GraphLine	=new mtGLine[AllocLayerNumb];

	GraphBase.setParent(Parent);
	GraphBase.SetScaleTypeY(mtLineGraph::mtConstant);
	GraphBase.move(0,0);

	for(int layer=0;layer<GetLayerNumb(Page);layer++){
		LineData[layer]	=new double[AllocXLen];
		GraphLine[layer].SetLineColor(GetParamGlobal()->GetOneGraphLayerColor(layer));
		GraphLine[layer].SetLineWidth(1);
		GraphLine[layer].SetOffsetX(0);

		GraphBase.AddGraph(&GraphLine[layer]);
	}
}
DisplayRealtimeGraphBrightness::~DisplayRealtimeGraphBrightness(void)
{
	for(int layer=0;layer<AllocLayerNumb;layer++){
		delete	[]LineData[layer];
	}
	delete	[]LineData;
	LineData=NULL;
	delete	[]GraphLine;
	GraphLine=NULL;
}

void	DisplayRealtimeGraphBrightness::SetGeometry(int x, int y ,int w ,int h)
{
	GraphBase.move(x,y);
	GraphBase.resize(w,h);
}
void	DisplayRealtimeGraphBrightness::Repaint(void)
{
	CamNo=0;
	CmdReqRealtimeGraphCamera	RCmd(GetLayersBase());
	if(Parent->PropertyRealtimeGraphPointer!=NULL){
		Parent->PropertyRealtimeGraphPointer->TransmitDirectly(&RCmd);
		CamNo		=RCmd.CamNo;
		Calclating	=RCmd.Capturing;
	}
	if(CamNo<0)
		return;

	int	LeftX=0;
	double	ZoomRate=1.0;
	if(Parent->RealtimeImagePanelPointer!=NULL){
		LeftX=Parent->RealtimeImagePanelPointer->GetMovx();
		ZoomRate=Parent->RealtimeImagePanelPointer->GetZoomRate();
	}

	IntList	PageList;
	GetParamGlobal()->GetPageListFromCameraNo(CamNo,PageList);
	int	Page=0;
	if(PageList.GetCount()>0){
		Page=PageList.GetFirst()->GetValue();
	}

	if(AllocLayerNumb!=GetLayerNumb(Page) || AllocXLen!=GetDotPerLine(Page)){
		AllocLayerNumb=GetLayerNumb(Page);
		for(int layer=0;layer<AllocLayerNumb;layer++){
			delete	[]LineData[layer];
		}
		delete	[]LineData;
		AllocXLen	=GetDotPerLine(Page);
		LineData	=new double*[AllocLayerNumb];

		GraphBase.ClearGraph();
		delete	[]GraphLine;

		GraphLine	=new mtGLine[AllocLayerNumb];

		for(int layer=0;layer<GetLayerNumb(Page);layer++){
			LineData[layer]	=new double[AllocXLen];
			GraphLine[layer].SetLineColor(GetParamGlobal()->GetOneGraphLayerColor(layer));
			GraphLine[layer].SetLineWidth(1);
			GraphLine[layer].SetOffsetX(0);

			GraphBase.AddGraph(&GraphLine[layer]);
		}
	}
	//GraphBase.SetOffsetX(LeftX);
	int	Wid=GraphBase.width();
	int	DotPerLine=GetDotPerLine(Page);

	ImagePointerContainer Images;
	DataInPage *dp=GetLayersBase()->GetPageData(Page);
	if(dp!=NULL){
		dp->GetTargetImages(Images);

		int	YN=GetMaxLines(Page);
		int	XN=GetDotPerLine(Page);
			
		#pragma omp parallel
		{
			#pragma omp for
			for(int layer=0;layer<AllocLayerNumb;layer++){
				memset(LineData[layer],0,XN*sizeof(double));
				ImageBuffer	*Buff=Images[layer];
				for(int y=0;y<YN;y++){
					BYTE	*s=Buff->GetY(y);
					for(int x=0;x<XN;x++){
						(LineData[layer])[x]+=s[x];
					}
				}
				for(int x=0;x<XN;x++){
					(LineData[layer])[x]/=(double)YN;
				}
				GraphLine[layer].DeleteXY();
				for(int i=0;i<XN;i++){
					GraphLine[layer].AddXY(i,(int)LineData[layer][i]);
				}
				//for(int w=0;w<Wid;w++){
				//	int	X=(w-LeftX)/ZoomRate;
				//	if(X<0 || DotPerLine<=X){
				//		GraphLine[layer].AddXY(w,0);
				//	}
				//	else{
				//		GraphLine[layer].AddXY(w,(int)LineData[layer][X]);
				//	}
				//}
			}
		}
		GraphBase.repaint();
	}
}

//======================================================================================

DisplayRealtimeGraphFocus::DisplayRealtimeGraphFocus(LayersBase *Base 
															  ,DisplayRealtimeGraph *p
															  ,QWidget *parent)
	:ServiceForLayers(Base),Parent(p)
{
	int	tPage=0;
	AllocLayerNumb=GetLayerNumb(tPage);
	AllocXLen	=GetDotPerLine(0);

	LineData	=new double*[GetLayerNumb(tPage)];
	GraphLine	=new mtGLine[AllocLayerNumb];

	GraphBase.setParent(Parent);
	GraphBase.SetScaleTypeY(mtLineGraph::mtConstant);
	GraphBase.move(0,0);

	for(int layer=0;layer<GetLayerNumb(tPage);layer++){
		LineData[layer]	=new double[AllocXLen];
		GraphLine[layer].SetLineColor(GetParamGlobal()->GetOneGraphLayerColor(layer));
		GraphLine[layer].SetLineWidth(1);
		GraphLine[layer].SetOffsetX(0);

		GraphBase.AddGraph(&GraphLine[layer]);
	}
}
DisplayRealtimeGraphFocus::~DisplayRealtimeGraphFocus(void)
{
	for(int layer=0;layer<AllocLayerNumb;layer++){
		delete	[]LineData[layer];
	}
	delete	[]LineData;
	LineData=NULL;
	delete	[]GraphLine;
	GraphLine=NULL;
}

void	DisplayRealtimeGraphFocus::SetGeometry(int x, int y ,int w ,int h)
{
	GraphBase.move(x,y);
	GraphBase.resize(w,h);
}

void	DisplayRealtimeGraphFocus::Repaint(void)
{
	CamNo=0;
	CmdReqRealtimeGraphCamera	RCmd(GetLayersBase());
	if(Parent->PropertyRealtimeGraphPointer!=NULL){
		Parent->PropertyRealtimeGraphPointer->TransmitDirectly(&RCmd);
		CamNo		=RCmd.CamNo;
		Calclating	=RCmd.Capturing;
	}
	if(CamNo<0)
		return;
	IntList	PageList;
	GetParamGlobal()->GetPageListFromCameraNo(CamNo,PageList);
	int	Page=0;
	if(PageList.GetCount()>0){
		Page=PageList.GetFirst()->GetValue();
	}

	if(AllocLayerNumb!=GetLayerNumb(Page) || AllocXLen!=GetDotPerLine(Page)){
		AllocLayerNumb=GetLayerNumb(Page);
		for(int layer=0;layer<AllocLayerNumb;layer++){
			delete	[]LineData[layer];
		}
		delete	[]LineData;
		AllocXLen	=GetDotPerLine(Page);
		LineData	=new double*[AllocLayerNumb];

		GraphBase.ClearGraph();
		delete	[]GraphLine;

		GraphLine	=new mtGLine[AllocLayerNumb];

		for(int layer=0;layer<GetLayerNumb(Page);layer++){
			LineData[layer]	=new double[AllocXLen];
			GraphLine[layer].SetLineColor(GetParamGlobal()->GetOneGraphLayerColor(layer));
			GraphLine[layer].SetLineWidth(1);
			GraphLine[layer].SetOffsetX(0);

			GraphBase.AddGraph(&GraphLine[layer]);
		}
	}

	ImagePointerContainer Images;
	DataInPage *dp=GetLayersBase()->GetPageData(Page);
	if(dp!=NULL){
		
		int	YN=GetMaxLines(Page);
		int	XN=GetDotPerLine(Page);
		#pragma omp parallel
		{
			#pragma omp for
			for(int layer=0;layer<AllocLayerNumb;layer++){
				double	*Brightness=Parent->PanelBrightness->LineData[layer];

				memset(LineData[layer],0,XN*sizeof(double));

				int	Len=16;
				int	Len2=Len/2;
				for(int x=Len2+10;x<XN-Len2-10;x++){
					LineData[layer][x]=MakeFFTValue(Brightness,x,Len);
				}
				GraphLine[layer].DeleteXY();
				for(int i=0;i<XN;i++){
					GraphLine[layer].AddXY(i,LineData[layer][i]);
				}
			}
		}
		GraphBase.repaint();
	}
}

double	DisplayRealtimeGraphFocus::MakeFFTValue(double Brightness[] ,int XPos,int Len)
{
	int	Len2=Len/2;
	double	MaxD=0;
	for(int L1=0;L1<Len2;L1++){
		double	d1=Brightness[XPos+L1];
		for(int L2=1;L2<Len2;L2++){
			double	d2=Brightness[XPos-L2];
			double	D=fabs(d1-d2)/(L1+L2);
			if(MaxD<D){
				MaxD=D;
			}
		}
	}
	return MaxD;
}

//======================================================================================


