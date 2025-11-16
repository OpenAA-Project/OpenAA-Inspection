#if	!defined(XLEARNINGSERVER_H)
#define	XLEARNINGSERVER_H

#include"XParamBase.h"
#include"XIntClass.h"
#include <QSqlDatabase>
#include <QThread>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XServerLayerBase.h"

class	AlgorithmLibraryList;
class	AlgorithmThreshold;
class	LearningServer;
class	QReadWriteLock;

class	ParamLearningServer : public ParamBase
{
public:
	QString	DatabaseHost;
	QString	DatabaseFileName;

	QString	LocalDatabase_FileName;
	int32	LocalDatabase_Port;
	QString	LocalDatabase_HostName;
	QString	TransDatabaseIP;
	int		TransDatabasePort;

	ParamLearningServer(void);
	~ParamLearningServer(void);

	virtual	QString	GetDataText(void){	return("LearningServer Data");	};
	virtual	QString	GetDefaultFileName(void){	return("LearningServer.dat");	}

	ParamLearningServer	&operator=(ParamBase &src);
};


class	ServerBase : public ServiceForLayers
{
	ParamLearningServer	*GlobalParam;
	//QSqlDatabase		*Database;
public:
	ServerBase(LayersBase *Base);
	~ServerBase(void);

	void	Initial(void);
	void	Release(void);
	bool	LoadParam(const QString &ParamFileName);
	bool	LoadDefault(void);

	QSqlDatabase	&GetDatabase(void);


	ParamLearningServer	*GetParamGlobal(void);
};

class LibTypeIDResult : public NPList<LibTypeIDResult>
{
public:
	int		LibType;
	int		LibID;
	double	EnStrength;
	int		ParamNumber;

	LibTypeIDResult(void){	EnStrength=0;	ParamNumber=-1;	}
};

class LearnigAlgorithmThresholdPointer : public AlgorithmThresholdPointer
{
public:
	LearningInDBThreshold	ParamThreshold;
	double	Value;

	LearnigAlgorithmThresholdPointer(AlgorithmThreshold *AThr ,int LibType ,int LibID)
		:AlgorithmThresholdPointer(AThr,LibType,LibID)	{	Value=0;	}
};


class ThreadServer : public QThread , public ServiceForLayers
{
	Q_OBJECT
		
	LearningServer		*Parent;
public:
	QReadWriteLock		AccessData;
	LearningInDBAll		LearningList;
	AlgorithmThresholdPointerContainer	AThrContainer;
	NPListPack<LibTypeIDResult>			LibTypeIDResultData;
public:
	volatile	bool	Terminated;
	volatile	bool	Halted;
	volatile	bool	Running;

	ThreadServer(LearningServer *p,LayersBase *Base);
	~ThreadServer(void);

	void	StopExecute(void);
	void	StartExecute(void);
	virtual	void	run();

signals:
	void	SignalShowList();
	void	SignalUpdateList();
private:
	void	LoadDatabase(void);
	void	MakeLibList(AlgorithmLibraryListContainer &ListContainer);
	void	OptimizeLib(AlgorithmLibraryList &Lib);
	double	CalcEnStrength(AlgorithmLibraryList &Lib,AlgorithmThreshold	*AControler);

public:
	AlgorithmThreshold	*CalcProcess(LearningInDB *s,LearningParamInDB *L
									,AlgorithmThreshold *ALibController
									,bool &Ret);
public:
	LibTypeIDResult	*GetLibTypeIDResultData(int LibType, int LibID);
};



extern	ServerBase	*ServerBaseData;

#endif
