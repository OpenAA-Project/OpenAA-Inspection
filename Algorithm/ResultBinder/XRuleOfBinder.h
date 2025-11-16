#if	!defined(XRuleOfBinder_h)
#define	XRuleOfBinder_h

#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
#include "XResult.h"
#include "XRuleOfBinderCommon.h"

const int	CharaterHeight=16;

class	RuleOfBinderBase;
class	ResultBinderItem;
class	RuleOfBinderContainer : public NPListPack<RuleOfBinderBase>
{
public:
	RuleOfBinderContainer(void){}

	virtual	RuleOfBinderBase	*Create(int ID);

	virtual	bool	ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	IsInclude(int X ,int Y,double ZoomRate)					;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy);

	int		GetLastID(void);
	void	BuildLinkFromIDList(void);

	RuleOfBinderBase	*Find(int x ,int y ,double ZoomRate);
	RuleOfBinderBase	*Find(int RuleID);
	RuleOfBinderBase	*GetConclusionRule(void);

	bool	GetClosedConnection(int X ,int Y,double ZoomRate, int &ParentRuleID ,int &ChildRuleID ,int Isolation=5);
	bool	RemoveConnection(int ParentRuleID,int ChildRuleID);

	void	ReplaceOKInSource(void);
};

class	RuleOfBinderPointer : public NPList<RuleOfBinderPointer>
{
public:
	RuleOfBinderBase	*Pointer;

	RuleOfBinderPointer(RuleOfBinderBase *w):Pointer(w){}
};

class	RuleOfBinderPointerContainer : public NPListPack<RuleOfBinderPointer>
{
public:
	RuleOfBinderPointerContainer(void){}
	//virtual	bool	Save(QIODevice *f);
	//virtual	bool	Load(QIODevice *f);
};

class	RuleOfBinderBase	: public NPList<RuleOfBinderBase>
{
	IntList					IDList;
public:
	RuleOfBinderPointerContainer	Children;
	int32					RuleID;
	QPoint					Location;
	QString					Name;
	QString					Remark;
	bool					Conclusion;
	ResultBinderItem		*ParentItem;
	RuleOfBinderContainer	*Root;

	int						Error;
	int						ResultCode;

	RuleOfBinderBase(RuleOfBinderContainer *p)
		:Root(p)
		{		RuleID=-1;	ParentItem=NULL;	Conclusion=false;	Error=0;	ResultCode=0;	}

	virtual	int		GetClassID(void)		=0;
	virtual	int		ReqMaxChildCount(void)	=0;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo);
	virtual	bool	GetResult(ResultInItemRoot *Res)=0;

	void	GetCenter(int &cx ,int &cy,double ZoomRate);
	void	DrawArrow(QPainter &Pnt,int x2,int y2,int x1,int y1 ,double ZoomRate ,int movx ,int movy);

	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	=0;
	virtual	void	DrawRuleChild(QImage &pnt ,double ZoomRate ,int movx ,int movy);
	virtual	bool	IsInclude(int X ,int Y,double ZoomRate)							;
	virtual	bool	GetClosedConnection(int X ,int Y,double ZoomRate, int &ChildRuleID ,int Isolation=5);
	virtual	bool	GetArrow(int fromX ,int fromY ,int &ToX ,int &ToY,double ZoomRate);
	virtual	void	DrawResult(QPainter &Pnt ,int XPos ,int YPos);

	virtual	int		GetWidth(void)	=0;
	virtual	int		GetHeight(void)	=0;

	void	GenerateChildIDListFromLink(void);
	void	BuildLinkFromIDList(void);

	virtual	void	ReplaceOKInSource(void);
};

//------------------------------------------------------------------------

#define	ID_ChildOfRuleAlgorithmItem					1
#define	ID_ChildOfRuleAllItemsInLayerAlgorithm		2
#define	ID_ChildOfRuleAllItemsInPageAlgorithm		3
#define	ID_ChildOfRuleOperationOR					100
#define	ID_ChildOfRuleOperationAND					101
#define	ID_ChildOfRuleOperationXOR					102
#define	ID_ChildOfRuleOperationNEG					103
#define	ID_ChildOfRuleOperationCond					104



