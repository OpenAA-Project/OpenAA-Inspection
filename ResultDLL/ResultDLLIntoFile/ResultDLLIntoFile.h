#ifndef RESULTDLLINTOFILE_H
#define RESULTDLLINTOFILE_H

#include "resultdllintofile_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include <QObject>
#include "XMLClient.h"
#include "XTypeDef.h"
#include <QThread>
#include "XServiceForLayers.h"
#include "XWriteResultThread.h"

class	FileThread;
class	ResultDLLIntoFile;
class	ResultInspectionForStockPointerContainer;

#pragma	pack(push,1)

struct	NGAreaRectangle
{
	char	Type;
	int32	X1,Y1,X2,Y2;
};

struct	NGAreaEllipse
{
	char	Type;
	int32	X1,Y1,X2,Y2;
};

struct	NGAreaRotEllipse
{
	char	Type;
	int32	Cx,Cy,Rx,Ry;;
	double	Angle;
};

struct	NGAreaRing
{
	char	Type;
	int32	X11,Y11,X12,Y12;
	int32	X21,Y21,X22,Y22;
};

#pragma	pack(pop)

class	ResultDLLIntoThread : public QThread ,public ServiceForLayers
{
	ResultDLLIntoFile	*Parent;
public:
	volatile	bool	Terminated;
	ResultInspection	*ResBuff[500];
	ResultInspectionForStockPointerContainer	ShadowResBuff[500];
	DWORD				PushedTime[500];
	DWORD				LastTime;
	int					CountResBuff;
	QMutex	ChangePoint;
	int		WPoint;
	int		RPoint;

	ResultDLLIntoThread(LayersBase *Base,ResultDLLIntoFile *p);

	void	Push(ResultInspection *Res);
	virtual	void	run();
};

struct	DbgInfoTable
{
	QString	FileName;
	int64	InspectionID;
	XDateTime	OTime;
	DWORD		DiffMilisec;
	bool		SaveInPage[100][10];
};

class	ResultDLLIntoFile : public QObject ,public ResultDLLBaseRoot
{
	Q_OBJECT

	bool		OutputLibData;
	QString		SharedFolder;
	QString		LastPath;
	bool		UseLotNameInFileName;

	struct	DbgInfoTable	*DbgDim;
	int		DbgWPoint;
	DWORD	LastTime;

	int		NGFlag;
	ResultDLLIntoThread	RThrrad;
public:
	bool	SaveNGImage;
	bool	WritePageDirectly;

	ResultDLLIntoFile(LayersBase *Base);
	virtual ~ResultDLLIntoFile(void);

	virtual	QString	GetDataText(void)			{	return QString("Result into File");		}
	virtual	QString	GetDefaultFileName(void)	{	return QString("ResultDLLIntoFile.dat");	}

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,const XDateTime &InspectedTime 
								,ResultInspection *Res 
								,const QString &LotID,int phase, int localPage);

	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res);
	bool	OutputInLotChangedSlave(int LocalPage);
	bool	OutputInLib(void);

	virtual	bool	OutputResultDirectly(int mode ,ResultInspection &Res,GUIDirectMessage *packet);
	bool	OutputCommonRaw(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);

protected:
	QString	GetLotID(void);
	QString	GetLotName(void);
	int		GetMachineID(void);
	int		GetMasterCode(void);
	QString	GetMasterName(void);

private:
	QString	GetFileName(void);

	bool	OutputInLibData(LogicDLL *L ,int32 LibID
									,QIODevice *f);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
						,FileThread &File,int32 MachineID 
						,const XDateTime &InspectedTime 
						,ResultInspection *Res 
						,const QString &LotID,int phase, int localPage);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
						,QBuffer &File,int32 MachineID 
						,const XDateTime &InspectedTime 
						,ResultInspection *Res 
						,const QString &LotID,int phase, int localPage);
};

#endif // RESULTDLLINTOFILE_H
