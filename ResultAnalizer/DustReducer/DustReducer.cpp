#include "DustReducer.h"
#include "XResultAnalizerDLL.h"
#include "XLanguageClass.h"
#include "XGeneralFunc.h"
#include "SettingDustReducerDialog.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "XResult.h"
#include "swap.h"

const	char	*sRoot=/**/"ResultAnalizer";
const	char	*sName=/**/"DustReducer";

DEFFUNCEX	void	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
}

DEFFUNCEX	bool	DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD	DLL_GetVersion(void)
{
	return 1;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangLibSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	ResultAnalizerItemBase	*DLL_Initial(LayersBase *base)
{
	return new DustReducer(base);
}
DEFFUNCEX	void			DLL_Release(ResultAnalizerItemBase *handle)
{
	delete	handle;
}
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	DustReducer	*d=(DustReducer *)handle;
	d->Allocate();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	DustReducer	*d=(DustReducer *)handle;
	d->ExecuteStartByInspection();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	DustReducer	*d=(DustReducer *)handle;
	return d->Execute(Res);
}

//================================================================================================

DustReducer::DustReducer(LayersBase *Base)
	:ResultAnalizerItemBase(Base)
{
	//NGMap=NULL;
	XLen	=0;
	XByte	=0;
	YLen	=0;
	AllocatedCount	=10000;
	WPoint			=0;
	Dim		=new struct	DustReducerResult[AllocatedCount];
}
DustReducer::~DustReducer(void)
{
	//if(NGMap!=NULL){
	//	::DeleteMatrixBuff(NGMap,YLen);
	//	NGMap=NULL;
	//}
	if(Dim!=NULL){
		delete	[]Dim;
		Dim=NULL;
	}
}
bool	DustReducer::Save(QIODevice *f)
{
	if(::Save(f,VLayer)==false)
		return false;
	if(::Save(f,BrightnessL)==false)
		return false;
	if(::Save(f,BrightnessH)==false)
		return false;
	if(::Save(f,MaxAreaDots)==false)
		return false;
	if(::Save(f,MaxLength)==false)
		return false;
	if(::Save(f,MaxV)==false)
		return false;
	return true;
}

bool	DustReducer::Load(QIODevice *f)
{
	if(::Load(f,VLayer)==false)
		return false;
	if(::Load(f,BrightnessL)==false)
		return false;
	if(::Load(f,BrightnessH)==false)
		return false;
	if(::Load(f,MaxAreaDots)==false)
		return false;
	if(::Load(f,MaxLength)==false)
		return false;
	if(::Load(f,MaxV)==false)
		return false;
	return true;
}

bool	DustReducer::ShowSettingDialogFunc(void)
{
	SettingDustReducerDialog	D(GetLayersBase(),this);
	D.exec();
	return true;
}

void		DustReducer::Allocate(void)
{
	//if(NGMap!=NULL){
	//	::DeleteMatrixBuff(NGMap,YLen);
	//}
	XLen=MaxLength*3;
	YLen=MaxLength*3;
	XByte=(XLen+7)/8;
	//NGMap=MakeMatrixBuff(XByte,YLen);
}
void		DustReducer::ExecuteStartByInspection(void)
{
	WPoint=0;
}
ExeResult	DustReducer::Execute(ResultInItemRoot *Res)
{
	if(Res->IsOk()==false){
		AlgorithmItemRoot	*Item=Res->GetAlgorithmItem();
		if(Item!=NULL && Res->GetPosList().GetCount()!=0){
			ImageBuffer	&TBuff=Item->GetDataInPage()->GetLayerData(VLayer)->GetTargetBuff();
			int	RNumber=0;
			for(ResultPosList *r=Res->GetPosList().GetFirst();r!=NULL;){
				ResultPosList *NextR=r->GetNext();
				int X, Y;
				r->GetPosInTarget(Res,X, Y);
				if(IsDust(Item->GetPhaseCode(),Item->GetPage(),Item->GetLayer(),Item->GetID(),RNumber,X,Y,TBuff)==true){
					Res->GetPosList().RemoveList(r);
					delete	r;
				}
				r=NextR;
				RNumber++;
			}
			if(Res->GetPosList().GetCount()==0){
				Res->SetError(1);	//OK
			}
		}
	}
			
	return _ER_true;
}

bool	DustReducer::IsDust(int Phase ,int Page ,int Layer ,int ItemID, int PosNo
							,int X,int Y,ImageBuffer &TBuff)
{
	int	RXLen=XLen/2;
	int	RYLen=YLen/2;

	int	MinY=99999999;
	int	MaxY=0;
	int	MinX=99999999;
	int	MaxX=0;
	int	AreaDots=0;
	double	AddedSS=0;
	double	AddedS=0;

	for(int yn=0;yn<YLen;yn++){
		BYTE	*s=TBuff.GetY(Y-RYLen+yn);
		//BYTE	*d=NGMap[yn];
		s+=X-RXLen;
		for(int xn=0;xn<XLen;xn++){
			BYTE	c=*(s++);
			if(BrightnessL<=c && c<=BrightnessH){
				if(MinY>yn)
					MinY=yn;
				if(MaxY<yn)
					MaxY=yn;
				if(MinX>xn)
					MinX=xn;
				if(MaxX<xn)
					MaxX=xn;
				//SetBmpBitOnY1(d,xn);
				AreaDots++;
			}
			else{
				//SetBmpBitOnY0(d,xn);
				AddedS+=c;
				AddedSS+=((int)c)*(int)c;
			}
		}
	}
	int	DustLen=max(MaxX-MinX,MaxY-MinY);
	int	N=XLen*YLen-AreaDots;
	double	AvrS=AddedS/N;
	double	V=AddedSS-AvrS*AvrS*N;
	double	S=sqrt(V/N);

	bool	Dust=true;
	if(DustLen>MaxLength || AreaDots>MaxAreaDots || S>MaxV){
		Dust=false;
	}
	if(WPoint<AllocatedCount){
		Dim[WPoint].Phase	=Phase;
		Dim[WPoint].Page	=Page;
		Dim[WPoint].Layer	=Layer;
		Dim[WPoint].ItemID	=ItemID;
		Dim[WPoint].PosNo	=PosNo;
		Dim[WPoint].Dots	=AreaDots;
		Dim[WPoint].Length	=DustLen;
		Dim[WPoint].S		=S;
		Dim[WPoint].Dust	=Dust;
	}
	if(WPoint<AllocatedCount){
		WPoint++;
	}
	return Dust;
}