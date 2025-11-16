#include "XRegulusWorld.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XRegulusWorldClient.h"
#include "XRegulusWorldObject.h"
#include "XRWDeviceInterface.h"
#include "XDataInLayer.h"
#include "XAnyData.h"
#include "XRWAlgorithmInterface.h"
#include "XRWAlgorithmBase.h"

RW3DItemRoot::RW3DItemRoot(RW3DInPageRoot *p)
	:Parent(p)
{
	BitAttr.Effective		=true;
	BitAttr.Selected		=false;
	BitAttr.Active			=false;
	BitAttr.EditLocked		=false;
	BitAttr.Changed			=true;
	BitAttr.CalcDone		=false;
	BitAttr.Visible			=true;
	BitAttr.Editable		=true;
	BitAttr.ManualCreated	=true;
}
ParamRegulusWorld	*RW3DItemRoot::GetParamRegulusWorld(void)	const
{
	return Parent->GetParamRegulusWorld();
}
RegulusWorld		*RW3DItemRoot::GetRegulusWorld(void)		const
{
	return Parent->GetRegulusWorld();
}
void	RW3DItemRoot::TransmitDirectly(GUIDirectMessage *packet)
{
}
RW3DInPageRoot	*RW3DItemRoot::GetParentInPage(void)	const
{	
	return Parent;
}
RW3DBaseRoot	*RW3DItemRoot::GetParentBase(void)	const
{
	return Parent->GetParentBase();
}
bool	RW3DItemRoot::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver		)==false)	return false;
	if(::Save(f,ItemID	)==false)	return false;
	if(::Save(f,ItemName)==false)	return false;
	if(f->write((const char *)&BitAttr,sizeof(BitAttr))!=sizeof(BitAttr)){
		return false;
	}
	return true;
}
bool	RW3DItemRoot::Load(QIODevice *f)
{
	int32	Ver=1;
	if(::Load(f,Ver		)==false)	return false;
	if(::Load(f,ItemID	)==false)	return false;
	if(::Load(f,ItemName)==false)	return false;
	if(f->read((char *)&BitAttr,sizeof(BitAttr))!=sizeof(BitAttr)){
		return false;
	}
	return true;
}

//-----------------------------------------

