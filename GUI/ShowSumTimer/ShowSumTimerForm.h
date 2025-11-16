#ifndef SHOWSUMTIMERFORM_H
#define SHOWSUMTIMERFORM_H

#include "XGUIFormBase.h"

namespace Ui {
    class ShowSumTimerForm;
}

class LongTime
{
private:
	bool m_isMinus;
	quint32 m_hour;
	quint32 m_minuite;
	quint32 m_second;
	quint32 m_milisecond;

public:
	LongTime(quint32 _hour=0, quint32 _minuite=0, quint32 _second=0, quint32 _miliSecond=0, bool minus=false);

	void addHour(quint64 h);
	void addMinuite(quint64 min);
	void addSecond(quint64 sec);
	void addMiliSecond(quint64 msec);

	qint64 toMiliSecond() const;

	void setMinus(bool minus){ m_isMinus = minus; };
	void setHour(quint32 h) { m_hour = h; };
	void setMinuite(quint32 min) { m_minuite = min; };
	void setSecond(quint32 sec) { m_second = sec; };
	void setMiliSecond(quint32 msec) { m_milisecond = msec; };

	bool isMinus() const { return m_isMinus; };
	quint32 hour() const { return m_hour; };
	quint32 minuite() const { return m_minuite; };
	quint32 second() const { return m_second; };
	quint32 miliSecond() const { return m_milisecond; };

	void clear(){ setHour(0); setMinuite(0); setSecond(0); setMiliSecond(0); };

	static LongTime fromMiliSecond(quint64 msec);

public:
	LongTime operator-(const LongTime &other) const { return LongTime::fromMiliSecond( this->toMiliSecond() - other.toMiliSecond() ); };
};

class	SignalOperandInt;
class	SignalOperandBit;

class ShowSumTimerForm : public GUIFormBase
{
    Q_OBJECT

public:
	QString		TitleName;

	int32		TimerControlIONumber;		// システムビットレジスタ番号
	int32		TimerProgressIONumber;
	int32		TimerFuncEndIONumber;

	int32		MaxTime_Hour;
	int32		MaxTime_Minuite;
	int32		MaxTime_Second;
	int32		MaxTime_MiliSec;

	bool	isIncreaseProgress;	// プログレスバーの進行方向(0->100 or 100->0)
	bool	isIncreaseTime;		// 時間表示を蓄積時間にするか、残り時間にするか
	
	bool	isViewTitleLabel;	// タイトルラベルの表示
	bool	isViewResetButton;	// リセットボタンの表示
	bool	isViewTimeLabel;	// 時間ラベルの表示
	bool	isViewProgressBar;	// プログレスバーの表示

	bool	isSaveToFile;		// ファイルに保存する設定

	QString	ViewStringFormat;
	int32	UpdateDuration;

	QFont	TitleFont;
	QFont	TimeFont;

	bool	isTimeEditEnable;

private:
	QTimeLine m_tline;
	LongTime m_sumTime;
	QMutex m_fileMutex;
	QElapsedTimer m_timer;

public:
	quint64 maxTime() const {
		LongTime t(MaxTime_Hour, MaxTime_Minuite, MaxTime_Second, MaxTime_MiliSec);
		return t.toMiliSecond();
	};

	quint64	sumTimeMSec() const {
		quint64 sum = 0;
		sum += m_sumTime.toMiliSecond();	// 今までの和
		//qDebug() << "func sumTime() m_sumTime.toMiliSecond() = " << sum;
		//sum += m_tline.currentTime();		// 現在の進行状況
		if(m_timer.isValid()==true){
			//qDebug() << "func sumTime() m_timer.elapsed() = " << m_timer.elapsed();
			sum += m_timer.elapsed();
		}
		return sum;
	};

	LongTime sumTime() const { return LongTime::fromMiliSecond(sumTimeMSec()); };

	void	setSumTime(quint64 msec){
		bool isRun;
		if(m_tline.state()==QTimeLine::State::Running){	// 動作中なら停止
			m_tline.stop();
			isRun = true;
		}else{
			isRun = false;
		}
		//quint64 rem = msec % m_tline.duration();	// 1400 % 1000 = 400
		//quint64 forSumTime = msec - rem;			// 1400 - 400 = 1000
		//m_tline.setCurrentTime( rem );				// 400 timer
		m_sumTime = LongTime::fromMiliSecond(msec);// 1000 is already finished.
		m_timer = QElapsedTimer();
		m_timer.invalidate();
		if(isRun==true){
			m_tline.start();
			m_timer.start();
		}
	};

	int		nextDuration() const;

	qreal	progressRate() const { return sumTimeMSec() / (qreal)maxTime(); };

private:
	void updateTitleLabel();
	void updateTimerLabel();
	void updateProgressBar();
	void updateView();
	void updateSumTime();

	void updateDuration();
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

public:
    explicit ShowSumTimerForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowSumTimerForm();

	SignalOperandInt	*ioTimerEnable;		// 0の時は何もしない、1の時は時間を数える、それ以外は時間をリセットする。
	SignalOperandInt	*ioTimerProgress;	// 初期値0から終了1000で表示する
	SignalOperandBit	*ioTimerFuncEnd;	// 処理完了フラグ(シーケンスで0に初期化、1で完了)

	QAction *m_showEditTimeAction;
	QMenu *m_contextMenu;

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;

protected:
	virtual	void contextMenuEvent(QContextMenuEvent *event)	override;

private slots:
	void	on_pbReset_clicked();
	void	OperandEnableChanged();
	void	timeLineFinished();

	void	showEditTimeForm();

private:
    Ui::ShowSumTimerForm *ui;

private:
	void load();
	void save();
};

#endif // SHOWSUMTIMERFORM_H
