/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Dent\XDentItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDentInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XDentLibrary.h"
#include "XImageProcess.h"
#include "swap.h"
#include <omp.h>
#include "XDisplayBitImage.h"
#include "XCrossObj.h"

//==============================================================================================


DentItem::DentBand::DentBand(DentItem *p)
	:Parent(p)
{
	AVector	=NULL;
	mx		=0;
	my		=0;
	AvrBrightnessH=0;
	AvrBrightnessL=0;
}
DentItem::DentBand::~DentBand(void)
{
}

void	DentItem::DentBand::ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo)
{
	int	Cx,Cy;
	Area.GetCenter(Cx,Cy);
	AVector=(AlignmentPacket2D *)Parent->GetAlignmentPointer(Cx,Cy);
	if(AVector!=NULL)
		AVector->Set(Parent);
}

void	DentItem::DentBand::ExecuteStartByInspection(void)
{
}

void	DentItem::DentBand::ExecuteProcessing(ImageBuffer &IBuff)
{
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	Cx,Cy;
		Area.GetCenter(Cx,Cy);
		V.PosXOnTarget=Cx;
		V.PosYOnTarget=Cy;
		V.ShiftX=0;
		V.ShiftY=0;
		Parent->GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	const	DentThreshold	*RThr=Parent->GetThresholdR(NULL);

	DentBase	*ABase=(DentBase *)Parent->GetParentBase();
	int		XList[1000];
	int	DotPerLine	=Parent->GetDotPerLine();
	int	MaxLines	=Parent->GetMaxLines();
	int	N=Area.GetFLineLen();
	int	Da=RThr->LinesForAverage;
	int	BaseWaveLen=ABase->BaseWaveLength;
	int	Ra=Da/2;
	for(int i=0;i<N;i++){
		int	Y=Area.GetFLineAbsY(i);
		int	DestY=Y+my;
		if(DestY<Ra || (MaxLines-Ra)<=DestY)
			continue;
		int	X=Area.GetFLineLeftX(i);
		int	DestX1=X+mx;
		int	DestX2=Area.GetFLineRightX(i)+mx;
		if(DestX1<0){
			X+=(-DestX1);
			DestX1=0;
		}
		if(DotPerLine<=DestX2)
			DestX2=DotPerLine-1;
		if(DestX1>DestX2)
			continue;
		int	MapY=Y-Parent->GetArea().GetMinY();
		int	MapX=X-Parent->GetArea().GetMinX();
		int	MapXMin=MapX;
		int	MapXMax=MapX+DestX2-DestX1;
		for(int x=DestX1;x<DestX2;x++,MapX++){
			int	AddedD=0;
			for(int dy=-Ra;dy<=Ra;dy++){
				BYTE	*s=&IBuff.GetY(DestY+dy)[x];
				AddedD+=*s;
			}
			XList[MapX]=AddedD;
		}
		double	B=0;
		double	BB=0;
		for(int x=MapXMin;x<MapXMax;x++){
			B+=XList[x];
			BB+=((double)XList[x])*((double)XList[x]);
		}
		double	SkipB=0;
		double	SkipBB=0;
		for(int x=MapXMin;x<MapXMax;x+=4){
			SkipB+=XList[x];
			SkipBB+=((double)XList[x])*((double)XList[x]);
		}

		int		Numb=MapXMax-MapXMin;
		int		SkipNumb=(Numb+3)>>2;
		if(Numb==0 || SkipNumb==0){
			continue;
		}
		double	AvrD=B/Numb;
		double	SkipAvrD=SkipB/SkipNumb;

		double	MaxM=-100000000;
		int		iMaxWaveLen=0;
		int		iMaxWavePhase=0;
		for(int w=0;w<WaveCount;w+=2){
			int	WaveLen=BaseWaveLen+w-WaveCount/2;
			for(int shift=0;shift<WaveLen;shift+=2){
				double	M=MakeCoefSkip(w ,shift ,ABase 
							,XList,MapXMin ,Numb
							,SkipAvrD ,SkipBB);
				if(MaxM<M){
					MaxM=M;
					iMaxWaveLen=w;
					iMaxWavePhase=shift;
				}
			}
		}
		int		MaxWaveLen=0;
		int		MaxWavePhase=0;
		MaxM=-100000000;
		for(int wi=-2;wi<=2;wi++){
			int	w=iMaxWaveLen+wi;
			if(w<0 || WaveCount<=w)
				continue;
			int	WaveLen=BaseWaveLen+w-WaveCount/2;
			for(int shifti=-2;shifti<=2;shifti++){
				int	shift=iMaxWavePhase+shifti;
				if(shift<0 || WaveLen<=shift)
					continue;
				double	M=MakeCoef(w ,shift ,ABase 
							,XList,MapXMin ,Numb
							,AvrD ,BB);
				if(MaxM<M){
					MaxM=M;
					MaxWaveLen=w;
					MaxWavePhase=shift;
				}
			}
		}

		Parent->ResultMaxD[MapY]	=MaxM;
		Parent->WaveLenList[MapY]	=MaxWaveLen;
		Parent->WavePhaseList[MapY]	=MaxWavePhase;
	}
	ResultDx=mx;
	ResultDy=my;
}
double	DentItem::DentBand::MakeCoef(int w ,int shift ,DentBase	*ABase 
							,int XList[],int MapXMin ,int Numb
							,double AvrD ,double BB)
{
	double	AB=0;
	int	*XListPointer=&XList[MapXMin];
	double	*WaveTablePointer=&ABase->WaveTable[w][shift];
	//for(int x=MapXMin;x<MapXMax;x++,s++){
	for(int m=0;m<Numb;m++){
		AB+=*(XListPointer++)*(*(WaveTablePointer++));
	}
	double	AvrS=ABase->WaveTableResult[w][shift][Numb].AvrS;
	double	Da	=ABase->WaveTableResult[w][shift][Numb].Da;

	double	D=Da*(BB-Numb*AvrD*AvrD);
	if(D<=0){
		return -100000000;
	}
	D=sqrt(D);
	double	K=AB-Numb*AvrS*AvrD;
	double	M=K/D;
	return M;
}
double	DentItem::DentBand::MakeCoefSkip(int w ,int shift ,DentBase	*ABase 
							,int XList[],int MapXMin ,int Numb
							,double SkipAvrD ,double SkipBB)
{
	double	AB=0;
	int	*XListPointer=&XList[MapXMin];
	double	*WaveTablePointer=&ABase->WaveTable[w][shift];
	//for(int x=MapXMin;x<MapXMax;x++,s++){
	for(int m=0;m<Numb;m+=4){
		AB+=*XListPointer*(*WaveTablePointer);
		XListPointer+=4;
		WaveTablePointer+=4;
	}
	int	SkipNumb=(Numb+3)>>2;
	double	SkipAvrS=ABase->WaveTableResult[w][shift][Numb].SkipAvrS;
	double	SkipDa	=ABase->WaveTableResult[w][shift][Numb].SkipDa;

	double	D=SkipDa*(SkipBB-SkipNumb*SkipAvrD*SkipAvrD);
	if(D<=0){
		return -100000000;
	}
	D=sqrt(D);
	double	K=AB-SkipNumb*SkipAvrS*SkipAvrD;
	double	M=K/D;
	return M;
}
void	DentItem::DentBand::DrawInHistogram(QImage &Pnt, QRgb Col, double ZoomRate ,int movx ,int movy)
{
	Area.Draw(mx,my,&Pnt,Col,ZoomRate,movx,movy);
}

