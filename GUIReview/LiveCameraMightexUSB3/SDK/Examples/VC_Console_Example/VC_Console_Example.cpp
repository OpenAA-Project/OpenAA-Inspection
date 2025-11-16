// VC_Console_Example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <assert.h>
#include <conio.h>

#include <iostream>


#include "SSClassic_USBCamera_SDK.h"

#define ALL_DEVICES 0x88


using namespace std;

void CameraFaultCallBack( int Device, int ImageType )
{
	assert(false);

	// Note: It's recommended to stop the engine and close the application
	SSClassicUSB_StopCameraEngine();
	SSClassicUSB_UnInitDevice();
}

void FrameCallBack( TProcessedDataProperty* Attributes, unsigned char *Frameptr )
{
	if ( Attributes->CameraID == 1 ) // The working camera.
	{
		// All frame related attributes is in Attributes.
		// All frame data is pointed by Frameptr

		cout << Attributes->TimeStamp << ":" << cout.flush();
	}

	assert(Attributes->CameraID == 1);
}

void FrameCallBack2( TProcessedDataProperty* Attributes, unsigned char *Frameptr )
{
	if ( Attributes->CameraID == 1 ) // The working camera.
	{
		// All frame related attributes is in Attributes.
		// All frame data is pointed by Frameptr

		cout << Attributes->TimeStamp << ":" << cout.flush();
	}

	assert(Attributes->CameraID == 1);
}

BOOL StopCamera(void)
{
	SSClassicUSB_StopFrameGrab( ALL_DEVICES );
	SSClassicUSB_StopCameraEngine();
	SSClassicUSB_UnInitDevice();
	return TRUE;
}

int main(int argc, char**argv)
{
	int ret;
	MSG   msg; 
//	HWND hw=NULL;
//	DWORD err;
//	CDialog cdia;

//	hw = CreateWindowEx(WS_EX_LEFT,"Message",NULL,WS_CHILD,CW_USEDEFAULT,0,CW_USEDEFAULT,0,HWND_MESSAGE,NULL,NULL,NULL);
//	if (hw==NULL)
//		err = GetLastError();

	ret = SSClassicUSB_InitDevice();
	assert(ret==1);

	ret = SSClassicUSB_AddDeviceToWorkingSet(1);
	ret = SSClassicUSB_InstallUSBDeviceHooker( CameraFaultCallBack );

//	ret = NewClassicUSB_StartCameraEngine(hw, 8);
	ret = SSClassicUSB_StartCameraEngine(NULL, 8, 2, 0);
	assert(ret);

	//if (NewClassicUSB_SetCustomizedResolution(1, 1280, 1024, 0) < 0)
	if (SSClassicUSB_SetCustomizedResolution(1, 1280, 1024, 0, 0) < 0)
	{
		StopCamera();
		return false;
	}

	ret = SSClassicUSB_StartFrameGrab(ALL_DEVICES, GRAB_FRAME_FOREVER);
	assert(ret==1);

// 0=RAW, 1=BMP in first param. 	NewClassicUSB_InstallFrameHooker( 0, FrameCallBack );
	ret = SSClassicUSB_InstallFrameHooker( 1, FrameCallBack );
	ret = SSClassicUSB_InstallFrameHooker( 0, FrameCallBack2 );
	assert(ret==1);

#if 0
	ret = SSClassicUSB_InstallFrameHooker( 1, NULL );
	assert(ret==1);
	unsigned char *rPtr;
	unsigned char *sPtr;
	rPtr = SSClassicUSB_GetCurrentFrame(1, 1, sPtr);
	assert(rPtr);
#endif

	int quit = 0;
	while (!quit)
	{
		if (!_kbhit())
		{
			Sleep(20);
			// The following is to let camera engine to be active..it needs message loop.
			if(GetMessage(&msg,NULL,NULL,NULL))   
			{   
				if(msg.message   ==   WM_TIMER)   
				{   
					TranslateMessage(&msg);   
					DispatchMessage(&msg);   
				}   
			}
		}
		else
		{
			char ch;

			ch = _getch();

			switch(toupper(ch))
			{
			case 'Q':
				quit=1;
				break;
			default:
				break;
			}

		}
	}

	StopCamera();

//	if (hw)
//	{
//		err = DestroyWindow(hw);
//		if (err=0)
//			err = GetLastError();
//	}

	return 0;
}



