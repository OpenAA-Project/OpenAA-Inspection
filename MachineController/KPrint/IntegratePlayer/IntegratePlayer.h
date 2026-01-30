/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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