RW3DInPageRoot::RW3DInPageRoot(RW3DBaseRoot *parent)
	:Parent(parent)
{
}
RW3DInPageRoot::~RW3DInPageRoot(void)
{
}
void	RW3DInPageRoot::AppendItem(RW3DItemRoot *item)
{
	MutexData.lock();
	item->SetItemID(Parent->GetNewID());
	Data.AppendList(item);
	MutexData.unlock();
}
void	RW3DInPageRoot::RemoveItem(RW3DItemRoot *item)
{
	MutexData.lock();
	Data.RemoveList(item);
	MutexData.unlock();
}
ParamRegulusWorld	*RW3DInPageRoot::GetParamRegulusWorld(void)	const
{
	return Parent->GetParamRegulusWorld();
}
RegulusWorld		*RW3DInPageRoot::GetRegulusWorld(void)		const
{
	return Parent->GetRegulusWorld();
}
RW3DBaseRoot	*RW3DInPageRoot::GetParentBase(void)	const
{	
	return Parent;
}
bool	RW3DInPageRoot::GetArea(Point3D &MinPoint ,Point3D &MaxPoint)
{
	Point3D tMinPoint ,tMaxPoint;
	bool	FirstOne=true;
	bool	Ret=false;
	for(RW3DItemRoot *a=GetFirstData();a!=NULL;a=(RW3DItemRoot *)a->GetNext()){
		if(a->GetArea(tMinPoint ,tMaxPoint)==true){
			if(FirstOne==true){
				MinPoint=tMinPoint;
				MaxPoint=tMaxPoint;
				FirstOne=false;
			}
			else{
				MinPoint=min(MinPoint,tMinPoint);
				MaxPoint=max(MaxPoint,tMaxPoint);
			}
			Ret=true;
		}
	}
	return Ret;
}
RW3DItemRoot	*RW3DInPageRoot::SearchIDItem(int64 ItemID)
{
	for(RW3DItemRoot *a=GetFirstData();a!=NULL;a=(RW3DItemRoot *)a->GetNext()){
		if(a->GetItemID()==ItemID){
			return a;
		}
	}
	return NULL;
}
void	RW3DInPageRoot::Draw(QImage &pnt, CameraView &CamView,AlgorithmDrawAttr *Attr)
{
	for(RW3DItemRoot *a=GetFirstData();a!=NULL;a=(RW3DItemRoot *)a->GetNext()){
		a->Draw(pnt, CamView ,Attr);
	}
}
void	RW3DInPageRoot::TransmitDirectly(GUIDirectMessage *packet)
{
}
bool	RW3DInPageRoot::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	int32	N=Data.GetCount();
	if(::Save(f,N)==false)	return false;
	for(RW3DItemRoot *a=GetFirstData();a!=NULL;a=(RW3DItemRoot *)a->GetNext()){
		int32	ClassType=a->GetItemClassType();
		if(::Save(f,ClassType)==false)	return false;
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RW3DInPageRoot::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	int32	N;
	if(::Load(f,N)==false)	return false;
	Data.RemoveAll();
	for(int i=0;i<N;i++){
		int32	ClassType;
		if(::Load(f,ClassType)==false)	return false;
		RW3DItemRoot	*a=CreateItem(ClassType);
		if(a->Load(f)==false){
			return false;
		}
		Data.AppendList(a);
	}
	return true;
}
//-----------------------------------------
RW3DBaseRoot::RW3DBaseRoot(RegulusWorld *base)
	:RBase(base)
{
	LoadedVersion=0;
	BaseID=0;
}
void	RW3DBaseRoot::Initial(RegulusWorld *Base)
{
}
void	RW3DBaseRoot::InitialAfterParamLoaded(void)
{
	InitialCreate();
}
void	RW3DBaseRoot::InitialCreate(void)
{
	BaseID=1;
	Data.RemoveAll();
	int	PageNumb=GetParamRegulusWorld()->PageNumb;
	for(int page=0;page<PageNumb;page++){
		RW3DInPageRoot	*Ap=CreateChild();
		Ap->SetPage(page);
		Data.AppendList(Ap);
	}
}
ParamRegulusWorld	*RW3DBaseRoot::GetParamRegulusWorld(void)	const
{
	RegulusWorld	*BBase=GetRegulusWorld();
	ParamRegulusWorld	*P=BBase->GetParamRegulusWorld();
	return P;
}
int64	RW3DBaseRoot::GetNewID(void)
{
	MutexBaseID.lock();
	int64	Ret=BaseID;
	BaseID++;
	MutexBaseID.unlock();
	return Ret;
}
RW3DInPageRoot	*RW3DBaseRoot::GetPageData(int page)
{
	for(RW3DInPageRoot *a=Data.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetPage()==page){
			return a;
		}
	}
	return NULL;
}

void	RW3DBaseRoot::TransmitDirectly(GUIDirectMessage *packet)
{
}
bool	RW3DBaseRoot::Save(QIODevice *f)
{
	int32	Ver=1;
	if(::Save(f,Ver)==false)	return false;

	int32	PageNumb=Data.GetCount();
	if(::Save(f,PageNumb)==false)	return false;
	for(RW3DInPageRoot *a=Data.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RW3DBaseRoot::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)	return false;

	int32	PageNumb=Data.GetCount();
	if(::Save(f,PageNumb)==false)	return false;

	Data.RemoveAll();
	for(int page=0;page<PageNumb;page++){
		RW3DInPageRoot	*a=CreateChild();
		if(a->Load(f)==false){
			return false;
		}
		Data.AppendList(a);
	}
	return true;
}
//=================================================
AccessSocket::AccessSocket(int id,RegulusWorld *p,QTcpSocket *s,QObject *parent)
	:QObject(parent),ID(id),Sock(s),Parent(p)
{
	Sock=NULL;
	OnRBuff=NULL;
	LastReceivingTime	=0;
	NowOnPoint			=0;
	NowOnXByte			=0;
	NowCmd				=0;
	RxState				=_NowOnWaiting;
	LastPacketLoadedSize=0;
	FastCommLeafRxReEntrant=0;

	connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	connect(Sock,SIGNAL(disconnected()),this ,SLOT(SlotDisconnected()));
}

