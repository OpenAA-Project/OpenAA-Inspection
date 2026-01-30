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

#ifndef RESULTXMLPRINTFAST_H
#define RESULTXMLPRINTFAST_H

#include "resultxmlprintfast_global.h"
#include "ResultXMLV3.h"

class	ResultInspectionForStockPointerContainer;

class ResultXMLPrintFast : public ResultXMLV3
{
	Q_OBJECT

	int		SmallLotCounter;
	QString		LastLotID;

	QString		iLotID;
	QString		iLotName;
	QString		iRemark;
	int64		InspectionID;

	volatile	bool3	FlagCommon;
	bool	FixedConnection;
	QString CommonStrLID ,CommonStr;
	QString SlaveStrLID ,SlaveSearchStr,SlaveInsData;
	char	*SerchStr;
	char	*ResList;
public:
	ResultXMLPrintFast(LayersBase *Base);
	~ResultXMLPrintFast();

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,const XDateTime &InspectedTime 
								,ResultInspection *Res 
								,const QString &LotID,int phase, int localPage);
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

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
	void	SignalOutputCommon();

private slots:
	void	SlotOutputCommon();
};

#endif // RESULTXMLPRINTFAST_H