#include "XRemoteLightController.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XRemoteLightCommon.h"

extern	LightClassPack		*LightPack;

RemoteLightItem::RemoteLightItem(LayersBase *Base ,RemoteLightContainer *parent)
:ServiceForLayers(Base)
{	
	Parent	=parent;
	PortNumber=14330;	
	LightPointer=NULL;	

	connect(this,SIGNAL(SignalReceived(int)),this,SLOT(SlotReceived(int)),Qt::QueuedConnection);
}
RemoteLightItem::~RemoteLightItem(void)
{
}
RemoteLightItem	*RemoteLightItem::GetNextD(RemoteLightContainer &parent)
{
	return parent.GetNextItem(this);
}

QString	RemoteLightItem::GetDLLName(void)
{
	if(LightPointer!=NULL){
		return LightPointer->GetDLLName();
	}
	return QString("??")+RegName;
}

bool	RemoteLightItem::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,DLLFileName)==false)
		return false;
	if(::Save(f,RegName)==false)
		return false;
	if(::Save(f,IPAddress)==false)
		return false;
	if(::Save(f,PortNumber)==false)
		return false;
	if(::Save(f,InitialString)==false)
		return false;
	return true;
}

bool	RemoteLightItem::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,DLLFileName)==false)
		return false;
	if(::Load(f,RegName)==false)
		return false;
	if(::Load(f,IPAddress)==false)
		return false;
	if(::Load(f,PortNumber)==false)
		return false;
	if(::Load(f,InitialString)==false)
		return false;
	return true;
}


bool	RemoteLightItem::SaveLightSetting(QIODevice *f)
{
	if(LightPointer!=NULL){
		LightRawData.clear();
		QBuffer	Buff(&LightRawData);
		Buff.open(QIODevice::ReadWrite);
		bool	Ret=LightPointer->Save(&Buff);
		if(Ret==false)
			return false;
		if(::Save(f,LightRawData)==false)
			return false;
		return true;
	}
	return false;
}

bool	RemoteLightItem::ReflectLight(void)
{
	if(LightPointer!=NULL){
		QBuffer	Buff(&LightRawData);
		Buff.open(QIODevice::ReadWrite);		
		return LightPointer->Load(&Buff);
	}
	return false;
}

bool	RemoteLightItem::LoadLightSetting(QIODevice *f)
{
	LightRawData.clear();
	if(::Load(f,LightRawData)==false)
		return false;
	if(LightPointer!=NULL){
		return ReflectLight();
	}
	return true;
}
RemoteLightItem	&RemoteLightItem::operator=(RemoteLightItem &src)
{
	//LightPointer	=src.LightPointer;
	ID				=src.ID;
	DLLFileName		=src.DLLFileName;
	RegName			=src.RegName;
	IPAddress		=src.IPAddress;
	PortNumber		=src.PortNumber;
	InitialString	=src.InitialString;
	LightRawData	=src.LightRawData;
	return *this;
}

bool	RemoteLightItem::OpenDLL(QObject *parent)
{
	int32	ErrorCode;
	bool	OutputMode=false;
	bool	Ret=true;

	setParent(parent);
	if(LightPointer==NULL){
		for(LightAccessList *G=LightPack->GetFirst();G!=NULL;G=G->GetNext()){
			if(DLLFileName==G->GetFileName()){
				LightPointer=new LightAccessList(GetLayersBase());
				if(LightPointer->InitialStraightPath(DLLFileName,InitialString
													,ErrorCode ,OutputMode)==false){
					Ret=false;
				}
				else{
					setParent(parent);
					Set(parent,IPAddress,PortNumber);
					if(!connect(LightPointer->GetHandle(),SIGNAL(SignalReflectDataInDialog())		,this,SLOT(SlotReflectDataInDialog())		,Qt::QueuedConnection))
						Ret=false;
					if(!connect(LightPointer->GetHandle(),SIGNAL(SignalReflectOnOffInDialog(bool))	 ,this,SLOT(SlotReflectOnOffInDialog(bool))	,Qt::QueuedConnection))
						Ret=false;
				}
			}
		}
	}
	return Ret;
}