AccessSocket::~AccessSocket(void)
{
	if(Sock!=NULL){
		Sock->close();
		delete	Sock;
	}
	Sock=NULL;
}
const	int		MaxWaitingSecondInPacketReceive=30;
void	AccessSocket::SlotReadyRead()
{
	FastCommLeafRxReEntrant++;
	do{
		if(RxState==_NowOnWaiting || (RxState==_NowOnReceiving && (time(NULL)-LastReceivingTime>MaxWaitingSecondInPacketReceive))){
			int Len=Sock->read(((char *)&Pct)+LastPacketLoadedSize, sizeof(Pct)-LastPacketLoadedSize);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			if((Len+LastPacketLoadedSize)!=sizeof(Pct)){
				LastPacketLoadedSize+=Len;
				FastCommLeafRxReEntrant--;
				return;
			}
			LastPacketLoadedSize=0;

			NowOnXByte	=Pct.NowOnXByte	;
			NowCmd		=Pct.NowCmd		;
			if(OnRBuff!=NULL){
				delete	OnRBuff;
			}
			OnRBuff=new RWRecList(NowOnXByte);
			OnRBuff->Cmd			=NowCmd;
			OnRBuff->EmitterNameLen	=Pct.EmitterNameLen;
			OnRBuff->ClassNameLen	=Pct.ClassNameLen;
			OnRBuff->ErrorCode		=Pct.ErrorCode;
			OnRBuff->ErrorLevel		=Pct.ErrorLevel;
			OnRBuff->ErrorMessageLen=Pct.ErrorMessageLen;
			OnRBuff->ErrorTimeLen	=Pct.ErrorTimeLen;
			OnRBuff->IDForUndo		=Pct.IDForUndo;

			NowOnPoint=0;
		
			int	N=Sock->bytesAvailable();
			if(N!=0){
				if(NowOnXByte>=N){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
				else if(NowOnXByte!=0){
					Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte);
					if(Len<0){
						FastCommLeafRxReEntrant--;
						return;
					}
					NowOnPoint+=Len;
				}
			}
			RxState=_NowOnReceiving;
		}
		else{
			//qint64	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), NowOnXByte-NowOnPoint);
			int	N=Sock->bytesAvailable();
			int	RByte=min(OnRBuff->Len-NowOnPoint,N);
			int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint),RByte);
			//int	Len=Sock->read((char *)(OnRBuff->GetPointer()+NowOnPoint), N);
			if(Len<0){
				FastCommLeafRxReEntrant--;
				return;
			}
			NowOnPoint+=Len;
		}

		LastReceivingTime=time(NULL);
		if(NowOnXByte<=NowOnPoint){
			RxState=_NowOnWaiting;
			MuteRecData.lock();
			RecData.AppendList(OnRBuff);
			OnRBuff=NULL;
			MuteRecData.unlock();
			emit	SignalReceived(ID ,NowCmd);
		}
	}while(Sock->bytesAvailable()!=0);
	FastCommLeafRxReEntrant--;
}

void	AccessSocket::SlotDisconnected()
{
	emit	SignalDisconnected(ID);
	deleteLater();
}

RWRecList	*AccessSocket::UnpackTopRxBuff(void)
{
	MuteRecData.lock();
	RWRecList	*a=RecData.GetFirst();
	if(a!=NULL){
		RecData.RemoveList(a);
	}
	MuteRecData.unlock();
	return a;
}

