/*
 * Copyright (C) 2021
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



#include "XNetworkDrive.h"
#include <QString>
#include <QProcess>
#include <QDir>
#include <QDebug>

#ifdef _MSC_VER
#include <windows.h>

#define	DEFFUNCEX		__declspec(dllexport) 


extern	"C"{

DEFFUNCEX	bool	CreateNetworkDrive(bool tInitialConnect 
						//,int DriveCode				//A drive=0 ,B drive=1 ,,, Z drive=25
						,const QString &DriveNameStr	//Windows:"Z:" ,Linux:"/mnt/xxx"
						,const QString  &tRemoteDiskName
						,const QString  &tPassword
						,const QString  &tUserName);
DEFFUNCEX	bool	DisconnectNetworkDrive(const QString &DriveNameStr);	//Windows:"Z:" ,Linux:"/mnt/xxx"

};
bool	CreateNetworkDrive(bool tInitialConnect 
						,const QString &DriveNameStr
						,const QString &tRemoteDiskName
						,const QString &tPassword
						,const QString &tUserName)
{
    NETRESOURCE nr;
	memset(&nr,0,sizeof(nr));
    WCHAR    DriveName[10240];
	memset(DriveName,0,sizeof(DriveName));

	DriveNameStr.toCaseFolded().toWCharArray (DriveName);

    nr.dwType=RESOURCETYPE_DISK;
    nr.lpLocalName=DriveName;
	wchar_t	tRemoteDiskNameBuff[256];
	memset(tRemoteDiskNameBuff,0,sizeof(tRemoteDiskNameBuff));
	tRemoteDiskName.toWCharArray (tRemoteDiskNameBuff);
	for(int i=0;i<wcslen(tRemoteDiskNameBuff);i++){
		if(tRemoteDiskNameBuff[i]=='/'){
			tRemoteDiskNameBuff[i]='\\';
		}
	}
	nr.lpRemoteName   =tRemoteDiskNameBuff;
    nr.lpProvider=NULL;
    if(tInitialConnect==true){
		if((tPassword.length()==0)
		&& (tUserName.length()==0)){
			if(::WNetAddConnection2(&nr ,NULL
				,NULL,CONNECT_UPDATE_PROFILE)==NO_ERROR){
                return(true);
			}
		}
		else{
			wchar_t	tPasswordBuff[256];
			memset(tPasswordBuff,0,sizeof(tPasswordBuff));
			tPassword.toWCharArray (tPasswordBuff);
			wchar_t	tUserNameBuff[256];
			memset(tUserNameBuff,0,sizeof(tUserNameBuff));
			tUserName.toWCharArray (tUserNameBuff);
			if(::WNetAddConnection2(&nr ,tPasswordBuff
				,tUserNameBuff,CONNECT_UPDATE_PROFILE)==NO_ERROR){
				return(true);
			}
		}
	}
    else{
		if((tPassword.length()==0)
		&& (tUserName.length()==0)){
			if(::WNetAddConnection2(&nr ,NULL
				,NULL,0)==NO_ERROR){
				return(true);
			}
		}
		else{
			wchar_t	tPasswordBuff[256];
			memset(tPasswordBuff,0,sizeof(tPasswordBuff));
			tPassword.toWCharArray (tPasswordBuff);
			wchar_t	tUserNameBuff[256];
			memset(tUserNameBuff,0,sizeof(tUserNameBuff));
			tUserName.toWCharArray (tUserNameBuff);
			if(::WNetAddConnection2(&nr ,tPasswordBuff
				,tUserNameBuff,0)==NO_ERROR){
				return(true);
			}
		}
	}
	return(false);

}

bool	DisconnectNetworkDrive(const QString &DriveNameStr)
{
    WCHAR    DriveName[10240];
	memset(DriveName,0,sizeof(DriveName));

	DriveNameStr.toCaseFolded().toWCharArray (DriveName);

	WNetCancelConnection2(DriveName,0,false);

	return true;
}

#else
bool	CreateNetworkDrive(bool tInitialConnect 
						,const QString &DriveNameStr	//Windows:"Z:" ,Linux:"/mnt/xxx"
						,const QString &tRemoteDiskName
						,const QString &tPassword
						,const QString &tUserName)
{
    // 1. マウントポイント（ディレクトリ）の存在確認と作成
    // Linuxではマウント先の空ディレクトリが事前に必要です
    QDir mountDir(DriveNameStr);
    if (!mountDir.exists()) {
        if (!mountDir.mkpath(".")) {
            qWarning() << "マウントポイントの作成に失敗しました:" << DriveNameStr;
            return false;
        }
    }

    // 2. mountコマンドの引数準備
    // 実行コマンドのイメージ: mount -t cifs -o username=user,password=pass //server/share /mnt/xxx
    QString program = "mount";
    QStringList arguments;
    
    arguments << "-t" << "cifs";
    
    // 認証情報などのオプション
    // ※ファイルの読み書き権限を持たせるため、必要に応じて "uid=1000,gid=1000" などのオプションを追記します
    QString options = QString("username=%1,password=%2").arg(tUserName, tPassword);
    arguments << "-o" << options;
    
    arguments << tRemoteDiskName; // 例: //192.168.1.100/share
    arguments << DriveNameStr;    // 例: /mnt/xxx

    // 3. プロセスの実行
    QProcess process;
    process.start(program, arguments);
    process.waitForFinished(-1); // コマンドが終了するまで待機

    // 4. 結果の判定
    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        return true;
    } else {
        return false;
    }
}
bool	DisconnectNetworkDrive(const QString &DriveNameStr)
{
// 1. 対象のディレクトリ（マウントポイント）が存在するか確認
    QDir mountDir(DriveNameStr);
    if (!mountDir.exists()) {
        qWarning() << "指定されたマウントポイントが存在しません:" << DriveNameStr;
        // 既に切断（削除）されているとみなして true を返すか、エラーとして false を返すかは仕様によります。
        // ここでは処理失敗として false を返します。
        return false;
    }

    // 2. umount コマンドの準備
    // 実行コマンドのイメージ: umount /mnt/xxx
    QString program = "umount";
    QStringList arguments;
    arguments << DriveNameStr; // 例: /mnt/xxx

    // 強制的にアンマウントしたい場合は "-f" や "-l" (lazy unmount) オプションを追加することもできます。
    // arguments << "-l" << DriveNameStr;

    // 3. プロセスの実行
    QProcess process;
    process.start(program, arguments);
    process.waitForFinished(-1); // コマンドが終了するまで待機

    // 4. 結果の判定
    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        return true;
    } else {
        return false;
    }
}

#endif