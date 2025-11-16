#include "XImageChecker.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XPointer.h"
#include "XBitImageProcessor.h"
#include "XImageProcess.h"
#include "XFocus.h"
#include "XFFT1d.h"
#define	_USE_MATH_DEFINES
#include "math.h"
#include "XCSV.h"
#include "XInterpolation.h"
#include "swap.h"

ImageCheckerThreshold::ImageCheckerThreshold(ImageCheckerItem *parent)
:AlgorithmThreshold(parent)
{
	PointType=_ShiftXYMatching;
	ImageCheckerRegMode=ImageCheckerThreshold::_ImageCheckerRegCalcCamX;
}
void	ImageCheckerThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ImageCheckerThreshold *s=(const ImageCheckerThreshold *)&src;
	PointType			=s->PointType;
	ImageCheckerRegMode	=s->ImageCheckerRegMode;
}
bool	ImageCheckerThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ImageCheckerThreshold *s=(const ImageCheckerThreshold *)&src;
	if(PointType			!=s->PointType			)	return false;
	if(ImageCheckerRegMode	!=s->ImageCheckerRegMode	)	return false;
	return true;
}
bool	ImageCheckerThreshold::Save(QIODevice *f)
{
	BYTE	D=(BYTE)PointType;
	if(::Save(f,D)==false){
		return false;
	}

	D=(BYTE)ImageCheckerRegMode;
	if(::Save(f,D)==false){
		return false;
	}

	return true;
}
bool	ImageCheckerThreshold::Load(QIODevice *f)
{
	BYTE	D;

	if(::Load(f,D)==false){
		return false;
	}
	PointType=(_PointType)D;

	if(::Load(f,D)==false){
		return false;
	}
	ImageCheckerRegMode=(__ImageCheckerRegMode)D;

	return true;
}


ImageCheckerItem::ImageCheckerItem(void)
{
	DotMatrix=NULL;
	MaxXCount=0;
	MaxYCount=0;

	CenterPointForSlideX=0;	//最初に設定される
	CenterPointForSlideY=0;	//最初に設定される
	memset(FFTList,0,sizeof(FFTList));
	FFTListCount=0;
	MainPosX=MainPosY=0;
}

ImageCheckerItem::~ImageCheckerItem(void)
{
	if(DotMatrix!=NULL){
		for(int y=0;y<MaxYCount;y++){
			delete	[]DotMatrix[y];
		}
		delete	[]DotMatrix;
		DotMatrix=NULL;
	}
}

bool    ImageCheckerItem::Save(QIODevice *f)
{
	if(AlgorithmItemPLI::Save(f)==false){
		return false;
	}
	if(::Save(f,CenterPointForSlideX)==false){
		return false;
	}
	if(::Save(f,CenterPointForSlideY)==false){
		return false;
	}
	if(::Save(f,MainPosX)==false){
		return false;
	}
	if(::Save(f,MainPosY)==false){
		return false;
	}
	return true;
}
bool    ImageCheckerItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(f,LBase)==false){
		return false;
	}
	if(::Load(f,CenterPointForSlideX)==false){
		return false;
	}
	if(::Load(f,CenterPointForSlideY)==false){
		return false;
	}
	if(::Load(f,MainPosX)==false){
		return false;
	}
	if(::Load(f,MainPosY)==false){
		return false;
	}
	return true;
}

void	ImageCheckerItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ImageCheckerInLayer	*ALayer=dynamic_cast<ImageCheckerInLayer *>(GetParentInLayer());
	ImageCheckerDrawAttr	*a=dynamic_cast<ImageCheckerDrawAttr *>(Attr);
	ImageCheckerBase	*ABase=(ImageCheckerBase *)GetParentBase();
	if(a!=NULL && ALayer!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyImageChecker" ,/**/"");
		CmdImageCheckerDrawMode	Da(GetLayersBase());
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Da);
		}
		bool	DrawOn=false;
		switch(Da.Mode){
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamX:
				if(ALayer->RegCalcCamX.LeftPoint==this){
					DrawOn=true;
				}
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamY:
				if(ALayer->RegCalcCamY.TopPoint==this){
					DrawOn=true;
				}
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamZ:
				if(ALayer->RegCalcCamZ.CenterPoint==this){
					DrawOn=true;
				}
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamXTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamYTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamRot:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageFlat:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVerocity:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVConst:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole:
				if(ALayer->RegCalcLightWhole.WholePoint==this){
					DrawOn=true;
				}
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightLeftRight:
				break;
		}
		if(DrawOn==true || ABase->ModeDotPattern==true){
			ImageCheckerDrawAttr A	=*((ImageCheckerDrawAttr *)Attr);
			A.NormalColor			=ABase->ColorNormal;
			A.NormalColor.setAlpha(ABase->TransparentLevel);
			A.SelectedColor			=ABase->NegColorSelected;
			AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
		}
	}
	if(DotMatrix!=NULL){
		for(int y=0;y<MaxYCount;y++){
			for(int x=0;x<MaxXCount;x++){
				if(DotMatrix[y][x]!=NULL){
					DotMatrix[y][x]->DrawAlpha(0,0,&pnt,qRgba(255,128,0,196)
									,ZoomRate ,movx ,movy);
				}
			}
		}
	}
}

class	FlexArea1Line
{
public:
	FlexArea	**PadLines;
	int	Count;
	int		y1,y2;
	int		Index;

	FlexArea1Line(int Count);
	~FlexArea1Line(void);

};

FlexArea1Line::FlexArea1Line(int _Count)
{
	PadLines=new FlexArea*[_Count];
	Count=_Count;
	y1=y2	=0;
	Index	=-1;
}
FlexArea1Line::~FlexArea1Line(void)
{
	delete	[]PadLines;
}

static	int	DotsDimFunc(const void *a, const void *b)
{
	if(*((int64 *)a)>*((int64 *)b))
		return 1;
	if(*((int64 *)a)<*((int64 *)b))
		return -1;
	return 0;
}
void	ImageCheckerItem::MakeDotMatrix(void)
{
	const ImageCheckerThreshold	*RThr=GetThresholdR();
	if(RThr->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcResolution
	|| RThr->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcMatching){
		return;
	}
	ImageCheckerBase	*ABase=(ImageCheckerBase *)GetParentBase();
	int	XByte	=(GetDotPerLine()+7)/8;
	int	YLen	=GetMaxLines();
	BYTE	**BinMap=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(BinMap,0,XByte,YLen);

	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	int	BlockSize=ABase->BlocksizeOfAutoPickPadUp;
	int	WNumb=W/BlockSize;
	int	HNumb=H/BlockSize;

	int	WBlockSize=(W+WNumb-1)/WNumb;
	int	HBlockSize=(H+HNumb-1)/HNumb;

	int	X1=GetArea().GetMinX();
	int	Y1=GetArea().GetMinY();
	BYTE	**TmpMap=MakeMatrixBuff(XByte,YLen);

	for(int yn=0;yn<HNumb;yn++){
		for(int xn=0;xn<WNumb;xn++){
			FlexArea	A=GetArea();
			A.ClipArea(X1+xn*WBlockSize ,Y1+yn*HBlockSize
					  ,X1+(xn+1)*WBlockSize ,Y1+(yn+1)*HBlockSize);
			int BrList[256];
			memset(BrList,0,sizeof(BrList));
			A.MakeBrightList(BrList ,GetDotPerLine(),GetMaxLines(),GetMasterBuff());

			int	L1=GetPeak(BrList);
			int	L2=GetSecondPeak(BrList,L1);
			int	Thresh=(L1+L2)/2;

			PickupBitmapWithTmp(A,0,0
					,BinMap, XByte ,YLen
					,GetMasterBuff()
					,Thresh,256
					,0,0
					,TmpMap);
		}
	}

	GetLayersBase()->ThinAreaN(BinMap	,TmpMap ,XByte,YLen,ABase->NoiseDot);
	GetLayersBase()->FatAreaN (BinMap	,TmpMap ,XByte,YLen,ABase->NoiseDot*2);
	GetLayersBase()->ThinAreaN(BinMap	,TmpMap ,XByte,YLen,ABase->NoiseDot);

	DeleteMatrixBuff(TmpMap,YLen);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BinMap, XByte ,GetDotPerLine(),YLen ,FPack);
	DeleteMatrixBuff(BinMap,YLen);

	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
		if(p->GetPatternByte()<100){
			PureFlexAreaList	*NextP=p->GetNext();
			FPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}
	int	k=0;
	int64	*DotsDim=new int64[FPack.GetNumber()];
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		DotsDim[k]=p->GetPatternByte();
		k++;
	}
	QSort(DotsDim,k,sizeof(DotsDim[0]),DotsDimFunc);
	int64	MidDots=DotsDim[k/2];
	int64	LDots=MidDots*0.8;
	int64	HDots=MidDots*1.2;
	delete	[]DotsDim;
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
		int64	Dots=p->GetPatternByte();
		if(Dots<LDots || HDots<Dots){
			PureFlexAreaList	*NextP=p->GetNext();
			FPack.RemoveList(p);
			delete	p;
			p=NextP;
		}
		else{
			p=p->GetNext();
		}
	}


	FlexArea1Line	*FY[10000];
	int	YCount=0;
	while(FPack.GetFirst()!=NULL){
		PureFlexAreaList *P1=FPack.GetFirst();
		FPack.RemoveList(P1);
		FlexArea	*PadLines[10000];
		PadLines[0]=P1;
		int	XCount=1;
		int	x1,y1,x2,y2;
		P1->GetXY(x1,y1,x2,y2);

		for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;){
			int	cx,cy;
			p->GetCenter(cx,cy);
			if(y1<=cy && cy<y2){
				PureFlexAreaList	*NextP=p->GetNext();
				FPack.RemoveList(p);
				PadLines[XCount]=p;
				XCount++;
				p=NextP;
			}
			else{
				p=p->GetNext();
			}
		}
