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

#ifndef RESULTXMLMULTIDELIVERY_H
#define RESULTXMLMULTIDELIVERY_H

#include "resultxmlmultidelivery_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XMLClient.h"
#include "XTypeDef.h"

class	ResultInspectionForStockPointerContainer;

class	ResultXMLMultiDelivery : public XMLServerHandle,public ResultDLLBaseRoot
{
	Q_OBJECT

protected:
	class	DeliveryPacket
	{
	public:
		XMLOperationHandle	*HandleCommon;
		XMLOperationHandle	*HandlePage;
		XMLOperationHandle	*HandleRemove;
		XMLOperationHandle	*HandleLastID;
		XMLOperationHandle	*HandlePiece;
		XMLOperationHandle	*HandleInsLib;

		QString		iLotID;		//Contain DeliveryNo and SubLotNumber
		QString		iLotName;
		int64		InspectionID;

		DeliveryPacket(void);
		~DeliveryPacket(void);
	};
	QStringList		DeliveryInfoList;
	DeliveryPacket	Delivery[1000];
	bool			OutputLibData;
	QString			iRemark;

public:
	ResultXMLMultiDelivery(LayersBase *Base);
	virtual ~ResultXMLMultiDelivery(void);	
	
	virtual	QString	GetDataText(void)			override{	return QString("XML ResultXMLMultiDelivery");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ResultXMLMultiDelivery.dat");		}

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
						,int32 MachineID ,const XDateTime &InspectedTime 
						,ResultInspection *Res 
						,const QString &LotID,int phase, int localPage);
	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID);
	bool	GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID);

	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)	override;
	bool	OutputInLotChangedSlave(int LocalPage);
	bool	OutputInLib(void);
	bool	SearchLotID(const QString &iLotID);
	bool	CheckConnection(void);

	int		SearchDeliveryNumber(const QString &DeliveryInfo);
	int		GetDeliveryCount(void)	{	return DeliveryInfoList.count();	}
	QString	GetDeliveryInfoList(int n);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	ResultInspection	*TmpRes;

	QString	GetLotID(int DeliveryNo);
	QString	GetLotName(int DeliveryNo);

	int64	GetInspectionNumber(void);
	int		GetMachineID(void);
	int		GetMasterCode(void);
	QString	GetMasterName(void);
	int64	GetInspectionID(void);

private:
	bool	OpenOperation(int DeliveryNo,XMLOperationHandle **Handle);
	void	OutputInLibData(LogicDLL *L ,int LibID
							,QStringList &RetInsertStrings);

	QString	GetXMLTableName(int DeliveryNo);
	QString	GetXMLTableName(const QString &iLotID);

	volatile	bool3	FlagCommon;
	volatile	bool3	FlagSlave;
	bool	FixedConnection;

signals:
	void	SignalOutputCommon(int DeliveryNo,QString Str);
	void	SignalOutputSlave(int DeliveryNo,QString SearchStr,QString InsData);

private slots:
	void	SlotOutputCommon(int DeliveryNo,QString Str);
	void	SlotOutputSlave(int DeliveryNo,QString SearchStr,QString InsData);
};


inline	QString	ResultXMLMultiDelivery::GetDeliveryInfoList(int n)
{
	if(n<DeliveryInfoList.count()){
		return DeliveryInfoList[n];
	}
	return "";
}

class	CmdChangeResultMultiDeliveryLotInfo : public GUIDirectMessage
{
public:
	int			DeliveryNo;
	QStringList	LotID;
	QStringList	LotName;
	QString		Remark;

	CmdChangeResultMultiDeliveryLotInfo(LayersBase *base):GUIDirectMessage(base){}
};

inline	QString	MakeDeliveryLot(const QString &IDLotName ,int DeliveryNo ,int SubLotNumber)
{
	return IDLotName+QString(/**/"-")+QString::number(DeliveryNo)+QString(/**/"-")+QString::number(SubLotNumber);
}


#endif // RESULTXMLMULTIDELIVERY_H