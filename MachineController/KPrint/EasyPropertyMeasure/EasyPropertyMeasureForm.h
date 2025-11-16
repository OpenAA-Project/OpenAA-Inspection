#ifndef EASYPROPERTYMEASUREFORM_H
#define EASYPROPERTYMEASUREFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XMeasureCommon.h"
#include <QPushButton>
#include <QModelIndex>
#include <QStringList>
#include "NListComp.h"

namespace Ui {
class EasyPropertyMeasureForm;
}

class	EasyMeasureImagePanel;
class	InspectionList;

class	MeasurePointButton : public QPushButton
{
	Q_OBJECT
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;	//0:
	int	MeasureNo;

	MeasurePointButton(void);

private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int EndNo , int MeasureNo);
};

#define		MaxCountOfMeasureResult	20

class	MeasureResult
{
public:
	int32	InspectionID;
	double	ResultDouble[MaxCountOfMeasureResult];
};

class	MeasureResultInMachine
{
public:
	int				CountingPoint;
	MeasureResult	*ResultDim;
	int				ResultCount;
	int				AllocatedResultCount;
	int				NGCount;
	struct UniqueIndex
	{
		int	Phase;
		int	Page;
		int	ItemID;
	}UniqueIndexData[MaxCountOfMeasureResult];

	MeasureResultInMachine(void);
	MeasureResultInMachine(const MeasureResultInMachine &src);
	~MeasureResultInMachine(void);

	MeasureResultInMachine	&operator=(const MeasureResultInMachine &src);
	void	SetResultPage(InspectionList *n);
	void	RemoveAll(void);
};


class EasyPropertyMeasureForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	MeasureDistanceItemInfoContainer	ListData;
	MeasureResultInMachine				MeasureResultData;

	int32	SlaveNo;
	int		DrawMode;	//0:StartPoint	,1:Edit Point1	2,EditPoint2
	int		CurrentMeasureNo;

    explicit EasyPropertyMeasureForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyMeasureForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	StartInitial(void)	override;
signals:
	void	SignalBusy();
	void	SignalIdle();
private slots:
    void on_pushButtonStartPoint1_clicked();
    void on_pushButtonDelete_clicked();
    void on_toolButtonGetCorrentValuesTarget_clicked();

	void	SlotDoneLoadResult(InspectionList *n);
	void	ResizeAction();
	void	SlotEndPointClicked(int EndNo,int MeasureNo);

    void on_toolButtonReflect_clicked();
    void on_tableWidgetList_itemSelectionChanged();
	void	SlotRightClicked(QAbstractButton *obj);
private:
    Ui::EasyPropertyMeasureForm *ui;
	void	ShowList(void);

	EasyMeasureImagePanel	*GetEasyMeasureImagePanel(void);
	void	ShowSearchDotOnButton(MeasurePointButton *b);
	void	ShowSearchDotOnButton(void);
};

//====================================================================================================

class	IntegrationCmdReqListData: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckListData : public IntegrationCmdPacketBase
{
public:
	MeasureDistanceItemInfoContainer	ListData;

	IntegrationCmdAckListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//====================================================================================================

class	IntegrationCmdSetCorrectValue : public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		Page;
	int		ItemID;
	double	OKLengthLUnit;
	double	OKLengthHUnit;	

	IntegrationCmdSetCorrectValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAddDistance : public IntegrationCmdPacketBase
{
public:
	int		LocalX1;
	int		LocalY1;
	int		LocalX2;
	int		LocalY2;
	int		LineLength;
	int		LineLibID1;
	int		LineLibID2;
	int		DistanceLibID;

	IntegrationCmdAddDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 SlaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

};
class	CmdSetEndPointDistance: public GUIDirectMessage
{
public:
	int	EndNo;
	int	MeasureNo;
	int	GlobalX,GlobalY;

	CmdSetEndPointDistance(LayersBase *base):GUIDirectMessage(base){}
	CmdSetEndPointDistance(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//====================================================================================================

class	IntegrationCmdSetMeasureDistanceEndPoint : public IntegrationCmdPacketBase
{
public:
	int		EndNo;
	int		MeasureNo;
	int		GlobalX;
	int		GlobalY;

	IntegrationCmdSetMeasureDistanceEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//====================================================================================================

class	IntegrationCmdDeleteDistance : public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		Page;
	int		MeasureNo;

	IntegrationCmdDeleteDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//====================================================================================================

class	IntegrationCmdReqMeasureLineInfo: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;

	IntegrationCmdReqMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckMeasureLineInfo : public IntegrationCmdPacketBase
{
public:
	int		SearchDot;

	IntegrationCmdAckMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetMeasureLineInfo : public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	IntegrationCmdSetMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationCmdSetMeasureLineInfoAll : public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	IntegrationCmdSetMeasureLineInfoAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // EASYPROPERTYMEASUREFORM_H
