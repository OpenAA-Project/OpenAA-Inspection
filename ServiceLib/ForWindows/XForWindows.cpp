/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XForWindows.h"
#ifdef _MSC_VER
#include "XTypeDef.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XGeneralFunc.h"
#include "Windows.h"

bool	_GetVolumeInformation(
  char *lpRootPathName,				// ルートディレクトリ
  char *lpVolumeNameBuffer,			// ボリューム名バッファ
  int32 nVolumeNameSize,            // 名前バッファのサイズ
  int32 &lpVolumeSerialNumber,		// ボリュームのシリアル番号
  int32 &lpMaximumComponentLength,	// ファイル名の最大の長さ
  int32 &lpFileSystemFlags,			// ファイルシステムのオプション
  char *lpFileSystemNameBuffer,		// ファイルシステム名を格納するバッファ
  int32 nFileSystemNameSize			// ファイルシステム名を格納するバッファのサイズ
);

bool	MtGetVolumeInformation(
  QString RootPathName,				// ルートディレクトリ
  QString &RetVolumeNameBuffer,		// ボリューム名バッファ
  int32 &VolumeSerialNumber,		// ボリュームのシリアル番号
  int32 &MaximumComponentLength,	// ファイル名の最大の長さ
  int32 &FileSystemFlags,			// ファイルシステムのオプション
  QString &FileSystemNameBuffer		// ファイルシステム名を格納するバッファ
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

bool	MtAdjustTime(int hour ,int minute ,int second)
{
	SYSTEMTIME	SystemTm;

	GetLocalTime(&SystemTm);

	SystemTm.wHour=hour;
	SystemTm.wMinute=minute;
	SystemTm.wSecond=second;

	SetLocalTime(&SystemTm);
	return true;
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
#else

#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <signal.h>
#include <time.h>
#include "XGeneralFuncCore.h"

#define PROC_DIRECTORY "/proc/"
#define CASE_SENSITIVE    1
#define CASE_INSENSITIVE  0
#define EXACT_MATCH       1
#define INEXACT_MATCH     0


#include <QString>
#include <QProcess>
#include <QCoreApplication>
#include <QStorageInfo>
#include <QByteArray>
#include <sys/statvfs.h>
#include <cstdint>

// 引数の int32 に対応するための typedef (環境に合わせて適宜 qint32 等に変更してください)
typedef int32_t int32;

bool MtGetVolumeInformation(
    QString RootPathName,           // ルートディレクトリ (例: "/", "/mnt/shared")
    QString &RetVolumeNameBuffer,   // ボリューム名バッファ
    int32 &VolumeSerialNumber,      // ボリュームのシリアル番号
    int32 &MaximumComponentLength,  // ファイル名の最大の長さ
    int32 &FileSystemFlags,         // ファイルシステムのオプション(フラグ)
    QString &FileSystemNameBuffer   // ファイルシステム名バッファ
)
{
    // 1. Qtの機能を使ってボリューム名(ラベル)とファイルシステム名を取得
    QStorageInfo storage(RootPathName);
    
    // パスが存在し、マウントされて準備ができているか確認
    if (!storage.isValid() || !storage.isReady()) {
        return false;
    }

    // ボリューム名 (Linuxではパーティションラベル)
    RetVolumeNameBuffer = storage.name();
    // ファイルシステム名 (例: "ext4", "vfat", "nfs" など)
    FileSystemNameBuffer = storage.fileSystemType();


    // 2. Linuxのシステムコール(statvfs)を使って詳細情報を取得
    struct statvfs st;
    QByteArray pathBytes = RootPathName.toLocal8Bit();
    
    if (statvfs(pathBytes.constData(), &st) != 0) {
        return false;
    }

    // ファイル名の最大の長さ (通常は 255)
    MaximumComponentLength = static_cast<int32>(st.f_namemax);

    // ファイルシステムのオプション/フラグ
    // ※Windowsのフラグ(FILE_CASE_SENSITIVE_SEARCH等)とは異なり、
    // Linuxでは ST_RDONLY(読み取り専用) や ST_NOSUID などのマウントフラグが入ります。
    FileSystemFlags = static_cast<int32>(st.f_flag);

    // ボリュームのシリアル番号の代替
    // LinuxにはWindowsのような32bitのシリアル番号の概念がないため、
    // 代わりにファイルシステムID (f_fsid) をキャストして使用します。
    VolumeSerialNumber = static_cast<int32>(st.f_fsid);

    return true;
}

bool MtShutdownSelfPC(bool BoolForciblyExitsOthers, bool BoolReboot)
{
    QString program;
    QStringList arguments;

    if (BoolReboot) {
        // --- 再起動 (Reboot) ---
        if (BoolForciblyExitsOthers) {
            // 他のプロセスを待たずに強制的に再起動
            program = "reboot";
            arguments << "-f"; 
        } else {
            // 通常の安全な再起動
            program = "shutdown";
            arguments << "-r" << "now";
        }
    } else {
        // --- シャットダウン (Shutdown) ---
        if (BoolForciblyExitsOthers) {
            // 他のプロセスを待たずに強制的に電源オフ
            program = "poweroff";
            arguments << "-f";
        } else {
            // 通常の安全なシャットダウン
            program = "shutdown";
            arguments << "-h" << "now";
        }
    }


    qint64 pid;
    bool success = QProcess::startDetached(program, arguments, QString(), &pid);

    if (success) {
        return true;
    } else {
        return false;
    }
}

bool MtAdjustTime(int hour, int minute, int second)
{
    // 1. 現在の時刻を取得（日付情報をそのまま保持するため）
    time_t now = time(nullptr);
    struct tm tm_info;

    // スレッドセーフな localtime_r を使用してローカルタイムを取得
    if (localtime_r(&now, &tm_info) == nullptr) {
        return false;
    }

    // 2. 引数の時間で上書き
    tm_info.tm_hour = hour;
    tm_info.tm_min = minute;
    tm_info.tm_sec = second;

    // 3. 構造体を Epoch タイム（1970年からの経過秒数）に変換
    struct timespec ts;
    ts.tv_sec = mktime(&tm_info);
    ts.tv_nsec = 0; // ミリ秒/ナノ秒は0にセット

    if (ts.tv_sec == -1) {
        return false;
    }

    // 4. Linuxのシステムコールで時刻を設定
    // CLOCK_REALTIME はシステムのリアルタイムクロック（カレンダー時刻）を指します
    if (clock_settime(CLOCK_REALTIME, &ts) == 0) {
		return true;
    } else {
        return false;
    }
}
int64 MtGetDiskFreeSpace(char *DriveStr)
{
    // 引数のNullチェック
    if (DriveStr == NULL) {
        return -1; 
    }

    struct statvfs stat;

    // statvfs関数でファイルシステムの統計情報を取得
    if (statvfs(DriveStr, &stat) != 0) {
        // パスが存在しない、またはアクセス権限がない場合はエラー
        perror("statvfs error");
        return -1;
    }

    int64 freeSpace = (int64)stat.f_bavail * (int64)stat.f_frsize;

    return freeSpace;
}

bool	MtGetComputerName(char CName[],int size)
{
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);

	strncpy(CName,hostname,size);
	return true;
}

bool	MtGetComputerName(QString &CName)
{
	char hostname[HOST_NAME_MAX];
	char username[LOGIN_NAME_MAX];
	gethostname(hostname, HOST_NAME_MAX);
	getlogin_r(username, LOGIN_NAME_MAX);

	CName=hostname;
	return true;
}

int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}


