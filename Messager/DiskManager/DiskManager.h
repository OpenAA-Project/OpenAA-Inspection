#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <QMainWindow>
#include "ui_DiskManager.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QIODevice>
#include "NList.h"
#include "XDateTime.h"
#include <time.h>
#include "XTypeDef.h"
#include <QByteArray>
#include <QMutex>
#include "XDiskInfoCommon.h"

class	DiskManager;


class	DiskList : public NPList<DiskList>
{
public:
	QString	DiskName;
	double	SizeNumb;
	QString	DiskUnit;
	bool	Alarm;

	DiskList(void){		Alarm=false;	}
};

class	MRecList : public NPList<MRecList>
{
public:
	BYTE		*Data;
	int32		Len;

	MRecList(int len);
	~MRecList(void);

	BYTE	*GetPointer(void){	return(Data);	}
	BYTE	*GetPointer(BYTE *p ,QByteArray &ret);
};

class	SourcePCSocket : public QObject ,public NPList<SourcePCSocket>
{
	Q_OBJECT
		
	DiskManager *Parent;
	QTcpSocket	*Sock;

	int		FastCommLeafRxReEntrant;
	enum	_RxState{
		_NowOnReceiving
		,_NowOnWaiting
		}RxState;
	time_t		LastReceivingTime;
	MRecList	*OnRBuff;
	int32		NowOnPoint;
	int32		NowOnXByte;
	int32		PctLen;
	int32		LastPacketLoadedSize;
	QMutex		MuteRecData;
	NPListPack<MRecList>	RecData;
public:
	QString		PCName;
	NPListPack<DiskList>	Disk;

	SourcePCSocket(DiskManager *parent ,QTcpSocket *s);
	void	Set(void);

	bool	Send(QByteArray &data);
	MRecList	*UnpackTopRxBuff(void);
	int		GetQueuedCount(void);
private slots:
	void	SlotReadyRead();
	void	SlotDisconnected();
	void	SlotReceived();
signals:
	void	SignalReceived();
};

class DiskManager : public QMainWindow
{
	Q_OBJECT

	QTcpServer	SockServer;

	bool		AutoMode;
	XDateTime	PassedTime;
	bool		RemoveMode;
	QStringList	Destinations;

public:
	NPListPack<SourcePCSocket>	SourcePCContainer;
	DiskFileInfoContainer		DiskFileInfoData;

	DiskManager(int Port,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DiskManager();

	void	ReviewWatch(void);
	void	ReviewFileList(void);
private slots:
    //void on_pushButtonAddDestination_clicked();
    //void on_pushButtonDeleteDestination_clicked();
    void on_pushButtonSaveSetting_clicked();
    //void on_listWidgetDestination_doubleClicked(const QModelIndex &index);
    void on_tableWidgetSourceDrive_clicked(const QModelIndex &index);
    void on_tableWidgetFileList_doubleClicked(const QModelIndex &index);
	void SlotNewConnection();
    void on_checkBoxAutoMode_clicked();

    void on_pushButtonTransmitSetting_clicked();

private:
	Ui::DiskManagerClass ui;
	bool SaveSetting(QIODevice *f);
	bool LoadSetting(QIODevice *f);
};

#endif // DISKMANAGER_H
