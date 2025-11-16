#include"XGeneralFunc.h"
#include"XFlexArea.h"
#include"XMainSchemeMemory.h"
#include"NList.h"
#include"XPointer.h"
#include"XImageProcess.h"
#include"XFlexAreaImageBuffer.h"
#include"XSweepPiece.h"
#include "omp.h"

class	XYCol : public NPList<XYCol>
{
	int	X,Y;
	int	Col;
public:
	XYCol(int x ,int y ,int col) : X(x),Y(y),Col(col){}
	int	GetX(void)	{	return X;	}
	int	GetY(void)	{	return Y;	}
	int	GetCol(void){	return Col;	}
};

class	XYColContainer : public NPListPack<XYCol>
{
public:
	XYColContainer(void){}

	void	Add(int x ,int y ,int col)	{	AppendList(new XYCol(x,y,col));		}
};

double	CalcCoefRough(ImageBuffer &Img,int x,int y,XYColContainer &PosList ,double AddedS,double AddedSS,int SDCount)
{
	int		AddedDD=0;
	int		AddedD=0;
	int		AddedSD=0;
	for(XYCol *a=PosList.GetFirst();a!=NULL;a=a->GetNext()){
		int	d=Img.GetPixel(a->GetX()+x,a->GetY()+y);
		AddedDD+=d*d;
		AddedD +=d;
		AddedSD+=d*a->GetCol();
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=((double)AddedS)/SDCount;
	double	AvrD=((double)AddedD)/SDCount;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	CalcCoefRough(ImageBuffer &Img,int x,int y,XYColContainer &PosList)
{
	int		AddedSS=0;
	int		AddedS=0;
	int		AddedDD=0;
	int		AddedD=0;
	int		AddedSD=0;
	int		SDCount=0;
	for(XYCol *a=PosList.GetFirst();a!=NULL;a=a->GetNext()){
		int	s=a->GetCol();
		int	DestX=a->GetX()+x;
		int	DestY=a->GetY()+y;
		if(0<=DestX && DestX<Img.GetWidth() && 0<=DestY && DestY<Img.GetHeight()){
			int	d=Img.GetPixel(DestX,DestY);
			AddedSS+=s*s;
			AddedS +=s;
			AddedDD+=d*d;
			AddedD +=d;
			AddedSD+=d*s;
			SDCount++;
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=((double)AddedS)/SDCount;
	double	AvrD=((double)AddedD)/SDCount;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}



double	CalcCoefMiddle(ImageBuffer &Img,int OffX,int OffY,FlexAreaImageBuffer &Seed)
{
	double	AddedSS=0.0;
	int		AddedS=0;
	double	AddedDD=0.0;
	int		AddedD=0;
	double	AddedSD=0.0;
	int		X1=Seed.GetArea().GetMinX();
	int		Y1=Seed.GetArea().GetMinY();
	int		N=Seed.GetArea().GetFLineLen();
	int		W=Seed.GetArea().GetWidth();
	int		SDCount=0;
	int	YSep,XSep;

	if(N<10)
		YSep=1;
	else if(N<20)
		YSep=2;
	else if(N<50)
		YSep=3;
	else if(N<100)
		YSep=4;
	else
		YSep=N/25;

	if(W<10)
		XSep=1;
	else if(W<20)
		XSep=2;
	else if(W<50)
		XSep=3;
	else if(W<100)
		XSep=4;
	else
		XSep=W/25;



	for(int i=0;i<N;i++){
		int	y=Seed.GetArea().GetFLineAbsY(i);
		int	x=Seed.GetArea().GetFLineLeftX(i);
		int	numb=Seed.GetArea().GetFLineNumb(i);
		int	DestY=y+OffY;
		if((y%YSep)!=0){
			continue;
		}
		if(0<=DestY && DestY<Img.GetHeight()){
			int		iAddedSS=0;
			int		iAddedDD=0;
			int		iAddedSD=0;
			BYTE	*s=Seed.GetImage().GetY(y);
			BYTE	*d=Img.GetY(DestY);
			for(int h=0;h<numb;h+=XSep){
				int	DestX=x+h+OffX;
				if(0<=DestX && DestX<Img.GetWidth()){
					int	S=s[x+h];
					int	D=d[DestX];
					iAddedSS+=S*S;
					AddedS  +=S;
					iAddedDD+=D*D;
					AddedD  +=D;
					iAddedSD+=S*D;
					SDCount++;
				}
			}
			AddedSS+=iAddedSS;
			AddedDD+=iAddedDD;
			AddedSD+=iAddedSD;
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=((double)AddedS)/SDCount;
	double	AvrD=((double)AddedD)/SDCount;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}

double	CalcCoefDetail(ImageBuffer &Img,int OffX,int OffY,FlexAreaImageBuffer &Seed)
{
	double	AddedSS=0.0;
	int		AddedS=0;
	double	AddedDD=0.0;
	int		AddedD=0;
	double	AddedSD=0.0;
	int		X1=Seed.GetArea().GetMinX();
	int		Y1=Seed.GetArea().GetMinY();
	int		N=Seed.GetArea().GetFLineLen();
	int		SDCount=0;

	for(int i=0;i<N;i++){
		int	y=Seed.GetArea().GetFLineAbsY(i);
		int	x=Seed.GetArea().GetFLineLeftX(i);
		int	numb=Seed.GetArea().GetFLineNumb(i);
		int	DestY=y+OffY;
		if(0<=DestY && DestY<Img.GetHeight()){
			int		iAddedSS=0;
			int		iAddedDD=0;
			int		iAddedSD=0;
			BYTE	*s=Seed.GetImage().GetY(y);
			BYTE	*d=Img.GetY(DestY);
			for(int h=0;h<numb;h++){
				int	DestX=x+h+OffX;
				if(0<=DestX && DestX<Img.GetWidth()){
					int	S=s[x+h];
					int	D=d[DestX];
					iAddedSS+=S*S;
					AddedS  +=S;
					iAddedDD+=D*D;
					AddedD  +=D;
					iAddedSD+=S*D;
					SDCount++;
				}
			}
			AddedSS+=iAddedSS;
			AddedDD+=iAddedDD;
			AddedSD+=iAddedSD;
		}
	}
	if(SDCount==0){
		return 0.0;
	}
	double	AvrS=((double)AddedS)/SDCount;
	double	AvrD=((double)AddedD)/SDCount;

	double	M=(AddedSS-SDCount*AvrS*AvrS)*(AddedDD-SDCount*AvrD*AvrD);
	if(M<=0){
		return 0.0;
	}
	M=sqrt(M);
	double	K=AddedSD-SDCount*AvrS*AvrD;
	return K/M;
}


double	GetMaxCoefPos(FlexArea *f,int GSep ,ImageBuffer &Img,FlexAreaImageBuffer &Seed,int &ResX,int &ResY,double CoEfficient)
{
	int	H=Seed.GetArea().GetHeight();
	int	W=Seed.GetArea().GetWidth();

	double	MaxD=0.0;
	int	N=f->GetFLineLen();
	for(int i=0;i<N;i++){
		int	y=f->GetFLineAbsY(i)*GSep;
		int	x=f->GetFLineLeftX(i)*GSep;
		int	numb=f->GetFLineNumb(i);
		for(int h=0;h<numb;h+=GSep){
			double	d=CalcCoefMiddle(Img,x+h-W/2,y-H/2,Seed);
			if(d>MaxD){
				MaxD=d;
				ResX=x+h-W/2;
				ResY=y  -H/2;
			}
		}
	}
	if(MaxD<CoEfficient)
		return MaxD;

	int	iResX=0;
	int	iResY=0;
	for(int iy=-GSep;iy<=GSep;iy++){
		for(int ix=-GSep;ix<=GSep;ix++){
			double	d=CalcCoefMiddle(Img,ResX+ix,ResY+iy,Seed);
			if(d>MaxD){
				MaxD=d;
				iResX=ix;
				iResY=iy;
			}
		}
	}
	ResX+=iResX;
	ResY+=iResY;

	double	FinalD=CalcCoefDetail(Img,ResX,ResY,Seed);
	return FinalD;
}

int	SweepDbg=0;
int	SweepDbgX=1173;
int	SweepDbgY=3103;

int		SweepPiece(ImageBuffer &Img ,FlexAreaImageBuffer &Seed ,SweepResultContainer &Found 
					,BYTE **BitBuff,int XByte ,int YLen
					,double CoEfficient)
{
	int	H=Seed.GetArea().GetHeight();
	int	W=Seed.GetArea().GetWidth();
	int	XSep,YSep;

	if(W<10)
		XSep=1;
	else if(W<20)
		XSep=2;
	else{
		XSep=W/5;
	}
	if(H<10)
		YSep=1;
	else if(H<20)
		YSep=2;
	else{
		YSep=H/5;
	}

	int	XCount=W/XSep;
	int	YCount=H/YSep;

	XYColContainer	PosList;
	int	GSep=2;

	//‘ŠŠÖƒŠƒXƒg¶¬
	for(int y=0;y<YCount;y++){
		for(int x=0;x<XCount;x++){
			int	X=x*XSep;
			int	Y=y*YSep;
			if(Seed.GetArea().IsInclude(X,Y)==true){
				PosList.Add(X,Y,Seed.GetImage().GetPixel(X,Y));
			}
		}
	}
	double	AddedS =0.0;
	double	AddedSS=0.0;
	int		SDCount=0;
	for(XYCol *a=PosList.GetFirst();a!=NULL;a=a->GetNext()){
		int	s=a->GetCol();
		AddedSS+=s*s;
		AddedS +=s;
		SDCount++;
	}

	MatrixBuffClear	(BitBuff,0,XByte,YLen);
	int	YNumb=Img.GetHeight()/GSep;
	int	XNumb=Img.GetWidth();
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int yn=0;yn<YNumb;yn++){
			int	y=yn*GSep;
			BYTE	*BitBuffYPointer=BitBuff[yn];
			for(int x=0;x<XNumb;x+=GSep){
				int	Mx=x-Seed.GetArea().GetWidth()/2;
				int	My=y-Seed.GetArea().GetHeight()/2;
				if(0<=Mx && (Mx+Seed.GetArea().GetWidth ())<Img.GetWidth()
				&& 0<=My && (My+Seed.GetArea().GetHeight())<Img.GetHeight()){
					double	d=CalcCoefRough(Img,Mx,My,PosList 
						,AddedS,AddedSS,SDCount);
					if(d>=CoEfficient){
						SetBmpBitOnY1(BitBuffYPointer,x/GSep);
					}
				}
				else{
					double	d=CalcCoefRough(Img,Mx,My,PosList);
					if(d>=CoEfficient){
						SetBmpBitOnY1(BitBuffYPointer,x/GSep);
					}
				}
			}
		}
	}
	PureFlexAreaListContainer FPack;
	PickupFlexArea(BitBuff,XByte ,XByte*8,YLen,FPack);

	//DeleteMatrixBuff(BitBuff,YLen);

	int	FoundCount=0;

	PureFlexAreaList *f;
	#pragma omp parallel
	#pragma omp single private(f)
	for(f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		#pragma omp task
		{
			if(f->IsInclude(SweepDbgX,SweepDbgY)==true){
				SweepDbg++;
			}
			int	X,Y;
			double	b=GetMaxCoefPos(f,GSep,Img,Seed,X,Y,CoEfficient);
			if(b>=CoEfficient){
				SweepResult	*k=new SweepResult(X,Y,b);

				#pragma omp critical
				{
					Found.AppendList(k);
					FoundCount++;
				}
			}
		}
	}
	return FoundCount;
}