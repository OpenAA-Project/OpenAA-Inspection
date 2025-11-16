#if	!defined(XIntegrationBasePacket_h)
#define	XIntegrationBasePacket_h

#include "XIntegrationPacketComm.h"
#include "XReportedTopic.h"
#include "XDataInLayer.h"

class	AccessToPage;

class	IntegrationReqMasterImage : public IntegrationCmdPacketBase
{
public:
	struct{
		int	Phase;
		int	Page;
		int	Layer;
		int	TopY;
		int	LineCount;
		bool MixMaster;
	}Info;

	IntegrationReqMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckMasterImage : public IntegrationCmdPacketBase
{
public:
	struct{
		int	Phase;
		int	Page;
		int	Layer;
		int	TopY;
		int	LineCount;
		int	DotPerLine;
		bool	OK;
	}Info;
	BYTE	*Data;
	int		AllocatedByteCount;

	IntegrationAckMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	virtual	~IntegrationAckMasterImage(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationReqMasterInfo : public IntegrationCmdPacketBase
{
public:

	IntegrationReqMasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckMasterInfo : public IntegrationCmdPacketBase
{
public:
	int	MasterCode	;
	int	PhaseNumb	;
	int	PageNumb	;
	//int	LayerNumb	;
	DataInPage::ConstructionData	*CData;
	int32	*LayerNumbDim;
	double	TransformUnitPerPixelX;
	double	TransformUnitPerPixelY;
	AccessToPage		*AccessToPageDim;

	IntegrationAckMasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);
	~IntegrationAckMasterInfo(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:

};


class	IntegrationReqAlive : public IntegrationCmdPacketBase
{
public:

	IntegrationReqAlive(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckAlive : public IntegrationCmdPacketBase
{
public:
	IntegrationAckAlive(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	IntegrationExecuteInitialAfterEdit: public IntegrationCmdPacketBase
{
public:
	IntegrationExecuteInitialAfterEdit(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//---------------------------------------------------------------------------------------------------
class	IntegrationCmdAddPhase : public IntegrationCmdPacketBase
{
public:
	QStringList PhaseNameList;

	IntegrationCmdAddPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdDelPhase : public IntegrationCmdPacketBase
{
public:
	int	PhaseNo;

	IntegrationCmdDelPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdChangeCurrentPhase : public IntegrationCmdPacketBase
{
public:
	int	PhaseNo;

	IntegrationCmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdReqPhaseNames : public IntegrationCmdPacketBase
{
public:

	IntegrationCmdReqPhaseNames(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckPhaseNames : public IntegrationCmdPacketBase
{
public:
	QStringList	PhaseNames;
	IntegrationCmdAckPhaseNames(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetPhase : public IntegrationCmdPacketBase
{
public:
	int		Phase;
	QString	PhaseName;

	IntegrationCmdSetPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=======================================================================================================

class	AlgorithmRootNameList : public NPListSaveLoad<AlgorithmRootNameList>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	WORD	AlgorithmType;
	int		LibType;

	AlgorithmRootNameList(void){	AlgorithmType=0;	LibType=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AlgorithmRootNameListContainer : public NPListPackSaveLoad<AlgorithmRootNameList>
{
public:
	AlgorithmRootNameListContainer(void){}

	virtual	AlgorithmRootNameList	*Create(void){	return new AlgorithmRootNameList();	}
};


class	IntegrationReqUsageAlgorithm : public IntegrationCmdPacketBase
{
public:
	IntegrationReqUsageAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckUsageAlgorithm : public IntegrationCmdPacketBase
{
public:
	AlgorithmRootNameListContainer	Datas;

	IntegrationAckUsageAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	

private:

};

//=======================================================================================================

class	IntegrationReqReportedTopics : public IntegrationCmdPacketBase
{
public:
	QString	DLLRoot;
	QString	DLLName;

	IntegrationReqReportedTopics(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckReportedTopics : public IntegrationCmdPacketBase
{
public:
	ReportedTopicsInItemContainer	Datas;

	IntegrationAckReportedTopics(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//=======================================================================================================
class	IntegrationRebuildThresholdLevel: public IntegrationCmdPacketBase
{
public:
	IntegrationRebuildThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationSetThresholdLevel : public IntegrationCmdPacketBase
{
public:
	int		LevelID;

	IntegrationSetThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationSetCurrentIntoThresholdLevel : public IntegrationCmdPacketBase
{
public:
	int		LevelID;

	IntegrationSetCurrentIntoThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCopyThresholdLevel : public IntegrationCmdPacketBase
{
public:
	int		SourceLevelID;
	int		DestLevelID;

	IntegrationCopyThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif