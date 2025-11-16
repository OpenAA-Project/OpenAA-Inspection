#include "ResultCategorizer.h"
#include "SettingCategoryDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "XResult.h"

ResultCatShape::LayerJudgement::LayerJudgement(void)
{
	MinLength	=0;
	MaxLength	=100;
	MinPixels	=0;
	MaxPixels	=10000;
	BrightDiffL	=20;
	BrightDiffH	=20;
}

bool	ResultCatShape::LayerJudgement::Save(QIODevice *f)
{
	int32	Ver=VersionResultCategorizer;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,MinLength)==false)
		return false;
	if(::Save(f,MaxLength)==false)
		return false;
	if(::Save(f,MinPixels)==false)
		return false;
	if(::Save(f,MaxPixels)==false)
		return false;
	if(::Save(f,BrightDiffL)==false)
		return false;
	if(::Save(f,BrightDiffH)==false)
		return false;
	return true;
}
bool	ResultCatShape::LayerJudgement::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,MinLength)==false)
		return false;
	if(::Load(f,MaxLength)==false)
		return false;
	if(::Load(f,MinPixels)==false)
		return false;
	if(::Load(f,MaxPixels)==false)
		return false;
	if(::Load(f,BrightDiffL)==false)
		return false;
	if(::Load(f,BrightDiffH)==false)
		return false;
	return true;
}

ResultCatShape::ResultCatShape(void)
{
	CategoryID=1;
	Phase=0;
	Priority=100;
}

bool	ResultCatShape::Save(QIODevice *f)
{
	int32	Ver=VersionResultCategorizer;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CategoryID)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Priority)==false)
		return false;
	if(::Save(f,ResultName)==false)
		return false;
	int32	LayerNumb=sizeof(Judge)/sizeof(Judge[0]);
	if(::Save(f,LayerNumb)==false)
		return false;
	for(int i=0;i<LayerNumb;i++){
		if(Judge[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ResultCatShape::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,CategoryID)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Priority)==false)
		return false;
	if(::Load(f,ResultName)==false)
		return false;
	int32	LayerNumb;
	if(::Load(f,LayerNumb)==false)
		return false;
	for(int i=0;i<LayerNumb && i<sizeof(Judge)/sizeof(Judge[0]);i++){
		if(Judge[i].Load(f)==false){
			return false;
		}
	}
	for(int i=sizeof(Judge)/sizeof(Judge[0]);i<LayerNumb;i++){
		struct LayerJudgement	Dummy;
		if(Dummy.Load(f)==false){
			return false;
		}
	}
	return true;
}
int	ResultCatShape::Compare(ResultCatShape &src)
{
	return Priority-src.Priority;
}

void	ResultCatShape::Execute(ResultInItemRoot *Res
								,ImageBuffer *MasterImageList[] 
								,ImageBuffer *TargetImageList[]
								,int LayerNumb)
{
	for(ResultPosList *r=Res->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
		if(Execute(Res,r,MasterImageList ,TargetImageList,LayerNumb)==true){
			r->Message=ResultName;
			r->result &=0xFFFF;
			r->result |= CategoryID<<16;
		}
	}
}

bool	ResultCatShape::Execute(ResultInItemRoot *Res
								,ResultPosList *r
								,ImageBuffer *MasterImageList[] 
								,ImageBuffer *TargetImageList[]
								,int LayerNumb)
{
	int	Len=hypot(r->NGShape.GetWidth(),r->NGShape.GetHeight());;
	int	NGSize=r->NGSize;

	bool	Ret=true;
	for(int L=0;L<LayerNumb && Ret==true;L++){
		if(Len<Judge[L].MinLength ||  Judge[L].MaxLength<Len){
			Ret=false;
			continue;
		}
		if(NGSize<Judge[L].MinPixels || Judge[L].MaxPixels<NGSize){
			Ret=false;
			continue;
		}
		int	Dx,Dy;
		r->GetDxyInTarget(Res,Dx, Dy);
		double	AvrT=r->NGShape.GetAverage(*TargetImageList[L],Dx,Dy);
		double	AvrM=r->NGShape.GetAverage(*MasterImageList[L],0,0);
		if(AvrT<=AvrM){
			double	d=AvrM-AvrT;
			if(d<Judge[L].BrightDiffL){
				Ret=false;
				continue;
			}
		}
		else
		if(AvrT>=AvrM){
			double	d=AvrT-AvrM;
			if(d<Judge[L].BrightDiffH){
				Ret=false;
				continue;
			}
		}
	}
	return Ret;
}

ResultCatShape	*ResultCatShapeContainer::Create(void)
{
	return new ResultCatShape();
}

//========================================================================

ResultCategorizer::ResultCategorizer(LayersBase *Base)
	:ResultAnalizerItemBase(Base)
{
}
ResultCategorizer::~ResultCategorizer(void)
{
}

bool	ResultCategorizer::Save(QIODevice *f)
{
	if(ResultCat.Save(f)==false)
		return false;
	return true;
}
bool	ResultCategorizer::Load(QIODevice *f)
{
	if(ResultCat.Load(f)==false)
		return false;
	return true;
}

bool	ResultCategorizer::ShowSettingDialogFunc(void)
{
	SettingCategoryDialog	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		return true;
	}
	return false;
}

void	ResultCategorizer::Allocate(void)
{
	ResultCat.Sort();
}

void		ResultCategorizer::ExecuteStartByInspection(void)
{
}
ExeResult	ResultCategorizer::Execute(ResultInItemRoot *Res)
{
	if(GetLayersBase()!=NULL){	
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Res->GetPhaseCode());
		if(Ph!=NULL){
			DataInPage *Dp=Ph->GetPageData(Res->GetPage());
			ImageBuffer *MasterImageList[100]; 
			ImageBuffer *TargetImageList[100];

			Dp->GetMasterImages	(MasterImageList,100);
			Dp->GetTargetImages	(TargetImageList,100);
			
			for(ResultCatShape *s=ResultCat.GetFirst();s!=NULL;s=s->GetNext()){
				s->Execute(Res
							,MasterImageList
							,TargetImageList
							,Dp->GetLayerNumb());
			}
		}
	}
	return _ER_true;
}
