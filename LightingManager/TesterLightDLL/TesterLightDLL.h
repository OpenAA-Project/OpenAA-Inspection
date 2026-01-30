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

#ifndef TESTERLIGHTDLL_H
#define TESTERLIGHTDLL_H

#include <QMainWindow>
#include "ui_TesterLightDLL.h"
#include <QTimer>
#include <QMutex>
#include "XServiceForLayers.h"

class TesterLightDLL : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	QTimer	IdleTimer;
	QMutex	MutexTimerFunc;
public:
	TesterLightDLL(LayersBase *Base ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TesterLightDLL();
	
	virtual	void	closeEvent(QCloseEvent *event)	override;
private slots:
    void    on_pushButtonLoadDLL_clicked();
    void    on_toolButtonOnOff_clicked();
    void    on_pushButtonSetting_clicked();
    void    on_pushButtonSaveToDefault_clicked();
    void on_pushButtonLoadFromDefault_clicked();
    void on_pushButtonSaveAs_clicked();
    void on_pushButtonLoadAs_clicked();

	void	SlotReflectDataInDialog();
	void	SlotReflectOnOffInDialog(bool LightOn);
protected slots:
	void	TimeOutForIdle(void);

private:
	Ui::TesterLightDLLClass ui;
};

#endif // TESTERLIGHTDLL_H