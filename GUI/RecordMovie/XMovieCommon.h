#pragma once
#include <QString>

enum EnumAVFormat
{
	FormatMotionJPeg
	,FormatMPeg1
	,FormatMPeg2
	,FormatMPeg4
};

struct RecordStruct
{
	enum Command
	{
		_ReqDetach			= 1
		,_ReqAttach			= 2
		,_StartRecording	= 3
		,_EndRecording		= 4
		,_RestartRecording	= 5
		,_HaltRecording		= 6

	}Cmd;
	int		MovieXSize;
	int		MovieYSize;
	int		LayerNumb;
	double	FPS;
	int		Quality;
};

struct RecordHeaderStruct
{
	wchar_t		FileName[1024];
	int			MovieXSize;
	int			MovieYSize;
	int			LayerNumb;
	double		FPS;
	int			Quality;
	long long	CurrentTime;
	long long	Duration;
	bool		Opened;
};