bool	AccessSocket::TxData(int32 cmd
							 ,const QString &EmitterNameString,const QString &CmdClassString 
							 ,QBuffer *f
							 ,int32 IDForUndo
							 ,ErrorCodeList &ErrorData)
{
	if(Sock!=NULL){

		Sock->waitForBytesWritten(5000);

		int32	Len=f->size();
		char	EmitterName[1000];
		QString2Char(EmitterNameString ,EmitterName,sizeof(EmitterName));
		char	CmdClass[1000];
		QString2Char(CmdClassString ,CmdClass,sizeof(CmdClass));

		if(Sock->isTextModeEnabled()==true){
			Sock->setTextModeEnabled(false);
		}	
		int32	EmitterNameLen	=strlen(EmitterName);	
		int32	CmdClassLen		=strlen(CmdClass);	
		struct	RWTxRxLowPacket	Pct;
		Pct.NowOnXByte	=Len+CmdClassLen+1
							+EmitterNameLen+1
						+sizeof(Len);
		Pct.NowCmd			=cmd;
		Pct.EmitterNameLen	=EmitterNameLen;
		Pct.ClassNameLen	=CmdClassLen;
		Pct.IDForUndo		=IDForUndo;

		Pct.ErrorLevel		=(BYTE)ErrorData.GetLevel();
		char	ErrorMessage[1000];
		char	ETime[30];
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			Pct.ErrorCode	=ErrorData.GetErrorCode();
			QString2Char(ErrorData.GetMessageStr() ,ErrorMessage,sizeof(ErrorMessage));
			Pct.ErrorMessageLen	=strlen(ErrorMessage);
			Pct.NowOnXByte +=Pct.ErrorMessageLen+1;
			QString	t=ErrorData.GetErrorTime().toString("d/M/yy h:m:s.z");
			QString2Char(t,ETime,sizeof(ErrorMessage));
			Pct.ErrorTimeLen=strlen(ETime);
			Pct.NowOnXByte +=Pct.ErrorTimeLen+1;
		}
		if(Sock->write((char *)&Pct,sizeof(Pct))!=sizeof(Pct)){
			return(false);
		}
		if(Sock->write((char *)EmitterName,EmitterNameLen+1)!=(EmitterNameLen+1)){
			return(false);
		}
		if(Sock->write((char *)CmdClass,CmdClassLen+1)!=(CmdClassLen+1)){
			return(false);
		}
		if(ErrorData.GetLevel()!=ErrorCodeList::_None){
			if(Sock->write((char *)ErrorMessage	,Pct.ErrorMessageLen+1)!=(Pct.ErrorMessageLen+1)){
				return(false);
			}
			if(Sock->write((char *)ETime		,Pct.ErrorTimeLen+1)!=(Pct.ErrorTimeLen+1)){
				return(false);
			}
		}
		if(Sock->write((char *)&Len,sizeof(Len))!=sizeof(Len)){
			return(false);
		}
		if(Sock->write(f->buffer().data(),Len)!=Len){
			return(false);
		}
		if(Sock->flush()==false){
			return false;
		}
		return(true);
	}
	return(false);
}

bool	AccessSocket::WaitForReadyRead(int milisec)
{
	if(Sock!=nullptr){
		return Sock->waitForReadyRead(milisec);
	}
	return false;
}

//=================================================

RegulusWorld::RegulusWorld(LayersBase *base,bool _ServerMode)
	:ServiceForLayers(base)
	,AnyDataList(/**/"RegulusWorld")
	,RParam(this)
{
	ServerMode=_ServerMode;
	ClientCommNo=-1;
	if(ServerMode==true){
		Objects=new RegWorldObject(this);
	}
	else{
		Objects=nullptr;
	}
	if(base!=NULL){
		RWDeviceAccessPackInst=new RWDeviceAccessPack(base);
	}
	else{
		RWDeviceAccessPackInst=NULL;
	}
	RWAlgorithmDLLContainerInst =new RWAlgorithmDLLContainer(this);
	RWLogicDLLBaseClassInst		=new RWLogicDLLBaseClass(this);
}
RegulusWorld::~RegulusWorld(void)
{
	if(RWDeviceAccessPackInst!=NULL){
		delete	RWDeviceAccessPackInst;
		RWDeviceAccessPackInst=NULL;
	}
}
	
bool	RegulusWorld::InitialLoadParam(void)
{
	QString	UserPath;
	if(GetLayersBase()!=NULL){
		UserPath=GetLayersBase()->GetUserPath();
	}
	if(RParam.LoadDefault(UserPath)==false){
		return false;
	}
	return true;
}
	
