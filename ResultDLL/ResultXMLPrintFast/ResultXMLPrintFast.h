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
