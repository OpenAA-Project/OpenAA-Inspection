#pragma once
#include<QImage>
#include<QString>
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XDateTime.h"
#include "XAlgorithmLibrary.h"

class	LogicDLL;

class	ReportDataStructure
{
public:
	XDateTime	ReportedTime;
	int			MasterCode;
	XDateTime	RegTime;
	QString		BoardName;
	QString		Remark;
	int			WorkerID;
	QString		WorkerName;
	int			MachineID;
	QString		MachineName;
	XDateTime	LastEditedTime;
	int			CategoryID;
	QString		Category;
	QImage		TopView;
	int			DotPerLine;
	int			MaxLines;
	int			PageNumb;
	int			LayerNumb;
	int			PhaseNumb;
	IntList		RelatedMasterID;
	int			LibFolderID;
	int			ThresholdLevelID;
	int			ThresholdLevelParentID;

	class	ReportAlgorithmList : public NPList<ReportAlgorithmList>
	{
	public:
		QString	DLLRoot;
		QString	DLLName;
		int		TotalItemCount;

		class	ReportLibraryList : public NPList<ReportLibraryList>
		{
		public:
			int		LibID;
			QString	LibName;
			int		ItemCount;
			int64	TotalAreaDots;

			ReportedTopicContainer	LibraryTopics;
			ReportedTopicContainer	ItemTypicalTopics;

			ReportLibraryList(void){	ItemCount=0;	TotalAreaDots=0;	}
		};

		NPListPack<ReportLibraryList>	ReportLibraryContainer;
		ReportedTopicContainer			AlgorithmTopics;

		ReportAlgorithmList(void){	TotalItemCount=0;	}
	};
	NPListPack<ReportAlgorithmList>	ReportAlgorithmContainer;

	ReportDataStructure(void){}
};

class	AlgorithmForReport : public QObject ,public ServiceForLayers
{
	Q_OBJECT

	int	MasterCode;
	int	MachineID;

	AlgorithmLibraryContainer	*sALibC;
	int							sLibID;
	//AlgorithmLibrary			*RetLib;
	AlgorithmLibraryLevelContainer	*RetLib;
	volatile	bool			Flag;
	bool						sRet;

	LogicDLL	**LoadedLogicDLL;
	int			LoadedLogicDLLCount;
public:
	ReportDataStructure	ReportData;

	AlgorithmForReport(int masterCode ,int machineID,LayersBase *base);
	~AlgorithmForReport(void);

	virtual void run ();

	bool	SaveEXCEL(const QString &filename);

	void	GetLibraryOutOfThread(void);
	void	LoadMaster(void);

private:
	bool LoadDataFromMaster(int masterCode);
	bool LoadAlgorithmData(void);
	bool MakeAlgoData(void);


signals:
	void	SignalStep(QString Msg);
	void	SignalReqLibrary();

};


