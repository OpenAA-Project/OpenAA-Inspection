#include "XGerberAperture.h"
#include "GerberFast.h"
#include "XGerberFast.h"
#include "XGeneralFunc.h"
#include "XGeneralFunc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "XImageProcess.h"
#include "XFlexAreaImage.h"
#include "XGerberFastLibrary.h"
#include "XCrossObj.h"
#include "XPointer.h"
#include "XGerberFastPacket.h"
#include <omp.h>
#include "swap.h"
#include <float.h>

int	DbgXn=0;
int	DbgYn=0;
int	DbgXY;
extern	int	DbgID;
extern	int	DbgPage	;
int	DbgIDMode=0;
int	DbgGerberID1=13912;
int	DbgGerberID2=72881;
int	DbgGerber=0;

int	DbgX=36831-35944,DbgY=147246;
int	DbgGerberID=32515;	//3646


extern	char	*sRoot;
extern	char	*sName;


AutomatchingBox::AutomatchingBox(void)
{	
	Parent=NULL;
	X1=0;
	Y1=0;
	X2=0;
	Y2=0;
	AdoptedLayer=0;

	ResultMatch	=-1;
	ResultDx	=0;
	ResultDy	=0;
	Enabled	=true;
	Adopted	=true;
	AreaDots	=0.0;

	CalcDx=CalcDy=0;
	DoneAutoMatch=false;
}

void	AutomatchingBox::GetCenter(int &cx ,int &cy)
{
	cx=(X1+X2)/2;
	cy=(Y1+Y2)/2;
}
void	AutomatchingBox::GetCenter(double &cx ,double &cy)
{
	cx=(X1+X2)/2.0;
	cy=(Y1+Y2)/2.0;
}
bool	AutomatchingBox::IsInclude(int x,int y)
{
	if(X1<=x && x<=X2 && Y1<=y && y<Y2)
		return true;
	return false;
}

void	AutomatchingBox::Draw(QPainter &Pnt ,QImage &pnt ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	GerberFastDrawAttr	*GAttr=(GerberFastDrawAttr *)Attr;

	int	Lx1=(X1+movx)*ZoomRate;
	int	Ly1=(Y1+movy)*ZoomRate;
	int	Lx2=(X2+movx)*ZoomRate;
	int	Ly2=(Y2+movy)*ZoomRate;

	if(Lx2<0 || Lx1>pnt.width() || Ly2<0 || Ly1>pnt.height())
		return;
	Pnt.setPen(Qt::red);
	Pnt.drawLine(Lx1,Ly1,Lx2,Ly1);
	Pnt.drawLine(Lx2,Ly1,Lx2,Ly2);
	Pnt.drawLine(Lx2,Ly2,Lx1,Ly2);
	Pnt.drawLine(Lx1,Ly2,Lx1,Ly1);

	QRgb	Col=qRgba(128,255,0,128);

	for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(0,0,&pnt,Col,ZoomRate,movx,movy);
	}
	if(GAttr->DrawAutoMatchingImage==true){
		for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
			a->DrawImage(0,0,&pnt 
						,ZoomRate ,movx ,movy
						,true,true,true
						,0x80);
		}
	}

	int	cx,cy;
	GetCenter(cx,cy);
	cx=(cx+movx)*ZoomRate;
	cy=(cy+movy)*ZoomRate;

	if(Adopted==true && Enabled==true)
		Pnt.setPen(Qt::cyan);
	else if(Adopted==false && Enabled==true)
		Pnt.setPen(Qt::magenta);
	else if(Adopted==true && Enabled==false)
		Pnt.setPen(Qt::yellow);
	else
		Pnt.setPen(Qt::red);

	char	buff[100];
	sprintf(buff,/**/"Xn,Yn=%d,%d",XAddr,YAddr);
	Pnt.drawText(cx,cy,buff);
	if(Adopted==true)
		sprintf(buff,/**/"Adopted : %.2lf",ResultMatch);
	else
		sprintf(buff,/**/"Not adopted");
	Pnt.drawText(cx,cy+16,buff);
	sprintf(buff,/**/"Dx,Dy=%d ,%d",ResultDx,ResultDy);
	Pnt.drawText(cx,cy+32,buff);

	sprintf(buff,/**/"CalcDx,CalcDy=%d ,%d",CalcDx,CalcDy);
	Pnt.drawText(cx,cy+48,buff);
}

void	AutomatchingBox::ExpandBitImage(BYTE **SrcImage ,BYTE Col ,int XByte,int YLen)
{
	for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
		a->ExpandBitImage(SrcImage ,Col ,XByte,YLen);
		FlexAreaImageListCoeff	*ac=dynamic_cast<FlexAreaImageListCoeff *>(a);
		if(ac!=NULL){
			ac->MakeSum();
		}
	}
}

double	AutomatchingBox::CalcSelfCoef(BYTE **ImagingBmp,int XLen ,int YLen ,int dx,int dy)
{
	int	MatchDot=0;
	int	TotalDot=0;
	for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
		int Sep=a->GetFLineLen()/10;
		if(Sep==0)
			Sep=1;
		if(Sep>20)
			Sep=20;
		for(int i=0;i<a->GetFLineLen();i+=Sep){
			int	y=a->GetFLineAbsY(i);
			int	x1=a->GetFLineLeftX(i);
			int	Numb=a->GetFLineNumb(i);
			int	Y=y+dy;
			if(Y<0 || Y>=YLen)
				continue;
			BYTE	*s=ImagingBmp[y];
			BYTE	*d=ImagingBmp[Y];
			int	X1=x1+dx;
			int	x=x1;
			int	X=X1;
			if(X<0){
				Numb+=X;
				x1-=X;
				X=0;
			}
			if(Numb<0)
				Numb=0;
			if((X+Numb)>=XLen){
				Numb=XLen-X;
			}
			if(Numb<0)
				Numb=0;

			int	Isolation=1;
			if(Numb<5)
				Isolation=2;
			else if(Numb<10)
				Isolation=3;
			else if(Numb<20)
				Isolation=5;
			else
				Isolation=10;

			for(int k=0;k<Numb;k+=Isolation,x+=Isolation,X+=Isolation){
				BYTE	ps=GetBmpBitOnY(s,x);
				BYTE	pd=GetBmpBitOnY(d,X);
				if((ps==0 && pd==0) || (ps!=0 && pd!=0)){
					MatchDot++;
				}
				TotalDot++;
			}
			
		}
	}
	if(TotalDot==0)
		return 0;
	return ((double)MatchDot)/(double)TotalDot;
}

double	AutomatchingBox::SelfSearch(BYTE **ImagingBmp,int XLen ,int YLen ,int SearchAreaInMatching,int Farther)
{
	double	MaxD=0;
	int		IndexX=0;
	int		IndexY=0;
	int		N=(SearchAreaInMatching*2+1)/4;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<N;i++){
		//for(int dx=-SearchAreaInMatching;dx<=SearchAreaInMatching;dx+=4){
			int	dx=i*4-SearchAreaInMatching;
			for(int dy=-SearchAreaInMatching;dy<=SearchAreaInMatching;dy+=4){
				if(abs(dx)<Farther && abs(dy)<Farther)
					continue;
				double	d=CalcSelfCoef(ImagingBmp,XLen ,YLen ,dx,dy);
				#pragma	omp	critical
				{
					if(d>MaxD){
						IndexX=dx;
						IndexY=dy;
						MaxD=d;
					}
				}
			}
		}
	}
	MaxD=0;
	int		Mx=0;
	int		My=0;
	for(int dx=(-3+IndexX);dx<=(3+IndexX);dx++){
		for(int dy=(-3+IndexY);dy<=(3+IndexY);dy++){
			if(abs(dx)<Farther && abs(dy)<Farther)
				continue;
			double	d=CalcSelfCoef(ImagingBmp,XLen ,YLen ,dx,dy);
			if(d>MaxD){
				Mx=dx;
				My=dy;
				MaxD=d;
			}
		}
	}
	return MaxD;
}

static	int	DSortFunc(const void *a ,const void *b)
{
	double	*ap=(double *)a;
	double	*bp=(double *)b;
	if(*ap>*bp)
		return 1;
	if(*ap<*bp)
		return -1;
	return 0;
}

double	AutomatchingBox::ExecuteMatching(int &dx ,int &dy)
{
	dx=0;
	dy=0;
	if(Parent==NULL)
		return 0.0;
	if(DbgXn==XAddr && DbgYn==YAddr){
		DbgXY++;
	}
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();
	int		SearchAreaInMatching	=Base->SearchAreaInMatching;
	ImageBuffer *ImageList[100];
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return 0;

	double	MaxD=0.0;
	int		IndexX=0,IndexY=0;
	int		Numb=SearchAreaInMatching;

	double	*DDim=new double[SearchAreaInMatching*SearchAreaInMatching];

	#pragma omp parallel
	{
		#pragma omp for
		//for(int my=-SearchAreaInMatching;my<=SearchAreaInMatching;my+=2){
		for(int i=0;i<Numb;i++){
			int	my=i*2-SearchAreaInMatching;
			for(int j=0;j<SearchAreaInMatching;j++){
			//for(int mx=-SearchAreaInMatching;mx<=SearchAreaInMatching;mx+=2){
				int	mx=j*2-SearchAreaInMatching;
				double	D[1000];
				int		DNumb=0;
				for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
					FlexAreaImageListCoeff	*ACoef=dynamic_cast<FlexAreaImageListCoeff	*>(a);
					if(ACoef!=NULL){
						double	d=ACoef->CalcCoeff(mx	,my	,*ImageList[AdoptedLayer]);
						D[DNumb]=fabs(d);
						DNumb++;
						if(DNumb>=sizeof(D)/sizeof(D[0])){
							break;
						}
					}
				}
				double	AvrD=0;
				if(DNumb>5){
					QSort(D,DNumb,sizeof(double),DSortFunc);
					double	SumD=0;
					int		SumDNumb=0;
					//for(int j=DNumb/4;j<3*DNumb/4;j++){
					for(int j=0;j<DNumb;j++){
						SumD+=D[j];
						SumDNumb++;
					}
					AvrD=SumD/SumDNumb;
				}
				else{
					double	SumD=0;
					int		SumDNumb=0;
					for(int j=0;j<DNumb;j++){
						SumD+=D[j];
						SumDNumb++;
					}
					AvrD=SumD/SumDNumb;
				}
				DDim[i*SearchAreaInMatching+j]=AvrD;
				/*
				#pragma omp critical
				{
					if(MaxD<AvrD){
						MaxD=AvrD;
						IndexX=mx;
						IndexY=my;
					}
				}
				*/
			}
		}
	}
	for(int i=0;i<SearchAreaInMatching;i++){
		for(int j=0;j<SearchAreaInMatching;j++){
			double	AvrD=DDim[i*SearchAreaInMatching+j];
			if(MaxD<AvrD){
				int	my=i*2-SearchAreaInMatching;
				int	mx=j*2-SearchAreaInMatching;
				MaxD=AvrD;
				IndexX=mx;
				IndexY=my;
			}
		}
	}
	delete	[]DDim;

	MaxD=0.0;
	for(int my=-2;my<=2;my++){
		for(int mx=-2;mx<=2;mx++){
			double	*D=new double[100000];
			int		DNumb=0;
			for(FlexAreaImageList *a=MatchingZones.GetFirst();a!=NULL;a=a->GetNext()){
				FlexAreaImageListCoeff	*ACoef=dynamic_cast<FlexAreaImageListCoeff	*>(a);
				if(ACoef!=NULL){
					double	d=ACoef->CalcCoeff(mx	,my	,*ImageList[AdoptedLayer]);
					D[DNumb]=fabs(d);
					DNumb++;
				}
			}
			double	AvrD=0.0;
			if(DNumb>5){
				QSort(D,DNumb,sizeof(double),DSortFunc);
				double	SumD=0;
				int		SumDNumb=0;
				for(int j=DNumb/4;j<3*DNumb/4;j++){
					SumD+=D[j];
					SumDNumb++;
				}
				AvrD=SumD/SumDNumb;
			}
			else{
				double	SumD=0;
				int		SumDNumb=0;
				for(int j=0;j<DNumb;j++){
					SumD+=D[j];
					SumDNumb++;
				}
				AvrD=SumD/SumDNumb;
			}
			if(MaxD<AvrD){
				MaxD=AvrD;
				dx=IndexX+mx;
				dy=IndexY+my;
			}
			delete	[]D;
		}
	}
	return MaxD;
}

void	AutomatchingBox::Clear(void)
{
	X1=Y1=X2=Y2=0;
	AdoptedLayer=-1;

	ResultMatch	=0;
	ResultDx=ResultDy=0;
	Adopted	=false;

	MatchingZones.RemoveAll();
}

bool	AutomatchingBox::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	if(::Save(f,AdoptedLayer)==false)
		return false;

	if(::Save(f,XAddr)==false)
		return false;
	if(::Save(f,YAddr)==false)
		return false;
	if(::Save(f,ResultMatch)==false)
		return false;
	if(::Save(f,ResultDx)==false)
		return false;
	if(::Save(f,ResultDy)==false)
		return false;
	if(::Save(f,Adopted)==false)
		return false;
	if(::Save(f,AreaDots)==false)
		return false;
	if(::Save(f,CalcDx)==false)
		return false;
	if(::Save(f,CalcDy)==false)
		return false;

	if(MatchingZones.Save(f)==false)
		return false;

	return true;
}
bool	AutomatchingBox::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	if(::Load(f,AdoptedLayer)==false)
		return false;

	if(::Load(f,XAddr)==false)
		return false;
	if(::Load(f,YAddr)==false)
		return false;
	if(::Load(f,ResultMatch)==false)
		return false;
	if(::Load(f,ResultDx)==false)
		return false;
	if(::Load(f,ResultDy)==false)
		return false;
	if(::Load(f,Adopted)==false)
		return false;
	if(::Load(f,AreaDots)==false)
		return false;
	if(::Load(f,CalcDx)==false)
		return false;
	if(::Load(f,CalcDy)==false)
		return false;

	if(MatchingZones.Load(f)==false)
		return false;

	return true;
}

//==================================================================================

bool	HasBit(BYTE **Image,int XByte,int YLen,int x1,int y1,int x2,int y2)
{
	x1=max(0,x1);
	x2=min(XByte*8,x2);
	y1=max(0,y1);
	y2=min(YLen,y2);
	for(int y=y1;y<y2;y++){
		BYTE	*s=Image[y];
		for(int x=x1;x<x2;x++){
			if(GetBmpBitOnY(s,x)!=0){
				return true;
			}
		}
	}
	return false;
}

static	int	SortAutomatchingBoxFunc(const void *a ,const void *b)
{
	AutomatchingBox	*pa=((AutomatchingBox **)a)[0];
	AutomatchingBox	*pb=((AutomatchingBox **)b)[0];
	if(pa->AreaDots>pb->AreaDots)
		return 1;
	else if(pa->AreaDots<pb->AreaDots)
		return -1;
	return 0;
}

void	GerberFastInPage::MakeAutoMatchingBox(bool UsageLayer ,int UsageLayerID
											, bool RemoveShiftable
											, BoolList &ButtonsToRemoveShiftableLayer ,IntList &OperateCompositeIDList
											, int32 MinDotsForAutoMatching
											, int32 ShrinkDotForAutoMatchingArea)
{
	CreateImagingBmpBuff();
	MatrixBuffClear	(ImagingBmp ,0,ImagingBmpXByte ,ImagingBmpYLen);

	GerberFastDrawAttr	Attr;
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	int	N=0;
	if(UsageLayer==true && UsageLayerID>=0){
		Attr.ShownFileID.Add(UsageLayerID);
	}
	else{
		Attr.ShownCompositeID.Add(UsageLayerID);
	}

	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2=MakeMatrixBuff(XByte ,YLen);
	BYTE	**SrcImage =MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
	if(UsageLayer==true && UsageLayerID>=0){
		GerberFileLayer	*F=FindFileLayer(UsageLayerID);
		if(F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						Item->MakeImage(ImagingBmp,0,0,XByte,YLen);
					}
				}
			}
		}
	}
	else if(UsageLayerID>=0){
		int	CompositeID=UsageLayerID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						Item->MakeImage(ImagingBmp,0,0,XByte,YLen);
					}
				}
			}
		}
	}
	if(ShrinkDotForAutoMatchingArea>0){
		GetLayersBase()->ThinAreaN(ImagingBmp,TmpImage2,XByte,YLen,ShrinkDotForAutoMatchingArea);
	}
	else{
		GetLayersBase()->FatAreaN (ImagingBmp,TmpImage2,XByte,YLen,ShrinkDotForAutoMatchingArea);
	}

	MatrixBuffCopy	(TmpImage,XByte,YLen
					,(const BYTE **)ImagingBmp,XByte,YLen);
	MatrixBuffCopy	(SrcImage,XByte,YLen
					,(const BYTE **)ImagingBmp,XByte,YLen);

	GetLayersBase()->FatAreaN (ImagingBmp,TmpImage2,XByte,YLen,GBase->AutoMatchingOutsideDot);
	GetLayersBase()->ThinAreaN(TmpImage  ,TmpImage2,XByte,YLen,GBase->AutoMatchingInsideDot);

	MatrixBuffNotAnd(ImagingBmp,(const BYTE **)TmpImage ,XByte,YLen);

	if(RemoveShiftable==true){
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		//GerberFastLibrary	*Lib=(GerberFastLibrary *)GBase->GetLibraryContainer()->CreateNew();
		MatrixBuffClear	(TmpImage2 ,0,XByte ,YLen);
		N=0;
		for(BoolClass *b=ButtonsToRemoveShiftableLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
			GerberFileLayer	*F=FileLayerList[N];
			if(b->GetValue()==true && F!=NULL){
				AlgorithmLibraryLevelContainer	LLib(Container);
				if(Container->GetLibrary(F->LibID,LLib)==true){
					GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
					MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
						if(Item!=NULL){
							if(Item->GetFileLayerID()==F->GetFileLayerID()){
								Item->MakeImage(TmpImage,0,0,XByte,YLen);
							}
						}
					}
					for(int dy=-ALib->MaxShiftDot;dy<=ALib->MaxShiftDot;dy++){
						int	XSize=ceil(sqrt((double)ALib->MaxShiftDot*ALib->MaxShiftDot- dy*dy));
						for(int dx=-XSize;dx<=XSize;dx++){
							MatrixBuffBitOr	(TmpImage2,TmpImage,XLen ,YLen
											,dx,dy);
						}
					}
				}
			}
		}
		for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
			int	CompositeID=b->GetValue();
			GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
			if(CL!=NULL){
				GerberCompositeDefLayer	*A=GBase->CompositeDef.Search(CompositeID);
				AlgorithmLibraryLevelContainer	LLib(Container);
				if(A!=NULL && Container->GetLibrary(A->LibID,LLib)==true){
					GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(LLib.GetLibrary());
					MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
					for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
						GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
						if(Item!=NULL){
							if(Item->GetCompositeID()==CompositeID){
								Item->MakeImage(TmpImage,0,0,XByte,YLen);
							}
						}
					}
					for(int dy=-ALib->MaxShiftDot;dy<=ALib->MaxShiftDot;dy++){
						int	XSize=ceil(sqrt((double)ALib->MaxShiftDot*ALib->MaxShiftDot- dy*dy));
						for(int dx=-XSize;dx<=XSize;dx++){
							MatrixBuffBitOr	(TmpImage2,TmpImage,XLen ,YLen
											,dx,dy);
						}
					}
				}
			}
		}
		MatrixBuffNotAnd(ImagingBmp,(const BYTE **)TmpImage2,XByte ,YLen);
	}
	//ガーバーの全エリア範囲を取得
	int		X1 ,Y1 ,X2 ,Y2;
	if(GetOccupiedItemXY(X1 ,Y1 ,X2 ,Y2)==true){
		int	MinX=max(0,X1-100);
		int	MinY=max(0,Y1-100);
		int	MaxX=min(GetDotPerLine(),X2+100);
		int	MaxY=min(GetMaxLines(),Y2+100);

		if(MinX<MaxX && MinY<MaxY
		&& CheckOverlapRectRect(MinX, MinY, MaxX, MaxY
							,0, 0, GetDotPerLine(), GetMaxLines())==true){

			//小矩形に探索ビット領域が含まれているか、その小矩形個数を数える
			ABoxXNum=10;
			ABoxYNum=10;
			int	XDot=(MaxX-MinX)/ABoxXNum;
			int	YDot=(MaxY-MinY)/ABoxYNum;
			if(XDot/YDot>=2){
				int	N=XDot/YDot;
				ABoxYNum=(ABoxYNum+N-1)/N;
				if(ABoxYNum>10)
					ABoxYNum=10;
				YDot=(MaxY-MinY)/ABoxYNum;
			}
			else if(YDot/XDot>=2){
				int	N=YDot/XDot;
				ABoxXNum=(ABoxXNum+N-1)/N;
				if(ABoxXNum>10)
					ABoxXNum=10;
				XDot=(MaxX-MinX)/ABoxXNum;
			}

			int	AreaCount=0;
			for(int xn=0;xn<ABoxXNum;xn++){
				for(int yn=0;yn<ABoxYNum;yn++){
					int	mx1=MinX+xn*XDot;
					int	my1=MinY+yn*YDot;
					int	mx2=mx1+XDot;
					int	my2=my1+YDot;
					if(HasBit(ImagingBmp,XByte,YLen,mx1,my1,mx2,my2)==true){
						AreaCount++;
					}
				}
			}
			if(AreaCount<ABoxXNum*ABoxYNum*0.4){
				ABoxXNum=5;
				ABoxYNum=5;
				XDot=(MaxX-MinX)/ABoxXNum;
				YDot=(MaxY-MinY)/ABoxYNum;
			}

			int	aXLen =XDot+50;
			int	aXByte=(aXLen+7)/8;
			int	aYLen =YDot+50;
			BYTE	**aBmp=MakeMatrixBuff(aXByte,aYLen);
	
			ImageBuffer *ImageList[100];
			if(GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
				GetMasterBuffList(ImageList);
			else if(GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
				GetTargetBuffList(ImageList);
			else
				return;

			for(int xn=0;xn<ABoxXNum;xn++){
				for(int yn=0;yn<ABoxYNum;yn++){
					MatrixBuffClear	(aBmp ,0,aXByte,aYLen);
					ABox[yn][xn].MatchingZones.RemoveAll();
					ABox[yn][xn].SetParent(this);
					ABox[yn][xn].X1=MinX+xn*XDot;
					ABox[yn][xn].Y1=MinY+yn*YDot;
					ABox[yn][xn].X2=ABox[yn][xn].X1+XDot;
					ABox[yn][xn].Y2=ABox[yn][xn].Y1+YDot;
					ABox[yn][xn].XAddr	=xn;
					ABox[yn][xn].YAddr	=yn;
					MatrixBuffPickupFromWindow  (aBmp	,aXLen,aYLen
										,ImagingBmp ,XLen ,YLen
										,ABox[yn][xn].X1-25,ABox[yn][xn].Y1-25
										,ABox[yn][xn].X2+25,ABox[yn][xn].Y2+25);
					ABox[yn][xn].AreaDots=0.0;
					PureFlexAreaListContainer FPack;
					PickupFlexArea(aBmp ,aXByte ,aXLen,aYLen ,FPack);
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->GetPatternByte()<MinDotsForAutoMatching){
							ABox[yn][xn].AdoptedLayer	=0;
							continue;
						}
						ABox[yn][xn].AreaDots+=f->GetPatternByte();
						FlexAreaImageListCoeff	*a=new FlexAreaImageListCoeff();
						f->MoveToNoClip(ABox[yn][xn].X1-25,ABox[yn][xn].Y1-25);

						double	MaxD=0;
						int		MaxLayer=0;
						if(GetLayerNumb()>=2){
							for(int layer=0;layer<GetLayerNumb();layer++){
								double	D=ImageList[layer]->GetV(
												 ABox[yn][xn].X1-25,ABox[yn][xn].Y1-25
												,ABox[yn][xn].X2+25,ABox[yn][xn].Y2+25);
								if(D>MaxD){
									MaxD=D;
									MaxLayer=layer;
								}
							}
						}
						ABox[yn][xn].AdoptedLayer	=MaxLayer;
						a->Set(*f,*ImageList[MaxLayer]);
						ABox[yn][xn].MatchingZones.AppendList(a);
					}
				}
			}
			AutomatchingBox	*PointDim[10*10];
			int	PointDimNumb=0;
			for(int xn=0;xn<ABoxXNum;xn++){
				for(int yn=0;yn<ABoxYNum;yn++){
					if(ABox[yn][xn].AreaDots==0.0)
						continue;
					double	SelfD=ABox[yn][xn].SelfSearch(SrcImage,XLen ,YLen ,GBase->SearchAreaInMatching*2,10);
					if(SelfD>GBase->ThresholdSelfMatch){
						ABox[yn][xn].Enabled=false;
					}
					else
						ABox[yn][xn].Enabled=true;
					PointDim[PointDimNumb]=&ABox[yn][xn];
					PointDimNumb++;
				}
			}
			/*
			//極?に?ッ?ング領域の面積の小さなものと、非常に大きなものを除外する
			if(PointDimNumb>20){
				QSort(PointDim,PointDimNumb,sizeof(AutomatchingBox	*),SortAutomatchingBoxFunc);
				for(int i=0;i<PointDimNumb/3;i++){
					PointDim[i]->AreaDots=0.0;
					PointDim[i]->MatchingZones.RemoveAll();
				}
				for(int i=PointDimNumb-1;i>4*PointDimNumb/5;i--){
					PointDim[i]->AreaDots=0.0;
					PointDim[i]->MatchingZones.RemoveAll();
				}
			}
			*/

			//ガ?バ?デ??から、２値画像にする
			for(int xn=0;xn<ABoxXNum;xn++){
				for(int yn=0;yn<ABoxYNum;yn++){
					ABox[yn][xn].ExpandBitImage(SrcImage ,0xFF,XByte,YLen);
				}
			}
			DeleteMatrixBuff(aBmp ,aYLen);
		}
	}

	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
	DeleteMatrixBuff(SrcImage ,YLen);
}

void	GerberFastInPage::ClearAutoMatchInfo(void)
{
	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			ABox[yn][xn].Clear();
		}
	}
	ABoxXNum=0;
	ABoxYNum=0;
}

AlignmentGeneralPipeInfo::AlignmentGeneralPipeInfo(GerberFastInPage *parent)
	: GeneralPipeInfo(parent->GetParentBase())
	,Parent(parent)
{}
bool	AlignmentGeneralPipeInfo::RequireAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY)
{
	return Parent->GetAlignmentPosition(X ,Y ,AckX ,AckY);
}

