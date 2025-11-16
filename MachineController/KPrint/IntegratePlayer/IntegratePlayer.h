#ifndef INTEGRATEPLAYER_H
#define INTEGRATEPLAYER_H

#include <QMainWindow>
#include "ui_IntegratePlayer.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XCameraClass.h"
#include <QThread>
#include "XBoolList.h"
#include <QMdiArea>
#include <QSignalMapper>
#include <QProcess>
#include "NListComp.h"
#include <QSharedMemory>
#include <QString>
#include <QMutex>
#include "XMainSchemeMemory.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QMutex>

#include "NetworkPIOLib.h"
#include "ShowIOForm.h"

#define	DefaultPIOPort	18830
class	PIOClass;
class	ExecuteIntegratePlayer;

class IntegratePlayer : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	NetworkPIOServer	PIOServer;
	ShowIOForm			*ShowIOFormInst;
	PIOClass	*OpenedPIO;
	QMutex		IOMutex;

	bool	ONTop	;
	bool	ONBottom;
	DWORD	TopLastTime;
	DWORD	BottomLastTime;

	QTimer	TM;

public:
	IntegratePlayer(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~IntegratePlayer();

	void	Initial(ExecuteIntegratePlayer *ExeIns[16]);

	void	GetClientIDList(IntList &IDList);
	int		GetNetworkPIOCount(void);
	int		GetIOInBitCount (int ID);
	int		GetIOOutBitCount(int ID);

	int		GetPIOInBit(int PIOID ,int PortNo);
	void	SetPIOOutBit(int PIOID ,int PortNo ,BYTE data);
	int		GetPIOOutBit(int PIOID ,int PortNo);

	QString	GetPIOInBitName	(int PIOID ,int BitNo);
	QString	GetPIOOutBitName(int PIOID ,int BitNo);

	void	SetResult(bool OKMode,int UnitNo);

private slots:
    void	on_pushButtonCheckIO_clicked();
	void	SlotTopOK();
	void	SlotTopNG();
	void	SlotBottomOK();
	void	SlotBottomNG();
	
	void	SlotTimerOut();

private:
	Ui::IntegratePlayerClass ui;
};

#endif // INTEGRATEPLAYER_H
