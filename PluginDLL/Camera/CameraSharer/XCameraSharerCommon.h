#if	!defined(XCameraSharerCommon_H)
#define	XCameraSharerCommon_H

#include "XTypeDef.h"
#include <QSharedMemory>
#include "XCameraHandle.h"

#define	CameraSharerCommand_PrepareCapture		1
#define	CameraSharerCommand_StartCapture		2
#define	CameraSharerCommand_HaltCapture			3
#define	CameraSharerCommand_GetStatus			4
#define	CameraSharerCommand_GetLineCount		5
#define	CameraSharerCommand_ClearError			6
#define	CameraSharerCommand_ClearBit			7
#define	CameraSharerCommand_GetImage			8
#define	CameraSharerCommand_ReqCameraError		9
#define	CameraSharerCommand_ShowSetting			10
#define	CameraSharerCommand_Save				11
#define	CameraSharerCommand_Load				12
#define	CameraSharerCommand_Allocate			13
#define	CameraSharerCommand_LockToChange		14
#define	CameraSharerCommand_UnlockToChange		15

class	LayersBase;

struct	CameraSharerHandleHeader
{
	int32	ShareNo;
	int32	CamNo;
	int32	Command;
	bool3	Response;
	int32	RespondedValue;
	int32	TotalSharedBufferByte;
	uint32	XSize;
	uint32	YSize;
	char	CameraError[64];
	BYTE	StreamData[16384];
	int32	StreamByte;
	uint32	LayerNumb;
	uint32	PageNumb;
};

class	CameraSharerHandle:public CameraHandle
{
	QSharedMemory	Packet;
	QSharedMemory	MemoryR;
	QSharedMemory	MemoryG;
	QSharedMemory	MemoryB;
public:
	int			ShareNo;
	LayersBase *Base;
	bool		ShouldFinish;

	CameraSharerHandle(int CamNo,LayersBase *Base ,int ShareNo);
	~CameraSharerHandle(void);

	struct	CameraSharerHandleHeader	*GetHeader(void);
	BYTE	*GetLayerBufferPointer(int Layer);
	bool	OpenForServer(void);
	bool	OpenForClient(void);

	bool	Allocate(void);
	bool	AllocateForClient(void);

	void	Lock(void)	;
	void	Unlock(void);

};

struct	CameraShareSwitcher
{
	int32	CurrentActiveNo;
	int32	Command;	//0:Nothing		1:Switch	2:Top	3:Bottom	-5:Set		-10:Lock	-11:Unlock
	int32	ReqSetActiveNo;
};

#endif