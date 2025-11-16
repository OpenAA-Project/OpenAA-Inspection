#ifndef DELAYEXE_H
#define DELAYEXE_H

#include <QMainWindow>
#include "ui_DelayExe.h"
#include <QTimer>

class DelayExe : public QMainWindow
{
	Q_OBJECT

	QTimer	TM;
	int		CurrentCounter;
	QString	ExeFileName;
	QStringList	SArg;

public:
	DelayExe(const QString &FileName , int WaitingTime , QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DelayExe();

private:
	Ui::DelayExeClass ui;

private slots:
	void	SlotTimeOut();
};

#endif // DELAYEXE_H
