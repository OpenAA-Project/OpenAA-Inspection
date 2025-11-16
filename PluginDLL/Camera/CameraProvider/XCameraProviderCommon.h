#if	!defined(XCameraProviderCommon_H)
#define	XCameraProviderCommon_H

#include "XTypeDef.h"
#include <QSharedMemory>
#include "XCameraHandle.h"

#define	CameraProviderCommand_PrepareCapture	1
#define	CameraProviderCommand_StartCapture		2
#define	CameraProviderCommand_HaltCapture		3
#define	CameraProviderCommand_GetStatus			4
#define	CameraProviderCommand_GetLineCount		5
#define	CameraProviderCommand_ClearError		6
#define	CameraProviderCommand_ClearBit			7
#define	CameraProviderCommand_GetImage			8
#define	CameraProviderCommand_ReqCameraError	9
#define	CameraProviderCommand_ShowSetting		10
#define	CameraProviderCommand_Save				11
#define	CameraProviderCommand_Load				12

class	LayersBase;

struct	CameraProviderHandleHeader
{
	int32	CameraNo;
	int32	Command;
	bool3	Response;
	int32	RespondedValue;
	int32	TotalSharedBufferByte;
	int32	XSize;
	int32	YSize;
	char	CameraError[64];
	BYTE	StreamData[16384];
	int32	StreamByte;
	int32	LayerNumb;
};

class	CameraProviderHandle :public CameraHandle
{
	QSharedMemory	Memory;
public:

	CameraProviderHandle(LayersBase *Base ,int CameraNo);
	~CameraProviderHandle(void);

	struct	CameraProviderHandleHeader	*GetHeader(void);
	BYTE	*GetLayerBufferPointer(int Layer);
	bool	OpenForServer(int XLen ,int YLen, int LayerNumb);
	bool	OpenForClient(void);

	void	Lock(void)	{	Memory.lock();	}
	void	Unlock(void){	Memory.unlock();	}

};

#endif