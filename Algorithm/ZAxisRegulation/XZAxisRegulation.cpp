#include "XZAxisRegulation.h"
#include "XFFT1d.h"
#include "XGeneralFunc.h"

ZAxisRegulationThreshold::ZAxisRegulationThreshold(AlgorithmItemPLI *parent)
:AlgorithmThreshold(parent)
{}

ZAxisRegulationYDirItem::ZAxisRegulationYDirItem(void)
{
	AxisID			=-1;
	AVector			=NULL;
	ResultTable		=NULL;
	ResultLen		=0;

	ResultPeakY		=0;
	CenterInMaster	=0;
	OKZone			=0;
	ResultCenter	=0;
	ResultOK		=0;
	ResultMx		=0;
	ResultMy		=0;
}
ZAxisRegulationYDirItem::~ZAxisRegulationYDirItem(void)
{
	if(ResultTable!=NULL){
		delete	[]ResultTable;
		ResultTable	=NULL;
		ResultLen	=0;
	}
}

bool	ZAxisRegulationYDirItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	if(::Save(f,AxisID)==false){
		return false;
	}
	if(::Save(f,CenterInMaster)==false){
		return false;
	}
	if(::Save(f,OKZone)==false){
		return false;
	}
	return true;
}

bool	ZAxisRegulationYDirItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}
	if(::Load(f,AxisID)==false){
		return false;
	}
	if(GetLoadedVersion()>1){
		if(::Load(f,CenterInMaster)==false){
			return false;
		}
		if(::Load(f,OKZone)==false){
			return false;
		}
	}
	return true;
}

double	MedianFilter(double Data[],int n)
{
	double	Src[1000];
	for(int i=0;i<n;i++){
		Src[i]=Data[i];
	}
	double	MaxD=0;
	int		Index=0;
	int		RetIndex=n/2;
	for(int k=0;k<RetIndex;k++){
		MaxD=0;
		for(int i=0;i<n;i++){
			if(Src[i]>MaxD){
				MaxD=Src[i];
				Index=i;
			}
		}
		Src[k]=0;
	}
	return MaxD;
}
ExeResult	ZAxisRegulationYDirItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);

	ZAxisRegulationBase	*Pr=(ZAxisRegulationBase *)GetParentBase();
	if(GetFromRental()==false){
		GetArea().ClipArea(Pr->Gap,Pr->Gap,GetDotPerLine()-Pr->Gap,GetMaxLines()-Pr->Gap);
	}
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	return Ret;
}

void	ZAxisRegulationYDirItem::Calc(void)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	ResultMx=mx;
	ResultMy=my;

	ZAxisRegulationBase	*Pr=(ZAxisRegulationBase *)GetParentBase();
	int	N=GetArea().GetFLineLen();
	if(ResultLen<N){
		if(ResultTable!=NULL){
			delete	[]ResultTable;
			ResultTable=NULL;
		}
	}
	DataInLayer		*Ly=GetDataInLayer();
	ImageBuffer	&IBuff=(Pr->CheckMaster==true)?Ly->GetMasterBuff():Ly->GetTargetBuff();

	ResultLen=N;
	if(ResultTable==NULL){
		ResultTable=new double[ResultLen];
	}
	double	TmpResult[10000];
	double	MaxD=0;
	for(int i=0;i<ResultLen;i++){
		int	Y =GetArea().GetFLineAbsY(i)+my;
		int	x1=GetArea().GetFLineLeftX(i)+mx;
		int	x2=GetArea().GetFLineRightX(i)+mx;
		BYTE	*s=IBuff.GetY(Y);
		double	Data[10000];
		int	N=0;
		for(int x=x1;x<x2;x++){
			Data[N]=s[x];
			N++;
			if(N>=sizeof(Data)/sizeof(Data[0])){
				break;
			}
		}
		if(N>20){
			double	D=CalcLine(Data,N);
			TmpResult[i]=D;
			if(MaxD<D){
				MaxD=D;
				ResultPeakY=Y;
			}
		}
		else{
			TmpResult[i]=0;
		}
	}
	/*
	int		Median=3;
	for(int i=0;i<Median;i++){
		ResultTable[i]=0;
	}
	for(int i=Median;i<ResultLen-Median;i++){
		ResultTable[i]=MedianFilter(&TmpResult[i],2*Median+1);
	}
	for(int i=ResultLen-Median;i<ResultLen;i++){
		ResultTable[i]=0;
	}
	*/
	for(int i=0;i<ResultLen;i++){
		ResultTable[i]=TmpResult[i];
	}
	ResultCenter=ResultPeakY-my;
	int	d=abs(CenterInMaster-ResultCenter);
	if(d<=OKZone)
		ResultOK=true;
	else
		ResultOK=false;
}


