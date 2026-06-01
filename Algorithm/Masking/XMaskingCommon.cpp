#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"
#include "XMasking.h"

bool	MaskingListForPacket::Save(QIODevice* f)
{
	if (f->write((const char*)&Data, sizeof(Data)) != sizeof(Data))
		return false;
	if (LimitedLib.Save(f) == false)
		return false;
	return true;
}
bool	MaskingListForPacket::Load(QIODevice* f)
{
	if (f->read((char*)&Data, sizeof(Data)) != sizeof(Data))
		return false;
	if (LimitedLib.Load(f) == false)
		return false;
	return true;
}
MaskingListForPacket& MaskingListForPacket::operator=(MaskingListForPacket& src)
{
	Data = src.Data;
	LimitedLib = src.LimitedLib;
	return *this;
}


bool	MaskingListForPacketPack::Save(QIODevice* f)
{
	int32	N = GetNumber();
	if (::Save(f, N) == false)
		return false;
	for (MaskingListForPacket* c = GetFirst(); c != NULL; c = c->GetNext()) {
		if (c->Save(f) == false)
			return false;
	}
	return true;
}
bool	MaskingListForPacketPack::Load(QIODevice* f)
{
	int32	N;
	if (::Load(f, N) == false)
		return false;
	RemoveAll();
	for (int i = 0; i < N; i++) {
		MaskingListForPacket* c = new MaskingListForPacket();
		if (c->Load(f) == false)
			return false;
		AppendList(c);
	}
	return true;
}

MaskingListForPacketPack& MaskingListForPacketPack::operator=(MaskingListForPacketPack& src)
{
	RemoveAll();
	operator+=(src);
	return *this;
}
MaskingListForPacketPack& MaskingListForPacketPack::operator+=(MaskingListForPacketPack& src)
{
	for (MaskingListForPacket* c = src.GetFirst(); c != NULL; c = c->GetNext()) {
		MaskingListForPacket* d = new MaskingListForPacket();
		*d = *c;
		AppendList(d);
	}
	return *this;
}
//=============================================================================
MaskingBindedList::BindedInPage::BindedInLayer::BindedInLayer(const MaskingBindedList::BindedInPage::BindedInLayer &src)
	:Parent(src.Parent)
{
	Layer	=src.Layer;
	ItemIDs	=src.ItemIDs;
}

bool	MaskingBindedList::BindedInPage::BindedInLayer::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(ItemIDs.Save(f)==false)
		return false;
	return true;
}
bool	MaskingBindedList::BindedInPage::BindedInLayer::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(ItemIDs.Load(f)==false)
		return false;
	return true;
}
MaskingBindedList::BindedInPage::BindedInLayer &MaskingBindedList::BindedInPage::BindedInLayer::operator=(const MaskingBindedList::BindedInPage::BindedInLayer &src)
{
	Layer	=src.Layer;
	ItemIDs	=src.ItemIDs;
	return *this;
}

void	MaskingBindedList::BindedInPage::BindedInLayerContainer::Merge(BindedInLayerContainer &Src)
{
	for(BindedInLayer *s=Src.GetFirst();s!=NULL;s=s->GetNext()){
		BindedInLayer *d=FindByLayer(s->Layer);
		if(d!=NULL){
			d->ItemIDs.Merge(s->ItemIDs);
		}
		else{
			BindedInLayer	*m=new BindedInLayer(Parent);
			*m=*s;
			AppendList(m);
		}
	}
}
MaskingBindedList::BindedInPage::BindedInLayerContainer &MaskingBindedList::BindedInPage::BindedInLayerContainer::operator=(const MaskingBindedList::BindedInPage::BindedInLayerContainer &src)
{
	RemoveAll();
	for(BindedInLayer *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BindedInLayer	*m=new BindedInLayer(Parent);
		*m=*s;
		AppendList(m);
	}
	return *this;
}

MaskingBindedList::BindedInPage::BindedInLayer	*MaskingBindedList::BindedInPage::BindedInLayerContainer::FindByLayer(int layer)
{
	for(BindedInLayer *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(s->Layer==layer){
			return s;
		}
	}
	return NULL;
}

MaskingBindedList::BindedInPage::BindedInPage(const MaskingBindedList::BindedInPage &src)
	:BindedInLayerContainerInst(this),Parent(src.Parent)
{
	Page=src.Page;
	BindedInLayerContainerInst=src.BindedInLayerContainerInst;
}
bool	MaskingBindedList::BindedInPage::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(BindedInLayerContainerInst.Save(f)==false)
		return false;
	return true;
}

bool	MaskingBindedList::BindedInPage::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(BindedInLayerContainerInst.Load(f)==false)
		return false;
	return true;
}

MaskingBindedList::BindedInPage &MaskingBindedList::BindedInPage::operator=(const MaskingBindedList::BindedInPage &src)
{
	Page=src.Page;
	BindedInLayerContainerInst=src.BindedInLayerContainerInst;
	return *this;
}

void	MaskingBindedList::BindedInPageContainer::Merge(BindedInPageContainer &Src)
{
	for(BindedInPage *s=Src.GetFirst();s!=NULL;s=s->GetNext()){
		bool	Found=false;
		for(BindedInPage *d=GetFirst();d!=NULL;d=d->GetNext()){
			if(s->Page==d->Page){
				d->BindedInLayerContainerInst.Merge(s->BindedInLayerContainerInst);
				Found=true;
				break;
			}
		}
		if(Found==false){
			BindedInPage	*m=new BindedInPage(Parent);
			*m=*s;
			AppendList(m);
		}
	}
}
MaskingBindedList::BindedInPageContainer &MaskingBindedList::BindedInPageContainer::operator=(const MaskingBindedList::BindedInPageContainer &src)
{
	RemoveAll();
	for(BindedInPage *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		BindedInPage	*m=new BindedInPage(Parent);
		*m=*s;
		AppendList(m);
	}
	return *this;
}

bool	MaskingBindedList::Save(QIODevice *f)
{
	if(BindedInPageContainerInst.Save(f)==false)
		return false;
	if(LimitedLib.Save(f)==false)
		return false;
	return true;
}

bool	MaskingBindedList::Load(QIODevice *f)
{
	if(BindedInPageContainerInst.Load(f)==false)
		return false;
	if(LimitedLib.Load(f)==false)
		return false;
	return true;
}
MaskingBindedList &MaskingBindedList::operator=(const MaskingBindedList &src)
{
	BindedInPageContainerInst=src.BindedInPageContainerInst;
	LimitedLib=src.LimitedLib;
	return *this;
}