bool MTCopyFile(const QString &SourceFileName, const QString &DestFileName, bool failIfExist)
{
    // 1. コピー元ファイルの存在確認
    QFileInfo sourceInfo(SourceFileName);
    if (!sourceInfo.exists() || !sourceInfo.isFile()) {
        qWarning() << "コピー元ファイルが存在しないか、ファイルではありません:" << SourceFileName;
        return false;
    }

    // 2. コピー先ファイルの存在確認と failIfExist の処理
    QFile destFile(DestFileName);
    if (destFile.exists()) {
        if (failIfExist) {
            // 上書きしない設定（failIfExist == true）の場合、コピーを中止
            qWarning() << "コピー先ファイルが既に存在するため、コピーを中止しました:" << DestFileName;
            return false;
        } else {
            // 上書きする設定（failIfExist == false）の場合、既存のファイルを削除する
            // ※重要: QFile::copy() は上書き機能を持たないため、事前に削除する必要があります
            if (!destFile.remove()) {
                qWarning() << "既存ファイルの削除（上書き準備）に失敗しました:" << DestFileName;
                return false;
            }
        }
    } else {
        // コピー先のディレクトリが存在しないと QFile::copy は失敗するため、
        // 必要に応じて親ディレクトリを作成します
        QFileInfo destInfo(DestFileName);
        QDir destDir = destInfo.absoluteDir();
        if (!destDir.exists()) {
            if (!destDir.mkpath(".")) {
                qWarning() << "コピー先のディレクトリ作成に失敗しました:" << destDir.absolutePath();
                return false;
            }
        }
    }

    // 3. ファイルのコピーを実行
    // DestFileName に異なるファイル名を指定すれば、リネームコピーになります
    if (QFile::copy(SourceFileName, DestFileName)) {
        // 必要に応じて権限（パーミッション）を設定し直す場合
        // QFile::setPermissions(DestFileName, QFile::ReadOwner | QFile::WriteOwner);
        return true;
    } else {
        qWarning() << "ファイルのコピーに失敗しました。権限などを確認してください。";
        return false;
    }
}
DWORD	MtGetCurrentProcessId(void)
{
	pid_t pid=getpid();
	return (DWORD)pid;
}
bool	KillProcess(DWORD dwProcessId, unsigned int uExitCode)
{
	kill(dwProcessId,0);
	return true;
}
void	KillPreviousDupProcess(void)
{
}