double	ZAxisRegulationYDirItem::CalcLine(double Data[],int N)
{
	ZAxisRegulationBase	*Pr=(ZAxisRegulationBase *)GetParentBase();
	int	ThreCol=Pr->BrightnessRange;

	/*
	FFTClass	FFTData;
	double	ResultData[10000];
	FFTData.fftPower(N,Data,ResultData);
	double	MaxD=0.0;
	int		MaxK=0;
	for(int k=1;k<30 && k<N/2;k++){
		if(ResultData[k]>MaxD){
			MaxD=ResultData[k];
			MaxK=k;
		}
	}
	return MaxD;
	*/

	int	BTable[256];
	for(int i=0;i<256;i++){
		BTable[i]=0;
	}
	for(int i=0;i<N;i++){
		BTable[(int)Data[i]]++;
	}
	int	k=0;
	double	Avr=0;
	int		AvrN=0;
	for(int i=255;i>=0;i--){
		k+=BTable[i];
		if(k>N*0.2){
			for(int j=0;j<i;j++){
				Avr +=BTable[j]*j;
				AvrN+=BTable[j];
			}
			break;
		}
	}
	if(AvrN==0)
		return 0;
	Avr/=AvrN;
	double	SumD=0;
	int		SumN=0;
	for(int i=0;i<N;i++){
		if(Avr-ThreCol<=Data[i] && Data[i]<=Avr+ThreCol){
			SumD+=(Data[i]-Avr)*(Data[i]-Avr);
			SumN++;
		}
	}
	if(SumN!=0){
		return SumD/SumN;
	}
	return 0;
}

void	ZAxisRegulationYDirItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	QPainter	Pnt(&pnt);
	Pnt.setPen(Qt::yellow);
	Pnt.drawLine((x1+movx)*ZoomRate , (ResultPeakY+movy)*ZoomRate, (x2+movx)*ZoomRate, (ResultPeakY+movy)*ZoomRate);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	int	kx=(cx+movx)*ZoomRate;
	int	ky=(cy+movy)*ZoomRate;
				
	QRect	rect(0,0,pnt.width(),pnt.height());
	Pnt.drawText(kx,ky,pnt.width()-kx,pnt.height()-ky
				,Qt::AlignLeft | Qt::AlignTop
				//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
				,QString("ID : ")+QString::number(AxisID)
				,&rect);
	Pnt.drawText(kx,ky+16,pnt.width()-kx,pnt.height()-ky
				,Qt::AlignLeft | Qt::AlignTop
				//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
				,QString("Raw result : ")+QString::number(ResultCenter)
				,&rect);

}

void	ZAxisRegulationYDirItem::DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)
{
	AlgorithmItemPLI::DrawResult    (Res,IData ,PData ,MovX ,MovY ,ZoomRate);
	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);
	PData.setPen(Qt::yellow);
	PData.drawLine((x1+MovX)*ZoomRate , (ResultPeakY+MovY)*ZoomRate, (x2+MovX)*ZoomRate, (ResultPeakY+MovY)*ZoomRate);
}


