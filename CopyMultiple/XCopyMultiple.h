#if	!defined(XCopyMultiple_h)
#define	XCopyMultiple_h

#include <QStringList>
#include "NList.h"
#include <QThread>
#include <QIODevice>
#include <QObject>
#include <QWidget>

class	ThreadCopy;

class	CopyMultipleData : public QObject
{
	Q_OBJECT
public:
	QString			SourcePath;
	QStringList		SearchFilter;
	QStringList		ExcludedFilter;

	QStringList		Destinations;

	class	FoundFileClass : public NPList<FoundFileClass>
	{
	public:
		CopyMultipleData	*Parent;

		QString		FoundFile;

		enum	State
		{
			_NotYet		=0
			,_Copied	=1
			,_NotCopied	=2
		}*CopiedState;

		FoundFileClass(CopyMultipleData	*parent);
		~FoundFileClass(void);
	};
	NPListPack<FoundFileClass>	SourceFiles;	//åüçıÇ≥ÇÍÇΩÉtÉ@ÉCÉã

	volatile	bool	TerminateCopy;
	ThreadCopy	**ThreadCopyDim;

	CopyMultipleData(void){	ThreadCopyDim=NULL;		TerminateCopy=false;	}
	~CopyMultipleData(void);

	int		GetDestCount(void);

	bool	SaveFilter(QIODevice *f);
	bool	LoadFilter(QIODevice *f);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	MakeFoundList(void);
	void	MakeFoundList(const QString &pathname);

	void	StartCopy(QWidget *parent);

signals:
	void	SignalFinishCopy();
private slots:
	void	FinishedThreadCopy();
};

class	ThreadCopy : public QThread
{
	CopyMultipleData	*DataParent;
	QString				DestPath;
	int					DestNumber;
public:
	ThreadCopy(CopyMultipleData *_DataParent 
				,const QString &_DestPath,int DestN
				,QObject *parent);

	virtual void run ();
	bool makeDirectory(QString pathname,QString oldname);
};

#endif