XNext:;
		for(int x=0;x<XCount-1;x++){
			int	cx1,cy1;
			int	cx2,cy2;
			PadLines[x	]->GetCenter(cx1,cy1);
			PadLines[x+1]->GetCenter(cx2,cy2);
			if(cx1>cx2){
				FlexArea	*Tmp=PadLines[x	];
				PadLines[x	]=PadLines[x+1];
				PadLines[x+1]=Tmp;
				goto	XNext;
			}
		}


		FlexArea1Line	*F=new FlexArea1Line(XCount);
		for(int i=0;i<XCount;i++){
			F->PadLines[i]=PadLines[i];
		}
		F->y1=y1;
		F->y2=y2;
		FY[YCount]=F;
		YCount++;
	}

YNext:;
	for(int y=0;y<YCount-1;y++){
		if(FY[y]->y1>FY[y+1]->y1){
			FlexArea1Line	*Tmp=FY[y];
			FY[y]=FY[y+1];
			FY[y+1]=Tmp;
			goto	YNext;
		}
	}

	MaxXCount=0;
	for(int y=0;y<YCount;y++){
		if(MaxXCount<FY[y]->Count){
			MaxXCount=FY[y]->Count;
		}
	}
	MaxXCount++;
	MaxYCount=YCount;
	DotMatrix=new FlexArea **[MaxYCount];
	for(int y=0;y<MaxYCount;y++){
		DotMatrix[y]=new FlexArea *[MaxXCount];
		for(int x=0;x<MaxXCount;x++){
			DotMatrix[y][x]=NULL;
		}
	}
	for(int y=0;y<YCount;y++){
		FY[y]->Index=0;
	}
	for(int CurrentX=0;CurrentX<MaxXCount;CurrentX++){
		int	MinX1=99999999;
		int	MinX2=99999999;
		for(int y=0;y<YCount;y++){
			if(FY[y]->Index>=FY[y]->Count)
				continue;
			int	x1,y1,x2,y2;
			FY[y]->PadLines[FY[y]->Index]->GetXY(x1,y1,x2,y2);
			if(MinX1>x1 && MinX2>x2){
				MinX1=x1;
				MinX2=x2;
			}
		}
		for(int y=0;y<YCount;y++){
			if(FY[y]->Index>=FY[y]->Count)
				continue;
			int	cx,cy;
			FY[y]->PadLines[FY[y]->Index]->GetCenter(cx,cy);
			if(MinX1<=cx && cx<MinX2){
				DotMatrix[y][CurrentX]=FY[y]->PadLines[FY[y]->Index];
				FY[y]->Index++;
			}
		}
	}

}

void	ImageCheckerItem::SetCenterPointForSlide(void)
{
	double	Cx,Cy;
	GetCenter(Cx,Cy);
	double	MinH=99999999;
	int	MinHx=0;
	int	MinHy=0;
	for(int y=0;y<MaxYCount;y++){
		for(int x=0;x<MaxXCount;x++){
			double	cx1,cy1;
			if(DotMatrix[y][x]!=NULL){
				DotMatrix[y][x]->GetCenter(cx1,cy1);
				double	H=hypot(Cx-cx1,Cy-cy1);
				if(H<MinH){
					MinH=H;
					MinHx=x;
					MinHy=y;
				}
			}
		}
	}
	DotMatrix[MinHy][MinHx]->GetCenter(CenterPointForSlideX,CenterPointForSlideY);
}


int	ImageCheckerItem::GetPeak(int *BrList)
{
	int	CMax=0;
	int	Index=0;
	for(int i=0;i<256;i++){
		if(CMax<BrList[i]){
			CMax=BrList[i];
			Index=i;
		}
	}
	return Index;
}
int	ImageCheckerItem::GetSecondPeak(int *BrList,int Peak)
{
	int	TmpTable[256];
	memset(TmpTable,0,sizeof(TmpTable));
	for(int i=0;i<256-3;i++){
		TmpTable[i]=(BrList[i]+BrList[i+1]+BrList[i+2])/3;
	}
	BrList=TmpTable;

	int	k1;
	int	CMax1=0;
	for(k1=Peak+10;k1<256-4;k1++){
		if((BrList[k1]+BrList[k1+1])<(BrList[k1+2]+BrList[k1+3]))
			break;
	}
	if(k1<252){
		for(int i=k1;i<256;i++){
			if(CMax1<BrList[i]){
				CMax1=BrList[i];
				k1=i;
			}
		}
	}
	int	k2;
	int	CMax2=0;
	for(k2=Peak-10;k2>=4;k2--){
		if((BrList[k2]+BrList[k2-1])<(BrList[k2-2]+BrList[k2-3]))
			break;
	}
	if(k2>4){
		for(int i=k2;i>0;i--){
			if(CMax2<BrList[i]){
				CMax2=BrList[i];
				k2=i;
			}
		}
	}
	if(CMax1>CMax2){
		return k1;
	}
	else if(CMax1<CMax2){
		return k2;
	}
	return -1;
}

void	ImageCheckerItem::MakeFFTList(void)
{
	ImageCheckerBase	*PBase=(ImageCheckerBase *)GetParentBase();
		
	FFTListCount=hypot(GetArea().GetWidth(),GetArea().GetHeight());
	int	BandWidth=3;
	double	sita=PBase->LineAngle*2.0*M_PI/360;
	int	Cx,Cy;
	GetCenter(Cx,Cy);
	
	double	CosS=cos(sita);
	double	SinS=sin(sita);
	int	StartPosX=Cx-FFTListCount/2*CosS;
	int	StartPosY=Cy-FFTListCount/2*SinS;
	int	L2=FFTListCount/2;

	for(int i=0;i<sizeof(FFTList)/sizeof(FFTList[0]);i++){
		FFTList[i]=0;
	}
	int	LoopCount=FFTListCount-2*BandWidth+1;
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int u=0;u<LoopCount;u++){
			int	t=u+BandWidth;
		//for(int t=BandWidth;t<L-BandWidth;t++){
			double	*TmpData=new double[10000];
			//double	*XXTData=new double[10000];
			double	XXTData[10000];
			for(int i=0;i<=FFTListCount;i++){
				TmpData[i]=0;
			}

			FFTClass	FFTData;

			for(int h=0;h<L2;h++){
				double	SumD=0;
				int	iCount=0;
				for(int i=-BandWidth;i<=BandWidth;i++){
					int	Hx=(t+i)*CosS+StartPosX;
					int	Hy=(t+i)*SinS+StartPosY;
					int	x= h*SinS+Hx;
					int	y=-h*CosS+Hy;
					if(GetArea().IsInclude(x,y)==true){
						int	D=GetMasterBuff().GetPixel(x,y);
						SumD+=D;
						iCount++;
					}
				}
				if(iCount!=0){
					TmpData[h+L2]=SumD/iCount;
				}
				SumD=0;
				iCount=0;
				for(int i=-BandWidth;i<=BandWidth;i++){
					int	Hx=(t+i)*CosS+StartPosX;
					int	Hy=(t+i)*SinS+StartPosY;
					int	x=-h*SinS+Hx;
					int	y= h*CosS+Hy;
					if(GetArea().IsInclude(x,y)==true){
						int	D=GetMasterBuff().GetPixel(x,y);
						SumD+=D;
						iCount++;
					}
				}
				if(iCount!=0){
					TmpData[-h+L2]=SumD/iCount;
				}
			}
			int	N=FFTListCount+1;
			int	k1,k2;
			for(k1=0;k1<N;k1++){
				if(TmpData[k1]!=0.0){
					break;
				}
			}
			for(k2=N-1;k2>=0;k2--){
				if(TmpData[k2]!=0.0){
					break;
				}
			}
			N=k2-k1+1;
			if(N>0){
				/*
				double	*dp=&TmpData[k1];
				for(int j=0;j<N/4;j++){
					dp[j]=dp[j]*((double)j)/((double)(N/4));
				}
				for(int j=3*N/4;j<N;j++){
					int	w=N-j;
					dp[j]=dp[j]*((double)w)/((double)(N/4));
				}
				*/
				FFTData.fftPower(N,&TmpData[k1],XXTData);
				double	MaxFFT=0;
				int		MaxAPos=0;
				int	E=N/(PBase->LineFreqMicron/PBase->DotResolutionMicron);
				for(int a=max(0,(int)(E*0.8));a<E*1.2;a++){
					if(MaxFFT<XXTData[a]){
						MaxFFT=XXTData[a];
						MaxAPos=a;
					}
				}
				double	SumFFT=0;
				int	Le=N/200;
				if(MaxAPos<E){
					for(int k=max(0,MaxAPos-Le);k<=E+Le;k++){
						SumFFT+=XXTData[k];
					}
				}
				else{
					for(int k=max(0,E-Le);k<=MaxAPos+Le;k++){
						SumFFT+=XXTData[k];
					}
				}
				FFTList[t]=SumFFT/1000.0;
			}
			delete	[]TmpData;
			//delete	[]XXTData;
		}
	}
}

