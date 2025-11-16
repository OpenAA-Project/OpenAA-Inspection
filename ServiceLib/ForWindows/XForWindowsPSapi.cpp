#include "swap.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XForWindows.h"
#include "ForWindows.h"
#include "XGeneralFunc.h"
#include "Windows.h"
#include <Psapi.h>

bool	GetProcessNames(QStringList &Processes)
{
	DWORD allProc[1024];
	DWORD cbNeeded;
	int nProc;

	// PID一覧を取得
	if (!::EnumProcesses(allProc, sizeof(allProc), &cbNeeded)) {
		return false;
	}

	nProc = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < nProc; i++) {
		TCHAR procName[MAX_PATH] = TEXT("<unknown>");

		HANDLE hProcess = ::OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			false, allProc[i]);

		// プロセス名を取得
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;

			if (::EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				::GetModuleBaseName(hProcess, hMod, procName, sizeof(procName)/sizeof(TCHAR));
				Processes.append(QString::fromWCharArray(procName));
			}
	        CloseHandle(hProcess);
		}
    }
	return true;
}


int	MtEnumProcess(DWORD ProcessID[], int MaxCountOfProcessID)
{
	DWORD cbNeeded;
	if(!EnumProcesses( ProcessID, MaxCountOfProcessID, &cbNeeded )){
		return 0;
	}
	return cbNeeded;
}

bool	GetProcessName(int ProcessID ,QString &ProcessName)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   false, ProcessID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) ){
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
		else{
			CloseHandle( hProcess );
			return false;
		}
    }
	else{
		return false;
	}
	ProcessName=QString::fromWCharArray(szProcessName);
    // Release the handle to the process.
    CloseHandle( hProcess );
	return true;
}

void	KillPreviousDupProcess(void)
{
	DWORD	ID=MtGetCurrentProcessId();
	QString ProcessName;
	GetProcessName(ID,ProcessName);
	DWORD ProcessID[1000];
	int		N=MtEnumProcess(ProcessID, 1000);
	for(int i=0;i<N;i++){
		QString OtherProcessName;
		GetProcessName(ProcessID[i],OtherProcessName);
		if(OtherProcessName==ProcessName && ProcessID[i]!=ID){
			KillProcess(ProcessID[i], 0);
		}
	}
}

void	KillOtherProcesses(const QString &ProcessName)
{
	DWORD	MyID=MtGetCurrentProcessId();
	DWORD ProcessID[1000];
	int		N=MtEnumProcess(ProcessID, 1000);
	for(int i=0;i<N;i++){
		QString OtherProcessName;
		GetProcessName(ProcessID[i],OtherProcessName);
		if(OtherProcessName==ProcessName && ProcessID[i]!=MyID){
			KillProcess(ProcessID[i], 0);
		}
	}
}

struct	FindWindowProc
{
	int		ProcessID;
	HWND	hWnd[1000];
	int		hWndNumb;
};


static	BOOL  CALLBACK  EnumWndProc( HWND hWnd, LPARAM lParam )
{
	struct	FindWindowProc	*C=(struct	FindWindowProc *)lParam;

	DWORD lpdwProcessId;
	DWORD	ThreadID=GetWindowThreadProcessId(hWnd,             // ウィンドウのハンドル
							&lpdwProcessId  // プロセス ID
							);
	if(lpdwProcessId==C->ProcessID){
		if(C->hWndNumb<sizeof(C->hWnd)/sizeof(C->hWnd[0])){
			C->hWnd		[C->hWndNumb]=hWnd;
			C->hWndNumb++;
		}
	}
	return TRUE;
}
static	BOOL  CALLBACK  EnumChildProc( HWND hWnd, LPARAM lParam )
{
	struct	FindWindowProc	*C=(struct	FindWindowProc *)lParam;

	if(C->hWndNumb<sizeof(C->hWnd)/sizeof(C->hWnd[0])){
		C->hWnd		[C->hWndNumb]=hWnd;
		C->hWndNumb++;
	}
	return TRUE;
}

bool	GetWindowPosition(int ProcessID ,QRect &rect)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;
		if(KNumb==0){
			rect.setRect(Rect.left,Rect.top,Rect.right-Rect.left ,Rect.bottom-Rect.top);
			KNumb++;
		}
		else{
			rect.setLeft  (min((long)rect.left(),Rect.left));
			rect.setTop   (min((long)rect.top (),Rect.top));
			rect.setRight (max((long)rect.right(),Rect.right));
			rect.setBottom(max((long)rect.bottom(),Rect.bottom));
			KNumb++;
		}
	}
	if(KNumb!=0)
		return true;
	if(KNumb==0)
		return false;

	return true;
}
bool	SetWindowPosition(int ProcessID ,QRect &rect)
{
	QRect SRect;
	if(GetWindowPosition(ProcessID ,SRect)==false){
		return false;
	}

	int	Dx=rect.left()-SRect.left();
	int	Dy=rect.top() -SRect.top();
	double	Zx=(double)rect.width() /(double)SRect.width();
	double	Zy=(double)rect.height()/(double)SRect.height();

	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;

		if(MoveWindow(C.hWnd[i]      // ウィンドウのハンドル
					,Rect.left+Dx
					,Rect.top+Dy
					,(Rect.right -Rect.left)*Zx
					,(Rect.bottom-Rect.top )*Zy
					,TRUE
					)==false){
			return false;
		}
		KNumb++;
	}
	if(KNumb==0)
		return false;
	return true;
}

bool	SetWindowCmdShow(int ProcessID ,int nCmdShow)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		RECT Rect;
		if(GetWindowRect(C.hWnd[i],      // ウィンドウのハンドル
						&Rect   // クライアント座標
						)==false){
			return false;
		}
		WINDOWINFO wi;

		if(GetWindowInfo(C.hWnd[i],&wi)==false)
			return false;
		if((wi.dwWindowStatus & WS_ACTIVECAPTION)==0){
			continue;
		}
		if((wi.dwStyle & WS_VISIBLE)==0)
			continue;

		if(ShowWindow(C.hWnd[i]      // ウィンドウのハンドル
					,nCmdShow
					)==false){
			return false;
		}
		KNumb++;
	}
	if(KNumb==0)
		return false;
	return true;
}

bool	SetForegroundOtherWindow(int ProcessID)
{
	struct	FindWindowProc	C;
	C.ProcessID=ProcessID;
	C.hWndNumb=0;
		
	EnumWindows(EnumWndProc,(LPARAM)&C);
	if(C.hWndNumb==0){
		return false;
	}
	int	KNumb=0;
	for(int i=0;i<C.hWndNumb;i++){
		SetForegroundWindow(C.hWnd[i]);
	}
	return true;
}