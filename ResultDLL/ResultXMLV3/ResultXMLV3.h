#ifndef RESULTXMLV3_H
#define RESULTXMLV3_H

#include "resultxmlv3_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XMLClient.h"
#include "XTypeDef.h"

class	ResultInspectionForStockPointerContainer;

class	ResultXMLV3 : public XMLServerHandle,public ResultDLLBaseRoot
{
	Q_OBJECT

protected:
	XMLOperationHandle	*HandleCommon;
	XMLOperationHandle	*HandlePage;
	XMLOperationHandle	*HandleRemove;
	XMLOperationHandle	*HandleLastID;
	XMLOperationHandle	*HandlePiece;
	XMLOperationHandle	*HandleInsLib;
	bool				OutputLibData;
public:
	int		WaitMilisecForConnection;
	ResultXMLV3(LayersBase *Base);
	virtual ~ResultXMLV3(void);	
	
	virtual	QString	GetDataText(void)			{	return QString("XML Result");		}
	virtual	QString	GetDefaultFileName(void)	{	return QString("ResultXMLV3.dat");	}

	bool	OutputCommon(ResultInspection &Res,ResultInspectionForStockPointerContainer &ShadowResStocks);
	bool	OutputResult(ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,const XDateTime &InspectedTime 
								,ResultInspection *Res 
								,const QString &LotID,int phase, int localPage);
	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime,	int64 InspectionID);
	bool	GetLastInspectionID(int MasterID, QString LotID ,int64 &InspectionID);

	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res);
	bool	OutputInLotChangedSlave(int LocalPage);
	bool	OutputInLib(void);
	bool	SearchLotID(const QString &iLotID);
	bool	CheckConnection(void);

protected:
	ResultInspection	*TmpRes;

	QString	GetLotID(void);
	QString	GetLotName(void);

	int64	GetInspectionNumber(void);
	int		GetMachineID(void);
	int		GetMasterCode(void);
	QString	GetMasterName(void);
	int64	GetInspectionID(void);

private:
	bool	OpenOperation(XMLOperationHandle **Handle);
	void	OutputInLibData(LogicDLL *L ,int LibID
							,QStringList &RetInsertStrings);

	QString	GetXMLTableName(void);
	QString	GetXMLTableName(const QString &iLotID);

	volatile	bool3	FlagCommon;
	volatile	bool3	FlagSlave;
	bool	FixedConnection;

signals:
	void	SignalOutputCommon(QString Str);
	void	SignalOutputSlave(QString SearchStr,QString InsData);

private slots:
	void	SlotOutputCommon(QString Str);
	void	SlotOutputSlave(QString SearchStr,QString InsData);

};
#endif // RESULTXMLV3_H
