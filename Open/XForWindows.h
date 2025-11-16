#if	!defined(XFORWINDOWS_H)
#define	XFORWINDOWS_H


#include "XTypeDef.h"
#include <QString>

bool	MtGetVolumeInformation(
  QString RootPathName,				// ルートディレクトリ
  QString &RetVolumeNameBuffer,     // ボリューム名バッファ
  int32 &VolumeSerialNumber,		// ボリュームのシリアル番号
  int32 &MaximumComponentLength,	// ファイル名の最大の長さ
  int32 &FileSystemFlags,			// ファイルシステムのオプション
  QString &FileSystemNameBuffer		// ファイルシステム名を格納するバッファ
);


// 仕様はXForWindows.cpp内のコメントに記載
bool	MtShutdownSelfPC( bool BoolForciblyExitsOthers, bool BoolReboot );

void	MtAdjustTime(int hour,int minute ,int second);
int64	MtGetDiskFreeSpace(char *DriveStr);
bool	MtGetComputerName(char CName[],int size);
bool	MtGetComputerName(QString &CName);
bool	GetProcessNames(QStringList &Processes);
bool	MTCopyFile(const QString &SourceFileName ,const QString &DestFileName ,bool failIfExist);
bool	MTCopyAll (const QString &SourcePath ,const QString &DestPath ,bool failIfExist);
bool	MTCopyAllExceptForOldAndNotExist (const QString &SourcePath ,const QString &DestPath);
DWORD	MtGetCurrentProcessId(void);
bool	KillProcess(DWORD dwProcessId, unsigned int uExitCode);
void	KillPreviousDupProcess(void);
void	KillOtherProcesses(const QString &ProcessName);

int		MtEnumProcess(DWORD ProcessID[], int MaxCountOfProcessID);
bool	GetProcessName(int ProcessID ,QString &ProcessName);

class	QRect;
bool	GetWindowPosition(int ProcessID ,QRect &rect);
bool	SetWindowPosition(int ProcessID ,QRect &rect);
bool	SetWindowCmdShow(int ProcessID ,int nCmdShow);
bool	SetForegroundOtherWindow(int ProcessID);

#endif