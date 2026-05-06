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

#pragma once


#include "XTypeDef.h"
#include <QString>

#ifndef SW_HIDE
#define SW_HIDE             0
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_MAXIMIZE         3
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_RESTORE          9
#endif

bool	MtGetVolumeInformation(
  QString RootPathName,				// ルートディレクトリ
  QString &RetVolumeNameBuffer,     // ボリューム名バッファ
  int32 &VolumeSerialNumber,		// ボリュームのシリアル番号
  int32 &MaximumComponentLength,	// ファイル名の最大の長さ
  int32 &FileSystemFlags,			// ファイルシステムのオプション
  QString &FileSystemNameBuffer		// ファイルシステム名を格納するバッファ
);


bool	MtShutdownSelfPC( bool BoolForciblyExitsOthers, bool BoolReboot );

bool	MtAdjustTime(int hour,int minute ,int second);
int64	MtGetDiskFreeSpace(char *DriveStr);
bool	MtGetComputerName(char CName[],int size);
bool	MtGetComputerName(QString &CName);
bool	GetProcessNames(QStringList &Processes);
bool	MTCopyFile(const QString &SourceFileName ,const QString &DestFileName ,bool failIfExist);
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
