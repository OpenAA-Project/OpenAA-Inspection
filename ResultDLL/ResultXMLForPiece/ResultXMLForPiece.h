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

#ifndef RESULTXMLFORPIECE_H
#define RESULTXMLFORPIECE_H

#include "resultxmlforpiece_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XMLClient.h"

class	ResultInspectionForStockPointerContainer;

class	ResultXMLForPiece : public ResultDLLBaseRoot,public XMLServerHandle
{
	XMLOperationHandle	*HandleCommon;
	XMLOperationHandle	*HandlePage;
	XMLOperationHandle	*HandleRemove;
	XMLOperationHandle	*HandleLastID;
	XMLOperationHandle	*HandlePiece;
	XMLOperationHandle	*HandleInsLib;
	bool				OutputLibData;
public:
	ResultXMLForPiece(LayersBase *Base);
	~ResultXMLForPiece(void);	
	
	virtual	QString	GetDataText(void)			override{	return QString("XML Result");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ResultXMLForPiece.dat");	}

	virtual	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	virtual	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,const XDateTime &InspectedTime 
								,ResultInspection *Res 
								,const QString &LotID,int phase, int localPage);
	virtual	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID);
	bool	GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID);

	bool	OutputInLotChangedSlave(int LocalPage);
	bool	OutputInLib(void);
	bool	SearchLotID(const QString &iLotID);
private:
	void	OutputInLibData(LogicDLL *L ,int LibID
							,QStringList &RetInsertStrings);

	bool	OpenOperation(XMLOperationHandle **Handle);
	QString	CreateNGFileNameForSlaveWithDrive(int localPage ,ResultInspection *Res ,int PieceAreaID);

	QString	GetXMLTableName(void);
	QString	GetXMLTableName(const QString &iLotID);
};
#endif // RESULTXMLFORPIECE_H