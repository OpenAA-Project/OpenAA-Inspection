
#ifdef _MSC_VER
#include "XTypeDef.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XForWindows.h"
#include "XGeneralFunc.h"
#include "Windows.h"

bool	_GetVolumeInformation(
  char *lpRootPathName,           // ルートディレクトリ
  char *lpVolumeNameBuffer,        // ボリューム名バッファ
  int32 nVolumeNameSize,            // 名前バッファのサイズ
  int32 &lpVolumeSerialNumber,     // ボリュームのシリアル番号
  int32 &lpMaximumComponentLength, // ファイル名の最大の長さ
  int32 &lpFileSystemFlags,        // ファイルシステムのオプション
  char *lpFileSystemNameBuffer,    // ファイルシステム名を格納するバッファ
  int32 nFileSystemNameSize       // ファイルシステム名を格納するバッファのサイズ
);

bool	MtGetVolumeInformation(
  QString RootPathName,           // ルートディレクトリ
  QString &RetVolumeNameBuffer,        // ボリューム名バッファ
  int32 &VolumeSerialNumber,     // ボリュームのシリアル番号
  int32 &MaximumComponentLength, // ファイル名の最大の長さ
  int32 &FileSystemFlags,        // ファイルシステムのオプション
  QString &FileSystemNameBuffer    // ファイルシステム名を格納するバッファ
)
{
	char iRootPathName[1000];
	char iVolumeNameBuffer[1000];
	char iFileSystemNameBuffer[1000];

	QString2Char(RootPathName,iRootPathName,sizeof(iRootPathName)-1);

	int	n=strlen(iRootPathName);
	if(n>0){
		if(iRootPathName[n-1]!='/' && iRootPathName[n-1]!='\\'){
			iRootPathName[n-1]='/';
			iRootPathName[n]=0;
		}
	}

	bool	ret=_GetVolumeInformation(
				//iRootPathName,           // ルートディレクトリ
				(char *)iRootPathName,
				iVolumeNameBuffer,        // ボリューム名バッファ
				sizeof(iVolumeNameBuffer),            // 名前バッファのサイズ
				VolumeSerialNumber,     // ボリュームのシリアル番号
				MaximumComponentLength, // ファイル名の最大の長さ
				FileSystemFlags,        // ファイルシステムのオプション
				iFileSystemNameBuffer,    // ファイルシステム名を格納するバッファ
				sizeof(iFileSystemNameBuffer)       // ファイルシステム名を格納するバッファのサイズ
		);
	RetVolumeNameBuffer		=iVolumeNameBuffer;
	FileSystemNameBuffer	=iFileSystemNameBuffer;
	return ret;
}

// MtShutdownSelfPC Function
//
//  * [概要] この関数を実行したPCをシャットダウンさせる
//  * [注意] この関数がtrueを返したとき、すでに終了処理に入っているので次の処理の動作に気をつけること
//  * [戻り値] シャットダウンに成功したかどうかのbool型変数を返す
//  * [引数]
//     * bool BoolForciblyExitsOthers
//       他のプロセスを終了させるときのモード
//         * true     なにがなんでも強制終了させる、大多数のアプリケーションでは保存していないデータは破棄される
//         * false    閉じるボタンと同じ命令を送って終了させる（と思われる）
//     * bool BoolReboot
//       シャットダウン後、再起動するかどうか

bool	MtShutdownSelfPC( bool BoolForciblyExitsOthers=false, bool BoolReboot=false )
{
	//いま起動しているプロセスにシャットダウンさせる権限を与える
	HANDLE HandleToken = NULL;

	HANDLE HandleCurrentProcess = GetCurrentProcess();
	if( ::OpenProcessToken( HandleCurrentProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &HandleToken ) == 0 )
		return false;

	//電源を切る権限もあるかどうか
	bool isPrivilegeOn = false;
	LUID id;
	if( ::LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &id) ){
		TOKEN_PRIVILEGES token;
		token.PrivilegeCount = 1;
		token.Privileges[0].Luid = id;
		token.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		isPrivilegeOn = ::AdjustTokenPrivileges(HandleToken, false, &token, 0, NULL, NULL);
	}

	//権限の操作おわり
	::CloseHandle( HandleToken );


	uint	uShutdownFlags = 0;
	if( BoolReboot == true)
		uShutdownFlags |= EWX_REBOOT;

	if( isPrivilegeOn == true )
		uShutdownFlags |= EWX_POWEROFF;
	else
		uShutdownFlags |= EWX_SHUTDOWN;

	if( BoolForciblyExitsOthers == true )
		uShutdownFlags |= EWX_FORCE;
	//else
	//	uShutdownFlags |= EWX_FORCEIFHUNG;	//Windows2000 only?

	//この関数がtrueを返したときにはすでに終了処理に入っている
	if( ::ExitWindowsEx( uShutdownFlags, 0 ) == false )
		return false;

	return true;
}

void	MtAdjustTime(int hour ,int minute ,int second)
{
	SYSTEMTIME	SystemTm;

	GetLocalTime(&SystemTm);

	SystemTm.wHour=hour;
	SystemTm.wMinute=minute;
	SystemTm.wSecond=second;

	SetLocalTime(&SystemTm);
}

