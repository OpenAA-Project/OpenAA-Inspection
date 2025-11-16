#include "XRWAlgorithmInterface.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "XErrorCode.h"
#include "XGUIFormBase.h"
#include "XFileRegistry.h"
#include "XMapBuffer.h"
#include "XDataComponent.h"
#include "XRWAlgorithmBase.h"


//=======================================================================================================================================

RWLogicDLL::RWLogicDLL(RegulusWorld *base)
:Base(base)
{
	DLLPointer			=NULL;
	Ver					=0;
	InstBase			=NULL;

	ShowAndSetItemsForm			=NULL;
	ChangeItemsAttrForm			=NULL;
}

RWLogicDLL::~RWLogicDLL(void)
{
	if(ShowAndSetItemsForm!=NULL){
		delete	ShowAndSetItemsForm;
		ShowAndSetItemsForm=NULL;
	}
	if(ChangeItemsAttrForm!=NULL){
		delete	ChangeItemsAttrForm;
		ChangeItemsAttrForm=NULL;
	}

	if(InstBase!=NULL)
		DLLPointer->Close(InstBase);
	InstBase=NULL;
}

void	RWLogicDLL::Set(RWAlgorithmDLLList *s)
{
	DLLPointer=s;
}

RWLogicDLL	&RWLogicDLL::operator=(RWLogicDLL &src)
{
	DLLPointer=src.DLLPointer;
	InitialAlloc(Base);

	RW3DBaseRoot	*Dest=GetInstance();
	RW3DBaseRoot	*Src =src.GetInstance();
	if(Dest!=NULL && Src!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Src->SaveParam(&Buff);
		Buff.seek(0);
		Dest->LoadParam(&Buff);
	}
	return *this;
}

bool	RWLogicDLL::IsRWAlgorithm(void)
{
	int	d=DLLPointer->GetDLLType();
	if((d&DLLModeMask)==DLLRWAlgorithmMode){
		return(true);
	}
	return(false);
}

bool	RWLogicDLL::SetLanguageCode(int LanguageCode)
{
	if(DLLPointer->SetLanguage(LanguageCode)==true){
		return true;
	}
	return false;
}

QString		RWLogicDLL::GetDefaultFileName(void)
{
	if(InstBase!=NULL){
		return InstBase->GetDefaultFileName();
	}
	return QString("XXX.dat");
}
void	RWLogicDLL::InitialName(void)
{
	DLLPointer->GetName();
}
bool	RWLogicDLL::InitialAlloc(RegulusWorld *Base)
{
	DLLPointer->CheckCopyright(Copyright);
	DLLType=DLLPointer->GetDLLType();

	Ver=DLLPointer->GetVersion();

	InitialName();
	DLLPointer->GetOrganization(Organization);

	int	LanguageCode=0;
	if(Base!=NULL && Base->GetLayersBase()->GetFRegistry()!=NULL){
		LanguageCode=Base->GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
	}
	SetLanguageCode(LanguageCode);
	InstBase=AllocOnly(Base);
	
	QString	ParamFileName=GetDefaultFileName();
	if(ParamFileName.isEmpty()==false){
		QFile	PFile(ParamFileName);
		if(PFile.open(QIODevice::ReadOnly)==true){
			if(InstBase!=NULL){
				InstBase->LoadParam(&PFile);
			}
		}
	}
	if(GetInstance()!=NULL){
		GetInstance()->LoadedVersion=Ver;
	}

	return(true);
}
void	RWLogicDLL::AssociateComponent	(ComponentListContainer &List)
{
	if(DLLPointer!=NULL){
		DLLPointer->AssociateComponent(List);
	}
}

RW3DBaseRoot	*RWLogicDLL::AllocOnly(RegulusWorld *Base)
{
	RW3DBaseRoot	*p=DLLPointer->InitialAlloc(Base);
	if(p!=NULL){
		p->LogicDLLPoint=this;
		return p;
	}

	return NULL;
}
void	RWLogicDLL::InitialAfterParamLoaded(void)
{
	if(InstBase!=NULL){
		InstBase->InitialAfterParamLoaded();
	}
}
void	RWLogicDLL::ReallocRW3DBaseRoot(RegulusWorld *Base)
{
	if(InstBase!=NULL){
		InstBase->Initial(Base);
		QFile	FAlgprithm(Base->GetLayersBase()->GetUserPath()
						 +GetSeparator()
						 +InstBase->GetSavedFileName());
		if(FAlgprithm.open(QIODevice::ReadOnly)==true){
			InstBase->LoadParam(&FAlgprithm);
		}	
		InstBase->InitialAfterParamLoaded();
		InstBase->LogicDLLPoint=this;
	}
}

QString		RWLogicDLL::GetExplain(void)
{	
	if(DLLPointer->GetExplain()==NULL){
		return /**/"";
	}
	return DLLPointer->GetExplain();
}


