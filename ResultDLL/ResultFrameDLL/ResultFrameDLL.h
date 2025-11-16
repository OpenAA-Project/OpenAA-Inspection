#ifndef RESULTFRAMEDLL_H
#define RESULTFRAMEDLL_H

#include "resultframedll_global.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XMLClient.h"
#include "XTypeDef.h"

class	ResultInspectionForStockPointerContainer;

class	ResultFrameDLL : public XMLServerHandle,public ResultDLLBaseRoot
{
	Q_OBJECT

protected:
	class	GroupPacket
	{
	public:
		XMLOperationHandle	*HandleCommon;
		XMLOperationHandle	*HandlePage;
		XMLOperationHandle	*HandleRemove;
		XMLOperationHandle	*HandleLastID;
		XMLOperationHandle	*HandlePiece;
		XMLOperationHandle	*HandleInsLib;

		QString		iLotID;		//Contain GroupNo and SubLotNumber
		QString		iLotName;
		int64		InspectionID;
		IntList		FrameNumber;

		GroupPacket(void);
		~GroupPacket(void);
	};
	GroupPacket		Group[1000];
	int				GroupCount;

	bool			OutputLibData;
	QString			iRemark;

public:
	ResultFrameDLL(LayersBase *Base);
	virtual ~ResultFrameDLL(void);	
	
	virtual	QString	GetDataText(void)			override{	return QString("XML ResultFrameDLL");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ResultFrameDLL.dat");	}

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

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)override;

protected:
	ResultInspection	*TmpRes;

	QString	GetLotID(int GroupNo);
	QString	GetLotName(int GroupNo);

	int64	GetInspectionNumber(int GroupNo,int FrameNumber);
	int		GetMachineID(void);
	int		GetMasterCode(void);
	QString	GetMasterName(void);
	int64	GetInspectionID(int GroupNo,int FrameNumber);

private:
	bool	OpenOperation(int GroupNo,XMLOperationHandle **Handle);
	void	OutputInLibData(LogicDLL *L ,int LibID
							,QStringList &RetInsertStrings);

	QString	GetXMLTableName(int GroupNo);
	QString	GetXMLTableName(const QString &iLotID);

	volatile	bool3	FlagCommon;
	volatile	bool3	FlagSlave;
	bool	FixedConnection;

signals:
	void	SignalOutputCommon(int GroupNo,int FrameNumber ,QString Str);
	void	SignalOutputSlave(int GroupNo,int FrameNumber ,QString SearchStr,QString InsData);

private slots:
	void	SlotOutputCommon(int GroupNo,int FrameNumber ,QString Str);
	void	SlotOutputSlave(int GroupNo,int FrameNumber ,QString SearchStr,QString InsData);
};


class	CmdChangeResultFrameDLLLotInfo : public GUIDirectMessage
{
public:
	int			GroupNo;
	QStringList	LotID;
	QStringList	LotName;
	QString		Remark;

	CmdChangeResultFrameDLLLotInfo(LayersBase *base):GUIDirectMessage(base){}
};

inline	QString	MakeGroupLot(const QString &IDLotName ,int GroupNo ,int SubLotNumber)
{
	return IDLotName+QString(/**/"-")+QString::number(GroupNo)+QString(/**/"-")+QString::number(SubLotNumber);
}
#endif // RESULTFRAMEDLL_H
