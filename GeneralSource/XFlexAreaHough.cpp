#include "XFlexAreaHough.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XPointer.h"
#include "XCrossObj.h"

HoughLine::HoughLine(void)
{
	DotCount=0;
}
HoughLine::~HoughLine(void)
{
}

bool	HoughLine::Save(QIODevice *f)
{
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	if(::Save(f,DotCount)==false)
		return false;
	return true;
}
bool	HoughLine::Load(QIODevice *f)
{
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	if(::Load(f,DotCount)==false)
		return false;
	return true;
}

struct HoughLineLimitless
{
	int	t,s;
	int	DCount;
};

static	int	FuncHDim(const void *a ,const void *b)
{
	const struct HoughLineLimitless	*pa=(const struct HoughLineLimitless *)a;
	const struct HoughLineLimitless	*pb=(const struct HoughLineLimitless *)b;
	int	d=pb->DCount - pa->DCount;
	return d;
}

void	PickupLinesByHough(FlexArea &Area
							,HoughLineContainer &PickedLines
							,int LineArea)
{
	PureFlexAreaList	*L=new PureFlexAreaList(Area);
	PureFlexAreaListContainer FPack;
	FPack.AppendList(L);
	PickupLinesByHough(FPack,PickedLines,LineArea);
}
void	PickupLinesByHough(PureFlexAreaListContainer &FPack
							,HoughLineContainer &PickedLines
							,int LineArea)
{
	int	MinX=99999999;
	int	MinY=99999999;
	int	MaxX=-99999999;
	int	MaxY=-99999999;
	const	int	MapSize=128;

	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		int	x1,y1,x2,y2;
		if(f->GetXY(x1,y1,x2,y2)==true){
			MinX=min(MinX,x1);
			MinY=min(MinY,y1);
			MaxX=max(MaxX,x2);
			MaxY=max(MaxY,y2);
		}
	}
	int	XLen=MaxX-MinX;
	int	YLen=MaxY-MinY;
	//p=x*cos(s)+y*sin(s)
	//pÇÃîÕàÕÇÕ-(XLen+YLen) Å` (XLen+YLen)

	int	SXLen=MapSize;
	int	XYLen=XLen+YLen+1;
	int	SYLen=MapSize;
	double	YRate=SYLen/((double)XYLen);
	BYTE	tMapDim[MapSize*MapSize*sizeof(uint16)+MapSize*16];
	uint16	**HMap=(uint16 **)MakeMatrixBuff(SXLen*sizeof(uint16) ,SYLen,tMapDim,sizeof(tMapDim));
	MatrixBuffClear	((BYTE **)HMap ,0 ,SXLen*sizeof(uint16) ,SYLen,false);

	double	CosTable[MapSize];
	double	SinTable[MapSize];

	for(int s=0;s<MapSize;s++){
		double	hs=2*M_PI/MapSize;
		CosTable[s]=cos(hs);
		SinTable[s]=sin(hs);
	}
	double	Cx=(MinX+MaxX)/2.0;
	double	Cy=(MinY+MaxY)/2.0;

	for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
		int	N=f->GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y	=f->GetFLineAbsY(i);
			int	X1	=f->GetFLineLeftX(i);
			int	Numb=f->GetFLineNumb(i);
			for(int x=0;x<Numb;x++){
				for(int s=0;s<MapSize;s++){
					double	p=(X1+x-Cx)*CosTable[s]+(Y-Cy)*SinTable[s];
					int	t=p*YRate+MapSize/2;
					(HMap[t])[s]++;
				}
			}
		}
	}

	struct HoughLineLimitless	HDim[MapSize*MapSize];
	int							HDimNumb=0;

	for(int t=LineArea;t<MapSize-LineArea-1;t++){
		for(int s=LineArea;s<MapSize-LineArea-1;s++){
			int	D=0;
			for(int dt=-LineArea;dt<=LineArea;dt++){
				for(int ds=-LineArea;ds<=LineArea;ds++){
					D+=(HMap[t+dt])[s+ds];
				}
			}
			if(D>0){
				HDim[HDimNumb].t=t;
				HDim[HDimNumb].s=s;
				HDim[HDimNumb].DCount=D;
				HDimNumb++;
			}
		}
	}
	QSort(HDim,HDimNumb,sizeof(struct HoughLineLimitless),FuncHDim);
	for(int k=0;k<HDimNumb;k++){
		for(int i=0;i<k;i++){
			if(abs(HDim[i].t-HDim[k].t)<=LineArea
			&& abs(HDim[i].s-HDim[k].s)<=LineArea){
				goto	NextK;
			}
		}
		HoughLine	*L=new HoughLine();
		double	s=HDim[k].s/((double)MapSize)*2*M_PI;
		double	p=HDim[k].t/YRate+Cy;
		double	a=cos(s);
		double	b=sin(s);
		double	c=-p;
		//a*x+b*y+c=0

		double	Px,Py;
		if(fabs(a)>fabs(b)){
			Px=-c/a;
			Py=0;
		}
		else{
			Px=0;
			Py=-c/b;
		}
		double	MinT=99999999;
		double	MaxT=-99999999;

		for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
			int	N=f->GetFLineLen();
			for(int i=0;i<N;i++){
				int	Y	=f->GetFLineAbsY(i);
				int	X1	=f->GetFLineLeftX(i);
				int	Numb=f->GetFLineNumb(i);
				for(int x=0;x<Numb;x++){
					double fX ,fY;
					double	Len=GetLinePointFoot(a,b,c ,X1+x ,Y,fX ,fY);
					if(Len<=LineArea){
						double	t=hypot(Px-fX,Py-fY);
						if(t<MinT){
							MinT=t;
							L->X1=X1+x;
							L->Y1=Y;
						}
						if(t>MaxT){
							MaxT=t;
							L->X2=X1+x;
							L->Y2=Y;
						}
						L->DotCount++;
					}
				}
			}
		}
		if(L->DotCount>2){
			PickedLines.AppendList(L);
		}
		else{
			delete	L;
		}
	NextK:;
	}
	::DeleteMatrixBuff((BYTE **)HMap,tMapDim,SYLen);
}