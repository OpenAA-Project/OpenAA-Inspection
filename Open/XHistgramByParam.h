#if	!defined(XHISTGRAMBYPARAM_H)
#define	XHISTGRAMBYPARAM_H

#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XGUIPacketForDLL.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "NListComp.h"

class	AlgorithmInPageRoot;
class	LayersBase;
class	HistgramTypeListInAlgoContainer;
class	HistStepClass;
class	AlgorithmItemPointerListContainerByLibContainer;
class	ParamAutoThreshold;

class	ValueDimStockerBase
{
public:
	ValueDimStockerBase(void){}
	virtual	~ValueDimStockerBase(void){}

	virtual	int	GetTypeCode(void)	=0;
	virtual	int	GetParamID(void)	=0;

	virtual	int		GetCount(void)	=0;
	virtual	void	Clear(void)		=0;

	virtual	bool	Save(QIODevice *f)=0;
	virtual	bool	Load(QIODevice *f)=0;

	virtual	bool	SaveText(QIODevice *f)=0;

	static	ValueDimStockerBase	*LoadNew(QIODevice *f);
	static	ValueDimStockerBase	*Create(int TypeCode ,int paramID);
};

template<class T>
class	ValueDimStocker : public ValueDimStockerBase
{
	T		*Dim;
	int32	AllocatedCount;
	int16	CurrentCount;
	int16	CurrentPoint;
public:

	ValueDimStocker(int allocatedCount = 100)
	{
		AllocatedCount = allocatedCount;
		CurrentCount = 0;
		CurrentPoint = 0;
		if (AllocatedCount > 0) {
			Dim = new T[AllocatedCount];
			memset(Dim, 0, sizeof(T) * AllocatedCount);
		}
	}
	virtual	~ValueDimStocker(void);

	void	Set(T n);
	virtual	void	Clear(void)	{	CurrentCount=0;	CurrentPoint=0;		}
	T		*GetPointer	(void)	{	return Dim;	}
	T		GetData(int n)		{	return Dim[n];	}
	T		GetLastData(int n)	{	return Dim[n];	}
	virtual	int		GetCount(void)	{	return CurrentCount;	}
	bool	AddTo(HistStepClass *Dest);

	double	GetAverage(void);
	double	GetDispersion(void);
	bool	GetDistribution(double &Average,double &Dispersion);

	bool	GetMinMax(T &MinData ,T &MaxData);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	SaveText(QIODevice *f);
	
private:
	void	Release(void);
};


template<class T>
class	HistgramDimStocker : public ValueDimStockerBase
{
	uint	*Dim;
	int32	AllocatedCount;
	T		MinData;
	T		MaxData;
	T		Step;
public:

	HistgramDimStocker(T mindata, T maxdata, T step = 1)
	{
		MinData = mindata;
		MaxData = maxdata;
		Step = step;
		AllocatedCount = ceil((double)(MaxData - MinData) / Step) + 1;
		if (AllocatedCount > 0) {
			Dim = new uint[AllocatedCount];
		}
		Clear();
	}
	HistgramDimStocker(void)
	{
		Dim = NULL;
		AllocatedCount = 0;
	}
	virtual	~HistgramDimStocker(void);

	void	Set(T n);
	virtual	void	Clear(void);
	virtual	int		GetCount(void);
	bool	AddTo(HistStepClass *Dest);
	uint	*GetPointer(void)	{	return Dim;	}

	double	GetAverage(void);
	double	GetDispersion(void);
	bool	GetDistribution(double &Average,double &Dispersion);

	bool	GetMinMax(T &MinData ,T &MaxData);
	T		GetStep(void)	{	return Step;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	SaveText(QIODevice *f);
private:
	void	Release(void);
};

//---------------------------------------------------------------------

class	HistgramByParamBase : public NPList<HistgramByParamBase>
{
	int	ID;
	ValueDimStockerBase	*Base;
public:
	HistgramByParamBase(int id ,ValueDimStockerBase *base):ID(id),Base(base){}
	~HistgramByParamBase(void);

	virtual	HistgramByParamBase		*Clone(void)	=0;
	int	GetTypeCode(void)	{	return	Base->GetTypeCode();	}
	int	GetParamID(void)	{	return	Base->GetParamID();		}
	int		GetID(void)		{	return ID;	}

	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	=0;
	virtual	void	Set(int data)	=0;
	virtual	void	Set(double data)=0;
	void	Clear(void)		{	return Base->Clear();		}
	int		GetCount(void)	{	return Base->GetCount();	}

	virtual	bool	AddTo(HistStepClass *Dest)	=0;

	bool	SaveHistgram(QIODevice *f)	{	return Base->Save(f);	}
	bool	LoadHistgram(QIODevice *f)	{	return Base->Load(f);	}

	ValueDimStockerBase	*CreateCopy(void);

	virtual	bool	GetDistribution(double &Average,double &Dispersion)	=0;
};

//-------------------------
class	HistgramByParamByte : public HistgramByParamBase ,public ValueDimStocker<BYTE>
{
public:
	HistgramByParamByte(int id):HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override	{	return new HistgramByParamByte(GetID());	}
	virtual	int		GetTypeCode(void)	override{	return 1;		}
	virtual	int		GetParamID(void)	override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)	override{	return ValueDimStocker<BYTE>::AddTo(Dest);	}

};
inline	void	HistgramByParamByte::Set(int data)
{	
	ValueDimStocker<BYTE>::Set((BYTE)data);	
}
inline	void	HistgramByParamByte::Set(double data)
{	
	ValueDimStocker<BYTE>::Set((BYTE)data);	
}

//-------------------------
class	HistgramByParamChar : public HistgramByParamBase ,public ValueDimStocker<char>
{
public:
	HistgramByParamChar(int id):HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override	{	return new HistgramByParamChar(GetID());	}
	virtual	int		GetTypeCode(void)	override{	return 2;		}
	virtual	int		GetParamID(void)	override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return ValueDimStocker<char>::AddTo(Dest);	}
};

inline	void	HistgramByParamChar::Set(int data)
{	
	ValueDimStocker<char>::Set((char)data);	
}
inline	void	HistgramByParamChar::Set(double data)
{	
	ValueDimStocker<char>::Set((char)data);
}

//-------------------------
class	HistgramByParamInt : public HistgramByParamBase ,public ValueDimStocker<int>
{
public:
	HistgramByParamInt(int id):HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override	{	return new HistgramByParamInt(GetID());	}
	virtual	int	GetTypeCode(void)		override{	return 3;		}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return ValueDimStocker<int>::AddTo(Dest);	}
};
inline	void	HistgramByParamInt::Set(int data)
{	
	ValueDimStocker<int>::Set((int)data);
}
inline	void	HistgramByParamInt::Set(double data)
{	
	ValueDimStocker<int>::Set((int)data);
}

//-------------------------
class	HistgramByParamShort : public HistgramByParamBase ,public ValueDimStocker<short>
{
public:
	HistgramByParamShort(int id):HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override	{	return new HistgramByParamShort(GetID());	}
	virtual	int	GetTypeCode(void)		override{	return 4;	}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return ValueDimStocker<short>::AddTo(Dest);	}
};
inline	void	HistgramByParamShort::Set(int data)	
{	
	ValueDimStocker<short>::Set((short)data);
}
inline	void	HistgramByParamShort::Set(double data)
{	
	ValueDimStocker<short>::Set((short)data);
}

//-------------------------

class	HistgramByParamDouble : public HistgramByParamBase ,public ValueDimStocker<double>
{
public:
	HistgramByParamDouble(int id):HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override	{	return new HistgramByParamDouble(GetID());	}
	virtual	int	GetTypeCode(void)		override{	return 5;	}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return ValueDimStocker<double>::AddTo(Dest);	}
	virtual	bool	SaveText(QIODevice *f)	override;
};
inline	void	HistgramByParamDouble::Set(int data)	
{	
	ValueDimStocker<double>::Set((double)data);
}
inline	void	HistgramByParamDouble::Set(double data)
{	
	ValueDimStocker<double>::Set(data);	
}

//-------------------------

