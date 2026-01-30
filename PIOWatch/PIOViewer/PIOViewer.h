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

#ifndef PIOVIEWER_H
#define PIOVIEWER_H

#include <QMainWindow>
#include "ui_PIOViewer.h"
#include <QThread>
#include "XTypeDef.h"
#include "XPIOSignal.h"
#include "XServiceForLayers.h"

class	PIOClass;
class	PIOThread;

class PIOViewer : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	PIOThread	*PIOThreadPointer;
public:
	PIOViewer(LayersBase *Base ,bool StartOnDLL,const QString &StartDLL
			, QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PIOViewer();
	
	PIOClass	*OpenedPIO;

	bool	IsChangedPIO(void);
	void	SetSignalsInData(void);

	BYTE	LastInByte[64];
	BYTE	LastOutByte[64];

	DWORD		StartMilisec;
	SignalData	*InBitStock;
	SignalData	*OutBitStock;

	bool	SaveSignal(QIODevice *f);
	bool	LoadSignal(QIODevice *f);

	QString	GetSignalInName(int BitNumber);
	QString	GetSignalOutName(int BitNumber);
	int		GetSignalInBitCount(void);
	int		GetSignalOutBitCount(void);
	DWORD	GetTotalSignalMilisec(void);
	SignalData	*GetSignal(bool InData,int BitNumber);

	virtual	void	closeEvent(QCloseEvent *ev)	override;

private slots:
        void on_pbClose_clicked();
        void on_pushButtonSelectIODefineFile_clicked();
        void on_pushButtonOpenPIO_clicked();
        void on_pushButtonShowSignal_clicked();
        void on_chkEchoBack_clicked();
        void on_comboBoxBoardNumber_currentIndexChanged(int index);
		void	SlotShowIO();
        void on_twOUT_itemChanged(QTableWidgetItem *item);
        void on_pushButtonSaveSignal_clicked();
        void on_pushButtonLoadSignal_clicked();
        void on_pushButtonClear_clicked();

private:
	Ui::PIOViewerClass ui;
};

class PIOThread : public QThread
{
	Q_OBJECT
	PIOViewer	*Parent;

public:
	volatile	bool	HaltOn;

	PIOThread(PIOViewer *parent);

	volatile	bool	ShouldFinish;
signals:
	void	SignalShowIO();

protected:
	void run();

};

#endif // PIOVIEWER_H