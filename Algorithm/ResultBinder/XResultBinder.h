#if	!defined(XResultBinder_h)
#define	XResultBinder_h

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
#include <QColor>
#include "XRuleOfBinder.h"
#include "XRuleOfBinderCommon.h"

#define	ResultBinderVersion		60

//=====================================================================
class	ResultBinderDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorResultBinder;
	QColor	NegColorSelected;
	bool	EffectiveMode;
	bool	IneffectiveMode;
	int		CurrentItemID;
	int		CurrentPage;

	ResultBinderDrawAttr(LayersBase *base){}
	ResultBinderDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	ResultBinderDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorResultBinder	=nncol;	
		NegColorSelected=nscol;	
		NegColorResultBinder.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};
//==========================================================================
class	ResultBinderThreshold : public AlgorithmThreshold
{
public:
	ResultBinderThreshold(ResultBinderItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
    virtual	bool	Load(QIODevice *f)					override{	return true;	}
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};


class	ResultBinderItem : public AlgorithmItemPI
{
public:
	RuleOfBinderContainer	Rule;

	ResultBinderItem(void)	{}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ResultBinderItem();	}
	const	ResultBinderThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ResultBinderThreshold *)GetThresholdBaseReadable(base);	}
	ResultBinderThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ResultBinderThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ResultBinderThreshold(this);	}

	virtual	FlexArea	&GetArea(void)						override;

	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	//virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	BindResult(ResultInItemRoot *Item,ResultPosList *RPos);
	void	ReplaceOKInSource(void);

	//virtual	bool	IsInclude(int x ,int y);
};

class   ResultBinderInPage : public AlgorithmInPagePI
{
public:
	ResultBinderInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			ResultBinderItem	*a=new ResultBinderItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;


	ResultBinderItem	*FindItem(QString areaname);
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;
};

class	ResultBinderBase : public AlgorithmBase
{
public:
	QColor	ColorResultBinder;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorResultBinder;
	QColor	NegColorSelected;

	ResultBinderBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new ResultBinderInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ResultBinder");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ResultBinder.dat");		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	//bool	GeneralDataRelease(int32 Command,void *data)			override;
	//void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	//bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	//bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	//bool	GeneralDataReply(int32 Command,void *data)				override;
private:

};
//==================================================================================
class	AddRulePacket : public GUIDirectMessage
{
public:
	int			ResultBinderItemID;
	FlexArea	Area;
	int			RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	QString	ItemName;
	ConditionListContainer	ConditionData;
	QString	RuleName;
	QString	RuleRemark;
	bool	NGOthers;
	bool	Conclusion;

	AddRulePacket(LayersBase *base):GUIDirectMessage(base){}
	AddRulePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdChangeRulePacket : public GUIDirectMessage
{
public:
	int			ResultBinderItemID;
	int			RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	QString	ItemName;
	ConditionListContainer	ConditionData;
	QString	RuleName;
	QString	RuleRemark;
	int		RuleID;
	bool	NGOthers;
	bool	Conclusion;
	bool	DeleteMode;

	CmdChangeRulePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdChangeRulePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqResultBinderItemAdd : public GUIDirectMessage
{
public:
	QString	ResultBinderItemName;
	int		ResultBinderItemID;

	CmdReqResultBinderItemAdd(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResultBinderItemAdd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqResultBinderItemInfo : public GUIDirectMessage
{
public:
	int	ItemID;
	QString	ItemName;

	CmdReqResultBinderItemInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResultBinderItemInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqResultBinderItemEnum : public GUIDirectMessage
{
public:
	ItemIDNameContainer		*Items;

	CmdReqResultBinderItemEnum(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResultBinderItemEnum(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqResultBinderItemMod : public GUIDirectMessage
{
public:
	int	ItemID;
	QString	ItemName;

	CmdReqResultBinderItemMod(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResultBinderItemMod(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqResultBinderItemDel: public GUIDirectMessage
{
public:
	int		ResultBinderItemID;

	CmdReqResultBinderItemDel(LayersBase *base):GUIDirectMessage(base){}
	CmdReqResultBinderItemDel(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqRuleOnXY: public GUIDirectMessage
{
public:
	double	ZoomRate;
	int		PosX ,PosY;
	int		ResultBinderItemID;
	int		RuleType;

	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	ConditionListContainer	ConditionData;
	QString	ItemName;
	QString	RuleName;
	QString	RuleRemark;
	bool	Conclusion;
	int		RuleID;
	bool	NGOthers;
	int		InputNumb;

	CmdReqRuleOnXY(LayersBase *base):GUIDirectMessage(base){}
	CmdReqRuleOnXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAddConnection : public GUIDirectMessage
{
public:
	int		ParentRuleID;
	int		ChildRuleID;
	int		ResultBinderItemID;

	CmdReqAddConnection(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAddConnection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAckClosedConnectionOnXY: public GUIDirectMessage
{
public:
	double	ZoomRate;
	int		PosX ,PosY;
	int		ResultBinderItemID;
	int		ParentRuleID;
	int		ChildRuleID;

	CmdAckClosedConnectionOnXY(LayersBase *base):GUIDirectMessage(base){}
	CmdAckClosedConnectionOnXY(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDelConnection: public GUIDirectMessage
{
public:
	int		ResultBinderItemID;
	int		ParentRuleID;
	int		ChildRuleID;

	CmdDelConnection(LayersBase *base):GUIDirectMessage(base){}
	CmdDelConnection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif