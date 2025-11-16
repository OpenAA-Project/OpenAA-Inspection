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
