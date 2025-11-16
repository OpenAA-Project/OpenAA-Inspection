#include "SpotReducer.h"
#include "XSpotReducer.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"

SpotReducerThreshold::SpotReducerThreshold(SpotReducerItem *parent)
:AlgorithmThreshold(parent)
{
	SpotBrightness=220;
	ReductionLevel=75;
	SpotArea=4;
	SpotCount=6;
}

void	SpotReducerThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const SpotReducerThreshold *s=(const SpotReducerThreshold *)&src;
	SpotBrightness	=s->SpotBrightness	;
	ReductionLevel	=s->ReductionLevel	;
	SpotArea		=s->SpotArea		;
	SpotCount		=s->SpotCount		;
}
bool	SpotReducerThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const SpotReducerThreshold *s=(const SpotReducerThreshold *)&src;
	if(SpotBrightness	!=s->SpotBrightness	)	return false;
	if(ReductionLevel	!=s->ReductionLevel	)	return false;
	if(SpotArea			!=s->SpotArea		)	return false;
	if(SpotCount		!=s->SpotCount		)	return false;
	return true;
}
bool	SpotReducerThreshold::Save(QIODevice *file)
{
	WORD	Ver=2;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,SpotBrightness)==false)
		return(false);
	if(::Save(file,ReductionLevel)==false)
		return(false);
	if(::Save(file,SpotArea)==false)
		return(false);
	if(::Save(file,SpotCount)==false)
		return(false);
	return(true);
}
bool	SpotReducerThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,SpotBrightness)==false)
		return(false);
	if(::Load(file,ReductionLevel)==false)
		return(false);
	if(Ver>=2){
		if(::Load(file,SpotArea)==false)
			return(false);
		if(::Load(file,SpotCount)==false)
			return(false);
	}
	return(true);
}

AlgorithmItemPLI	&SpotReducerItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPLI::operator=(src);
	return *this;
}

bool    SpotReducerItem::Save(QIODevice *f)
{
	WORD	Ver=1;

	if(f->write((const char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Save(f)==false)
		return false;
	return true;
}
bool    SpotReducerItem::Load(QIODevice *f,LayersBase *LBase)
{
	WORD	Ver;
	if(f->read((char *)&Ver,sizeof(Ver))!=sizeof(Ver))
		return(false);
	if(AlgorithmItemPLI::Load(f,LBase)==false)
		return false;

	return true;
}

void	SpotReducerItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	SpotReducerBase	*ABase=(SpotReducerBase	*)GetParentBase();
	SpotReducerDrawAttr	*a=dynamic_cast<SpotReducerDrawAttr	*>(Attr);
	if(a!=NULL && ABase!=NULL){
		SpotReducerDrawAttr	A=*((SpotReducerDrawAttr *)Attr);
		AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,&A);
	}
	else{
		AlgorithmItemPLI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

ExeResult	SpotReducerItem::ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	SpotReducerInLayer	*P=(SpotReducerInLayer *)GetParent();
	const SpotReducerThreshold	*RThr=GetThresholdR();
	int	c=RThr->SpotBrightness;
	int	N=GetArea().GetFLineLen();
	#pragma omp parallel                  
	{                                                
		#pragma omp for
	    for(int i=0;i<N;i++){
		    int x1=GetArea().GetFLineLeftX (i);
			int x2=GetArea().GetFLineRightX(i);
	        int y =GetArea().GetFLineAbsY  (i);
			if(0<=y && y<GetMaxLines()){
				BYTE	*d=P->SpotMap[y];
				BYTE	*s=GetTargetBuff().GetY(y)+x1;
				for(int x=x1;x<x2;x++,s++){
					if(*s>=c){
						d[x>>3] |= (0x80>>(x&7));
					}
				}
			}
		}
	}
	GetArea().ThinAreaPartial(P->SpotMap,P->SpotMap2,P->AllocatedXByte,P->AllocatedYLen);
	GetArea().FatAreaPartial(1,P->SpotMap,P->SpotMap2,P->AllocatedXByte,P->AllocatedYLen);
	double	Avr=GetArea().GetAverageRough(GetTargetBuff(),0,0);

	if(GetPageNumb()==1)
		return _ER_true;

	//ここで消えたビットが輝点
	#pragma omp parallel                  
	{                                                
		#pragma omp for
	    for(int i=0;i<N;i++){
		    int x1=GetArea().GetFLineLeftX (i);
			int x2=GetArea().GetFLineRightX(i);
	        int y =GetArea().GetFLineAbsY  (i);
			if(0<=y && y<GetMaxLines()){
				BYTE	*d=P->SpotMap[y];
				BYTE	*s=GetTargetBuff().GetY(y)+x1;
				for(int x=x1;x<x2;x++,s++){
					if(*s>=c){
						if((d[x>>3] & (0x80>>(x&7)))==0){
							ReduceSpot(x,y,Avr);
						}
					}
				}
			}
		}
	}
	return _ER_true;
}

void	SpotReducerItem::ReduceSpot(int x, int y
									,double Avr)
{
	const SpotReducerThreshold	*RThr=GetThresholdR();
	int	c					=RThr->SpotBrightness;
	int	SpotArea			=RThr->SpotArea;
	double ReductionLevel	=RThr->ReductionLevel;
	int	Count=0;
	for(int iy=-SpotArea;iy<=SpotArea;iy++){
		int	Y=y+iy;
		BYTE	*LTop=GetTargetBuff().GetY(Y);
		if(Y<0 || Y>=GetMaxLines()){
			continue;
		}
		for(int ix=-SpotArea;ix<=SpotArea;ix++){
			int	X=x+ix;
			if(X<0 || X>=GetDotPerLine()){
				continue;
			}
			BYTE	*s=LTop+X;
			if(*s>=c){
				Count++;
			}
		}
	}
	if(Count<RThr->SpotCount){
		for(int iy=-SpotArea;iy<=SpotArea;iy++){
			int	Y=y+iy;
			if(Y<0 || Y>=GetMaxLines()){
				continue;
			}
			BYTE	*LTop=GetTargetBuff().GetY(Y);
			for(int ix=-SpotArea;ix<=SpotArea;ix++){
				int	X=x+ix;
				if(X<0 || X>=GetDotPerLine()){
					continue;
				}	
				BYTE	*s=LTop+X;
				int	c = (*s-Avr)*ReductionLevel/100.0+Avr;
				if(c<0)
					c=0;
				if(c>255)
					c=255;
				*s=c;
			}
		}
	}
}

//===========================================
SpotReducerInLayer::SpotReducerInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	SpotMap			=NULL;
	SpotMap2		=NULL;
	AllocatedXByte	=0;
	AllocatedYLen	=0;
}
SpotReducerInLayer::~SpotReducerInLayer(void)
{
	if(SpotMap!=NULL){
		DeleteMatrixBuff(SpotMap,AllocatedYLen);
		SpotMap=NULL;
	}
	if(SpotMap2!=NULL){
		DeleteMatrixBuff(SpotMap2,AllocatedYLen);
		SpotMap2=NULL;
	}
}

