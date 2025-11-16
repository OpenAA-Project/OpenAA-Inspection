#include "XDirectoryAPI.h"

#include <windows.h>
#include <tchar.h>

bool IsEmptyDirectory(const QString &dirPath){
	const int buffSize = 1024;
	TCHAR *resBuff;

	// 現在カレントディレクトリを取得
	resBuff = new TCHAR[buffSize];
	DWORD dwNumb = GetCurrentDirectory(buffSize, resBuff);
	if(dwNumb==0){// エラー
		delete []resBuff;
		return false;
	}else if(dwNumb>buffSize){// バッファ不足エラー
		delete []resBuff;
		resBuff = new TCHAR[dwNumb];
		GetCurrentDirectory(dwNumb, resBuff);
	}
	
	// カレントディレクトリを移動
	if(SetCurrentDirectory(dirPath.toStdWString().data())==false){
		// カレントディレクトリを元に戻す
		SetCurrentDirectory(resBuff);

		// バッファの削除
		delete []resBuff;	
		return false;
	}

	// ファイルがあるかどうかを調べる
	WIN32_FIND_DATA fd;
	bool res;
	HANDLE searchHdl = FindFirstFile(L"?*", &fd);// これは [.] や [..] もマッチする

	// 有効なハンドルの場合は各ファイルを確認する
	if(searchHdl!=INVALID_HANDLE_VALUE){
		// ファイル確認
		QStringList ret;
		if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){// [.] や [..]でない場合はファイルあり
			// ハンドルのクローズ
			FindClose(searchHdl);

			// カレントディレクトリを元に戻す
			SetCurrentDirectory(resBuff);

			// バッファの削除
			delete []resBuff;

			return false;
		}
	
		// 逐次取得していく
		while( FindNextFile(searchHdl, &fd) ){
			if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
				// ハンドルのクローズ
				FindClose(searchHdl);

				// カレントディレクトリを元に戻す
				SetCurrentDirectory(resBuff);

				// バッファの削除
				delete []resBuff;

				return false;
			}
		}
		if( GetLastError() == ERROR_NO_MORE_FILES ){
			// ハンドルのクローズ
			FindClose(searchHdl);

			// カレントディレクトリを元に戻す
			SetCurrentDirectory(resBuff);

			// バッファの削除
			delete []resBuff;
			
			return true;
		}
	
	}


	// カレントディレクトリを元に戻す
	SetCurrentDirectory(resBuff);

	// バッファの削除
	delete []resBuff;

	return false;
}

QStringList GetDirectoryFileList(const QString &dirPath, const QString &wildCardFilter){
	QStringList ret;
	
	const int buffSize = 1024;
	TCHAR *resBuff;

	// 現在カレントディレクトリを取得
	resBuff = new TCHAR[buffSize];
	DWORD dwNumb = GetCurrentDirectory(buffSize, resBuff);
	if(dwNumb==0){// エラー
		delete []resBuff;
		return QStringList();
	}else if(dwNumb>buffSize){// バッファ不足エラー
		delete []resBuff;
		resBuff = new TCHAR[dwNumb];
		GetCurrentDirectory(dwNumb, resBuff);
	}

	// カレントディレクトリを移動
	SetCurrentDirectory(dirPath.toStdWString().data());

	// ファイルがあるかどうかを調べる
	WIN32_FIND_DATA fd;
	bool res;
	HANDLE searchHdl = FindFirstFile(wildCardFilter.toStdWString().data(), &fd);
	if(searchHdl==INVALID_HANDLE_VALUE){
		// カレントディレクトリを元に戻す
		SetCurrentDirectory(resBuff);

		// バッファの削除
		delete []resBuff;

		return QStringList();
	}
	if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
		ret.append( QString::fromWCharArray(fd.cFileName, dwNumb) );
	}
	
	// 逐次取得していく
	while( FindNextFile(searchHdl, &fd) ){
		if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
			ret.append( QString::fromWCharArray(fd.cFileName, dwNumb) );
		}
	}
	
	// ハンドルのクローズ
	FindClose(searchHdl);
	
	// カレントディレクトリを元に戻す
	SetCurrentDirectory(resBuff);
	
	// バッファの削除
	delete []resBuff;

	return ret;
}

bool DeleteFileApi(const QString &filename){
	BOOL ok = DeleteFile(filename.toStdWString().data());
	return (ok==TRUE);
}

bool RemoveDirectoryApi(const QString &directoryPath)
{
	BOOL ret = RemoveDirectory(directoryPath.toStdWString().data());
	return (ret==TRUE);
}