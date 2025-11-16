#ifndef SCREENLOCK_H
#define SCREENLOCK_H

#include <QMainWindow>
#include "ui_ScreenLock.h"
#include <QTimer>

class ScreenLock : public QMainWindow
{
	Q_OBJECT

	QString Password;
	QTimer	TM;
	int		BreakTime;
public:
	ScreenLock(const QString &Password , const QString &title 
				,int _BreakTime
				,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ScreenLock();

	virtual	void	showEvent (QShowEvent * event)	override;

private slots:
    void on_pushButtonOK_clicked();
	void	SlotTimeOut();

private:
	Ui::ScreenLockClass ui;
};

#endif // SCREENLOCK_H
