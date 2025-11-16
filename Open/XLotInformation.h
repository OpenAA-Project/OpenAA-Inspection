#if	!defined(XLOTINFORMATION_H)
#define	XLOTINFORMATION_H

#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"

class	LotInformation : public ServiceForLayers
{
	int32			DeliveryNo;
	int32			LotAutoCount;
	QString			LotID;
	QString			LotName;
	QString			Remark;

	int32			NextLotAutoCount;
	QString			NextLotID;
	QString			NextLotName;
	QString			NextRemark;

public:
	LotInformation(void);
	LotInformation(LayersBase *base);

	virtual	int32	GetLotAutoCount(void)		const	{	return LotAutoCount;	}
	virtual	void	SetLotAutoCount(int32 code)			{	LotAutoCount=code;		}
	virtual	QString	GetLotID(void)				const	{	return LotID;			}
	virtual	void	SetLotID(QString lotID)				{	LotID=lotID;			}
	virtual	QString	GetLotName(void)			const	{	return LotName;			}
	virtual	void	SetLotName(const QString &lotName)	{	LotName=lotName;	}
	virtual	QString	GetRemark(void)				const	{	return Remark;		}
	virtual	void	SetRemark(const QString &remark)	{	Remark=remark;		}

	void	SetDeliveryNo(int n)			{	DeliveryNo=n;		}
	int		GetDeliveryNo(void)		const	{	return DeliveryNo;	}

	virtual	void	ExecuteEveryInspectInMaster(int InspectionID){}
	virtual	void	ExecuteEveryInspectInSlave(int InspectionID,int Phase ,int Page){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	ReserveChangeLot(int32 _NextLotAutoCount
							,QString _NextLotID
							,QString _NextLotName
							,QString _NextRemark);


	virtual	void	Reserve(int32 NextLotAutoCount
							,QString NextLotID
							,QString NextLotName
							,QString NextRemark);

	virtual	void	ChangeLotInfo(void);
};

class	LotBase : public ServiceForLayers
{
	QString		LotBaseName;
	QString		LotBaseID;
	QString		LotBaseRemark;
	int32		ClusterID;

	LotInformation	*LotDim;
	int				AllocatedLotDeliveryCount;
public:
	LotBase(LayersBase *base);
	~LotBase(void);

	void	Initial(void);
	LotInformation	*GetLot(int n)	const;

	virtual	QString	GetLotID(void)							const	{	return LotBaseID;			}
	virtual	void	SetLotID(const QString &lotID)					{	LotBaseID=lotID;			}
	virtual	QString	GetLotName(void)						const	{	return LotBaseName;			}
	virtual	void	SetLotName(const QString &lotName)				{	LotBaseName=lotName;		}
	virtual	QString	GetLotRemark(void)						const	{	return LotBaseRemark;		}
	virtual	void	SetLotRemark(const QString &lotRemark)			{	LotBaseRemark=lotRemark;	}
	virtual	int		GetClusterID(void)						const	{	return ClusterID;			}

	virtual	void	ExecuteEveryInspectInMaster(int InspectionID){}
	virtual	void	ExecuteEveryInspectInSlave(int InspectionID,int Phase ,int Page){}

	IntList	GetLotAutoCount(void)	const;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

#endif