#pragma once

#include "resultwritecsvbarcodeline_global.h"
#include "XResult.h"


class	ResultInspectionForStockPointerContainer;
	
class	ResultWriteCSVBarcodeLine : public ResultDLLBaseRoot
{
public:
	QString	OutputPath;

	ResultWriteCSVBarcodeLine(LayersBase *Base);
	~ResultWriteCSVBarcodeLine(void);	
	
	virtual	QString	GetDataText(void)			{	return QString("ResultWriteCSVBarcodeLine");		}
	virtual	QString	GetDefaultFileName(void)	{	return QString("ResultWriteCSVBarcodeLine.dat");	}

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
						,int32 MachineID ,const XDateTime &InspectedTime 
						,ResultInspection *Res 
						,const QString &LotID,int phase, int localPage);
	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID);
private:
	QString	MakeLockFile(int32 MachineID ,int MasterCode,int Page);
	QString	MakeCSVFile (int32 MachineID ,int MasterCode,int Page);
};