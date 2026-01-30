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

#include "Windows.h"
#include <string.h>
#include <time.h>
#include <Psapi.h>
#include <QString>

bool	FindProcess(char *ProcessImageName);

// �E�B���h�E�n���h�����擾���A�v���P�[�V�������I���������B
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    // CreateProcess()�Ŏ擾����PROCESS_INFORMATION�\���̂̃|�C���^���擾
    PROCESS_INFORMATION* pi = (PROCESS_INFORMATION*)lParam;

    // �E�C���h�E���쐬�����v���Z�XID���擾�B
    DWORD lpdwProcessId = 0;
    ::GetWindowThreadProcessId(hWnd, &lpdwProcessId);

    // CreateProcess�ŋN�������A�v���̃v���Z�XID�ƃ��C���E�B���h�E��
    // �쐬�����v���Z�XID�������ꍇ�A�N�������A�v�����I���������B
    if(pi->dwProcessId == lpdwProcessId)
    {
        ::PostMessage(hWnd, WM_CLOSE, 0, 0);
        return false;
    }
    return TRUE;
}

bool	CloseProcessFunction(char *ProcessImageName ,int MaxWaitForTerminte)
{
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;
	bool	ClosedMode=false;

	// PID�ꗗ���擾
	if (!::EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return false;
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < nProc; i++) {

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE	,
			false, allProc[i]);

		// �v���Z�X�����擾
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				TCHAR procName[MAX_PATH] = TEXT("<unknown>");
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				QString	s=QString::fromWCharArray(procName);
				if(s.toLower()==QString(ProcessImageName).toLower()){
//					::TerminateProcess(hProcess,0);

					PROCESS_INFORMATION pi;
					pi.dwProcessId=allProc[i];
					// �R�[���o�b�N�֐��̌Ăяo���B
					EnumWindows(EnumWindowsProc, (LPARAM)&pi);
					ClosedMode=true;
				}
			}
	        CloseHandle(hProcess);
		}
    }
	if(ClosedMode==true){
		for(time_t t=time(NULL);time(NULL)-t<=MaxWaitForTerminte;){
			if(FindProcess(ProcessImageName)==false){
				break;
			}
		}
	}
	return true;
}

bool	FindProcess(char *ProcessImageName)
{
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;

	// PID�ꗗ���擾
	if (!::EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return false;
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < nProc; i++) {

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE	,
			false, allProc[i]);

		// �v���Z�X�����擾
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				TCHAR procName[MAX_PATH] = TEXT("<unknown>");
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				QString	s=QString::fromWCharArray(procName);
				if(s.toLower()==QString(ProcessImageName).toLower()){
					return true;
				}
			}
	        CloseHandle(hProcess);
		}
    }
	return false;
}