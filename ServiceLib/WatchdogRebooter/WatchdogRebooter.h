#ifndef WATCHDOGREBOOTER_H
#define WATCHDOGREBOOTER_H

#include <QMainWindow>
#include <QTimer>
#include "ui_WatchdogRebooter.h"

#include "XWatchdogRebooter.h"

class WatchdogRebooter : public QMainWindow
{
	Q_OBJECT

	WatchdogPack	WPack;
	QTimer			TM;
public:
	WatchdogRebooter(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~WatchdogRebooter();

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddProgram_clicked();
    void on_pushButtonDeleteProgram_clicked();
    void on_pushButtonClose_clicked();
	void SlotTimeOut();
	void	SlotShow();
	void	SlotWatchdogEvent(const QString &ErrorType,const QString &FileName ,int pid);

private:
	Ui::WatchdogRebooterClass ui;

	bool	LoadData(void);
	bool	SaveData(void);
	void	ShowList(void);

	QString		GetDefaultFileName(void)	{	return "ConfigWatchdogRebooter.dat";	}
};

#endif // WATCHDOGREBOOTER_H
