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

#include "XAutoStart.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"
#ifdef _MSC_VER
#include "Windows.h"
#endif

#include <QApplication>
#include <QGuiApplication>


AutoStartExecution::AutoStartExecution(void)
{	
	Location		=0;
	BootingWaitTime	=1000;
	PID				=0;
	ExitCode		=0;
}

void	AutoStartExecution::SetParent(QObject *parent)
{
	setParent(parent);
	Process.setParent(this);
}

bool	AutoStartExecution::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,ExeFilePath)==false){
		return false;
	}
	if(::Save(f,Parameter)==false){
		return false;
	}
	if(::Save(f,WorkingPath)==false){
		return false;
	}
	if(::Save(f,Location)==false){
		return false;
	}
	if(::Save(f,BootingWaitTime)==false){
		return false;
	}
	return true;
}
bool	AutoStartExecution::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,ExeFilePath)==false){
		return false;
	}
	if(::Load(f,Parameter)==false){
		return false;
	}
	if(::Load(f,WorkingPath)==false){
		return false;
	}
	if(::Load(f,Location)==false){
		return false;
	}
	if(::Load(f,BootingWaitTime)==false){
		return false;
	}
	return true;
}
bool	AutoStartExecution::StartProgram(void)
{
	if(WorkingPath.isEmpty()==false)
		Process.setWorkingDirectory(WorkingPath);
	bool	Ret=connect(&Process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
	Process.start(ExeFilePath,Parameter.split(" "));
	PID	=Process.processId();
	PrID=Process.processId();
	return true;
}

void AutoStartExecution::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit) {
        mExitCode=exitCode;
    } else {
        mExitCode=exitCode;
    }
    
}
bool	AutoStartExecution::IsFinished(void)
{
	if(PID!=0){
#ifdef _MSC_VER
			QString ProcessName;
			PROCESS_INFORMATION *pi=(PROCESS_INFORMATION *)PID;
			if(::GetProcessName(pi->dwProcessId ,ProcessName)==true)
				return false;
#else

		QString procPath = QString("/proc/%1").arg(PID);
		QDir procDir(procPath);
    
		return procDir.exists();
#endif
	}
	return true;
}

int		AutoStartExecution::GetExitCode(void)
{
#ifdef _MSC_VER
	PROCESS_INFORMATION *pi=(PROCESS_INFORMATION *)PID;
	if(pi!=NULL){
		DWORD lpExitCode;
		if(::GetExitCodeProcess(pi->hProcess,&lpExitCode)!=0)
			return lpExitCode;
	}
	return 0;
#else
		return mExitCode;
#endif
}

void	AutoStartExecution::Close(void)
{
	Process.close();
}
void	AutoStartExecution::WaitForStarted(void)
{
	while(Process.waitForStarted(-1)==false){
		QApplication::processEvents();
	}
}
void	AutoStartExecution::ResizeAlignment(QRect &Rect)
{
#ifdef _MSC_VER
	PROCESS_INFORMATION *pi=(PROCESS_INFORMATION *)PID;
		
	QRect rect;
	bool	Ret=true;
	do{
		while(GetWindowPosition(pi->dwProcessId ,rect)==false){
			QApplication::processEvents();
		}
		GSleep(BootingWaitTime);
		QApplication::processEvents();
	}while(GetWindowPosition(pi->dwProcessId ,rect)==false);

	int	W=rect.width();
	int	H=rect.height();
	switch(Location){
		case 1:
			rect.setLeft(0);
			rect.setWidth(W);
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setLeft(rect.width());
				Rect.setWidth(Rect.width()-rect.width());
			}
			break;
		case 2:
			rect.setLeft(Rect.width()-rect.width());
			rect.setWidth(W);
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setWidth(Rect.width()-rect.width());
			}
			break;
		case 3:
			rect.setTop(0);
			rect.setHeight(H);
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setTop(rect.height());
				Rect.setHeight(Rect.height()-rect.height());
			}
			break;
		case 4:
			rect.setBottom(Rect.height()-rect.height());
			rect.setHeight(H);
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setHeight(Rect.height()-rect.height());
			}
			break;
		case 5:
			rect=Rect;
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setWidth(0);
				Rect.setHeight(0);
			}
			break;
		case 6:
			rect.setLeft(0);
			rect.setWidth(W);
			rect.setTop(0);
			rect.setHeight(Rect.height());
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setLeft(rect.width());
				Rect.setWidth(Rect.width()-rect.width());
			}
			break;
		case 7:
			rect.setLeft(Rect.width()-rect.width());
			rect.setWidth(W);
			rect.setTop(0);
			rect.setHeight(Rect.height());
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setWidth(Rect.width()-rect.width());
			}
			break;
		case 8:
			rect.setTop(0);
			rect.setHeight(H);
			rect.setLeft(0);
			rect.setWidth(Rect.width());
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setTop(rect.height());
				Rect.setHeight(Rect.height()-rect.height());
			}
			break;
		case 9:
			rect.setBottom(Rect.height()-rect.height());
			rect.setHeight(H);
			rect.setLeft(0);
			rect.setWidth(Rect.width());
			while((Ret=SetWindowPosition(pi->dwProcessId ,rect))==false){
				QApplication::processEvents();
			}
			if(Ret==true){
				Rect.setHeight(Rect.height()-rect.height());
			}
			break;
	}
