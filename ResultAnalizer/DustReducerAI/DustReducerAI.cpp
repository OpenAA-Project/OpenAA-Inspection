#include "DustReducerAI.h"
#include "XResultAnalizerDLL.h"
#include "XLanguageClass.h"
#include "XGeneralFunc.h"
#include "ShowResultDialog.h"
#include "SettingParamDialog.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "XResult.h"
#include "swap.h"

const	char	*sRoot=/**/"ResultAnalizer";
const	char	*sName=/**/"DustReducerAI";

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
	new GUICmdReqRADustReducerAIAddCurrent		(base ,sRoot,sName);
	new GUICmdReqRADustReducerAIUpdateRegLib	(base ,sRoot,sName);
	new GUICmdReqRADustReducerAIDeleteRegLib	(base ,sRoot,sName);

	return new DustReducerAI(base);
}
DEFFUNCEX	void			DLL_Release(ResultAnalizerItemBase *handle)
{
	delete	handle;
}
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	DustReducerAI	*d=(DustReducerAI *)handle;
	d->Allocate(Res->GetPage());
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	DustReducerAI	*d=(DustReducerAI *)handle;
	return d->Execute(Res);
}
DEFFUNCEX	bool	DLL_CheckParallelExecution(ModeParallelExecution mode)
{
	return false;
}

//==========================================================================
DustReducerAI::DustReducerAI(LayersBase *Base)
:ResultAnalizerItemBase(Base)
{
	CurrentPattern[0]=NULL;
	CurrentPattern[1]=NULL;
	CurrentPattern[2]=NULL;
	ShouldAllocate	=true;
	MinMatchRate	=0.8;
	Page			=-1;

	XLen	=256;
	YLen	=256;
	RegPackFileName	=/**/"DustReducerAILib.dat";
}

DustReducerAI::~DustReducerAI()
{
	for(int i=0;i<3;i++){
		if(CurrentPattern[i]!=NULL){
			delete	[]CurrentPattern[i];
		}
		CurrentPattern[i]=NULL;
	}
}

void	DustReducerAI::Allocate(int page)
{
	if(ShouldAllocate==true){
		for(int i=0;i<GetLayerNumb(page);i++){
			if(CurrentPattern[i]!=NULL){
				delete	[]CurrentPattern[i];
			}	
			CurrentPattern[i]=new BYTE[XLen*YLen];
		}
		ShouldAllocate=false;
	}
}

bool	DustReducerAI::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)	return false;
	if(::Save(f,XLen)==false)	return false;
	if(::Save(f,YLen)==false)	return false;
	if(::Save(f,RegPackFileName	)==false)	return false;
	if(::Save(f,MinMatchRate	)==false)	return false;
	if(AdaptedLayer.Save(f)==false)			return false;

	return true;
}
bool	DustReducerAI::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,XLen)==false)	return false;
	if(::Load(f,YLen)==false)	return false;
	if(::Load(f,RegPackFileName)==false)	return false;
	if(::Load(f,MinMatchRate	)==false)	return false;
	if(AdaptedLayer.Load(f)==false)			return false;

	QFile	File(RegPackFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		RegLib.Load(&File);
	}
	ShouldAllocate=true;
	return true;
}
bool	DustReducerAI::SaveLib(void)
{
	QFile	File(RegPackFileName);
	if(File.open(QIODevice::WriteOnly)==true){
		return RegLib.Save(&File);
	}
	return false;
}

bool	DustReducerAI::ShowSettingDialogFunc(void)
{
	SettingParamDialog	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		ShouldAllocate=true;
		return true;
	}
	return false;
}

struct	DustRegListPointerMapDim
{
	int		DustRegListID;
	double	Result;
};

bool	DustReducerAI::MakeDataForShow(ResultInItemRoot *Res ,QByteArray &RetData)
{
	AlgorithmItemRoot	*Item=Res->GetAlgorithmItem();
	if(Item!=NULL){
		int X, Y;
		if(Res->GetPosList().GetCount()!=0){
			for(ResultPosList *r=Res->GetPosList().GetFirst();r!=NULL;){
				ResultPosList *NextR=r->GetNext();
			
				r->GetPosInTarget(Res,X, Y);
				break;
			}
		}
		else{
			int	cx,cy;
			Res->GetCenter(cx,cy);
			X=cx+Res->GetAlignedX();
			Y=cy+Res->GetAlignedY();
		}
		Page=Item->GetPage();
		MakePattern(Item->GetPhaseCode(),Page,X,Y);

		RegLib.Calc(CurrentPattern,GetLayerNumb(Page),XLen,YLen,AdaptedLayer,_Judge_None);

		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		int	LayerNumb=GetLayerNumb(Page);
		::Save(&Buff,LayerNumb);
		int	Len=XLen*YLen;
		for(int layer=0;layer<LayerNumb;layer++){
			Buff.write((const char *)CurrentPattern[layer],Len);
		}
		int	N=RegLib.GetCount();
		::Save(&Buff,N);
		for(DustRegListPointer *r=RegLib.DustRegListPointerContainer.GetFirst();r!=NULL;r=r->GetNext()){
			struct	DustRegListPointerMapDim	D;
			D.DustRegListID	=r->Point->ID;
			D.Result		=r->Result;
			Buff.write((const char *)&D,sizeof(D));
		}
		RetData	=Buff.buffer();

		return true;
	}
	return false;
}