void	SpotReducerInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
}

ExeResult	SpotReducerInLayer::ExecuteInitialAfterEdit	(int ExeID 
														,ResultInLayerRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	if(SpotMap!=NULL && (AllocatedXByte!=(GetDotPerLine()+7)/8 || AllocatedYLen!=GetMaxLines())){
		DeleteMatrixBuff(SpotMap,AllocatedYLen);
		SpotMap=NULL;
	}
	if(SpotMap2!=NULL && (AllocatedXByte!=(GetDotPerLine()+7)/8 || AllocatedYLen!=GetMaxLines())){
		DeleteMatrixBuff(SpotMap2,AllocatedYLen);
		SpotMap2=NULL;
	}
	if(SpotMap==NULL){
		AllocatedXByte	=(GetDotPerLine()+7)/8;
		AllocatedYLen	=GetMaxLines();
		SpotMap=MakeMatrixBuff(AllocatedXByte,AllocatedYLen);
	}
	if(SpotMap2==NULL){
		AllocatedXByte	=(GetDotPerLine()+7)/8;
		AllocatedYLen	=GetMaxLines();
		SpotMap2=MakeMatrixBuff(AllocatedXByte,AllocatedYLen);
	}
	return Ret;
}
ExeResult	SpotReducerInLayer::ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)
{
	ExeResult	Ret=AlgorithmInLayerPLI::ExecuteStartByInspection(ExeID ,Res);
	MatrixBuffClear(SpotMap,0,AllocatedXByte,AllocatedYLen);
	MatrixBuffClear(SpotMap2,0,AllocatedXByte,AllocatedYLen);
	return Ret;
}

//===========================================

void	SpotReducerInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddSpotReducerAreaPacket	*AddMArea=dynamic_cast<AddSpotReducerAreaPacket *>(packet);
	if(AddMArea!=NULL){
		for(IntClass *d=AddMArea->LayerList.GetFirst();d!=NULL;d=d->GetNext()){
			SpotReducerInLayer	*L					=(SpotReducerInLayer *)GetLayerData(d->GetValue());
			SpotReducerItem	*MData					=(SpotReducerItem	*)L->CreateItem(0);
			MData->GetThresholdW()->SpotBrightness	=AddMArea->SpotBrightness;
			MData->GetThresholdW()->ReductionLevel	=AddMArea->ReductionLevel;
			MData->GetThresholdW()->SpotArea		=AddMArea->SpotArea;
			MData->GetThresholdW()->SpotCount		=AddMArea->SpotCount;
			MData->SetArea(AddMArea->Area);
			MData->SetManualCreated(true);
			L->AppendItem(MData);
		}
		return;
	}
}

//===========================================
SpotReducerBase::SpotReducerBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	TransparentLevel=80;
	SetParam(&TransparentLevel	, /**/"Color" ,/**/"TransparentLevel"	,"Color for Transparent display level");
}

AlgorithmDrawAttr	*SpotReducerBase::CreateDrawAttr(void)
{
	return new SpotReducerDrawAttr();
}

bool	SpotReducerBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	return true;
}