//==============================================================================================

DentItem::DentItem(void)
{
	AVector		=NULL;
	XByte		=0;
	YLen		=0;
	ResultMaxD	=NULL;
}

DentItem::DentItem(FlexArea &area)
:AlgorithmItemPLITemplate<DentInLayer,DentInPage,DentBase>(area)
{
	AVector		=NULL;

	XByte		=0;
	YLen		=0;
	ResultMaxD	=NULL;
}
DentItem::~DentItem(void)
{
	if(ResultMaxD!=NULL){
		delete	[]ResultMaxD;
		ResultMaxD=NULL;
	}
}

DentItem &DentItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(*((DentItem *)&src));
	return *this;
}

void	DentItem::CopyThreshold(DentItem &src)
{
	GetThresholdW()->CopyFrom(*((DentThreshold *)src.GetThresholdR()));
}

void	DentItem::CopyThresholdOnly(DentItem &src)
{
	GetThresholdW()->CopyFrom(*((DentThreshold *)src.GetThresholdR()));
}

bool    DentItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;

	return true;
}
bool    DentItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;

	return true;
}

void	DentItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((DentItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((DentItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((DentItem *)Data));
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((DentItem *)Data)->GetLibID()){
			DentInPage	*Ly=dynamic_cast<DentInPage *>(GetParentInPage());
			UndoElement<DentInPage>	*UPointer=new UndoElement<DentInPage>(Ly,&DentInPage::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			DentItem *src=(DentItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

void	DentItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	DentItem	*ASrc=dynamic_cast<DentItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((DentBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
	}
}
void	DentItem::CopyArea(DentItem &src)
{
	SetArea(src.GetArea());
}

static	int	Mergin=8;

ExeResult	DentItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	int	BandWidth=GetThresholdR()->BandWidth;

	DentBandPack.RemoveAll();
	if(BandWidth>0){
		for(int y=GetArea().GetMinY();y<GetArea().GetMaxY();y+=BandWidth/2){
			DentBand	*b=new DentBand(this);
			b->Area=GetArea();
			b->Area.ClipArea(GetArea().GetMinX(),y,GetArea().GetMaxX(),y+BandWidth);
			
			DentBandPack.AppendList(b);	
		}
	}
	for(DentBand *b=DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
		b->ExecuteInitialAfterEdit(EInfo);
	}

	XByte	=(GetArea().GetWidth()+7)/8;
	YLen	=GetArea().GetHeight();

	ResultMapXLen	=GetArea().GetWidth();
	ResultMapYLen	=GetArea().GetHeight();
	if(ResultMaxD!=NULL){
		delete	[]ResultMaxD;
	}
	ResultMaxD		=new double[ResultMapYLen];


	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

ExeResult	DentItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	for(DentBand *b=DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
		b->ExecuteStartByInspection();
	}
	//MatrixBuffClear(BitMap		,0 ,XByte,YLen);
	//MatrixBuffClear(DarkBitMap	,0 ,XByte,YLen);

	for(int y=0;y<ResultMapYLen;y++){
		ResultMaxD[y]=-1;
		WaveLenList[y]=-1;
	}
	return _ER_true;
}

static	int	DbgY=4132;

ExeResult	DentItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPLI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

	if(GetID()==DbgID)
		DbgNumer++;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

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

	ResultDx =mx;
	ResultDy =my;
	ResultMaxNGSize=0;
	const	DentThreshold	*RThr=GetThresholdR();
	int	Error=1;
	ImageBuffer &IBuff=GetTargetBuff();
	DentBand *b;
	#pragma omp parallel
	#pragma omp single private(b)
	for(b=DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
		#pragma omp task
		{
			if(b->Area.GetMinY()<=DbgY && DbgY<b->Area.GetMaxY())
				DbgNumer++;

			b->ExecuteProcessing(IBuff);
		}
	}
	int	TmpWaveLenList[WaveTableLen];
	TmpWaveLenList[0]=-1;
	TmpWaveLenList[1]=-1;
	TmpWaveLenList[ResultMapYLen-2]=-1;
	TmpWaveLenList[ResultMapYLen-1]=-1;
	for(int y=2;y<ResultMapYLen-2;y++){
		int	Dim[5];
		Dim[0]=WaveLenList[y-2];
		Dim[1]=WaveLenList[y-1];
		Dim[2]=WaveLenList[y  ];
		Dim[3]=WaveLenList[y+1];
		Dim[4]=WaveLenList[y+2];
		bool	Changed;
		do{
			Changed=false;
			for(int i=0;i<4;i++){
				if(Dim[i]<Dim[i+1]){
					swap(Dim[i],Dim[i+1]);
					Changed=true;
				}
			}
		}while(Changed==true);
		TmpWaveLenList[y]=Dim[2];
	}

	for(int y=0;y<ResultMapYLen;y++){
		ResultMaxD[y]=TmpWaveLenList[y];	//*ResultMaxD[y];
	}

	for(int y=2;y<ResultMapYLen-1;y++){
		if((ResultMaxD[y-2]-ResultMaxD[y  ]>RThr->MaxDiffCoef)
		&& (ResultMaxD[y-2]-ResultMaxD[y+1]>RThr->MaxDiffCoef)
		&& ResultMaxD[y]>=0){
			int	Index1=y;
			int	Index2=y;
			for(int n=y+1;n<(ResultMapYLen-1);n++){
				if((ResultMaxD[y-2]-ResultMaxD[n  ]<RThr->MaxDiffCoef)
				&& (ResultMaxD[y-2]-ResultMaxD[n+1]<RThr->MaxDiffCoef)
				&& (ResultMaxD[n  ]-ResultMaxD[n-2]>RThr->MaxDiffCoef)
				&& (ResultMaxD[n+1]-ResultMaxD[n-2]>RThr->MaxDiffCoef)
				&& ResultMaxD[n]>0){
					Index2=n;
					break;
				}
				if(ResultMaxD[n]<0){
					Index2=99999999;
					break;
				}
			}
			int	NGSize=Index2-Index1;
			if(RThr->MinNGSize<=NGSize && NGSize<RThr->MaxNGSize){
				int	NGY=GetArea().GetMinY()+(Index1+Index2)/2;
				int IndexStart ,IndexEnd;
				GetArea().FindIndex(NGY,IndexStart ,IndexEnd);
				int	NGX=(GetArea().GetFLineLeftX((IndexStart+IndexEnd)/2)
						+GetArea().GetFLineRightX((IndexStart+IndexEnd)/2))/2;


				AlignmentPacket2D	V;
				V.PosXOnTarget=NGX;
				V.PosYOnTarget=NGY;
				V.ShiftX=0;
				V.ShiftY=0;
				GetAlignmentForProcessing(V);
				int	wmx=V.ShiftX;
				int	wmy=V.ShiftY;

				ResultPosList	*R=new ResultPosList(NGX,NGY,wmx-mx,wmy-my);
				R->result	=0x10000;
				R->NGSize	=NGSize;
				ResultMaxNGSize=NGSize;
				Res->AddPosList(R);
				Error=2;
				y=Index2;
			}
		}
	}

	Res->SetAlignedXY(mx,my);
	Res->SetError(Error);

	ExeResult	Ret=_ER_true;

	return Ret;
}

void	DentItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DentDrawAttr	*BAttr=dynamic_cast<DentDrawAttr *>(Attr);
	if(BAttr!=NULL){

		QColor	SavedColor;
		SavedColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	BAttr->NormalColor=BAttr->BlockColor0;	break;
			case 1:	BAttr->NormalColor=BAttr->BlockColor1;	break;
			case 2:	BAttr->NormalColor=BAttr->BlockColor2;	break;
			case 3:	BAttr->NormalColor=BAttr->BlockColor3;	break;
			case 4:	BAttr->NormalColor=BAttr->BlockColor4;	break;
			case 5:	BAttr->NormalColor=BAttr->BlockColor5;	break;
			case 6:	BAttr->NormalColor=BAttr->BlockColor6;	break;
			case 7:	BAttr->NormalColor=BAttr->BlockColor7;	break;
		}
		if(BAttr->Master==true){
			AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,BAttr);
		}
		else{
			AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx+ResultDx ,movy+ResultDy ,ZoomRate ,BAttr);
		}
		BAttr->NormalColor=SavedColor;
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}