void KillOtherProcesses(const QString &ProcessName)
{
    // ==========================================
    // ステップ1: pgrepコマンドで指定された名前のPID一覧を取得
    // -x オプション: プロセス名が完全に一致するもののみを対象にする
    // ==========================================
    QProcess pgrepProcess;
    pgrepProcess.start("pgrep", QStringList() << "-x" << ProcessName);
    pgrepProcess.waitForFinished(3000);

    // プロセスが見つからない場合は exitCode が 0 以外になります
    if (pgrepProcess.exitStatus() != QProcess::NormalExit || pgrepProcess.exitCode() != 0) {
        qDebug() << "終了対象のプロセスが見つかりませんでした:" << ProcessName;
        return;
    }

    // 標準出力からPIDのリスト（改行区切り）を取得
    QString output = pgrepProcess.readAllStandardOutput();

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStringList pidStrings = output.split('\n', Qt::SkipEmptyParts);
#else
    QStringList pidStrings = output.split('\n', QString::SkipEmptyParts);
#endif

    // ==========================================
    // ステップ2: 自分自身のPIDを取得
    // ==========================================
    // Qtの関数を使用（POSIX標準の getpid() でも同等です）
    qint64 myPid = QCoreApplication::applicationPid();

    // ==========================================
    // ステップ3: 自分以外のPIDに対して終了シグナルを送信
    // ==========================================
    for (const QString &pidStr : pidStrings) {
        bool ok;
        qint64 targetPid = pidStr.toLongLong(&ok);

        if (ok && targetPid > 0 && targetPid != myPid) {
            
            // kill関数はプロセスを強制終了する関数ではなく、「シグナルを送る」システムコールです。
            // SIGTERM (15): プロセスに終了を「要求」する（安全な終了）
            // SIGKILL (9): プロセスを「強制終了」する（保存していないデータは消える）
            
            if (kill(static_cast<pid_t>(targetPid), SIGTERM) == 0) {
                qDebug() << "プロセスに終了要求を送信しました。PID:" << targetPid;
            } else {
                qWarning() << "プロセスの終了に失敗しました。PID:" << targetPid 
                         << "（権限不足、または既に終了している可能性があります）";
            }
        }
    }
}

int MtEnumProcess(DWORD ProcessID[], int MaxCountOfProcessID)
{
    char chrarry_CommandLinePath[100];
    char chrarry_NameOfProcess[300];
    pid_t pid_ProcessIdentifier = (pid_t) -1;
    int PidCount = 0;
    struct dirent* de_DirEntity = NULL;
    DIR* dir_proc = NULL;

    dir_proc = opendir(PROC_DIRECTORY);
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory");
        return 0;
    }

    // Loop while not NULL
    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(chrarry_CommandLinePath, PROC_DIRECTORY);
                strcat(chrarry_CommandLinePath, de_DirEntity->d_name);
                strcat(chrarry_CommandLinePath, "/cmdline");
                
                FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt");
                if (fd_CmdLineFile)
                {
                    // fscanfの戻り値をチェック
                    if (fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) == 1) {
                        pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name);
                        
                        if (PidCount < MaxCountOfProcessID) {
                            ProcessID[PidCount] = pid_ProcessIdentifier;
                            PidCount++;
                        } else {
                            fclose(fd_CmdLineFile);
                            break; // 上限に達したらループを抜ける
                        }
                    }
                    fclose(fd_CmdLineFile);
                    // 【修正】ここにあった closedir(dir_proc); も削除しました
                }
            }
        }
    }
    closedir(dir_proc); // 正しいクローズ位置
    
    return PidCount;
}
bool GetProcessName(int ProcessID, QString &ProcessName)
{
    // 1. 読み込むファイルのパスを構築 (例: PIDが1234なら "/proc/1234/comm")
    QString path = QString("/proc/%1/comm").arg(ProcessID);

    // 2. ファイルを開く
    QFile file(path);
    // 読み取り専用のテキストモードで開く
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // PIDが存在しない、またはアクセス権限がない場合は失敗
        qWarning() << "プロセスの情報を取得できません。PID:" << ProcessID;
        return false;
    }

    // 3. 中身（プロセス名）を読み取る
    QTextStream in(&file);
    QString name = in.readLine();

    if (name.isNull() || name.isEmpty()) {
        qWarning() << "プロセス名が空です。PID:" << ProcessID;
        return false;
    }

    // 4. 改行コードなどを取り除いて引数の変数に格納
    ProcessName = name.trimmed();

    return true;
}

