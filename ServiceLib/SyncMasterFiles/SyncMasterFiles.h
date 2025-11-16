#ifndef SYNCMASTERFILES_H
#define SYNCMASTERFILES_H

#include <QMainWindow>
#include "ui_SyncMasterFiles.h"
#include "NList.h"
#include <QThread>
#include <QMutex>
#include "XDateTime.h"

class	SyncMasterFiles;

class	FileAndTimeStamp : public NPList<FileAndTimeStamp>
{
public:
	QString		FileName;
	XDateTime	TimeStamp;

	FileAndTimeStamp(void){}
	FileAndTimeStamp	&operator=(FileAndTimeStamp &src);
};

class	FileAndTimeStampContainer : public NPListPack<FileAndTimeStamp>
{
public:
	FileAndTimeStampContainer(void){}

	FileAndTimeStampContainer	&operator=(FileAndTimeStampContainer &src);
};

class	ThreadMakeFileTable : public QThread
{
	Q_OBJECT
	SyncMasterFiles	*PBase;
public:
	bool	TerminationFlag;

	ThreadMakeFileTable(SyncMasterFiles *pbase ,QObject *parent);

	virtual	void	run(void)	override;
	bool	CopyFileInThread(const QString &FileName ,const QString &DestPath);
	bool	UpdateFile(const QString &FileName ,const QString &DestPath);
	bool	RemoveFile(const QString &FileName);

signals:
	void	SignalCopyed();
	void	SignalUpdated();
	void	SignalRemoved();
	void	SignalStep();
};

class SyncMasterFiles : public QMainWindow
{
	Q_OBJECT

	ThreadMakeFileTable			ThreadChecker;
public:
	FileAndTimeStampContainer	SrcFiles;
	FileAndTimeStampContainer	DstFiles;
	QString SourcePath;
	QString DestPath;
	int		SleepTimeSec;
	QStringList		ExcludedFiles;
	bool			SrcPathExists;

	QStringList		MessagesFromThread;
	QMutex			MessagesMutex;

	SyncMasterFiles(const QString &_SourcePath ,const QString &_DestPath ,int _SleepTimeSec
					,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~SyncMasterFiles();

	int		MakeContainer(const QString &path ,FileAndTimeStampContainer &ret ,bool &PathExists);

	QString	GetSettingFileName(void){	return QString(/**/"SyncMasterFilesSetting.dat");	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	virtual	void	closeEvent(QCloseEvent *ev)	override;

private slots:
	void	SlotCopyed();
	void	SlotUpdated();
	void	SlotRemoved();
	void	SlotStep();

    void on_pushButtonAddExcluded_clicked();
    void on_pushButtonDelExcluded_clicked();

private:
	Ui::SyncMasterFilesClass ui;
};



#endif // SYNCMASTERFILES_H
