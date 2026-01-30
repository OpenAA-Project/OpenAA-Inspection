/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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