void	ZAxisRegulationInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddArea	*CmdAddAreaVar=dynamic_cast<CmdAddArea *>(packet);
	if(CmdAddAreaVar!=NULL){
		AlgorithmItemRoot	*L=CreateItem(0);
		L->SetArea(CmdAddAreaVar->Area);
		ZAxisRegulationYDirItem	*YItem=dynamic_cast<ZAxisRegulationYDirItem *>(L);
		if(YItem!=NULL){
			YItem->AxisID			=CmdAddAreaVar->AxisID;
			YItem->CenterInMaster	=CmdAddAreaVar->CenterInMaster;
			YItem->OKZone			=CmdAddAreaVar->OKZone;
		}
		AppendItem(L);
		return;
	}
	CmdStartCalc	*CmdStartCalcVar=dynamic_cast<CmdStartCalc *>(packet);
	if(CmdStartCalcVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			ZAxisRegulationYDirItem	*YItem=dynamic_cast<ZAxisRegulationYDirItem *>(item);
			if(YItem!=NULL){
				YItem->Calc();
			}
		}
		return;
	}
	CmdReqItemInfoList	*CmdReqItemInfoListVar=dynamic_cast<CmdReqItemInfoList *>(packet);
	if(CmdReqItemInfoListVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			ZAxisRegulationYDirItem	*YItem=dynamic_cast<ZAxisRegulationYDirItem *>(item);
			if(YItem!=NULL){
				ItemInfoList	*a=new ItemInfoList();
				YItem->GetXY(a->x1,a->y1,a->x2,a->y2);
				a->ItemID	=YItem->GetID();
				a->AxisID	=YItem->AxisID;
				a->Layer	=GetLayer();
				a->Page		=GetPage();
				a->CenterInMaster	=YItem->CenterInMaster;
				a->OKZone			=YItem->OKZone;
				a->ResultCenter		=YItem->ResultCenter;
				a->ResultOK			=YItem->ResultOK;
				CmdReqItemInfoListVar->Infos.AppendList(a);
			}
		}
		return;
	}
	CmdSetItemInfo	*CmdSetItemInfoVar=dynamic_cast<CmdSetItemInfo *>(packet);
	if(CmdSetItemInfoVar!=NULL){
		AlgorithmItemRoot *item=SearchIDItem(CmdSetItemInfoVar->ItemID);
		if(item!=NULL){
			ZAxisRegulationYDirItem	*YItem=dynamic_cast<ZAxisRegulationYDirItem *>(item);
			if(YItem!=NULL){
				YItem->AxisID			=CmdSetItemInfoVar->AxisID;
				YItem->CenterInMaster	=CmdSetItemInfoVar->CenterInMaster;
				YItem->OKZone			=CmdSetItemInfoVar->OKZone;
			}
		}
		return;
	}
	CmdReqItemResult	*CmdReqItemResultVar=dynamic_cast<CmdReqItemResult *>(packet);
	if(CmdReqItemResultVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			ZAxisRegulationYDirItem	*YItem=dynamic_cast<ZAxisRegulationYDirItem *>(item);
			if(YItem!=NULL){
				if(YItem->AxisID==CmdReqItemResultVar->AxisID){
					CmdReqItemResultVar->ResultTable=new double[YItem->ResultLen];
					CmdReqItemResultVar->ResultCount=YItem->ResultLen;
					for(int i=0;i<CmdReqItemResultVar->ResultCount;i++){
						CmdReqItemResultVar->ResultTable[i]=YItem->ResultTable[i];
					}
					return;
				}
			}
		}
		return;
	}
}

void	ZAxisRegulationInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddArea	*CmdAddAreaVar=dynamic_cast<CmdAddArea *>(packet);
	if(CmdAddAreaVar!=NULL){
		if(CmdAddAreaVar->Layers.IsEmpty()==true){
			for(int layer=0;layer<GetLayerNumb();layer++){
				GetLayerData(layer)->TransmitDirectly(CmdAddAreaVar);
			}
		}
		else{
			for(IntClass *c=CmdAddAreaVar->Layers.GetFirst();c!=NULL;c=c->GetNext()){
				GetLayerData(c->GetValue())->TransmitDirectly(CmdAddAreaVar);
			}
		}
		return;
	}
	CmdStartCalc	*CmdStartCalcVar=dynamic_cast<CmdStartCalc *>(packet);
	if(CmdStartCalcVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqItemInfoList	*CmdReqItemInfoListVar=dynamic_cast<CmdReqItemInfoList *>(packet);
	if(CmdReqItemInfoListVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdSetItemInfo	*CmdSetItemInfoVar=dynamic_cast<CmdSetItemInfo *>(packet);
	if(CmdSetItemInfoVar!=NULL){
		GetLayerData(CmdSetItemInfoVar->Layer)->TransmitDirectly(packet);
		return;
	}
}

//=======================================================================
ZAxisRegulationBase::ZAxisRegulationBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorRegulation		=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorRegulation	=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	BrightnessRange		=20;
	CheckMaster			=true;
	Gap					=100;

	SetParam(&ColorRegulation	, /**/"Color" ,/**/"ColorRegulation"		,"Color for Regulation area");
	SetParam(&ColorSelected		, /**/"Color" ,/**/"ColorSelected"			,"Color for Selected Piece");
	SetParam(&ColorActive		, /**/"Color" ,/**/"ColorActive"			,"Color for Active Piece");
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&NegColorRegulation, /**/"Color" ,/**/"NegColorRegulation"		,"Color for Negative Regulation area");
	SetParam(&NegColorSelected	, /**/"Color" ,/**/"NegColorSelected"		,"Color for Negative selected Regulation");
	SetParam(&BrightnessRange	, /**/"Setting" ,/**/"BrightnessRange"		,"Range of brightness (one side)");
	SetParam(&CheckMaster		, /**/"Setting" ,/**/"CheckMaster"			,"Check if master image is checked");
	SetParam(&Gap				, /**/"Setting" ,/**/"Gap"					,"Dummy zone of outline image");
}

AlgorithmDrawAttr	*ZAxisRegulationBase::CreateDrawAttr(void)
{
	return new ZAxisRegulationDrawAttr();
}
