#include "XDotRegulation.h"
#include "XFFT1d.h"
#include "XGeneralFunc.h"
#include "XPropertyDotRegulationPacket.h"
#include "XPointer.h"
#include "XImageProcess.h"

DotRegulationThreshold::DotRegulationThreshold(AlgorithmItemPLI *parent)
:AlgorithmThreshold(parent)
{}

DotRegulationBrightnessItem::DotRegulationBrightnessItem(void)
{
	ResultTable	=NULL;
	ResultLen	=0;
}
DotRegulationBrightnessItem::~DotRegulationBrightnessItem(void)
{
	if(ResultTable!=NULL){
		delete	[]ResultTable;
		ResultTable	=NULL;
		ResultLen	=0;
	}
}

bool	DotRegulationBrightnessItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	return true;
}

bool	DotRegulationBrightnessItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}
	return true;
}

void	DotRegulationBrightnessItem::Calc(void)
{
	int	N=GetArea().GetFLineLen();
	if(ResultLen<N){
		if(ResultTable!=NULL){
			delete	[]ResultTable;
			ResultTable=NULL;
		}
	}
	DataInLayer		*Ly=GetDataInLayer();
	ImageBuffer	&IBuff=Ly->GetMasterBuff();

	ResultLen=N;
	if(ResultTable==NULL){
		ResultTable=new double[ResultLen];
	}
	for(int i=0;i<ResultLen;i++){
		int	Y =GetArea().GetFLineAbsY(i);
		int	x1=GetArea().GetFLineLeftX(i);
		int	x2=GetArea().GetFLineRightX(i);
		FFTClass	FFTData;
		BYTE	*s=IBuff.GetY(Y);
		double	Data[10000];
		double	ResultData[10000];
		int	N=0;
		for(int x=x1;x<x2;x++){
			Data[N]=s[x];
			N++;
			if(N>=sizeof(Data)/sizeof(Data[0])){
				break;
			}
		}
		if(N>20){
			FFTData.fftPower(N,Data,ResultData);
			double	MaxD=0.0;
			int		MaxK=0;
			for(int k=1;k<30 && k<N/2;k++){
				if(ResultData[k]>MaxD){
					MaxD=ResultData[k];
					MaxK=k;
				}
			}
			/*
			MaxD=0.0;
			double	OtherD=0.0;
			for(int k=1;k<N/2;k++){
				if((MaxK-1)<=k && k<=(MaxK+1)){
					MaxD+=ResultData[k];
				}
				else{
					OtherD+=ResultData[k];
				}
			}
			if(OtherD!=0.0){
				ResultTable[i]=MaxD/OtherD;
			}
			else{
				ResultTable[i]=0.0;
			}
			*/
			ResultTable[i]=MaxD;
		}
		else{
			ResultTable[i]=0;
		}
	}
}

//==================================================================================
DotRegulationFocusItem::DotRegulationFocusItem(void)
{
}
DotRegulationFocusItem::~DotRegulationFocusItem(void)
{
}


bool    DotRegulationFocusItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	return true;
}
bool    DotRegulationFocusItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}
	return true;
}

void	DotRegulationFocusItem::Calc(void)
{
}

//==================================================================================
DotRegulationDotArea::DotRegulationDotArea(void)
{
}
DotRegulationDotArea::~DotRegulationDotArea(void)
{
}


bool    DotRegulationDotArea::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	return true;
}
bool    DotRegulationDotArea::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}
	return true;
}

void	DotRegulationDotArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	//AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);

	QRgb	col=qRgb(200,0,130);

	for(PureFlexAreaList *p=PureFlexAreaListContainer.GetFirst();p!=NULL;p=p->GetNext()){
		p->Draw(0,0,&pnt,col,ZoomRate,movx,movy);
	}
}
void	DotRegulationDotArea::Pickup(int Threshold)
{
	ImageBuffer	&Buff=GetMasterBuff();

	int	XByte=(GetDotPerLine()+7)/8;
	int	YLen =GetMaxLines();
	BYTE	**BmpMap=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(BmpMap ,0 ,XByte ,YLen);

	for(int i=0;i<GetArea().GetFLineLen();i++){
		int y	=GetArea().GetFLineAbsY(i);
		int	x1	=GetArea().GetFLineLeftX(i);
		int	Numb=GetArea().GetFLineNumb(i);

		BYTE	*S=Buff.GetY(y);
		BYTE	*D=BmpMap[y];


		for(int n=0;n<Numb;n++){
			int	x=x1+n;
			if(Threshold<=S[x]){
				SetBmpBitOnY1(D,x);
			}
		}
	}

	PureFlexAreaListContainer.RemoveAll();
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpMap ,XByte ,GetDotPerLine(),YLen,FPack);
	double	AreaSum=0;
	int		AreaN=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		AreaSum+=f->GetPatternByte();
		AreaN++;
	}
	if(AreaN!=0){
		double	AreaAvr=AreaSum/AreaN;
		double	ThreL=AreaAvr*0.6;
		double	ThreH=AreaAvr*1.6;
		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			int64	N=f->GetPatternByte();
			if(ThreL<N && N<ThreH){
				PureFlexAreaList	*L=new PureFlexAreaList();
				*L=*f;
				PureFlexAreaListContainer.AppendList(L);
			}
		}
	}
	DeleteMatrixBuff(BmpMap,YLen);
}