bool	RemoteLightItem::ShowSetting(QWidget *parent)
{
	if(LightPointer!=NULL){
		return LightPointer->ShowSetting(parent);
	}
	return false;
}

bool	RemoteLightItem::CloseDLL(void)
{
	if(LightPointer!=NULL){
		delete	LightPointer;
		LightPointer=NULL;
	}
	return true;
}

bool	RemoteLightItem::SetOnOff(bool OnMode)
{
	bool	Ret=true;

	if(LightPointer!=NULL){
		if(LightPointer->GetHandle()!=NULL){
			LightPointer->GetHandle()->ReflectOnOffInDialog(OnMode);
		}
	}
	return Ret;
}

bool	RemoteLightItem::SendCommand(BYTE *Data ,int32 DataLen)
{
	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	int	Cmd=CmdLightSendCommand;
	if(::Save(&Buff,Cmd)==false)
		return false;
	if(::Save(&Buff,DataLen)==false)
		return false;
	if(Buff.write((const char *)Data,DataLen)!=DataLen)
		return false;

	return TxData(&Buff);
}

void	RemoteLightItem::SlotReceived(int id)
{
	RecList	*R=UnpackTopRxBuff();
	if(R!=NULL){
		BYTE	*p=R->GetPointer();
		QBuffer ret;
		p=R->GetPointer(p ,ret);
		ret.open(QIODevice::ReadWrite);
		int	Cmd=0;
		::Load(&ret,Cmd);
		if(Cmd==CmdLightAckData){
			QByteArray	Data;
			if(::Load(&ret,Data)==false)
				goto	NextPoint;
			QBuffer		Buff(&Data);
			Buff.open(QIODevice::ReadOnly);
			LightPointer->Load(&Buff);
		}
NextPoint:;
		delete	R;
	}
}
void	RemoteLightItem::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		QBuffer		Buff;
		Buff.open(QIODevice::WriteOnly);
		int	Cmd=CmdLightSetData;
		if(::Save(&Buff,Cmd)==false)
			return;
		if(LightPointer->Save(&Buff)==false)
			return;
		TxData(&Buff);
	}
}

void	RemoteLightItem::SlotReflectOnOffInDialog(bool LightOn)
{
	QBuffer		Buff;
	Buff.open(QIODevice::WriteOnly);
	int	Cmd=CmdLightOnOff;
	if(::Save(&Buff,Cmd)==false)
		return;
	if(::Save(&Buff,LightOn)==false)
		return;
	TxData(&Buff);
}

//-------------------------------------------------------------------

RemoteLightContainer::RemoteLightContainer(LayersBase *Base)
:ServiceForLayers(Base)
{
	for(int i=0;i<LightDimCount;i++){
		Dim[i]=NULL;
	}
}
RemoteLightItem	*RemoteLightContainer::Create(void)
{	
	return new RemoteLightItem(GetLayersBase(),this);
}
int		RemoteLightContainer::GetMaxID(void)
{
	int	MaxID=0;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			if(MaxID<Dim[i]->ID){
				MaxID=Dim[i]->ID;
			}
		}
	}
	return MaxID;
}

RemoteLightContainer	&RemoteLightContainer::operator=(RemoteLightContainer &src)
{
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			delete	Dim[i];
		}
	}
	for(int i=0;i<LightDimCount;i++){
		if(src.Dim[i]!=NULL){
			Dim[i]=new RemoteLightItem(GetLayersBase(),this);
			*Dim[i]=*src.Dim[i];
		}
	}
	return *this;
}

bool	RemoteLightContainer::OpenDLL(QObject *parent)
{
	bool	Ret=true;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			if(Dim[i]->OpenDLL(parent)==false)
				Ret=false;
		}
	}
	return Ret;
}

bool	RemoteLightContainer::CloseDLL(void)
{
	bool	Ret=true;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			if(Dim[i]->CloseDLL()==false)
				Ret=false;
			delete	Dim[i];
			Dim[i]=NULL;
		}
	}
	return Ret;
}