bool GetWindowPosition(int ProcessID, QRect &rect)
{
    // wmctrlコマンドを実行して、全ウィンドウの詳細情報リストを取得する
    // オプション: 
    // -l : ウィンドウ一覧を出力
    // -p : PIDを含める
    // -G : ジオメトリ(X, Y, 幅, 高さ)を含める
    QProcess process;
    process.start("wmctrl", QStringList() << "-l" << "-p" << "-G");
    process.waitForFinished(3000); // 最大3秒待機

    // コマンドが正常終了したか確認
    if (process.exitStatus() != QProcess::NormalExit || process.exitCode() != 0) {
        qWarning() << "wmctrl コマンドの実行に失敗しました。パッケージがインストールされているか確認してください。";
        return false;
    }

    // 標準出力をすべて読み込む
    QString output = process.readAllStandardOutput();
    
    // 行ごとに分割
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
#else
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
#endif

    for (const QString &line : lines) {
        // line.simplified() で余分な空白やタブを単一のスペースに変換してから分割
        QStringList parts = line.simplified().split(' ');

        // wmctrl -l -p -G の出力フォーマットは以下の通り:
        // [0]WindowID [1]DesktopID [2]PID [3]X [4]Y [5]Width [6]Height [7]Machine [8...]Title
        if (parts.size() >= 7) {
            bool ok;
            int currentPid = parts[2].toInt(&ok);

            // 対象のPIDと一致するかチェック
            if (ok && currentPid == ProcessID) {
                int x = parts[3].toInt();
                int y = parts[4].toInt();
                int w = parts[5].toInt();
                int h = parts[6].toInt();

                rect.setRect(x, y, w, h);
                return true; // 該当するウィンドウを見つけたら終了
            }
        }
    }

    // 指定されたPIDのウィンドウが見つからなかった場合
    qWarning() << "指定された PID のウィンドウが見つかりません。PID:" << ProcessID;
    return false;
}

