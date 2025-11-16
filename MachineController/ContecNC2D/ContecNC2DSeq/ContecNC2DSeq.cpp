#include "ContecNC2DSeq.h"
#include "XSeqDLLGlobal.h"


ContecNC2DController::ContecNC2DController(QObject *parent)
	:QObject(parent)
{
	Socket=NULL;
	Received=false;
}

ContecNC2DController::~ContecNC2DController(void)
{
	if(Socket!=NULL){
		Socket->disconnectFromServer();
		delete	Socket;
		Socket=NULL;
	}
}

bool	ContecNC2DController::StartConnect(void)
{
	Socket=new QLocalSocket(parent());
	connect(Socket,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
	Socket->connectToServer ("ContecNC2D");
	if(Socket->waitForConnected (3000)==false){
		Socket->deleteLater();
		Socket=NULL;
		return false;
	}
	return true;
}

void	ContecNC2DController::SlotReadyRead()
{
	QByteArray	R=Socket->readAll();
	QString	Req(R);
	RData	=Req;
	
	Received=true;
}

void	ContecNC2DController::SendCommand(const QString &Str)
{
	if(Socket==NULL){
		StartConnect();
	}
	Received=false;
	if(Socket!=NULL){
		QByteArray	Array;
		Array+=Str;
		Socket->write(Array);
		Socket->flush();
	}
}

bool	ContecNC2DController::WaitForRead(void)
{
	if(Socket==NULL){
		StartConnect();
	}
	if(Socket!=NULL){
		Socket->waitForReadyRead(1);
		return Received;
	}
	return false;
}

//===========================================================================

//ContecNC2DController	*Pointer=NULL;

class	SeqPack
{
public:
	ContecNC2DController	*Pointer;

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
	str="ContecNC2D";
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
	return "ContecNC2D";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"ContecNC2D-1");
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
		LSeq->Pointer	=new ContecNC2DController(&App);
		return true;
	}
	else if(cmdstr=="Start"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("Start");
		}
		return true;
	}
	else if(cmdstr=="Step"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("Start");
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
	if(cmdstr=="IsEnd"){
		if(LSeq->Pointer!=NULL){
			LSeq->Pointer->SendCommand("IsEnd");
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
			if(LSeq->Pointer->WaitForRead()==true){
				*data=LSeq->Pointer->RData.toInt();
				return true;
			}
		}
		return false;
	}

	return false;
}