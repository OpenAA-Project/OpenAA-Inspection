#include "XSeqDLLGlobal.h"
#include "IOLogger.h"
#include "XIOLogThread.h"
#include <string.h>
#include <QFileInfo>
#include "XDateTime.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

//ThreadIOLogger	*ThreadLog=NULL;


DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base,const QString &Param)
{
	ThreadIOLogger	*ThreadLog=new ThreadIOLogger(Base->GetSeqControl());
	return ThreadLog;
}

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="IOLogger";
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
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "I/O Log writer";
}

/*
    初期に一度呼ばれる
*/

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"I/O Log writer");
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	ThreadIOLogger	*ThreadLog=(ThreadIOLogger	*)handle;
	if(ThreadLog!=NULL && ThreadLog->isFinished()==false){
		ThreadLog->terminate();
		ThreadLog->wait(1000);
	}
	if(ThreadLog!=NULL){
		delete	ThreadLog;
		ThreadLog=NULL;
	}
}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	QByteArray Buff;
	return DLLSeq_CmdStrRet(handle,App ,cmdstr , datastr ,Buff);
}

bool	DLLSeq_CmdStrRet(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,QByteArray &Buff)
{
	ThreadIOLogger	*ThreadLog=(ThreadIOLogger	*)handle;

	if(cmdstr=="Start"){
		QString	A=datastr;
		QFileInfo	FInfo(A);
		QString	Suf		=FInfo.suffix();
		QString	Path	=FInfo.path();
		QString	BaseName=FInfo.completeBaseName();
		XDateTime	Now=XDateTime::currentDateTime ();
		QString	PathSpace=::GetSeparator();
		if(Path.right(1)==QString('/') || Path.right(1)==QString('\\')){
			PathSpace=/**/"";
		}
		ForceDirectories(Path);
		QString	LogFileName=Path+PathSpace+BaseName+Now.toString("_yyMMdd-hhmmss")+QString(".")+Suf;

		::QString2Char(LogFileName,ThreadLog->FileName,sizeof(ThreadLog->FileName));
		ThreadLog->start();
		return true;
	}
	if(cmdstr=="AddReg"){
		ThreadLog->AddReg(datastr);
		return true;
	}
	if(cmdstr=="AddMsg"){
		ThreadLog->AddMessage(datastr);
		return true;
	}
	return false;
}
