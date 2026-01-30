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

#include "XDirectoryAPI.h"

#include <windows.h>
#include <tchar.h>

bool IsEmptyDirectory(const QString &dirPath){
	const int buffSize = 1024;
	TCHAR *resBuff;

	// ���݃J�����g�f�B���N�g�����擾
	resBuff = new TCHAR[buffSize];
	DWORD dwNumb = GetCurrentDirectory(buffSize, resBuff);
	if(dwNumb==0){// �G���[
		delete []resBuff;
		return false;
	}else if(dwNumb>buffSize){// �o�b�t�@�s���G���[
		delete []resBuff;
		resBuff = new TCHAR[dwNumb];
		GetCurrentDirectory(dwNumb, resBuff);
	}
	
	// �J�����g�f�B���N�g�����ړ�
	if(SetCurrentDirectory(dirPath.toStdWString().data())==false){
		// �J�����g�f�B���N�g�������ɖ߂�
		SetCurrentDirectory(resBuff);

		// �o�b�t�@�̍폜
		delete []resBuff;	
		return false;
	}

	// �t�@�C�������邩�ǂ����𒲂ׂ�
	WIN32_FIND_DATA fd;
	bool res;
	HANDLE searchHdl = FindFirstFile(L"?*", &fd);// ������ [.] �� [..] ���}�b�`����

	// �L���ȃn���h���̏ꍇ�͊e�t�@�C�����m�F����
	if(searchHdl!=INVALID_HANDLE_VALUE){
		// �t�@�C���m�F
		QStringList ret;
		if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){// [.] �� [..]�łȂ��ꍇ�̓t�@�C������
			// �n���h���̃N���[�Y
			FindClose(searchHdl);

			// �J�����g�f�B���N�g�������ɖ߂�
			SetCurrentDirectory(resBuff);

			// �o�b�t�@�̍폜
			delete []resBuff;

			return false;
		}
	
		// �����擾���Ă���
		while( FindNextFile(searchHdl, &fd) ){
			if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
				// �n���h���̃N���[�Y
				FindClose(searchHdl);

				// �J�����g�f�B���N�g�������ɖ߂�
				SetCurrentDirectory(resBuff);

				// �o�b�t�@�̍폜
				delete []resBuff;

				return false;
			}
		}
		if( GetLastError() == ERROR_NO_MORE_FILES ){
			// �n���h���̃N���[�Y
			FindClose(searchHdl);

			// �J�����g�f�B���N�g�������ɖ߂�
			SetCurrentDirectory(resBuff);

			// �o�b�t�@�̍폜
			delete []resBuff;
			
			return true;
		}
	
	}


	// �J�����g�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(resBuff);

	// �o�b�t�@�̍폜
	delete []resBuff;

	return false;
}

QStringList GetDirectoryFileList(const QString &dirPath, const QString &wildCardFilter){
	QStringList ret;
	
	const int buffSize = 1024;
	TCHAR *resBuff;

	// ���݃J�����g�f�B���N�g�����擾
	resBuff = new TCHAR[buffSize];
	DWORD dwNumb = GetCurrentDirectory(buffSize, resBuff);
	if(dwNumb==0){// �G���[
		delete []resBuff;
		return QStringList();
	}else if(dwNumb>buffSize){// �o�b�t�@�s���G���[
		delete []resBuff;
		resBuff = new TCHAR[dwNumb];
		GetCurrentDirectory(dwNumb, resBuff);
	}

	// �J�����g�f�B���N�g�����ړ�
	SetCurrentDirectory(dirPath.toStdWString().data());

	// �t�@�C�������邩�ǂ����𒲂ׂ�
	WIN32_FIND_DATA fd;
	bool res;
	HANDLE searchHdl = FindFirstFile(wildCardFilter.toStdWString().data(), &fd);
	if(searchHdl==INVALID_HANDLE_VALUE){
		// �J�����g�f�B���N�g�������ɖ߂�
		SetCurrentDirectory(resBuff);

		// �o�b�t�@�̍폜
		delete []resBuff;

		return QStringList();
	}
	if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
		ret.append( QString::fromWCharArray(fd.cFileName, dwNumb) );
	}
	
	// �����擾���Ă���
	while( FindNextFile(searchHdl, &fd) ){
		if(wcscmp(fd.cFileName, L".")!=0 && wcscmp(fd.cFileName, L"..")!=0){
			ret.append( QString::fromWCharArray(fd.cFileName, dwNumb) );
		}
	}
	
	// �n���h���̃N���[�Y
	FindClose(searchHdl);
	
	// �J�����g�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(resBuff);
	
	// �o�b�t�@�̍폜
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