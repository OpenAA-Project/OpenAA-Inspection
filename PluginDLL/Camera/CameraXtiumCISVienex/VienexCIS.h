#pragma once

#include "XTypeDef.h"
#include <QIODevice>
#include <QSerialPort>
#include "half.hpp"

class CameraXtiumCISVienex;

class VienexCIS : public QObject
{
	Q_OBJECT

	CameraXtiumCISVienex	*Parent;
	QSerialPort				*Sio;
	char					RxData[100];
	int						RxPoint;
	int						WaitingMiliSec;
public:
	struct{
		int16	FPGA_VER;

		int		SHADING:1;
		int		DARK:1;
		int		GET_SHADING:1;
		int		GET_DARK:1;
		int		AVE_NUM:3;

		int		SET_MODE:1;
		int16	SHADING_TARGET_VAL;
		int		SHADING_TARGET_VAL_R;
		int		SHADING_TARGET_VAL_G;
		int		SHADING_TARGET_VAL_B;
		half_float::half	ODD_IC_MULTIPLIER;
		half_float::half	EVEN_IC_MULTIPLIER;

		int		CL_CONFIG:4;
		int		CL_FREQ:2;

		int		TRIG_CYCLE;
		int		SYNC_MODE:2;

		int		GRAY_SCALE_R;
		int		GRAY_SCALE_G;
		int		GRAY_SCALE_B;

		int		LED_ON_1_CYCLE;
		int		LED_ON_2_CYCLE;
		int16	LED_CTRL_1;
		int16	LED_CTRL_2;
		int		CONTINUOUS:1;
		int		LED1_ON:1;
		int		LED2_ON:1;

		int		LINE_ADJUST_DIRECTION:1;
		int		LINE_ADJUST_ON_OFF:1;

		int		D_RANGE:1;
		int		RES_SEL:1;

		int		GAIN_R:4;
		int		OFFSET_R:6;
		int		GAIN_G:4;
		int		OFFSET_G:6;
		int		GAIN_B:4;
		int		OFFSET_B:6;

		int		STAGGERED_SHIFT_DIRECTION:1;
		int		STAGGERED_SHIFT_ON_OFF:1;
		int		BASE_STAGGERED_SHIFT:5;
		int		ADD_STAGGERED_SHIFT_0 :2;
		int		ADD_STAGGERED_SHIFT_1 :2;
		int		ADD_STAGGERED_SHIFT_2 :2;
		int		ADD_STAGGERED_SHIFT_3 :2;
		int		ADD_STAGGERED_SHIFT_4 :2;
		int		ADD_STAGGERED_SHIFT_5 :2;
		int		ADD_STAGGERED_SHIFT_6 :2;
		int		ADD_STAGGERED_SHIFT_7 :2;
		int		ADD_STAGGERED_SHIFT_8 :2;
		int		ADD_STAGGERED_SHIFT_9 :2;
		int		ADD_STAGGERED_SHIFT_10:2;
		int		ADD_STAGGERED_SHIFT_11:2;
		int		ADD_STAGGERED_SHIFT_12:2;
		int		ADD_STAGGERED_SHIFT_13:2;
		int		ADD_STAGGERED_SHIFT_14:2;
		int		ADD_STAGGERED_SHIFT_15:2;
		int		ADD_STAGGERED_SHIFT_16:2;
		int		ADD_STAGGERED_SHIFT_17:2;

		int		REMOVE_OVERLAPPING_PIXELS_ON_OFF : 1;
		int		REMOVED_PIXELS_0 :2;
		int		REMOVED_PIXELS_1 :2;
		int		REMOVED_PIXELS_2 :2;
		int		REMOVED_PIXELS_3 :2;
		int		REMOVED_PIXELS_4 :2;
		int		REMOVED_PIXELS_5 :2;
		int		REMOVED_PIXELS_6 :2;
		int		REMOVED_PIXELS_7 :2;
		int		REMOVED_PIXELS_8 :2;
		int		REMOVED_PIXELS_9 :2;
		int		REMOVED_PIXELS_10:2;
		int		REMOVED_PIXELS_11:2;
		int		REMOVED_PIXELS_12:2;
		int		REMOVED_PIXELS_13:2;
		int		REMOVED_PIXELS_14:2;
		int		REMOVED_PIXELS_15:2;
		int		REMOVED_PIXELS_16:2;
		int		REMOVED_PIXELS_17:2;

	}CISVienexData;

public:
	VienexCIS(CameraXtiumCISVienex *p);
	~VienexCIS(void);

	bool	Release(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	OpenComm(void);
	bool	CloseComm(void);
	bool	StoreToCam(void);
	bool	LoadFromCam(void);
	bool	LoadFromROMonCam(void);

	bool	LoadFromCamera(QIODevice *f);
	bool	StoreToCamera(QIODevice *f);
	bool	LoadFromROMonCamera(QIODevice *f);

private slots:
	void	SlotReadyRead();

private:
	bool	SendCom(QIODevice *f,char *Str);
	bool	ReceiveComm(QIODevice *f,char *Str,unsigned long MaxWaitingMilisec);
	bool	SendCommand(QIODevice *f,int Addr ,DWORD Data);
	bool3	ReqData(QIODevice *f,int Addr ,DWORD &Data);

};
