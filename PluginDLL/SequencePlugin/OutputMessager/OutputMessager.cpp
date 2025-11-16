#include "OutputMessager.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include "XGeneralFunc.h"
#include "XMessagerClient.h"
#include <QApplication>


class	OutputMessager
{
public:
	MessagerClient	*MessagerInst;

	OutputMessager(void)
	{
		MessagerInst=NULL;
	}
};



WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="OutputMessager";
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
	return "Output messager";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"Output messager");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	OutputMessager	*Messager=new OutputMessager();
	return Messager;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	OutputMessager	*Messager=(OutputMessager *)handle;

	if(Messager->MessagerInst!=NULL){
		delete	Messager->MessagerInst;
	}
	delete	Messager;
}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	OutputMessager	*Messager=(OutputMessager *)handle;

	if(cmdstr=="Start"){
		if(Messager->MessagerInst==NULL){
			QString	IPAddress=datastr;
			Messager->MessagerInst=new MessagerClient(&App);
			Messager->MessagerInst->Initial(IPAddress);
			Messager->MessagerInst->Start();
		}
		return true;
	}
	else if(cmdstr=="ShowOn"){
		if(Messager->MessagerInst!=NULL){
			Messager->MessagerInst->Send(2,0,datastr);
			return true;
		}
	}
	else if(cmdstr=="ShowOff"){
		if(Messager->MessagerInst!=NULL){
			Messager->MessagerInst->Send(3,0,datastr);
			return true;
		}
	}
	return false;
}

