#ifndef LCD_4DSYSTEM_1_H
#define LCD_4DSYSTEM_1_H

#include "lcd_4dsystem_1_global.h"
#include <QThread>
#include <QReadWriteLock>
#include "XTypeDef.h"
#include "XSequence.h"

class   LCD_4DSystem;

// 主クラス
// LCD_4DSystemクラスのインスタンスを保有し、自身のメンバ変数を設定させる
// 各パラメータをDLL_~で使用する
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

// サブクラス
// タッチパネルとのCOM通信を行う
// 通信のやり取りによって主クラスのパラメータを順次変更していく
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
	// 初期化
	virtual	bool    Initial(void)				;
	virtual void	Uninitialize(void)			;
	// 初期化済みフラグ
    virtual	bool    IsInitialed(void){  return Initialed;   }
	// COMから1文字受信 戻り値:char文字数値, 失敗時 -1
	virtual	int		GetChar(void)				;
	// COMから1文字送信
	virtual	void	SendChar(unsigned char d)	;
	// CPU時間取得
	virtual	unsigned int	GetCPUMilisec(void)	;

	bool	isRecieved(void) const { return Recieved; };
	void	resetRecieved(void){ Recieved = false; };

	// タッチパネルへPCB数を送信
	void	ShowPCBCount(int pcbCount);
	// タッチパネルへ枚数不明を送信
	void	ShowUnknown(void);
	// タッチパネルへミラー状況を送信
	void	ShowMirrorState(bool state);
	// COMより文字列を取得し解析、Motionのパラメータを適宜変更する
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
