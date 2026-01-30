/*
 * Copyright (C) 2014
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

#ifndef LCD_4DSYSTEM_1_H
#define LCD_4DSYSTEM_1_H

#include "lcd_4dsystem_1_global.h"
#include <QThread>
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "XSequence.h"

class   LCD_4DSystem;

// ���N���X
// LCD_4DSystem�N���X�̃C���X�^���X���ۗL���A���g�̃����o�ϐ����ݒ肳����
// �e�p�����[�^��DLL_~�Ŏg�p����
class ThreadComm : public QThread
{
	Q_OBJECT

public:
	volatile	bool	ModePushedCalcStart;
	volatile	bool	ModePushedDetail;

	volatile	bool	ModeShowPCBCount;
	volatile	bool	ModeShowUnknown;
	volatile	int		PCBCount;
	volatile	bool	MirrorState;
	volatile	bool	ModeShowMirrorState;

	volatile	bool	ModePushedLightAdjust;
	volatile	bool	ModeMirrorCheck;

	volatile	bool	ModePushedShutdown;

public:
	LCD_4DSystem	*Motioner;
	volatile	bool	Initialized;

private:
	volatile	bool	m_stop;
	volatile	bool	m_isStopped;

public:
	ThreadComm(SeqControl *seq,const QString &Param);

	void run();

	bool	IsCalcStartPushed(void);
	bool	IsDetailButtonPushed(void);

	void	ShowPCBCount(int pcbCount);
	void	ShowUnknown(void);
	void	ShowMirrorState(bool state);

	void	SendBooted(void);
	void	SendEnd(void);

	bool	IsLightAdjustPushed(void);
	bool	IsMirrorCheckPushed(void);

	void	stop(){ m_stop = true; m_isStopped = false;};
	bool	isStopped() const { return m_isStopped; };

	void	uninitialize(void);
};


class	QextSerialPort;
class	TestProgram;

// �T�u�N���X
// �^�b�`�p�l���Ƃ�COM�ʐM���s��
// �ʐM�̂��������ɂ����Ď��N���X�̃p�����[�^�������ύX���Ă���
class   LCD_4DSystem : public QObject
{
	Q_OBJECT

private:
    QextSerialPort    *sio;
    bool    Initialed;
	ThreadComm	*Motion;
	QString		Param;
	volatile bool Recieved;

public:
	LCD_4DSystem(ThreadComm* Owner,const QString &_Param);
    ~LCD_4DSystem(void);

public:
	// ������
	virtual	bool    Initial(void)				;
	virtual void	Uninitialize(void)			;
	// �������ς݃t���O
    virtual	bool    IsInitialed(void){  return Initialed;   }
	// COM����1�������M �߂��l:char�������l, ���s�� -1
	virtual	int		GetChar(void)				;
	// COM����1�������M
	virtual	void	SendChar(unsigned char d)	;
	// CPU���Ԏ擾
	virtual	unsigned int	GetCPUMilisec(void)	;

	bool	isRecieved(void) const { return Recieved; };
	void	resetRecieved(void){ Recieved = false; };

	// �^�b�`�p�l����PCB���𑗐M
	void	ShowPCBCount(int pcbCount);
	// �^�b�`�p�l���֖����s���𑗐M
	void	ShowUnknown(void);
	// �^�b�`�p�l���փ~���[�󋵂𑗐M
	void	ShowMirrorState(bool state);
	// COM���蕶�������擾�����́AMotion�̃p�����[�^���K�X�ύX����
	void	Loop(void);
	void	SendBooted(void);
	void	SendEnd(void);

	void	StopThread(void);

private:
	int		GetRxStopless(unsigned char *data ,int buffsize);
	void	AnalizeReceivedData(unsigned char *data ,int buffsize);

	void	shutdown();
};


#endif // LCD_4DSYSTEM_1_H