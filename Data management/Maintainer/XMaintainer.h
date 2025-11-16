#if	!defined(XMaintainer_h)
#define	XMaintainer_h

#include <QStringList>
#include <QIODevice>
#include <QThread>
#include <QDateTime>
#include <QFileInfo>
#include "XTypeDef.h"
#include "NList.h"

class Maintainer;

class	MaintainerSetting
{
public:
	QStringList		FileNames;
	QStringList		FolderNames;
	bool			UseDaysToKeepTerm;
	bool			UseMonthsToKeepTerm;
	int32			TermDaysToKeep;
	int32			TermMonthsToKeep;
	bool			PrioritySpace;
	int32			SpaceGBRemaining;
	int32			CheckingHour	;
	int32			CheckingMinute	;
	QString			DestinationPath	;

	MaintainerSetting(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsOlder(const QDateTime &FileStamp , const QDateTime &CurrentTime);
};

class	MFileList : public NPList<MFileList>
{
public:
	QString	AbsFileName;
	int64	FileSize;
	QDateTime	TimeStamp;

	MFileList(const QFileInfo &Info);
	virtual	int	Compare(MFileList &src)	override;
};




class	MaintainThread : public QThread
{
	Maintainer	*Parent;
public:
	int		WaitingMilisec;
	volatile	bool	Terminated;

	MaintainThread(Maintainer *p,QObject * parent);

	virtual	void run ();
private:
	bool	RemoveAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime ,NPListPack<MFileList> &AliveFiles);
	bool	BackupAllFilesAndFolder(const QString &Path ,const QDateTime &CurrentTime ,NPListPack<MFileList> &AliveFiles);
};


#endif