class	HistgramByBoundaryByte : public HistgramByParamBase ,public HistgramDimStocker<BYTE>
{
public:
	HistgramByBoundaryByte(int id ,BYTE mindata ,BYTE maxdata)
		:HistgramByParamBase(id,this),HistgramDimStocker<BYTE>(mindata ,maxdata){}
	HistgramByBoundaryByte(int id )
		:HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override
			{	BYTE mn ,mx;	
				GetMinMax(mn ,mx);
				return new HistgramByBoundaryByte(GetID(),mn ,mx);
			}
	virtual	int		GetTypeCode(void)	override{	return 11;		}
	virtual	int		GetParamID(void)	override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return HistgramDimStocker<BYTE>::AddTo(Dest);	}
};
inline	void	HistgramByBoundaryByte::Set(int data)
{	
	HistgramDimStocker<BYTE>::Set((BYTE)data);
}
inline	void	HistgramByBoundaryByte::Set(double data)
{	
	HistgramDimStocker<BYTE>::Set((BYTE)data);
}

//-------------------------
class	HistgramByBoundaryChar : public HistgramByParamBase ,public HistgramDimStocker<char>
{
public:
	HistgramByBoundaryChar(int id,char mindata ,char maxdata)
		:HistgramByParamBase(id,this),HistgramDimStocker<char>(mindata ,maxdata){}
	HistgramByBoundaryChar(int id )
		:HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override
			{	char mn ,mx;	
				GetMinMax(mn ,mx);
				return new HistgramByBoundaryChar(GetID(),mn ,mx);
			}
	virtual	int		GetTypeCode(void)	override{	return 12;		}
	virtual	int		GetParamID(void)	override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return HistgramDimStocker<char>::AddTo(Dest);	}
};
inline	void	HistgramByBoundaryChar::Set(int data)
{	
	HistgramDimStocker<char>::Set((char)data);
}
inline	void	HistgramByBoundaryChar::Set(double data)
{
	HistgramDimStocker<char>::Set((char)data);
}

//-------------------------
class	HistgramByBoundaryInt : public HistgramByParamBase ,public HistgramDimStocker<int>
{
public:
	HistgramByBoundaryInt(int id,int mindata ,int maxdata)
		:HistgramByParamBase(id,this),HistgramDimStocker<int>(mindata ,maxdata){}
	HistgramByBoundaryInt(int id )
		:HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override
			{	int mn ,mx;	
				GetMinMax(mn ,mx);
				return new HistgramByBoundaryInt(GetID(),mn ,mx);
			}
	virtual	int	GetTypeCode(void)		override{	return 13;		}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override;
	virtual	void	Set(double data)	override;
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return HistgramDimStocker<int>::AddTo(Dest);	}
};
inline	void	HistgramByBoundaryInt::Set(int data)
{	
	HistgramDimStocker<int>::Set((int)data);
}
inline	void	HistgramByBoundaryInt::Set(double data)
{	
	HistgramDimStocker<int>::Set((int)data);
}

class	HistgramByBoundaryShort : public HistgramByParamBase ,public HistgramDimStocker<short>
{
public:
	HistgramByBoundaryShort(int id,short mindata ,short maxdata)
		:HistgramByParamBase(id,this),HistgramDimStocker<short>(mindata ,maxdata){}
	HistgramByBoundaryShort(int id )
		:HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override
			{	short mn ,mx;	
				GetMinMax(mn ,mx);
				return new HistgramByBoundaryShort(GetID(),mn ,mx);
			}
	virtual	int	GetTypeCode(void)		override{	return 14;	}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override{	HistgramDimStocker<short>::Set((short)data);	}
	virtual	void	Set(double data)	override{	HistgramDimStocker<short>::Set((short)data);	}
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)		override{	return HistgramDimStocker<short>::AddTo(Dest);	}
};

class	HistgramByBoundaryDouble : public HistgramByParamBase ,public HistgramDimStocker<double>
{
public:
	HistgramByBoundaryDouble(int id,double mindata ,double maxdata,double step)
		:HistgramByParamBase(id,this),HistgramDimStocker<double>(mindata ,maxdata,step){}
	HistgramByBoundaryDouble(int id )
		:HistgramByParamBase(id,this){}

