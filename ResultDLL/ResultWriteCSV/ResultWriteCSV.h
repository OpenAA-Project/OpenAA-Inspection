#ifndef RESULTWRITECSV_H
#define RESULTWRITECSV_H

#include "resultwritecsv_global.h"

class	ResultInspectionForStockPointerContainer;
	
class	ResultWriteCSV : public ResultDLLBaseRoot
{
public:
	QString	OutputPath;

	ResultWriteCSV(LayersBase *Base);
	~ResultWriteCSV(void);	
	
	virtual	QString	GetDataText(void)			{	return QString("ResultWriteCSV");		}
	virtual	QString	GetDefaultFileName(void)	{	return QString("ResultWriteCSV.dat");	}

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
						,int32 MachineID ,const XDateTime &InspectedTime 
						,ResultInspection *Res 
						,const QString &LotID,int phase, int localPage);
	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID);
private:
	QString	MakeLockFile(int32 MachineID ,int MasterCode ,const XDateTime &InspectedTime);
	QString	MakeCSVFile(int32 MachineID ,int MasterCode ,const XDateTime &InspectedTime);
};
#endif // RESULTWRITECSV_H
