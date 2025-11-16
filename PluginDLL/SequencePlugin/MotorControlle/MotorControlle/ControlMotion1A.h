/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\MotorControlle\MotorControlle\ControlMotion1A.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if !defined(CONTROLMOTION1A_H)
#define CONTROLMOTION1A_H

//原点→撮像完了位置まで移動
#define		MotionStage1Code	90
//原点→プラスリミットまで移動
#define		MotionStage2Code	91
//撮像完了位置→プラスリミットまで移動
#define		MotionStage3Code	92
//マイナスリミットまで移動
#define		MotionStage4Code	93
//原点復帰移動２(プラス方向)
#define		MotionStage5Code	94
//原点復帰移動　電源ＯＮ後の動作
#define		MotionStage6Code	95


struct	MotionStruct
{
	unsigned short	TargetCount;	//等速区間の速度になるカウンター数
	unsigned short	Direction;		//回転方向　0 or 1
	unsigned int	StartPulse;		//加速区間のパルス数
	unsigned int	MiddlePulse;	//等速区間のパルス数
	unsigned int	EndPulse;		//減速区間のパルス数
};

struct	MotionAttrStruct{
	unsigned int		MotionStopPercentage;	//このパーセンテージの静止時電流になる
	unsigned int		DropTime;	    //落下待機時間
    MotionAttrStruct(void){ MotionStopPercentage=40;    DropTime=10000;  }
};

struct	TriggerSetting{
	unsigned int		OutTriggerStartPulse;
	unsigned int		OutTriggerKeepOnTime;
	unsigned int		OutTriggerPort;
};

class	ControlMotion1A
{
	unsigned char	*RxData;
	int		RxByte;
	int		RxWPoint;
	int		RxNumb;
	char	RxCmd;

protected:
    struct	MotionStruct    MotionStage1Data;
    struct	MotionStruct    MotionStage2Data;
    struct	MotionStruct    MotionStage3Data;
    struct	MotionStruct    MotionStage4Data;
    struct	MotionStruct    MotionStage5Data;
    struct	MotionStruct    MotionStage6Data;

public:
	enum	MotionState{
		StateStop		='S'
		,StateRun		='G'
		,StateRelease	='R'
		,StateRestart	='A'
	};

	ControlMotion1A(void);
	~ControlMotion1A(void);

	bool	SendAck(void);

	bool	SetMotionNumb(int N);
	bool	ReqMotionNumb(int &N);

	bool	SetMotionData(short N,struct MotionStruct &Data);
	bool	ReqMotionData(short N,struct MotionStruct &Data);

	bool	SetMotionAttr(struct MotionAttrStruct &Data);
	bool	ReqMotionAttr(struct MotionAttrStruct &Data);

	bool	SetCurrentMotion(MotionState  c);
	bool	ReqCurrentMotion(MotionState &c);

    bool    SetTriggerSetting(struct TriggerSetting &Data);
    bool    ReqTriggerSetting(struct TriggerSetting &Data);

	bool	ReqInport(int port ,unsigned char &portbit);
	bool	ReqInport(unsigned char &portallbit);

	bool	SendOutport(int port ,unsigned char portbit);
	bool	SendOutport(unsigned char portbit);

	bool	SendMotionCommand(unsigned char CommandNo);
	bool	SetMotionData1(void);
	bool	SetMotionData2(void);
	bool	SetMotionData3(void);
	bool	SetMotionData4(void);
	bool	SetMotionData5(void);
	bool	SetMotionData6(void);

	virtual	bool    Initial(void)				=0;
    virtual	bool    IsInitialed(void)           =0;
	virtual	int		GetChar(void)				=0;
	virtual	void	SendChar(unsigned char d)	=0;
	virtual	unsigned int	GetCPUMilisec(void)	=0;
private:
	void 	SendTx(char Cmd ,char *Buff, unsigned short datalen);
	bool	GetRx(int &Cmd ,unsigned char *data ,int buffsize);
    void    Wait1ms(void);
    void    Wait100ms(void);
};


#endif