void	DrawBitImageOnlyMap(QImage &Pnt, const BYTE **Src ,int XLen ,int XByte ,int YLen
					,int movx ,int movy ,double ZoomRate
					,int OffsetX ,int OffsetY
					,const QColor &Col)
{
	double	IZoomRate=1.0/ZoomRate;
	int64	AddX=(int64)(0x100000000*IZoomRate);
	DWORD	C=(DWORD)Col.rgba();
	int	YNumb=Pnt.height();
	int	XNumb=Pnt.width();

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			DWORD	*d=(DWORD *)Pnt.scanLine(y);
			int		ry= -movy+OffsetY+y/ZoomRate;
			if((0<=ry) && (ry<YLen)){
				int	x=0;
				uint64	mx=0;
				if((OffsetX-movx)<0){
					for(;x<XNumb;x++){
						if((((int)(mx>>32))+OffsetX-movx)>=0){
							break;
						}
						d++;
						mx+=AddX;
					}
				}
				const BYTE	*s=Src[ry];
				for(;x<XNumb;x++){
					if((mx>>32)+OffsetX-movx>=XLen){
						break;
					}
					int	kx=OffsetX-movx+(mx>>32);
					if((*(s+(kx>>3)) & (0x80>>(kx&7)))!=0){
						*d=C;
					}
					d++;
					mx+=AddX;
				}
			}
		}
	}
}

