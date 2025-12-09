
#include "XFlexArea.h"
#include "swap.h"
#include "XCrossObj.h"
#include <omp.h>

const	int	XNumb=6;
const	int	YNumb=25;


class	FlexAreaPointerListWithXY : public NPList<FlexAreaPointerListWithXY>
{
	FlexArea	*Pointer;
public:
	int	x1,y1,x2,y2;

	FlexAreaPointerListWithXY(void)		    {	Pointer=NULL;	}
	FlexAreaPointerListWithXY(FlexArea *P)    {	Pointer=P;		}

	FlexArea	*GetArea(void)	const   {	return Pointer;	}
};

class	FlexAreaPointerContainerWithXY : public NPListPack<FlexAreaPointerListWithXY>
{
public:
	FlexAreaPointerContainerWithXY(void){}
	FlexAreaPointerListWithXY	*Add(FlexArea *a)
			{	
				FlexAreaPointerListWithXY	*p=new FlexAreaPointerListWithXY(a);
				AppendList(p);
				return p;
			}
};


static	void	Remove(FlexAreaPointerContainerWithXY	DTable[YNumb][XNumb]
			  ,PureFlexAreaList *s
			  ,int WDot,int HDot
			  ,int OffsetX ,int OffsetY)
{
	int	x1,y1,x2,y2;
	s->GetXY(x1,y1,x2,y2);

	int	Nx1=(x1-OffsetX)/WDot;
	int	Ny1=(y1-OffsetY)/HDot;
	int	Nx2=(x2-OffsetX)/WDot;
	int	Ny2=(y2-OffsetY)/HDot;
	if(Nx1<0)
		Nx1=0;
	if(Ny1<0)
		Ny1=0;
	if(Nx2>=XNumb)
		Nx2=XNumb-1;
	if(Ny2>=YNumb)
		Ny2=YNumb-1;

	for(int ny=Ny1;ny<=Ny2;ny++){
		for(int nx=Nx1;nx<=Nx2;nx++){
			for(FlexAreaPointerListWithXY *b=DTable[ny][nx].GetFirst();b!=NULL;){
				FlexAreaPointerListWithXY *bnext=b->GetNext();
				if(b->GetArea()==s){
					DTable[ny][nx].RemoveList(b);
					delete	b;
				}
				b=bnext;
			}
		}
	}
}

