#include "XNamingPacket.h"
#include "XGeneralFunc.h"
#include "XNaming.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//================================================================================
SlaveCommReqOverlappedIndex::SlaveCommReqOverlappedIndex(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
}

bool	SlaveCommReqOverlappedIndex::Load(QIODevice *f)
{
	if(GlobalArea.Load(f)==false)
		return false;
	return true;
}
bool	SlaveCommReqOverlappedIndex::Save(QIODevice *f)
{
	if(GlobalArea.Save(f)==false)
		return false;
	return true;
}

void	SlaveCommReqOverlappedIndex::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SlaveCommAckOverlappedIndex	*S
	=(SlaveCommAckOverlappedIndex *)((GetSendBackPacket()==NULL)?new SlaveCommAckOverlappedIndex(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);

	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Pg=BBase->GetPageData(localPage);
		if(Pg!=NULL){
			FlexArea	A=GlobalArea;
			XYData		*XY=Pg->GetDataInPage()->GetOutlineOffset();
			A.MoveToClip(-XY->x,-XY->y,0,0,P->GetDotPerLine(),P->GetMaxLines());
			if(A.IsNull()==false){
				CmdFindOverlappedItem	RCmd(GetLayersBase());
				RCmd.Area=&A;
				Pg->TransmitDirectly(&RCmd);
				if(RCmd.Item!=NULL){
					S->Row=RCmd.Item->Row;
					S->Column=RCmd.Item->Column;
					S->Found=true;
				}
				else{
					S->Found=false;
				}
			}
		}
	}
	S->Send(this,GetGlobalPageFrom(),0);
	CloseSendBack(S);
}

SlaveCommAckOverlappedIndex::SlaveCommAckOverlappedIndex(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:DirectCommPacketBase(base,globalPage,EmitterRoot,EmitterName ,typeid(this).name())
{
	Found=false;
}

bool	SlaveCommAckOverlappedIndex::Load(QIODevice *f)
{
	if(::Load(f,Row)==false)
		return false;
	if(::Load(f,Column)==false)
		return false;
	if(::Load(f,Found)==false)
		return false;
	return true;
}
bool	SlaveCommAckOverlappedIndex::Save(QIODevice *f)
{
	if(::Save(f,Row)==false)
		return false;
	if(::Save(f,Column)==false)
		return false;
	if(::Save(f,Found)==false)
		return false;
	return true;
}