bool	DustReducerAI::ShowResultDialogFunc(QByteArray &Data)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	int	LayerNumb;
	if(::Load(&Buff,LayerNumb)==false)
		return false;
	int	Len=XLen*YLen;
	int	MaxLayerNumb=GetLayersBase()->GetMaxLayerNumb();
	for(int layer=0;layer<LayerNumb && layer<MaxLayerNumb;layer++){
		if(Buff.read((char *)CurrentPattern[layer],Len)!=Len)
			return false;
	}
	int	N;
	if(::Load(&Buff,N)==false)
		return false;
	RegLib.DustRegListPointerContainer.RemoveAll();
	for(int i=0;i<N;i++){
		struct	DustRegListPointerMapDim	D;
		if(Buff.read((char *)&D,sizeof(D))!=sizeof(D))
			return false;
		DustRegList	*r=RegLib.FindByID(D.DustRegListID);
		if(r==NULL)
			return false;
		DustRegListPointer	*rp=new DustRegListPointer(r);
		rp->Result	=D.Result;
		RegLib.DustRegListPointerContainer.AppendList(rp);
	}

	ShowResultDialog	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		SaveLib();
		return true;
	}
	return false;
}

void	DustReducerAI::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowResultDialog	*CmdShowResultDialogVar=dynamic_cast<CmdShowResultDialog *>(packet);
	if(CmdShowResultDialogVar!=NULL){
		ShowResultDialog	D(GetLayersBase(),this);
		D.exec();
		return;
	}
}

void	DustReducerAI::AddToLib(const QString &Comment ,JudgeDust OkNg)
{
	DustRegList	*a=new DustRegList();
	a->ID=RegLib.GetMaxID()+1;
	a->Set(CurrentPattern,GetLayerNumb(Page),XLen,YLen,Comment,OkNg);
	RegLib.AppendList(a);
}

void	DustReducerAI::Calc(void)
{
	RegLib.Calc(CurrentPattern,GetLayerNumb(Page),XLen,YLen,AdaptedLayer,_Judge_None);
}

ExeResult	DustReducerAI::Execute(ResultInItemRoot *Res)
{
	if(Res->IsOk()==false){
		AlgorithmItemRoot	*Item=Res->GetAlgorithmItem();
		if(Item!=NULL && Res->GetPosList().GetCount()!=0){
			for(ResultPosList *r=Res->GetPosList().GetFirst();r!=NULL;){
				ResultPosList *NextR=r->GetNext();
				int X, Y;
				r->GetPosInTarget(Res,X, Y);
				int	Page=Item->GetPage();
				MakePattern(Item->GetPhaseCode(),Page,X,Y);

				DustRegListPointer	*p=RegLib.Calc(CurrentPattern,GetLayerNumb(Page),XLen,YLen,AdaptedLayer,_Judge_OK);
				if(p!=NULL){
					if(p->Result>=MinMatchRate){
						Res->GetPosList().RemoveList(r);
						delete	r;
					}
				}
				r=NextR;
			}
			if(Res->GetPosList().GetCount()==0){
				Res->SetError(1);	//OK
			}
		}
	}
	else{
		AlgorithmItemRoot	*Item=Res->GetAlgorithmItem();
		if(Item!=NULL){
			int	cx,cy;
			Res->GetCenter(cx,cy);
			int	X=cx+Res->GetAlignedX();
			int	Y=cy+Res->GetAlignedY();

			int	Page=Item->GetPage();
			MakePattern(Item->GetPhaseCode(),Page,X,Y);

			DustRegListPointer	*p=RegLib.Calc(CurrentPattern,GetLayerNumb(Page),XLen,YLen,AdaptedLayer,_Judge_NG);
			if(p!=NULL){
				if(p->Result>=MinMatchRate){
					Res->SetError(2);
				}
			}
		}
	}

	return _ER_true;
}