void	DentItem::MakeImageMap(QImage &IData ,int MovX ,int MovY ,double ZoomRate
								,int dx, int dy)
{
	int	Height	=IData.height();
	int	Width	=IData.width();
	for(int y=0;y<Height;y++){
		int Gy=y/ZoomRate-MovY;
		int	Y=Gy-dy;
		if(Y<0 || ResultMapYLen<=Y)
			continue;
		for(DentItem::DentBand *b=DentBandPack.GetFirst();b!=NULL;b=b->GetNext()){
			int	IndexStart,IndexEnd;
			//if(b->Area.FindIndex(Gy-b->ResultDy+ResultDy,IndexStart,IndexEnd)>0){
			if(b->Area.FindIndex(Gy-b->ResultDy,IndexStart,IndexEnd)>0){
				int	x1=b->Area.GetFLineLeftX (IndexStart)+b->ResultDx-dx;	//-ResultDx
				int	x2=b->Area.GetFLineRightX(IndexStart)+b->ResultDx-dx;	//-ResultDx
				QRgb	*d=(QRgb *)IData.scanLine(y);
				BYTE	s=Clipping(ResultMaxD[Y]*255/WaveCount,0.0,255.0);
				for(int x=0;x<Width;x++,d++){
					int	X=x/ZoomRate-MovX-dx;
					if(X<x1 || x2<=X)
						continue;
					*d=qRgba(s,0,0,128);
				}
			}
		}
	}
}

void	DentItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		//if(Res.IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			//if(Res.IsOk()==false){
			MakeImageMap(IData ,MovX ,MovY ,ZoomRate
					,GetArea().GetMinX(), GetArea().GetMinY());

		//}
	//}
	}
}

void	DentItem::MoveForAlignment(void)
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
	MoveTo(mx,my);
}