void	GerberFastInPage::ExecuteMatching(void)
{
	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			if(ABox[yn][xn].Enabled==false){
				ABox[yn][xn].Adopted	=false;
			}
			else{
				int	dx,dy;
				ABox[yn][xn].ResultMatch	=ABox[yn][xn].ExecuteMatching(dx ,dy);
				ABox[yn][xn].ResultDx	=dx;
				ABox[yn][xn].ResultDy	=dy;
				if(ABox[yn][xn].ResultMatch==0.0)
					ABox[yn][xn].Adopted	=false;
				else
					ABox[yn][xn].Adopted	=true;
			}
		}
	}

	//3個区間の平均で、極?に異なるものを除外する
	for(int xn=1;xn<ABoxXNum-1;xn+=3){
		for(int yn=1;yn<ABoxYNum-1;yn+=3){
			double	Dx=0.0;
			double	Dy=0.0;
			int	Numb=0;
			for(int ix=-1;ix<=1;ix++){
				for(int iy=-1;iy<=1;iy++){
					if(ABox[yn+iy][xn+ix].Adopted==true){
						Dx+=ABox[yn+iy][xn+ix].ResultDx;
						Dy+=ABox[yn+iy][xn+ix].ResultDy;
						Numb++;
					}
				}
			}
			Dx/=Numb;
			Dy/=Numb;
			for(int ix=-1;ix<=1;ix++){
				for(int iy=-1;iy<=1;iy++){
					if(ABox[yn+iy][xn+ix].Adopted==true){
						double	L=hypot(ABox[yn+iy][xn+ix].ResultDx-Dx,ABox[yn+iy][xn+ix].ResultDy-Dy);
						if(L>10){
							ABox[yn+iy][xn+ix].Adopted=false;
						}
					}
				}
			}
		}
	}
	/*
	//最大移動矩?を除外
	double	MaxL=0;
	int	IndexX=0;
	int	IndexY=0;
	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			if(ABox[yn][xn].Adopted==true){
				double	L=hypot(ABox[yn][xn].ResultDx ,ABox[yn][xn].ResultDy);
				if(MaxL<L){
					MaxL=L;
					IndexX=xn;
					IndexY=yn;
				}
			}
		}
	}
	ABox[IndexY][IndexX].Adopted=false;

	//最小移動矩?を除外
	double	MinL=DBL_MAX;
	IndexX=0;
	IndexY=0;
	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			if(ABox[yn][xn].Adopted==true){
				double	L=hypot(ABox[yn][xn].ResultDx ,ABox[yn][xn].ResultDy);
				if(MinL>L){
					MinL=L;
					IndexX=xn;
					IndexY=yn;
				}
			}
		}
	}
	ABox[IndexY][IndexX].Adopted=false;
	*/
	ExecuteAllocateMatching();
}

void	GerberFastInPage::ExecuteAllocateMatching(void)
{
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	AutoInterpolation.RemoveAll();
	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			if(ABox[yn][xn].Adopted==true){
				int	cx,cy;
				ABox[yn][xn].GetCenter(cx,cy);
				AutoInterpolation.Add(cx,cy,ABox[yn][xn].ResultDx,ABox[yn][xn].ResultDy,xn,yn);
			}
		}
	}
	for(int i=0;i<100;i++){
		if(AMImagePoint[i].x==0.0 && AMImagePoint[i].y==0.0)
			break;
		AutoInterpolation.Add(AMCadPoint[i].x,AMCadPoint[i].y
							,AMImagePoint[i].x,AMImagePoint[i].y,-1,i);
	}

	AutoInterpolation.Build();

	for(int xn=0;xn<ABoxXNum;xn++){
		for(int yn=0;yn<ABoxYNum;yn++){
			double	cx,cy;
			ABox[yn][xn].GetCenter(cx,cy);
			double ResultX ,ResultY;
			if(AutoInterpolation.Calc(cx ,cy ,ResultX ,ResultY)==true){
				ABox[yn][xn].CalcDx=ResultX-cx;
				ABox[yn][xn].CalcDy=ResultY-cy;
				ABox[yn][xn].DoneAutoMatch=true;
			}
		}
	}

	UndoElement<GerberFastInPage>	*UPointer=new UndoElement<GerberFastInPage>(this,&GerberFastInPage::UndoAutoMatch);
	int32	UndoNumb=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(item!=NULL){
			UndoNumb++;
		}
	}
	::Save(UPointer->GetWritePointer(),UndoNumb);

	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(item!=NULL){
			double	cx,cy;
			item->GetCenter(cx,cy);
			::Save(UPointer->GetWritePointer(),item->GetID());
			item->Save(UPointer->GetWritePointer());
		}
	}
	AlgorithmItemPI	*a;
	//#pragma omp parallel
	//#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
	//	#pragma omp task
		{
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				if(item->GetID()==DbgID)
					DbgIDMode++;
				//double	cx,cy;
				//item->GetCenter(cx,cy);
				double	X1,Y1,X2,Y2;
				item->GetXY(X1,Y1,X2,Y2);
				if(CheckOverlapRectRect(X1,Y1,X2,Y2
										,(double)-GBase->AutoMatchingMerginDot, (double)-GBase->AutoMatchingMerginDot
										, (double)GetDotPerLine()+GBase->AutoMatchingMerginDot, (double)GetMaxLines()+GBase->AutoMatchingMerginDot)==true){
					GerberControlPoint CDim[10000];
					int	n=item->GetGerberControlPoint(CDim,10000);
					for(int i=0;i<n;i++){
						CDim[i].m=AutoInterpolation.Calc(CDim[i].SrcX,CDim[i].SrcY);
					}
					if(n>=0){
						item->TransformControlPoint(CDim,n);
					}
				}
			}
		}
	}
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
}
void	GerberFastInPage::ExecuteAllocateForOthers(void)
{
	QString OwnDLLRoot;
	QString OwnDLLName;
	GetParentBase()->GetAlgorithmRootName(OwnDLLRoot ,OwnDLLName);
	//Gerber以外のすべての要素を移動させる
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLRoot()==OwnDLLRoot && L->GetDLLName()==OwnDLLName)
			continue;
		AlignmentGeneralPipeInfo	Info(this);
		Info.Cmd	=GeneralPipeInfo::_GI_ReqToMoveByAlignment;
		AlgorithmBase	*Ab=L->GetInstance();
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(GetPage());
		if(Ap->PipeGeneration(Info)==false)
			continue;
	}
}

bool	GerberFastInPage::GetAlignmentPosition(double X ,double Y ,double &AckX ,double &AckY)
{
	double	*m=AutoInterpolation.Calc(X,Y);
	if(m!=NULL){
		AckX=m[0]*X + m[1]*Y + m[2];
		AckY=m[3]*X + m[4]*Y + m[5];
		return true;
	}
	return false;
}

void	GerberFastInPage::MakeShrinkImage(BYTE **TmpImage ,int ImageXLen ,int ImageYLen
										,double ShrinkRate
										,ImageBuffer &IBuff)
{
	MatrixBuffClear	(TmpImage ,0 ,ImageXLen ,ImageYLen);
	int	XLen=GetDotPerLine()*ShrinkRate;
	int	YLen=GetMaxLines()*ShrinkRate;
	double	Z=1.0/ShrinkRate;
	XLen=min(XLen,ImageXLen);
	YLen=min(YLen,ImageYLen);
	for(int y=0;y<YLen;y++){
		int	Y=y*Z;
		BYTE	*s=IBuff.GetY(Y);
		BYTE	*d=TmpImage[y];
		double	Mx=0;
		for(int x=0;x<XLen;x++){
			d[x] = s[(int)(Mx)];
			Mx+=Z;
		}
	}
}

void	GerberFastInPage::MakePattern(BYTE **TmpPattern ,int PatternXLen ,int PatternYLen
									,double ShrinkRate
									,int StartPointX ,int StartPointY
									,BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList)
{
	int	XLen=min(4000,PatternXLen);
	int	YLen=min(4000,PatternYLen);
	int	XNumb=(PatternXLen+XLen-1)/XLen;
	int	YNumb=(PatternYLen+YLen-1)/YLen;

	int	PatternXByte=(PatternXLen+7)/8;
	MatrixBuffClear	(TmpPattern ,0 ,PatternXByte ,PatternYLen);

	GerberFastDrawAttr	Attr;
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	int	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		if(b->GetValue()==true && FileLayerList[N]!=NULL){
			Attr.ShownFileID.Add(FileLayerList[N]->FileLayerID);
			Attr.LayerColor[N]=Qt::white;
		}
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		Attr.ShownCompositeID.Add(CompositeID);
		Attr.CompColor[CompositeID]=Qt::white;
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int yn=0;yn<YNumb;yn++){
			QImage	TmpImage(XLen,YLen,QImage::Format_ARGB32);
			for(int xn=0;xn<XNumb;xn++){
				TmpImage.fill(0);

				N=0;
				for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
					GerberFileLayer	*F=FileLayerList[N];
					if(b->GetValue()==true && F!=NULL){
						for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
							GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
							if(Item!=NULL){
								if(Item->GetFileLayerID()==F->GetFileLayerID()){
									a->Draw(TmpImage,(-xn*XLen+StartPointX)/ShrinkRate,(-yn*YLen+StartPointY)/ShrinkRate,ShrinkRate,&Attr);
								}
							}
						}
					}
				}	

				for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
					int	CompositeID=b->GetValue();
					GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
					if(CL!=NULL){
						GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
						for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
							GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
							if(Item!=NULL){
								if(Item->GetCompositeID()==CompositeID){
									a->Draw(TmpImage,(-xn*XLen+StartPointX)/ShrinkRate,(-yn*YLen+StartPointY)/ShrinkRate,ShrinkRate,&Attr);
								}
							}
						}
					}
				}
				
				for(int y=0;y<YLen;y++){
					QRgb	*s=(QRgb *)TmpImage.scanLine(y);
					int	Y=y+yn*YLen;
					if(Y>=PatternYLen)
						break;
					BYTE	*d=TmpPattern[Y];
					int	X=xn*XLen;
					int	XLenNumb=XLen;
					if((X+XLen)>=PatternXLen){
						XLenNumb=PatternXLen-X;
					}
					for(int x=0;x<XLenNumb;x++,X++){
						if(s[x]!=0)
							SetBmpBitOnY1(d,X);
						else
							SetBmpBitOnY0(d,X);
					}
				}
			}
		}
	}
}

double	MatchR(int dx,int dy
			,BYTE **TmpImage ,int ImageXLen,int ImageYLen
			,BYTE **TmpPattern	,int PatternXByte,int PatternXLen,int PatternYLen
			,int Isolation)
{
	int		N=0;
	double	AddedA=0;
	double	AddedB=0;
	double	AddedAA=0;
	double	AddedBB=0;
	double	AddedAB=0;

	for(int y=0;y<ImageYLen;y+=Isolation){
		BYTE	*d=TmpImage[y];
		int	iAddedA=0;
		int	iAddedB=0;
		int	iAddedAA=0;
		int	iAddedBB=0;
		int	iAddedAB=0;
		int	Y= y+dy;
		if(Y<0 || Y>=PatternYLen)
			continue;
		for(int x=0;x<ImageXLen;x+=Isolation){
			int	X= x+dx;
			if(X<0 || X>=PatternXLen)
				continue;
			iAddedA	+=d[x];
			iAddedAA+=d[x]*d[x];
			BYTE	*s=TmpPattern[Y];
			if(GetBmpBitOnY(s,X)!=0){
				iAddedB	++;
				iAddedBB++;
				iAddedAB+=d[x];
			}
			else{
				iAddedB	--;
				iAddedBB++;
				iAddedAB-=d[x];
			}
			N++;
		}
		AddedA +=iAddedA;
		AddedB +=iAddedB;
		AddedAA+=iAddedAA;
		AddedBB+=iAddedBB;
		AddedAB+=iAddedAB;
	}
	if(N==0)
		return 0;
	double	As=AddedA/N;
	double	Bs=AddedB/N;
	double	D=(AddedAA-As*As*N)*(AddedBB-Bs*Bs*N);
	if(D<=0)
		return 0;
	double	P=(AddedAB-As*Bs*N)/sqrt(D);
	return fabs(P);
}

double	MatchR(int dx,int dy,double Rot
			,BYTE **TmpImage ,int ImageXLen,int ImageYLen
			,BYTE **TmpPattern	,int PatternXByte,int PatternXLen,int PatternYLen
			,int Isolation)
{
	double	CosS=cos(Rot);
	double	SinS=sin(Rot);

	int		N=0;
	double	AddedA=0;
	double	AddedB=0;
	double	AddedAA=0;
	double	AddedBB=0;
	double	AddedAB=0;

	for(int y=0;y<ImageYLen;y+=Isolation){
		BYTE	*d=TmpImage[y];
		int	iAddedA=0;
		int	iAddedB=0;
		int	iAddedAA=0;
		int	iAddedBB=0;
		int	iAddedAB=0;
		for(int x=0;x<ImageXLen;x+=Isolation){
			int	X= CosS*x+SinS*y+dx;
			int	Y=-SinS*x+CosS*y+dy;
			if(X<0 || X>=PatternXLen || Y<0 || Y>=PatternYLen)
				continue;
			iAddedA	+=d[x];
			iAddedAA+=d[x]*d[x];
			BYTE	*s=TmpPattern[Y];
			if(GetBmpBitOnY(s,X)!=0){
				iAddedB	++;
				iAddedBB++;
				iAddedAB+=d[x];
			}
			else{
				iAddedB	--;
				iAddedBB++;
				iAddedAB-=d[x];
			}
			N++;
		}
		AddedA +=iAddedA;
		AddedB +=iAddedB;
		AddedAA+=iAddedAA;
		AddedBB+=iAddedBB;
		AddedAB+=iAddedAB;
	}
	if(N==0)
		return 0;
	double	As=AddedA/N;
	double	Bs=AddedB/N;
	double	D=(AddedAA-As*As*N)*(AddedBB-Bs*Bs*N);
	if(D<=0)
		return 0;
	double	P=(AddedAB-As*Bs*N)/sqrt(D);
	return fabs(P);
}

double	MatchR(int dx,int dy ,double Rot
			,ImageBuffer &TmpImage ,int ImageXLen,int ImageYLen
			,BYTE **TmpPattern	,int PatternXByte,int PatternXLen,int PatternYLen
			,double Zx ,double Zy)
{
	double	CosS=cos(Rot);
	double	SinS=sin(Rot);

	int		N=0;
	double	AddedA=0;
	double	AddedB=0;
	double	AddedAA=0;
	double	AddedBB=0;
	double	AddedAB=0;

	for(int y=0;y<ImageYLen;y++){
		BYTE	*d=TmpImage.GetY(y);
		int	iAddedA=0;
		int	iAddedB=0;
		int	iAddedAA=0;
		int	iAddedBB=0;
		int	iAddedAB=0;
		for(int x=0;x<ImageXLen;x++){
			int	X=( CosS*x+SinS*y)*Zx+dx;
			int	Y=(-SinS*x+CosS*y)*Zy+dy;
			if(X<0 || X>=PatternXLen || Y<0 || Y>=PatternYLen)
				continue;
			iAddedA	+=d[x];
			iAddedAA+=d[x]*d[x];
			BYTE	*s=TmpPattern[Y];
			if(GetBmpBitOnY(s,X)!=0){
				iAddedB	++;
				iAddedBB++;
				iAddedAB+=d[x];
			}
			else{
				iAddedB	--;
				iAddedBB++;
				iAddedAB-=d[x];
			}
			N++;
		}
		AddedA +=iAddedA;
		AddedB +=iAddedB;
		AddedAA+=iAddedAA;
		AddedBB+=iAddedBB;
		AddedAB+=iAddedAB;
	}
	if(N==0)
		return 0;
	double	As=AddedA/N;
	double	Bs=AddedB/N;
	double	D=(AddedAA-As*As*N)*(AddedBB-Bs*Bs*N);
	if(D<=0)
		return 0;
	double	P=(AddedAB-As*Bs*N)/sqrt(D);
	return fabs(P);
}

class	InflectionPoint : public NPList<InflectionPoint>
{
public:
	int	X,Y,R;
	double	Result;
	double	ResX,ResY;
	double	Rot;
	double	FinalX;
	double	FinalY;
	double	FinalRot;
	double	Zx,Zy;

	virtual	int	Compare(InflectionPoint &src)	
	{	
		if(Result<src.Result)
			return 1;
		if(Result>src.Result)
			return -1;
		return 0;
	}
};


#define	AccessMatchRate(Y,X,R)	(MatchRate[(Y)*(2*DSize+1)*10 + (X)*10+(R)])


void	MakeXProjection(int StartY,int LineNumb,int StartX,int XNumb ,int *ProjectionListX,ImageBuffer &IBuff,double Angle,int Isolation)
{
	double	TanS=tan(Angle);

	int	MaxT=LineNumb/2;
	memset(ProjectionListX,0,sizeof(int)*(StartX+XNumb));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<XNumb;i++){
			int	x=StartX+i;
			int	d=0;
			for(int t=0;t<MaxT;t+=Isolation){
				int	Y1=StartY+MaxT-t;
				int	k=t*TanS;
				int	X1=x+k;
				if(0<=X1 && X1<(StartX+XNumb)){
					d+=IBuff.GetY(Y1)[X1];
				}
				int	Y2=StartY+MaxT+t;
				int	X2=x-k;
				if(0<=X2 && X2<(StartX+XNumb)){
					d+=IBuff.GetY(Y2)[X2];
				}
			}
			ProjectionListX[x]=d;
		}
	}
}

void	MakeXProjection(int StartY,int LineNumb,int StartX,int XNumb ,int *ProjectionListX,BYTE **IBuff)
{
	memset(ProjectionListX,0,sizeof(int)*(StartX+XNumb));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<XNumb;i++){
			int	x=StartX+i;
			int	d=0;
			int	EndY=StartY+LineNumb;
			for(int y=StartY;y<EndY;y++){
				d+=*(IBuff[y]+x);
			}
			ProjectionListX[x]=d;
		}
	}
}

void	MakeXProjectionBit(int StartY,int LineNumb,int XNumb ,int *ProjectionListX,BYTE **BitMap)
{
	memset(ProjectionListX,0,sizeof(int)*XNumb);
	#pragma omp parallel
	{
		#pragma omp for
		for(int x=0;x<XNumb;x++){
			for(int y=0;y<LineNumb;y++){
				BYTE	*s=BitMap[y+StartY];
				if(GetBmpBitOnY(s,x)!=0){
					ProjectionListX[x]++;
				}
				else
					ProjectionListX[x]--;
			}
		}
	}
}

void	MakeYProjection(int StartX,int XNumb,int StartY,int LineNumb ,int *ProjectionListY,ImageBuffer &IBuff,double Angle,int Isolation)
{
	double	TanS=tan(-Angle);

	int	MaxT=XNumb/2;
	memset(ProjectionListY,0,sizeof(int)*(StartY+LineNumb));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<LineNumb;i++){
			int	y=StartY+i;
			int	d=0;
			for(int t=0;t<MaxT;t+=Isolation){
				int	X1=StartX+MaxT-t;
				int	k=t*TanS;
				int	Y1=y+k;
				if(0<=Y1 && Y1<(StartY+LineNumb)){
					d+=IBuff.GetY(Y1)[X1];
				}
				int	X2=StartX+MaxT+t;
				int	Y2=y-k;
				if(0<=Y2 && Y2<(StartY+LineNumb)){
					d+=IBuff.GetY(Y2)[X2];
				}
			}
			ProjectionListY[y]=d;
		}
	}
}

void	MakeYProjection(int StartX,int XNumb,int StartY,int LineNumb ,int *ProjectionListY,BYTE **IBuff)
{
	memset(ProjectionListY,0,sizeof(int)*(StartY+LineNumb));
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<LineNumb;i++){
			int	y=StartY+i;
			BYTE	*s=IBuff[y];
			int	d=0;
			int	EndX=StartX+XNumb;
			for(int x=StartX;x<EndX;x++){
				d+=s[x];
			}
			ProjectionListY[y]=d;
		}
	}
}



void	MakeYProjectionBit(int StartX,int XNumb ,int LineNumb,int *ProjectionListY,BYTE **BitMap)
{
	memset(ProjectionListY,0,sizeof(int)*LineNumb);
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<LineNumb;y++){
			BYTE	*s=BitMap[y];
			for(int x=0;x<XNumb;x++){
				int	X=StartX+x;
				if(GetBmpBitOnY(s,X)!=0){
					ProjectionListY[y]++;
				}
				else
					ProjectionListY[y]--;
			}
		}
	}
}


void	GetEffectiveArea(ImageBuffer &IBuff,int XLen,int YLen
								,int &ImgX1,int &ImgY1,int &ImgX2,int &ImgY2)
{
	ImgY1=0;
	for(int y=0;y<YLen;y++){
		BYTE	*s=IBuff.GetY(y);
		for(int x=0;x<XLen;x++){
			if(s[x]!=0)
				goto	TopEnd;
		}
		ImgY1=y;
	}
TopEnd:;

	ImgY2=YLen;
	for(int y=YLen-1;y>0;y--){
		BYTE	*s=IBuff.GetY(y);
		for(int x=0;x<XLen;x++){
			if(s[x]!=0)
				goto	BottomEnd;
		}
		ImgY2=y;
	}
BottomEnd:;

	ImgX1=0;
	for(int x=0;x<XLen;x++){
		for(int y=0;y<YLen;y++){
			BYTE	*s=IBuff.GetY(y);
			if(s[x]!=0)
				goto	LeftEnd;
		}
		ImgX1=x;
	}
LeftEnd:;

	ImgX2=XLen;
	for(int x=XLen-1;x>0;x--){
		for(int y=0;y<YLen;y++){
			BYTE	*s=IBuff.GetY(y);
			if(s[x]!=0)
				goto	RightEnd;
		}
		ImgX2=x;
	}
RightEnd:;
}

void	GetEffectiveArea(BYTE **IBuff,int XLen,int YLen
								,int &ImgX1,int &ImgY1,int &ImgX2,int &ImgY2)
{
	ImgY1=0;
	for(int y=0;y<YLen;y++){
		BYTE	*s=IBuff[y];
		for(int x=0;x<XLen;x++){
			if(s[x]!=0)
				goto	TopEnd;
		}
		ImgY1=y;
	}
TopEnd:;

	ImgY2=YLen;
	for(int y=YLen-1;y>0;y--){
		BYTE	*s=IBuff[y];
		for(int x=0;x<XLen;x++){
			if(s[x]!=0)
				goto	BottomEnd;
		}
		ImgY2=y;
	}
BottomEnd:;

	ImgX1=0;
	for(int x=0;x<XLen;x++){
		for(int y=0;y<YLen;y++){
			BYTE	*s=IBuff[y];
			if(s[x]!=0)
				goto	LeftEnd;
		}
		ImgX1=x;
	}
LeftEnd:;

	ImgX2=XLen;
	for(int x=XLen-1;x>0;x--){
		for(int y=0;y<YLen;y++){
			BYTE	*s=IBuff[y];
			if(s[x]!=0)
				goto	RightEnd;
		}
		ImgX2=x;
	}
RightEnd:;
}

double	MakeCoeff(int *ProjectionDstListX,int DstLen
				, int *ProjectionSrcListX,int SrcLen,int ImgX1,int ImgX2
				,int StartX,double ZoomRate
				,int Isolation)
{
	int	x=0;
	int		N=0;
	double	AddedA=0;
	double	AddedB=0;
	double	AddedAA=0;
	double	AddedBB=0;
	double	AddedAB=0;
	double	Mx=0;
	double	Added=ZoomRate*Isolation;
	for(int x=ImgX1;x<SrcLen && x<ImgX2;x+=Isolation,Mx+=Added){
		int	X=StartX+Mx;
		if(0<=X && X<DstLen){
			double	a=ProjectionDstListX[X];
			double	b=ProjectionSrcListX[x];
			AddedA	+=a;
			AddedAA	+=a*a;
			AddedB	+=b;
			AddedBB	+=b*b;
			AddedAB	+=a*b;
			N++;
		}
	}
	if(N==0)
		return 0;
	double	As=AddedA/N;
	double	Bs=AddedB/N;
	double	D=(AddedAA-As*As*N)*(AddedBB-Bs*Bs*N);
	if(D<=0)
		return 0;
	double	P=(AddedAB-As*Bs*N)/sqrt(D);
	return fabs(P);
}

struct	RestructTooBigClass
{
	GerberFastItemBase	*Item;
	AlgorithmItemPointerListContainer Container;
	bool	Result;
};

void	GerberFastInPage::RestructTooBig(double TooBigSizeForCut)
{
	int	ItemCount=GetItemCount();
	struct	RestructTooBigClass	*LDim=new struct	RestructTooBigClass[ItemCount];

	int	n=0;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(item!=NULL){
			LDim[n].Item=item;
			n++;
		}
	}
	//#pragma omp parallel for
	for(int i=0;i<n;i++){
		if(LDim[i].Item->GetID()==DbgGerberID1)
			DbgGerber++;
		LDim[i].Result=CheckAndSplitBySize(LDim[i].Item,TooBigSizeForCut ,LDim[i].Container);
	}
	for(int k=0;k<n;k++){
		if(LDim[k].Result==true){
			int	N=LDim[k].Container.GetCount();
			for(int i=0;i<N;i++){
				AlgorithmItemRoot	*b=LDim[k].Container[i]->GetItem();
				GerberFastItemBase	*t=static_cast<GerberFastItemBase *>(b);
				if(t!=NULL){
					InsertItem(t,LDim[k].Item);
				}
			}
			RemoveItem(LDim[k].Item);
		}
	}
	delete	[]LDim;

	/*
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
		AlgorithmItemPI	*NextA=a->GetNext();
		GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
		if(a->GetID()==DbgGerberID1 || a->GetID()==DbgGerberID2)
			DbgGerber++;
		if(item!=NULL){
			AlgorithmItemPointerListContainer Container;
			if(CheckAndSplitBySize(item,TooBigSizeForCut ,Container)==true){
				int	N=Container.GetCount();
				for(int i=0;i<N;i++){
					AlgorithmItemRoot	*b=Container[i]->GetItem();
					GerberFastItemBase	*t=static_cast<GerberFastItemBase *>(b);
					if(t!=NULL){
						InsertItem(t,item);
					}
				}
				RemoveItem(item);
			}
		}
		a=NextA;
	}
	*/
}
bool	GerberFastInPage::CheckAndSplitBySize(GerberFastItemBase *item,double TooBigSizeForCut ,AlgorithmItemPointerListContainer &Container)
{
	double	X1,Y1,X2,Y2;
	if(item->GetID()==DbgID)
		DbgIDMode++;
	item->GetXY(X1,Y1,X2,Y2);
	double	W=X2-X1;
	double	H=Y2-Y1;
	if(H>TooBigSizeForCut){
		GerberFastItemBase *Obj[1000];
		int	CNumb=item->SplitVerticalCut(Obj,1000);
		if(CNumb>0){
			for(int k=0;k<CNumb;k++){
				Obj[k]->SetParent(this);
				if(CheckAndSplitBySize(Obj[k],TooBigSizeForCut,Container)==true){
					delete	Obj[k];
				}
			}
			return true;
		}
		else{
			Container.Add(item);
		}
	}
	else if(W>TooBigSizeForCut){
		GerberFastItemBase *Obj[1000];
		int	CNumb=item->SplitHorizontalCut(Obj,1000);
		if(CNumb>0){
			for(int k=0;k<CNumb;k++){
				Obj[k]->SetParent(this);
				if(CheckAndSplitBySize(Obj[k],TooBigSizeForCut,Container)==true){
					delete	Obj[k];
				}
			}
			return true;
		}
		else{
			Container.Add(item);
		}
	}
	else{
		Container.Add(item);
	}
	return false;
}