bool	RegulusWorld::InitialLoadDevice(void)
{
	if(RWDeviceAccessPackInst!=NULL){
		int32 ErrorCode;
		//RWDeviceAccessPackInst->SearchAddDLL(ErrorCode);
		return RWDeviceAccessPackInst->Initial(ErrorCode);
	}
	return false;
}
bool	RegulusWorld::InitialAlgorithm(const QStringList &AlgorithmPathList)
{
	if(RWAlgorithmDLLContainerInst!=NULL){
		RWAlgorithmDLLContainerInst->SearchAddDLL(this,AlgorithmPathList);

		if(RWLogicDLLBaseClassInst!=NULL){
			RWLogicDLLBaseClassInst->AddDLLs(*RWAlgorithmDLLContainerInst ,this);
			for(RWLogicDLL *a=RWLogicDLLBaseClassInst->GetFirst();a!=NULL;a=a->GetNext()){
				a->InitialAfterParamLoaded();
			}
		}
	}
	return false;
}

void	RegulusWorld::InitialServer(int Port)
{
	connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	Server.listen(QHostAddress::Any,Port);
}
QString	RegulusWorld::GetDataFileName(void)
{

}
void	RegulusWorld::SlotNewConnection()
{
	QTcpSocket *v=Server.nextPendingConnection();

	int	MaxID=0;
	for(AccessSocket *a=ServerSocket.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()>MaxID){
			MaxID=a->GetID();
		}
	}

	AccessSocket	*sv=new AccessSocket(MaxID+1,this,v,nullptr);
	connect(sv,SIGNAL(SignalReceived(int,int)),this,SLOT(SlotReceived(int,int)),Qt::QueuedConnection);
	connect(sv,SIGNAL(SignalDisconnected(int)),this,SLOT(SlotDisconnected(int)),Qt::QueuedConnection);
	ServerSocket.AppendList(sv);
}

AccessSocket	*RegulusWorld::GetServerSocket(int ID)
{
	for(AccessSocket *a=ServerSocket.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			return a;
		}
	}
	return nullptr;
}

RWClientSocket	*RegulusWorld::GetClientSocket			(int ID)
{
	for(RWClientSocket *a=ClientSocketPackInst.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			return a;
		}
	}
	return nullptr;
}

void	RegulusWorld::SlotReceived(int ID,int Cmd)
{
	const char	*EmitterName	=NULL;
	const char	*CmdClass		=NULL;
	AccessSocket	*sv=GetServerSocket(ID);
	if(sv!=NULL){
		RWRecList	*R=sv->UnpackTopRxBuff();
		if(R!=NULL){
			char	EmitterNameBuff[100];
			char	CmdClassBuff[100];
			BYTE	*fp	=R->GetClassNamePointer(EmitterNameBuff ,CmdClassBuff,sizeof(CmdClassBuff));
			if(fp==NULL){
				MiscatchPacket(EmitterName ,CmdClass,/**/"Packet error");
				delete	R;
				return;
			}

			ErrorCodeList	ErrorData((ErrorCodeList::CautionLevel)R->ErrorLevel);
			if(ErrorData.GetLevel()!=ErrorCodeList::_None){
				fp	=R->GetError(fp,ErrorData);
			}

			EmitterName	=EmitterNameBuff;
			CmdClass	=CmdClassBuff;
			QBuffer buff;
			R->GetPointer(fp ,buff);
			buff.open(QIODevice::ReadWrite);

			for(RWPacketBasePointerList *w=PacketBase.GetFirst();w!=NULL;w=w->GetNext()){
				RWPacketBase	*wp=w->GetBase();
				if(wp->EmitterName==EmitterName
				&& wp->ClassName	==CmdClass){
					if(wp->Load(&buff)==false){
						MiscatchPacket(EmitterName ,CmdClass,/**/"Load error");
						delete	R;
						return;
					}
					wp->Receive(Cmd ,EmitterName,sv->GetClientID());
					delete	R;
					return;
				}
			}
			delete	R;
		}	
	}
	MiscatchPacket(EmitterName ,CmdClass,/**/"No class");
}
void	RegulusWorld::SlotDisconnected(int id)
{
	for(AccessSocket *a=ServerSocket.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==id){
			ServerSocket.RemoveList(a);
			delete	a;
			break;
		}
	}
}

