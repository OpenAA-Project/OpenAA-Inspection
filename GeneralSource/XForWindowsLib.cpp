
#ifdef _MSC_VER
#include "XTypeDef.h"
#include <cmath>
#include <windows.h>
#include "XForWindows.h"


bool	_GetVolumeInformation(
  char *lpRootPathName,           // ルートディレクトリ
  char *lpVolumeNameBuffer,        // ボリューム名バッファ
  int32 nVolumeNameSize,            // 名前バッファのサイズ
  int32 &lpVolumeSerialNumber,     // ボリュームのシリアル番号
  int32 &lpMaximumComponentLength, // ファイル名の最大の長さ
  int32 &lpFileSystemFlags,        // ファイルシステムのオプション
  char *lpFileSystemNameBuffer,    // ファイルシステム名を格納するバッファ
  int32 nFileSystemNameSize       // ファイルシステム名を格納するバッファのサイズ
)
{
	static	DWORD	ErrorCode;

	bool	ret=::GetVolumeInformationA(
			(LPCSTR)lpRootPathName,						// ルートディレクトリ
			(LPSTR)lpVolumeNameBuffer,        // ボリューム名バッファ
			nVolumeNameSize,            // 名前バッファのサイズ
			(LPDWORD)&lpVolumeSerialNumber,     // ボリュームのシリアル番号
			(LPDWORD)&lpMaximumComponentLength, // ファイル名の最大の長さ
			(LPDWORD)&lpFileSystemFlags,        // ファイルシステムのオプション
			(LPSTR)lpFileSystemNameBuffer,    // ファイルシステム名を格納するバッファ
			nFileSystemNameSize);
	if(ret==false){
		ErrorCode=::GetLastError();
	}
	return ret;
}

#endif