bool	GerberFastInPage::MatchRough(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
									,bool &MirrorMode
									,double &MovX ,double &MovY
									,double &ZoomX,double &ZoomY
									,double &Rotation)
{
	/*
	const	int		DSize=1024;
	MirrorMode	=false;

	double	Zx=GetDotPerLine()/(double)DSize;
	double	Zy=GetMaxLines()/(double)DSize;
	double	Z =max(Zx,Zy);
	int		XByte	=(GetDotPerLine()+7)/8;
	int		YLen	=GetMaxLines();
	double	ShrinkRate=min((double)DSize/(double)GetDotPerLine(),(double)DSize/(double)GetMaxLines());

	int	ImageXLen=DSize;
	int	ImageYLen=DSize;
	BYTE	**TmpImage=MakeMatrixBuff(ImageXLen,ImageYLen);
	ImagePointerContainer Images;
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		GetMasterImages(Images);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		GetTargetImages(Images);

	MakeShrinkImage(TmpImage,ImageXLen,ImageYLen
					,ShrinkRate
					,*Images[0]);

	int	PatternXLen=DSize*GetLayersBase()->GetGlobalPageNumb()*3;
	int	PatternYLen=DSize*GetLayersBase()->GetGlobalPageNumb()*3;
	int	PatternXByte=(PatternXLen+7)/8;
	int	StartPointX=DSize;
	int	StartPointY=DSize;
	BYTE	**TmpPattern=MakeMatrixBuff(PatternXByte,PatternYLen);
	MakePattern(TmpPattern,PatternXLen,PatternYLen
				,ShrinkRate
				,StartPointX,StartPointY
				,ButtonsToOperateLayer ,ButtonsToOperateComposite);

	double	*MatchRate=new double[(2*DSize+1)*(2*DSize+1)*10];
	double	AngleDiv=0.5*M_PI/180.0;

	SavePNGFileByte("Test1.png",(const BYTE **)TmpImage,ImageXLen,ImageYLen);
	SavePNGFileBit ("Test2.png",(const BYTE **)TmpPattern ,PatternXByte ,PatternYLen);

	NPListPack<InflectionPoint>	Inflection;
	int	YNumb=2*DSize+1;
	#pragma omp parallel
	{
		#pragma omp for
		for(int	Y=0;Y<YNumb;Y++){
			for(int dx=-DSize;dx<=DSize;dx++){
				int	X=DSize+dx;
				for(int Rot=-4;Rot<=4;Rot++){
					int	R=4+Rot;
					//MatchRate[Y][X][R]	=MatchR(X,Y,((double)Rot)*AngleDiv
					AccessMatchRate(Y,X,R)
										=MatchR(X,Y,((double)Rot)*AngleDiv
												,TmpImage	,ImageXLen,ImageYLen
												,TmpPattern	,PatternXByte,PatternXLen,PatternYLen
												,2);
				}
			}
		}
	}
	//Search Inflection points
	for(int dy=-DSize+1;dy<=DSize-1;dy++){
		int	Y=DSize+dy;
		for(int dx=-DSize+1;dx<=DSize-1;dx++){
			int	X=DSize+dx;
			for(int Rot=-4+1;Rot<=4-1;Rot++){
				int	R=4+Rot;
				bool	Flag=true;
				for(int py=-1;py<=1;py++){
					for(int px=-1;px<=1;px++){
						for(int pr=-1;pr<=1;pr++){
							if(px==0 && py==0 && pr==0)
								continue;
							//if(MatchRate[Y+py][X+px][R+pr]>=MatchRate[Y][X][R]){
							if(AccessMatchRate(Y+py,X+px,R+pr)>=AccessMatchRate(Y,X,R)){
								Flag=false;
								goto	TNext;
							}
						}
					}
				}
TNext:;
				if(Flag==true){
					InflectionPoint	*c=new InflectionPoint();
					c->X=X-DSize;
					c->Y=Y-DSize;
					c->R=R-4;
					//c->Result	=MatchRate[Y][X][R];
					c->Result	=AccessMatchRate(Y,X,R);
					Inflection.AppendList(c);
				}
			}
		}
	}
	delete	[]MatchRate;

	Inflection.Sort();
	DeleteMatrixBuff(TmpImage,ImageYLen);
	DeleteMatrixBuff(TmpPattern,PatternYLen);

	int	DtailXNumb=GetDotPerLine()/4;
	int	DtailYNumb=GetMaxLines()/4;
	double	ShrinkRateL	=0.25;

	ImageXLen=GetDotPerLine()*ShrinkRateL;
	ImageYLen=GetMaxLines()*ShrinkRateL;
	TmpImage=MakeMatrixBuff(ImageXLen,ImageYLen);
	MakeShrinkImage(TmpImage,ImageXLen,ImageYLen
					,ShrinkRateL
					,*Images[0]);

	PatternXLen=ImageXLen*GetLayersBase()->GetGlobalPageNumb()+513;
	PatternYLen=ImageYLen*GetLayersBase()->GetGlobalPageNumb()+513;
	PatternXByte=(PatternXLen+7)/8;
	TmpPattern=MakeMatrixBuff(PatternXByte,PatternYLen);
	MakePattern(TmpPattern,PatternXLen,PatternYLen
				,ShrinkRateL
				,256,256
				,ButtonsToOperateLayer ,ButtonsToOperateComposite);
	double	AngleDivL=0.2*M_PI/180.0;
	while(Inflection.GetCount()>10){
		InflectionPoint	*c=Inflection.GetLast();
		Inflection.RemoveList(c);
		delete	c;
	}

	for(int i=0;i<Inflection.GetCount();i++){
		double	MaxD=0;
		InflectionPoint	*p=Inflection[i];
		for(int dy=-4;dy<=4;dy++){
			for(int dx=-2;dx<=2;dx++){
				for(int Rot=-3;Rot<=3;Rot++){
					double	Mx=p->X/ShrinkRate*ShrinkRateL+dx;
					double	My=p->Y/ShrinkRate*ShrinkRateL+dy;
					double	RotAngle=p->R*AngleDiv + Rot*AngleDivL;
					double	D=MatchR(Mx+256,My+256,RotAngle
									,TmpImage	,ImageXLen,ImageYLen
									,TmpPattern	,PatternXByte,PatternXLen,PatternYLen
									,1);
					if(D>MaxD){
						p->ResX=Mx*4;
						p->ResY=My*4;
						p->Rot =RotAngle;
						p->Result	=MaxD;
						MaxD=D;
					}
				}
			}
		}
	}
	DeleteMatrixBuff(TmpImage,ImageYLen);
	DeleteMatrixBuff(TmpPattern,PatternYLen);

	Inflection.Sort();
	double	ZoomDiv=(GetDotPerLine()<GetMaxLines())?3.0/(double)GetMaxLines():3.0/(double)GetDotPerLine();	
	PatternXLen=GetDotPerLine();
	PatternYLen=GetMaxLines();
	PatternXByte=(PatternXLen+7)/8;
	TmpPattern=MakeMatrixBuff(PatternXByte,PatternYLen);
	double	AngleDivFinal=AngleDivL/3.0;
	double	FinalMaxD=0;
	for(int i=0;i<5 && i<Inflection.GetCount();i++){
		InflectionPoint	*p=Inflection[i];
		MakePattern(TmpPattern,PatternXLen,PatternYLen
				,1.0
				,p->ResX,p->ResY
				,ButtonsToOperateLayer ,ButtonsToOperateComposite);

		double	MaxD=0;
		for(int Zy=-4;Zy<=4;Zy++){
			for(int Zx=-4;Zx<=4;Zx++){
				for(int dy=-4;dy<=4;dy++){
					for(int dx=-4;dx<=4;dx++){
						for(int Rot=-2;Rot<=2;Rot++){
							double	Mx=p->ResX+dx;
							double	My=p->ResY+dy;
							double	R=p->Rot+Rot*AngleDivFinal;
							double	D=MatchR(Mx,My,R
											,*Images[0]	,GetDotPerLine(),GetMaxLines()
											,TmpPattern	,PatternXByte,PatternXLen,PatternYLen
											,1.0+Zx*ZoomDiv,1.0+Zy*ZoomDiv);
							if(D>MaxD){
								MaxD=D;
								p->FinalX=Mx;
								p->FinalY=My;
								p->FinalRot	=R;
								p->Result	=MaxD;
								p->Zx		=Zx;
								p->Zy		=Zy;
							}
							if(D>FinalMaxD){
								FinalMaxD=D;
								MovX=Mx;
								MovY=My;
								Rotation=R;
								ZoomX	=1.0+Zx*ZoomDiv;
								ZoomY	=1.0+Zy*ZoomDiv;
							}
						}
					}
				}
			}
		}
	}
	DeleteMatrixBuff(TmpPattern,PatternYLen);
	*/

//Projection X-Dir
	int	PatternXLen=GetDotPerLine()*2;
	int	PatternYLen=GetMaxLines();
	int	PatternXByte=(PatternXLen+7)/8;
	BYTE	**TmpPattern=MakeMatrixBuff(PatternXByte,PatternYLen);
	MakePattern(TmpPattern,PatternXLen,PatternYLen
			,1.0
			,0,0
			,ButtonsToOperateLayer ,OperateCompositeIDList);

	ImagePointerContainer Images;
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		GetMasterImages(Images);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		GetTargetImages(Images);
	else
		return false;

	double	AngleDiv=M_PI/180.0*0.1;

	int	ImgX1,ImgY1,ImgX2,ImgY2;
	GetEffectiveArea(*Images[0],GetDotPerLine(),GetMaxLines()
								,ImgX1,ImgY1,ImgX2,ImgY2);

	const int	AngleCount=10;
	int		*ProjectionSrcListX[2*AngleCount+1];
	for(int i=0;i<(2*AngleCount+1);i++){
		ProjectionSrcListX[i]=new int[GetDotPerLine()];
		double	Angle=(i-AngleCount)*AngleDiv;
		memset(ProjectionSrcListX[i],0,sizeof(int)*GetDotPerLine());
		MakeXProjection(ImgY1,ImgY2-ImgY1,ImgX1,ImgX2-ImgX1,ProjectionSrcListX[i],*Images[0],Angle,2);
	}

	int		*ProjectionDstListX=new int[PatternXLen];
	MakeXProjectionBit(0,PatternYLen,PatternXLen,ProjectionDstListX,TmpPattern);

	double	ZoomDiv=(GetDotPerLine()<GetMaxLines())?3.0/(double)GetMaxLines():2.0/(double)GetDotPerLine();	
	int	XArea=GetDotPerLine()/500;
	if(XArea<300)
		XArea=300;
	double	MaxDX=0;
	double	MaxZ=0;
	double	MaxX1=0;
	double	MaxX=0;
	double	MaxRot;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int zi=0;zi<21;zi++){
			//int	Z=zi-10;
		for(int Rot=0;Rot<(2*AngleCount+1);Rot++){
			for(int Z=-10;Z<=10;Z++){
				for(int X=-XArea;X<=XArea;X+=2){
					double	D=MakeCoeff( ProjectionDstListX,PatternXLen
										,ProjectionSrcListX[Rot],GetDotPerLine(),ImgX1,ImgX2
										,X,1.0+Z*ZoomDiv,2);
					#pragma omp critical
					{
						if(D>MaxDX){
							MaxDX=D;
							MaxX1=X;
						}
					}
				}
			}
		}
	}
	MaxDX=0;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int zi=0;zi<21;zi++){
			//int	Z=zi-10;
		for(int Rot=0;Rot<(2*AngleCount+1);Rot++){
			for(int Z=-10;Z<=10;Z++){
				for(int X=-2+MaxX1;X<=2+MaxX1;X++){
					double	D=MakeCoeff( ProjectionDstListX,PatternXLen
										,ProjectionSrcListX[Rot],GetDotPerLine(),ImgX1,ImgX2
										,X,1.0+Z*ZoomDiv,1);
					#pragma omp critical
					{
						if(D>MaxDX){
							MaxDX=D;
							MaxZ=1+Z*ZoomDiv;
							MaxX=X;
							MaxRot=Rot-AngleCount;
						}
					}
				}
			}
		}
	}
	for(int i=0;i<(2*AngleCount+1);i++){
		delete	[]ProjectionSrcListX[i];
	}
	delete	[]ProjectionDstListX;

	Rotation=-MaxRot*AngleDiv;
	MovX		=-MaxX;
	ZoomX		=1.0/MaxZ;


//Projection Y-Dir
	const int	AngleCountX=5;
	int		*ProjectionSrcListY[2*AngleCountX+1];

	int	BandW=ImgX2-ImgX1;
	int	Sx=0;
	int	Dx=0;
	if(MaxX>=0){
		Dx=MaxX;
	}
	else{
		Sx=-MaxX;
		BandW+=MaxX;
	}
	double	AngleDivX=AngleDiv/2;
	for(int i=0;i<(2*AngleCountX+1);i++){
		ProjectionSrcListY[i]=new int[GetMaxLines()];
		memset(ProjectionSrcListY[i],0,sizeof(int)*GetMaxLines());
		MakeYProjection(Sx,BandW,ImgY1,ImgY2-ImgY1,ProjectionSrcListY[i],*Images[0],MaxRot*AngleDiv+(i-AngleCountX)*AngleDivX,2);
	}

	int		*ProjectionDstListY=new int[PatternYLen];
	MakeYProjectionBit(Dx,BandW,PatternYLen,ProjectionDstListY,TmpPattern);

	int	YArea=GetMaxLines()/50;
	if(YArea<300)
		YArea=300;
	double	MaxDY=0;
	MaxZ=0;
	double	MaxY1=0;
	double	MaxY=0;
	int		MaxRotY=0;
	#pragma omp parallel
	{
		#pragma omp for
		for(int zi=0;zi<21;zi++){
		//for(int Z=-10;Z<=10;Z++){
			int	Z=zi-10;
			for(int Rot=0;Rot<(2*AngleCountX+1);Rot++){
				for(int Y=-YArea;Y<=YArea;Y+=2){
					double	D=MakeCoeff( ProjectionDstListY     ,PatternYLen
										,ProjectionSrcListY[Rot],GetMaxLines(),ImgY1,ImgY2
										,Y,1.0+Z*ZoomDiv,2);
					#pragma omp critical
					{
						if(D>MaxDY){
							MaxDY=D;
							MaxY1=Y;
						}
					}
				}
			}
		}
	}
	MaxDY=0;
	#pragma omp parallel
	{
		#pragma omp for
		for(int zi=0;zi<21;zi++){
			int	Z=zi-10;
			//for(int Z=-10;Z<=10;Z++){
			for(int Rot=0;Rot<(2*AngleCountX+1);Rot++){
				for(int Y=-2+MaxY1;Y<=2+MaxY1;Y++){
					double	D=MakeCoeff( ProjectionDstListY     ,PatternYLen
										,ProjectionSrcListY[Rot],GetMaxLines(),ImgY1,ImgY2
										,Y,1.0+Z*ZoomDiv,1);
					#pragma omp critical
					{
						if(D>MaxDY){
							MaxDY=D;
							MaxZ=1+Z*ZoomDiv;
							MaxY=Y;
							MaxRotY=Rot;
						}
					}
				}
			}
		}
	}
	for(int i=0;i<(2*AngleCountX+1);i++){
		delete	[]ProjectionSrcListY[i];
	}
	delete	[]ProjectionDstListY;
	MovY		=-MaxY;
	ZoomY		=1.0/MaxZ;
	//if(MaxDX<MaxDY)
		Rotation	=-(MaxRot*AngleDiv+(MaxRotY-AngleCountX)*AngleDivX);
	//else
	//	Rotation	=MaxRot*AngleDiv;

	DeleteMatrixBuff(TmpPattern,PatternYLen);

	return true;
}

void	GerberFastInPage::MakeMatchShrinked(BoolList &ButtonsToOperateLayer ,IntList &OperateCompositeIDList
									,double ShrinkedRate
									,QByteArray	&ImageData
									,QByteArray	&GerberData)
{
	int	ImageXLen=GetDotPerLine()*ShrinkedRate;
	int	ImageYLen=GetMaxLines()*ShrinkedRate;
	BYTE	**TmpImage=MakeMatrixBuff(ImageXLen,ImageYLen);

	ImagePointerContainer Images;
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		GetMasterImages(Images);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		GetTargetImages(Images);
	else
		return;

	MakeShrinkImage(TmpImage,ImageXLen,ImageYLen
					,ShrinkedRate
					,*Images[0]);

	int	PatternXByte=(ImageXLen+7)/8;
	BYTE	**TmpPattern=MakeMatrixBuff(PatternXByte,ImageYLen);
	MakePattern(TmpPattern,ImageXLen,ImageYLen
				,ShrinkedRate
				,0,0
				,ButtonsToOperateLayer ,OperateCompositeIDList);


	QBuffer	IBuff;
	IBuff.open(QIODevice::WriteOnly);
	::Save(&IBuff,ImageXLen);
	::Save(&IBuff,ImageYLen);
	for(int y=0;y<ImageYLen;y++){
		IBuff.write((const char *)TmpImage[y],ImageXLen);
	}
	ImageData	=IBuff.buffer();

	QBuffer	GBuff;
	GBuff.open(QIODevice::WriteOnly);
	::Save(&GBuff,PatternXByte);
	::Save(&GBuff,ImageYLen);
	for(int y=0;y<ImageYLen;y++){
		GBuff.write((const char *)TmpPattern[y],PatternXByte);
	}
	GerberData	=GBuff.buffer();

	DeleteMatrixBuff(TmpImage	,ImageYLen);
	DeleteMatrixBuff(TmpPattern	,ImageYLen);
}

void	GerberFastInPage::MakeEnabledAutomatchFlag(void)
{
	double	Mergin=-5.0;

	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			double	x1,y1,x2,y2;
			Item->GetXY(x1,y1,x2,y2);
			if(CheckOverlapRectRect(x1,y1,x2,y2
								,-Mergin ,-Mergin,GetDotPerLine()+Mergin ,GetMaxLines()+Mergin)==true){
				Item->EnabledAutomatch=true;
			}
			else
				Item->EnabledAutomatch=false;
		}
	}
}

void	GerberFastBase::MatchGlobal(double ShrinkedRate ,QByteArray ImageData[],QByteArray GerberData[] 
									,int &Dx,int &Dy ,double &ZoomX ,double &ZoomY)
{
	int x1 ,y1 ,x2 ,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);
	int	ImageXLen=x2*ShrinkedRate;
	int	ImageYLen=y2*ShrinkedRate;
	int	PatternXLen	=ImageXLen;
	int	PatternYLen	=ImageYLen;

	BYTE	**TmpImage=MakeMatrixBuff(ImageXLen,ImageYLen);
	MatrixBuffClear	(TmpImage,0,ImageXLen,ImageYLen);

	int	PatternXByte=(PatternXLen+7)/8;
	BYTE	**TmpPattern=MakeMatrixBuff(PatternXByte,PatternYLen);
	MatrixBuffClear	(TmpPattern,0,PatternXByte,PatternYLen);

	for(int page=0;page<GetPageNumb();page++){
		XYData	*XY=GetLayersBase()->GetGlobalOutlineOffset(page);
		int	XPos=XY->x*ShrinkedRate;
		int	YPos=XY->y*ShrinkedRate;
		int	XLen,YLen;
		QBuffer	IBuff(&ImageData[page]);
		IBuff.open(QIODevice::ReadOnly);
		::Load(&IBuff,XLen);
		::Load(&IBuff,YLen);
		int	Len=XLen;
		if(XPos+Len>ImageXLen)
			Len=ImageXLen-XPos;
		int	Dummy=XLen-Len;
		for(int y=0;y<YLen;y++){
			if(YPos+y<0){
				for(int x=0;x<XLen;x++){
					char	D;
					IBuff.read((char *)&D,1);
				}
			}
			else if(YPos+y>=ImageYLen){
				break;
			}
			else{
				IBuff.read((char *)(TmpImage[YPos+y]+XPos),Len);
				for(int x=0;x<Dummy;x++){
					char	D;
					IBuff.read((char *)&D,1);
				}
			}
		}
		QBuffer	GBuff(&GerberData[page]);
		GBuff.open(QIODevice::ReadOnly);
		int	GerberXByte,GerberYLen;
		::Load(&GBuff,GerberXByte);
		::Load(&GBuff,GerberYLen);
		BYTE	LineData[65535];
		for(int y=0;y<GerberYLen;y++){
			if(YPos+y<0){
				for(int x=0;x<GerberXByte;x++){
					char	D;
					GBuff.read((char *)&D,1);
				}
			}
			else if(YPos+y>=PatternYLen){
				break;
			}
			else{
				GBuff.read((char *)LineData,GerberXByte);
				BYTE	*d=TmpPattern[YPos+y];
				for(int x=0;x<GerberXByte;x++){
					BYTE	Mask=0x80;
					for(int b=0;b<8;b++,Mask>>=1){
						int	X=XPos+(x<<3)+b;
						if(0<=X && X<PatternXLen){
							if((LineData[x]&Mask)!=0)
								SetBmpBitOnY1(d,X);
						}
					}
				}
			}
		}
	}
	SavePNGFileByte("Test1.png",TmpImage,ImageXLen,ImageYLen);
	SavePNGFileBit ("Test2.png",TmpPattern ,PatternXByte ,ImageYLen);

	int	ShiftAreaX=ImageXLen/4;
	int	ShiftAreaY=ImageYLen/4;
	int	ImgX1,ImgY1,ImgX2,ImgY2;
	GetEffectiveArea(TmpImage,ImageXLen,ImageYLen
								,ImgX1,ImgY1,ImgX2,ImgY2);

	/*
	double	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	int	N=2*ShiftAreaY+1;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int dy=-ShiftAreaY;dy<=ShiftAreaY;dy++){
		for(int i=0;i<N;i++){
			int	dy=i-ShiftAreaY;
			for(int dx=-ShiftAreaX;dx<=ShiftAreaX;dx++){
				double	D=MatchR(dx,dy
								,TmpImage ,ImageXLen,ImageYLen
								,TmpPattern	,PatternXByte,ImageXLen,ImageYLen
								,1);
				#pragma omp critical
				{
					if(D>MaxD){
						MaxD=D;
						MaxDx=dx;
						MaxDy=dy;
					}
				}
			}
		}
	}
	double	MaxD2=0;
	int	MaxDx2=0;
	int	MaxDy2=0;
	for(int dy=MaxDy-2;dy<=MaxDy+2;dy++){
		for(int dx=MaxDx-2;dx<=MaxDx+2;dx++){
			double	D=MatchR(dx,dy
							,TmpImage ,ImageXLen,ImageYLen
							,TmpPattern	,PatternXByte,ImageXLen,ImageYLen
							,1);
			if(D>MaxD2){
				MaxD2=D;
				MaxDx2=dx;
				MaxDy2=dy;
			}
		}
	}
	*/
	int		*ProjectionSrcListX=new int[ImageXLen];
	memset(ProjectionSrcListX,0,sizeof(int)*ImageXLen);
	MakeXProjection(ImgY1,ImgY2-ImgY1,ImgX1,ImgX2-ImgX1,ProjectionSrcListX,TmpImage);

	int		*ProjectionDstListX=new int[PatternXLen];
	MakeXProjectionBit(0,PatternYLen,PatternXLen,ProjectionDstListX,TmpPattern);

	double	ZoomDiv=(ImageXLen<ImageYLen)?3.0/(double)ImageYLen:2.0/(double)ImageXLen;	
	double	MaxDX=0;
	double	MaxZ=0;
	double	MaxX=0;
	ZoomX=1.0;
	int	NX	=2*ShiftAreaX+1;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int X=-ShiftAreaX;X<=ShiftAreaX;X++){
		for(int i=0;i<NX;i++){
			int	X=i-ShiftAreaX;
			for(int Z=-10;Z<=10;Z++){
				double	D=MakeCoeff( ProjectionDstListX,PatternXLen
									,ProjectionSrcListX,ImageXLen,ImgX1,ImgX2
									,X,1.0+Z*ZoomDiv,1);
				#pragma omp critical
				{
					if(D>MaxDX){
						MaxDX=D;
						MaxX=X;
						MaxZ=1+Z*ZoomDiv;
					}
				}
			}
		}
	}
	delete	[]ProjectionSrcListX;
	delete	[]ProjectionDstListX;
	Dx		=-MaxX;
	ZoomX	=1.0/MaxZ;


//Projection Y-Dir
	int		*ProjectionSrcListY=new int[ImageYLen];
	memset(ProjectionSrcListY,0,sizeof(int)*ImageYLen);
	MakeYProjection(ImgX1,ImgX2-ImgX1,ImgY1,ImgY2-ImgY1,ProjectionSrcListY,TmpImage);

	int		*ProjectionDstListY=new int[PatternYLen];
	MakeYProjectionBit(0,PatternXLen,PatternYLen,ProjectionDstListY,TmpPattern);

	double	MaxDY=0;
	MaxZ=0;
	double	MaxY=0;
	ZoomY=1.0;
	int	NY	=2*ShiftAreaY+1;
	#pragma omp parallel
	{
		#pragma omp for
		//for(int Y=-ShiftAreaY;Y<=ShiftAreaY;Y+=2){
		for(int i=0;i<NY;i++){
			int	Y=i-ShiftAreaY;
			for(int Z=-10;Z<=10;Z++){
				double	D=MakeCoeff( ProjectionDstListY,PatternYLen
									,ProjectionSrcListY,ImageYLen,ImgY1,ImgY2
									,Y,1.0+Z*ZoomDiv,1);
				#pragma omp critical
				{
					if(D>MaxDY){
						MaxDY=D;
						MaxY=Y;
						MaxZ=1+Z*ZoomDiv;
					}
				}
			}
		}
	}
	delete	[]ProjectionSrcListY;
	delete	[]ProjectionDstListY;
	Dy		=-MaxY;
	ZoomY	=1.0/MaxZ;

	DeleteMatrixBuff(TmpImage	,ImageYLen);
	DeleteMatrixBuff(TmpPattern	,PatternYLen);
}
						
//=====================================================================


void	ParallelRoughMatch::MakeArea(BYTE **CurrentBmp ,int XByte ,int YLen ,FlexAreaPointerContainer &Container)
{
	TransZone.RemoveAll();
	OutsideZone.RemoveAll();
	InsideZone.RemoveAll();

	BYTE **mCurrentBmp=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(mCurrentBmp,0,XByte ,YLen);
	for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetArea()->MakeBitData(mCurrentBmp,XByte*8,YLen);
	}
	BYTE **TmpMap1=MakeMatrixBuff(XByte ,YLen);
	BYTE **TmpMap2=MakeMatrixBuff(XByte ,YLen);
	BYTE **TmpMap3=MakeMatrixBuff(XByte ,YLen);
	BYTE **SrcMap =MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(TmpMap1	,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);
	MatrixBuffCopy	(SrcMap		,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);

	Parent->GetLayersBase()->FatAreaN(mCurrentBmp
				,TmpMap2
				,XByte ,YLen 
				,Parent->ParamParent->TransDot);

	Parent->GetLayersBase()->ThinAreaN(TmpMap1
				,TmpMap2
				,XByte ,YLen 
				,Parent->ParamParent->TransDot);
	PickupFlexArea(TmpMap1 ,XByte ,XByte*8,YLen ,InsideZone);

	MatrixBuffCopy	(TmpMap3	,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);
	Parent->GetLayersBase()->FatAreaN(TmpMap3
				,TmpMap2
				,XByte ,YLen 
				,Parent->ParamParent->TransDot);

	MatrixBuffXor	(TmpMap3,(const BYTE **)mCurrentBmp ,XByte ,YLen);
	PickupFlexArea(TmpMap3 ,XByte ,XByte*8,YLen ,OutsideZone);

	MatrixBuffCopy	(TmpMap3	,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);

	MatrixBuffXor	(mCurrentBmp,(const BYTE **)TmpMap1 ,XByte ,YLen);
	PureFlexAreaListContainer TransPack;
	PickupFlexArea(mCurrentBmp ,XByte ,XByte*8,YLen ,TransPack);
	for(PureFlexAreaList *a=TransPack.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeffAndResult	*b=new FlexAreaImageListCoeffAndResult();
		*b=*a;
		b->ExpandBitImage(SrcMap,0x80,XByte,YLen);
		//b->MakeSum();
		//b->SetCross(CurrentBmp ,XByte ,YLen);
		TransZone.AppendList(b);
	}
	FlexAreaImageList *k;
	#pragma omp parallel
	#pragma omp single private(k)
	for(k=TransZone.GetFirst();k!=NULL;k=k->GetNext()){
		#pragma omp task
		{
			FlexAreaImageListCoeffAndResult	*h=(FlexAreaImageListCoeffAndResult *)k;
			h->MakeSum();
			h->SetCross(Container,CurrentBmp ,XByte ,YLen);
		}
	}

	DeleteMatrixBuff(mCurrentBmp,YLen);	
	DeleteMatrixBuff(TmpMap1	,YLen);	
	DeleteMatrixBuff(TmpMap2	,YLen);	
	DeleteMatrixBuff(TmpMap3	,YLen);	
	DeleteMatrixBuff(SrcMap		,YLen);	
}