	virtual	HistgramByParamBase		*Clone(void)	override
			{	double mn ,mx;	
				GetMinMax(mn ,mx);
				return new HistgramByBoundaryDouble(GetID(),mn ,mx,GetStep());
			}
	virtual	int	GetTypeCode(void)		override{	return 15;	}
	virtual	int	GetParamID(void)		override{	return GetID();	}
	virtual	void	Set(int data)		override{	HistgramDimStocker<double>::Set((double)data);	}
	virtual	void	Set(double data)	override{	HistgramDimStocker<double>::Set(data);			}
	virtual	bool	GetMinMaxData(double &MinData ,double &MaxData)	override;
	virtual	bool	GetDistribution(double &Average,double &Dispersion)	override;
	virtual	bool	AddTo(HistStepClass *Dest)	override{	return HistgramDimStocker<double>::AddTo(Dest);	}
	virtual	bool	SaveText(QIODevice *f)		override;
};

//---------------------------------------------------------------------

class	HistgramInThreshold : public NPListPack<HistgramByParamBase>
{
	AlgorithmItemRoot					*Item;
public:

	HistgramInThreshold(AlgorithmItemRoot *item);

	void	Copy(const HistgramInThreshold &src);

	void	RegistByte	(const QString &Name ,int id);
	void	RegistChar	(const QString &Name ,int id);
	void	RegistShort	(const QString &Name ,int id);
	void	RegistInt	(const QString &Name ,int id);
	void	RegistDouble(const QString &Name ,int id);

	void	RegistBoundaryByte	(const QString &Name ,int id ,BYTE mindata ,BYTE maxdata);
	void	RegistBoundaryChar	(const QString &Name ,int id ,char mindata ,char maxdata);
	void	RegistBoundaryShort	(const QString &Name ,int id ,short mindata ,short maxdata);
	void	RegistBoundaryInt	(const QString &Name ,int id ,int mindata ,int maxdata);
	void	RegistBoundaryDouble(const QString &Name ,int id ,double mindata ,double maxdata,double step=1.0);

	HistgramByParamBase	*GetHistgramBase(int id);

	void	AddHist(int id ,BYTE data);
	void	AddHist(int id ,char data);
	void	AddHist(int id ,int  data);
	void	AddHist(int id ,short data);
	void	AddHist(int id ,double data);

	void	EnumHistgram(IntList &RetIDLists);

	bool	SaveHistgram(QIODevice *f);
	bool	LoadHistgram(QIODevice *f);
	void	ClearHistgram(void);
};


class	ParamAutoThreshold
{
public:
	int		LibID;
	int		HistID;
	bool	ModeOneWork;
	bool	ModeMultiWork;
	double	AdoptRate;
	double	SigmaMultiply;
	double	ThresholdA,ThresholdB;
	bool	DirectThreshold;

	ParamAutoThreshold(void);
	virtual ~ParamAutoThreshold(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	HistgramInBinder
{
public:
	virtual	bool	ExecuteAutoThreshold(ParamAutoThreshold &executer);
	virtual	bool	ExecuteAutoThresholdByAlgo(AlgorithmItemPointerListContainerByLibContainer &Items ,ParamAutoThreshold &executer){	return true;	}
	virtual	ParamAutoThreshold *CreateParamAutoThreshold(void);
protected:
	virtual	void	GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items)=0;
};


//==============================================================================================
class	HistgramByParamBasePointerList : public NPList<HistgramByParamBasePointerList>
{
public:
	HistgramByParamBase	*Pointer;

	HistgramByParamBasePointerList(HistgramByParamBase *a):Pointer(a){}
};

class	HistgramByParamBasePointerContainer : public NPListPack<HistgramByParamBasePointerList>
{
public:
	HistgramByParamBasePointerContainer(void){}

	void	Add(HistgramByParamBase *a)	{	AppendList(new HistgramByParamBasePointerList(a));	}
};

//==============================================================================================

class	HistStepClass
{
	int		*HistData;
	double	MinData;
	double	MaxData;
	double	Step;
	int		AllocatedNumb;

public:
	HistStepClass(void);
	~HistStepClass(void);