class	ChildOfRuleAlgorithmItem : public RuleOfBinderBase
{
	AlgorithmItemRoot	*Item;
public:
	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	QString	ItemName;

	ChildOfRuleAlgorithmItem(RuleOfBinderContainer *p)
	:RuleOfBinderBase(p){
		Item	=NULL;
		Phase	=-1;
		Page	=-1;
		Layer	=-1;
		ItemID	=-1;
	}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleAlgorithmItem;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 0;	};

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
	virtual	bool	ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 250;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*8;	}

	virtual	void	ReplaceOKInSource(void)	override;
};

class	ChildOfRuleAllItemsInLayerAlgorithm : public RuleOfBinderBase
{
	AlgorithmInLayerRoot	*AlgoLayer;
public:
	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;
	int		Layer;

	ChildOfRuleAllItemsInLayerAlgorithm(RuleOfBinderContainer *p)
	:RuleOfBinderBase(p)
	{
		AlgoLayer	=NULL;
		Phase	=-1;
		Page	=-1;
		Layer	=-1;
	}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleAllItemsInLayerAlgorithm;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 0;	};

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
	virtual	bool	ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 250;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*7;	}

	virtual	void	ReplaceOKInSource(void)	override;
};

class	ChildOfRuleAllItemsInPageAlgorithm : public RuleOfBinderBase
{
	AlgorithmInPageRoot	*AlgoPage;
public:
	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Page;

	ChildOfRuleAllItemsInPageAlgorithm(RuleOfBinderContainer *p)
	:RuleOfBinderBase(p){
		AlgoPage	=NULL;
		Phase	=-1;
		Page	=-1;
	}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleAllItemsInPageAlgorithm;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 0;	};

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;
	virtual	bool	ExecuteInitialAfterEdit(LayersBase *base,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 250;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*7;	}

	virtual	void	ReplaceOKInSource(void)	override;
};


class	ChildOfRuleOperationOR : public RuleOfBinderBase
	// Result OK if one child is OK
{
public:

	ChildOfRuleOperationOR(RuleOfBinderContainer *p):RuleOfBinderBase(p){}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleOperationOR;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 100;	};

	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 200;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*4;	}
};


class	ChildOfRuleOperationAND : public RuleOfBinderBase
	// Result OK if all children is OK
{
public:

	ChildOfRuleOperationAND(RuleOfBinderContainer *p):RuleOfBinderBase(p){}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleOperationAND;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 100;	};

	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 200;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*4;	}
};


class	ChildOfRuleOperationXOR : public RuleOfBinderBase
	// Result XOR
{
public:

	ChildOfRuleOperationXOR(RuleOfBinderContainer *p):RuleOfBinderBase(p){}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleOperationXOR;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 2;	};

	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 200;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*4;	}
};


class	ChildOfRuleOperationNEG : public RuleOfBinderBase
	// Logic Negative
{
public:

	ChildOfRuleOperationNEG(RuleOfBinderContainer *p):RuleOfBinderBase(p){}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleOperationNEG;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 1;	};

	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	int		GetWidth(void)		override{	return 200;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*4;	}
};

class	ChildOfRuleOperationConditional : public RuleOfBinderBase
	// Logic Negative
{
public:

	ConditionListContainer	ConditionData;
	bool					NGOthers;

	ChildOfRuleOperationConditional(RuleOfBinderContainer *p):RuleOfBinderBase(p){	NGOthers=true;	}

	virtual	int		GetClassID(void)		override{	return ID_ChildOfRuleOperationCond;	};
	virtual	int		ReqMaxChildCount(void)	override{	return 1;	};

	virtual	bool	GetResult(ResultInItemRoot *Res)							override;
	virtual	void	DrawRule(QImage &pnt ,double ZoomRate ,int movx ,int movy)	override;

	virtual	bool	Save(QIODevice *f)		override;
	virtual	bool	Load(QIODevice *f)		override;

	virtual	int		GetWidth(void)		override{	return 200;		}
	virtual	int		GetHeight(void)		override{	return 10+CharaterHeight*4;	}
};






#endif