int	SortFuncDouble(const void *a ,const void *b)
{
	double	*pa=(double *)a;
	double	*pb=(double *)b;
	if(*pa>*pb)
		return 1;
	else if(*pa<*pb)
		return -1;
	return 0;
}

void	DotRegulationDotArea::MakeXPosListStr(DoubleList &List)
{
	double	DDim[2000];
	int		DDimNumb=0;
	PureFlexAreaList *f;
	while((f=PureFlexAreaListContainer.GetFirst())!=NULL){
		PureFlexAreaListContainer	PContainer;
		PureFlexAreaListContainer.RemoveList(f);
		PContainer.AppendList(f);

		PureFlexAreaList	*a=f;
		while((a=FindUpper(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}
		a=f;
		while((a=FindDown(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}

		double	AddedCx=0;
		int		N=0;
		for(PureFlexAreaList *t=PContainer.GetFirst();t!=NULL;t=t->GetNext()){
			double	Cx,Cy;
			t->GetCenter(Cx,Cy);
			AddedCx+=Cx;
			N++;
		}
		AddedCx/=N;

		DDim[DDimNumb]=AddedCx;
		DDimNumb++;
	}

	QSort(DDim,DDimNumb,sizeof(double),SortFuncDouble);

	for(int i=0;i<DDimNumb;i++){
		List.Add(DDim[i]);
	}
}

PureFlexAreaList	*DotRegulationDotArea::FindUpper(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer)
{
	double	MinL=99999999;
	PureFlexAreaList	*Found=NULL;
	int	sx1,sy1,sx2,sy2;
	a->GetXY(sx1,sy1,sx2,sy2);
	for(PureFlexAreaList *b=PureFlexAreaListContainer.GetFirst();b!=NULL;b=b->GetNext()){
		int	cx,cy;
		b->GetCenter(cx,cy);
		if(sx1<=cx && cx<=sx2 && sy1>cy){
			double	L=hypot((sx1+sx2)/2-cx ,(sy1+sy2)/2-cy);
			if(MinL>L){
				MinL=L;
				Found=b;
			}
		}
	}
	if(Found!=NULL){
		PureFlexAreaListContainer.RemoveList(Found);
	}
	return Found;
}

PureFlexAreaList	*DotRegulationDotArea::FindDown(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer)
{
	double	MinL=99999999;
	PureFlexAreaList	*Found=NULL;
	int	sx1,sy1,sx2,sy2;
	a->GetXY(sx1,sy1,sx2,sy2);
	for(PureFlexAreaList *b=PureFlexAreaListContainer.GetFirst();b!=NULL;b=b->GetNext()){
		int	cx,cy;
		b->GetCenter(cx,cy);
		if(sx1<=cx && cx<=sx2 && sy2<cy){
			double	L=hypot((sx1+sx2)/2-cx ,(sy1+sy2)/2-cy);
			if(MinL>L){
				MinL=L;
				Found=b;
			}
		}
	}
	if(Found!=NULL){
		PureFlexAreaListContainer.RemoveList(Found);
	}
	return Found;
}

void	DotRegulationDotArea::MakeYPosListStr(DoubleList &List)
{
	double	DDim[2000];
	int		DDimNumb=0;
	//_CrtCheckMemory();

	PureFlexAreaList *f;
	while((f=PureFlexAreaListContainer.GetFirst())!=NULL){
		PureFlexAreaListContainer	PContainer;
		PureFlexAreaListContainer.RemoveList(f);
		PContainer.AppendList(f);

		PureFlexAreaList	*a=f;
		while((a=FindLeft(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}
		a=f;
		while((a=FindRight(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}

		double	AddedCy=0;
		int		N=0;
		for(PureFlexAreaList *t=PContainer.GetFirst();t!=NULL;t=t->GetNext()){
			double	Cx,Cy;
			t->GetCenter(Cx,Cy);
			AddedCy+=Cy;
			N++;
		}
		AddedCy/=N;

		DDim[DDimNumb]=AddedCy;
		DDimNumb++;
	}
//	_CrtCheckMemory();
	QSort(DDim,DDimNumb,sizeof(double),SortFuncDouble);

	for(int i=0;i<DDimNumb;i++){
		List.Add(DDim[i]);
	}
}

PureFlexAreaList	*DotRegulationDotArea::FindLeft(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer)
{
	double	MinL=99999999;
	PureFlexAreaList	*Found=NULL;
	int	sx1,sy1,sx2,sy2;
	a->GetXY(sx1,sy1,sx2,sy2);
	for(PureFlexAreaList *b=PureFlexAreaListContainer.GetFirst();b!=NULL;b=b->GetNext()){
		int	cx,cy;
		b->GetCenter(cx,cy);
		if(sy1<=cy && cy<=sy2 && sx1>cx){
			double	L=hypot((sx1+sx2)/2-cx ,(sy1+sy2)/2-cy);
			if(MinL>L){
				MinL=L;
				Found=b;
			}
		}
	}
	if(Found!=NULL){
		PureFlexAreaListContainer.RemoveList(Found);
	}
	return Found;
}

PureFlexAreaList	*DotRegulationDotArea::FindRight(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer)
{
	double	MinL=99999999;
	PureFlexAreaList	*Found=NULL;
	int	sx1,sy1,sx2,sy2;
	a->GetXY(sx1,sy1,sx2,sy2);
	for(PureFlexAreaList *b=PureFlexAreaListContainer.GetFirst();b!=NULL;b=b->GetNext()){
		int	cx,cy;
		b->GetCenter(cx,cy);
		if(sy1<=cy && cy<=sy2 && sx2<cx){
			double	L=hypot((sx1+sx2)/2-cx ,(sy1+sy2)/2-cy);
			if(MinL>L){
				MinL=L;
				Found=b;
			}
		}
	}
	if(Found!=NULL){
		PureFlexAreaListContainer.RemoveList(Found);
	}
	return Found;
}

class	DLineList
{
public:
	double		AvrX,AvrY;
	DoubleList	DList;

	DLineList(void){	AvrX=AvrY=0;	}
	void	GetCenter(int &x ,int &y){	x=AvrX; y=AvrY;	}
};


int	SortFlexAreaListPointer(const void *a ,const void *b)
{
	PureFlexAreaList **pa=(PureFlexAreaList **)a;
	PureFlexAreaList **pb=(PureFlexAreaList **)b;
	int	Cxa,Cya;
	(*pa)->GetCenter(Cxa,Cya);
	int	Cxb,Cyb;
	(*pb)->GetCenter(Cxb,Cyb);
	return Cxa-Cxb;
}

int	SortDPoint(const void *a ,const void *b)
{
	DLineList **pa=(DLineList **)a;
	DLineList **pb=(DLineList **)b;
	int	Cxa,Cya;
	(*pa)->GetCenter(Cxa,Cya);
	int	Cxb,Cyb;
	(*pb)->GetCenter(Cxb,Cyb);
	return Cxa-Cxb;
}

void	DotRegulationDotArea::MakeBrightnessListStr(QStringListListCSV &List)
{
	ImageBuffer	&Buff=GetMasterBuff();

	DLineList	*DPoint[10000];
	int			DPointNumb=0;

	int	Row=0;
	PureFlexAreaList *f;
	while((f=PureFlexAreaListContainer.GetFirst())!=NULL){
		PureFlexAreaListContainer	PContainer;
		PureFlexAreaListContainer.RemoveList(f);
		PContainer.AppendList(f);

		PureFlexAreaList	*a=f;
		while((a=FindLeft(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}
		a=f;
		while((a=FindRight(a,PureFlexAreaListContainer))!=NULL){
			PContainer.AppendList(a);
		}

		PureFlexAreaList *Dim[10000];
		int	DimNumb=0;
		PureFlexAreaList *t;
		while((t=PContainer.GetFirst())!=NULL){
			PContainer.RemoveList(t);
			Dim[DimNumb]=t;
			DimNumb++;
		}
		QSort(Dim,DimNumb,sizeof(Dim[0]),SortFlexAreaListPointer);
		DLineList	*D=new DLineList();
		double	AddedX=0;
		double	AddedY=0;
		for(int i=0;i<DimNumb;i++){
			D->DList.Add(Dim[i]->GetAverage(Buff,0,0));
			int		Cx,Cy;
			Dim[i]->GetCenter(Cx,Cy);
			AddedY+=Cy;
			AddedX+=Cx;
		}
		DPoint[DPointNumb]=D;
		DPoint[DPointNumb]->AvrX=AddedX/DimNumb;
		DPoint[DPointNumb]->AvrY=AddedY/DimNumb;
		DPointNumb++;
	}
	QSort(DPoint,DPointNumb,sizeof(DPoint[0]),SortDPoint);

	for(int i=0;i<DPointNumb;i++){
		int	C=0;
		for(DoubleClass *d=DPoint[i]->DList.GetFirst();d!=NULL;d=d->GetNext()){
			List.Set(C,i,QString::number(d->GetValue()));
			C++;
		}
	}

}

//==================================================================================

AlgorithmItemRoot		*DotRegulationInLayer::CreateItem(int ItemClassType)
{	
	AlgorithmItemPLI	*a=NULL;
	switch(ItemClassType){
		case 0:	a=new DotRegulationBrightnessItem();
				break;
		case 1:	a=new DotRegulationFocusItem();
				break;
		case 2: a=new DotRegulationDotArea();
				break;
	}
	if(a!=NULL){
		a->SetParent(this);
	}
	return a;
}


void	DotRegulationInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaBrightness	*CmdAddAreaBrightnessVar=dynamic_cast<CmdAddAreaBrightness *>(packet);
	if(CmdAddAreaBrightnessVar!=NULL){
		AlgorithmItemRoot	*L=CreateItem(0);
		L->SetArea(CmdAddAreaBrightnessVar->Area);
		DotRegulationBrightnessItem	*YItem=dynamic_cast<DotRegulationBrightnessItem *>(L);
		AppendItem(L);
		return;
	}
	CmdAddDotArea	*CmdAddDotAreaVar=dynamic_cast<CmdAddDotArea *>(packet);
	if(CmdAddDotAreaVar!=NULL){
		AlgorithmItemRoot	*L=CreateItem(2);
		L->SetArea(CmdAddDotAreaVar->Area);
		DotRegulationDotArea	*YItem=dynamic_cast<DotRegulationDotArea *>(L);
		AppendItem(L);
		return;
	}
	CmdAddAreaFocus	*CmdAddAreaFocusVar=dynamic_cast<CmdAddAreaFocus *>(packet);
	if(CmdAddAreaFocusVar!=NULL){
		AlgorithmItemRoot	*L=CreateItem(1);
		L->SetArea(CmdAddAreaFocusVar->Area);
		DotRegulationFocusItem	*YItem=dynamic_cast<DotRegulationFocusItem *>(L);
		AppendItem(L);
		return;
	}
	CmdReqItemInfoList	*CmdReqItemInfoListVar=dynamic_cast<CmdReqItemInfoList *>(packet);
	if(CmdReqItemInfoListVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationBrightnessItem	*YItem=dynamic_cast<DotRegulationBrightnessItem *>(item);
			if(YItem!=NULL){
				/*
				ItemInfoList	*a=new ItemInfoList();
				YItem->GetXY(a->x1,a->y1,a->x2,a->y2);
				a->ItemID	=YItem->GetID();
				a->AxisID	=YItem->AxisID;
				a->Layer	=GetLayer();
				a->Page		=GetPage();
				CmdReqItemInfoListVar->Infos.AppendList(a);
				*/
			}
		}
		return;
	}
	CmdSetItemInfo	*CmdSetItemInfoVar=dynamic_cast<CmdSetItemInfo *>(packet);
	if(CmdSetItemInfoVar!=NULL){
		AlgorithmItemRoot *item=SearchIDItem(CmdSetItemInfoVar->ItemID);
		if(item!=NULL){
			DotRegulationBrightnessItem	*YItem=dynamic_cast<DotRegulationBrightnessItem *>(item);
			if(YItem!=NULL){
			}
		}
		return;
	}
	CmdReqItemResult	*CmdReqItemResultVar=dynamic_cast<CmdReqItemResult *>(packet);
	if(CmdReqItemResultVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationBrightnessItem	*YItem=dynamic_cast<DotRegulationBrightnessItem *>(item);
			if(YItem!=NULL){
			}
		}
		return;
	}
	GUICmdReqPickup	*GUICmdReqPickupVar=dynamic_cast<GUICmdReqPickup *>(packet);
	if(GUICmdReqPickupVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationDotArea	*YItem=dynamic_cast<DotRegulationDotArea *>(item);
			if(YItem!=NULL){
				YItem->Pickup(GUICmdReqPickupVar->Threshold);
			}
		}
		return;
	}
	GUICmdAckXPosList	*GUICmdAckXPosListVar=dynamic_cast<GUICmdAckXPosList *>(packet);
	if(GUICmdAckXPosListVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationDotArea	*YItem=dynamic_cast<DotRegulationDotArea *>(item);
			if(YItem!=NULL){
				YItem->MakeXPosListStr(GUICmdAckXPosListVar->List);
			}
		}
		return;
	}
	GUICmdAckYPosList	*GUICmdAckYPosListVar=dynamic_cast<GUICmdAckYPosList *>(packet);
	if(GUICmdAckYPosListVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationDotArea	*YItem=dynamic_cast<DotRegulationDotArea *>(item);
			if(YItem!=NULL){
				YItem->MakeYPosListStr(GUICmdAckYPosListVar->List);
			}
		}
		return;
	}
	GUICmdAckBrightnessList	*GUICmdAckBrightnessListVar=dynamic_cast<GUICmdAckBrightnessList *>(packet);
	if(GUICmdAckBrightnessListVar!=NULL){
		for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
			DotRegulationDotArea	*YItem=dynamic_cast<DotRegulationDotArea *>(item);
			if(YItem!=NULL){
				YItem->MakeBrightnessListStr(GUICmdAckBrightnessListVar->List);
			}
		}
		return;

	}
}

void	DotRegulationInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAddAreaBrightness	*CmdAddAreaBrightnessVar=dynamic_cast<CmdAddAreaBrightness *>(packet);
	if(CmdAddAreaBrightnessVar!=NULL){
		if(CmdAddAreaBrightnessVar->Layers.IsEmpty()==true){
			for(int layer=0;layer<GetLayerNumb();layer++){
				GetLayerData(layer)->TransmitDirectly(CmdAddAreaBrightnessVar);
			}
		}
		else{
			for(IntClass *c=CmdAddAreaBrightnessVar->Layers.GetFirst();c!=NULL;c=c->GetNext()){
				GetLayerData(c->GetValue())->TransmitDirectly(CmdAddAreaBrightnessVar);
			}
		}
		return;
	}
	CmdAddAreaFocus	*CmdAddAreaFocusVar=dynamic_cast<CmdAddAreaFocus *>(packet);
	if(CmdAddAreaFocusVar!=NULL){
		if(CmdAddAreaFocusVar->Layers.IsEmpty()==true){
			for(int layer=0;layer<GetLayerNumb();layer++){
				GetLayerData(layer)->TransmitDirectly(CmdAddAreaFocusVar);
			}
		}
		else{
			for(IntClass *c=CmdAddAreaFocusVar->Layers.GetFirst();c!=NULL;c=c->GetNext()){
				GetLayerData(c->GetValue())->TransmitDirectly(CmdAddAreaFocusVar);
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

//================================================================

DotRegulationBase::DotRegulationBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorRegulation		=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorRegulation	=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;

	SetParam(&ColorRegulation	,/**/"Color" ,/**/"ColorRegulation"		,"Color for Regulation area");
	SetParam(&ColorSelected		,/**/"Color" ,/**/"ColorSelected"			,"Color for Selected Piece");
	SetParam(&ColorActive		,/**/"Color" ,/**/"ColorActive"			,"Color for Active Piece");
	SetParam(&TransparentLevel	,/**/"Color" ,/**/"TransparentLevel"		,"Color for Transparent display level");
	SetParam(&NegColorRegulation,/**/"Color" ,/**/"NegColorRegulation"		,"Color for Negative Regulation area");
	SetParam(&NegColorSelected	,/**/"Color" ,/**/"NegColorSelected"		,"Color for Negative selected Regulation");
}

AlgorithmDrawAttr	*DotRegulationBase::CreateDrawAttr(void)
{
	return new DotRegulationDrawAttr();
}


