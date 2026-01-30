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

#ifndef CONTECNC2D_H
#define CONTECNC2D_H

#include <QMainWindow>
#include "ui_ContecNC2D.h"
#include "XContecNC2DInfo.h"
#include<QTimer>
#include "XContecNC2DPipe.h"


class ContecNC2D : public QMainWindow
{
	Q_OBJECT

	short Id ;
	ContecNC2DInfo	Data;
	int				CurrentScan;
	QTimer			TM;
	ContecNC2DPipe	PipeServer;
public:
	ContecNC2D(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ContecNC2D();


	void	ExeStart();
	void	ExeStep();
	bool	IsEnd();
	bool	IsStartButton();

private slots:
    void on_pushButtonGoStartPos_clicked();
    void on_pushButtonStartScan_clicked();
    void on_pushButtonJogYP_clicked();
    void on_pushButtonJogYM_clicked();
    void on_pushButtonJogXP_clicked();
    void on_pushButtonJogXM_clicked();
    void on_pushButtonGoOrigin_clicked();
    void on_pushButtonConvertToScan_clicked();
    void on_pushButtonSave_clicked();
    void on_toolButtonVacuum_clicked();
    void on_pushButtonStop_clicked();
	void	SlotTimeOut();
    void on_toolButtonPatlightR_clicked();
    void on_toolButtonPatlightY_clicked();
    void on_toolButtonPatlightG_clicked();

private:
	Ui::ContecNC2DClass ui;

	void	ShowDataToWindow(void);
	void	DataFromWindow(void);

	bool	RButtonON;
	bool	LButtonON;
	bool	FootSWON;
	bool	AreaSewnsorON;
	bool	EmergencyON;

	bool	FootVacuumON;
	bool	lastFootSWON;

	bool	CheckOnMoving(void);
};

#endif // CONTECNC2D_H