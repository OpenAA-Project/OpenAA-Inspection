#include "XGerberAperture.h"
#include "XGerberFastComposite.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexArea.h"


//========================================================================

bool	GerberCompositeDefLayerItem::Save(QIODevice *f)
{
	int32	Ope=Operation;
	if(::Save(f,Ope)==false)
		return false;
	if(::Save(f,LayerTypeLibID)==false)
		return false;
	if(::Save(f,DotSpr)==false)
		return false;
	if(::Save(f,NegMode)==false)
		return false;
	return true;
}
bool	GerberCompositeDefLayerItem::Load(QIODevice *f)
{
	int32	Ope;
	if(::Load(f,Ope)==false)
		return false;
	Operation=(_Operation)Ope;
	if(::Load(f,LayerTypeLibID)==false)
		return false;
	if(::Load(f,DotSpr)==false)
		return false;
	if(::Load(f,NegMode)==false)
		return false;
	return true;
}
GerberCompositeDefLayerItem	&GerberCompositeDefLayerItem::operator=(GerberCompositeDefLayerItem &src)
{
	QBuffer	MBuff;
	MBuff.open(QIODevice::ReadWrite);
	src.Save(&MBuff);
	MBuff.seek(0);
	Load(&MBuff);
	return *this;
}

GerberCompositeDefLayerItemContainer	&GerberCompositeDefLayerItemContainer::operator=(GerberCompositeDefLayerItemContainer &src)
{
	RemoveAll();
	for(GerberCompositeDefLayerItem *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		GerberCompositeDefLayerItem *d=new GerberCompositeDefLayerItem();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	GerberCompositeDefLayer::Save(QIODevice *f)
{
	int	Ver=2;
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,CompositeID)==false)
		return false;
	int32	N=Combination.GetNumber();

	N |= Ver<<16;
	if(::Save(f,N)==false)
		return false;
	for(GerberCompositeDefLayerItem *c=Combination.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,NegMode)==false)
		return false;
	if(::Save(f,LibFolderID)==false)
		return false;
	if(::Save(f,SourceCompositeID)==false)
		return false;
	return true;
}
bool	GerberCompositeDefLayer::Load(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,CompositeID)==false)
		return false;
	int32	N;
	if(::Load(f,N)==false)
		return false;

	Ver=N>>16;
	N &= 0xFFFF;

	Combination.RemoveAll();
	for(int i=0;i<N;i++){
		GerberCompositeDefLayerItem *c=new GerberCompositeDefLayerItem();
		if(c->Load(f)==false)
			return false;
		Combination.AppendList(c);
	}
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,NegMode)==false)
		return false;
	if(Ver>=1){
		if(::Load(f,LibFolderID)==false)
			return false;
	}
	if(Ver>=2){
		if(::Load(f,SourceCompositeID)==false)
			return false;
	}
	return true;
}
GerberCompositeDefLayer	&GerberCompositeDefLayer::operator=(GerberCompositeDefLayer &src)
{
	QBuffer	MBuff;
	MBuff.open(QIODevice::ReadWrite);
	src.Save(&MBuff);
	MBuff.seek(0);
	Load(&MBuff);
	return *this;
}


bool	GerberCompositeDefPack::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(GerberCompositeDefLayer *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
bool	GerberCompositeDefPack::Load(QIODevice *f)
{
	RemoveAll();
	return Append(f);
}
bool	GerberCompositeDefPack::Append(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		GerberCompositeDefLayer *c=new GerberCompositeDefLayer();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}
GerberCompositeDefPack	&GerberCompositeDefPack::operator=(GerberCompositeDefPack &src)
{
	QBuffer	MBuff;
	MBuff.open(QIODevice::ReadWrite);
	src.Save(&MBuff);
	MBuff.seek(0);
	Load(&MBuff);
	return *this;
}
GerberCompositeDefLayer	*GerberCompositeDefPack::Search(int compositeDefID)
{
	for(GerberCompositeDefLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CompositeID==compositeDefID)
			return L;
	}
	return NULL;
}

GerberCompositeLayer	&GerberCompositeLayer::operator=(GerberCompositeLayer &src)
{
	CompositeID		=src.CompositeID;
	LayerColor		=src.LayerColor;
	Remark			=src.Remark;
	Visible			=src.Visible;
	Operational		=src.Operational;
	return *this;
}

bool	GerberCompositeLayer::Save(QIODevice *f)
{
	if(::Save(f,CompositeID)==false)
		return false;
	if(::Save(f,LayerColor)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;

	return true;
}
bool	GerberCompositeLayer::Load(QIODevice *f)
{
	if(::Load(f,CompositeID)==false)
		return false;
	if(::Load(f,LayerColor)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;

	return true;
}

//==========================================================================
GerberCompositeLayerContainer::GerberCompositeLayerContainer(void)
{
}
GerberCompositeLayerContainer	&GerberCompositeLayerContainer::operator=(GerberCompositeLayerContainer &src)
{
	RemoveAll();
	for(GerberCompositeLayer *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		GerberCompositeLayer *a=new GerberCompositeLayer(-1);
		*a=*L;
		AppendList(a);
	}
	return *this;
}
bool	GerberCompositeLayerContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(GerberCompositeLayer *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	GerberCompositeLayerContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		GerberCompositeLayer *a=new GerberCompositeLayer(i);
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

bool	GerberCompositeDefPack::CopyCompositeIntoFolder(int NewLibFolderID , int OriginalLibFolderID)
{
	for(GerberCompositeDefLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->LibFolderID==OriginalLibFolderID){
			GerberCompositeDefLayer	*L=new GerberCompositeDefLayer();
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			a->Save(&Buff);
			Buff.seek(0);
			L->Load(&Buff);
			L->LibFolderID=NewLibFolderID;
			L->CompositeID=GetMaxID()+1;
			L->SourceCompositeID=a->CompositeID;
			AppendList(L);
		}
	}
	return true;
}

int32	GerberCompositeDefPack::GetMaxID(void)
{
	int	MaxID=0;
	for(GerberCompositeDefLayer *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(MaxID<a->CompositeID){
			MaxID=a->CompositeID;
		}
	}
	return MaxID;
}
void	GerberCompositeDefPack::EnumChildren(int CompositeID ,IntList &RetID)
{
	for(GerberCompositeDefLayer *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->SourceCompositeID==CompositeID){
			RetID.Add(d->CompositeID);
			EnumChildren(d->CompositeID ,RetID);
		}
	}
}
