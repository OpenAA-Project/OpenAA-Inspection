#include "KeyenceILSensor.h"
#include "XSeqDLLGlobal.h"
#include <string.h>
#include <QFileInfo>
#include "XDateTime.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"

#include <qextserialport.h>

//static QextSerialPort *port;
/*
    初期に一度呼ばれる
*/

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"KeyenceILSensor 1.0");
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="KeyenceILSensor";
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


const char	*DLL_GetExplain(void)
{
	return "DL-RS1A command operator for KeyenceILSensor";
}

void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
}

void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	QextSerialPort	*port = new QextSerialPort(Param);
	port->setBaudRate(BAUD9600);
	port->setFlowControl(FLOW_OFF);
	port->setParity(PAR_NONE);
	port->setDataBits(DATA_8);
	port->setStopBits(STOP_1);
	if(port->open(QIODevice::ReadWrite)==false){
		delete	port;
		port=NULL;
	}
}

bool	SendData(QextSerialPort *port,char *fp)
{

	if(port->write(*fp,Len)!=Len)
		return false;
	return true;
}


bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
{
	if(cmdstr=="Zero"){
		if(port!=NULL){
			SendData("SW,00,001,0\x0d\x0a");
		}
	}

}



bool	DLLSeq_CmdStr(void *handle ,QApplication &App ,const QString &cmdstr , const QString &datastr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	if(cmdstr=="Open"){
		port = new QextSerialPort(datastr);
		port->setBaudRate(BAUD9600);
		port->setFlowControl(FLOW_OFF);
		port->setParity(PAR_NONE);
		port->setDataBits(DATA_8);
		port->setStopBits(STOP_1);
		if(port->open(QIODevice::ReadWrite))
			return true;
		return false;

	}
	return false;
}