bool	RemoteLightContainer::Save(QIODevice *f)
{
	int32	Ver=200;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,LightDimCount)==false)
		return false;

	for(int i=0;i<LightDimCount;i++){
		if(::Save(f,i)==false)
			return false;
		bool	Exist	=(Dim[i]==NULL)?false:true;
		if(::Save(f,Exist)==false)
			return false;
		if(Exist==true){
			QBuffer	mBuff;
			mBuff.open(QIODevice::WriteOnly);
			if(Dim[i]->Save(&mBuff)==false)
				return false;
			if(::Save(f,mBuff.buffer())==false){
				return false;
			}
		}
	}
	return true;
}

bool	RemoteLightContainer::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(Ver<200){
		int		iLightDimCount=Ver;
		for(int i=0;i<iLightDimCount;i++){
			int	k;
			if(::Load(f,k)==false)
				return false;
			if(k<0)
				k=0;
			if(LightDimCount<=k)
				k=LightDimCount-1;
			bool	Exist;
			if(::Load(f,Exist)==false)
				return false;
			if(Exist==true){
				if(Dim[k]==NULL){
					Dim[k]=new RemoteLightItem(GetLayersBase(),this);
				}
				if(Dim[k]->Load(f)==false){
					//return false;
					delete	Dim[k];
					Dim[k]=NULL;
				}
			}
		}
	}
	else{
		int		iLightDimCount;
		if(::Load(f,iLightDimCount)==false)
			return false;
		for(int i=0;i<iLightDimCount;i++){
			int	k;
			if(::Load(f,k)==false)
				return false;
			if(k<0)
				k=0;
			if(LightDimCount<=k)
				k=LightDimCount-1;
			bool	Exist;
			if(::Load(f,Exist)==false)
				return false;
			if(Exist==true){
				QByteArray	Data;
				if(::Load(f,Data)==false)
					return false;
				QBuffer		mBuff(&Data);
				mBuff.open(QIODevice::ReadOnly);
					
				if(Dim[k]==NULL){
					Dim[k]=new RemoteLightItem(GetLayersBase(),this);
				}
				if(Dim[k]->Load(&mBuff)==false){
					//return false;
					delete	Dim[k];
					Dim[k]=NULL;
				}
			}
		}
	}
	return true;
}

void			RemoteLightContainer::RemoveAll(void)
{
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			delete	Dim[i];
			Dim[i]=NULL;
		}
	}
}
bool			RemoteLightContainer::AppendList(RemoteLightItem *a)
{
	for(int i=LightDimCount-1;i>=0;i--){
		if(Dim[i]!=NULL){
			i++;
			if(i>=LightDimCount-1){
				return false;
			}
			Dim[i]=a;
			return true;
		}
	}
	Dim[0]=a;
	return true;
}

bool			RemoteLightContainer::RemoveList(RemoteLightItem *a)
{
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]==a){
			Dim[i]=NULL;
		}
	}
	return true;
}
void			RemoteLightContainer::MoveFrom(RemoteLightContainer	&a)
{
	for(int i=0;i<LightDimCount;i++){
		Dim[i]=a.Dim[i];
		a.Dim[i]=NULL;
	}
}

RemoteLightItem	*RemoteLightContainer::GetFirst(void)
{
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			return Dim[i];
		}
	}
	return NULL;
}

RemoteLightItem	*RemoteLightContainer::GetNextItem(RemoteLightItem *p)
{
	int	Index=-1;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]==p){
			Index=i;
			break;
		}
	}
	if(Index>=0){
		for(int i=Index+1;i<LightDimCount;i++){
			if(Dim[i]!=NULL){
				return Dim[i];
			}
		}
	}
	return NULL;
}

RemoteLightItem	*RemoteLightContainer::GetItem(int n)
{
	int	Counter=0;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			if(Counter==n){
				return Dim[i];
			}
			Counter++;
		}
	}
	return NULL;
}

int				RemoteLightContainer::GetCount(void)
{
	int	Counter=0;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			Counter++;
		}
	}
	return Counter;
}
bool	RemoteLightContainer::ReflectLight(void)
{
	bool	Ret=true;
	for(int i=0;i<LightDimCount;i++){
		if(Dim[i]!=NULL){
			if(Dim[i]->ReflectLight()==false)
				Ret=false;
		}
	}
	return Ret;
}