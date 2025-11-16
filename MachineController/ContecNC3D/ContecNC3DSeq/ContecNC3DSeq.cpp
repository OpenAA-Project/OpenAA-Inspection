#include "ContecNC3DSeq.h"
#include "XSeqDLLGlobal.h"
#include "XGeneralFunc.h"


ContecNC3DController::ContecNC3DController(QObject *parent)
	:QObject(parent)
{
	Socket=NULL;
	Received=false;
}

ContecNC3DController::~ContecNC3DController(void)
{
	if(Socket!=NULL){
		Socket->disconnectFromServer();
		delete	Socket;
		Socket=NULL;
	}
}

bool	ContecNC3DController::StartConnect(void)
{
	Socket=new QLocalSocket(parent());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer ("ContecNC3D");
	if(Socket->waitForConnected (3000)==false){
		Socket->deleteLater();
		Socket=NULL;
		return false;
	}
	return true;
}

void	ContecNC3DController::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	RData	=Req;
	
	Received=true;
}

void	ContecNC3DController::SendCommand(const QString &Str)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,Str);
		QByteArray	Array=Buff.buffer();
		Socket->write(Array);
		Socket->flush();
	}
}
void	ContecNC3DController::SendCommand(const QString &Str ,int data)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		::Save(&Buff,Str);
		::Save(&Buff,data);
		QByteArray	Array=Buff.buffer();
		Socket->write(Array);
		Socket->flush();
	}
}

bool	ContecNC3DController::WaitForRead(int WTm)
{
	if(Socket==NULL){
		StartConnect();
	}
	if(Socket!=NULL){
		Socket->waitForReadyRead(WTm);
		return Received;
	}
	return false;
}

//===========================================================================

//ContecNC3DController	*Pointer=NULL;
class	SeqPack
{
public:
	ContecNC3DController	*Pointer;

	SeqPack(void)	{	Pointer=NULL;	}
};

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="ContecNC3D";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2015.1";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "ContecNC3D";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"ContecNC3D-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	SeqPack	*LSeq=new SeqPack();
	return LSeq;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
{
	SeqPack	*LSeq=(SeqPack *)handle;
	delete	LSeq;
}

bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	SeqPack	*LSeq=(SeqPack *)handle;
	if(cmdstr=="Init"){
		LSeq->Pointer	=new ContecNC3DController(&App);
		return true;
	}
	else if(cmdstr=="GoOrigin"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("GoOrigin");
		}
		return true;
	}
	else if(cmdstr=="StartXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("StartXY");
		}
		return true;
	}
	else if(cmdstr=="StepXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("StepXY");
		}
		return true;
	}
	else if(cmdstr=="SetLightGreenON"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("SetLightGreenON");
		}
		return true;
	}

	else if(cmdstr=="SetLightGreenOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("SetLightGreenOFF");
		}
		return true;
	}
	else if(cmdstr=="BlinkButton"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("BlinkButton");
		}
		return true;
	}
	else if(cmdstr=="BlinkOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("BlinkOFF");
		}
		return true;
	}
	else if(cmdstr=="VacuumON"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("VacuumON");
		}
		return true;
	}
	else if(cmdstr=="VacuumOFF"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("VacuumOFF");
		}
		return true;
	}
	return false;
}
DEFFUNCEX		bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	SeqPack	*LSeq=(SeqPack *)handle;
	if(cmdstr=="IsEndXY"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEndXY");
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}
	if(cmdstr=="IsStart"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsStartButton");
			if(LSeq->Pointer->WaitForRead(500)==true){
				LSeq->Pointer->SendCommand("IsStartButton");
				if(LSeq->Pointer->WaitForRead(500)==true){
					*data=LSeq->Pointer->RData.toInt();
					return true;
				}
			}
		}
		return false;
	}
	if(cmdstr=="IsEndZ"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEndZ");
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}
	if(cmdstr=="MoveZ"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("MoveZ",*data);
		}
		return true;
	}

	return false;
}