	void	Create(double mindata ,double maxdata ,double step);
	void	Clear(void);
	int		GetDimCount(void)		{	return AllocatedNumb;	}
	int		GetHistData(int index)	{	return HistData[index];	}
	double	GetMinData(void)		{	return MinData;			}
	double	GetMaxData(void)		{	return MaxData;			}
	int		GetStep(void)			{	return Step;			}

	void	AddCount(double value ,int Counter);

	HistStepClass	&operator=(const HistStepClass &src);
	HistStepClass	&operator+=(const HistStepClass &src);

	int		GetTotalCount(void);
	double	GetAverage(void);
	double	GetDispersion(double Avr=-99999999.0);
	bool	GetAverageByTable(double AdoptedRate ,double &Avr , double &VAdd);

	double	RealPercentage(double ThresholdL,double ThresholdH);
	double	IdealPercentage(double ThresholdL,double ThresholdH);
	void	GetRealThreshold(double SpareRateL,double SpareRateH 
							,double &ThresholdL,double &ThresholdH);
	void	GetIdealThreshold(double SpareRateL,double SpareRateH 
							 ,double &ThresholdL,double &ThresholdH);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//==============================================================================================

class	HistgramTypeListInAlgo : public NPList<HistgramTypeListInAlgo>
{
public:
	int			HistID;
	QString		HistName;

	HistgramTypeListInAlgo(void){	HistID=-1;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	HistgramTypeListInAlgo	&operator=(const HistgramTypeListInAlgo &src);
	bool					operator==(const HistgramTypeListInAlgo &src)	const;
};

class	HistgramTypeListInAlgoContainer : public NPListPack<HistgramTypeListInAlgo>
{
public:
	HistgramTypeListInAlgoContainer(void){}

	HistgramTypeListInAlgoContainer	&operator=(const HistgramTypeListInAlgoContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//==============================================================================================

class	GUICmdReqEnumHistgram : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			GlobalPage;
	int			Layer;

	GUICmdReqEnumHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckEnumHistgram : public GUICmdPacketBase
{
public:
	HistgramTypeListInAlgoContainer	RetLists;

	GUICmdAckEnumHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUICmdReqHistgram : public GUICmdPacketBase
{
public:
	int			ItemID;
	int			HistID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;

	GUICmdReqHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckHistgram : public GUICmdPacketBase
{
public:
	HistStepClass	HistData;

	GUICmdAckHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUICmdReqInfoForHistgram : public GUICmdPacketBase
{
public:
	int			ItemID;
	int			HistID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;

	GUICmdReqInfoForHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckInfoForHistgram : public GUICmdPacketBase
{
public:
	QString	HistName;
	int		LibID;

	GUICmdAckInfoForHistgram(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==============================================================================================

class	GUICmdReqInfoForHistDirect : public GUICmdPacketBase
{
public:
	int			LibID;
	int			ItemID;
	int			HistID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;

	GUICmdReqInfoForHistDirect(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckInfoForHistDirect : public GUICmdPacketBase
{
public:
	ValueDimStockerBase	*Data;

	GUICmdAckInfoForHistDirect(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==============================================================================================

class	GUICmdReqAlgorithmUsageLib : public GUICmdPacketBase
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;

	GUICmdReqAlgorithmUsageLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlgorithmUsageLib : public GUICmdPacketBase
{
public:
	IntList		LibList;

	GUICmdAckAlgorithmUsageLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUICmdReqHistgramLib : public GUICmdPacketBase
{
public:
	int			LibID;
	int			HistID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;

	GUICmdReqHistgramLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckHistgramLib : public GUICmdPacketBase
{
public:
	HistStepClass	HistData;
	QString			HistName;

	GUICmdAckHistgramLib(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUICmdReqSetThreshold : public GUICmdPacketBase
{
public:
	int			LibID;
	int			HistID;
	QString		AlgoRoot;
	QString		AlgoName;
	int			Phase;
	int			Layer;
	double		ThresholdA,ThresholdB;

	GUICmdReqSetThreshold(LayersBase *base,const QString &EmitterRoot ,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

bool	GetAverageByTable(double Table[] ,int TableCount ,double AdoptedRate ,double &Avr , double &VAdd);



#endif