void	ImageCheckerItem::MatchingPosInLine(int &X ,int &Y)
{
	int	XByte=(GetDotPerLine()+7)/8;

	int	YLen=GetMaxLines();
	BYTE	**BmpMap=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpMap2=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear(BmpMap ,0,XByte,YLen);

	PickupBitmapWithTmp(GetArea(),0,0
					,BmpMap, XByte ,YLen
					,GetMasterBuff()
					,100 ,256
					,0,0
					,BmpMap2);

	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpMap,XByte ,XByte*8,YLen ,FPack);
	int	cx,cy;
	GetArea().GetCenter(cx,cy);

	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsInclude(cx,cy)==true){
			a->GetCenter(X,Y);
			break;
		}
	}
	DeleteMatrixBuff(BmpMap,YLen);
	DeleteMatrixBuff(BmpMap2,YLen);
}


//--------------------------------------------------------------------------------------

bool	ImageCheckerRegCalcBase::Save(QIODevice *f)
{
	return true;
}
bool	ImageCheckerRegCalcBase::Load(QIODevice *f)
{
	return true;
}

bool	ImageCheckerRegCalcBase::IsMasterMode(void)
{
	ImageCheckerBase	*PBase=dynamic_cast<ImageCheckerBase *>(LayerPoint->GetParentBase());
	if(PBase!=NULL){
		return PBase->InspectMaster;
	}
	return true;
}

//--------------------------------------------------------------------------------------
ImageCheckerRegCalcCamX::ImageCheckerRegCalcCamX(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LeftPoint		=NULL;	
	StandardValue	=0;
	LLimit			=0;
	HLimit			=0;
}

