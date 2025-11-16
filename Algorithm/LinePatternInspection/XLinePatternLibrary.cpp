#include "XLinePatternInspection.h"
#include "XGeneralFunc.h"
#include "XInterpolation.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "swap.h"

LinePatternLibrary::LinePatternLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	LineWidthInPattern	=2;
	LineWidthOutside	=2;
	LimitLength			=200;
	GlobalSize			=2000;
	MinLineLength		=100;

	BrightWidthIL		=20;
	BrightWidthIH		=20;
	BrightWidthOL		=20;
	BrightWidthOH		=20;
	NGSizeIL			=10;
	NGSizeIH			=10;
	NGSizeOL			=10;
	NGSizeOH			=10;
	TransitDot			=1;
	SearchDot			=5;
	AdjustBrightIL		=20;
	AdjustBrightIH		=20;
	AdjustBrightOL		=20;
	AdjustBrightOH		=20;
	GlobalSearchDot		=100;

	PointMove.ModeEnabled				=true;
	PointMove.ModeAbsoluteBright		=false;
	PointMove.ModeCenterBrightFromParts	=false;
	PointMove.ModeDynamicMask			=true;
	PointMove.ModeUseRegularBrightness	=true;

	RegulatedColI		=100;
	RegulatedColO		=200;
	AngleNumb			=1;
}

bool	LinePatternLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=3;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(SubtractBlock.Save(f)==false){
		return false;
	}
	if(::Save(f,LineWidthInPattern)==false){
		return false;
	}
	if(::Save(f,LineWidthOutside)==false){
		return false;
	}
	if(::Save(f,LimitLength)==false){
		return false;
	}
	if(::Save(f,GlobalSize)==false){
		return false;
	}
	if(::Save(f,MinLineLength)==false){
		return false;
	}

	if(::Save(f,BrightWidthIL)==false){
		return false;
	}
	if(::Save(f,BrightWidthIH)==false){
		return false;
	}
	if(::Save(f,BrightWidthOL)==false){
		return false;
	}
	if(::Save(f,BrightWidthOH)==false){
		return false;
	}
	if(::Save(f,NGSizeIL)==false){
		return false;
	}
	if(::Save(f,NGSizeIH)==false){
		return false;
	}
	if(::Save(f,NGSizeOL)==false){
		return false;
	}
	if(::Save(f,NGSizeOH)==false){
		return false;
	}
	if(::Save(f,TransitDot)==false){
		return false;
	}
	if(::Save(f,SearchDot)==false){
		return false;
	}
	if(::Save(f,AdjustBrightIL)==false){
		return false;
	}
	if(::Save(f,AdjustBrightIH)==false){
		return false;
	}
	if(::Save(f,AdjustBrightOL)==false){
		return false;
	}
	if(::Save(f,AdjustBrightOH)==false){
		return false;
	}
	if(::Save(f,GlobalSearchDot)==false){
		return false;
	}
	if(::Save(f,RegulatedColI)==false){
		return false;
	}
	if(::Save(f,RegulatedColO)==false){
		return false;
	}
	DWORD	Tmp=0;
	memcpy(&Tmp,&PointMove,sizeof(PointMove));
	if(::Save(f,Tmp)==false){
		return false;
	}
	if(::Save(f,AngleNumb)==false){
		return false;
	}
	return true;
}
bool	LinePatternLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(SubtractBlock.Load(f)==false){
		return false;
	}
	if(::Load(f,LineWidthInPattern)==false){
		return false;
	}
	if(::Load(f,LineWidthOutside)==false){
		return false;
	}
	if(::Load(f,LimitLength)==false){
		return false;
	}
	if(::Load(f,GlobalSize)==false){
		return false;
	}
	if(Ver>=2){
		if(::Load(f,MinLineLength)==false){
			return false;
		}
	}
	if(::Load(f,BrightWidthIL)==false){
		return false;
	}
	if(::Load(f,BrightWidthIH)==false){
		return false;
	}
	if(::Load(f,BrightWidthOL)==false){
		return false;
	}
	if(::Load(f,BrightWidthOH)==false){
		return false;
	}
	if(::Load(f,NGSizeIL)==false){
		return false;
	}
	if(::Load(f,NGSizeIH)==false){
		return false;
	}
	if(::Load(f,NGSizeOL)==false){
		return false;
	}
	if(::Load(f,NGSizeOH)==false){
		return false;
	}
	if(::Load(f,TransitDot)==false){
		return false;
	}
	if(::Load(f,SearchDot)==false){
		return false;
	}
	if(::Load(f,AdjustBrightIL)==false){
		return false;
	}
	if(::Load(f,AdjustBrightIH)==false){
		return false;
	}
	if(::Load(f,AdjustBrightOL)==false){
		return false;
	}
	if(::Load(f,AdjustBrightOH)==false){
		return false;
	}
	if(::Load(f,GlobalSearchDot)==false){
		return false;
	}
	if(::Load(f,RegulatedColI)==false){
		return false;
	}
	if(::Load(f,RegulatedColO)==false){
		return false;
	}
	DWORD	Tmp;
	if(::Load(f,Tmp)==false){
		return false;
	}
	memcpy(&PointMove,&Tmp,sizeof(PointMove));
	if(Ver>=3){
		if(::Load(f,AngleNumb)==false){
			return false;
		}
	}
	return true;
}