struct	MatchList
{
	int	Dx,Dy;
	double	Coeff;
};

int	MListFunc(const void *a ,const void *b)
{
	struct	MatchList	*pa=(struct	MatchList *)a;
	struct	MatchList	*pb=(struct	MatchList *)b;
	if(pa->Coeff<pb->Coeff)
		return 1;
	if(pa->Coeff>pb->Coeff)
		return -1;
	return 0;
}

void	ParallelRoughMatch::RoughMatch(ImageBuffer &IBuff ,int SearchDot ,int &Mx,int &My)
{
	int	N=(2*SearchDot+1)*(2*SearchDot+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dx=-SearchDot;dx<=SearchDot;dx+=3){
		for(int dy=-SearchDot;dy<=SearchDot;dy+=3){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int n=0;n<ShiftNumb;n++){
			int	dx=ShiftList[n].x;
			int	dy=ShiftList[n].y;
			MList[n].Dx=dx;
			MList[n].Dy=dy;

			double	SumP=0;
			for(FlexAreaImageList *k=TransZone.GetFirst();k!=NULL;k=k->GetNext()){
				FlexAreaImageListCoeffAndResult	*h=(FlexAreaImageListCoeffAndResult *)k;
				SumP+=h->CalcCross(dx,dy,IBuff);
			}
			MList[n].Coeff=fabs(SumP);
		}
	}

	/*
	#pragma omp parallel
	{
		#pragma omp for
		for(int n=0;n<ShiftNumb;n++){
			int	dx=ShiftList[n].x;
			int	dy=ShiftList[n].y;
			MList[n].Dx=dx;
			MList[n].Dy=dy;
			double	MinD=0;
			int	MinN=0;
			for(PureFlexAreaList *a=InsideZone.GetFirst();a!=NULL;a=a->GetNext()){
				int	x1,y1,x2,y2;
				a->GetXY(x1,y1,x2,y2);
				if(0<=x1+dx && x2+dx<Parent->GetDotPerLine()
				&& 0<=y1+dy && y2+dy<Parent->GetMaxLines()){
					MinD+=a->GetAverageRough(IBuff,dx ,dy);
					MinN++;
				}
			}
			double	MaxD=0;
			int	MaxN=0;
			for(PureFlexAreaList *a=OutsideZone.GetFirst();a!=NULL;a=a->GetNext()){
				int	x1,y1,x2,y2;
				a->GetXY(x1,y1,x2,y2);
				if(0<=x1+dx && x2+dx<Parent->GetDotPerLine()
				&& 0<=y1+dy && y2+dy<Parent->GetMaxLines()){
					MaxD+=a->GetAverageRough(IBuff,dx ,dy);
					MaxN++;
				}
			}
			MList[n].Coeff=fabs(MaxD/(double)MaxN-MinD/(double)MinN);
		}
	}
	*/

	delete	[]ShiftList;
	QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);

	int	Numb=ShiftNumb/1600;
	if(Numb<20)
		Numb=20;
	if(Numb>ShiftNumb)
		Numb=ShiftNumb;
	int	MaxDx=0;
	int	MaxDy=0;
	double	MaxD=0;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<Numb;i++){
			int	dx=MList[i].Dx;
			int	dy=MList[i].Dy;
			for(int tx=-1;tx<=1;tx++){
				for(int ty=-1;ty<=1;ty++){
					double	SumD=0;
					for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
						FlexAreaImageListCoeffAndResult	*c=static_cast<FlexAreaImageListCoeffAndResult *>(a);
						SumD+=c->CalcCoeff(tx+dx ,ty+dy	,IBuff);
					}
					SumD=fabs(SumD);
					#pragma omp critical
					{
						if(SumD>MaxD){
							MaxD=SumD;
							MaxDx=tx+dx;
							MaxDy=ty+dy;
						}
					}
				}
			}
		}
	}
	delete	[]MList;
	Mx=MaxDx;
	My=MaxDy;
}
void	ParallelRoughMatch::MoveTo(int dx ,int dy)
{
	for(PureFlexAreaList *a=InsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
	for(PureFlexAreaList *a=OutsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
}
void	ParallelRoughMatch::Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col)
{
	QRgb	InsideCol=qRgba(col.red()/2,col.green()/2,col.blue()/2,col.alpha());
	for(PureFlexAreaList *a=InsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawAlpha(0,0,&pnt ,InsideCol
									,ZoomRate ,movx ,movy);
	}
	QRgb	OutsideCol=qRgba(col.red(),col.green(),col.blue(),col.alpha());
	for(PureFlexAreaList *a=OutsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawAlpha(0,0,&pnt ,OutsideCol
									,ZoomRate ,movx ,movy);
	}
	QRgb	TransCol=qRgba(255,col.green(),col.blue(),col.alpha());
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawImage(0,0,&pnt 
						,ZoomRate ,movx ,movy
						,true ,false ,false
						,0x80);
		a->DrawAlpha(0,0,&pnt ,TransCol
									,ZoomRate ,movx ,movy);
	}
	Pnt.setPen(Qt::red);
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeffAndResult	*c=static_cast<FlexAreaImageListCoeffAndResult *>(a);
		Pnt.drawLine((c->HStart+movx)*ZoomRate			,(c->Cy+movy)*ZoomRate
					,(c->HStart+c->HLen+movx)*ZoomRate	,(c->Cy+movy)*ZoomRate);
		Pnt.drawLine((c->Cx+movx)*ZoomRate				,(c->VStart+movy)*ZoomRate
					,(c->Cx+movx)*ZoomRate				,(c->VStart+c->VLen+movy)*ZoomRate);
	}
}

void	ParallelRoughMatch::Clear(void)
{
	TransZone.RemoveAll();
	OutsideZone.RemoveAll();
	InsideZone.RemoveAll();
}
	
bool	ParallelRoughMatch::Save(QIODevice *f)
{
	int32	H=TransZone.GetCount();
	if(::Save(f,H)==false)
		return false;
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeffAndResult *t=dynamic_cast<FlexAreaImageListCoeffAndResult *>(a);
		if(t->Save(f)==false)
			return false;
	}

	int32	N=InsideZone.GetCount();
	if(::Save(f,N)==false)
		return false;
	for(PureFlexAreaList *a=InsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	int32	M=OutsideZone.GetCount();
	if(::Save(f,M)==false)
		return false;
	for(PureFlexAreaList *a=OutsideZone.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	ParallelRoughMatch::Load(QIODevice *f)
{
	int32	H;
	if(::Load(f,H)==false)
		return false;
	TransZone.RemoveAll();
	for(int i=0;i<H;i++){
		FlexAreaImageListCoeffAndResult *a=new FlexAreaImageListCoeffAndResult();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		TransZone.AppendList(a);
	}

	int32	N;
	if(::Load(f,N)==false)
		return false;
	InsideZone.RemoveAll();
	for(int i=0;i<N;i++){
		PureFlexAreaList *a=new PureFlexAreaList();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		InsideZone.AppendList(a);
	}

	int32	M;
	if(::Load(f,M)==false)
		return false;
	OutsideZone.RemoveAll();
	for(int i=0;i<M;i++){
		PureFlexAreaList *a=new PureFlexAreaList();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		OutsideZone.AppendList(a);
	}

	return true;
}



void	ParallelDetalMatch::MakeArea(BYTE **CurrentBmp ,int XByte ,int YLen ,FlexAreaPointerContainer &Container)
{
	TransZone.RemoveAll();
	BYTE **mCurrentBmp=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(mCurrentBmp,0,XByte ,YLen);
	for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		p->GetArea()->MakeBitData(mCurrentBmp,XByte*8,YLen);
	}
	BYTE **TmpMap1=MakeMatrixBuff(XByte ,YLen);
	BYTE **TmpMap2=MakeMatrixBuff(XByte ,YLen);
	BYTE **SrcMap =MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(TmpMap1	,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);
	MatrixBuffCopy	(SrcMap		,XByte ,YLen
					,(const BYTE **)mCurrentBmp	,XByte ,YLen);

	Parent->GetLayersBase()->FatAreaN(mCurrentBmp
				,TmpMap2
				,XByte ,YLen 
				,Parent->ParamParent->TransDot);

	Parent->GetLayersBase()->ThinAreaN(TmpMap1
				,TmpMap2
				,XByte ,YLen 
				,Parent->ParamParent->TransDot);

	MatrixBuffXor	(mCurrentBmp,(const BYTE **)TmpMap1 ,XByte ,YLen);
	PureFlexAreaListContainer TransPack;
	PickupFlexArea(mCurrentBmp ,XByte ,XByte*8,YLen ,TransPack);
	for(PureFlexAreaList *a=TransPack.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeffAndResult	*b=new FlexAreaImageListCoeffAndResult();
		*b=*a;
		b->ExpandBitImage(SrcMap,0x80,XByte,YLen);
		//b->MakeSum();
		//b->SetCross(CurrentBmp ,XByte ,YLen);
		TransZone.AppendList(b);
	}
	FlexAreaImageList *k;
	#pragma omp parallel
	#pragma omp single private(k)
	for(k=TransZone.GetFirst();k!=NULL;k=k->GetNext()){
		#pragma omp task
		{
			FlexAreaImageListCoeffAndResult	*h=(FlexAreaImageListCoeffAndResult *)k;
			h->MakeSum();
			h->SetCross(Container,CurrentBmp ,XByte ,YLen);
		}
	}
	DeleteMatrixBuff(mCurrentBmp,YLen);	
	DeleteMatrixBuff(TmpMap1	,YLen);	
	DeleteMatrixBuff(TmpMap2	,YLen);	
	DeleteMatrixBuff(SrcMap		,YLen);	
}
void	ParallelDetalMatch::Match(ImageBuffer &IBuff ,int SearchArea ,int &Mx,int &My)
{
	int	N=(2*SearchArea+1)*(2*SearchArea+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dx=-SearchArea;dx<=SearchArea;dx+=3){
		for(int dy=-SearchArea;dy<=SearchArea;dy+=3){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int n=0;n<ShiftNumb;n++){
			int	dx=ShiftList[n].x;
			int	dy=ShiftList[n].y;
			MList[n].Dx=dx;
			MList[n].Dy=dy;

			double	SumP=0;
			for(FlexAreaImageList *k=TransZone.GetFirst();k!=NULL;k=k->GetNext()){
				FlexAreaImageListCoeffAndResult	*h=(FlexAreaImageListCoeffAndResult *)k;
				SumP+=h->CalcCross(dx,dy,IBuff);
			}
			MList[n].Coeff=fabs(SumP);
		}
	}


	/*
	int	MaxDx=0;
	int	MaxDy=0;
	double	MaxD=0;
	int	N=TransZone.GetCount();
	FlexAreaImageListCoeffAndResult **List=new FlexAreaImageListCoeffAndResult *[N];
	int	n=0;
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext(),n++){
		List[n]=static_cast<FlexAreaImageListCoeffAndResult *>(a);
	}
	int	Sep=N/10;
	if(Sep<=0)
		Sep=1;
	int	Isolation=Parent->ParamParent->TransDot/2;
	if(Isolation<=0)
		Isolation=1;

	XYClass	*ShiftList=new XYClass[(2*SearchArea+1)*(2*SearchArea+1)];
	int	ShiftNumb=0;
	for(int dy=-SearchArea;dy<=SearchArea;dy+=Isolation){
		for(int dx=-SearchArea;dx<=SearchArea;dx+=Isolation){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int k=0;k<ShiftNumb;k++){
			int	dx=ShiftList[k].x;
			int	dy=ShiftList[k].y;
			double	SumD=0;
			for(int i=0;i<N;i+=Sep){
				SumD+=List[i]->CalcCoeff(dx ,dy	,IBuff);
			}
			SumD=fabs(SumD);
			#pragma omp critical
			{
				if(SumD>MaxD){
					MaxD=SumD;
					MaxDx=dx;
					MaxDy=dy;
				}
			}
		}
	}
	delete	[]ShiftList;
	delete	[]List;

	MaxD=0;
	int	MaxKx=0;
	int	MaxKy=0;
	for(int dy=-Isolation;dy<=Isolation;dy++){
		for(int dx=-Isolation;dx<=Isolation;dx++){
			double	SumD=0;
			for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
				FlexAreaImageListCoeffAndResult	*c=static_cast<FlexAreaImageListCoeffAndResult *>(a);
				SumD+=c->CalcCoeff(dx+MaxDx ,dy+MaxDy	,IBuff);
			}
			SumD=fabs(SumD);
			if(SumD>MaxD){
				MaxD=SumD;
				MaxKx=dx;
				MaxKy=dy;					
			}
		}
	}
	Mx=MaxDx+MaxKx;
	My=MaxDy+MaxKy;
	*/
	delete	[]ShiftList;
	QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);

	int	Numb=ShiftNumb/1600;
	if(Numb<20)
		Numb=20;
	if(Numb>ShiftNumb)
		Numb=ShiftNumb;
	int	MaxDx=0;
	int	MaxDy=0;
	double	MaxD=0;
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<Numb;i++){
			int	dx=MList[i].Dx;
			int	dy=MList[i].Dy;
			for(int tx=-1;tx<=1;tx++){
				for(int ty=-1;ty<=1;ty++){
					double	SumD=0;
					for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
						FlexAreaImageListCoeffAndResult	*c=static_cast<FlexAreaImageListCoeffAndResult *>(a);
						SumD+=c->CalcCoeff(tx+dx ,ty+dy	,IBuff);
					}
					SumD=fabs(SumD);
					#pragma omp critical
					{
						if(SumD>MaxD){
							MaxD=SumD;
							MaxDx=tx+dx;
							MaxDy=ty+dy;
						}
					}
				}
			}
		}
	}
	delete	[]MList;
	Mx=MaxDx;
	My=MaxDy;
}
void	ParallelDetalMatch::MoveTo(int dx ,int dy)
{
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->MoveToNoClip(dx,dy);
	}
}
void	ParallelDetalMatch::GetCenter(double &Cx,double &Cy)
{
	double	SumCx=0;
	double	SumCy=0;
	int		N=0;
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		int	cx,cy;
		a->GetCenter(cx,cy);
		SumCx+=cx;
		SumCy+=cy;
		N++;
	}
	if(N>0){
		Cx=SumCx/N;
		Cy=SumCy/N;
	}
}
void	ParallelDetalMatch::Rotate(double Angle,double Cx,double Cy)
{
	double	CosS=cos(Angle);
	double	SinS=sin(Angle);
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		int	ex,ey;
		a->GetCenter(ex,ey);
		double	x= (ex-Cx)*CosS + (ey-Cy)*SinS + Cx;
		double	y=-(ex-Cx)*SinS + (ey-Cy)*CosS + Cy;
		int	dx=x-ex;
		int	dy=y-ey;
		a->MoveToNoClip(dx,dy);
	}
}
void	ParallelDetalMatch::Zoom(double ZoomX, double ZoomY ,double Cx,double Cy)
{
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		int	ex,ey;
		a->GetCenter(ex,ey);
		double	x= (ex-Cx)*ZoomX + Cx;
		double	y= (ey-Cy)*ZoomY + Cy;
		int	dx=x-ex;
		int	dy=y-ey;
		a->MoveToNoClip(dx,dy);
	}
}

void	ParallelDetalMatch::Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col)
{
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		a->DrawImage(0,0,&pnt 
						,ZoomRate ,movx ,movy
						,true ,false ,false
						,0x80);
		a->DrawAlpha(0,0,&pnt ,col.rgba()
									,ZoomRate ,movx ,movy);
	}
	Pnt.setPen(Qt::red);
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		FlexAreaImageListCoeffAndResult	*c=static_cast<FlexAreaImageListCoeffAndResult *>(a);
		Pnt.drawLine((c->HStart+movx)*ZoomRate			,(c->Cy+movy)*ZoomRate
					,(c->HStart+c->HLen+movx)*ZoomRate	,(c->Cy+movy)*ZoomRate);
		Pnt.drawLine((c->Cx+movx)*ZoomRate				,(c->VStart+movy)*ZoomRate
					,(c->Cx+movx)*ZoomRate				,(c->VStart+c->VLen+movy)*ZoomRate);
	}
}
void	ParallelDetalMatch::Clear(void)
{
	TransZone.RemoveAll();
}
bool	ParallelDetalMatch::Save(QIODevice *f)
{
	int32	H=TransZone.GetCount();
	if(::Save(f,H)==false)
		return false;
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

bool	ParallelDetalMatch::Load(QIODevice *f)
{
	int32	H;
	if(::Load(f,H)==false)
		return false;
	TransZone.RemoveAll();
	for(int i=0;i<H;i++){
		FlexAreaImageListCoeffAndResult *a=new FlexAreaImageListCoeffAndResult();
		if(a->Load(f)==false){
			delete	a;
			return false;
		}
		TransZone.AppendList(a);
	}
	return true;
}

bool	ParallelDetalMatch::IsEmpty(void)
{
	if(TransZone.IsEmpty()==true)
		return true;
	return false;
}


bool	MatchAutoLikeManual::CreateArea(FlexArea *Mask,BYTE **CurrentBmp,int XByte ,int YLen)
{
	MaskArea=*Mask;

	BYTE **TmpBmp=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(TmpBmp,0,XByte ,YLen);
	Mask->MakeBitData(TmpBmp ,XByte*8 ,YLen);
	MatrixBuffAnd	(TmpBmp,(const BYTE **)CurrentBmp ,XByte ,YLen);

	if(Parent->MatchAlignmentArea1.IsEmpty()==true){
		PureFlexAreaListContainer ItemPack;
		PickupFlexArea(TmpBmp ,XByte ,XByte*8,YLen ,ItemPack);

		int	W=Parent->GetDotPerLine()*ParamParent->RoughMatchAreaWidthRate;
		int	H=Parent->GetMaxLines()	 *ParamParent->RoughMatchAreaHeightRate;
		int	Xn=1.0/ParamParent->RoughMatchAreaWidthRate;
		int	Yn=1.0/ParamParent->RoughMatchAreaHeightRate;
		int	FixedXn=-1;
		int FixedYn=-1;
		FlexAreaPointerContainer	Container;

		for(int yi=1;yi<Yn;yi++){
			for(int xi=1;xi<Xn-1;xi++){
				PickupArea(xi*W,yi*H,W,H ,Container,ItemPack);
				double	D=SelfMatch(TmpBmp,XByte,YLen,Container,ParamParent->SearchAreaRoughMatch);
				if(D<ParamParent->MatchingRateToNeighbor){
					FixedXn=xi;
					FixedYn=yi;
					goto	JumpPoint1;
				}
			}
		}

	JumpPoint1:;
		if(FixedXn==-1 || FixedYn==-1){
			DeleteMatrixBuff(TmpBmp,YLen);
			return false;
		}
		AreaForRough.MakeArea(CurrentBmp,XByte ,YLen ,Container);
		AreaForParallel.MakeArea(CurrentBmp,XByte ,YLen ,Container);

		int	RotPosY=-1;
		for(int yi=Yn-2;yi>FixedYn;yi--){
			PickupArea(FixedXn*W,yi*H,W,H ,Container,ItemPack);
			double	D=SelfMatch(TmpBmp,XByte,YLen,Container,ParamParent->SearchAreaRoughMatch);
			if(D<ParamParent->MatchingRateToNeighbor){
				RotPosY=yi;
				break;
			}
		}
		if(RotPosY==-1){
			DeleteMatrixBuff(TmpBmp,YLen);
			return false;
		}
		AreaForRotate.MakeArea(CurrentBmp,XByte ,YLen ,Container);

		int	ZoomPosX=-1;
		if(FixedXn<Xn/2){
			for(int yi=Yn-2;yi>FixedYn;yi--){
				for(int xi=Xn-2;xi>FixedXn;xi--){
					PickupArea(xi*W,yi*H,W,H ,Container,ItemPack);
					double	D=SelfMatch(TmpBmp,XByte,YLen,Container,ParamParent->SearchAreaRoughMatch);
					if(D<ParamParent->MatchingRateToNeighbor){
						ZoomPosX=xi;
						goto	JumpPoint2;
					}
				}
			}
	JumpPoint2:;
			if(ZoomPosX==-1){
				DeleteMatrixBuff(TmpBmp,YLen);
				return false;
			}
			AreaForZoom.MakeArea(CurrentBmp,XByte ,YLen ,Container);
		}
		else{
			for(int yi=Yn-1;yi>FixedYn;yi--){
				for(int xi=0;xi<FixedXn;xi++){
					PickupArea(xi*W,yi*H,W,H ,Container,ItemPack);
					double	D=SelfMatch(TmpBmp,XByte,YLen,Container,ParamParent->SearchAreaRoughMatch);
					if(D<ParamParent->MatchingRateToNeighbor){
						ZoomPosX=xi;
						goto	JumpPoint3;
					}
				}
			}
	JumpPoint3:;
			if(ZoomPosX==-1){
				DeleteMatrixBuff(TmpBmp,YLen);
				return false;
			}
			AreaForZoom.MakeArea(CurrentBmp,XByte ,YLen ,Container);
		}
	}
	else{
		BYTE **TmpBmp2=MakeMatrixBuff(XByte ,YLen);
		MatrixBuffClear	(TmpBmp2,0,XByte ,YLen);
		for(MatchAlignmentArea *a=Parent->MatchAlignmentArea1.GetFirst();a!=NULL;a=a->GetNext()){
			a->Area.MakeBitData(TmpBmp2,XByte*8,YLen);
		}
		MatrixBuffAnd	(TmpBmp2,(const BYTE **)TmpBmp ,XByte ,YLen);

		PureFlexAreaListContainer ItemPack1;
		PickupFlexArea(TmpBmp2 ,XByte ,XByte*8,YLen ,ItemPack1);
		FlexAreaPointerContainer	Container1;
		for(PureFlexAreaList *s=ItemPack1.GetFirst();s!=NULL;s=s->GetNext()){
			FlexAreaPointerList	*t=new FlexAreaPointerList(s);
			Container1.AppendList(t);
		}
		AreaForRough.MakeArea(CurrentBmp,XByte ,YLen ,Container1);
		AreaForParallel.MakeArea(CurrentBmp,XByte ,YLen ,Container1);

		MatrixBuffClear	(TmpBmp2,0,XByte ,YLen);
		for(MatchAlignmentArea *a=Parent->MatchAlignmentArea2.GetFirst();a!=NULL;a=a->GetNext()){
			a->Area.MakeBitData(TmpBmp2,XByte*8,YLen);
		}
		MatrixBuffAnd	(TmpBmp2,(const BYTE **)TmpBmp ,XByte ,YLen);

		PureFlexAreaListContainer ItemPack2;
		PickupFlexArea(TmpBmp2 ,XByte ,XByte*8,YLen ,ItemPack2);
		FlexAreaPointerContainer	Container2;
		for(PureFlexAreaList *s=ItemPack2.GetFirst();s!=NULL;s=s->GetNext()){
			FlexAreaPointerList	*t=new FlexAreaPointerList(s);
			Container2.AppendList(t);
		}
		AreaForRotate.MakeArea(CurrentBmp,XByte ,YLen ,Container2);

		MatrixBuffClear	(TmpBmp2,0,XByte ,YLen);
		for(MatchAlignmentArea *a=Parent->MatchAlignmentArea3.GetFirst();a!=NULL;a=a->GetNext()){
			a->Area.MakeBitData(TmpBmp2,XByte*8,YLen);
		}
		MatrixBuffAnd	(TmpBmp2,(const BYTE **)TmpBmp ,XByte ,YLen);

		PureFlexAreaListContainer ItemPack3;
		PickupFlexArea(TmpBmp2 ,XByte ,XByte*8,YLen ,ItemPack3);
		FlexAreaPointerContainer	Container3;
		for(PureFlexAreaList *s=ItemPack3.GetFirst();s!=NULL;s=s->GetNext()){
			FlexAreaPointerList	*t=new FlexAreaPointerList(s);
			Container3.AppendList(t);
		}
		AreaForZoom.MakeArea(CurrentBmp,XByte ,YLen ,Container3);

		DeleteMatrixBuff(TmpBmp2,YLen);
	}
	DeleteMatrixBuff(TmpBmp,YLen);
	return true;
}


double	MatchAutoLikeManual::SelfMatch(BYTE **CurrentBmp,int XByte ,int YLen ,FlexAreaPointerContainer &Container ,int SearchDot)
{
	double	MaxD=0;
	int	MaxDx=0;
	int	MaxDy=0;
	int	N=Container.GetCount();
	FlexAreaPointerList **List=new FlexAreaPointerList *[N];
	int	n=0;
	for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext(),n++){
		List[n]=p;
	}
	int	Sep=N/10;
	if(Sep<=0)
		Sep=1;

	for(int dy=-SearchDot;dy<=SearchDot;dy+=ParamParent->DataIsolation){
		for(int dx=-SearchDot;dx<=SearchDot;dx+=ParamParent->DataIsolation){
			double	D=0;
			if(abs(dx)<ParamParent->NearByPattern && abs(dy)<ParamParent->NearByPattern)
				continue;
			//for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
				//D+=p->GetArea()->GetCrossBitCount(CurrentBmp,dx ,dy,XByte,YLen);
			for(int i=0;i<N;i+=Sep){
				D+=List[i]->GetArea()->GetCrossBitCount(CurrentBmp,dx ,dy,XByte,YLen,ParamParent->DataIsolation/2);
			}
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	delete	[]List;

	MaxD=0;
	for(int dy=-ParamParent->DataIsolation;dy<=ParamParent->DataIsolation;dy++){
		for(int dx=-ParamParent->DataIsolation;dx<=ParamParent->DataIsolation;dx++){
			double	D=0;
			int	Kx=MaxDx+dx;
			int	Ky=MaxDy+dy;
			if(abs(Kx)<ParamParent->NearByPattern && abs(Ky)<ParamParent->NearByPattern)
				continue;
			for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
				D+=p->GetArea()->GetCrossBitCount(CurrentBmp,Kx ,Ky,XByte,YLen);
			}
			if(MaxD<D){
				MaxD=D;
			}
		}
	}
	double	TotalPixels=0;
	for(FlexAreaPointerList *p=Container.GetFirst();p!=NULL;p=p->GetNext()){
		TotalPixels+=p->GetArea()->GetPatternByte();
	}
	if(TotalPixels==0.0)
		return 1.0;
	return MaxD/TotalPixels;
}

void	MatchAutoLikeManual::PickupArea(int x1,int y1,int W,int H ,FlexAreaPointerContainer &Container,PureFlexAreaListContainer &ItemPack)
{
	Container.RemoveAll();
	for(PureFlexAreaList *a=ItemPack.GetFirst();a!=NULL;a=a->GetNext()){
		int	fx1,fy1,fx2,fy2;
		a->GetXY(fx1,fy1,fx2,fy2);
		if(CheckOverlapRectRect( (long)x1,(long)y1,(long)x1+W,(long)y1+H
								,(long)fx1,(long)fy1,(long)fx2,(long)fy2)==true
		&& (fx2-fx1)<W && (fy2-fy1)<H){
			FlexAreaPointerList	*p=new FlexAreaPointerList(a);
			Container.AppendList(p);
		}
	}
}

void	MatchAutoLikeManual::ExecuteMatchFirst(void)
{
	ImageBuffer *ImageList[100];
	//Parent->GetTargetBuffList(ImageList);
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return;

	ImageBuffer	&IBuff=*ImageList[0];

	if(Parent->CheckValidity()==false)
		return;

	int	Mx,My;
	AreaForRough.RoughMatch(IBuff,ParamParent->SearchAreaRoughMatch ,Mx,My);
	if(Parent->CheckValidity()==false)
		return;
	MatchAutoLikeManualMove(Mx,My);
	if(Parent->CheckValidity()==false)
		return;

	AreaForRough	.MoveTo(Mx,My);
	AreaForParallel	.MoveTo(Mx,My);
	AreaForRotate	.MoveTo(Mx,My);
	AreaForZoom		.MoveTo(Mx,My);
	if(Parent->CheckValidity()==false)
		return;

	int	Dx,Dy;
	if(AreaForParallel.IsEmpty()==true)
		return;
	AreaForParallel.Match(IBuff,ParamParent->SearchAreaParallelMatch ,Dx,Dy);
	MatchAutoLikeManualMove(Dx,Dy);
	if(Parent->CheckValidity()==false)
		return;
	AreaForRough	.MoveTo(Dx,Dy);
	AreaForParallel	.MoveTo(Dx,Dy);
	AreaForRotate	.MoveTo(Dx,Dy);
	AreaForZoom		.MoveTo(Dx,Dy);
	if(Parent->CheckValidity()==false)
		return;

	double	Cx,Cy;
	AreaForParallel	.GetCenter(Cx,Cy);
	if(AreaForRotate.IsEmpty()==false){
		AreaForRotate.Match(IBuff,ParamParent->SearchAreaRotateMatch+ParamParent->SearchAreaRoughMatch ,Dx,Dy);
		if(Parent->CheckValidity()==false)
			return;
		double	Ex,Ey;
		AreaForRotate	.GetCenter(Ex,Ey);
		double	s1=GetSita(Ex-Cx,Ey-Cy);
		double	s2=GetSita(Ex-Cx+Dx,Ey-Cy+Dy);

		double	Angle=s2-s1;
		MatchAutoLikeManualRotation(Cx,Cy ,-360*Angle/(2.0*M_PI));

		if(Parent->CheckValidity()==false)
			return;

		AreaForRotate	.Rotate(-Angle,Cx,Cy);
		AreaForZoom		.Rotate(-Angle,Cx,Cy);
		if(Parent->CheckValidity()==false)
			return;
	}

	if(AreaForZoom.IsEmpty()==false){
		AreaForZoom.Match(IBuff,ParamParent->SearchAreaZoomMatch+ParamParent->SearchAreaRoughMatch ,Dx,Dy);
		if(Parent->CheckValidity()==false)
			return;
		double	Fx,Fy;
		AreaForZoom	.GetCenter(Fx,Fy);
		double	XZoomDir	=(Fx-Cx+Dx)/(Fx-Cx);
		double	YZoomDir	=(Fy-Cy+Dy)/(Fy-Cy);
		MatchAutoLikeManualZoom(Cx,Cy ,XZoomDir,YZoomDir);
		if(Parent->CheckValidity()==false)
			return;
		AreaForRotate	.Zoom(XZoomDir,YZoomDir ,Cx ,Cy);
		AreaForZoom		.Zoom(XZoomDir,YZoomDir ,Cx ,Cy);
		if(Parent->CheckValidity()==false)
			return;
	}
}

void	MatchAutoLikeManual::MatchAutoLikeManualMove(int Mx,int My)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				//if(a->GetID()==DbgGerberID1 || a->GetID()==DbgGerberID2)
				//	DbgGerber++;
				//if(item->IsCrossed(&MaskArea)==true){
					if(item->EnabledAutomatch==true){
						item->MoveToFloat(Mx,My);
					}
				//}
			}
		}
	}
}