bool	ImageCheckerRegCalcCamX::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcCamX::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}

	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id=LeftPoint->GetID();
		if(::Save(f,id)==false){
			return false;
		}
	}
	if(::Save(f,StandardValue)==false){
		return false;
	}
	if(::Save(f,LLimit)==false){
		return false;
	}
	if(::Save(f,HLimit)==false){
		return false;
	}

	return true;
}
bool	ImageCheckerRegCalcCamX::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id;
		if(::Load(f,id)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	if(::Load(f,StandardValue)==false){
		return false;
	}
	if(::Load(f,LLimit)==false){
		return false;
	}
	if(::Load(f,HLimit)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamX::DeletedItem(AlgorithmItemPLI *Item)
{
	if(LeftPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	return false;
}


//--------------------------------------------------------------------------------------
ImageCheckerRegCalcCamY::ImageCheckerRegCalcCamY(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	StandardValue	=0;
	LLimit			=0;
	HLimit			=0;
	TopPoint=NULL;	
}

bool	ImageCheckerRegCalcCamY::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcCamY::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	TopPointExist=(TopPoint!=NULL)?true:false;
	if(::Save(f,TopPointExist)==false){
		return false;
	}
	if(TopPoint!=NULL){
		int32	id=TopPoint->GetID();
		if(::Save(f,id)==false){
			return false;
		}
	}
	if(::Save(f,StandardValue)==false){
		return false;
	}
	if(::Save(f,LLimit)==false){
		return false;
	}
	if(::Save(f,HLimit)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcCamY::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	TopPointExist;
	if(::Load(f,TopPointExist)==false){
		return false;
	}
	if(TopPointExist==true){
		int32	id;
		if(::Load(f,id)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id);
		if(L==NULL){
			return false;
		}
		TopPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(TopPoint==NULL){
			return false;
		}
	}
	if(::Load(f,StandardValue)==false){
		return false;
	}
	if(::Load(f,LLimit)==false){
		return false;
	}
	if(::Load(f,HLimit)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamY::DeletedItem(AlgorithmItemPLI *Item)
{
	if(TopPoint==Item){
		TopPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcCamZ::ImageCheckerRegCalcCamZ(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	StandardValue	=0;
	LLimit			=0;
	HLimit			=0;
	CenterPoint=NULL;
}

static	int	FocusDimFunc(const void *a,const void *b)
{
	if(*((double *)a)>*((double *)b))
		return 1;
	if(*((double *)a)<*((double *)b))
		return -1;
	return 0;
}


bool	ImageCheckerRegCalcCamZ::Execute(int ShiftX ,int ShiftY)
{
	ImageCheckerItem	*Item=NULL;
	AlgorithmItemPLI *a;
	for(a=LayerPoint->GetFirstData();a!=NULL;a=a->GetNext()){
		Item=dynamic_cast<ImageCheckerItem *>(a);
		if(Item!=NULL && Item->GetThresholdR(LayerPoint->GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcResolution){
			break;
		}
	}
	ImageCheckerBase	*PBase=(ImageCheckerBase *)LayerPoint->GetParentBase();
	if(Item==NULL || a==NULL){
		return false;
	}

	if(PBase->ModeDotPattern==false){
		double Avr ,Var;
		if(CenterPoint!=NULL){
			 LayerPoint->MakeAvrVar(CenterPoint->GetArea()
									,((IsMasterMode()==true)?CenterPoint->GetMasterBuff():CenterPoint->GetTargetBuff())
				,Avr ,Var ,100);
			if(Avr>0.1){
				Result=sqrt(Var)/Avr*100;
				if(LLimit<=Result && Result<=HLimit){
					Ok=true;
				}
				else{
					Ok=false;
				}
			}
		}
	}
	else if(Item!=NULL){
		QStringListListCSV	TextCSV;
		for(int i=0;i<Item->FFTListCount;i++){
			TextCSV.Set(0, i,QString::number(Item->FFTList[i],'f',3));
		}
		TextCSV.SaveFromCSVFile("TextCSVZ.csv");
	
		//ピークを計算
		double	MaxFFTList=0;
		for(int i=0;i<Item->FFTListCount;i++){
			if(MaxFFTList<Item->FFTList[i]){
				MaxFFTList=Item->FFTList[i];
			}
		}
		double	MinFFTList=MaxFFTList*0.1;
		double	SumFFTList=0;
		double	MulFFTList=0;
		for(int i=0;i<Item->FFTListCount;i++){
			if(MinFFTList<Item->FFTList[i]){
				SumFFTList+=Item->FFTList[i];
				MulFFTList+=Item->FFTList[i]*i;
			}
		}

		double	sita=PBase->LineAngle*2.0*M_PI/360;
		int	Cx,Cy;
		Item->GetCenter(Cx,Cy);
	
		double	CosS=cos(sita);
		double	SinS=sin(sita);

		double	CenterPos=MulFFTList/SumFFTList;
		double	CenterPosX=(CenterPos-Item->FFTListCount/2.0)*CosS+Cx-ShiftX;
		double	CenterPosY=(CenterPos-Item->FFTListCount/2.0)*SinS+Cy-ShiftY;

		Result=CenterPosY*sin(PBase->SlopAngle*2*M_PI/360)*PBase->DotResolutionMicron;
		Result2=CenterPosY;
		if(LLimit<=Result && Result<=HLimit){
			Ok=true;
		}
		else{
			Ok=false;
		}
	}
		
	return true;
}
bool	ImageCheckerRegCalcCamZ::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	CenterPointExist=(CenterPoint!=NULL)?true:false;
	if(::Save(f,CenterPointExist)==false){
		return false;
	}
	if(CenterPoint!=NULL){
		int32	id=CenterPoint->GetID();
		if(::Save(f,id)==false){
			return false;
		}
	}
	if(::Save(f,StandardValue)==false){
		return false;
	}
	if(::Save(f,LLimit)==false){
		return false;
	}
	if(::Save(f,HLimit)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcCamZ::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	CenterPointExist;
	if(::Load(f,CenterPointExist)==false){
		return false;
	}
	if(CenterPointExist==true){
		int32	id;
		if(::Load(f,id)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id);
		if(L==NULL){
			return false;
		}
		CenterPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(CenterPoint==NULL){
			return false;
		}
	}
	if(::Load(f,StandardValue)==false){
		return false;
	}
	if(::Load(f,LLimit)==false){
		return false;
	}
	if(::Load(f,HLimit)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamZ::DeletedItem(AlgorithmItemPLI *Item)
{
	if(CenterPoint==Item){
		CenterPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcCamXTilt::ImageCheckerRegCalcCamXTilt(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot	=0;
	LeftPoint=NULL;	
	RightPoint=NULL;
}

bool	ImageCheckerRegCalcCamXTilt::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcCamXTilt::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id1=LeftPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	RightPointExist=(RightPoint!=NULL)?true:false;
	if(::Save(f,RightPointExist)==false){
		return false;
	}
	if(RightPoint!=NULL){
		int32	id2=RightPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcCamXTilt::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	bool	RightPointExist;
	if(::Load(f,RightPointExist)==false){
		return false;
	}
	if(RightPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		RightPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(RightPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamXTilt::DeletedItem(AlgorithmItemPLI *Item)
{
	if(RightPoint==Item){
		RightPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------

ImageCheckerRegCalcCamYTilt::ImageCheckerRegCalcCamYTilt(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	LeftPoint=NULL;	
	RightPoint=NULL;	
	CenterPoint=NULL;	
}

bool	ImageCheckerRegCalcCamYTilt::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcCamYTilt::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id1=LeftPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	RightPointExist=(RightPoint!=NULL)?true:false;
	if(::Save(f,RightPointExist)==false){
		return false;
	}
	if(RightPoint!=NULL){
		int32	id2=RightPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	bool	CenterPointExist=(CenterPoint!=NULL)?true:false;
	if(::Save(f,CenterPointExist)==false){
		return false;
	}
	if(CenterPoint!=NULL){
		int32	id3=CenterPoint->GetID();
		if(::Save(f,id3)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcCamYTilt::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	bool	RightPointExist;
	if(::Load(f,RightPointExist)==false){
		return false;
	}
	if(RightPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		RightPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(RightPoint==NULL){
			return false;
		}
	}
	bool	CenterPointExist;
	if(::Load(f,CenterPointExist)==false){
		return false;
	}
	if(CenterPointExist==true){
		int32	id3;
		if(::Load(f,id3)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id3);
		if(L==NULL){
			return false;
		}
		CenterPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(CenterPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamYTilt::DeletedItem(AlgorithmItemPLI *Item)
{
	if(LeftPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	if(RightPoint==Item){
		RightPoint=NULL;
		return true;
	}
	if(CenterPoint==Item){
		CenterPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcCamRot::ImageCheckerRegCalcCamRot(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	LeftPoint=NULL;	
	RightPoint=NULL;	
}

bool	ImageCheckerRegCalcCamRot::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcCamRot::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id1=LeftPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	RightPointExist=(RightPoint!=NULL)?true:false;
	if(::Save(f,RightPointExist)==false){
		return false;
	}
	if(RightPoint!=NULL){
		int32	id2=RightPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcCamRot::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	bool	RightPointExist;
	if(::Load(f,RightPointExist)==false){
		return false;
	}
	if(RightPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		RightPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(RightPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcCamRot::DeletedItem(AlgorithmItemPLI *Item)
{
	if(RightPoint==Item){
		RightPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcStageFlat::ImageCheckerRegCalcStageFlat(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	TopPoint=NULL;
	LeftPoint=NULL;
	RightPoint=NULL;
	BottomPoint=NULL;
}

bool	ImageCheckerRegCalcStageFlat::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcStageFlat::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id1=LeftPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	RightPointExist=(RightPoint!=NULL)?true:false;
	if(::Save(f,RightPointExist)==false){
		return false;
	}
	if(RightPoint!=NULL){
		int32	id2=RightPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	bool	TopPointExist=(TopPoint!=NULL)?true:false;
	if(::Save(f,TopPointExist)==false){
		return false;
	}
	if(TopPoint!=NULL){
		int32	id3=TopPoint->GetID();
		if(::Save(f,id3)==false){
			return false;
		}
	}
	bool	BottomPointExist=(BottomPoint!=NULL)?true:false;
	if(::Save(f,BottomPointExist)==false){
		return false;
	}
	if(BottomPoint!=NULL){
		int32	id4=BottomPoint->GetID();
		if(::Save(f,id4)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcStageFlat::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	bool	RightPointExist;
	if(::Load(f,RightPointExist)==false){
		return false;
	}
	if(RightPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		RightPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(RightPoint==NULL){
			return false;
		}
	}
	bool	TopPointExist;
	if(::Load(f,TopPointExist)==false){
		return false;
	}
	if(TopPointExist==true){
		int32	id3;
		if(::Load(f,id3)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id3);
		if(L==NULL){
			return false;
		}
		TopPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(TopPoint==NULL){
			return false;
		}
	}
	bool	BottomPointExist;
	if(::Load(f,BottomPointExist)==false){
		return false;
	}
	if(BottomPointExist==true){
		int32	id4;
		if(::Load(f,id4)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id4);
		if(L==NULL){
			return false;
		}
		BottomPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(BottomPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcStageFlat::DeletedItem(AlgorithmItemPLI *Item)
{
	if(TopPoint==Item){
		TopPoint=NULL;
		return true;
	}
	if(LeftPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	if(RightPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	if(BottomPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcStageVerocity::ImageCheckerRegCalcStageVerocity(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	TopPoint=NULL;	
	BottomPoint=NULL;	
}

bool	ImageCheckerRegCalcStageVerocity::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcStageVerocity::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	TopPointExist=(TopPoint!=NULL)?true:false;
	if(::Save(f,TopPointExist)==false){
		return false;
	}
	if(TopPoint!=NULL){
		int32	id1=TopPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	BottomPointExist=(BottomPoint!=NULL)?true:false;
	if(::Save(f,BottomPointExist)==false){
		return false;
	}
	if(BottomPoint!=NULL){
		int32	id2=BottomPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcStageVerocity::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	TopPointExist;
	if(::Load(f,TopPointExist)==false){
		return false;
	}
	if(TopPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		TopPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(TopPoint==NULL){
			return false;
		}
	}
	bool	BottomPointExist;
	if(::Load(f,BottomPointExist)==false){
		return false;
	}
	if(BottomPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		BottomPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(BottomPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcStageVerocity::DeletedItem(AlgorithmItemPLI *Item)
{
	if(TopPoint==Item){
		TopPoint=NULL;
		return true;
	}
	if(BottomPoint==Item){
		BottomPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcStageVConst::ImageCheckerRegCalcStageVConst(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	TopToBottomPoint=NULL;	
}

bool	ImageCheckerRegCalcStageVConst::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcStageVConst::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	TopToBottomPointExist=(TopToBottomPoint!=NULL)?true:false;
	if(::Save(f,TopToBottomPointExist)==false){
		return false;
	}
	if(TopToBottomPoint!=NULL){
		int32	id1=TopToBottomPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcStageVConst::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	TopToBottomPointExist;
	if(::Load(f,TopToBottomPointExist)==false){
		return false;
	}
	if(TopToBottomPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		TopToBottomPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(TopToBottomPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcStageVConst::DeletedItem(AlgorithmItemPLI *Item)
{
	if(TopToBottomPoint==Item){
		TopToBottomPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcLightWhole::ImageCheckerRegCalcLightWhole(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	StandardValue	=0;
	LLimit			=0;
	HLimit			=0;
	WholePoint=NULL;
}

bool	ImageCheckerRegCalcLightWhole::Execute(void)
{
	ImageCheckerItem	*Item=NULL;
	ImageCheckerBase	*PBase=(ImageCheckerBase *)LayerPoint->GetParentBase();
	AlgorithmItemPLI *a;
	Result=0;
	Ok=true;
	if(PBase->ModeDotPattern==false){
		if(WholePoint!=NULL){
			double Avr ,Var;
			LayerPoint->MakeAvrVar(WholePoint->GetArea()
								,((IsMasterMode()==true)?WholePoint->GetMasterBuff():WholePoint->GetTargetBuff())
																	
				,Avr ,Var ,100);
			Result=Avr;
			if(LLimit<=Avr && Avr<=HLimit){
				Ok=true;
			}
			else{
				Ok=false;
			}
		}
	}
	else if(PBase->ModeDotPattern==true){
		for(a=LayerPoint->GetFirstData();a!=NULL;a=a->GetNext()){
			Item=dynamic_cast<ImageCheckerItem *>(a);
			if(Item!=NULL && Item->GetThresholdR(LayerPoint->GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcSlide){
				break;
			}
		}
		if(Item==NULL || a==NULL){
			return false;
		}
		double	SumAvr=0.0;
		int		SumAvrCount=0;
		for(int yn=0;yn<Item->MaxYCount;yn++){
			for(int xn=0;xn<Item->MaxXCount;xn++){
				if(Item->DotMatrix[yn][xn]!=NULL){
					double Avr;
					double Var;
					Item->DotMatrix[yn][xn]->CalcAvrVar(0,0
														,((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
														,Avr ,Var);
					SumAvr+=Avr;
					SumAvrCount++;
				}
			}
		}
		if(SumAvrCount!=0){
			SumAvr/=SumAvrCount;
		}
		Result=SumAvr;
		if(LLimit<=SumAvr && SumAvr<=HLimit){
			Ok=true;
		}
		else{
			Ok=false;
		}		
	}

	return true;
}
bool	ImageCheckerRegCalcLightWhole::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	WholePointExist=(WholePoint!=NULL)?true:false;
	if(::Save(f,WholePointExist)==false){
		return false;
	}
	if(WholePoint!=NULL){
		int32	id1=WholePoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	if(::Save(f,StandardValue)==false){
		return false;
	}
	if(::Save(f,LLimit)==false){
		return false;
	}
	if(::Save(f,HLimit)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcLightWhole::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	WholePointExist;
	if(::Load(f,WholePointExist)==false){
		return false;
	}
	if(WholePointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		WholePoint=dynamic_cast<ImageCheckerItem *>(L);
		if(WholePoint==NULL){
			return false;
		}
	}
	if(::Load(f,StandardValue)==false){
		return false;
	}
	if(::Load(f,LLimit)==false){
		return false;
	}
	if(::Load(f,HLimit)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcLightWhole::DeletedItem(AlgorithmItemPLI *Item)
{
	if(WholePoint==Item){
		WholePoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcLightLeftRight::ImageCheckerRegCalcLightLeftRight(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	LimitDot=0;
	LeftPoint=NULL;	
	RightPoint=NULL;
}

bool	ImageCheckerRegCalcLightLeftRight::Execute(void)
{
	return true;
}
bool	ImageCheckerRegCalcLightLeftRight::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist=(LeftPoint!=NULL)?true:false;
	if(::Save(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPoint!=NULL){
		int32	id1=LeftPoint->GetID();
		if(::Save(f,id1)==false){
			return false;
		}
	}
	bool	RightPointExist=(RightPoint!=NULL)?true:false;
	if(::Save(f,RightPointExist)==false){
		return false;
	}
	if(RightPoint!=NULL){
		int32	id2=RightPoint->GetID();
		if(::Save(f,id2)==false){
			return false;
		}
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	return true;
}
bool	ImageCheckerRegCalcLightLeftRight::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	bool	LeftPointExist;
	if(::Load(f,LeftPointExist)==false){
		return false;
	}
	if(LeftPointExist==true){
		int32	id1;
		if(::Load(f,id1)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id1);
		if(L==NULL){
			return false;
		}
		LeftPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(LeftPoint==NULL){
			return false;
		}
	}
	bool	RightPointExist;
	if(::Load(f,RightPointExist)==false){
		return false;
	}
	if(RightPointExist==true){
		int32	id2;
		if(::Load(f,id2)==false){
			return false;
		}
		AlgorithmItemRoot		*L=LayerPoint->SearchIDItem(id2);
		if(L==NULL){
			return false;
		}
		RightPoint=dynamic_cast<ImageCheckerItem *>(L);
		if(RightPoint==NULL){
			return false;
		}
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcLightLeftRight::DeletedItem(AlgorithmItemPLI *Item)
{
	if(LeftPoint==Item){
		LeftPoint=NULL;
		return true;
	}
	if(RightPoint==Item){
		RightPoint=NULL;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcResolution::ImageCheckerRegCalcResolution(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	Resolution	=0;
	PosY		=0;
	DifResLow	=0;
	DifResHigh	=0;
}

bool	ImageCheckerRegCalcResolution::Execute(int ShiftX ,int ShiftY)
{
	ImageCheckerItem	*Item=NULL;
	AlgorithmItemPLI *a;
	for(a=LayerPoint->GetFirstData();a!=NULL;a=a->GetNext()){
		Item=dynamic_cast<ImageCheckerItem *>(a);
		if(Item!=NULL && Item->GetThresholdR(LayerPoint->GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcResolution){
			break;
		}
	}
	if(Item==NULL || a==NULL){
		return false;
	}
	/*
	//ピークを計算
	double	MaxFFTList=0;
	for(int i=0;i<Item->FFTListCount;i++){
		if(MaxFFTList<Item->FFTList[i]){
			MaxFFTList=Item->FFTList[i];
		}
	}
	double	MinFFTList=MaxFFTList*0.1;
	double	SumFFTList=0;
	double	MulFFTList=0;
	for(int i=0;i<Item->FFTListCount;i++){
		if(MinFFTList<Item->FFTList[i]){
			SumFFTList+=Item->FFTList[i];
			MulFFTList+=Item->FFTList[i]*i;
		}
	}
	int	CenterPos=MulFFTList/SumFFTList;
	double	SumData=0;
	int		SumDataCount=0;
	for(int i=CenterPos-5;i<CenterPos+5;i++){
		SumData+=Item->FFTList[i];
		SumDataCount++;
	}
	double	Avr=SumData/SumDataCount;
	
	Result	=Avr;
	*/

	int	W=Item->GetArea().GetWidth();
	int	Cx,Cy;
	Item->GetCenter(Cx,Cy);

	double Avr ,Var;
	Item->GetArea().CalcAvrVar(ShiftX ,ShiftY
								,((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
								,Avr ,Var
					,1.0,1.0
					,Cx-W/2,PosY-20,Cx+W/2,PosY+20);

	double	Dif=sqrt(Var);
	Result	=Dif;
	Ok=true;
	if(Dif<0){
		if(-Dif>DifResLow){
			Ok=false;
		}
	}
	if(Dif>0){
		if(Dif>DifResHigh){
			Ok=false;
		}
	}

	return true;
}
bool	ImageCheckerRegCalcResolution::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,Resolution)==false){
		return false;
	}
	if(::Save(f,PosY)==false){
		return false;
	}
	if(::Save(f,DifResLow)==false){
		return false;
	}
	if(::Save(f,DifResHigh)==false){
		return false;
	}

	return true;
}
bool	ImageCheckerRegCalcResolution::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,Resolution)==false){
		return false;
	}
	if(::Load(f,PosY)==false){
		return false;
	}
	if(::Load(f,DifResLow)==false){
		return false;
	}
	if(::Load(f,DifResHigh)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcResolution::DeletedItem(AlgorithmItemPLI *Item)
{
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcSlide::ImageCheckerRegCalcSlide(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	XPos		=0;
	YPos		=0;
	DifPosLow	=0;
	DifPosHigh	=0;
}

bool	ImageCheckerRegCalcSlide::Execute(void)
{
	ImageCheckerItem	*Item=NULL;
	AlgorithmItemPLI *a;
	for(a=LayerPoint->GetFirstData();a!=NULL;a=a->GetNext()){
		Item=dynamic_cast<ImageCheckerItem *>(a);
		if(Item!=NULL && Item->GetThresholdR(LayerPoint->GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcSlide){
			break;
		}
	}
	if(Item==NULL || a==NULL){
		return false;
	}

	if(Item!=NULL){
			
		double	Cx=Item->CenterPointForSlideX;
		double	Cy=Item->CenterPointForSlideY;
		double	MinH=99999999;
		int	MinHx=0;
		int	MinHy=0;
		for(int y=0;y<Item->MaxYCount;y++){
			for(int x=0;x<Item->MaxXCount;x++){
				double	cx1,cy1;
				if(Item->DotMatrix[y][x]!=NULL){
					Item->DotMatrix[y][x]->GetCenter(cx1,cy1);
					double	H=hypot(Cx-cx1,Cy-cy1);
					if(H<MinH){
						MinH=H;
						MinHx=x;
						MinHy=y;
					}
				}
			}
		}
		int		SumCount=0;
		double	SumCx=0;
		double	SumCy=0;
		for(int y=max(0,MinHy-1);y<Item->MaxYCount && y<=MinHy+1;y++){
			for(int x=max(0,MinHx-1);x<Item->MaxXCount && x<=MinHx+1;x++){
				double	cx1,cy1;
				if(Item->DotMatrix[y][x]!=NULL){
					Item->DotMatrix[y][x]->GetCenter(cx1,cy1);
					SumCount++;
					SumCx+=cx1;
					SumCy+=cy1;
				}
			}
		}
		
		if(SumCount!=0){
			SumCx/=SumCount;
			SumCy/=SumCount;
		}
		Result	=SumCx;
		Result2	=SumCy;

		double	L=hypot(SumCx-XPos,SumCy-YPos);
		if(L>DifPosLow){
			Ok=false;
		}
		else{
			Ok=true;
		}
	}

	return true;
}
bool	ImageCheckerRegCalcSlide::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,XPos)==false){
		return false;
	}
	if(::Save(f,YPos)==false){
		return false;
	}
	if(::Save(f,DifPosLow)==false){
		return false;
	}
	if(::Save(f,DifPosHigh)==false){
		return false;
	}

	return true;
}
bool	ImageCheckerRegCalcSlide::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,XPos)==false){
		return false;
	}
	if(::Load(f,YPos)==false){
		return false;
	}
	if(::Load(f,DifPosLow)==false){
		return false;
	}
	if(::Load(f,DifPosHigh)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcSlide::DeletedItem(AlgorithmItemPLI *Item)
{
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcIncline::ImageCheckerRegCalcIncline(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	VarTop	=0;
	VarLeft	=0;
	VarRight=0;
	VarBottom=0;
	DifLow	=0;
	DifHigh	=0;
}

bool	ImageCheckerRegCalcIncline::Execute(void)
{
	AlgorithmItemPLI	*a=LayerPoint->GetFirstData();
	ImageCheckerItem	*Item=dynamic_cast<ImageCheckerItem *>(a);

	if(Item!=NULL){
		double	SumTop		=0;
		int		SumTopCount	=0;
		for(int y=0;y<Item->MaxYCount/3;y++){
			for(int x=0;x<Item->MaxXCount;x++){
				if(Item->DotMatrix[y][x]!=NULL){
					SumTop+=GetFocusLevel(((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
											, *(Item->DotMatrix[y][x]),8);
					SumTopCount++;
				}
			}
		}
		if(SumTopCount!=0){
			SumTop/=SumTopCount;
		}
		Result=SumTop;

		double	SumLeft		=0;
		int		SumLeftCount	=0;
		for(int y=0;y<Item->MaxYCount;y++){
			for(int x=0;x<Item->MaxXCount/3;x++){
				if(Item->DotMatrix[y][x]!=NULL){
					SumLeft+=GetFocusLevel(((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
											, *(Item->DotMatrix[y][x]),8);
					SumLeftCount++;
				}
			}
		}
		if(SumLeftCount!=0){
			SumLeft/=SumLeftCount;
		}
		Result2=SumLeft;

		double	SumRight		=0;
		int		SumRightCount	=0;
		for(int y=0;y<Item->MaxYCount;y++){
			for(int x=2*Item->MaxXCount/3;x<Item->MaxXCount;x++){
				if(Item->DotMatrix[y][x]!=NULL){
					SumRight+=GetFocusLevel(((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
											, *(Item->DotMatrix[y][x]),8);
					SumRightCount++;
				}
			}
		}
		if(SumRightCount!=0){
			SumRight/=SumRightCount;
		}
		Result3=SumRight;

		double	SumBottom		=0;
		int		SumBottomCount	=0;
		for(int y=2*Item->MaxYCount/3;y<Item->MaxYCount;y++){
			for(int x=0;x<Item->MaxXCount;x++){
				if(Item->DotMatrix[y][x]!=NULL){
					SumBottom+=GetFocusLevel(((IsMasterMode()==true)?Item->GetMasterBuff():Item->GetTargetBuff())
											, *(Item->DotMatrix[y][x]),8);
					SumBottomCount++;
				}
			}
		}
		if(SumBottomCount!=0){
			SumBottom/=SumBottomCount;
		}
		Result4=SumBottom;

		if(VarTop>0.001 && VarLeft>0.001 && VarRight>0.001 && VarBottom>0.001
		&& SumTop>0.001 && SumLeft>0.001 && SumRight>0.001 && SumBottom>0.001){
			double	YNew=SumTop/SumBottom;
			double	YOld=VarTop/VarBottom;
			double	XNew=SumLeft/SumRight;
			double	XOld=VarLeft/VarRight;

			double	YValue=YNew/YOld;
			double	XValue=XNew/XOld;

			if(YValue<DifLow || XValue<DifLow){
				Ok=false;
			}
			else if(YValue>DifHigh || XValue>DifHigh){
				Ok=false;
			}
			else{
				Ok=true;
			}
			Result5=YValue;
			Result6=XValue;
		}
	}

	return true;
}
bool	ImageCheckerRegCalcIncline::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,VarTop)==false){
		return false;
	}
	if(::Save(f,VarLeft)==false){
		return false;
	}
	if(::Save(f,VarRight)==false){
		return false;
	}
	if(::Save(f,VarBottom)==false){
		return false;
	}
	if(::Save(f,DifLow)==false){
		return false;
	}
	if(::Save(f,DifHigh)==false){
		return false;
	}

	return true;
}
bool	ImageCheckerRegCalcIncline::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,VarTop)==false){
		return false;
	}
	if(::Load(f,VarLeft)==false){
		return false;
	}
	if(::Load(f,VarRight)==false){
		return false;
	}
	if(::Load(f,VarBottom)==false){
		return false;
	}
	if(::Load(f,DifLow)==false){
		return false;
	}
	if(::Load(f,DifHigh)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcIncline::DeletedItem(AlgorithmItemPLI *Item)
{
	return false;
}
//--------------------------------------------------------------------------------------
ImageCheckerRegCalcParamEntry::ImageCheckerRegCalcParamEntry(ImageCheckerInLayer *Ly)
:ImageCheckerRegCalcBase(Ly)
{	
	CamA=0;
	CamB=0;
	LightA=0;
	LightB=0;
}

bool	ImageCheckerRegCalcParamEntry::Execute(void)
{
	Result=0;
	Result2=0;
	if(CamA>0.0000001){
		Result	=LayerPoint->RegCalcCamZ.GetResult()-CamA;
	}
	if(LightA>0.0000001){
		Result2	=(LayerPoint->RegCalcLightWhole.GetResult()-LightA)*LightB;
	}
	return true;
}

bool	ImageCheckerRegCalcParamEntry::Save(QIODevice *f)
{
	if(::Save(f,CamA)==false){
		return false;
	}
	if(::Save(f,CamB)==false){
		return false;
	}
	if(::Save(f,LightA)==false){
		return false;
	}
	if(::Save(f,LightB)==false){
		return false;
	}
	return true;
}

bool	ImageCheckerRegCalcParamEntry::Load(QIODevice *f)
{
	if(::Load(f,CamA)==false){
		return false;
	}
	if(::Load(f,CamB)==false){
		return false;
	}
	if(::Load(f,LightA)==false){
		return false;
	}
	if(::Load(f,LightB)==false){
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------

ImageCheckerInLayer::ImageCheckerInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
,RegCalcCamX(this)
,RegCalcCamY(this)
,RegCalcCamZ(this)
,RegCalcCamXTilt(this)
,RegCalcCamYTilt(this)
,RegCalcCamRot(this)
,RegCalcStageFlat(this)
,RegCalcStageVerocity(this)
,RegCalcStageVConst(this)
,RegCalcLightWhole(this)
,RegCalcLightLeftRight(this)
,RegCalcResolution(this)
,RegCalcSlide(this)
,RegCalcIncline(this)
,RegCalcParamEntry(this)
{}

void	ImageCheckerInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	AddAreaPacket	*AddAreaPacketVar=dynamic_cast<AddAreaPacket *>(packet);
	if(AddAreaPacketVar!=NULL){
		ImageCheckerBase	*PBase=(ImageCheckerBase *)GetParentBase();
		ImageCheckerItem	*MData=(ImageCheckerItem	*)CreateItem(0);

		switch(AddAreaPacketVar->Mode){
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamX:
				RegCalcCamX.LeftPoint	=MData;
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamY:
				RegCalcCamY.TopPoint	=MData;
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamZ:
				RegCalcCamZ.CenterPoint	=MData;
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamXTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamYTilt:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcCamRot:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageFlat:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVerocity:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcStageVConst:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightWhole:
				RegCalcLightWhole.WholePoint	=MData;
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcLightLeftRight:
				break;
			case ImageCheckerThreshold::_ImageCheckerRegCalcResolution:
				break;
		}
		MData->SetArea(AddAreaPacketVar->Area);
		MData->SetManualCreated(true);
		AppendItem(MData);
		if(AddAreaPacketVar->Mode!=ImageCheckerThreshold::_ImageCheckerRegCalcResolution
		&& AddAreaPacketVar->Mode!=ImageCheckerThreshold::_ImageCheckerRegCalcMatching){
			if(PBase->ModeDotPattern==true){
				MData->MakeDotMatrix();
				MData->SetCenterPointForSlide();
			}
		}
		if(AddAreaPacketVar->Mode==ImageCheckerThreshold::_ImageCheckerRegCalcMatching){
			MData->MatchingPosInLine(MData->MainPosX ,MData->MainPosY);
		}
		MData->GetThresholdW()->ImageCheckerRegMode=AddAreaPacketVar->Mode;
		return;
	}
	SetRegDataPacket	*SetRegDataPacketVar=dynamic_cast<SetRegDataPacket *>(packet);
	if(SetRegDataPacketVar!=NULL){
		RegCalcCamX.LLimit			=SetRegDataPacketVar->RegData.RegCalcCamX.LLimit;
		RegCalcCamX.HLimit			=SetRegDataPacketVar->RegData.RegCalcCamX.HLimit;
		RegCalcCamX.StandardValue	=SetRegDataPacketVar->RegData.RegCalcCamX.StandardValue;
		
		RegCalcCamY.LLimit			=SetRegDataPacketVar->RegData.RegCalcCamY.LLimit;
		RegCalcCamY.HLimit			=SetRegDataPacketVar->RegData.RegCalcCamY.HLimit;
		RegCalcCamY.StandardValue	=SetRegDataPacketVar->RegData.RegCalcCamY.StandardValue;

		RegCalcCamZ.LLimit			=SetRegDataPacketVar->RegData.RegCalcCamZ.LLimit;
		RegCalcCamZ.HLimit			=SetRegDataPacketVar->RegData.RegCalcCamZ.HLimit;
		RegCalcCamZ.StandardValue	=SetRegDataPacketVar->RegData.RegCalcCamZ.StandardValue;
		
		//RegCalcCamXTilt;
		//RegCalcCamYTilt;
		//RegCalcCamRot;
		//RegCalcStageFlat;
		//RegCalcStageVerocity;
		//RegCalcStageVConst;
		RegCalcLightWhole.LLimit		=SetRegDataPacketVar->RegData.RegCalcLightWhole[GetLayer()].LLimit;
		RegCalcLightWhole.HLimit		=SetRegDataPacketVar->RegData.RegCalcLightWhole[GetLayer()].HLimit;
		RegCalcLightWhole.StandardValue	=SetRegDataPacketVar->RegData.RegCalcLightWhole[GetLayer()].StandardValue;
		//RegCalcLightLeftRight;

		RegCalcResolution.Resolution	=SetRegDataPacketVar->RegData.RegCalcResolution.Resolution;
		RegCalcResolution.PosY			=SetRegDataPacketVar->RegData.RegCalcResolution.PosY;
		RegCalcResolution.DifResLow		=SetRegDataPacketVar->RegData.RegCalcResolution.DifResLow;
		RegCalcResolution.DifResHigh	=SetRegDataPacketVar->RegData.RegCalcResolution.DifResHigh;

		RegCalcSlide.XPos				=SetRegDataPacketVar->RegData.RegCalcSlide.XPos;
		RegCalcSlide.YPos				=SetRegDataPacketVar->RegData.RegCalcSlide.YPos;
		RegCalcSlide.DifPosLow			=SetRegDataPacketVar->RegData.RegCalcSlide.DifPosLow;
		RegCalcSlide.DifPosHigh			=SetRegDataPacketVar->RegData.RegCalcSlide.DifPosHigh;

		RegCalcIncline.VarTop			=SetRegDataPacketVar->RegData.RegCalcIncline.VarTop;
		RegCalcIncline.VarLeft			=SetRegDataPacketVar->RegData.RegCalcIncline.VarLeft;
		RegCalcIncline.VarRight			=SetRegDataPacketVar->RegData.RegCalcIncline.VarRight;
		RegCalcIncline.VarBottom		=SetRegDataPacketVar->RegData.RegCalcIncline.VarBottom;
		RegCalcIncline.DifLow			=SetRegDataPacketVar->RegData.RegCalcIncline.DifLow;
		RegCalcIncline.DifHigh			=SetRegDataPacketVar->RegData.RegCalcIncline.DifHigh;

		RegCalcParamEntry.CamA			=SetRegDataPacketVar->RegData.RegParamEntry.CamA;
		RegCalcParamEntry.CamB			=SetRegDataPacketVar->RegData.RegParamEntry.CamB;
		RegCalcParamEntry.LightA		=SetRegDataPacketVar->RegData.RegParamEntry.LightA;
		RegCalcParamEntry.LightB		=SetRegDataPacketVar->RegData.RegParamEntry.LightB;

		return;
	}
	ReqValuePacket	*ReqValuePacketVar=dynamic_cast<ReqValuePacket *>(packet);
	if(ReqValuePacketVar!=NULL){
		int	ShiftX=0;
		int	ShiftY=0;
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			ImageCheckerItem	*p=(ImageCheckerItem *)a;
			if(p->GetThresholdR(GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcMatching){
				int X ,Y;
				p->MatchingPosInLine(X ,Y);
				ShiftX=X-p->MainPosX;
				ShiftY=Y-p->MainPosY;
			}
		}
		for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			ImageCheckerItem	*p=(ImageCheckerItem *)a;
			if(p->GetThresholdR(GetLayersBase())->ImageCheckerRegMode==ImageCheckerThreshold::_ImageCheckerRegCalcResolution){
				p->MakeFFTList();
			}
		}
		SetRegData(ReqValuePacketVar->RegData);
		RegCalcCamX.Execute();
		ReqValuePacketVar->RegData.RegCalcCamX.Value=RegCalcCamX.GetResult();
		ReqValuePacketVar->RegData.RegCalcCamX.Ok	=RegCalcCamX.GetOk();
		RegCalcCamY.Execute();
		ReqValuePacketVar->RegData.RegCalcCamY.Value=RegCalcCamY.GetResult();
		ReqValuePacketVar->RegData.RegCalcCamY.Ok	=RegCalcCamY.GetOk();

		ImageCheckerBase	*PBase=(ImageCheckerBase *)GetParentBase();
		if(PBase->ModeDotPattern==true){
			for(AlgorithmItemPLI *a=GetFirstData();a!=NULL;a=a->GetNext()){
				ImageCheckerItem	*Item=dynamic_cast<ImageCheckerItem *>(a);
				if(Item!=NULL){
					Item->MakeDotMatrix();
				}
			}
		}
		if(GetFirstData()==NULL){
			ReqValuePacketVar->Effective=false;
		}
		else{
			ReqValuePacketVar->Effective=true;
		}

		if(RegCalcCamZ.Execute(ShiftX,ShiftY)==true){
			ReqValuePacketVar->RegData.RegCalcCamZ.Value=RegCalcCamZ.GetResult();
			ReqValuePacketVar->RegData.RegCalcCamZ.Value2=RegCalcCamZ.GetResult2();
			ReqValuePacketVar->RegData.RegCalcCamZ.Ok	=RegCalcCamZ.GetOk();
		}

		if(RegCalcLightWhole.Execute()==true){
			ReqValuePacketVar->RegData.RegCalcLightWhole[GetLayer()].Value	=RegCalcLightWhole.GetResult();
			ReqValuePacketVar->RegData.RegCalcLightWhole[GetLayer()].Ok		=RegCalcLightWhole.GetOk();
		}

		if(RegCalcResolution.Execute(ShiftX,ShiftY)==true){
			ReqValuePacketVar->RegData.RegCalcResolution.Value	=RegCalcResolution.GetResult();
			ReqValuePacketVar->RegData.RegCalcResolution.Ok		=RegCalcResolution.GetOk();
		}

		if(RegCalcSlide.Execute()==true){
			ReqValuePacketVar->RegData.RegCalcSlide.Value		=RegCalcSlide.GetResult();
			ReqValuePacketVar->RegData.RegCalcSlide.Value2		=RegCalcSlide.GetResult2();
			ReqValuePacketVar->RegData.RegCalcSlide.Ok			=RegCalcSlide.GetOk();
		}

		if(RegCalcParamEntry.Execute()==true){
			ReqValuePacketVar->RegData.RegParamEntry.CamA	=RegCalcParamEntry.CamA;
			ReqValuePacketVar->RegData.RegParamEntry.CamB	=RegCalcParamEntry.CamB;
			ReqValuePacketVar->RegData.RegParamEntry.LightA	=RegCalcParamEntry.LightA;
			ReqValuePacketVar->RegData.RegParamEntry.LightB	=RegCalcParamEntry.LightB;
			//ReqValuePacketVar->RegData.RegParamEntry.Value		=RegCalcParamEntry.GetResult();
			//ReqValuePacketVar->RegData.RegParamEntry.Value2		=RegCalcParamEntry.GetResult2();
		}

		/*
		RegCalcIncline.Execute();
		ReqValuePacketVar->RegData.RegCalcIncline.Value		=RegCalcIncline.GetResult();
		ReqValuePacketVar->RegData.RegCalcIncline.Value2	=RegCalcIncline.GetResult2();
		ReqValuePacketVar->RegData.RegCalcIncline.Value3	=RegCalcIncline.GetResult3();
		ReqValuePacketVar->RegData.RegCalcIncline.Value4	=RegCalcIncline.GetResult4();
		ReqValuePacketVar->RegData.RegCalcIncline.Value5	=RegCalcIncline.GetResult5();
		ReqValuePacketVar->RegData.RegCalcIncline.Value6	=RegCalcIncline.GetResult6();
		ReqValuePacketVar->RegData.RegCalcIncline.Ok		=RegCalcIncline.GetOk();
		*/

		return;
	}
	ReqRegDataPacket	*ReqRegDataPacketVar=dynamic_cast<ReqRegDataPacket *>(packet);
	if(ReqRegDataPacketVar!=NULL){
		SetRegData(ReqRegDataPacketVar->RegData);
		return;
	}
}

void	ImageCheckerInLayer::SetRegData(struct ImageCheckerRegData &RegData)
{
	RegData.RegCalcCamX.StandardValue	=RegCalcCamX.StandardValue;
	RegData.RegCalcCamX.LLimit			=RegCalcCamX.LLimit;
	RegData.RegCalcCamX.HLimit			=RegCalcCamX.HLimit;

	RegData.RegCalcCamY.StandardValue	=RegCalcCamY.StandardValue;
	RegData.RegCalcCamY.LLimit			=RegCalcCamY.LLimit;
	RegData.RegCalcCamY.HLimit			=RegCalcCamY.HLimit;

	RegData.RegCalcCamZ.StandardValue	=RegCalcCamZ.StandardValue;
	RegData.RegCalcCamZ.LLimit			=RegCalcCamZ.LLimit;
	RegData.RegCalcCamZ.HLimit			=RegCalcCamZ.HLimit;

	RegData.RegCalcLightWhole[GetLayer()].StandardValue	=RegCalcLightWhole.StandardValue;
	RegData.RegCalcLightWhole[GetLayer()].LLimit		=RegCalcLightWhole.LLimit;
	RegData.RegCalcLightWhole[GetLayer()].HLimit		=RegCalcLightWhole.HLimit;

	RegData.RegCalcResolution.Resolution	=RegCalcResolution.Resolution;
	RegData.RegCalcResolution.PosY			=RegCalcResolution.PosY;
	RegData.RegCalcResolution.DifResLow		=RegCalcResolution.DifResLow;
	RegData.RegCalcResolution.DifResHigh	=RegCalcResolution.DifResHigh;

	RegData.RegCalcSlide.XPos				=RegCalcSlide.XPos;
	RegData.RegCalcSlide.YPos				=RegCalcSlide.YPos;
	RegData.RegCalcSlide.DifPosLow			=RegCalcSlide.DifPosLow;
	RegData.RegCalcSlide.DifPosHigh			=RegCalcSlide.DifPosHigh;

	RegData.RegCalcIncline.VarTop			=RegCalcIncline.VarTop;
	RegData.RegCalcIncline.VarLeft			=RegCalcIncline.VarLeft;
	RegData.RegCalcIncline.VarRight			=RegCalcIncline.VarRight;
	RegData.RegCalcIncline.VarBottom		=RegCalcIncline.VarBottom;
	RegData.RegCalcIncline.DifLow			=RegCalcIncline.DifLow;
	RegData.RegCalcIncline.DifHigh			=RegCalcIncline.DifHigh;

	RegData.RegParamEntry.CamA				=RegCalcParamEntry.CamA;
	RegData.RegParamEntry.CamB				=RegCalcParamEntry.CamB;
	RegData.RegParamEntry.LightA			=RegCalcParamEntry.LightA;
	RegData.RegParamEntry.LightB			=RegCalcParamEntry.LightB;
}


bool	ImageCheckerInLayer::Save(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Save(f)==false){
		return false;
	}

	if(RegCalcCamX.Save(f)==false)			{		return false;	}
	if(RegCalcCamY.Save(f)==false)			{		return false;	}
	if(RegCalcCamZ.Save(f)==false)			{		return false;	}
	if(RegCalcCamXTilt.Save(f)==false)		{		return false;	}
	if(RegCalcCamYTilt.Save(f)==false)		{		return false;	}
	if(RegCalcCamRot.Save(f)==false)		{		return false;	}
	if(RegCalcStageFlat.Save(f)==false)		{		return false;	}
	if(RegCalcStageVerocity.Save(f)==false)	{		return false;	}
	if(RegCalcStageVConst.Save(f)==false)	{		return false;	}
	if(RegCalcLightWhole.Save(f)==false)	{		return false;	}
	if(RegCalcLightLeftRight.Save(f)==false){		return false;	}
	if(RegCalcResolution.Save(f)==false)	{		return false;	}
	if(RegCalcSlide.Save(f)==false)			{		return false;	}
	if(RegCalcIncline.Save(f)==false)		{		return false;	}
	if(RegCalcParamEntry.Save(f)==false)	{		return false;	}

	return true;
}
bool	ImageCheckerInLayer::Load(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Load(f)==false){
		return false;
	}

	if(RegCalcCamX.Load(f)==false)			{		return false;	}
	if(RegCalcCamY.Load(f)==false)			{		return false;	}
	if(RegCalcCamZ.Load(f)==false)			{		return false;	}
	if(RegCalcCamXTilt.Load(f)==false)		{		return false;	}
	if(RegCalcCamYTilt.Load(f)==false)		{		return false;	}
	if(RegCalcCamRot.Load(f)==false)		{		return false;	}
	if(RegCalcStageFlat.Load(f)==false)		{		return false;	}
	if(RegCalcStageVerocity.Load(f)==false)	{		return false;	}
	if(RegCalcStageVConst.Load(f)==false)	{		return false;	}
	if(RegCalcLightWhole.Load(f)==false)	{		return false;	}
	if(RegCalcLightLeftRight.Load(f)==false){		return false;	}
	if(RegCalcResolution.Load(f)==false)	{		return false;	}
	if(RegCalcSlide.Load(f)==false)			{		return false;	}
	if(RegCalcIncline.Load(f)==false)		{		return false;	}
	if(RegCalcParamEntry.Load(f)==false)	{		return false;	}

	return true;
}

void	ImageCheckerInLayer::MakeAvrVar(FlexArea &Area ,ImageBuffer &Buff,double &Avr ,double &Var ,int CellSize)
{
	int	W=Area.GetWidth();
	int	H=Area.GetHeight();
	int	WCount=(W+CellSize-1)/CellSize;
	int	HCount=(H+CellSize-1)/CellSize;

	Avr=0;
	Var=0;
	int	N=0;
	for(int w=0;w<WCount;w++){
		if(WCount>=4 && (w==0  || w==(WCount-1))){
			continue;
		}
		for(int h=0;h<HCount;h++){
			if(HCount>=4 && (h==0  || h==(HCount-1))){
				continue;
			}
			double	tAvr ,tVar;
			Area.CalcAvrVar(0,0,Buff,tAvr ,tVar
							,0.9,0.9
							,Area.GetMinX()+w*CellSize		,Area.GetMinY()+h*CellSize
							,Area.GetMinX()+(w+1)*CellSize	,Area.GetMinY()+(h+1)*CellSize);
			Avr+=tAvr;
			Var+=tVar;
			N++;
		}
	}
	if(N==0)
		return;
	Avr/=N;
	Var/=N;
}

struct	AvrVarStruct
{
	double Avr;
	double Var;
};

static	int	AvrVarDimFunc(const void *a,const void *b)
{
	if(((struct AvrVarStruct *)a)->Var>((struct AvrVarStruct *)b)->Var)
		return 1;
	if(((struct AvrVarStruct *)a)->Var<((struct AvrVarStruct *)b)->Var)
		return -1;
	return 0;
}

void	ImageCheckerInLayer::MakeAvrVar(FlexArea &Area ,ImageBuffer &Buff
										,BYTE **MaskMap
										,double &Avr ,double &Var ,int CellSize)
{
	int	W=Area.GetWidth();
	int	H=Area.GetHeight();
	int	WCount=(W+CellSize-1)/CellSize;
	int	HCount=(H+CellSize-1)/CellSize;
	struct	AvrVarStruct	*AvrVarDim=new struct AvrVarStruct[WCount*HCount];

	Avr=0;
	Var=0;
	int	N=0;
	for(int w=0;w<WCount;w++){
		if(WCount>=4 && (w==0  || w==(WCount-1))){
			continue;
		}
		for(int h=0;h<HCount;h++){
			if(HCount>=4 && (h==0  || h==(HCount-1))){
				continue;
			}
			double	tAvr ,tVar;
			Area.CalcAvrVar(0,0,Buff,tAvr ,tVar
							,MaskMap
							,0.9,0.9
							,Area.GetMinX()+w*CellSize		,Area.GetMinY()+h*CellSize
							,Area.GetMinX()+(w+1)*CellSize	,Area.GetMinY()+(h+1)*CellSize);
			AvrVarDim[N].Avr=tAvr;
			AvrVarDim[N].Var=tVar;
			N++;
		}
	}
	if(N==0){
		delete	[]AvrVarDim;
		return;
	}

	QSort(AvrVarDim,N,sizeof(AvrVarDim[0]),AvrVarDimFunc);

	Avr=0;
	Var=0;
	int	Count=0;
	for(int i=N/3;i<2*N/3;i++){
		Avr+=AvrVarDim[i].Avr;
		Var+=AvrVarDim[i].Var;
		Count++;
	}
	Avr/=Count;
	Var/=Count;
	delete	[]AvrVarDim;
}

void	ImageCheckerInLayer::DeleteSelectedItems(void)
{
	for(AlgorithmItemPLI *item=GetFirstData();item!=NULL;item=item->GetNext()){
		if(item->GetSelected()==true){
			RegCalcCamX.DeletedItem(item);
			RegCalcCamY.DeletedItem(item);
			RegCalcCamZ.DeletedItem(item);
			RegCalcCamXTilt.DeletedItem(item);
			RegCalcCamYTilt.DeletedItem(item);
			RegCalcCamRot.DeletedItem(item);
			RegCalcStageFlat.DeletedItem(item);
			RegCalcStageVerocity.DeletedItem(item);
			RegCalcStageVConst.DeletedItem(item);
			RegCalcLightWhole.DeletedItem(item);
			RegCalcLightLeftRight.DeletedItem(item);
			RegCalcResolution.DeletedItem(item);
			RegCalcSlide.DeletedItem(item);
			RegCalcIncline.DeletedItem(item);
			RegCalcParamEntry.DeletedItem(item);
		}
	}
	AlgorithmInLayerPLI::DeleteSelectedItems();
}

//===========================================
void	ImageCheckerInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddAreaPacket	*AddAreaPacketVar=dynamic_cast<AddAreaPacket *>(packet);
	if(AddAreaPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	SetRegDataPacket	*SetRegDataPacketVar=dynamic_cast<SetRegDataPacket *>(packet);
	if(SetRegDataPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	ReqValuePacket	*ReqValuePacketVar=dynamic_cast<ReqValuePacket *>(packet);
	if(ReqValuePacketVar!=NULL){
		memset(&ReqValuePacketVar->RegData,0,sizeof(ReqValuePacketVar->RegData));
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	ReqRegDataPacket	*ReqRegDataPacketVar=dynamic_cast<ReqRegDataPacket *>(packet);
	if(ReqRegDataPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
}
//===========================================
ImageCheckerBase::ImageCheckerBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorNormal		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	ColorNormal		=Qt::darkGreen;
	NegColorMask	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	ModeDotPattern	=false;
	BlocksizeOfAutoPickPadUp	=500;
	NoiseDot		=3;
	LineAngle		=90;
	LineFreqMicron	=20.0;
	DotResolutionMicron=4.7;
	SlopAngle		=20;
	InspectMaster	=true;

	SetParam(&ColorNormal		, /**/"Color"	,/**/"ColorNormal"		,"Color for Normal Mask");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"	,"Color for Selected Mask");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"		,"Color for Active Mask");
	SetParam(&NegColorNormal	, /**/"Color"	,/**/"NegColorNormal"	,"Color for Neg Normal Mask");
	SetParam(&NegColorMask		, /**/"Color"	,/**/"NegColorMask"		,"Color for Negative Mask");
	SetParam(&NegColorSelected	, /**/"Color"	,/**/"NegColorSelected"	,"Color for Selected Negative Mask");
	SetParam(&TransparentLevel	, /**/"Color"	,/**/"TransparentLevel"	,"Color for Transparent display level");
	SetParam(&ModeDotPattern	, /**/"Setting" ,/**/"ModeDotPattern"	,"Mode of DotPattern");
	SetParam(&BlocksizeOfAutoPickPadUp, /**/"Setting" ,/**/"BlocksizeOfAutoPickPadUp"	,"Blocksize of Auto-Pick Pad up");
	SetParam(&NoiseDot			,/**/"Setting" ,/**/"NoiseDot"			,"Noise dot size");
	SetParam(&LineAngle			,/**/"Setting" ,/**/"LineAngle"			,"Line Angle");
	SetParam(&LineFreqMicron	,/**/"Setting" ,/**/"LineFreqMicron"	,"Frequency of Line (micron)");
	SetParam(&DotResolutionMicron,/**/"Setting" ,/**/"DotResolutionMicron"	,"Dot Resolution(micron)");
	SetParam(&SlopAngle			,/**/"Setting" ,/**/"SlopAngle"			,"Slop Angle");
	SetParam(&InspectMaster		,/**/"Setting" ,/**/"InspectMaster"		,"Check when master image is inspected");
}

AlgorithmDrawAttr	*ImageCheckerBase::CreateDrawAttr(void)
{
	return new ImageCheckerDrawAttr();
}
