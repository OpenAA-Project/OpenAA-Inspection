#include "XAutoStart.h"
#include "XGeneralFunc.h"
#include "XForWindows.h"
#include "Windows.h"
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
}

bool	AutoStartExecution::IsFinished(void)
{
	if(PID!=0){
		QString ProcessName;
		PROCESS_INFORMATION *pi=(PROCESS_INFORMATION *)PID;
		if(::GetProcessName(pi->dwProcessId ,ProcessName)==true)
			return false;
	}
	return true;
}

int		AutoStartExecution::GetExitCode(void)
{
	PROCESS_INFORMATION *pi=(PROCESS_INFORMATION *)PID;
	if(pi!=NULL){
		DWORD lpExitCode;
		if(::GetExitCodeProcess(pi->hProcess,&lpExitCode)!=0)
			return lpExitCode;
	}
	return 0;
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
//○他のプログラムのウインドウを列挙--------------------------------------------------

#include <stdio.h>
#include <windows.h>

BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	char buff[256]="";
	GetWindowText( hWnd,buff, sizeof(buff));//ウィンドウ名を取得
	printf("%s\n",buff);
	return true;
}

int main(int argc, char* argv[])
{
	EnumWindows( EnumWndProc, (LPARAM)NULL );
	return 0;
}


//○他のプログラムのウインドウサイズを変更-------------------------------------------

#include <stdio.h>
#include <windows.h>

BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	char buff[256]="";
	GetWindowText( hWnd,buff, sizeof(buff));
	if(strcmp(buff,(char*)lParam)==0){//名前が一致したら、
		SetWindowPos(hWnd,HWND_TOP,0 ,0 ,100,100,SWP_SHOWWINDOW);//ウインドウの位置とサイズを変更
	}
	return true;
}

int main(int argc, char* argv[])
{
	LPARAM lParam=(LPARAM)"無題 - メモ帳";//検索するウィンドウの名前
	EnumWindows( EnumWndProc, (LPARAM)lParam);
	return 0;
}

//○他のプログラムのウインドウハンドルを取得する----------------------------------------

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
	GetWindowText( hWnd,buff, sizeof(buff));//ウインドウの文字を取得して、
	if(strcmp(buff,((cell*)lParam)->WindowName)==0){//名前が一致したら、
		((cell*)lParam)->hWnd = hWnd;//ウィンドウハンドルを渡す
	}
	return true;
}

int main(int argc, char* argv[])
{
	cell c;
	c.hWnd =NULL;
	strcpy(c.WindowName,"無題 - メモ帳");//検索するウィンドウの名前

	EnumWindows( EnumWndProc, (LPARAM)&c);

	if(c.hWnd != NULL){
		//目的のウインドウハンドルが取得できました
		SetWindowPos(c.hWnd,HWND_TOP,0 ,0 ,100,100,SWP_SHOWWINDOW);//ウインドウのサイズを変更
	}
	return 0;
}

*/