int64	MtGetDiskFreeSpace(char *DriveStr)
{
	wchar_t			DStr[100];
	ULARGE_INTEGER FreeBytesAvailable;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	if(DriveStr[1]==':' && DriveStr[2]==0){
		DriveStr[2]='/';
		DriveStr[3]=0;
	}
	int	i=0;
	for(char *fp=DriveStr;*fp!=0;fp++){
		DStr[i]=*fp;
		i++;
	}
	DStr[i]=0;

	if(::GetDiskFreeSpaceEx(DStr,
		&FreeBytesAvailable,    // 呼び出し側が利用できるバイト数
		&TotalNumberOfBytes,    // ディスク全体のバイト数
		&TotalNumberOfFreeBytes // ディスク全体の空きバイト数
		)==TRUE){
		return (int64)TotalNumberOfFreeBytes.QuadPart;
	}
	return -1;
}


bool	MtGetComputerName(char CName[],int size)
{
	wchar_t			DStr[1000];
	DWORD		LSize=1000-1;
	if(::GetComputerName(DStr,&LSize)==TRUE){
		QString	Str=QString::fromStdWString (DStr);
		QString2Char(Str,CName,size);
		return true;
	}
	return false;
}

bool	MtGetComputerName(QString &CName)
{
	wchar_t			DStr[1000];
	static	DWORD	Err;
	DWORD		LSize=1000-1;
	if(::GetComputerName(DStr,&LSize)==TRUE){
		CName=QString::fromStdWString (DStr);
		return true;
	}
	Err=GetLastError();
	return false;
}

bool	MTCopyFile(const QString &SourceFileName ,const QString &DestFileName ,bool failIfExist)
{
	wchar_t iSourceName[1000];
	wchar_t iDestName[1000];

	memset(iSourceName,0,sizeof(iSourceName));
	memset(iDestName,0	,sizeof(iDestName));

	SourceFileName.toWCharArray(iSourceName);
	DestFileName.toWCharArray(iDestName);

	if(::CopyFile(iSourceName,iDestName,failIfExist)==false){
		return false;
	}
	return true;
}

bool KillProcess(DWORD dwProcessId, unsigned int uExitCode)
{
     DWORD dwDesiredAccess = PROCESS_TERMINATE;
     BOOL  bInheritHandle  = false;
     HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
     if (hProcess == NULL)
         return false;
 
     BOOL result = TerminateProcess(hProcess, uExitCode);
 
     CloseHandle(hProcess);
 
	 if(result==TRUE)
		 return true;
     return false;
}

DWORD	MtGetCurrentProcessId(void)
{
	return GetCurrentProcessId();
}

bool	MTCopyAll (const QString &SourcePath ,const QString &DestPath ,bool failIfExist)
{
	::ForceDirectories(DestPath);
	QDir	sDir(SourcePath);
	QStringList SubFolders=sDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<SubFolders.count();i++){
		QString	sFolder= SourcePath
						+::GetSeparator()
						+SubFolders[i];
		QString	dFolder= DestPath
						+::GetSeparator()
						+SubFolders[i];
		if(::MTCopyAll (sFolder ,dFolder,failIfExist)==false){
			return false;
		}
	}
	QStringList FileNames=sDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<FileNames.count();i++){
		QString	sFileName= SourcePath
						+::GetSeparator()
						+FileNames[i];
		QString	dFileName= DestPath
						+::GetSeparator()
						+FileNames[i];
		if(::MTCopyFile(sFileName ,dFileName,failIfExist)==false){
			return false;
		}
	}
	return true;
}

bool	MTCopyAllExceptForOldAndNotExist (const QString &SourcePath ,const QString &DestPath)
{
	::ForceDirectories(DestPath);
	QDir	sDir(SourcePath);
	QStringList SubFolders=sDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i=0;i<SubFolders.count();i++){
		QString	sFolder= SourcePath
						+::GetSeparator()
						+SubFolders[i];
		QString	dFolder= DestPath
						+::GetSeparator()
						+SubFolders[i];
		if(::MTCopyAllExceptForOldAndNotExist (sFolder ,dFolder)==false){
			return false;
		}
	}
	QStringList FileNames=sDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<FileNames.count();i++){
		QString	sFileName= SourcePath
						+::GetSeparator()
						+FileNames[i];
		QString	dFileName= DestPath
						+::GetSeparator()
						+FileNames[i];
		if(QFile::exists(dFileName)==false){
			if(::MTCopyFile(sFileName ,dFileName,false)==false){
				return false;
			}
		}
		else{
			QFileInfo	SInfo(sFileName);
			QFileInfo	DInfo(dFileName);
			QDateTime	sTime=SInfo.lastModified();
			QDateTime	dTime=DInfo.lastModified();
			if(sTime>dTime){
				if(::MTCopyFile(sFileName ,dFileName,false)==false){
					return false;
				}
			}
		}
	}
	return true;
}
#endif