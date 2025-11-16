#include "XCacheTargetImage.h"

CacheTargetImageInLayer::CacheTargetImageInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
}
CacheTargetImageInLayer::~CacheTargetImageInLayer(void)
{
}

void	CacheTargetImageInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	PacketSetToTarget	*PacketSetToTargetVar=dynamic_cast<PacketSetToTarget *>(packet);
	if(PacketSetToTargetVar!=NULL){
		DataInLayer		*L=GetDataInLayer();
		ImageBuffer	*Img=IBuffer.GetItem(PacketSetToTargetVar->Number);
		if(Img==NULL)
			return;
		L->SetToTargetBuff(*Img);
		return;
	}
	PacketGetImageBuffer	*PacketGetImageBufferVar=dynamic_cast<PacketGetImageBuffer *>(packet);
	if(PacketGetImageBufferVar!=NULL){
		PacketGetImageBufferVar->Img=IBuffer.GetItem(PacketGetImageBufferVar->Number);
		return;
	}
}

ExeResult	CacheTargetImageInLayer::ExecuteInitialAfterEdit(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	CacheTargetImageBase	*ABase=dynamic_cast<CacheTargetImageBase *>(GetParentBase());
	for(ImageBufferList *p=IBuffer.GetFirst();p!=NULL;){
		ImageBufferList *NextP=p->GetNext();
		if(p->GetWidth()!=GetDotPerLine() || p->GetHeight()!=GetMaxLines()){
			IBuffer.RemoveList(p);
			delete	p;
		}
		p=NextP;
	}
	while(IBuffer.GetCount()<ABase->BufferCount){
		ImageBufferList	*p=new ImageBufferList(ImageBufferTarget,GetDotPerLine(),GetMaxLines());
		IBuffer.AppendList(p);
	}
	while(IBuffer.GetCount()>ABase->BufferCount){
		ImageBufferList	*p=IBuffer.GetLast();
		IBuffer.RemoveList(p);
		delete	p;
	}
	return _ER_true;
}
ExeResult	CacheTargetImageInLayer::ExecuteProcessing	(int ExeID ,ResultInLayerRoot *Res)
{
	ImageBufferList	*p=IBuffer.GetFirst();
	if(p!=NULL){
		*((ImageBuffer *)p)=GetTargetBuff();
		IBuffer.RemoveList(p);
		IBuffer.AppendList(p);
	}
	return _ER_true;
}

ImageBuffer	*CacheTargetImageInLayer::GetPoint(int n)
{
	ImageBufferList	*p=IBuffer.GetItem(n);
	if(p!=NULL){
		return p;
	}
	return NULL;
}

//=================================================================================================================

void	CacheTargetImageInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	PacketSetToTarget	*PacketSetToTargetVar=dynamic_cast<PacketSetToTarget *>(packet);
	if(PacketSetToTargetVar!=NULL){
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			GetLayerData(Layer)->TransmitDirectly(packet);
		}
		return;
	}
}

//=================================================================================================================
CacheTargetImageBase::CacheTargetImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	BufferCount	=5;

	SetParam(&BufferCount		, /**/"Setting" ,/**/"BufferCount"		,"Count of stored target images");
}


AlgorithmDrawAttr	*CacheTargetImageBase::CreateDrawAttr(void)
{
	return NULL;
}