void	MatchAutoLikeManual::MatchAutoLikeManualRotation(double	Cx,double Cy ,double Angle)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				//if(item->IsCrossed(&MaskArea)==true){
					item->Rotate(2*M_PI*Angle/360.0
							,Cx,Cy);
				//}
			}
		}
	}
}

void	MatchAutoLikeManual::MatchAutoLikeManualZoom(double Cx,double Cy ,double XZoomDir,double YZoomDir)
{
	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*item=static_cast<GerberFastItemBase *>(a);
			if(item!=NULL){
				//if(item->IsCrossed(&MaskArea)==true){
					item->Zoom(XZoomDir,YZoomDir
							 , Cx,Cy);
				//}
			}
		}
	}
}

FlexAreaImageListCoeffAndResult	&FlexAreaImageListCoeffAndResult::operator=(FlexArea &src)
{	
	FlexAreaImageListCoeff::operator=(src);
	return *this;
}
FlexAreaImageListCoeffAndResult	&FlexAreaImageListCoeffAndResult::operator=(FlexAreaImageListCoeffAndResult &src)
{
	FlexAreaImageListCoeff::operator=(*((FlexAreaImageListCoeff *)&src));
	FlexAreaImageListCoeffAndResult	*s=&src;
	if(s!=NULL){
		if(s->HData!=NULL){
			if(s->HLen!=HLen){
				if(HData!=NULL)
					delete	[]HData;
				HData=NULL;
			}
			HLen=s->HLen;
			if(HData==NULL){
				HData=new BYTE[HLen];
			}
			HStart=s->HStart;
			memcpy(HData,s->HData,HLen);
		}
		else{
			if(HData!=NULL){
				delete	[]HData;
				HData=NULL;
			}
			HLen=s->HLen;
			HStart=s->HStart;
		}
		if(s->VData!=NULL){
			if(s->VLen!=VLen){
				if(VData!=NULL)
					delete	[]VData;
				VData=NULL;
			}
			VLen=s->VLen;
			if(VData==NULL){
				VData=new BYTE[VLen];
			}
			VStart=s->VStart;
			memcpy(VData,s->VData,VLen);
		}
		else{
			if(VData!=NULL){
				delete	[]VData;
				VData=NULL;
			}
			VLen=s->VLen;
			VStart=s->VStart;
		}
		HSAvr	=s->HSAvr;
		HSS		=s->HSS;
		VSAvr	=s->VSAvr;
		VSS		=s->VSS;
	}
	return *this;
}

void	FlexAreaImageListCoeffAndResult::SetCross(FlexAreaPointerContainer &Container,BYTE **CurrentBmp ,int XByte ,int YLen)
{
	int	MaxOverLine=16;

	GetCenter(Cx,Cy);
	int	H=GetHeight();
	int	W=GetWidth();
	int	XLen=XByte*8;

	HLen=W+W/2;
	HStart=Cx-HLen/2;
	VLen=H+H/2;
	VStart=Cy-VLen/2;
	if(HData!=NULL){
		delete	[]HData;
	}
	HData=NULL;
	if(VData!=NULL){
		delete	[]VData;
	}
	VData=NULL;
	int	iHAvr=0;
	HSAvr=0;
	HSS=0;
	VSAvr=0;
	VSS=0;
	if(0<=Cy && Cy<YLen){
		for(int n=1;n<HLen;n++){
			int	X=HStart+n;
			if(0<=X && X<XLen){
				if(GetBmpBit(CurrentBmp,X,Cy)!=0){
					int	L=X-HStart;
					if(L>MaxOverLine){
						int	C=L-MaxOverLine;
						HStart=X-MaxOverLine;
						HLen-=C;
						break;
					}
				}
			}
		}
		for(int n=HLen-1;n>=0;n--){
			int	X=HStart+n;
			if(0<=X && X<XLen){
				if(GetBmpBit(CurrentBmp,X,Cy)!=0){
					int	L=HStart+HLen-X;
					if(L>MaxOverLine){
						HLen=X+MaxOverLine-HStart;
						break;
					}
				}
			}
		}
		if(HLen>0){
			HData=new BYTE[HLen];
			for(int n=0;n<HLen;n++){
				int	X=HStart+n;
				if(0<=X && X<XLen){
					if(GetBmpBit(CurrentBmp,X,Cy)==0){
						HData[n]=0;
					}
					else{
						HData[n]=1;
					}
				}
				else{
					HData[n]=2;
				}
			}
			int	L1=0;
			while(L1<HLen){
				BYTE	d=HData[L1];
				int	n;
				int	L2=L1+1;
				for(n=L1+1;n<HLen;n++){
					if(HData[n]!=d){
						L2=n-1;
						break;
					}
				}
				if(n>=HLen)
					break;
				if((L2-L1+1)>2*MaxOverLine){
					int	cL1=L1+MaxOverLine;
					int	cL2=L2-MaxOverLine;
					for(int i=cL1;i<cL2;i++){
						HData[i]=2;
					}
				}
				L1=L2+1;
			}
			for(int n=0;n<HLen;n++){
				if(HData[n]==0){
					iHAvr+=-1;
					HSS+=1.0;
				}
				else
				if(HData[n]==1){
					iHAvr+=1;
					HSS+=1.0;
				}
			}
		}
		else{
			HLen=0;
		}
	}
	int	iVAvr=0;
	if(0<=Cx && Cx<XLen){
		for(int n=1;n<VLen;n++){
			int	Y=VStart+n;
			if(0<=Y && Y<YLen){
				if(GetBmpBit(CurrentBmp,Cx,Y)!=0){
					int	L=Y-VStart;
					if(L>MaxOverLine){
						int	C=L-MaxOverLine;
						VStart=Y-MaxOverLine;
						VLen-=C;
						break;
					}
				}
			}
		}
		for(int n=VLen-1;n>=0;n--){
			int	Y=VStart+n;
			if(0<=Y && Y<YLen){
				if(GetBmpBit(CurrentBmp,Cx,Y)!=0){
					int	L=VStart+VLen-Y;
					if(L>MaxOverLine){
						VLen=Y+MaxOverLine-VStart;
						break;
					}
				}
			}
		}
		if(VLen>0){
			VData=new BYTE[VLen];
			for(int n=0;n<VLen;n++){
				int	Y=VStart+n;
				if(0<=Y && Y<YLen){
					if(GetBmpBit(CurrentBmp,Cx,Y)==0){
						VData[n]=0;
					}
					else{
						VData[n]=1;
					}
				}
				else{
					VData[n]=2;
				}
			}
			int	L1=0;
			while(L1<VLen){
				BYTE	d=VData[L1];
				int	n;
				int	L2=L1+1;
				for(n=L1+1;n<VLen;n++){
					if(VData[n]!=d){
						L2=n-1;
						break;
					}
				}
				if(n>=VLen)
					break;
				if((L2-L1+1)>2*MaxOverLine){
					int	cL1=L1+MaxOverLine;
					int	cL2=L2-MaxOverLine;
					for(int i=cL1;i<cL2;i++){
						VData[i]=2;
					}
				}
				L1=L2+1;
			}
			for(int n=0;n<VLen;n++){
				if(VData[n]==0){
					iVAvr+=-1;
					VSS+=1.0;
				}
				else
				if(VData[n]==1){
					iVAvr+=1;
					VSS+=1.0;
				}
			}
		}
		else{
			VLen=0;
		}
	}
	int	N=HLen+VLen;
	HSAvr=iHAvr;
	VSAvr=iVAvr;
}

double	FlexAreaImageListCoeffAndResult::CalcCross(int dx ,int dy ,ImageBuffer &Buff)
{
	int	XLen=Buff.GetWidth();
	int	YLen=Buff.GetHeight();

	double	HDAvr=0;
	double	HDD=0;
	double	HSD=0;
	double	HP=0;
	if(0<=(Cy+dy) && (Cy+dy)<YLen){
		if(0<=(dx+HStart) && (dx+HStart+HLen)<XLen){
			BYTE	*dp=Buff.GetY(Cy+dy);
			for(int n=0;n<HLen;n++){
				if(HData[n]==2)
					continue;
				int	X=dx+HStart+n;
				if(0<=X && X<XLen){
					BYTE	d=dp[X];
					HDAvr+=d;
					HDD +=d*d;
					if(HData[n]==0){
						HSD +=-d;
					}
					else
					if(HData[n]==1){
						HSD +=d;
					}
				}
			}
			if(HSS==0){
				HP=0.0;
			}
			else{
				double	HAs=HSAvr/HSS;
				double	HBs=HDAvr/HSS;
				double	HD=(HSS-HAs*HAs*HSS)*(HDD-HBs*HBs*HSS);
				if(HD<0)
					return 0;
				if(HD>0)
					HP=(HSD-HAs*HBs*HSS)/sqrt(HD);
			}
		}
		else{
			int	Numb=0;
			double	tHSAvr=0;
			BYTE	*dp=Buff.GetY(Cy+dy);
			for(int n=0;n<HLen;n++){
				if(HData[n]==2)
					continue;
				int	X=dx+HStart+n;
				if(0<=X && X<XLen){
					BYTE	d=dp[X];
					HDAvr+=d;
					HDD +=d*d;
					if(HData[n]==0){
						tHSAvr+=-1;
						HSD +=-d;
					}
					else
					if(HData[n]==1){
						tHSAvr+=1;
						HSD +=d;
					}
					Numb++;
				}
			}
			if(Numb==0){
				HP=0.0;
			}
			else{
				double	HAs=tHSAvr/Numb;
				double	HBs=HDAvr/Numb;
				double	HD=(Numb-HAs*HAs*Numb)*(HDD-HBs*HBs*Numb);
				if(HD<0)
					return 0;
				if(HD>0)
					HP=(HSD-HAs*HBs*Numb)/sqrt(HD);
			}
		}
	}
	double	VDAvr=0;
	double	VDD=0;
	double	VSD=0;
	double	VP=0;
	int	X=dx+Cx;
	if(0<=X && X<XLen){
		if(0<=(dy+VStart) && (dy+VStart+VLen)<YLen){
			for(int n=0;n<VLen;n++){
				if(VData[n]==2)
					continue;
				int	Y=dy+VStart+n;
				if(0<=Y && Y<YLen){
					BYTE	*dp=Buff.GetY(Y);
					BYTE	d=dp[X];
					VDAvr+=d;
					VDD +=d*d;
					if(VData[n]==0){
						VSD +=-d;
					}
					else
					if(VData[n]==1){
						VSD +=d;
					}
				}
			}
			if(VSS==0){
				VP=0.0;
			}
			else{
				double	VAs=VSAvr/VSS;
				double	VBs=VDAvr/VSS;
				double	VD=(VSS-VAs*VAs*VSS)*(VDD-VBs*VBs*VSS);
				if(VD<0)
					return 0;
				if(VD>0)
					VP=(VSD-VAs*VBs*VSS)/sqrt(VD);
			}
		}
		else{
			int	Numb=0;
			double	tVSAvr=0;
			for(int n=0;n<VLen;n++){
				if(VData[n]==2)
					continue;
				int	Y=dy+VStart+n;
				if(0<=Y && Y<YLen){
					BYTE	*dp=Buff.GetY(Y);
					BYTE	d=dp[X];
					VDAvr+=d;
					VDD +=d*d;
					if(VData[n]==0){
						tVSAvr+=-1;
						VSD +=-d;
					}
					else
					if(VData[n]==1){
						tVSAvr+=1;
						VSD +=d;
					}
					Numb++;
				}
			}
			if(Numb==0){
				VP=0.0;
			}
			else{
				double	VAs=tVSAvr/Numb;
				double	VBs=VDAvr/Numb;
				double	VD=(Numb-VAs*VAs*Numb)*(VDD-VBs*VBs*Numb);
				if(VD<0)
					return 0;
				if(VD>0)
					VP=(VSD-VAs*VBs*Numb)/sqrt(VD);
			}
		}
	}
	if(HP==0.0)
		return VP;
	if(VP==0.0)
		return HP;
	return HP*HP+VP*VP;
}

void	FlexAreaImageListCoeffAndResult::DrawCross(QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &col)
{
	int	X1=(HStart		+movx)*ZoomRate;
	int	X2=(HStart+HLen	+movx)*ZoomRate;
	int	Y =(Cy			+movy)*ZoomRate;
	QRgb	R=qRgba(255,0,0,180);
	QRgb	B=qRgba(0,0,0,180);
	if(0<=X2 && X1<pnt.width() && 0<=Y && Y<pnt.height()){
		X1=max(X1,0);
		X2=min(X2,pnt.width());
		double	Z=1.0/ZoomRate;
		QRgb	*d=(QRgb *)pnt.scanLine(Y);
		for(int	x=X1;x<X2;x++){
			int	L=x*Z-movx-HStart;
			if(0<=L && L<HLen){
				if(HData[L]==0)
					d[x]=col.rgba();
				else if(HData[L]==1)
					d[x]=R;
				else
					d[x]=B;
			}
		}
	}

	int	X =(Cx			+movx)*ZoomRate;
	int	Y1=(VStart		+movy)*ZoomRate;
	int	Y2=(VStart+VLen +movy)*ZoomRate;
	if(0<=X && X<pnt.width() && 0<=Y2 && Y1<pnt.height()){
		Y1=max(Y1,0);
		Y2=min(Y2,pnt.height());
		double	Z=1.0/ZoomRate;
		for(int	y=Y1;y<Y2;y++){
			QRgb	*d=(QRgb *)pnt.scanLine(y);
			int	L=y*Z-movy-VStart;
			if(0<=L && L<VLen){
				if(VData[L]==0)
					d[X]=col.rgba();
				else if(VData[L]==1)
					d[X]=R;
				else
					d[X]=B;
			}
		}
	}
}

void	MatchAutoLikeManual::Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();

	AreaForRough	.Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Base->AutoMatchManualColorParallel);

	AreaForParallel	.Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Base->AutoMatchManualColorParallel);
	AreaForRotate	.Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Base->AutoMatchManualColorRotation);
	AreaForZoom		.Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Base->AutoMatchManualColorZooming);
}


void	MatchAutoLikeManual::Clear(void)
{
	AreaForRough.Clear();
	AreaForParallel.Clear();
	AreaForRotate.Clear();
	AreaForZoom.Clear();
}


bool	MatchAutoLikeManual::Save(QIODevice *f)
{
	if(MaskArea.Save(f)==false)
		return false;
	if(AreaForRough.Save(f)==false)
		return false;
	if(AreaForParallel.Save(f)==false)
		return false;
	if(AreaForRotate.Save(f)==false)
		return false;
	if(AreaForZoom.Save(f)==false)
		return false;


	return true;
}

bool	MatchAutoLikeManual::Load(QIODevice *f)
{
	if(Parent->GetLoadedVersion()>=5){
		if(MaskArea.Load(f)==false)
			return false;
	}
	else{
		MaskArea.SetRectangle(0,0,Parent->GetDotPerLine(),Parent->GetMaxLines());
	}
	if(AreaForRough.Load(f)==false)
		return false;
	if(AreaForParallel.Load(f)==false)
		return false;
	if(AreaForRotate.Load(f)==false)
		return false;
	if(AreaForZoom.Load(f)==false)
		return false;

	return true;
}
ParallelRoughMatch::ParallelRoughMatch(MatchAutoLikeManual *parent)
	:Parent(parent)
{
}

ParallelDetalMatch::ParallelDetalMatch(MatchAutoLikeManual *parent)
:Parent(parent)
{
}

MatchAutoLikeManual::MatchAutoLikeManual(MatchAutoLikeManualContainer *parent)
	:ServiceForLayers(parent->GetLayersBase())
	,AreaForRough(this)
	,AreaForParallel(this)
	,AreaForRotate(this)
	,AreaForZoom(this)
	,Parent(parent->Parent)
	,ParamParent(parent)
{
}
MatchAutoLikeManual::MatchAutoLikeManual(LayersBase *p)
	:ServiceForLayers(p)
	,AreaForRough(this)
	,AreaForParallel(this)
	,AreaForRotate(this)
	,AreaForZoom(this)
	,Parent(NULL)
	,ParamParent(NULL)
{
}
LayersBase	*MatchAutoLikeManualContainer::GetLayersBase(void)
{
	return Parent->GetLayersBase();
}

void	MatchAutoLikeManualContainer::Draw(QPainter &Pnt,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	for(MatchAutoLikeManual *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->Draw(Pnt,pnt, movx ,movy ,ZoomRate ,Attr);
	}
	for(PureFlexAreaList *a=PartialPack.GetFirst();a!=NULL;a=a->GetNext()){
		a->Draw(0,0,&pnt,qRgba(255,0,255,64)
									,ZoomRate ,movx ,movy);
	}
	/*
	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			for(FlexAreaImageList *t=Item->TransDetail.GetFirst();t!=NULL;t=t->GetNext()){
						t->DrawImage(0,0,&pnt 
									,ZoomRate ,movx ,movy				
									,false,false ,true
									,0x80);
			}
		}
	}
	*/
}

bool	MatchAutoLikeManualContainer::CreateArea(void)
{
	bool	SwapMode=false;
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();
	if(((double)Parent->GetDotPerLine())*((double)Parent->GetMaxLines())>=((double)Parent->GetParamGlobal()->SwapOutSizeMegaByte)*1000.0*1000.0){
		GetLayersBase()->SwapImageOutOfBuffer();
		SwapMode=true;
	}

	int	XByte=(Parent->GetDotPerLine()+7)/8;
	int	YLen=Parent->GetMaxLines();

	BYTE **CurrentBmp=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(CurrentBmp,0,XByte ,YLen);
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	if(AdpptedLayer<10000){
		int	Row=0;
		for(GerberFileLayer *f=Parent->FileLayerList.GetFirst();f!=NULL;f=f->GetNext(),Row++){
			if(Row==AdpptedLayer){
				ButtonsToOperateLayer.Add(true);
			}
			else{
				ButtonsToOperateLayer.Add(false);
			}
		}
	}
	else{
		int	Row=0;
		for(GerberCompositeLayer *f=Parent->CompositeLayer.GetFirst();f!=NULL;f=f->GetNext(),Row++){
			if(Row==(AdpptedLayer%10000)){
				OperateCompositeIDList.Add(f->CompositeID);
			}
		}
	}
	int	LayerID=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),LayerID++){
		Parent->MakeImage(CurrentBmp,LayerID,true);
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int	CompositeID=b->GetValue();
		Parent->MakeImage(CurrentBmp,CompositeID,false);
	}

	PureFlexAreaListContainer MaskPack;
	ConstMapBufferListContainer MaskMap;
	if(Parent->GetReflectionMap(_Reflection_Mask,MaskMap)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		PickupFlexAreaWhole(Map.GetBitMap(),XByte ,XByte*8,YLen ,MaskPack);
	}

	RemoveAll();
	for(PureFlexAreaList *Mask=MaskPack.GetFirst();Mask!=NULL;Mask=Mask->GetNext()){
		MatchAutoLikeManual	*s=new MatchAutoLikeManual(this);
		s->CreateArea(Mask,CurrentBmp,XByte ,YLen);
		AppendList(s);
	}
	DeleteMatrixBuff(CurrentBmp,YLen);

	if(SwapMode==true){
		GetLayersBase()->SwapImageInToBuffer();
	}
	return true;
}


bool	MatchAutoLikeManualContainer::CreateDetail(void)
{
	bool	SwapMode=false;
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();
	if(((double)Parent->GetDotPerLine())*((double)Parent->GetMaxLines())>=((double)Base->GetParamGlobal()->SwapOutSizeMegaByte)*1000.0*1000.0){
		GetLayersBase()->SwapImageOutOfBuffer();
		SwapMode=true;
	}

	int	XByte=(Parent->GetDotPerLine()+7)/8;
	int	YLen=Parent->GetMaxLines();
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	int	Row=0;
	for(GerberFileLayer *f=Parent->FileLayerList.GetFirst();f!=NULL;f=f->GetNext(),Row++){
		if(Row==AdpptedLayer){
			ButtonsToOperateLayer.Add(true);
		}
		else{
			ButtonsToOperateLayer.Add(false);
		}
	}
	if(AdpptedLayer>=10000){
		Row=0;
		for(GerberCompositeLayer *f=Parent->CompositeLayer.GetFirst();f!=NULL;f=f->GetNext(),Row++){
			if(Row==(AdpptedLayer%10000)){
				OperateCompositeIDList.Add(f->CompositeID);
			}
		}
	}

	if(Parent->CheckValidity()==false){
		if(SwapMode==true){
			GetLayersBase()->SwapImageInToBuffer();
		}

		return false;
	}
	
	//PartiallyMatch(MaskMap ,SearchAreaMatchDetail
	//			, ButtonsToOperateLayer
	//			, ButtonsToOperateComposite);

	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			Item->ResetCalcDone();
		}
	}

	ConstMapBufferListContainer MaskMap;
	if(Parent->GetReflectionMap(_Reflection_Mask,MaskMap)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		int	N=0;
		for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
			GerberFileLayer	*F=Parent->FileLayerList[N];
			if(b->GetValue()==true && F!=NULL){
				for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
					if(Item!=NULL){
						if(Item->GetFileLayerID()==F->GetFileLayerID()){
							if(Item->GetID()==2799 && Parent->GetPage()==2)
								DbgIDMode++;
							Item->MakeTransDetailArea(Map ,TransDot);
						}
					}
				}
			}
		}
	
		for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
			int CompositeID=b->GetValue();
			GerberCompositeLayer	*CL=Parent->SearchCompositeLayer(CompositeID);
			if(b->GetValue()==true && CL!=NULL){
				GerberCompositeDefLayer	*CDef=Base->CompositeDef.Search(CompositeID);
				for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
					GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
					if(Item!=NULL){
						if(Item->GetCompositeID()==CompositeID){
							Item->MakeTransDetailArea(Map ,TransDot);
						}
					}
				}
			}
		}
	}
	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			Item->ResetCalcDone();
		}
	}

	if(SwapMode==true){
		GetLayersBase()->SwapImageInToBuffer();
	}
	return true;
}
void	MatchAutoLikeManualContainer::Clear(void)
{
	RemoveAll();
	PartialPack.RemoveAll();
}

void	MatchAutoLikeManualContainer::ExecuteMatchFirst(void)
{
	for(MatchAutoLikeManual *s=GetFirst();s!=NULL;s=s->GetNext()){
		s->ExecuteMatchFirst();
	}
}


void	MatchAutoLikeManualContainer::PartiallyMatch(ConstMapBuffer &MaskMap ,int SesarchDot
													, BoolList &ButtonsToOperateLayer
													, IntList &OperateCompositeIDList)