void	RegulusWorld::MiscatchPacket(const char	*EmitterName 
									,const char	*CmdClass 
									,const QString &Msg)
{
	QString	FileName="MiscatchPacket.txt";
	QFileInfo LInfo(FileName);
	if(LInfo.size()<10000000){
		QFile	F(FileName);

		if(F.open(QIODevice::Append)==true){
			QTextStream	LF(&F);
			if(EmitterName!=NULL){
				LF<<"  Name:";
				LF<<EmitterName;
			}
			if(CmdClass!=NULL){
				LF<<"  CmdClass:";
				LF<<CmdClass;
			}
			LF<<"  Error:";
			LF<<Msg;
			LF<<"\n";
		}
	}
}

void	RegulusWorld::AppendPacket(RWPacketBase *PSrc ,const QString &emitterName ,const QString &className)
{
	PacketMutex.lock();
	RCmdBase.AppendList(new RWReceiverList(emitterName ,className,PSrc));
	PacketMutex.unlock();
}

bool	RegulusWorld::RemovePacket(RWPacketBase *PSrc)
{
	bool	Ret=false;
	PacketMutex.lock();
	for(RWReceiverList *p=RCmdBase.GetLast();p!=NULL;p=p->GetPrev()){
		if(p->Point==PSrc){
			RCmdBase.RemoveList(p);
			delete	p;
			Ret=true;
			break;
		}
	}
	PacketMutex.unlock();
	return Ret;
}


void	RegulusWorld::PopupPacketPriority(RWPacketBase *PSrc)
{
	PacketMutex.lock();
	for(RWReceiverList *p=RCmdBase.GetLast();p!=NULL;p=p->GetPrev()){
		if(p->Point==PSrc){
			RCmdBase.RemoveList(p);
			RCmdBase.AppendList(p);
			break;
		}
	}
	PacketMutex.unlock();
}

RWPacketBase *RegulusWorld::FindPacket(const QString &ClassName)
{
	PacketMutex.lock();
	for(RWReceiverList *p=RCmdBase.GetLast();p!=NULL;p=p->GetPrev()){
		if(p->ClassName==ClassName){
			PacketMutex.unlock();
			return p->Point;
		}
	}
	PacketMutex.unlock();
	return NULL;
}

RWPacketBase *RegulusWorld::FindPacket(const QString &ClassName, QString &emitterName)
{
	PacketMutex.lock();
	for(RWReceiverList *p=RCmdBase.GetLast();p!=NULL;p=p->GetPrev()){
		if((p->EmitterName==emitterName) && (p->ClassName==ClassName) ){
			PacketMutex.unlock();
			emitterName	=p->EmitterName;
			return p->Point;
		}
	}
	PacketMutex.unlock();
	return NULL;
}

void	RegulusWorld::AddError(ErrorCodeList *e)
{
	ErrorMutex.lock(); 
	ErrorContainer.AppendList(e); 
	ErrorMutex.unlock(); 
	if(RParam.ErrorLogFile.isEmpty()==false){ 
		QFile	FL(RParam.ErrorLogFile); 
		if(FL.open(QIODevice::Append | QIODevice::Text)==true){ 
			QTextStream	TxtStr(&FL); 
			e->OutputStr(TxtStr); 
			TxtStr<<QString("\n"); 
		} 
	} 
}
RWDeviceAccessPack	*RegulusWorld::GetRWDeviceAccessPack(void)
{
	return RWDeviceAccessPackInst;
}
RWDeviceBaseClass	*RegulusWorld::FindByDeviceID(int deviceID)
{
	return RWDeviceAccessPackInst->FindByDeviceID(deviceID);
}

RegulusWorld	*GetRegulusWorld(LayersBase *d)
{
	if(d==nullptr)	return nullptr;
	AnyDataList	*a=d->GetAnyData()->Find(/**/"RegulusWorld");
	if(a!=nullptr){
		return dynamic_cast<RegulusWorld *>(a);
	}
	return nullptr;
}
ParamRegulusWorld	*RegulusWorld::GetParamRegulusWorld(void)
{	
	return &RParam;
}
RW3DBaseRoot	*RegulusWorld::GetRW3DBaseRoot(const QString &DLLRoot ,const QString DLLName)
{
	for(RWLogicDLL *a=RWLogicDLLBaseClassInst->GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetDLLRoot()==DLLRoot
		&& a->GetDLLName()==DLLName){
			return a->GetInstance();
		}
	}
	return NULL;
}
