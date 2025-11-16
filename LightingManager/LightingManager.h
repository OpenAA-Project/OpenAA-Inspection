#ifndef LIGHTINGMANAGER_H
#define LIGHTINGMANAGER_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QTimer>
#include "ui_LightingManager.h"
#include "time.h"

class LightingManager : public QWidget
{
	Q_OBJECT

public:
	LightingManager(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LightingManager();

	void SetWarmMinute		(int Value)		{	WarmMinute		=Value;		}
	void SetChangeHour		(int Value)		{	ChangeHour		=Value;		}
	void SetTotalSumHour	(time_t Value)	{	TotalSumHour	=Value;		}
	void SetIsShowWidget	(bool Enable)	{	IsShowWidget	=Enable;	}
	void SetIsCloseWidget	(bool Enable)	{	IsCloseWidget	=Enable;	}
	void SetIsStartExe		(bool Enable)	{	IsStartExe		=Enable;	}
	void SetStartExe		(QString Str)	{	StartExe		=Str;		}

protected:
    virtual	void closeEvent(QCloseEvent *event)	override;

private slots:
	void pbResetTotalSumHourClicked	();
	void pbDetailClicked			(bool checked);
	void sbWarmMinuteValueChanged	(int value)		{	SetWarmMinute	(value);	}
	void sbChangeHourValueChanged	(int value)		{	SetChangeHour	(value);	}
	void chkIsShowWidgetClicked		(bool checked)	{	SetIsShowWidget	(checked);	}
	void chkIsCloseWidgetClicked	(bool checked)	{	SetIsCloseWidget(checked);	}
	void gbIsStartExeClicked		(bool checked)	{	SetIsStartExe	(checked);	}
	void tbStartExeClicked			();
	void pbShowMessageClicked		();
	void iconActivated				(QSystemTrayIcon::ActivationReason reason);
	void SlotTimerMonitoring		();
	void SlotClose					();

	void SlotCommitDataRequest		(QSessionManager &manager);

private:
	Ui::LightingManagerClass ui;

    QAction			*restoreAction;
    QAction			*exitAction;
    QMenu			*trayIconMenu;
    QSystemTrayIcon	*trayIcon;

	time_t	StartTime;			//アプリケーションの起動時間
	time_t	TerminationTime;	//アプリケーションの終了時間
	QTimer	TimerMonitoring;	//監視用タイマー

	int		WarmMinute;			//暖機時間
	int		ChangeHour;			//照明交換目安時間
	time_t	TotalSumHour;		//累計時間
	bool	IsShowWidget;		//起動時に画面を表示する
	bool	IsCloseWidget;		//暖機終了後、画面を閉じる
	bool	IsStartExe;			//暖機終了後、起動するソフトを指定する
	QString	StartExe;			//暖機終了後、起動するソフト

	bool	IsShutdown;			//シャットダウンかどうか
	bool	DoneExit;			//手動終了かどうか
	char	Index;				//背景色反転フラグ
	QString BlinkStyleSheet[2];	//背景色反転用スタイルシート文字列

    void createActions();
    void createTrayIcon();
	void SettingUpdate();
};

#endif // LIGHTINGMANAGER_H