{
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();

	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			Item->ResetCalcDone();
		}
	}

	int	XByte=(Parent->GetDotPerLine()+7)/8;
	int	YLen = Parent->GetMaxLines();

	BYTE	**BmpMap=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear	(BmpMap ,0,XByte ,YLen);

	int	N=0;
	for(BoolClass *b=ButtonsToOperateLayer.GetFirst();b!=NULL;b=b->GetNext(),N++){
		GerberFileLayer	*F=Parent->FileLayerList[N];
		if(b->GetValue()==true && F!=NULL){
			for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						Item->MakeImage(BmpMap ,0,0,XByte ,YLen);
					}
				}
			}
		}
	}
	for(IntClass *b=OperateCompositeIDList.GetFirst();b!=NULL;b=b->GetNext()){
		int CompositeID=b->GetValue();
		GerberCompositeLayer	*CL=Parent->SearchCompositeLayer(CompositeID);
		if(b->GetValue()==true && CL!=NULL){
			GerberCompositeDefLayer	*CDef=Base->CompositeDef.Search(CompositeID);
			for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						Item->MakeImage(BmpMap ,0,0,XByte ,YLen);
					}
				}
			}
		}
	}
	BYTE	**TmpMap=MakeMatrixBuff(XByte ,YLen);
	BYTE	**ThinMap=MakeMatrixBuff(XByte ,YLen);
	BYTE	**BaseMap=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(ThinMap	,XByte ,YLen
					,(const BYTE **)BmpMap ,XByte ,YLen);
	MatrixBuffCopy	(BaseMap	,XByte ,YLen
					,(const BYTE **)BmpMap ,XByte ,YLen);
	GetLayersBase()->FatAreaN(BmpMap
				,TmpMap
				,XByte ,YLen
				,TransDot);
	GetLayersBase()->ThinAreaN(ThinMap
				,TmpMap
				,XByte ,YLen
				,TransDot);
	MatrixBuffXor	(BmpMap,(const BYTE **)ThinMap,XByte ,YLen);
	MatrixBuffAnd	(BmpMap ,(const BYTE **)MaskMap.GetBitMap() ,XByte ,YLen);
	DeleteMatrixBuff(ThinMap,YLen);
	DeleteMatrixBuff(TmpMap,YLen);

	PureFlexAreaListContainer TPack;
	PickupFlexArea(BmpMap ,XByte ,XByte*8,YLen ,TPack);
	PartialPack.RemoveAll();
	int		PickupLength=TransDot*3;
	for(PureFlexAreaList *a=TPack.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetWidth()<PickupLength*2 && a->GetHeight()<PickupLength*2){
			PureFlexAreaList *b=new PureFlexAreaList(*a);
			PartialPack.AppendList(b);
		}
		else if(a->GetWidth()<PickupLength*2){
			PureFlexAreaList *T=new PureFlexAreaList(*a);
			PureFlexAreaList *B=new PureFlexAreaList(*a);
			T->ClipArea(a->GetMinX(),a->GetMinY(),a->GetMaxX(),a->GetMinY()+PickupLength);
			B->ClipArea(a->GetMinX(),a->GetMaxY()-PickupLength,a->GetMaxX(),a->GetMaxY());
			PartialPack.AppendList(T);
			PartialPack.AppendList(B);
		}
		else if(a->GetHeight()<PickupLength*2){
			PureFlexAreaList *L=new PureFlexAreaList(*a);
			PureFlexAreaList *R=new PureFlexAreaList(*a);
			L->ClipArea(a->GetMinX(),a->GetMinY(),a->GetMinX()+PickupLength,a->GetMaxY());
			R->ClipArea(a->GetMaxX()-PickupLength,a->GetMinY(),a->GetMaxX(),a->GetMaxY());
			PartialPack.AppendList(L);
			PartialPack.AppendList(R);
		}
		else{
			PureFlexAreaList *L=new PureFlexAreaList(*a);
			PureFlexAreaList *R=new PureFlexAreaList(*a);
			PureFlexAreaList *T=new PureFlexAreaList(*a);
			PureFlexAreaList *B=new PureFlexAreaList(*a);
			L->ClipArea(a->GetMinX(),a->GetMinY(),a->GetMinX()+PickupLength,a->GetMaxY());
			R->ClipArea(a->GetMaxX()-PickupLength,a->GetMinY(),a->GetMaxX(),a->GetMaxY());
			T->ClipArea(a->GetMinX(),a->GetMinY(),a->GetMaxX(),a->GetMinY()+PickupLength);
			B->ClipArea(a->GetMinX(),a->GetMaxY()-PickupLength,a->GetMaxX(),a->GetMaxY());
			PartialPack.AppendList(L);
			PartialPack.AppendList(R);
			PartialPack.AppendList(T);
			PartialPack.AppendList(B);
		}
	}

	DeleteMatrixBuff(BmpMap,YLen);

	int	DivNumbX=6;
	int	DivNumbY=15;

	int	DivLenX	=Parent->GetDotPerLine()/DivNumbX;
	int	DivLenY	=Parent->GetMaxLines()  /DivNumbY;

	ImageBuffer *ImageList[100];
	//Parent->GetTargetBuffList(ImageList);
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return;

	ImageBuffer	&Ibuff=*ImageList[0];

	for(int yn=0;yn<DivNumbY;yn++){
		for(int xn=0;xn<DivNumbX;xn++){
			int	Mx,My;
			int	AreaX1=xn*DivLenX;
			int	AreaY1=yn*DivLenY;
			int	AreaX2=AreaX1+DivLenX;
			int	AreaY2=AreaY1+DivLenY;
			if(Parent->GetPage()==DbgPage
			&& AreaX1<=DbgX && DbgX<AreaX2
			&& AreaY1<=DbgY && DbgY<AreaY2)
				DbgGerber++;

   			PartiallyMatchSlight(Ibuff,PartialPack,BaseMap,XByte,YLen
								,AreaX1,AreaY1,AreaX2,AreaY2
								,0,0,Mx,My
								,SesarchDot ,2);
			int	Dx,Dy;
			PartiallyMatchSlight(Ibuff,PartialPack,BaseMap,XByte,YLen
								,AreaX1,AreaY1,AreaX2,AreaY2
								,Mx,My,Dx,Dy
								,3 ,1);
			for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL && Item->IsCalced()==false){
					if(Item->GetID()==DbgGerberID)
						DbgGerber++;
					double	x1,y1,x2,y2;
					Item->GetXY(x1,y1,x2,y2);
					double	Cx=(x1+x2)/2;
					double	Cy=(y1+y2)/2;
					if(AreaX1<=Cx && AreaY1<=Cy	&& Cx<AreaX2 && Cy<AreaY2){
						if(Item->EnabledAutomatch==true){
							Item->MoveToFloat(-Dx, -Dy);
						}
						Item->SetCalcDone(true);	
					}
				}
			}
		}
	}
	DeleteMatrixBuff(BaseMap,YLen);
}

void	MatchAutoLikeManualContainer::PartiallyMatchSlight(ImageBuffer &Ibuff
								,PureFlexAreaListContainer &FPack,BYTE **BaseMap,int XByte,int YLen
								,int AreaX1,int AreaY1,int AreaX2,int AreaY2
								,int dx,int dy,int &Mx,int &My
								,int TransDot ,int Sep)
{
	double	MaxD=0;
	Mx=0;
	My=0;
	FlexAreaPointerContainer	ContainerD;
	FlexAreaPointerContainer	Container;
	int	Numb=0;
	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		 if(f->CheckOverlapRectangle(AreaX1-TransDot,AreaY1-TransDot,AreaX2+TransDot,AreaY2+TransDot)==true){
			 ContainerD.Add(f);
			 Numb++;
		 }
	}
	int		AdoptedNumb=20;
	int		ListSep=Numb/AdoptedNumb;
	if(ListSep==0)
		ListSep=1;
	for(int i=0;i<AdoptedNumb && i<Numb;i++){
		FlexAreaPointerList *f=ContainerD[i*ListSep];
		Container.Add(f->GetArea());
	}

	int	N=(2*TransDot+1)*(2*TransDot+1);

	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int x=-TransDot;x<TransDot;x+=Sep){
		for(int y=-TransDot;y<TransDot;y+=Sep){
			ShiftList[ShiftNumb].x=x;
			ShiftList[ShiftNumb].y=y;
			ShiftNumb++;
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<ShiftNumb;i++){
			double	TotalD=0;
			for(FlexAreaPointerList *f=Container.GetFirst();f!=NULL;f=f->GetNext()){
 				double	D=PartiallyMatchSlight(Ibuff
									,f->GetArea(),BaseMap,XByte,YLen

									,AreaX1,AreaY1,AreaX2,AreaY2
									,dx+ShiftList[i].x
									,dy+ShiftList[i].y);
				TotalD+=D*D;
			}
			#pragma omp critical
			{
				if(TotalD>MaxD){
					MaxD=TotalD;
					Mx=dx+ShiftList[i].x;
					My=dy+ShiftList[i].y;
				}
			}
		}
	}
	delete	[]ShiftList;
 }


double	MatchAutoLikeManualContainer::PartiallyMatchSlight(ImageBuffer &Ibuff
								,FlexArea *f,BYTE **BaseMap,int XByte,int YLen
								,int AreaX1,int AreaY1,int AreaX2,int AreaY2
								,int dx,int dy)
{
	int64	A	=0;
	int64	AA	=0;
	int		B	=0;
	int		BB	=0;
	int64	AB	=0;
	int		DNumb=0;
	int	XLen=XByte*8;

	for(int i=0;i<f->GetFLineLen();i++){
		int	y	=f->GetFLineAbsY(i);
		int	Y	=y+dy;
		if(y<AreaY1 || Y<AreaY1 || AreaY2<=y || AreaY2<=Y)
			continue;
		int	Left=f->GetFLineLeftX(i);
		int	Numb=f->GetFLineNumb(i);
		BYTE	*s=Ibuff.GetY(y);
		BYTE	*d=BaseMap[Y];
		int		StartX=0;
		if(Left<AreaX1)
			StartX=AreaX1-Left;
		if(Left+StartX+dx<AreaX1)
			StartX=AreaX1-Left-dx;
		if(Left+Numb>AreaX2)
			Numb=AreaX2-Left;
		if(Left+Numb+dx<AreaX1)
			Numb=AreaX2-Left-dx;

		for(int n=StartX;n<Numb;n++){
			int	x=Left+n;
			int	X=Left+dx+n;
			int	c=s[x];
			A+=c;
			AA+=c*c;
			if(GetBmpBitOnY(d,X)!=0){
				B+=1;
				BB+=1;
				AB+=c;
			}
			else{
				B-=1;
				BB+=1;
				AB-=c;
			}
			DNumb++;
		}
	}
	if(DNumb==0)
		return 0;

	double	AvrS=(double)A/(double)DNumb;
	double	AvrD=(double)B/(double)DNumb;

	double	D=((double)AA-DNumb*AvrS*AvrS)*((double)BB-DNumb*AvrD*AvrD);
	if(D<=0){
		return 0;
	}
	D=sqrt(D);
	double	K=(double)AB-DNumb*AvrS*AvrD;
	return K/D;
}

class	Matching2DList : public NPList<Matching2DList>
{
public:
	double	PosXOnTarget,PosYOnTarget;
	double	ShiftX		,ShiftY;

};


void	MatchAutoLikeManualContainer::ExecuteMatchDetail(bool BrighterInPattern)
{
	GerberFastBase	*GBase=(GerberFastBase *)Parent->GetParentBase();
	int	EdgeMergin=GBase->AutoMatchingEdgeOmitDot;

	ImageBuffer *ImageList[100];
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return;

	ImageBuffer	&Ibuff=*ImageList[0];

	int	Isolation=2;
	int	SearchAreaDot=SearchAreaMatchDetail;
	int	N=(2*SearchAreaDot+1)*(2*SearchAreaDot+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	struct	MatchList	*WList=new struct	MatchList[N];	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dy=-SearchAreaDot;dy<=SearchAreaDot;dy+=Isolation){
		for(int dx=-SearchAreaDot;dx<=SearchAreaDot;dx+=Isolation){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}


	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==false){
				bool	LeftFix=false;
				bool	RightFix=false;
				bool	TopFix=false;
				bool	BottomFix=false;
				int		LimitSize=300;

				//****
				#pragma omp parallel
				{
					#pragma omp for
					for(int n=0;n<ShiftNumb;n++){
						int	dx=ShiftList[n].x;
						int	dy=ShiftList[n].y;
						double	D=Item->TransDetail.MatchExecute(Item ,dx ,dy
																,EdgeMergin,EdgeMergin,Parent->GetDotPerLine()-EdgeMergin ,Parent->GetMaxLines()-EdgeMergin
																,GBase->UseBrighterInPattern,BrighterInPattern);
						MList[n].Coeff=D*D;
						MList[n].Dx=dx;
						MList[n].Dy=dy;
					}
				}
				QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);
		
				if(MList[0].Coeff>0.0){
					int	Numb=5;
					if(Numb>ShiftNumb)
						Numb=ShiftNumb;
					int	WNumb=0;
					for(int i=0;i<Numb;i++){
						for(int tx=-Isolation;tx<=Isolation;tx++){
							for(int ty=-Isolation;ty<=Isolation;ty++){
								WList[WNumb].Dx=MList[i].Dx+tx;
								WList[WNumb].Dy=MList[i].Dy+ty;
								WNumb++;
							}
						}
					}

					int	MaxDx=MList[0].Dx;
					int	MaxDy=MList[0].Dy;
					if(MList[0].Coeff>0.0001){
						if(Isolation>1){
							double	MaxD=0;
							#pragma omp parallel
							{
								#pragma omp for
								for(int i=0;i<WNumb;i++){
									int	dx=WList[i].Dx;
									int	dy=WList[i].Dy;
									double	D=Item->TransDetail.MatchExecute(Item ,dx ,dy
																			,EdgeMergin,EdgeMergin,Parent->GetDotPerLine()-EdgeMergin ,Parent->GetMaxLines()-EdgeMergin
																			,GBase->UseBrighterInPattern,BrighterInPattern);
									D=D*D;
									#pragma omp critical
									{
										if(D>MaxD){
											MaxD=D;
											MaxDx=dx;
											MaxDy=dy;
										}
									}
								}
							}
						}

						//Item->MoveToFloat(MaxDx, MaxDy);
						Item->DetailShiftX=MaxDx;
						Item->DetailShiftY=MaxDy;
						Item->FinishCalc();

						for(AlgorithmItemPointerList *t=Item->RelatedItems.GetFirst();t!=NULL;t=t->GetNext()){
							GerberFastItemBase	*tItem=dynamic_cast<GerberFastItemBase *>(t->GetItem());
							if(tItem!=NULL && tItem->IsCalcDone()==false){
								if(tItem->GetPage()==DbgPage && tItem->GetID()==DbgGerberID)
									DbgGerber++;						
								//tItem->MoveToFloat(MaxDx, MaxDy);
								tItem->DetailShiftX=MaxDx;
								tItem->DetailShiftY=MaxDy;
								tItem->FinishCalc();
							}
						}
					}
				}
				else{
					Item->FinishCalc();
				}
			}
		}
	}
	delete	[]WList;
	delete	[]MList;
	delete	[]ShiftList;

	ExecuteMatchDetail2();
	ExecuteMatchDetail3(BrighterInPattern);
	//ExecuteMatchDetail4(BrighterInPattern);

	NPListPack<Matching2DList>	Matching2DContainer;
	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==true){
			if(Item->TransDetail.IsEmpty()==false){
				double	x1,y1,x2,y2;
				Item->GetXY(x1,y1,x2,y2);
				if(0<=x1 || Parent->GetDotPerLine()<x1 && 0<=y2 && y1<Parent->GetMaxLines()){
					Matching2DList	*P2d=new Matching2DList();
					P2d->PosXOnTarget=(x1+x2)/2.0;
					P2d->PosYOnTarget=(y1+y2)/2.0;
					P2d->ShiftX=Item->DetailShiftX;
					P2d->ShiftY=Item->DetailShiftY;
					Matching2DContainer.AppendList(P2d);
				}
			}
		}
	}

	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();

		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==true && Item->RelationParent!=NULL){
				if(Item->RelationParent->IsCalcDone()==true && Item->RelationParent->EnabledAutomatch==true){
					if(Item->EnabledAutomatch==true){
						Item->MoveToFloat(Item->RelationParent->DetailShiftX, Item->RelationParent->DetailShiftY);
					}
				}
			}
		}
	}
}

void	MatchAutoLikeManualContainer::ExecuteMatchDetail2(void)
{
	GerberFastBase	*ABase=(GerberFastBase	*)Parent->GetParentBase();
	int		DivLen=ABase->AutoMatchAreaSize;	//3000
	int		XNumb=Parent->GetDotPerLine()/DivLen;
	int		YNumb=Parent->GetMaxLines()  /DivLen;
	if(XNumb==0)
		XNumb=1;
	if(YNumb==0)
		YNumb=1;
	int		XDivLen=Parent->GetDotPerLine()/XNumb;
	int		YDivLen=Parent->GetMaxLines()  /YNumb;
	int		MinIx=99999999;
	int		MaxIx=-99999999;
	int		MinIy=99999999;
	int		MaxIy=-99999999;

	GerberFastItemBasePointerContainer	*ItemDiv[200];
	for(int i=0;i<200;i++){
		ItemDiv[i]=new GerberFastItemBasePointerContainer[200];
	}

	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL){
			if(Item->TransDetail.IsEmpty()==false){
				double	X1,Y1,X2,Y2;
				Item->GetXY(X1,Y1,X2,Y2);
				if(X1<-20 && X2<-20)
					continue;
				if(Y1<-20 && Y2<-20)
					continue;
				if(X1>=(Parent->GetDotPerLine()+20) && X2>=(Parent->GetDotPerLine()+20))
					continue;
				if(Y1>=(Parent->GetMaxLines()+20) && Y2>=(Parent->GetMaxLines()+20))
					continue;
				int	ix=(X1+X2)/2/XDivLen;
				int	iy=(Y1+Y2)/2/YDivLen;
				if(ix<0)
					ix=0;
				if(ix>=XNumb)
					ix=XNumb-1;
				if(iy<0)
					iy=0;
				if(iy>=YNumb)
					iy=YNumb-1;
				ItemDiv[ix][iy].Add(Item);

				MinIx=min(ix,MinIx);
				MinIy=min(iy,MinIy);
				MaxIx=max(ix,MaxIx);
				MaxIy=max(iy,MaxIy);
			}
		}
	}
	for(int ix=MinIx;ix<=MaxIx;ix++){
		for(int iy=MinIy;iy<=MaxIy;iy++){
			if(ItemDiv[ix][iy].GetCount()==0)
				continue;
			if(ItemDiv[ix][iy].GetCount()<10){
				int	LItemCount=0;
				int	tx=-1,ty=-1;
				if(0<=ix-1 && 0<=iy-1){
					int	d=ItemDiv[ix-1][iy-1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix-1;
						ty=iy-1;
					}
				}
				if(0<=ix-1){
					int	d=ItemDiv[ix-1][iy].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix-1;
						ty=iy;
					}
				}
				if(0<=ix-1 && iy+1<=MaxIy){
					int	d=ItemDiv[ix-1][iy+1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix-1;
						ty=iy+1;
					}
				}
				if(0<=iy-1){
					int	d=ItemDiv[ix][iy-1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix;
						ty=iy-1;
					}
				}
				if(iy+1<=MaxIy){
					int	d=ItemDiv[ix][iy+1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix;
						ty=iy+1;
					}
				}
				if(ix+1<MaxIx && 0<=iy-1){
					int	d=ItemDiv[ix+1][iy-1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix+1;
						ty=iy-1;
					}
				}
				if(ix+1<MaxIx){
					int	d=ItemDiv[ix+1][iy].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix+1;
						ty=iy;
					}
				}
				if(ix+1<MaxIx && iy+1<=MaxIy){
					int	d=ItemDiv[ix+1][iy+1].GetCount();
					if(LItemCount>d){
						LItemCount=d;
						tx=ix+1;
						ty=iy+1;
					}
				}
				if(tx>=0 && ty>=0){
					ItemDiv[tx][ty].AddMove(ItemDiv[ix][iy]);
				}
			}
		}
	}
	int	ShiftNumb=0;
	XYClass	*ShiftList=NULL;
	if(MaxIx>=MinIx && MaxIy>=MinIy){
		ShiftNumb=(MaxIx-MinIx+1)*(MaxIy-MinIy+1);
		ShiftList=new XYClass[ShiftNumb];
		int	k=0;
		for(int ix=MinIx;ix<=MaxIx;ix++){
			for(int iy=MinIy;iy<=MaxIy;iy++){
				ShiftList[k].x=ix;
				ShiftList[k].y=iy;
				k++;
			}
		}
	}
	//#pragma omp parallel
	//{
	//	#pragma omp for
		for(int m=0;m<ShiftNumb;m++){

			int	ix=ShiftList[m].x;
			int	iy=ShiftList[m].y;

			if(ItemDiv[ix][iy].GetCount()!=0){
				const	int		MapCount=500;
				const	int		MapAxisNumb=MapCount*2+1;
				int		*MovMapBuff=new int[MapAxisNumb*MapAxisNumb];
				int		*MovMap[MapAxisNumb];
				for(int i=0;i<MapAxisNumb;i++){
					MovMap[i]=&MovMapBuff[i*MapAxisNumb];
				}
				memset(MovMapBuff,0,sizeof(int)*MapAxisNumb*MapAxisNumb);
				int	TotalCount=0;
				int	MinKx=99999999;
				int	MinKy=99999999;
				int	MaxKx=-99999999;
				int	MaxKy=-99999999;
				for(GerberFastItemBasePointerList *c=ItemDiv[ix][iy].GetFirst();c!=NULL;c=c->GetNext()){
					GerberFastItemBase	*Item=c->GetItem();
					if(Item==NULL)
						continue;
					if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
						DbgGerber++;
					if(Item->IsCalcDone()==true){
						int	kx=MapCount+Item->DetailShiftX;
						int	ky=MapCount+Item->DetailShiftY;

						MovMap[kx][ky]++;
						TotalCount++;
						MinKx=min(MinKx,kx);
						MinKy=min(MinKy,ky);
						MaxKx=max(MaxKx,kx);
						MaxKy=max(MaxKy,ky);
					}
				}

				int	MaxDNumb=0;
				int	MaxKxPP=0;
				int	MaxKyPP=0;

				for(int kx=MinKx;kx<=MaxKx;kx++){
					for(int ky=MinKy;ky<=MaxKy;ky++){
						double	DNumb=0;
						for(int x=kx-2;x<=kx+2;x++){
							for(int y=ky-2;y<=ky+2;y++){
								if(0<=x && x<MapAxisNumb && 0<=y && y<MapAxisNumb)
									DNumb+=MovMap[x][y];
							}
						}
						if(DNumb>MaxDNumb){
							MaxDNumb=DNumb;
							MaxKxPP=kx;
							MaxKyPP=ky;
						}
					}
				}
				int	dx=MaxKxPP-MapCount;
				int	dy=MaxKyPP-MapCount;
				if(-SearchAreaMatchDetail<=dx && dx<=SearchAreaMatchDetail && -SearchAreaMatchDetail<=dy && dy<=SearchAreaMatchDetail){
					for(GerberFastItemBasePointerList *c=ItemDiv[ix][iy].GetFirst();c!=NULL;c=c->GetNext()){
						GerberFastItemBase	*Item=c->GetItem();
						if(Item==NULL)
							continue;
						if(Item->IsCalcDone()==false){
							if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
								DbgGerber++;
							Item->DetailShiftX=dx;
							Item->DetailShiftY=dy;
						}
						Item->SetCalcDone(false);
					}
				}
				delete	[]MovMapBuff;
			}
		}
	//}
	/*
	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(a->GetPage()==DbgPage && a->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item->IsCalcDone()==false && Item->TransDetail.IsEmpty()==false){
			double	X1,Y1,X2,Y2;
			Item->GetXY(X1,Y1,X2,Y2);
			if(X1<-20 && X2<-20)
				continue;
			if(Y1<-20 && Y2<-20)
				continue;
			if(X1>=(Parent->GetDotPerLine()+20) && X2>=(Parent->GetDotPerLine()+20))
				continue;
			if(Y1>=(Parent->GetMaxLines()+20) && Y2>=(Parent->GetMaxLines()+20))
				continue;
			int	ix=(X1+X2)/2/XDivLen;
			int	iy=(Y1+Y2)/2/YDivLen;
			if(ix<0)
				ix=0;
			if(ix>=XNumb)
				ix=XNumb-1;
			if(iy<0)
				iy=0;
			if(iy>=YNumb)
				iy=YNumb-1;
			if(ItemDiv[ix][iy].GetCount()>0){
				double	Dx=0;
				double	Dy=0;
				int		Nn=0;
				for(GerberFastItemBasePointerList *c=ItemDiv[ix][iy].GetFirst();c!=NULL;c=c->GetNext()){
					Dx+=c->GetItem()->DetailShiftX;
					Dy+=c->GetItem()->DetailShiftY;
					Nn++;
				}
				Dx+=Nn;
				Dy+=Nn;
				Item->DetailShiftX=Dx;
				Item->DetailShiftY=Dy;
			}
			else{
			}
		}
	}
	*/

	delete	[]ShiftList;

	for(int i=0;i<200;i++){
		delete	[]ItemDiv[i];
	}

}
void	MatchAutoLikeManualContainer::ExecuteMatchDetail4(bool BrighterInPattern)
{
	GerberFastBase	*GBase=(GerberFastBase *)Parent->GetParentBase();
	int	EdgeMergin=GBase->AutoMatchingEdgeOmitDot;

	ImageBuffer *ImageList[100];
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return;

	ImageBuffer	&Ibuff=*ImageList[0];

	int	Isolation=2;
	int	N=(2*SearchAreaMatchDetail+1)*(2*SearchAreaMatchDetail+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dy=-SearchAreaMatchDetail;dy<=SearchAreaMatchDetail;dy+=Isolation){
		for(int dx=-SearchAreaMatchDetail;dx<=SearchAreaMatchDetail;dx+=Isolation){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}

	/*
	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		a->SetCalcDone(false);
	}

	for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(a->GetPage()==DbgPage && a->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==false){
				bool	LeftFix=false;
				bool	RightFix=false;
				bool	TopFix=false;
				bool	BottomFix=false;
				int		LimitSize=300;

				//#pragma omp parallel
				//{
				//	#pragma omp for
					for(int n=0;n<ShiftNumb;n++){
						int	dx=ShiftList[n].x;
						int	dy=ShiftList[n].y;
						double	D=Item->TransDetail.MatchExecute(Item ,dx ,dy
																,EdgeMergin,EdgeMergin,Parent->GetDotPerLine()-EdgeMergin ,Parent->GetMaxLines()-EdgeMergin
																,GBase->UseBrighterInPattern,BrighterInPattern);
						MList[n].Coeff=D*D;
						MList[n].Dx=dx;
						MList[n].Dy=dy;
					}
				//}
				QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);
		

				Item->MoveToFloat(MList[0].Dx+Item->DetailShiftX, MList[0].Dy+Item->DetailShiftY);
				Item->DetailShiftX=MList[0].Dx;
				Item->DetailShiftY=MList[0].Dy;
				Item->FinishCalc();
			}
		}
	}
	*/
	delete	[]MList;
	delete	[]ShiftList;

	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==true){
				double	SCx,SCy;
				Item->GetCenter(SCx,SCy);

				GerberFastItemBase	*ClosedItem=NULL;
				double				MinD=DBL_MAX;
				//for(AlgorithmItemPI	*b=Parent->GetFirstData();b!=NULL;b=b->GetNext()){
				//	GerberFastItemBase	*BItem=dynamic_cast<GerberFastItemBase *>(b);
				for(GerberFastItemBasePointerList *b=Parent->ItemListInside.GetFirst();b!=NULL;b=b->GetNext()){
					GerberFastItemBase	*BItem=b->GetItem();
					if(BItem!=NULL && BItem->IsCalcDone()==true && BItem->TransDetail.IsEmpty()==false){
						double	DCx,DCy;
						BItem->GetCenter(DCx,DCy);
						double	D=hypot(SCx-DCx,SCy-DCy);
						if(D<MinD){
							MinD=D;
							ClosedItem=BItem;
						}
					}
				}
				if(ClosedItem!=NULL){
					Item->DetailShiftX=ClosedItem->DetailShiftX;
					Item->DetailShiftY=ClosedItem->DetailShiftY;
					if(Item->EnabledAutomatch==true){
						Item->MoveToFloat(Item->DetailShiftX, Item->DetailShiftY);
					}
					Item->FinishCalc();
				}
			}
		}
	}
}

