
#include "windows.h"
#include "atlstr.h"
#include <math.h>
#include "XDLLType.h"
#include "XCameraDLL.h"
#include <atlstr.h>
#include "saperaCtrl.h"

#include "CameraXtiumMitsubishiCIS.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDLLType.h"
#include "XCameraCommon.h"


CameraXtiumBoard::CameraXtiumBoard(LayersBase *base ,CameraXtiumMitsubishiCIS *p ,int _ID)
	:ServiceForLayers(base)
	,Parent(p)
	,ID(_ID)
{
	_sapera	= new saperaCtrl(p->GetCamNo(),base,Parent,this);

	CamDotPerLine=-1;
}

CameraXtiumBoard::~CameraXtiumBoard()
{
	if (_sapera) {
		delete _sapera;
		_sapera = NULL;
	}
}
void	CameraXtiumBoard::InitialXTable(void)
{

}
bool	CameraXtiumBoard::Open(const QString &ConfigFileName)
{
	char buff[1024];
	QString2Char(ConfigFileName,buff ,sizeof(buff));
	_sapera->link(buff);
	return true;
}
bool	CameraXtiumBoard::Release(void)
{
	return true;
}
bool	CameraXtiumBoard::OpenCOM(void)
{
	QString	RawPortName=_sapera->GetSerialPortName();
	QString	PortName=QString(/**/"\\\\.\\")+RawPortName;

	wchar_t	ComFileName[MAX_PATH];
	memset(ComFileName,0,sizeof(ComFileName));
	PortName.toWCharArray ( ComFileName); 

	ComHandle = CreateFile(
			 ComFileName
			,GENERIC_READ|GENERIC_WRITE
			,0
			,NULL
			,OPEN_EXISTING
			//,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED
			,0
			,NULL
	);
	DWORD	Error=0;
	if(ComHandle==INVALID_HANDLE_VALUE){
		Error=GetLastError();
		return false;
	}

	BOOL	ret_B;
	DCB		DCBData;
	COMMTIMEOUTS	CommTimeouts;

	/* 通信ポートの現在の設定取得 */
	ret_B = GetCommState( ComHandle, &DCBData );
	if( !ret_B )
		return false;

	/* 設定の変更 */
	DCBData.DCBlength	=sizeof(DCBData);
	DCBData.BaudRate = 19200;
	DCBData.ByteSize = 8;
	DCBData.Parity   = NOPARITY;
	DCBData.StopBits = ONESTOPBIT;

	DCBData.fOutxCtsFlow= false;      // 以下 フロー制御
	DCBData.fOutxDsrFlow= false;
	DCBData.fDtrControl	= false;
	DCBData.fOutX		= false;
	DCBData.fInX		= false;
	DCBData.fRtsControl	= RTS_CONTROL_DISABLE;

	ret_B = SetCommState( ComHandle, &DCBData );
	if(ret_B==false)
		return false;

	/* 通信パラメータ初期化 */
	ret_B = SetupComm( ComHandle
	                   , 1024    // 受信バッファサイズ
	                   , 1024 ); // 送信バッファサイズ
	if(ret_B==false)
		return false;

	/* 通信用バッファ（システム）の初期化 */
	ret_B = PurgeComm( ComHandle, PURGE_TXABORT | PURGE_RXABORT
	                   | PURGE_TXCLEAR | PURGE_RXCLEAR );
	if(ret_B==false )
		return false;

	/* タイムアウトの設定 */
	//CommTimeouts.ReadIntervalTimeout         = 50;
	//CommTimeouts.ReadTotalTimeoutMultiplier  = 50;
	//CommTimeouts.ReadTotalTimeoutConstant    = 10;
	//CommTimeouts.WriteTotalTimeoutMultiplier = 50;
	//CommTimeouts.WriteTotalTimeoutConstant   = 10;
	CommTimeouts.ReadIntervalTimeout         = 5000;
	CommTimeouts.ReadTotalTimeoutMultiplier  = 5000;
	CommTimeouts.ReadTotalTimeoutConstant    = 1000;
	CommTimeouts.WriteTotalTimeoutMultiplier = 5000;
	CommTimeouts.WriteTotalTimeoutConstant   = 1000;
	ret_B = SetCommTimeouts( ComHandle, &CommTimeouts );
	if(ret_B==false)
		return false;

	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = CreateEvent( 0, TRUE, false, 0 );
	return true;
}

bool	CameraXtiumBoard::Save(QIODevice *f)
{
	return true;
}
bool	CameraXtiumBoard::Load(QIODevice *f)
{
	return true;
}

bool	CameraXtiumBoard::GrabPrepare(void)
{
	_sapera->prepareCapture();
	return true;
}
bool	CameraXtiumBoard::GrabStart(void)
{
	_sapera->startCapture();
	return true;
}
bool	CameraXtiumBoard::StopGrab(void)
{
	_sapera->stopCapture();
	return true;
}
bool	CameraXtiumBoard::IsCaptured(void)
{
	return _sapera->getStatus();
}
bool	CameraXtiumBoard::ChangeLineCount(int YLen)
{
	_sapera->saperaCtrl::ChangeLineCount(YLen);
	return true;
}

bool	CameraXtiumBoard::getImage(ImageBuffer *Buff[] )
{
	_sapera->getImage(Buff);
	return true;
}

bool	CameraXtiumBoard::SendPacket(int Cmd ,int ICode ,int Address ,BYTE *Param ,int ParamByte)
{
	char	Buff[256];

	Buff[0]=0x1b;
	Buff[1]=Cmd;
	Buff[2]=0;
	if(Address>=0)
		Buff[3]=1+2+ParamByte;
	else
		Buff[3]=1+ParamByte;
	Buff[4]=ICode;
	int	n=5;
	if(Address>=0){
		Buff[n]=Address>>8;
		n++;
		Buff[n]=Address&0xFF;
		n++;
	}
	for(int i=0;i<ParamByte;i++){
		Buff[n]=Param[i];
		n++;
	}
	Buff[n]=0xFF;
	n++;

	ResetEvent( ov.hEvent );

	DWORD wByte;
	if(WriteFile( ComHandle, Buff,n, &wByte, &ov)==false){
		DWORD tError=GetLastError();
		if(tError==ERROR_IO_PENDING){
			if(GetOverlappedResult(ComHandle, &ov, &wByte, TRUE)==false){
				return false;
			}
		}
		else{
			return false;
		}
	}
	if(n!=wByte)
		return false;
	return true;
}
bool	CameraXtiumBoard::ReceiveCom(BYTE RData[],int &RDataLen ,int MaxMilisec)
{
	DWORD dwErrors;
	COMSTAT ComStat;
	DWORD dwRead;
	
	if(ClearCommError(ComHandle, &dwErrors, &ComStat)==false){
		return false;
	}

	if(dwErrors!=0){
		return false;
	}

	if(ReadFile(ComHandle, RData, ComStat.cbInQue, &dwRead, &ov)==false){
		return false;
	}
	PurgeComm( ComHandle, PURGE_TXABORT | PURGE_RXABORT
						 | PURGE_TXCLEAR | PURGE_RXCLEAR );
	RDataLen	=dwRead;

	return true;
}

