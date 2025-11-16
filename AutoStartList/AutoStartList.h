#ifndef AUTOSTARTLIST_H
#define AUTOSTARTLIST_H

#include <QMainWindow>
#include "ui_AutoStartList.h"
#include "XAutoStartListThread.h"
#include <QCloseEvent>
#include <QTimer>
#include "XAutoStart.h"
#include <QSystemTrayIcon>
#include <QMenu>

class AutoStartList : public QMainWindow
{
	Q_OBJECT

	QSystemTrayIcon		*TrayIcon;
	QMenu				*TrayIconMenu;
	bool				EnableClose;
public:
	AutoStartList(bool EnableClose ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~AutoStartList();

	volatile	bool	Ticking;
	volatile	bool	Counting;
	volatile	bool	AllFinished;
	bool	IsFinishedAll(void);
	bool	ExecuteAll(void);

	AutoStartExeList	AutoStartExeListData;

protected:
	virtual	void	closeEvent(QCloseEvent *ev)	override;
private:
	Ui::AutoStartListClass ui;
	ThreadAutoStartList	LThread;

	QTimer	TM;

	QAction	*minimizeAction;
	QAction	*showAction;
	QAction	*quitAction;

private slots:
	void on_pushButtonParam_clicked();
	void on_toolButtonStop_clicked();
	void on_pushButtonStart_clicked();
	void	Timeout();
};

#endif // AUTOSTARTLIST_H
