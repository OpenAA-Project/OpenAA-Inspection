#pragma once

struct ControllerInfo
{
	double	EncoderMMPerPulse;

	unsigned short	EncoderMul;

	unsigned short	TriggerFilderON;
	unsigned short	TriggerFilterOff;

	struct FrameTriggerPosition
	{
		unsigned short	TriggerPosition;
		unsigned short	ResultAcceptableStart;
		unsigned short	ResultAcceptableEnd;
	};
	struct FrameTriggerPosition	FrameA;
	struct FrameTriggerPosition	FrameB;
	struct FrameTriggerPosition	FrameC;
	struct FrameTriggerPosition	FrameD;

	unsigned int	FlapPosition;
	unsigned short	FlapONPulse;
};
