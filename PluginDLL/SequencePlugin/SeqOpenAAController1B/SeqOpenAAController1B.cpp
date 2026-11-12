#include "SeqOpenAAController1B.h"
#include "XSeqDLLGlobal.h"


WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="SeqOpenAAController1B";
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
	CopyrightString="Copyright(c) MEGATRADE 2026.10";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Output OpenAAController1B";
}

void	DLLSeq_GetDLLVersion(char *buff)
{
	strcpy(buff,"Output OpenAAController1B");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	SeqOpenAAController1B	*Messager=new SeqOpenAAController1B(Base,Param);
	Messager->ConnectToHost();
	return Messager;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
{
	SeqOpenAAController1B	*Messager=(SeqOpenAAController1B *)handle;
	Messager->deleteLater();
}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
{
	SeqOpenAAController1B	*Messager=(SeqOpenAAController1B *)handle;

	if(cmdstr=="OK"){
		Messager->SendOK();
		return true;
	}
	else if(cmdstr=="NG"){
		Messager->SendNG();
	}
	return false;
}

DEFFUNCEX		bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
{
	SeqOpenAAController1B	*Messager=(SeqOpenAAController1B *)handle;

	if(cmdstr=="OK"){
		Messager->SendOK();
		return true;
	}
	else if(cmdstr=="NG"){
		Messager->SendNG();
	}
	return false;
}

//=================================================================================

SeqOpenAAController1B::SeqOpenAAController1B(LayersBase *base,const QString &Param)
	:ServiceForLayers(base)
{
	Sock=NULL;
	IPAddress=Param;
}

SeqOpenAAController1B::~SeqOpenAAController1B(void)
{
	if(Sock!=NULL){
		Sock->disconnectFromHost();
		Sock->waitForDisconnected(1000);
		Sock->deleteLater();
		Sock=NULL;
	}
}

bool    SeqOpenAAController1B::ConnectToHost()
{
	if(Sock==NULL){
		Sock=new QTcpSocket(this);
	}
	if(Sock->state()!=QAbstractSocket::ConnectedState){
		Sock->connectToHost(IPAddress ,OpenAAController1BSeqPort);
		Sock->waitForConnected(2000);
	}
	if(Sock->state()!=QAbstractSocket::ConnectedState){
		return false;
	}
	return true;
}
bool    SeqOpenAAController1B::SendOK()
{
	if(Sock->state()==QAbstractSocket::ConnectedState){
		Sock->write("1",1);
		Sock->flush();
		return true;
	}
	return false; 
}
bool    SeqOpenAAController1B::SendNG()
{
	if(Sock->state()==QAbstractSocket::ConnectedState){
		Sock->write("2",1);
		Sock->flush();
		return true;
	}
	return false; 
}
