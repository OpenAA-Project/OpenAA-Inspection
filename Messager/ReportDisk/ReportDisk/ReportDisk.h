#ifndef REPORTDISK_H
#define REPORTDISK_H

#include <QMainWindow>
#include "ui_ReportDisk.h"
#include <QThread>
#include "XFileRegistry.h"
#include "XMessagerClient.h"

class	ThreadDiskChecker;

class ReportDisk : public QMainWindow
{
	Q_OBJECT
	ThreadDiskChecker	*ThreadDisk;
	FileRegistry		FRegistry;

public:
	MessagerClient	MClient;

	ReportDisk(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ReportDisk();

protected:
	virtual void closeEvent ( QCloseEvent * event )	override;

private:
	Ui::ReportDiskClass ui;

private slots:
	void on_pushButtonOK_clicked();
    void on_checkBoxAutoMode_clicked();
    void on_pushButtonAddDestination_clicked();
    void on_pushButtonDeleteDestination_clicked();
	void	SlotReceived();
    void on_pushButtonForceExecute_clicked();
    void on_checkBoxExecuteDelete_clicked();
};

class	ThreadDiskChecker : public QThread
{
	bool	ModeForce;
public:
	ReportDisk 	*Parent;
	QString	DiskPath1;
	uint	AlertSpace1;
	QString	DiskPath2;
	uint	AlertSpace2;
	QString	DiskPath3;
	uint	AlertSpace3;
	QString	DiskPath4;
	uint	AlertSpace4;
	bool	CloseMode;
	QString	ComputerName;

	bool		AutoMode;
	XDateTime	PassedTime;
	bool		RemoveMode;
	QStringList	Destinations;

	ThreadDiskChecker(ReportDisk  *parent);

	virtual void run();

	void	ErrorOut(QString Msg);
	void	ReportOut(QString Msg,int64 FreeSpace);
	bool	CheckDisk(QString Drive, int AlertSpace,int64 &FreeSpace);
	bool	ScanDisk(QString &Path);

	bool SaveSetting(QIODevice *f);
	bool LoadSetting(QIODevice *f);

	void	ForceExecute(void)	{	ModeForce=true;	}
};


#endif // REPORTDISK_H
