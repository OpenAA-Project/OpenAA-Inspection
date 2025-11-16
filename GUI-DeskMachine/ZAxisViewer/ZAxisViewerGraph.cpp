#include "ZAxisViewerGraph.h"
#include "XZAxisRegulation.h"
#include "XPropertyZRegulationPacket.h"

extern	char	*sRoot;
extern	char	*sName;

ZAxisViewerGraph::ZAxisViewerGraph(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),LGraph(parent)
{
	ui.setupUi(this);

	ID		=0;
	Page	=0;
	PowerColor	=Qt::green;
	LineColor	=Qt::red;

	LGraph.setParent(this);
	//LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	LGraph.move(0,0);
	LGraph.resize(width(),height());

	GraphPower	.SetLineColor(PowerColor);
	GraphPower	.SetLineWidth(1);
	GraphPower	.SetOffsetX(0);
	GraphLine		.SetLineColor(LineColor);	
	GraphLine		.SetLineWidth(1);
	GraphLine		.SetOffsetX(2);

	LGraph.AddGraph(&GraphPower);
	LGraph.AddGraph(&GraphLine);
	//connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));
}

ZAxisViewerGraph::~ZAxisViewerGraph()
{

}

void	ZAxisViewerGraph::ShowInPlayer(int64 shownInspectionID)
{
}
void	ZAxisViewerGraph::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdStartCalc	*CmdStartCalcVar=dynamic_cast<CmdStartCalc *>(packet);
	if(CmdStartCalcVar!=NULL){
		GraphPower	.SetLineColor(PowerColor);
		GraphLine	.SetLineColor(LineColor);

		GUICmdReqItemResult	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdAckItemResult	ACmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.AxisID	=ID;
		RCmd.Layer	=0;
	
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ZRegulationImagePanel" ,/**/"");
		if(GProp==NULL){
			return;
		}
		CmdReqLayersListPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		if(Da.Layers.IsEmpty()==true){
			RCmd.Layer	=0;
		}
		else{
			IntClass	*c=Da.Layers.GetFirst();
			RCmd.Layer	=c->GetValue();
		}

		if(RCmd.Send(Page,0,ACmd)==true){
			if(ACmd.ResultTable!=NULL){
				GraphPower.DeleteXY();
				GraphLine.DeleteXY();

				double	YMax=0.0;
				for(int i=0;i<ACmd.ResultCount;i++){
					if(YMax<ACmd.ResultTable[i]){
						YMax=ACmd.ResultTable[i];
					}
				}
				if(YMax!=0.0){
					for(int i=0;i<ACmd.ResultCount;i++){
						GraphPower.AddXY(i,ACmd.ResultTable[i]*1000.0/YMax);
					}
				}
			}
	
			//GraphLine.AddXY(ThresholdB,PeakHist);
			LGraph.repaint();
		}
	}
}


//==================================================================================
GUICmdReqItemResult::GUICmdReqItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqItemResult::Load(QIODevice *f)
{
	if(::Load(f,AxisID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqItemResult::Save(QIODevice *f)
{
	if(::Save(f,AxisID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	return true;
}
void	GUICmdReqItemResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckItemResult	*SendBack=GetSendBack(GUICmdAckItemResult,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	QString	AlgoRoot=/**/"Regulation";
	QString	AlgoName=/**/"ZAxis";
	AlgorithmBase	*Base=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);

	CmdReqItemResult	RCmd(GetLayersBase());
	RCmd.AxisID=AxisID;
	
	Base->GetPageData(localPage)->GetLayerData(Layer)->TransmitDirectly(&RCmd);
	SendBack->ResultTable	=RCmd.ResultTable;
	SendBack->ResultCount	=RCmd.ResultCount;
	RCmd.ResultTable	=NULL;
	RCmd.ResultCount	=0;

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckItemResult::GUICmdAckItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ResultTable=NULL;
	ResultCount=0;
}
GUICmdAckItemResult::~GUICmdAckItemResult(void)
{
	if(ResultTable!=NULL){
		delete	[]ResultTable;
		ResultTable=NULL;
	}
	ResultCount=0;
}
bool	GUICmdAckItemResult::Load(QIODevice *f)
{
	if(::Load(f,ResultCount)==false){
		return false;
	}
	if(ResultTable!=NULL){
		delete	[]ResultTable;
	}
	ResultTable=new double[ResultCount];
	f->read((char *)ResultTable,ResultCount*sizeof(double));
	return true;
}
bool	GUICmdAckItemResult::Save(QIODevice *f)
{
	if(::Save(f,ResultCount)==false){
		return false;
	}
	f->write((const char *)ResultTable,ResultCount*sizeof(double));
	return true;
}