void	BindClusterize(PureFlexAreaListContainer &FPackIn ,PureFlexAreaListContainer &Binded ,double Distance)
{
	int	W=FPackIn.GetWidth();
	int	H=FPackIn.GetHeight();

	int	WDot=(W+XNumb-1)/XNumb;
	int	HDot=(H+YNumb-1)/YNumb;

	FlexAreaPointerContainerWithXY	DTable[YNumb][XNumb];

	for(PureFlexAreaList *f=FPackIn.GetFirst();f!=NULL;f=f->GetNext()){
		int	x1,y1,x2,y2;
		f->GetXY(x1,y1,x2,y2);

		int	Nx1=(x1-FPackIn.GetMinX())/WDot;
		int	Ny1=(y1-FPackIn.GetMinY())/HDot;
		int	Nx2=(x2-FPackIn.GetMinX())/WDot;
		int	Ny2=(y2-FPackIn.GetMinY())/HDot;

		if(Nx1<0)
			Nx1=0;
		if(Ny1<0)
			Ny1=0;
		if(Nx2>=XNumb)
			Nx2=XNumb-1;
		if(Ny2>=YNumb)
			Ny2=YNumb-1;

		for(int ny=Ny1;ny<=Ny2;ny++){
			for(int nx=Nx1;nx<=Nx2;nx++){
				FlexAreaPointerListWithXY	*p=DTable[ny][nx].Add(f);
				p->x1=Nx1;
				p->y1=Ny1;
				p->x2=Nx2;
				p->y2=Ny2;
			}
		}
	}

	const	int	XYNumb=XNumb*YNumb;
	FlexAreaPointerContainerWithXY	*DTableDim[XYNumb];
	for(int ky=0;ky<YNumb;ky++){
		for(int kx=0;kx<XNumb;kx++){
			DTableDim[ky*XNumb+kx]=&DTable[ky][kx];
		}
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<XYNumb;i++){
			int	ny=i/XNumb;
			int	nx=i%XNumb;
			for(FlexAreaPointerListWithXY *a=DTable[ny][nx].GetFirst();a!=NULL;a=a->GetNext()){
				if(a->x1==a->x2 && a->y1==a->y2){
					int	rx1,ry1,rx2,ry2;
					a->GetArea()->GetXY(rx1,ry1,rx2,ry2);
					for(FlexAreaPointerListWithXY *b=a->GetNext();b!=NULL;){
						FlexAreaPointerListWithXY *bnext=b->GetNext();
						if(b->x1==b->x2 && b->y1==b->y2){
							bool	Overlapped;
							int	tx1,ty1,tx2,ty2;
							b->GetArea()->GetXY(tx1,ty1,tx2,ty2);
							if((Overlapped=CheckOverlapRectRect(tx1,ty1,tx2,ty2 ,rx1,ry1,rx2,ry2))==true
							|| GetDistanceRect2Rect(tx1,ty1,tx2,ty2 ,rx1,ry1,rx2,ry2)<=Distance){
								if(Overlapped==true
								|| b->GetArea()->GetDistance(*b->GetArea())<=Distance){
									DTable[ny][nx].RemoveList(b);
									*a->GetArea() += *b->GetArea();
									delete	b;
								}
							}
						}
						b=bnext;
					}
				}
			}
		}
	}


	for(int ky=0;ky<YNumb;ky++){
		for(int kx=0;kx<XNumb;kx++){
			FlexAreaPointerListWithXY *a;
			while((a=DTable[ky][kx].GetFirst())!=NULL){
				DTable[ky][kx].RemoveList(a);

				PureFlexAreaList	*s=new PureFlexAreaList(*a->GetArea());
				Remove(DTable,(PureFlexAreaList *)a->GetArea()
						,WDot,HDot
						,FPackIn.GetMinX() ,FPackIn.GetMinY());

				int	tx1,ty1,tx2,ty2;
				bool	FlagBindArea;
				do{
					FlagBindArea=false;
					s->GetXY(tx1,ty1,tx2,ty2);
					int	Nx1=(tx1-FPackIn.GetMinX())/WDot;
					int	Ny1=(ty1-FPackIn.GetMinY())/HDot;
					int	Nx2=(tx2-FPackIn.GetMinX())/WDot;
					int	Ny2=(ty2-FPackIn.GetMinY())/HDot;
					if(Nx1<0)
						Nx1=0;
					if(Ny1<0)
						Ny1=0;
					if(Nx2>=XNumb)
						Nx2=XNumb-1;
					if(Ny2>=YNumb)
						Ny2=YNumb-1;
					for(int ny=Ny1;ny<=Ny2;ny++){
						for(int nx=Nx1;nx<=Nx2;nx++){
							if(nx!=kx || ny!=ky){
								for(FlexAreaPointerListWithXY *b=DTable[ny][nx].GetFirst();b!=NULL;){
									FlexAreaPointerListWithXY *bnext=b->GetNext();
									int	rx1,ry1,rx2,ry2;
									b->GetArea()->GetXY(rx1,ry1,rx2,ry2);
									bool	Overlapped;
									if((Overlapped=CheckOverlapRectRect(tx1,ty1,tx2,ty2 ,rx1,ry1,rx2,ry2))==true
									|| GetDistanceRect2Rect(tx1,ty1,tx2,ty2 ,rx1,ry1,rx2,ry2)<=Distance){
										if(Overlapped==true
										|| s->GetDistance(*b->GetArea())<=Distance){
											DTable[ky][kx].RemoveList(b);
											*s+=*b->GetArea();

											Remove(DTable,(PureFlexAreaList *)b->GetArea()
													,WDot,HDot
													,FPackIn.GetMinX() ,FPackIn.GetMinY());
											s->GetXY(tx1,ty1,tx2,ty2);
											FlagBindArea=true;
										}
									}
									b=bnext;
								}
							}
						}
					}
				}while(FlagBindArea==true);
				Binded.AppendList(s);
			}
		}
	}
}