void	MatchAutoLikeManualContainer::ExecuteMatchDetail3(bool BrighterInPattern)
{
	GerberFastBase	*GBase=(GerberFastBase *)Parent->GetParentBase();
	int	EdgeMergin=GBase->AutoMatchingEdgeOmitDot;

	ImageBuffer *ImageList[100];
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		Parent->GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		Parent->GetTargetBuffList(ImageList);
	else
		return;

	ImageBuffer	&Ibuff=*ImageList[0];

	int	Isolation=1;
	int	SearchAreaDot=2;
	int	N=(2*SearchAreaDot+1)*(2*SearchAreaDot+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dy=-SearchAreaDot;dy<=SearchAreaDot;dy+=Isolation){
		for(int dx=-SearchAreaDot;dx<=SearchAreaDot;dx+=Isolation){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}

	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==false){
				bool	LeftFix=false;
				bool	RightFix=false;
				bool	TopFix=false;
				bool	BottomFix=false;
				int		LimitSize=300;

				#pragma omp parallel
				{
					#pragma omp for
					for(int n=0;n<ShiftNumb;n++){
						int	dx=ShiftList[n].x;
						int	dy=ShiftList[n].y;
						double	D=Item->TransDetail.MatchExecute(Item ,dx+Item->DetailShiftX ,dy+Item->DetailShiftY
																,EdgeMergin,EdgeMergin,Parent->GetDotPerLine()-EdgeMergin ,Parent->GetMaxLines()-EdgeMergin
																,GBase->UseBrighterInPattern,BrighterInPattern);
						MList[n].Coeff=D*D;
						MList[n].Dx=dx;
						MList[n].Dy=dy;
					}
				}
				QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);
		
				if(MList[0].Coeff>0){
					if(Item->EnabledAutomatch==true){
						Item->MoveToFloat(MList[0].Dx+Item->DetailShiftX, MList[0].Dy+Item->DetailShiftY);
						Item->DetailShiftX+=MList[0].Dx;
						Item->DetailShiftY+=MList[0].Dy;
					}
				}
				Item->FinishCalc();
			}
		}
	}
	//for(AlgorithmItemPI	*a=Parent->GetFirstData();a!=NULL;a=a->GetNext()){
	//	GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
	for(GerberFastItemBasePointerList *h=Parent->ItemListInside.GetFirst();h!=NULL;h=h->GetNext()){
		GerberFastItemBase	*Item=h->GetItem();
		if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
			DbgGerber++;
		if(Item!=NULL && Item->IsCalcDone()==false){
			if(Item->TransDetail.IsEmpty()==true){
				double	SCx,SCy;
				Item->GetCenter(SCx,SCy);

				GerberFastItemBase	*ClosedItem=NULL;
				double				MinD=DBL_MAX;
				//for(AlgorithmItemPI	*b=Parent->GetFirstData();b!=NULL;b=b->GetNext()){
				//	GerberFastItemBase	*BItem=dynamic_cast<GerberFastItemBase *>(b);
				for(GerberFastItemBasePointerList *b=Parent->ItemListInside.GetFirst();b!=NULL;b=b->GetNext()){
					GerberFastItemBase	*BItem=b->GetItem();
					if(BItem!=NULL && BItem->IsCalcDone()==true && BItem->TransDetail.IsEmpty()==false && BItem->EnabledAutomatch==true){
						double	DCx,DCy;
						BItem->GetCenter(DCx,DCy);
						double	D=hypot(SCx-DCx,SCy-DCy);
						if(D<MinD){
							MinD=D;
							ClosedItem=BItem;
						}
					}
				}
				if(ClosedItem!=NULL){
					if(Item->EnabledAutomatch==true){
						Item->DetailShiftX=ClosedItem->DetailShiftX;
						Item->DetailShiftY=ClosedItem->DetailShiftY;
						Item->MoveToFloat(Item->DetailShiftX, Item->DetailShiftY);
					}
					Item->FinishCalc();
				}
			}
		}
	}

	delete	[]MList;
	delete	[]ShiftList;
}

FlexAreaImageListCoeffAndResult	*MatchAutoLikeManualContainer::GetClosed(AlgorithmItemPI *c
																,FlexAreaImagePointerListContainer &PointMap)
{
	double	Cx,Cy;
	c->GetCenter(Cx,Cy);
	double	MinD=DBL_MAX;
	FlexAreaImageList *MinP=NULL;
	for(FlexAreaImagePointerList *a=PointMap.GetFirst();a!=NULL;a=a->GetNext()){
		int	ex,ey;
		a->Get()->GetCenter(ex,ey);
		double	D=hypot(Cx-ex,Cy-ey);
		if(D<MinD){
			MinD=D;
			MinP=a->Get();
		}
	}

	return static_cast<FlexAreaImageListCoeffAndResult *>(MinP);
}
void	ParallelRoughMatch::RemoveArea(int localX,int localY)
{
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;){
		if(a->IsInclude(localX,localY)==true){
			FlexAreaImageList *NextP=a->GetNext();
			TransZone.RemoveList(a);
			delete	a;
			a=NextP;
		}
		else{
			a=a->GetNext();
		}
	}
}
void	ParallelDetalMatch::RemoveArea(int localX,int localY)
{
	for(FlexAreaImageList *a=TransZone.GetFirst();a!=NULL;){
		if(a->IsInclude(localX,localY)==true){
			FlexAreaImageList *NextP=a->GetNext();
			TransZone.RemoveList(a);
			delete	a;
			a=NextP;
		}
		else{
			a=a->GetNext();
		}
	}
}
void	MatchAutoLikeManual::RemoveArea(int localX,int localY)
{
	AreaForRough	.RemoveArea(localX,localY);
	AreaForParallel	.RemoveArea(localX,localY);
	AreaForRotate	.RemoveArea(localX,localY);
	AreaForZoom		.RemoveArea(localX,localY);
}


bool	MatchAutoLikeManualContainer::SaveParam(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,AdpptedLayer)==false)
		return false;
	if(::Save(f,TransDot)==false)
		return false;
	if(::Save(f,RoughMatchAreaWidthRate)==false)
		return false;
	if(::Save(f,RoughMatchAreaHeightRate)==false)
		return false;
	if(::Save(f,SearchAreaRoughMatch)==false)
		return false;
	if(::Save(f,SearchAreaParallelMatch)==false)
		return false;
	if(::Save(f,SearchAreaRotateMatch)==false)
		return false;
	if(::Save(f,SearchAreaZoomMatch)==false)
		return false;
	if(::Save(f,SearchAreaMatchDetail)==false)
		return false;
	if(::Save(f,DataIsolation)==false)
		return false;
	if(::Save(f,NearByPattern)==false)
		return false;
	if(::Save(f,MatchingRateToNeighbor)==false)
		return false;
	return true;
}

bool	MatchAutoLikeManualContainer::LoadParam(QIODevice *f)
{
	int32	Ver=1;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,AdpptedLayer)==false)
		return false;
	if(::Load(f,TransDot)==false)
		return false;
	if(::Load(f,RoughMatchAreaWidthRate)==false)
		return false;
	if(::Load(f,RoughMatchAreaHeightRate)==false)
		return false;
	if(::Load(f,SearchAreaRoughMatch)==false)
		return false;
	if(::Load(f,SearchAreaParallelMatch)==false)
		return false;
	if(::Load(f,SearchAreaRotateMatch)==false)
		return false;
	if(::Load(f,SearchAreaZoomMatch)==false)
		return false;
	if(::Load(f,SearchAreaMatchDetail)==false)
		return false;
	if(::Load(f,DataIsolation)==false)
		return false;
	if(::Load(f,NearByPattern)==false)
		return false;
	if(::Load(f,MatchingRateToNeighbor)==false)
		return false;
	return true;
}


bool	MatchAutoLikeManualContainer::Save(QIODevice *f)
{
	if(SaveParam(f)==false)
		return false;

	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(MatchAutoLikeManual *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}

	return true;
}

bool	MatchAutoLikeManualContainer::Load(QIODevice *f)
{
	int	Ver=Parent->GetLoadedVersion();

	if(LoadParam(f)==false)
		return false;
	if(Ver<=5){
		FlexAreaImageListCoeffAndResultContainer		DummyTransDetail;
		if(DummyTransDetail.Load(f)==false)
			return false;
	}
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		MatchAutoLikeManual	*a=new MatchAutoLikeManual(this);
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}

	return true;
}

MatchAlignmentArea::MatchAlignmentArea(GerberFastInPage	*parent)
	:Parent(parent)
{
	PointType=1;
}

void	MatchAlignmentArea::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,QColor &col)
{
	Area.Draw(0,0,&pnt,col.rgba(),ZoomRate,movx ,movy);
}

bool	MatchAlignmentArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,PointType)==false)
		return false;
	return true;
}
bool	MatchAlignmentArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,PointType)==false)
		return false;
	return true;
}

MatchAlignmentAreaContainer::MatchAlignmentAreaContainer(GerberFastInPage *parent)
	:Parent(parent)
{
}

bool	MatchAlignmentAreaContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(MatchAlignmentArea *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	MatchAlignmentAreaContainer::Load(QIODevice *f)
{
	int32	N;

	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		MatchAlignmentArea *a=new MatchAlignmentArea(Parent);
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}

void	MatchAlignmentAreaContainer::RemoveArea(int localX,int localY)
{
	for(MatchAlignmentArea *a=GetFirst();a!=NULL;){
		MatchAlignmentArea	*NextP=a->GetNext();
		if(a->IsInclude(localX,localY)==true){
			RemoveList(a);
			delete	a;
		}
		a=NextP;
	}
}

double	MakeBrightness(ImageBuffer &IBuff,BYTE **BmpMap,int dx,int dy, int XByte,int YLen)
{
	double	AddD=0;
	int		N=0;
	int		MaxX=IBuff.GetWidth();
	int		MaxY=IBuff.GetHeight();
	for(int y=0;y<YLen;y++){
		int	Y=y+dy;
		if(Y<0 || MaxY<=Y)
			continue;
		BYTE	*a=IBuff.GetY(Y);
		BYTE	*b=BmpMap[y];
		for(int m=0;m<XByte;m++){
			if(b[m]==0)
				continue;
			int		XIndex=(m<<3) + dx;
			if(XIndex<0 || MaxX<=XIndex)
				continue;
			BYTE Mask=0x80;
			for(int i=0;i<8;i++,Mask>>=1){
				if((Mask&b[m])!=0){
					int	x=XIndex + i;
					if(0<=x && x<MaxX){
						AddD += a[x];
						N++;
					}
				}
			}
		}
	}
	if(N==0)
		return 0;
	return AddD/N;
}

void	GerberFastItemBase::MakeTransDetailArea(ConstMapBuffer &MaskMap ,int TransDot)
{
	GerberFastBase	*Base=(GerberFastBase *)Parent->GetParentBase();
	if(GetPage()==DbgPage && GetID()==DbgGerberID)
		DbgGerber++;

	if(IsCalced()==true)
		return;

	GerberFastInPage	*PData=(GerberFastInPage *)GetParentInPage();
	int x1 ,y1 ,x2 ,y2;
	GetXY(x1 ,y1 ,x2 ,y2);
	int	W=x2-x1;
	int	H=y2-y1;

	int	gx1=x1-20-TransDot;
	int	gy1=y1-4 -TransDot;
	int	gx2=x2+20+TransDot;
	int	gy2=y2+4 +TransDot;

	bool	Edged=false;

	int	px1;
	int	py1;
	int	px2;
	int	py2;
	if(gx1<=0){
		px1=0;
		Edged=true;
	}
	else
		px1=gx1;

	if(gy1<=0){
		py1=0;
		Edged=true;
	}
	else
		py1=gy1;

	if(gx2>=GetDotPerLine()){
		px2=GetDotPerLine();
		Edged=true;
	}
	else
		px2=gx2;

	if(gy2>=GetMaxLines()){
		py2=GetMaxLines();
		Edged=true;
	}
	else
		py2=gy2;

	int	XByte=(px2-px1+7)/8;
	int	YLen=py2-py1;
	if(XByte<=0 || YLen<=0)
		return;

	BYTE	**BmpMap	=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear	(BmpMap,0,XByte,YLen);
	bool	Polarity=GetFileLayer()->GetPolarity();
	bool	PosiImage=GetPosiImage();
	GetFileLayer()->SetPolarity(true);
	SetPosiImage(true);
	MakeImage(BmpMap,-gx1 ,-gy1,XByte ,YLen);
	if(GetPage()==DbgPage && GetID()==DbgGerberID){
		//::SavePNGFileBit ("TestGB.png" ,(const BYTE **)BmpMap ,XByte,YLen);
	}
	GetFileLayer()->SetPolarity(Polarity);
	SetPosiImage(PosiImage);

	double	Cx,Cy;
	GetCenter(Cx,Cy);
	RelatedItems.RemoveAll();
	FlexAreaPointerContainer	Container;
	PureFlexAreaListContainer HFPack;
	PickupFlexArea(BmpMap,XByte ,XByte*8,YLen ,HFPack);
	if(GetPosiImage()==true && HFPack.GetFirst()!=NULL){
		PureFlexAreaList	*f=HFPack.GetFirst();
		f->MoveToNoClip(gx1 ,gy1);
		Container.Add(f);

		int	mx1=Clipping(x1,0,GetDotPerLine());
		int	mx2=Clipping(x2,0,GetDotPerLine());
		int	my1=Clipping(y1,0,GetMaxLines());
		int	my2=Clipping(y2,0,GetMaxLines());
		if(mx1!=mx2 && my1!=my2){
			int	px1=mx1/PData->AccessDimXLen;
			int	px2=mx2/PData->AccessDimXLen;
			int	py1=my1/PData->AccessDimYLen;
			int	py2=my2/PData->AccessDimYLen;

			int	CountY=py2-py1;
			//for(int yn=py1;yn<=py2;yn++){
			#pragma omp parallel
			{
				#pragma omp for
				for(int h=0;h<CountY;h++){
					int	yn=h+py1;
					for(int xn=px1;xn<=px2;xn++){
						AlgorithmItemPointerList *k;
						for(k=PData->AccessDim[xn][yn].GetFirst();k!=NULL;k=k->GetNext()){
							if(k->GetItem()==this)
								break;
						}
						if(k==NULL){
							continue;
						}
						do{
							k=k->GetNext();
							if(k==NULL || k->GetItem()==NULL){
								break;
							}
						}while(dynamic_cast<GerberFastItemBase *>(k->GetItem())->GetFileLayerID()!=GetFileLayerID());

						if(k==NULL || k->GetItem()==NULL){
							continue;
						}

						//#pragma omp parallel
						//#pragma omp single private(k)
						while(k!=NULL){
							//#pragma omp task
							//{
								bool	bExist;
								#pragma	omp	critical
								{
									bExist=RelatedItems.IsExist(k->GetItem());
								}
								if(bExist==false){
									GerberFastItemBase	*tItem=dynamic_cast<GerberFastItemBase *>(k->GetItem());
									if(tItem!=NULL){
										if(tItem->GetFileLayerID()==GetFileLayerID()){
											double	tCx,tCy;
											tItem->GetCenter(tCx,tCy);
											double	Len=hypot(Cx-tCx,Cy-tCy);
											if(Len<Base->MaxBindedAreaLength){
												int	qx1,qy1,qx2,qy2;
												tItem->GetXY(qx1,qy1,qx2,qy2);
												int	tW=qx2-qx1;
												int	tH=qx2-qx1;
												if((tW<Base->MaxBindedAreaLength || tH<Base->MaxBindedAreaLength)
												&& W<tW*2 && tW<W*2 && H<tH*2 && tH<H*2
												&& tItem->IsCrossed(x1,y1,x2,y2)==true){
													if(tItem->IsCrossed(f)==true){
														#pragma	omp	critical
														RelatedItems.Add(tItem);
														tItem->RelationParent=this;
													}
												}
											}
										}
									}
								}
							do{
								k=k->GetNext();
								if(k==NULL || k->GetItem()==NULL){
									break;
								}
							}while(dynamic_cast<GerberFastItemBase *>(k->GetItem())->GetFileLayerID()!=GetFileLayerID());
						}
						//}
					}
				}
			}
		}
	}
	/*
	if(RelatedItems.GetCount()<2){
		for(AlgorithmItemPointerList *a=RelatedItems.GetFirst();a!=NULL;a=a->GetNext()){
			GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a->GetItem());
			Item->MakeImage(BmpMap,-gx1 ,-gy1,XByte ,YLen);
			Item->SetCalcDone(true);

			if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
				DbgGerber++;
		}
	}
	else{
		int	ThreadNumb=min((int)RelatedItems.GetCount(),8);
		BYTE	**BmpMapTmp[8];
		BmpMapTmp[0]=BmpMap;
		for(int i=1;i<ThreadNumb;i++){
			BmpMapTmp[i]=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear	(BmpMapTmp[i],0,XByte,YLen);
		}
		AlgorithmItemPointerList **RDim=new AlgorithmItemPointerList *[RelatedItems.GetCount()];
		int	N=0;
		for(AlgorithmItemPointerList *a=RelatedItems.GetFirst();a!=NULL;a=a->GetNext(),N++){
			RDim[N]=a;
		}
		#pragma omp parallel num_threads(ThreadNumb)
		{
			#pragma omp for
			for(int i=0;i<N;i++){
				int	t=omp_get_thread_num();
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(RDim[i]->GetItem());
				Item->MakeImage(BmpMapTmp[t],-gx1 ,-gy1,XByte ,YLen);
				Item->SetCalcDone(true);
			}
		}
		for(int i=1;i<ThreadNumb;i++){
			MatrixBuffOr	(BmpMap,(const BYTE **)BmpMapTmp[i],XByte, YLen);
		}
		for(int i=1;i<ThreadNumb;i++){
			DeleteMatrixBuff(BmpMapTmp[i],YLen);
		}
	}

	BYTE	**BmpOut	=MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpMap	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpIn		=MakeMatrixBuff(XByte,YLen);

	MatrixBuffBitAnd	(BmpMap ,(BYTE **)MaskMap.GetBitMap() ,XByte*8 ,YLen ,-gx1 ,-gy1);

	MatrixBuffCopy	(BmpOut,XByte,YLen
					,(const BYTE **)BmpMap ,XByte,YLen);
	FatAreaN(BmpOut ,TmpMap	,XByte, YLen,TransDot);
	//MatrixBuffXor	(BmpOut,(const BYTE **)BmpMap ,XByte, YLen);

	MatrixBuffCopy	(BmpIn ,XByte,YLen
					,(const BYTE **)BmpMap ,XByte,YLen);
	ThinAreaN(BmpIn ,TmpMap	,XByte, YLen,TransDot);

	MatrixBuffXor	(BmpOut,(const BYTE **)BmpIn,XByte, YLen);		//Outline bit image

	TransDetail.RemoveAll();

	DeleteMatrixBuff(TmpMap,YLen);
	DeleteMatrixBuff(BmpIn ,YLen);
	double	AutoMatchMinWidthForPartial=Base->AutoMatchMinWidthForPartial;
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BmpOut ,XByte ,XByte*8,YLen ,FPack);

	int	h=0;
	for(PureFlexAreaList *a=FPack.GetFirst();a!=NULL;a=a->GetNext(),h++){
		FlexArea	*b=new FlexArea();
		FlexArea	*c=NULL;
		if(Edged==false && a->GetWidth()>a->GetHeight()*4 && a->GetHeight()<=AutoMatchMinWidthForPartial){
			c=new FlexArea();
			*b=*a;
			*c=*a;
			b->ClipArea(b->GetMinX()-1					 ,b->GetMinY()-1,b->GetMinX()+b->GetHeight()*1.5,b->GetMaxY()+1);
			c->ClipArea(c->GetMaxX()+1-c->GetHeight()*1.5,c->GetMinY()-1,c->GetMaxX()+1					,c->GetMaxY()+1);
		}
		else if(Edged==false && a->GetWidth()*4<a->GetHeight() && a->GetWidth()<=AutoMatchMinWidthForPartial){
			c=new FlexArea();
			*b=*a;
			*c=*a;
			b->ClipArea(b->GetMinX()-1,b->GetMinY()-1				 ,b->GetMaxX()+1,b->GetMinY()+b->GetWidth()*1.5);
			c->ClipArea(c->GetMinX()-1,c->GetMaxY()-c->GetWidth()*1.5,c->GetMaxX()+1,c->GetMaxY()+1);
		}
		else{
			*b=*a;
		}

		OutlineArea	*po=TransDetail[h];
		if(po!=NULL)
			*po=*b;
		else{
			po=new OutlineArea();
			*po=*b;
		}
	}

	DeleteMatrixBuff(BmpOut,YLen);
	DeleteMatrixBuff(BmpMap,YLen);
	*/
}

void	GerberFastItemBase::MatchClosed(ImageBuffer &IBuff ,int SearchDotX1 ,int SearchDotY1 ,int SearchDotX2 ,int SearchDotY2 ,int &Dx ,int &Dy)
{
	int x1 ,y1 ,x2 ,y2;
	GetXY(x1 ,y1 ,x2 ,y2);

	int	gx1=x1-4;
	int	gy1=y1-4;
	int	gx2=x2+4;
	int	gy2=y2+4;
	int	XByte=(gx2-gx1+7)/8;
	int	YLen=gy2-gy1;

	BYTE	**BmpMap	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpOut	=MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpMap	=MakeMatrixBuff(XByte,YLen);
	BYTE	**BmpIn		=MakeMatrixBuff(XByte,YLen);

	MatrixBuffClear	(BmpMap,0,XByte,YLen);
	MakeImage(BmpMap,-gx1 ,-gy1,XByte ,YLen);

	MatrixBuffCopy	(BmpOut,XByte,YLen
					,(const BYTE **)BmpMap ,XByte,YLen);
	FatArea(BmpOut ,TmpMap	,XByte, YLen);
	FatArea(BmpOut ,TmpMap	,XByte, YLen);

	MatrixBuffXor	(BmpOut,(const BYTE **)BmpMap ,XByte, YLen);

	MatrixBuffCopy	(BmpIn ,XByte,YLen
					,(const BYTE **)BmpMap ,XByte,YLen);
	ThinArea(BmpIn ,TmpMap	,XByte, YLen);
	ThinArea(BmpIn ,TmpMap	,XByte, YLen);
	MatrixBuffXor	(BmpMap,(const BYTE **)BmpIn,XByte, YLen);

	double	MaxD=0;
	int		MaxDx=0,MaxDy=0;
	for(int dy=-SearchDotY1;dy<=SearchDotY2;dy++){
		for(int dx=-SearchDotX1;dx<=SearchDotX2;dx++){
			double	AvrOut=MakeBrightness(IBuff,BmpOut,gx1+dx,gy1+dy,XByte,YLen);
			double	AvrIn =MakeBrightness(IBuff,BmpMap,gx1+dx,gy1+dy,XByte,YLen);
			double	d=fabs(AvrOut-AvrIn);
			if(d>MaxD){
				MaxD=d;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	DeleteMatrixBuff(BmpMap,YLen);
	DeleteMatrixBuff(BmpOut,YLen);
	DeleteMatrixBuff(TmpMap,YLen);
	DeleteMatrixBuff(BmpIn ,YLen);

	Dx=MaxDx;
	Dy=MaxDy;
}

void	GerberFastInPage::MakeTransArea(bool UsageLayer ,int UsageLayerID)
{
	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	int	Numb=GetItemCount();
	GerberFastItemBase	**BaseDim=new GerberFastItemBase*[Numb];
	int					BaseDimCount=0;
	int	N=0;

	if(UsageLayer==true && UsageLayerID>=0){
		GerberFileLayer	*F=FindFileLayer(UsageLayerID);
		if(F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						BaseDim[BaseDimCount]=Item;
						BaseDimCount++;
					}
				}
			}
		}
	}
	if(UsageLayerID>=0){
		int	CompositeID=UsageLayerID;
		GerberCompositeLayer	*CL=GetCompositeLayer(CompositeID);
		if(CL!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						BaseDim[BaseDimCount]=Item;
						BaseDimCount++;
					}
				}
			}
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<BaseDimCount;i++){
			if(BaseDim[i]->GetPage()==DbgPage && BaseDim[i]->GetID()==DbgGerberID)
				DbgGerber++;
			BaseDim[i]->MakeOutlineWithHairlineAll(ABase->HairlineIsolation ,ABase->HairlineLength,0,0);
			BaseDim[i]->RestructHairline();
		}
	}

	delete	[]BaseDim;
}


void	GerberFastInPage::InitialTransArea(bool UsageLayer ,int UsageLayerID)
{
	int	XLen=GetDotPerLine();
	int	XByte=(XLen+7)/8;
	int	YLen=GetMaxLines();
	BYTE	**TmpImage =MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpImage2=MakeMatrixBuff(XByte ,YLen);

	GerberFastBase	*ABase=(GerberFastBase *)GetParentBase();
	int	Numb=GetItemCount();
	GerberFastItemBase	**BaseDim=new GerberFastItemBase*[Numb];
	int					BaseDimCount=0;
	int	N=0;
	MatrixBuffClear	(TmpImage ,0,XByte ,YLen);
	if(UsageLayer==true && UsageLayerID>=0){
		GerberFileLayer	*F=FindFileLayer(UsageLayerID);
		if(F!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
				if(Item!=NULL){
					if(Item->GetFileLayerID()==F->GetFileLayerID()){
						Item->MakeImage(TmpImage,0,0,XByte,YLen);
						BaseDim[BaseDimCount]=Item;
						BaseDimCount++;
					}
				}
			}
		}
	}
	else if(UsageLayerID>=0){
		int	CompositeID=UsageLayerID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a);
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID){
						Item->MakeImage(TmpImage,0,0,XByte,YLen);
						BaseDim[BaseDimCount]=Item;
						BaseDimCount++;
					}
				}
			}
		}
	}

	ThinArea(TmpImage,TmpImage2,XByte,YLen);
	FatArea (TmpImage,TmpImage2,XByte,YLen);
	FatArea (TmpImage,TmpImage2,XByte,YLen);
	ThinArea(TmpImage,TmpImage2,XByte,YLen);

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<BaseDimCount;i++){
			if(BaseDim[i]->GetPage()==DbgPage && BaseDim[i]->GetID()==DbgGerberID)
				DbgGerber++;
			BaseDim[i]->TransDetail.EditInitialAfterEdit(BaseDim[i],AutoLikeManualData.SearchAreaMatchDetail
														,TmpImage,XByte,YLen
														,ABase->UseMasterImage);
		}
	}

	delete	[]BaseDim;
	DeleteMatrixBuff(TmpImage ,YLen);
	DeleteMatrixBuff(TmpImage2,YLen);
}