QString		RWLogicDLL::GetFileName(void)	const	{	return DLLPointer->GetFileName();		}
QString		RWLogicDLL::GetDLLRoot(void)	const	{	return DLLPointer->GetDLLRoot();		}
QString		RWLogicDLL::GetDLLName(void)	const	{	return DLLPointer->GetDLLName();		}
bool		RWLogicDLL::CheckDLL(const QString &root, const QString &name)
{	
	return DLLPointer->CheckDLL(root, name);
}

int		RWLogicDLL::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	return DLLPointer->RegistMacroFunction(Functions,MaxBuffer);
}

RWLogicDLLBaseClass::RWLogicDLLBaseClass(RegulusWorld *base)
	:Base(base)
{
}
RWLogicDLLBaseClass::~RWLogicDLLBaseClass(void)
{
	//ResultData.Release();
	RWLogicDLL *c=NULL;
	while((c=GetFirst())!=NULL){
		RemoveList(c);
		delete	c;
	}
}

RWLogicDLLBaseClass	&RWLogicDLLBaseClass::operator=(const RWLogicDLLBaseClass &src)
{
	RemoveAll();
	for(RWLogicDLL *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		RWLogicDLL *M=new RWLogicDLL(Base);
		*M= *L;
		AppendList(M);
	}
	return *this;
}

int	RWLogicDLLBaseClass::AddDLLs(const RWAlgorithmDLLContainer &AlgoCont ,RegulusWorld *Base)
{
	int	N=0;

	RemoveAll();
	for(RWAlgorithmDLLList *L=AlgoCont.GetFirst();L!=NULL;L=L->GetNext()){
		RWLogicDLL	*DLLInst=new RWLogicDLL(Base);
		DLLInst->Set(L);
		DLLInst->InitialName();

		printf("InitialAlloc\n");
		DLLInst->InitialAlloc(Base);
		AppendList(DLLInst);
		N++;
	}
	return N;
}
bool	RWLogicDLLBaseClass::LoadOneDLL(RegulusWorld *Base ,const QString &DLLFileNameWithPath)
{
	for(RWAlgorithmDLLList *L=Base->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetFileName()==DLLFileNameWithPath){
			RWLogicDLL	*DLLInst=new RWLogicDLL(Base);
			DLLInst->Set(L);
			DLLInst->InitialName();

			printf("InitialAlloc\n");
			DLLInst->InitialAlloc(Base);
			AppendList(DLLInst);
			return true;
		}
	}
	return false;
}

RWLogicDLL	*RWLogicDLLBaseClass::Search(int dynamicID)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDynamicID()==dynamicID){
			return(L);
		}
	}
	return(NULL);
}
void    RWLogicDLLBaseClass::InitialAfterParamLoaded(void)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->InitialAfterParamLoaded();
	}
}
RWLogicDLL	*RWLogicDLLBaseClass::Search(const QString &_DLLRoot ,const QString &_DLLName)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckDLL(_DLLRoot ,_DLLName)==true){
			return(L);
		}
	}
	return(NULL);
}
int		RWLogicDLLBaseClass::GetDLLCounts(void)
{
	return GetNumber();
}

bool	RWLogicDLLBaseClass::Save(QIODevice *f)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RWLogicDLLBaseClass::Load(QIODevice *f)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetInstance()->Load(f)==false){
			return false;
		}
	}
	return true;
}


void	RWLogicDLLBaseClass::AssociateComponent	 (ComponentListContainer &List)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ComponentListContainer TmpList;
		L->AssociateComponent(TmpList);
		for(ComponentList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
			ComponentList	*Boss;
			for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
				if(*Boss==*L){
					break;
				}
			}
			if(Boss==NULL){
				ComponentList	*d=new ComponentList(*L);
				List.AppendList(d);
			}
		}
	}
}

bool	RWLogicDLLBaseClass::SetLanguageCode(int LanguageCode)
{
	for(RWLogicDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->SetLanguageCode(LanguageCode);
	}
	return true;
}

bool	RWLogicDLLBaseClass::CheckInstalledAlgorithm(RootNameListContainer &FromGUI,RootNameListContainer &LackOfAlgorithm)
{
	LackOfAlgorithm.RemoveAll();
	for(RootNameList *a=FromGUI.GetFirst();a!=NULL;a=a->GetNext()){
		if(Search(a->DLLRoot ,a->DLLName)==NULL){
			RootNameList	*b=new RootNameList();
			*b= *a;
			LackOfAlgorithm.AppendList(b);
		}
	}
	if(LackOfAlgorithm.GetNumber()!=0){
		return false;
	}
	return true;
}

bool	RWLogicDLLBaseClass::CheckDuplicatedAlgorithm(QStringList &Error)
{
	bool	Dup=false;
	for(RWLogicDLL *a=GetFirst();a!=NULL;a=a->GetNext()){
		for(RWLogicDLL *b=a->GetNext();b!=NULL;b=b->GetNext()){
			if(a->GetDLLRoot()==b->GetDLLRoot() && a->GetDLLName()==b->GetDLLName()){
				QString	Msg=QString("Installed duplicated algorithm (")
							+a->GetDLLRoot()
							+QString(",")
							+a->GetDLLName()
							+QString(")");
				Error.append(Msg);
				Dup=true;
			}
		}
	}
	return Dup;
}

