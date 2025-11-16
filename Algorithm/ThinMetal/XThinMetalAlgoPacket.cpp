#include "XThinMetalAlgoPacket.h"
#include "XGeneralFunc.h"
#include "XThinMetal.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

LibraryEfectivity::LibraryEfectivity(void)
{
	LibID	=0;
	IncludedInMask	=false;
}

bool	LibraryEfectivity::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,IncludedInMask)==false)
		return false;
	return true;
}

bool	LibraryEfectivity::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,IncludedInMask)==false)
		return false;
	return true;
}


bool	LibraryEfectivityContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}
bool	LibraryEfectivityContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		LibraryEfectivity	*a=new LibraryEfectivity();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
bool	LibraryEfectivityContainer::IsIncluded(int LibID)
{
	for(LibraryEfectivity *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibID==LibID){
			return a->IncludedInMask;
		}
	}
	return false;
}

//================================================================================
SlaveCommReqLibraryInMaskOfThinMetal::SlaveCommReqLibraryInMaskOfThinMetal(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqLibraryInMaskOfThinMetal::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqLibraryInMaskOfThinMetal::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqLibraryInMaskOfThinMetal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckLibraryInMaskOfThinMetal	*S
	=(SlaveCommAckLibraryInMaskOfThinMetal *)((GetSendBackPacket()==NULL)?new SlaveCommAckLibraryInMaskOfThinMetal(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		for(IntClass *a=UsedLibraries.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryLevelContainer	SrcLib(BBase);
			SrcLib.SetLibID(a->GetValue());
			AlgorithmLibrary	*Lib=SrcLib.GetLibrary();
			S->UsedLibraries.AppendList(new LibraryEfectivity(a->GetValue(),Pg->IncludeLibInReflection(_Reflection_Mask,Lib)));
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckLibraryInMaskOfThinMetal::SlaveCommAckLibraryInMaskOfThinMetal(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommAckLibraryInMaskOfThinMetal::Load(QIODevice *f)
{
	if(UsedLibraries.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommAckLibraryInMaskOfThinMetal::Save(QIODevice *f)
{
	if(UsedLibraries.Save(f)==false)
		return false;
	return true;
}

static	int	TestDbg=1;
void	SlaveCommAckLibraryInMaskOfThinMetal::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	TestDbg++;
}
