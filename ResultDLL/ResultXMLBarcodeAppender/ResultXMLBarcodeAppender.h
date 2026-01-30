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

#ifndef RESULTXMLBARCODEAPPENDER_H
#define RESULTXMLBARCODEAPPENDER_H

#include "resultxmlbarcodeappender_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XMLClient.h"
#include "XTypeDef.h"
#include "ResultXMLV3.h"

class	ResultInspectionForStockPointerContainer;

class ResultXMLBarcodeAppender : public ResultXMLV3
{
	Q_OBJECT

	int		SmallLotCounter;
	QString		LastLotID;

	QString		iLotID;
	QString		iLotName;
	QString		iRemark;
	int64		InspectionID;

	volatile	bool3	FlagCommon;
	volatile	bool3	FlagSlave;
	bool	FixedConnection;

public:
	ResultXMLBarcodeAppender(LayersBase *Base);
	~ResultXMLBarcodeAppender();

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,const XDateTime &InspectedTime ,ResultInspection *Res 
								,const QString &LotID,int phase, int localPage);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)	override;

protected:
	QString	GetLotID(void)				;
	QString	GetLotName(void)			;
	int64	GetInspectionID(void)		;
	int64	GetInspectionNumber(void)	;
	int		GetMachineID(void)			;
	int		GetMasterCode(void)			;
	QString	GetMasterName(void)			;

	QString	GetXMLTableName(const QString &StrLID);

private:
	bool	OpenOperation(const QString &StrLID ,XMLOperationHandle **Handle);

signals:
	void	SignalOutputCommon(QString StrLID ,QString Str);
	void	SignalOutputSlave(QString StrLID ,QString SearchStr,QString InsData);

private slots:
	void	SlotOutputCommon(QString StrLID ,QString Str);
	void	SlotOutputSlave(QString StrLID ,QString SearchStr,QString InsData);
};

#endif // RESULTXMLBARCODEAPPENDER_H