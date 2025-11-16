#include "CheckProgramRun.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QFileInfo>
#include "XDateTime.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"


/*
    初期に一度呼ばれる
*/

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"Check program to run");
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="CheckProgramRun";
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
	return "Check program to run";
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{

}
bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="Check"){
		QString	Program=datastr;

		QStringList Processes;
		if(GetProcessNames(Processes)==true){
			for(int i=0;i<Processes.count();i++){
				if(Processes[i]==Program){
					return true;
				}
			}
		}
		return false;
	}
	return false;
}