void	GerberFastInPage::MakeAccessDim(void)
{
	ClearAccessDim();
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item!=NULL){
			AddAccessDim(Item);
		}
	}
}

void	GerberFastInPage::MakeRelatedInOtherLayerItems(bool UsageLayer ,int UsageLayerID)
{
	int	N=0;
	IntList	FileLayerIDContainer;
	if(UsageLayer==true && UsageLayerID>=0){
		GerberFileLayer	*F=FindFileLayer(UsageLayerID);
		if(F!=NULL){
			FileLayerIDContainer.Add(F->GetFileLayerID());
		}
	}

	AlgorithmItemPI	*a;
	#pragma omp parallel
	#pragma omp single private(a)
	for(a=GetFirstData();a!=NULL;a=a->GetNext()){
		#pragma omp task
		{
			GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
			if(Item->GetPage()==DbgPage && Item->GetID()==DbgGerberID)
				DbgGerber++;
			if(Item!=NULL){
				if(FileLayerIDContainer.IsInclude(Item->GetFileLayerID())==false){
					Item->SetDetailMatchRelation(FileLayerIDContainer);
				}
			}
		}
	}
}
void	GerberFastInPage::MakeABox(void)
{
	//ガーバーの全エリア範囲を取得
	NPListPack<GerberFastItemPointer>	PointerList[10][10];
	AutoInterpolation.RemoveAll();

	int		X1 ,Y1 ,X2 ,Y2;
	if(GetOccupiedItemXY(X1 ,Y1 ,X2 ,Y2)==true){
		int	MinX=max(0,X1-100);
		int	MinY=max(0,Y1-100);
		int	MaxX=min(GetDotPerLine(),X2+100);
		int	MaxY=min(GetMaxLines(),Y2+100);

		if(MinX<MaxX && MinY<MaxY
		&& CheckOverlapRectRect(MinX, MinY, MaxX, MaxY
							,0, 0, GetDotPerLine(), GetMaxLines())==true){

			//小矩形に探索ビット領域が含まれているか、その小矩形個数を数える
			ABoxXNum=10;
			ABoxYNum=10;
			int	XDot=(MaxX-MinX)/ABoxXNum;
			int	YDot=(MaxY-MinY)/ABoxYNum;
			if(YDot>0 && XDot/YDot>=2){
				int	N=XDot/YDot;
				ABoxYNum=(ABoxYNum+N-1)/N;
				if(ABoxYNum>10)
					ABoxYNum=10;
				YDot=(MaxY-MinY)/ABoxYNum;
			}
			else if(XDot>0 && YDot/XDot>=2){
				int	N=YDot/XDot;
				ABoxXNum=(ABoxXNum+N-1)/N;
				if(ABoxXNum>10)
					ABoxXNum=10;
				XDot=(MaxX-MinX)/ABoxXNum;
			}
			else if(XDot!=0 && YDot==0){
				int	N=(MaxX-MinX)/(MaxY-MinY);
				ABoxYNum=(ABoxYNum+N-1)/N;
				if(ABoxYNum>10)
					ABoxYNum=10;
				YDot=(MaxY-MinY)/ABoxYNum;
			}
			else if(XDot==0 && YDot!=0){
				int	N=(MaxY-MinY)/(MaxX-MinX);
				ABoxXNum=(ABoxXNum+N-1)/N;
				if(ABoxXNum>10)
					ABoxXNum=10;
				XDot=(MaxX-MinX)/ABoxXNum;
			}
			
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				GerberFastItemBase	*Item=static_cast<GerberFastItemBase *>(a);
				if(Item->IsCalcDone()==true){
					int	ix=(Item->CxBefore-MinX)/XDot;
					int	iy=(Item->CyBefore-MinY)/YDot;
					if(0<=ix && ix<ABoxXNum && 0<=iy && iy<ABoxYNum ){
						PointerList[ix][iy].AppendList(new GerberFastItemPointer(Item));
					}
				}
			}
			for(int iy=0;iy<ABoxYNum;iy++){
				for(int ix=0;ix<ABoxXNum;ix++){
					ABox[iy][ix].MatchingZones.RemoveAll();
					ABox[iy][ix].SetParent(this);
					ABox[iy][ix].X1=MinX+ix*XDot;
					ABox[iy][ix].Y1=MinY+iy*YDot;
					ABox[iy][ix].X2=ABox[iy][ix].X1+XDot;
					ABox[iy][ix].Y2=ABox[iy][ix].Y1+YDot;
					ABox[iy][ix].XAddr	=ix;
					ABox[iy][ix].YAddr	=iy;

					SetABox(ix,iy,ABox[iy][ix],PointerList[ix][iy]);
				}
			}
		}
	}
	AutoInterpolation.Build();
}

void	GerberFastInPage::SetABox(int ix,int iy,AutomatchingBox &AB,NPListPack<GerberFastItemPointer> &PointerList)
{
	AB.Clear();
	if(PointerList.GetCount()<4){
		for(GerberFastItemPointer	*g=PointerList.GetFirst();g!=NULL;g=g->GetNext()){
			MultiInterpolationPole	*a=new MultiInterpolationPole();
			a->X	=g->GetPoint()->CxBefore;
			a->Y	=g->GetPoint()->CyBefore;
			a->Xn	=ix;
			a->Yn	=iy;
			double	Cx,Cy;
			g->GetPoint()->GetCenter(Cx,Cy);
			a->dX	=Cx-g->GetPoint()->CxBefore;
			a->dY	=Cy-g->GetPoint()->CyBefore;
			AutoInterpolation.AppendList(a);
		}
	}
	else{
		double	PCx1=AB.X1+  AB.GetWidth() /4;
		double	PCy1=AB.Y1+  AB.GetHeight()/4;
		double	PCx2=AB.X1+3*AB.GetWidth() /4;
		double	PCy2=AB.Y1+  AB.GetHeight()/4;
		double	PCx3=AB.X1+  AB.GetWidth() /4;
		double	PCy3=AB.Y1+3*AB.GetHeight()/4;
		double	PCx4=AB.X1+3*AB.GetWidth() /4;
		double	PCy4=AB.Y1+3*AB.GetHeight()/4;

		GerberFastItemPointer	*P1=NULL;
		GerberFastItemPointer	*P2=NULL;
		GerberFastItemPointer	*P3=NULL;
		GerberFastItemPointer	*P4=NULL;
		double	PLen1=DBL_MAX;
		double	PLen2=DBL_MAX;
		double	PLen3=DBL_MAX;
		double	PLen4=DBL_MAX;

		for(GerberFastItemPointer	*g=PointerList.GetFirst();g!=NULL;g=g->GetNext()){
			double	Cx=g->GetPoint()->CxBefore;
			double	Cy=g->GetPoint()->CyBefore;
			double	D1=hypot(Cx-PCx1,Cy-PCy1);
			double	D2=hypot(Cx-PCx2,Cy-PCy2);
			double	D3=hypot(Cx-PCx3,Cy-PCy3);
			double	D4=hypot(Cx-PCx4,Cy-PCy4);
			if(D1<=D2 && D1<=D3 && D1<=D4){
				if(D1<PLen1){
					PLen1=D1;
					P1=g;
				}
			}
			else if(D2<=D1 && D2<=D3 && D2<=D4){
				if(D2<PLen2){
					PLen2=D2;
					P2=g;
				}
			}
			else if(D3<=D1 && D3<=D2 && D3<=D4){
				if(D3<PLen3){
					PLen3=D3;
					P3=g;
				}
			}
			else if(D4<=D1 && D4<=D2 && D4<=D3){
				if(D4<PLen4){
					PLen4=D4;
					P4=g;
				}
			}
		}
		if(P1!=NULL){
			MultiInterpolationPole	*a=new MultiInterpolationPole();
			a->X	=P1->GetPoint()->CxBefore;
			a->Y	=P1->GetPoint()->CyBefore;
			a->Xn	=ix;
			a->Yn	=iy;
			double	Cx,Cy;
			P1->GetPoint()->GetCenter(Cx,Cy);
			a->dX	=Cx-P1->GetPoint()->CxBefore;
			a->dY	=Cy-P1->GetPoint()->CyBefore;
			AutoInterpolation.AppendList(a);
		}
		if(P2!=NULL){
			MultiInterpolationPole	*a=new MultiInterpolationPole();
			a->X	=P2->GetPoint()->CxBefore;
			a->Y	=P2->GetPoint()->CyBefore;
			a->Xn	=ix;
			a->Yn	=iy;
			double	Cx,Cy;
			P2->GetPoint()->GetCenter(Cx,Cy);
			a->dX	=Cx-P2->GetPoint()->CxBefore;
			a->dY	=Cy-P2->GetPoint()->CyBefore;
			AutoInterpolation.AppendList(a);
		}
		if(P3!=NULL){
			MultiInterpolationPole	*a=new MultiInterpolationPole();
			a->X	=P3->GetPoint()->CxBefore;
			a->Y	=P3->GetPoint()->CyBefore;
			a->Xn	=ix;
			a->Yn	=iy;
			double	Cx,Cy;
			P3->GetPoint()->GetCenter(Cx,Cy);
			a->dX	=Cx-P3->GetPoint()->CxBefore;
			a->dY	=Cy-P3->GetPoint()->CyBefore;
			AutoInterpolation.AppendList(a);
		}
		if(P4!=NULL){
			MultiInterpolationPole	*a=new MultiInterpolationPole();
			a->X	=P4->GetPoint()->CxBefore;
			a->Y	=P4->GetPoint()->CyBefore;
			a->Xn	=ix;
			a->Yn	=iy;
			double	Cx,Cy;
			P4->GetPoint()->GetCenter(Cx,Cy);
			a->dX	=Cx-P4->GetPoint()->CxBefore;
			a->dY	=Cy-P4->GetPoint()->CyBefore;
			AutoInterpolation.AppendList(a);
		}
	}
}


double	GetDistanceRectRect(double px1 ,double py1 ,double px2, double py2
						   ,double qx1 ,double qy1 ,double qx2 ,double qy2)
{
	double	d1=GetLengthLine2Point(px1,py1,px2,py2 ,qx1,qy1);
	double	d2=GetLengthLine2Point(px1,py1,px2,py2 ,qx1,qy2);
	double	d3=GetLengthLine2Point(px1,py1,px2,py2 ,qx2,qy1);
	double	d4=GetLengthLine2Point(px1,py1,px2,py2 ,qx2,qy2);
	double	d5=GetLengthLine2Point(qx1,qy1,qx2,qy2 ,px1,py1);
	double	d6=GetLengthLine2Point(qx1,qy1,qx2,qy2 ,px1,py2);
	double	d7=GetLengthLine2Point(qx1,qy1,qx2,qy2 ,px2,py1);
	double	d8=GetLengthLine2Point(qx1,qy1,qx2,qy2 ,px2,py2);
	
	return min(min(min(d1,d2),min(d3,d4)) ,min(min(d5,d6),min(d7,d8)));
}

class	ClusterMatchDetailClass : public NPList<ClusterMatchDetailClass>
{
public:
	NPListPack<GerberFastItemPointer>	ItemPointers;
	double	X1,Y1,X2,Y2;
	int		ShiftX,ShiftY;

	void	SearchMatch(ImageBuffer	&Ibuff ,int SearchAreaMatchDetail
						,int DotPerLine ,int MaxLines ,int EdgeMergin
						,bool GBaseUseBrighterInPattern,bool BrighterInPattern);
	bool	IsInclude(GerberFastItemBase *b);
};

void	GerberFastInPage::ExecuteClusterMatchDetail(bool UsageLayer ,int UsageLayerID
													,bool BrighterInPattern)
{
	NPListPack<GerberFastItemPointer>	MatchingItemList;
	NPListPack<GerberFastItemPointer>	OtherItemList;
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetID()==DbgGerberID1)
			DbgGerber++;
	}
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		GerberFastItemBase	*Item=dynamic_cast<GerberFastItemBase *>(a);
		if(Item->EnabledAutomatch==true){
			OtherItemList.AppendList(new GerberFastItemPointer(Item));
		}
	}
	
	GerberFastBase	*GBase=(GerberFastBase *)GetParentBase();
	if(UsageLayer==true && UsageLayerID>=0){
		GerberFileLayer	*F=FindFileLayer(UsageLayerID);
		if(F!=NULL){
			for(GerberFastItemPointer	*a=OtherItemList.GetFirst();a!=NULL;){
				GerberFastItemPointer	*NextA=a->GetNext();
				GerberFastItemBase	*Item=a->GetPoint();
				if(Item->GetID()==DbgGerberID1)
					DbgGerber++;
				if(Item->GetFileLayerID()==F->GetFileLayerID() && Item->TransDetail.GetCount()!=0){
					OtherItemList.RemoveList(a);
					MatchingItemList.AppendList(a);
				}
				a=NextA;
			}
		}
	}
	else if(UsageLayerID>=0){
		int	CompositeID=UsageLayerID;
		GerberCompositeLayer	*CL=SearchCompositeLayer(CompositeID);
		if(CL!=NULL){
			GerberCompositeDefLayer	*CDef=GBase->CompositeDef.Search(CompositeID);
			for(GerberFastItemPointer	*a=OtherItemList.GetFirst();a!=NULL;){
				GerberFastItemPointer	*NextA=a->GetNext();
				GerberFastItemComposite	*Item=dynamic_cast<GerberFastItemComposite *>(a->GetPoint());
				if(Item!=NULL){
					if(Item->GetCompositeID()==CompositeID && Item->TransDetail.GetCount()!=0){
						OtherItemList.RemoveList(a);
						MatchingItemList.AppendList(a);
					}
				}
				a=NextA;
			}
		}
	}

	NPListPack<ClusterMatchDetailClass>	BigSizeMatchCluster;
	NPListPack<ClusterMatchDetailClass>	NormalMatchCluster;

	//Big size item separates for independent automating
	int	BigSizeForEachItem=GBase->AutoMatchAreaSize;
	for(GerberFastItemPointer *a=MatchingItemList.GetFirst();a!=NULL;){
		if(a->GetPoint()->GetID()==DbgGerberID1)
			DbgGerber++;
		GerberFastItemPointer	*NextA=a->GetNext();
		double	x1,y1,x2,y2;
		a->GetPoint()->GetXY(x1,y1,x2,y2);
		if((x2-x1)>BigSizeForEachItem || (y2-y1)>BigSizeForEachItem){
			MatchingItemList.RemoveList(a);
			ClusterMatchDetailClass	*K=new ClusterMatchDetailClass();
			BigSizeMatchCluster.AppendList(K);
			K->ItemPointers.AppendList(a);
		}
		a=NextA;
	}

	GerberFastItemPointer *a;
	while((a=MatchingItemList.GetFirst())!=NULL){
		if(a->GetPoint()->GetID()==DbgGerberID1)
			DbgGerber++;
		MatchingItemList.RemoveList(a);
		double	x1,y1,x2,y2;
		a->GetPoint()->GetXY(x1,y1,x2,y2);
		double	cx=(x1+x2)/2;
		double	cy=(y1+y2)/2;

		double	MinD=99999999.0;
		ClusterMatchDetailClass *MinK=NULL;
		for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
			double	Ex=(k->X1+k->X2)/2;
			double	Ey=(k->Y1+k->Y2)/2;
			double	D=hypot(Ex-cx,Ey-cy);
			if(MinD>D){
				MinD=D;
				MinK=k;
			}
		}
		if(MinK!=NULL){
			double	mx1=min(MinK->X1,x1);
			double	my1=min(MinK->Y1,y1);
			double	mx2=max(MinK->X2,x2);
			double	my2=max(MinK->Y2,y2);
			if((mx2-mx1)<GBase->AutoMatchAreaSize && (my2-my1)<GBase->AutoMatchAreaSize){
				MinK->X1=mx1;
				MinK->Y1=my1;
				MinK->X2=mx2;
				MinK->Y2=my2;
				MinK->ItemPointers.AppendList(a);
			}
			else{
				ClusterMatchDetailClass	*K=new ClusterMatchDetailClass();
				NormalMatchCluster.AppendList(K);
				K->ItemPointers.AppendList(a);
				K->X1=x1;
				K->Y1=y1;
				K->X2=x2;
				K->Y2=y2;
			}
		}
		else{
			ClusterMatchDetailClass	*K=new ClusterMatchDetailClass();
			NormalMatchCluster.AppendList(K);
			K->ItemPointers.AppendList(a);
			K->X1=x1;
			K->Y1=y1;
			K->X2=x2;
			K->Y2=y2;
		}
	}
	for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;){
		for(GerberFastItemPointer	*a=k->ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetPoint()->GetID()==DbgGerberID1)
				DbgGerber++;
		}
		ClusterMatchDetailClass	*NextK=k->GetNext();
		if(k->ItemPointers.GetCount()<=2){
			for(ClusterMatchDetailClass *p=NormalMatchCluster.GetFirst();p!=NULL;p=p->GetNext()){
				if(k==p)
					continue;
				if(GetDistanceRectRect(k->X1,k->Y1,k->X2,k->Y2
									 , p->X1,p->Y1,p->X2,p->Y2)<GBase->AutoMatchAreaSize){
					NormalMatchCluster.RemoveList(k);
					p->X1=min(p->X1,k->X1);
					p->Y1=min(p->Y1,k->Y1);
					p->X2=max(p->X2,k->X2);
					p->Y2=max(p->Y2,k->Y2);

					p->ItemPointers.AddMove(k->ItemPointers);
					delete	k;
					break;
				}
			}
		}
		k=NextK;
	}

	ImageBuffer *ImageList[100];
	if(Parent->GetLayersBase()->GetParamGlobal()->AllocateMasterBuff==true)
		GetMasterBuffList(ImageList);
	else if(Parent->GetLayersBase()->GetParamGlobal()->AllocateTargetBuff==true)
		GetTargetBuffList(ImageList);
	else
		return;

	int	EdgeMergin=GBase->AutoMatchingEdgeOmitDot;
	ImageBuffer	&Ibuff=*ImageList[0];
	for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
		k->SearchMatch(Ibuff,AutoLikeManualData.SearchAreaMatchDetail
											,GetDotPerLine() ,GetMaxLines() ,EdgeMergin
											,GBase->UseBrighterInPattern,BrighterInPattern);
	}
	for(ClusterMatchDetailClass *k=BigSizeMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
		k->SearchMatch(Ibuff,AutoLikeManualData.SearchAreaMatchDetail
											,GetDotPerLine() ,GetMaxLines() ,EdgeMergin
											,GBase->UseBrighterInPattern,BrighterInPattern);
	}

	for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
		for(GerberFastItemPointer	*a=k->ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetPoint()->GetID()==DbgGerberID1)
				DbgGerber++;
			a->GetPoint()->DetailShiftX=k->ShiftX;
			a->GetPoint()->DetailShiftY=k->ShiftY;
			int	OffsetX ,OffsetY;
			a->GetPoint()->FuncEachSearchDot(Ibuff,GBase->EachSearchDot
										,k->ShiftX,k->ShiftY ,OffsetX ,OffsetY
										,GetDotPerLine() ,GetMaxLines() ,EdgeMergin
										,GBase->UseBrighterInPattern,BrighterInPattern);
			a->GetPoint()->MoveToFloat(k->ShiftX+OffsetX,k->ShiftY+OffsetY);
		}
	}
	for(GerberFastItemPointer	*a=OtherItemList.GetFirst();a!=NULL;a=a->GetNext()){
		for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
			if(k->IsInclude(a->GetPoint())==true){
				if(a->GetPoint()->GetID()==DbgGerberID1)
					DbgGerber++;
				a->GetPoint()->DetailShiftX=k->ShiftX;
				a->GetPoint()->DetailShiftY=k->ShiftY;
				a->GetPoint()->MoveToFloat(k->ShiftX,k->ShiftY);
				a->GetPoint()->SetCalcDone(true);
				break;
			}
		}
		for(ClusterMatchDetailClass *k=BigSizeMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
			if(k->IsInclude(a->GetPoint())==true){
				if(a->GetPoint()->GetID()==DbgGerberID1)
					DbgGerber++;
				a->GetPoint()->DetailShiftX=k->ShiftX;
				a->GetPoint()->DetailShiftY=k->ShiftY;
				a->GetPoint()->MoveToFloat(k->ShiftX,k->ShiftY);
				a->GetPoint()->SetCalcDone(true);
				break;
			}
		}
		if(a->GetPoint()->IsCalcDone()==false){
			double	x1,y1,x2,y2;
			a->GetPoint()->GetXY(x1,y1,x2,y2);
			double	MinD=99999999;
			ClusterMatchDetailClass *MinK=NULL;
			for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
				double	D=GetDistanceRectRect(x1 ,y1 ,x2, y2
											,k->X1,k->Y1,k->X2,k->Y2);
				if(D<MinD){
					MinK=k;
					MinD=D;
				}
			}
			for(ClusterMatchDetailClass *k=BigSizeMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
				double	D=GetDistanceRectRect(x1 ,y1 ,x2, y2
											,k->X1,k->Y1,k->X2,k->Y2);
				if(D<MinD){
					MinK=k;
					MinD=D;
				}
			}
			if(MinK!=NULL){
				a->GetPoint()->DetailShiftX=MinK->ShiftX;
				a->GetPoint()->DetailShiftY=MinK->ShiftY;
				if(a->GetPoint()->GetID()==DbgGerberID1)
					DbgGerber++;
				a->GetPoint()->MoveToFloat(MinK->ShiftX,MinK->ShiftY);
				a->GetPoint()->SetCalcDone(true);
			}
		}
	}
	
	double	AvrShiftX=0;
	double	AvrShiftY=0;
	int	N=0;
	for(ClusterMatchDetailClass *k=NormalMatchCluster.GetFirst();k!=NULL;k=k->GetNext()){
		AvrShiftX+=k->ShiftX;
		AvrShiftY+=k->ShiftY;
		N++;
	}
	if(N!=NULL){
		AvrShiftX/=N;
		AvrShiftY/=N;
		for(GerberFastItemPointer	*a=OtherItemList.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetPoint()->IsCalcDone()==false){
				if(a->GetPoint()->GetID()==DbgGerberID1)
					DbgGerber++;
				a->GetPoint()->DetailShiftX=AvrShiftX;
				a->GetPoint()->DetailShiftY=AvrShiftY;
				a->GetPoint()->MoveToFloat(AvrShiftX,AvrShiftY);
				a->GetPoint()->SetCalcDone(true);
			}
		}
	}
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		if(a->GetID()==DbgGerberID1)
			DbgGerber++;
	}
}


void	ClusterMatchDetailClass::SearchMatch(ImageBuffer &Ibuff ,int SearchAreaMatchDetail
											,int DotPerLine ,int MaxLines ,int EdgeMergin
											,bool GBaseUseBrighterInPattern,bool BrighterInPattern)
{
	int	Isolation=2;
	int	SearchAreaDot=SearchAreaMatchDetail;
	int	N=(2*SearchAreaDot+1)*(2*SearchAreaDot+1);
	struct	MatchList	*MList=new struct	MatchList[N];
	struct	MatchList	*WList=new struct	MatchList[N];
	XYClass	*ShiftList=new XYClass[N];
	int	ShiftNumb=0;
	for(int dy=-SearchAreaDot;dy<=SearchAreaDot;dy+=Isolation){
		for(int dx=-SearchAreaDot;dx<=SearchAreaDot;dx+=Isolation){
			ShiftList[ShiftNumb].x=dx;
			ShiftList[ShiftNumb].y=dy;
			ShiftNumb++;
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int n=0;n<ShiftNumb;n++){
			int	dx=ShiftList[n].x;
			int	dy=ShiftList[n].y;
			double	SumD=0;

			for(GerberFastItemPointer *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
				double	D=a->GetPoint()->TransDetail.MatchExecute(a->GetPoint(),dx ,dy
													,EdgeMergin,EdgeMergin,DotPerLine-EdgeMergin ,MaxLines-EdgeMergin
													,GBaseUseBrighterInPattern,BrighterInPattern);
				SumD+=D*D;
			}
			MList[n].Coeff=SumD;
			MList[n].Dx=dx;
			MList[n].Dy=dy;
		}
	}
	QSort(MList,ShiftNumb,sizeof(struct	MatchList),MListFunc);

	int	MaxDx=0;
	int	MaxDy=0;
	if(MList[0].Coeff>0.0){
		int	Numb=5;
		if(Numb>ShiftNumb)
			Numb=ShiftNumb;
		int	WNumb=0;
		for(int i=0;i<Numb;i++){
			for(int tx=-Isolation;tx<=Isolation;tx++){
				for(int ty=-Isolation;ty<=Isolation;ty++){
					WList[WNumb].Dx=MList[i].Dx+tx;
					WList[WNumb].Dy=MList[i].Dy+ty;
					WNumb++;
				}
			}
		}

		MaxDx=MList[0].Dx;
		MaxDy=MList[0].Dy;
		if(MList[0].Coeff>0.0001){
			if(Isolation>1){
				double	MaxD=0;
				#pragma omp parallel
				{
					#pragma omp for
					for(int i=0;i<WNumb;i++){
						int	dx=WList[i].Dx;
						int	dy=WList[i].Dy;
						double	SumD=0;
						for(GerberFastItemPointer *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
							double	D=a->GetPoint()->TransDetail.MatchExecute(a->GetPoint(),dx ,dy
																,EdgeMergin,EdgeMergin,DotPerLine-EdgeMergin ,MaxLines-EdgeMergin
																,GBaseUseBrighterInPattern,BrighterInPattern);
							SumD+=D*D;
						}
						#pragma omp critical
						{
							if(SumD>MaxD){
								MaxD=SumD;
								MaxDx=dx;
								MaxDy=dy;
							}
						}
					}
				}
			}
		}
	}
	delete	[]WList;
	delete	[]MList;
	delete	[]ShiftList;

	ShiftX=MaxDx;
	ShiftY=MaxDy;
}

void	GerberFastItemBase::FuncEachSearchDot(ImageBuffer &Ibuff,int EachSearchDot
							,int Mx,int My	,int &OffsetX ,int &OffsetY
							,int DotPerLine ,int MaxLines ,int EdgeMergin
							,bool UseBrighterInPattern,bool BrighterInPattern)
{
	if(EachSearchDot==0){
		OffsetX=0;
		OffsetY=0;
		return;
	}
	double	MaxD=0;
	int		MaxDx=0;
	int		MaxDy=0;
	for(int dy=-EachSearchDot;dy<=EachSearchDot;dy++){
		for(int dx=-EachSearchDot;dx<=EachSearchDot;dx++){
			double	D=TransDetail.MatchExecute(this,Mx+dx ,My+dy
											,EdgeMergin,EdgeMergin,DotPerLine-EdgeMergin ,MaxLines-EdgeMergin
											,UseBrighterInPattern,BrighterInPattern);
			if(MaxD<D){
				MaxD=D;
				MaxDx=dx;
				MaxDy=dy;
			}
		}
	}
	OffsetX=MaxDx;
	OffsetY=MaxDy;
}


bool	ClusterMatchDetailClass::IsInclude(GerberFastItemBase *b)
{
	double	x1,y1,x2,y2;
	b->GetXY(x1,y1,x2,y2);
	return CheckOverlapRectRect(X1, Y1, X2, Y2
							,x1,y1,x2,y2);
}