bool SetWindowPosition(int ProcessID, QRect &rect)  //Does not work in Wayland
{
    // ==========================================
    // ステップ1: PIDから対象の「ウィンドウID」を取得する
    // ==========================================
    QProcess getProcess;
    // -l: ウィンドウリスト, -p: PIDを表示
    getProcess.start("wmctrl", QStringList() << "-l" << "-p");
    getProcess.waitForFinished(3000);

    if (getProcess.exitStatus() != QProcess::NormalExit || getProcess.exitCode() != 0) {
        qWarning() << "wmctrl コマンドの実行に失敗しました。パッケージがインストールされているか確認してください。";
        return false;
    }

    QString output = getProcess.readAllStandardOutput();
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
#else
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
#endif

    QString targetWindowId = "";

    // リストから対象のPIDを探す
    for (const QString &line : lines) {
        QStringList parts = line.simplified().split(' ');
        if (parts.size() >= 3) {
            bool ok;
            int currentPid = parts[2].toInt(&ok);
            if (ok && currentPid == ProcessID) {
                targetWindowId = parts[0]; // 例: "0x04000003" などの16進数文字列
                break;                     // 最初に見つかったウィンドウを対象とする
            }
        }
    }

    if (targetWindowId.isEmpty()) {
        qWarning() << "指定された PID のウィンドウが見つかりません。PID:" << ProcessID;
        return false;
    }

    // ==========================================
    // ステップ2: 取得したウィンドウIDに対して位置とサイズを設定する
    // ==========================================
    // wmctrl -e オプションのフォーマット: <gravity>,<X>,<Y>,<Width>,<Height>
    // ※ gravity に 0 を指定すると、ウィンドウマネージャのデフォルト設定を使用します。
    QString geometryStr = QString("0,%1,%2,%3,%4")
                              .arg(rect.x())
                              .arg(rect.y())
                              .arg(rect.width())
                              .arg(rect.height());

    QStringList setArgs;
    // -i : 対象をウィンドウIDの数値として解釈する
    // -r : 対象のウィンドウを指定
    // -e : ジオメトリ（位置とサイズ）を設定
    setArgs << "-i" << "-r" << targetWindowId << "-e" << geometryStr;

    QProcess setProcess;
    setProcess.start("wmctrl", setArgs);
    setProcess.waitForFinished(3000);

    if (setProcess.exitStatus() == QProcess::NormalExit && setProcess.exitCode() == 0) {
        qDebug() << "ウィンドウの位置とサイズを設定しました。PID:" << ProcessID;
        return true;
    } else {
        qWarning() << "ウィンドウの設定に失敗しました。エラー:" << setProcess.readAllStandardError();
        return false;
    }
}
bool SetWindowCmdShow(int ProcessID,int nCmdShow)  //Does not work in Wayland
{
    // ==========================================
    // ステップ1: PIDから対象の「ウィンドウID」を取得する
    // ==========================================
    QProcess getProcess;
    getProcess.start("wmctrl", QStringList() << "-l" << "-p");
    getProcess.waitForFinished(3000);

    if (getProcess.exitStatus() != QProcess::NormalExit || getProcess.exitCode() != 0) {
        qWarning() << "wmctrl コマンドの実行に失敗しました。";
        return false;
    }

    QString output = getProcess.readAllStandardOutput();
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);
#else
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
#endif

    QString targetWindowId = "";

    for (const QString &line : lines) {
        QStringList parts = line.simplified().split(' ');
        if (parts.size() >= 3) {
            bool ok;
            int currentPid = parts[2].toInt(&ok);
            if (ok && currentPid == ProcessID) {
                targetWindowId = parts[0]; // ウィンドウID (例: 0x04000003)
                break;
            }
        }
    }

    if (targetWindowId.isEmpty()) {
        qWarning() << "指定された PID のウィンドウが見つかりません。PID:" << ProcessID;
        return false;
    }

    // ==========================================
    // ステップ2: nCmdShow の値に応じてコマンドを発行する
    // ==========================================
    QString program;
    QStringList args;

    switch (nCmdShow) {
        case SW_MAXIMIZE:
            // 最大化: wmctrl に「縦・横の最大化プロパティを追加」と指示
            program = "wmctrl";
            args << "-i" << "-r" << targetWindowId << "-b" << "add,maximized_vert,maximized_horz";
            break;

        case SW_NORMAL:
        case SW_RESTORE:
            // 元に戻す: wmctrl に「最大化プロパティを削除」と指示し、アクティブにする
            QProcess::execute("wmctrl", QStringList() << "-i" << "-r" << targetWindowId << "-b" << "remove,maximized_vert,maximized_horz");
            program = "wmctrl";
            args << "-i" << "-a" << targetWindowId; // ウィンドウを最前面にしてアクティブ化
            break;

        case SW_MINIMIZE:
        case SW_SHOWMINIMIZED:
            // 最小化: wmctrl には確実な最小化コマンドがないため xdotool を使用
            program = "xdotool";
            args << "windowminimize" << targetWindowId;
            break;

        case SW_HIDE:
            // 非表示: xdotool を使用してウィンドウのマップ（描画）を解除
            program = "xdotool";
            args << "windowunmap" << targetWindowId;
            break;

        case SW_SHOW:
            // 表示: xdotool でマップし、wmctrl でアクティブにする
            QProcess::execute("xdotool", QStringList() << "windowmap" << targetWindowId);
            program = "wmctrl";
            args << "-i" << "-a" << targetWindowId;
            break;

        default:
            qWarning() << "サポートされていない nCmdShow の値です:" << nCmdShow;
            return false;
    }

    // コマンドの実行
    QProcess setProcess;
    setProcess.start(program, args);
    setProcess.waitForFinished(3000);

    if (setProcess.exitStatus() == QProcess::NormalExit && setProcess.exitCode() == 0) {
        qDebug() << "ウィンドウの状態を変更しました。PID:" << ProcessID << "State:" << nCmdShow;
        return true;
    } else {
        qWarning() << "ウィンドウ状態の変更に失敗しました。エラー:" << setProcess.readAllStandardError();
        return false;
    }
}

#endif
