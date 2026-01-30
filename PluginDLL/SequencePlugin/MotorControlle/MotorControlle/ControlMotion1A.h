/*
 * Copyright (C) 2023
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



#if !defined(CONTROLMOTION1A_H)
#define CONTROLMOTION1A_H

//���_���B�������ʒu�܂ňړ�
#define		MotionStage1Code	90
//���_���v���X���~�b�g�܂ňړ�
#define		MotionStage2Code	91
//�B�������ʒu���v���X���~�b�g�܂ňړ�
#define		MotionStage3Code	92
//�}�C�i�X���~�b�g�܂ňړ�
#define		MotionStage4Code	93
//���_���A�ړ��Q(�v���X����)
#define		MotionStage5Code	94
//���_���A�ړ��@�d���n�m���̓���
#define		MotionStage6Code	95


struct	MotionStruct
{
	unsigned short	TargetCount;	//�������Ԃ̑��x�ɂȂ��J�E���^�[��
	unsigned short	Direction;		//���]�����@0 or 1
	unsigned int	StartPulse;		//�������Ԃ̃p���X��
	unsigned int	MiddlePulse;	//�������Ԃ̃p���X��
	unsigned int	EndPulse;		//�������Ԃ̃p���X��
};

struct	MotionAttrStruct{
	unsigned int		MotionStopPercentage;	//���̃p�[�Z���e�[�W�̐Î~���d���ɂȂ�
	unsigned int		DropTime;	    //�����ҋ@����
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