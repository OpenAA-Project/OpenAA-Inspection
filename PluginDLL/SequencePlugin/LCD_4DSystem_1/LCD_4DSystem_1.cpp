#include "XSeqDLLGlobal.h"
#include "LCD_4DSystem_1.h"
#include <string.h>
#include <QFileInfo>
#include "XGeneralFunc.h"
#include "XForWindows.h"
#include "XCriticalFunc.h"
#include "XDataInLayer.h"

//ThreadComm	*ThreadExe=NULL;

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="LCD_4DSystem_1";
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
	CopyrightString="Copyright(c) MEGATRADE 2013.3";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "Sequence for LCD-4DSystem-1";
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
	strcpy(buff,"LCD-4DSystem-1");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	ThreadComm	*ThreadExe=new ThreadComm(Base->GetSeqControl(),Param);
	return ThreadExe;
}

DEFFUNCEX		void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	ThreadComm	*ThreadExe=(ThreadComm	*)handle;

	if(ThreadExe!=NULL && ThreadExe->isFinished()==false){
		ThreadExe->terminate();
		ThreadExe->wait(1000);
	}
	if(ThreadExe!=NULL){
		delete	ThreadExe;
	}
}
bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	ThreadComm	*ThreadExe=(ThreadComm	*)handle;

	if(cmdstr=="Start"){
		if(ThreadExe->isRunning()==false){
			ThreadExe->start();
		}
		while(ThreadExe->Initialized==false){
			GSleep(10);
		}

		return true;
	}
	else if(cmdstr=="Unknown"){
		ThreadExe->ShowUnknown();

		return true;
	}
	else if(cmdstr=="Reset"){
		ThreadExe->ModePushedCalcStart = false;
		ThreadExe->ModePushedDetail = false;
		ThreadExe->ModeShowPCBCount = false;
		ThreadExe->ModeShowUnknown = false;
		ThreadExe->ModeShowMirrorState = false;
		ThreadExe->ModePushedLightAdjust = false;
		ThreadExe->ModeMirrorCheck = false;
		return true;
	}else if(cmdstr=="IsCalcStartPushed"){
		return ThreadExe->IsCalcStartPushed();
	}else if(cmdstr=="IsDetailButtonPushed"){
		return ThreadExe->IsDetailButtonPushed();
	}else if(cmdstr=="Booted"){
		ThreadExe->SendBooted();
		return true;
	}else if(cmdstr=="End"){
		ThreadExe->SendEnd();
		return true;
	}else if(cmdstr=="IsLightAdjustPushed"){
		return ThreadExe->IsLightAdjustPushed();
	}else if(cmdstr=="ShowPCBCountInitial"){
		ThreadExe->ShowPCBCount(0);
		return true;
	}else if(cmdstr=="IsMirrorCheckPushed"){
		return ThreadExe->IsMirrorCheckPushed();
	}else if(cmdstr=="QuitApp"){
		qApp->quit();
		return true;
	}else if(cmdstr=="Free"){
		ThreadExe->stop();
		while(ThreadExe->isFinished()==false){qApp->processEvents(QEventLoop::ExcludeUserInputEvents);}
		ThreadExe->uninitialize();
	}else if(cmdstr=="IsRecieved"){
		return ThreadExe->Motioner->isRecieved();
	}else if(cmdstr=="ResetRecieved"){
		ThreadExe->Motioner->resetRecieved();
		return true;
	}

	return false;
}

bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
{
	ThreadComm	*ThreadExe=(ThreadComm	*)handle;

	if(cmdstr=="ShowPCBCount"){
		if(*data>=0){
			ThreadExe->ShowPCBCount(*data);
		}else{
			ThreadExe->ShowUnknown();
		}
		return true;
	}else if(cmdstr=="ShowMirrorState"){
		if(*data>=0){
			ThreadExe->ShowMirrorState(true);
		}else{
			ThreadExe->ShowMirrorState(false);
		}
		return true;
	}else if(cmdstr=="ExitApp"){
		qApp->exit(*data);
		return true;
	}

	return false;
}