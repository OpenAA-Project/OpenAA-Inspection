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

#ifndef MAINTAINER_H
#define MAINTAINER_H

#include <QMainWindow>
#include "ui_Maintainer.h"
#include "XMaintainer.h"

class Maintainer : public QMainWindow
{
	Q_OBJECT

	QString		SettingFileName;

	MaintainThread	MaintainThreadInst;
	int	MaxLines;
public:
	MaintainerSetting	DeleteData;
	MaintainerSetting	BackupData;
	QString		LogFileName;
	volatile	bool	NowOnShowing;
	volatile	int		QueuedCounter;
	volatile	bool	ModeExecuteNow;
	//QMutex		MutexQueuedCounter;

	Maintainer(const QString &settingFileName ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~Maintainer();

	void	DoneRemoveFile(const QString &FileName);
	void	DoneBackupFile(const QString &FileName);
	void	DoneRemoveDir (const QString &Path);
	void	Step(void);
	void	SetMaxStep(const QString &ActionName ,const QString &path ,int MaxN);
signals:
	void	SignalDoneRemoveFile(const QString &FileName);
	void	SignalDoneBackupFile(const QString &FileName);
	void	SignalDoneRemoveDir (const QString &Path);
	void	SignalStep();
	void	SignalSetMaxStep(const QString &ActionName ,const QString &path ,int MaxN);
private slots:
    void on_pushButtonSettingDelete_clicked();
    void on_pushButtonSettingBackup_clicked();
    void on_pushButtonSetting_clicked();

	void	SlotDoneRemoveFile(const QString &FileName);
	void	SlotDoneBackupFile(const QString &FileName);
	void	SlotDoneRemoveDir (const QString &Path);
	void	SlotStep();
	void	SlotSetMaxStep(const QString &ActionName ,const QString &path ,int MaxN);
    void on_pushButtonExecuteNow_clicked();

private:
	Ui::MaintainerClass ui;

	bool	SaveSetting(void);
	bool	LoadSetting(void);
};

#endif // MAINTAINER_H