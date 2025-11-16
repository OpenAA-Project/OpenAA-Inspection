#ifndef RESULTXMLSMALLLOT_H
#define RESULTXMLSMALLLOT_H

#include "resultxmlsmalllot_global.h"
#include "ResultXMLV3.h"

class	ResultInspectionForStockPointerContainer;

class ResultXMLSmallLot : public ResultXMLV3
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
	QString CommonStrLID ,CommonStr;
	QString SlaveStrLID ,SlaveSearchStr,SlaveInsData;
public:
	ResultXMLSmallLot(LayersBase *Base);
	~ResultXMLSmallLot();

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
	void	SignalOutputSlave();

private slots:
	void	SlotOutputCommon();
	void	SlotOutputSlave();
};

#endif // RESULTXMLSMALLLOT_H
