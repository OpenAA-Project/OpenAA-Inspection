#include "XDXFOperation.h"


	
DXFLayer::DXFLayer(DXFLayerContainer *parent)
{
	LayerID=0;
}

DXFLayer &DXFLayer::operator=(const DXFLayer &src)
{
	LayerID		=src.LayerID;
	LayerName	=src.LayerName;
	LineType	=src.LineType;
	ColorCode	=src.ColorCode;
	return *this;
}

bool	DXFLayer::Save(QIODevice *f)
{
	if(::Save(f,LayerID)==false)
		return false;
	if(::Save(f,LayerName)==false)
		return false;
	if(::Save(f,(int)LineType)==false)
		return false;
	if(::Save(f,ColorCode)==false)
		return false;
	return true;
}
bool	DXFLayer::Load(QIODevice *f)
{
	if(::Load(f,LayerID)==false)
		return false;
	if(::Load(f,LayerName)==false)
		return false;
	int	iLineType;
	if(::Load(f,iLineType)==false)
		return false;
	LineType=(EnumDXFLineType)iLineType;
	if(::Load(f,ColorCode)==false)
		return false;
	return true;
}


int		DXFLayerContainer::GetMaxFileLayerID(void)
{
	int	MaxID=0;
	for(DXFLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxID<L->LayerID){
			MaxID=L->LayerID;
		}
	}
	return MaxID;
}

DXFLayer	*DXFLayerContainer::Find(int ID)
{
	for(DXFLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LayerID==ID){
			return L;
		}
	}
	return NULL;
}


DXFLayer	*DXFLayerContainer::FindLayer(const QString &name)
{
	for(DXFLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->LayerName==name){
			return L;
		}
	}
	return NULL;
}

void	DXFLayerContainer::Merge(DXFLayerContainer &src)
{
	for(DXFLayer *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(DXFLayer *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(s->LayerName==d->LayerName){
				Found=true;
				break;
			}
		}
		if(Found==false){
			DXFLayer	*b=new DXFLayer(this);
			*b=*s;
			AppendList(b);
		}
	}
}