#else
    QString output = QString::fromUtf8(Process.readAllStandardOutput()).trimmed();
    
    if (output.isEmpty()) {
        return;
    }

    // 1つのPIDに対して複数のウィンドウ(非表示のダイアログなど)が存在する場合があるため、最初のIDを取得
    QStringList windowIds = output.split('\n');
    QString mainWindowId = windowIds.first(); 

    // 2. 取得したウィンドウIDに対して、移動とリサイズを実行する
    QProcess modifyProcess;
    QStringList args;
    // コマンド: xdotool windowmove <WID> <X> <Y> windowsize <WID> <W> <H>
    args << "windowmove" << mainWindowId << QString::number(Rect.x()) << QString::number(Rect.y())
         << "windowsize" << mainWindowId << QString::number(Rect.width()) << QString::number(Rect.height());

    modifyProcess.start("xdotool", args);
 
    modifyProcess.waitForFinished(3000);
#endif
}

AutoStartExeList::AutoStartExeList(const AutoStartExeList &src)
{
	operator=(src);
	LoopCount=src.LoopCount;
}
bool	AutoStartExeList::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,LoopCount)==false){
		return false;
	}
	if(::Save(f,AllDesktopArea)==false){
		return false;
	}
	if(::Save(f,AreaLeft)==false){
		return false;
	}
	if(::Save(f,AreaTop)==false){
		return false;
	}
	if(::Save(f,AreaRight)==false){
		return false;
	}
	if(::Save(f,AreaBottom)==false){
		return false;
	}
	if(::Save(f,Tasktray)==false){
		return false;
	}

	if(NPListPackSaveLoad<AutoStartExecution>::Save(f)==false)
		return false;
	return true;
}
bool	AutoStartExeList::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,LoopCount)==false){
		return false;
	}
	if(Ver>=2){
		if(::Load(f,AllDesktopArea)==false){
			return false;
		}
		if(::Load(f,AreaLeft)==false){
			return false;
		}
		if(::Load(f,AreaTop)==false){
			return false;
		}
		if(::Load(f,AreaRight)==false){
			return false;
		}
		if(::Load(f,AreaBottom)==false){
			return false;
		}
		if(::Load(f,Tasktray)==false){
			return false;
		}
	}
	if(NPListPackSaveLoad<AutoStartExecution>::Load(f)==false)
		return false;
	return true;
}

void	AutoStartExeList::SetParent(QObject *parent)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->SetParent(parent);
	}
}

bool	AutoStartExeList::SaveDefault(void)
{
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		return Save(&File);
	}
	return false;
}
bool	AutoStartExeList::LoadDefault(void)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		return Load(&File);
	}
	return false;
}

bool	AutoStartExeList::IsFinishedAll(void)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->IsFinished()==false){
			return false;
		}
	}
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->ExitCode=a->GetExitCode();
	}
	return true;
}

bool	AutoStartExeList::StartImmediately(void)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ExitCode==-100){
			return true;
		}
	};
	return false;
}

bool	AutoStartExeList::ExecuteAll(void)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->StartProgram();
	}
	return true;
}

void	AutoStartExeList::CloseAll(void)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Close();
	}
}

void	AutoStartExeList::WaitForStarted(void)
{
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->WaitForStarted();
	}
}
void	AutoStartExeList::ResizeAlignment(void)
{
	QScreen	*Scr=qGuiApp->screens()[0];
	QRect	Rect(Scr->geometry());

	if(AllDesktopArea==false){
		Rect.setLeft	(AreaLeft);
		Rect.setTop		(AreaTop);
		Rect.setRight	(AreaRight);
		Rect.setBottom	(AreaBottom);
	}
	for(AutoStartExecution *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->ResizeAlignment(Rect);
	}
}


/*
//�����̃v���O�����̃E�C���h�E������--------------------------------------------------

#include <stdio.h>
#include <windows.h>

BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	char buff[256]="";
	GetWindowText( hWnd,buff, sizeof(buff));//�E�B���h�E�����擾
	printf("%s\n",buff);
	return true;
}

int main(int argc, char* argv[])
{
	EnumWindows( EnumWndProc, (LPARAM)NULL );
	return 0;
}


//�����̃v���O�����̃E�C���h�E�T�C�Y���ύX-------------------------------------------

#include <stdio.h>
#include <windows.h>

BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	char buff[256]="";
	GetWindowText( hWnd,buff, sizeof(buff));
	if(strcmp(buff,(char*)lParam)==0){//���O�����v�������A
		SetWindowPos(hWnd,HWND_TOP,0 ,0 ,100,100,SWP_SHOWWINDOW);//�E�C���h�E�̈ʒu�ƃT�C�Y���ύX
	}
	return true;
}

int main(int argc, char* argv[])
{
	LPARAM lParam=(LPARAM)"���� - ������";//���������E�B���h�E�̖��O
	EnumWindows( EnumWndProc, (LPARAM)lParam);
	return 0;
}

//�����̃v���O�����̃E�C���h�E�n���h�����擾����----------------------------------------

#include <stdio.h>
#include <string.h>
#include <windows.h>

struct  cell{
	HWND hWnd;
	char WindowName[256];
};

BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	char buff[256]="";
	GetWindowText( hWnd,buff, sizeof(buff));//�E�C���h�E�̕������擾���āA
	if(strcmp(buff,((cell*)lParam)->WindowName)==0){//���O�����v�������A
		((cell*)lParam)->hWnd = hWnd;//�E�B���h�E�n���h�����n��
	}
	return true;
}

int main(int argc, char* argv[])
{
	cell c;
	c.hWnd =NULL;
	strcpy(c.WindowName,"���� - ������");//���������E�B���h�E�̖��O

	EnumWindows( EnumWndProc, (LPARAM)&c);

	if(c.hWnd != NULL){
		//�ړI�̃E�C���h�E�n���h�����擾�ł��܂���
		SetWindowPos(c.hWnd,HWND_TOP,0 ,0 ,100,100,SWP_SHOWWINDOW);//�E�C���h�E�̃T�C�Y���ύX
	}
	return 0;
}

*/