LinePatternLibrary	&LinePatternLibrary::operator=(const AlgorithmLibrary &src)
{
	const LinePatternLibrary	*s=dynamic_cast<const LinePatternLibrary *>(&src);
		
	SubtractBlock		=s->SubtractBlock;
	LineWidthInPattern	=s->LineWidthInPattern;
	LineWidthOutside	=s->LineWidthOutside;
	LimitLength			=s->LimitLength;
	GlobalSize			=s->GlobalSize;
	MinLineLength		=s->MinLineLength;

	BrightWidthIL		=s->BrightWidthIL;
	BrightWidthIH		=s->BrightWidthIH;
	BrightWidthOL		=s->BrightWidthOL;
	BrightWidthOH		=s->BrightWidthOH;
	NGSizeIL			=s->NGSizeIL;
	NGSizeIH			=s->NGSizeIH;
	NGSizeOL			=s->NGSizeOL;
	NGSizeOH			=s->NGSizeOH;
	TransitDot			=s->TransitDot;
	SearchDot			=s->SearchDot;
	AdjustBrightIL		=s->AdjustBrightIL;
	AdjustBrightIH		=s->AdjustBrightIH;
	AdjustBrightOL		=s->AdjustBrightOL;
	AdjustBrightOH		=s->AdjustBrightOH;
	GlobalSearchDot		=s->GlobalSearchDot;
	RegulatedColI		=s->RegulatedColI;
	RegulatedColO		=s->RegulatedColO;

	PointMove			=s->PointMove;
	AngleNumb			=s->AngleNumb;

	return *this;
}

static	void	Vectorize(XYClassArea &src,VectorLineDouble &VLine ,double Error)
{
	bool	First=true;
	XYClass	*FirstOne=src.NPListPack<XYClass>::GetFirst();
	for(XYClass	*p1=FirstOne;src.NPListPack<XYClass>::GetCount()>1;){
		int	N=1;
		double	x[10000];
		double	y[10000];
		x[0]=p1->x;
		y[0]=p1->y;
		XYClass	*p2=src.NPListPack<XYClass>::GetRingNext(p1);
		for(;;){
			x[N]=p2->x;
			y[N]=p2->y;
			N++;
			if(N>=sizeof(x)/sizeof(x[0]))
				return;

			if(N>2 && N<src.NPListPack<XYClass>::GetCount()){
				double A,B,C;
				MakeInterpolatedLine(x ,y ,N ,A,B,C);
				double	M=hypot(A,B);
				for(int i=0;i<N;i++){
					double	d=fabs(A*x[i]+B*y[i]+C)/M;
					if(d>=Error){
						N--;
						goto	ErrorBreak;
					}
				}
			}
			p2=src.NPListPack<XYClass>::GetRingNext(p2);
			if(p1->x==p2->x && p1->y==p2->y){
				N--;
				break;
			}
		}
ErrorBreak:;
		if(N==1)
			break;
		if(First==false){
			VLine.AppendItemBase(new VectorItemDouble(x[N],y[N]));
			if(p1==p2){
				break;
			}
			for(XYClass	*t=p1;t!=p2 && src.GetCount()!=0;){
				XYClass	*tt=src.GetRingNext(t);
				src.RemoveList(t);
				delete	t;
				t=tt;
			}
		}
		else{
			VLine.AppendItemBase(new VectorItemDouble(p2->x,p2->y));
		}
		First=false;
		p1=p2;
		if(src.GetCount()<=1)
			break;
	}
}

int	DbgLinePattern=0;

