#include "ColorDifferenceResource.h"
#include "SHowFlowGraphDialog.h"
#include "ui_SHowFlowGraphDialog.h"
#include "swap.h"


SHowFlowGraphDialog::SHowFlowGraphDialog(LayersBase *base ,ColorDifferenceItem *item ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Item(item)
    ,ui(new Ui::SHowFlowGraphDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	
	QColor	MasterColor=ui->label_Flow->palette().color(QPalette::Window);
	QColor	TargetColor=ui->label_Target->palette().color(QPalette::Window);
	QColor	ThreshColor=ui->label_Thresh->palette().color(QPalette::Window);

	HLGraph.setParent(ui->frameH);
	HLGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	HLGraph.move(0,0);
	HGraphColMaster	.SetLineColor(MasterColor);
	HGraphColMaster	.SetLineWidth(1);
	HGraphColMaster	.SetOffsetX(0);
	HGraphColTarget	.SetLineColor(TargetColor);
	HGraphColTarget	.SetLineWidth(1);
	HGraphColTarget	.SetOffsetX(1);
	HGraphThresh	.SetLineColor(ThreshColor);	
	HGraphThresh	.SetLineWidth(1);
	HGraphThresh	.SetOffsetX(2);
	HLGraph.AddGraph(&HGraphColMaster);
	HLGraph.AddGraph(&HGraphColTarget);
	HLGraph.AddGraph(&HGraphThresh);

	SLGraph.setParent(ui->frameS);
	SLGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	SLGraph.move(0,0);
	SGraphColMaster	.SetLineColor(MasterColor);
	SGraphColMaster	.SetLineWidth(1);
	SGraphColMaster	.SetOffsetX(0);
	SGraphColTarget	.SetLineColor(TargetColor);
	SGraphColTarget	.SetLineWidth(1);
	SGraphColTarget	.SetOffsetX(1);
	SGraphThresh	.SetLineColor(ThreshColor);	
	SGraphThresh	.SetLineWidth(1);
	SGraphThresh	.SetOffsetX(2);
	SLGraph.AddGraph(&SGraphColMaster);
	SLGraph.AddGraph(&SGraphColTarget);
	SLGraph.AddGraph(&SGraphThresh);

	VLGraph.setParent(ui->frameV);
	VLGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	VLGraph.move(0,0);
	VGraphColMaster	.SetLineColor(MasterColor);
	VGraphColMaster	.SetLineWidth(1);
	VGraphColMaster	.SetOffsetX(0);
	VGraphColTarget	.SetLineColor(TargetColor);
	VGraphColTarget	.SetLineWidth(1);
	VGraphColTarget	.SetOffsetX(1);
	VGraphThresh	.SetLineColor(ThreshColor);	
	VGraphThresh	.SetLineWidth(1);
	VGraphThresh	.SetOffsetX(2);
	VLGraph.AddGraph(&VGraphColMaster);
	VLGraph.AddGraph(&VGraphColTarget);
	VLGraph.AddGraph(&VGraphThresh);

	ELGraph.setParent(ui->frameE);
	ELGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	ELGraph.move(0,0);
	EGraphColMaster	.SetLineColor(MasterColor);
	EGraphColMaster	.SetLineWidth(1);
	EGraphColMaster	.SetOffsetX(0);
	EGraphColTarget	.SetLineColor(TargetColor);
	EGraphColTarget	.SetLineWidth(1);
	EGraphColTarget	.SetOffsetX(1);
	EGraphThresh	.SetLineColor(ThreshColor);	
	EGraphThresh	.SetLineWidth(1);
	EGraphThresh	.SetOffsetX(2);
	ELGraph.AddGraph(&EGraphColMaster);
	ELGraph.AddGraph(&EGraphColTarget);
	ELGraph.AddGraph(&EGraphThresh);

	ShowGraph();
}

SHowFlowGraphDialog::~SHowFlowGraphDialog()
{
    delete ui;
}

void SHowFlowGraphDialog::resizeEvent ( QResizeEvent * event )
{
	int	H=(height()-ui->frameHeader->height())/4;
	ui->frameHeader->resize(width(),ui->frameHeader->height());

	ui->labelH	->setGeometry(0	,ui->frameHeader->height()+0	,42,H);
	ui->labelS	->setGeometry(0	,ui->frameHeader->height()+H	,42,H);
	ui->labelV	->setGeometry(0	,ui->frameHeader->height()+H*2	,42,H);
	ui->labelE	->setGeometry(0	,ui->frameHeader->height()+H*3	,42,H);

	ui->frameH->setGeometry(42	,ui->frameHeader->height()+0	,width()-42,H);
	ui->frameS->setGeometry(42	,ui->frameHeader->height()+H	,width()-42,H);
	ui->frameV->setGeometry(42	,ui->frameHeader->height()+H*2	,width()-42,H);
	ui->frameE->setGeometry(42	,ui->frameHeader->height()+H*3	,width()-42,H);

	HLGraph.resize(ui->frameH->width(),ui->frameH->height());
	SLGraph.resize(ui->frameS->width(),ui->frameS->height());
	VLGraph.resize(ui->frameV->width(),ui->frameV->height());
	ELGraph.resize(ui->frameE->width(),ui->frameE->height());

	HLGraph.repaint();
	SLGraph.repaint();
	VLGraph.repaint();
	ELGraph.repaint();
}

void SHowFlowGraphDialog::ShowGraph(void)
{
	HGraphColMaster.DeleteXY();
	HGraphColTarget.DeleteXY();
	HGraphThresh.DeleteXY();

	SGraphColMaster.DeleteXY();
	SGraphColTarget.DeleteXY();
	SGraphThresh.DeleteXY();

	VGraphColMaster.DeleteXY();
	VGraphColTarget.DeleteXY();
	VGraphThresh.DeleteXY();

	EGraphColMaster.DeleteXY();
	EGraphColTarget.DeleteXY();
	EGraphThresh.DeleteXY();

	ColorDifferenceBase	*ABase=Item->tGetParentBase();
	int	N=Item->FlowBrightness.GetCount();
	double	*HDim=new double [N];
	double	*SDim=new double [N];
	double	*VDim=new double [N];
	double	*EDim=new double [N];

	double	MinH=99999999;
	double	MaxH=-99999999;
	double	MinS=99999999;
	double	MaxS=-99999999;
	double	MinV=99999999;
	double	MaxV=-99999999;
	double	MinE=99999999;
	double	MaxE=-99999999;

	double	mL,mA,mB;
	double	mX,mY,mZ;
	::RGB2XYZ(Item->MasterColor.GetRed(),Item->MasterColor.GetGreen(),Item->MasterColor.GetBlue(),mX ,mY ,mZ);
	::XYZ2LAB(mX,mY,mZ,mL,mA,mB);
	int	n=0;
	for(PreciseColorList *L=Item->FlowBrightness.GetFirst();L!=NULL;L=L->GetNext(),n++){
		double	H,S,V;
		::RGB2HSV(H,S,V ,L->GetRed(),L->GetGreen(),L->GetBlue());
		double	tX,tY,tZ;
		::RGB2XYZ(L->GetRed(),L->GetGreen(),L->GetBlue(),tX ,tY ,tZ);
		double	tL,tA,tB;
		::XYZ2LAB(tX,tY,tZ,tL,tA,tB);
		double	E;
		if(ABase->DeltaE2000==true)
			E=::GetDeltaE2000(mL,mA,mB ,tL,tA,tB);
		else
			E=::GetDeltaE76(mL,mA,mB ,tL,tA,tB);

		HDim[n]=H;
		SDim[n]=S;
		VDim[n]=V;
		MinH=min(H,MinH);
		MaxH=max(H,MaxH);
		MinS=min(S,MinS);
		MaxS=max(S,MaxS);
		MinV=min(V,MinV);
		MaxV=max(V,MaxV);
		EDim[n]=E;
		MinE=min(MinE,E);
		MaxE=max(MaxE,E);
	}
	double	tH,tS,tV;
	double	tE;
	{
		::RGB2HSV(tH,tS,tV ,Item->ReferedCurrentColor.GetRed(),Item->ReferedCurrentColor.GetGreen(),Item->ReferedCurrentColor.GetBlue());
		double	tX,tY,tZ;
		::RGB2XYZ(Item->ReferedCurrentColor.GetRed(),Item->ReferedCurrentColor.GetGreen(),Item->ReferedCurrentColor.GetBlue(),tX ,tY ,tZ);
		double	tL,tA,tB;
		::XYZ2LAB(tX,tY,tZ,tL,tA,tB);
		if(ABase->DeltaE2000==true)
			tE=::GetDeltaE2000(mL,mA,mB ,tL,tA,tB);
		else
			tE=::GetDeltaE76(mL,mA,mB ,tL,tA,tB);

		MinH=min(tH,MinH);
		MaxH=max(tH,MaxH);
		MinS=min(tS,MinS);
		MaxS=max(tS,MaxS);
		MinV=min(tV,MinV);
		MaxV=max(tV,MaxV);
		MinE=min(MinE,tE);
		MaxE=max(MaxE,tE);
	}
	MinE=min(MinE,Item->GetThresholdR(GetLayersBase())->THDeltaE);
	MaxE=max(MaxE,Item->GetThresholdR(GetLayersBase())->THDeltaE);

	const	int	DN=50;
	double	dH=(MaxH-MinH)/DN;
	double	dS=(MaxS-MinS)/DN;
	double	dV=(MaxV-MinV)/DN;
	double	dE=(MaxE-MinE)/DN;

	int	HistH[DN+1];
	int	HistS[DN+1];
	int	HistV[DN+1];
	int	HistE[DN+1];

	memset(HistH,0,sizeof(HistH));
	memset(HistS,0,sizeof(HistS));
	memset(HistV,0,sizeof(HistV));
	memset(HistE,0,sizeof(HistE));
	for(int i=0;i<N;i++){
		HistH[(dH>0)?(int)((HDim[i]-MinH)/dH):0]++;
		HistS[(dS>0)?(int)((SDim[i]-MinS)/dS):0]++;
		HistV[(dV>0)?(int)((VDim[i]-MinV)/dV):0]++;
		HistE[(dE>0)?(int)((EDim[i]-MinE)/dE):0]++;
	}
	int	MaxHistH=0;
	int	MaxHistS=0;
	int	MaxHistV=0;
	int	MaxHistE=0;
	for(int i=0;i<DN+1;i++){
		if(HistH[i]!=0)	HGraphColMaster.AddXY(i*dH+MinH,HistH[i]);
		if(HistS[i]!=0)	SGraphColMaster.AddXY(i*dS+MinS,HistS[i]);
		if(HistV[i]!=0)	VGraphColMaster.AddXY(i*dV+MinV,HistV[i]);
		if(HistE[i]!=0)	EGraphColMaster.AddXY(i*dE+MinE,HistE[i]);

		MaxHistH=max(MaxHistH,HistH[i]);
		MaxHistS=max(MaxHistS,HistS[i]);
		MaxHistV=max(MaxHistV,HistV[i]);
		MaxHistE=max(MaxHistE,HistE[i]);
	}
	HGraphColTarget.AddXY( ((int)((dH>0)?(tH-MinH)/dH:0))*dH+MinH,MaxHistH);
	SGraphColTarget.AddXY( ((int)((dS>0)?(tS-MinS)/dS:0))*dS+MinS,MaxHistS);
	VGraphColTarget.AddXY( ((int)((dV>0)?(tV-MinV)/dV:0))*dV+MinV,MaxHistV);
	EGraphColTarget.AddXY( ((int)((dE>0)?(tE-MinE)/dE:0))*dE+MinE,MaxHistE);

	HGraphThresh.AddXY( ((int)(dH>0)?((Item->StatisticData.HAvr-Item->GetThresholdR(GetLayersBase())->dH -MinH)/dH):0)*dH+MinH,MaxHistH);
	SGraphThresh.AddXY( ((int)(dS>0)?((Item->StatisticData.SAvr-Item->GetThresholdR(GetLayersBase())->dSL-MinS)/dS):0)*dS+MinS,MaxHistS);
	VGraphThresh.AddXY( ((int)(dV>0)?((Item->StatisticData.VAvr-Item->GetThresholdR(GetLayersBase())->dVL-MinV)/dV):0)*dV+MinV,MaxHistV);
	HGraphThresh.AddXY( ((int)(dH>0)?((Item->StatisticData.HAvr+Item->GetThresholdR(GetLayersBase())->dH -MinH)/dH):0)*dH+MinH,MaxHistH);
	SGraphThresh.AddXY( ((int)(dS>0)?((Item->StatisticData.SAvr+Item->GetThresholdR(GetLayersBase())->dSH-MinS)/dS):0)*dS+MinS,MaxHistS);
	VGraphThresh.AddXY( ((int)(dV>0)?((Item->StatisticData.VAvr+Item->GetThresholdR(GetLayersBase())->dVH-MinV)/dV):0)*dV+MinV,MaxHistV);
	EGraphThresh.AddXY( ((int)(dE>0)?((Item->GetThresholdR(GetLayersBase())->THDeltaE-MinE)/dE):0)*dE+MinE,MaxHistE);

	HLGraph.repaint();
	SLGraph.repaint();
	VLGraph.repaint();
	ELGraph.repaint();

	delete	[]HDim;
	delete	[]SDim;
	delete	[]VDim;
	delete	[]EDim;
}
