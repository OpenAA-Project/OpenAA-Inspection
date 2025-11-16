#include "XGerberAperture.h"
#include "XGerberFast.h"

//=================================================================================

AlgoGenerationalLine::AlgoGenerationalLine(int id)
{
	AlgoGenID		=id;
	BaseLayerID		=-1;

	AutoGenType	=_Gen_FromLayer;

	UpperLayers	=new AlgoGenerationalContainer();
}

AlgoGenerationalLine::~AlgoGenerationalLine(void)
{
	delete	UpperLayers;
	UpperLayers=NULL;
}

bool	AlgoGenerationalLine::Save(QIODevice *f)
{
	if(::Save(f,AlgoGenID)==false)
		return false;
	if(::Save(f,BaseLayerID)==false)
		return false;
	if(UpperLayers->Save(f)==false)
		return false;

	BYTE	d=(BYTE)AutoGenType;
	if(::Save(f,d)==false)
		return false;
	if(Libraries.Save(f)==false)
		return false;
	return true;
}
bool	AlgoGenerationalLine::Load(QIODevice *f)
{
	if(::Load(f,AlgoGenID)==false)
		return false;
	if(::Load(f,BaseLayerID)==false)
		return false;
	if(UpperLayers->Load(f)==false)
		return false;

	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	AutoGenType	=(GenType)d;
	if(Libraries.Load(f)==false)
		return false;
	return true;
}
AlgoGenerationalLine	&AlgoGenerationalLine::operator=(AlgoGenerationalLine &src)
{
	AlgoGenID		=src.AlgoGenID;
	BaseLayerID		=src.BaseLayerID;
	*UpperLayers	=*src.UpperLayers;
	AutoGenType		=src.AutoGenType;
	Libraries		=src.Libraries;
	return *this;
}

bool	AlgoGenerationalLine::IsLayer(AlgoGenerationalLine::GenType e)
{
	if(e==_GenFromComposite
	|| e==_GenFromCompositeShiftable
	|| e==_GenFromCompositeEnlarge
	|| e==_GenFromCompositeShrinked
	|| e==_GenFromCompositeUnstable
	|| e==_GenFromCompositeStable){
		return false;
	}
	return true;
}

AlgoGenerationalContainer::AlgoGenerationalContainer(void)
{
}

bool	AlgoGenerationalContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	AlgoGenerationalContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AlgoGenerationalLine	*a=new AlgoGenerationalLine(-1);
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

int		AlgoGenerationalContainer::GetMaxID(void)
{
	int	MaxID=0;
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->AlgoGenID>MaxID){
			MaxID=a->AlgoGenID;
		}
	}
	return MaxID;
}
void	AlgoGenerationalContainer::ClearLibrary(void)
{
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Libraries.RemoveAll();
	}
}

AlgoGenerationalContainer	&AlgoGenerationalContainer::operator=(AlgoGenerationalContainer &src)
{
	RemoveAll();
	for(AlgoGenerationalLine *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		AlgoGenerationalLine *d=new AlgoGenerationalLine(-1);
		*d=*a;
		AppendList(d);
	}
	return *this;
}
bool	AlgoGenerationalContainer::DoAllChildHaveLibrary(void)
{
	for(AlgoGenerationalLine *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Libraries.IsEmpty()==false){
			return true;
		}
	}
	return false;
}

void	AlgoGenerationalContainer::Merge(AlgoGenerationalContainer &t)
{
	for(AlgoGenerationalLine *ta=t.GetFirst();ta!=NULL;ta=ta->GetNext()){
		bool	MFound=false;
		for(AlgoGenerationalLine *tb=GetFirst();tb!=NULL;tb=tb->GetNext()){
			if(ta->AlgoGenID==tb->AlgoGenID && ta->BaseLayerID==tb->BaseLayerID){
				for(AlgoGenerationalLine *ka=ta->UpperLayers->GetFirst();ka!=NULL;ka=ka->GetNext()){
					bool	Found=false;
					for(AlgoGenerationalLine *kb=tb->UpperLayers->GetFirst();kb!=NULL;kb=kb->GetNext()){
						if(ka->AlgoGenID==kb->AlgoGenID && ka->BaseLayerID==kb->BaseLayerID){
							if(kb->Libraries.IsEmpty()==true){
								kb->Libraries=ka->Libraries;
							}
							Found=true;
						}
					}
					if(Found==false){
						AlgoGenerationalLine	*h=new AlgoGenerationalLine(ka->AlgoGenID);
						*h=*ka;
						tb->UpperLayers->AppendList(h);
					}
				}
				MFound=true;
			}
		}
		if(MFound==false){
			AlgoGenerationalLine	*d=new AlgoGenerationalLine(ta->AlgoGenID);
			*d=*ta;
			AppendList(d);
		}
	}
}