void	LinePatternLibrary::MakeLinePatternOnly(int localpage
								,BYTE **CurrentMap,const BYTE **MaskMap ,BYTE **DriftMap 
								,int XByte ,int XLen,int YLen
								,NPListPack<AlgorithmItemPLI> &TmpBlockData
								,int OmitZoneDot)
{
	if(GetLayersBase()->GetBootingLevel()!=0)
		OmitZoneDot=10;

	BYTE	**TmpData=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpData2=MakeMatrixBuff(XByte ,YLen);
	MatrixBuffCopy	(TmpData,XByte ,YLen
						,(const BYTE **)CurrentMap ,XByte ,YLen);

	GetLayersBase()->ThinAreaN(TmpData
				,TmpData2
				,XByte ,YLen
				,LineWidthInPattern+LineWidthOutside+4);
	GetLayersBase()->FatAreaN(TmpData
				,TmpData2
				,XByte ,YLen
				,LineWidthInPattern+LineWidthOutside+4);
	MatrixBuffXor	(TmpData ,(const BYTE **)CurrentMap ,XByte ,YLen);
	MatrixBuffAnd	(TmpData ,(const BYTE **)MaskMap ,XByte ,YLen);
	//ThinArea(TmpData
	//			,TmpData2
	//			,XByte ,YLen);

	PureFlexAreaListContainer PFPack;
	::PickupFlexArea(TmpData,XByte ,XLen,YLen ,PFPack);

	for(PureFlexAreaList *f=PFPack.GetFirst();f!=NULL;f=f->GetNext()){
		XYClassCluster XY;
		f->MakeOutlineDot(XY);
		for(XYClassArea *a=XY.GetFirst();a!=NULL;a=a->GetNext()){
			VectorLineDouble	VLine;
			Vectorize(*a,VLine,0.9);
	
			for(VectorItemBase *d=VLine.GetFirstItem();d!=NULL;d=d->GetNext()){
				VectorItemBase *e=d->GetNext();
				if(e==NULL){
					break;
				}
				VectorItemDouble	*dh=dynamic_cast<VectorItemDouble *>(d);
				VectorItemDouble	*eh=dynamic_cast<VectorItemDouble *>(e);

				double	kx1=dh->GetX();
				double	ky1=dh->GetY();
				double	kx2=eh->GetX();
				double	ky2=eh->GetY();

				if(kx1==0 && ky1==0){
					DbgLinePattern++;
					continue;
				}
				if(kx2==0 && ky2==0){
					DbgLinePattern++;
					continue;
				}
				double	Len=hypot(kx2-kx1,ky2-ky1);
				if(Len>4000 && fabs(ky2-ky1)<100){
					DbgLinePattern++;
					continue;
				}
				if(Len<MinLineLength){
					continue;
				}
				double	Vx=(ky2-ky1)/Len;
				double	Vy=-(kx2-kx1)/Len;
				int	px=(kx1+kx2)/2 + Vx*2;
				int	py=(ky1+ky2)/2 + Vy*2;
				if(GetBmpBit(TmpData,px,py)==0){
					swap(kx1,kx2);
					swap(ky1,ky2);
				}
				int	SideMergin=SearchDot+3;
				int	BLen=LimitLength-2*SideMergin;
				if(BLen<=0)
					BLen=10;
				int	N=(Len-2*SideMergin+BLen-1)/BLen;
				if(N<=0)
					N=1;
				int	DivLen=(Len-2*SideMergin)/N;
				double	Dx=(kx2-kx1)/Len;
				double	Dy=(ky2-ky1)/Len;
				for(int	t=0;t<N;t++){
					double	hx1=kx1+Dx*(SideMergin+DivLen*t);
					double	hy1=ky1+Dy*(SideMergin+DivLen*t);
					double	hx2=hx1+Dx*(2*SideMergin+DivLen);
					double	hy2=hy1+Dy*(2*SideMergin+DivLen);

					LinePatternItem	*Item=new LinePatternItem();
					VectorLineDouble	*V=new VectorLineDouble();
					V->AppendItemBase(new VectorItemDouble(hx1,hy1));
					V->AppendItemBase(new VectorItemDouble(hx2,hy2));
					Item->SetVector(V);
					Item->SetArea(*f);
					Item->SetLibID(GetLibID());
					Item->CopyThresholdFromLibrary(GetParentLevelContainer());
					TmpBlockData.AppendList(Item);
				}
			}
		}
	}
}


//==============================================================

LinePatternLibraryContainer::LinePatternLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{}