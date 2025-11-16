#if	!defined(XMEASURECOMMON_H)
#define	XMEASURECOMMON_H

#include "NListComp.h"
#include <QIODevice>
#include "XGeneralFunc.h"


class	AlgorithmItemPI;

class	MeasureCommon
{
public:
	MeasureCommon(void){}

	virtual	int		GetItemID(void)						=0;
	virtual	double	GetIsolation(double x ,double y)	=0;
	virtual	double	GetDrawParam(double x ,double y)	=0;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	=0;
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)	=0;
	virtual	void	GetShiftVector(double &sx, double &sy)	=0;

	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)	=0;
	virtual	void	GetCenterPoint(double &cx, double &cy)	=0;
	virtual	void	Move(double dx ,double dy)				=0;

	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	=0;

};

class	MeasureDataList : public NPListSaveLoad<MeasureDataList>
{
public:
	int		Page;
	QString	Name;
	QString	AlgoType;
	double	Value;

	MeasureDataList(void){}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	MeasureDataContainer :public NPListPackSaveLoad<MeasureDataList>
{
public:
	MeasureDataContainer(void){}
	virtual	MeasureDataList	*Create(void){	return new MeasureDataList();	}
};

inline bool	MeasureDataList::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Name)==false)
		return false;
	if(::Save(f,AlgoType)==false)
		return false;
	if(::Save(f,Value)==false)
		return false;
	return true;
}

inline bool	MeasureDataList::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Name)==false)
		return false;
	if(::Load(f,AlgoType)==false)
		return false;
	if(::Load(f,Value)==false)
		return false;
	return true;

}

class	CmdReqMeasureDataPacket : public GUIDirectMessage
{
public:
	MeasureDataContainer	Data;

	CmdReqMeasureDataPacket(LayersBase *base):GUIDirectMessage(base){}
};

struct	MeasureHVInfoOld
{
	bool	bOnlyInside;
	bool	bHorizontal;
	bool	bFrom0;
	bool	bPartnerFrom0;
	double	PartnerPos;		//mm
	int32	RegLineLength;
	double	CorrectLength;	//mm
	double	OKWidth;		//mm

	MeasureHVInfoOld(void)
	{
		bOnlyInside		=false;
		bHorizontal		=true;
		bFrom0			=true;
		bPartnerFrom0	=true;
		PartnerPos		=0;
		RegLineLength	=0;
		CorrectLength	=0;
		OKWidth			=0;
	}
};

struct	MeasureHVInfo
{
	char	MeasureName[65];
	bool	bOnlyInside;
	bool	bHorizontal;
	bool	bFrom0;
	bool	bPartnerFrom0;
							//ÔPet‚Í@bOnlyInside=true , bHorizontal=false ,bFrom0=false ,bPartnerFrom0=true/false
	double	PartnerPos;		//mm
	int32	RegLineLength;
	double	CorrectLength;	//mm
	double	OKWidth;		//mm

	MeasureHVInfo(void)
	{
		MeasureName[0]	=0;
		bOnlyInside		=false;
		bHorizontal		=true;
		bFrom0			=true;
		bPartnerFrom0	=true;
		PartnerPos		=0;
		RegLineLength	=0;
		CorrectLength	=0;
		OKWidth			=0;
	}
};

class	BladeMeasure
{
public:
	struct	MeasureHVInfo	GenDatas[100];
	int32	CountGenDatas;
	int32	UpperFilmIndex;
	int32	UpperFilmPointNo;
	int32	LowerFilmIndex;
	int32	LowerFilmPointNo;


	BladeMeasure(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	BladeMeasure	&operator=(const BladeMeasure &src);
};
inline	BladeMeasure::BladeMeasure(void)
{
	CountGenDatas=0;
	UpperFilmIndex=-1;
	LowerFilmIndex=-1;
	UpperFilmPointNo=-1;
	LowerFilmPointNo=-1;
}
inline	bool	BladeMeasure::Save(QIODevice *f)
{
	int32	Ver=3;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,CountGenDatas)==false)
		return false;
	if(f->write((const char *)GenDatas,sizeof(GenDatas))!=sizeof(GenDatas))
		return false;
	if(::Save(f,UpperFilmIndex)==false)
		return false;
	if(::Save(f,UpperFilmPointNo)==false)
		return false;
	if(::Save(f,LowerFilmIndex)==false)
		return false;
	if(::Save(f,LowerFilmPointNo)==false)
		return false;
	return true;
}
inline	bool	BladeMeasure::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,CountGenDatas)==false)
		return false;
	if(Ver==1){
		struct	MeasureHVInfoOld	GenDatas1[sizeof(GenDatas)/sizeof(GenDatas[0])];
		if(f->read((char *)GenDatas1,sizeof(GenDatas1))!=sizeof(GenDatas1))
			return false;
		for(int i=0;i<sizeof(GenDatas1)/sizeof(GenDatas1[0]);i++){
			GenDatas[i].bOnlyInside		=GenDatas1[i].bOnlyInside	;
			GenDatas[i].bHorizontal		=GenDatas1[i].bHorizontal	;
			GenDatas[i].bFrom0			=GenDatas1[i].bFrom0		;
			GenDatas[i].bPartnerFrom0	=GenDatas1[i].bPartnerFrom0	;
			GenDatas[i].PartnerPos		=GenDatas1[i].PartnerPos	;
			GenDatas[i].RegLineLength	=GenDatas1[i].RegLineLength	;
			GenDatas[i].CorrectLength	=GenDatas1[i].CorrectLength	;
			GenDatas[i].OKWidth			=GenDatas1[i].OKWidth		;
		}
	}
	else{
		if(f->read((char *)GenDatas,sizeof(GenDatas))!=sizeof(GenDatas))
			return false;
	}
	if (Ver>=3) {
		if(::Load(f,UpperFilmIndex)==false)
			return false;
		if(::Load(f,UpperFilmPointNo)==false)
			return false;
		if(::Load(f,LowerFilmIndex)==false)
			return false;
		if(::Load(f,LowerFilmPointNo)==false)
			return false;
	}
	return true;
}

inline	BladeMeasure	&BladeMeasure::operator=(const BladeMeasure &src)
{
	CountGenDatas	=src.CountGenDatas;
	memcpy(GenDatas,src.GenDatas,sizeof(GenDatas));
	return *this;
}

//=================================================================================================

class MeasureDistanceItemInfo : public NPListSaveLoad<MeasureDistanceItemInfo>
{
public:
	struct {
		int	Phase;
		int	Page;
		int	MeasureNo;
		int	ItemID;

		double	OKLengthL;
		double	OKLengthH;
		double	CurrentValue;

		double	OKLengthLUnit;
		double	OKLengthHUnit;
		double	CurrentValueUnit;
	}Data;

	MeasureDistanceItemInfo(void){}
	MeasureDistanceItemInfo(const MeasureDistanceItemInfo &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	MeasureDistanceItemInfo	&operator=(const MeasureDistanceItemInfo &src);
private:

};

class MeasureDistanceItemInfoContainer : public NPListPackSaveLoad<MeasureDistanceItemInfo>
{
public:
	MeasureDistanceItemInfoContainer(void){}

	virtual	MeasureDistanceItemInfo	*Create(void)	{	return new MeasureDistanceItemInfo();	}
	MeasureDistanceItemInfoContainer	&operator=(const MeasureDistanceItemInfoContainer &src);
	MeasureDistanceItemInfoContainer	&operator+=(const MeasureDistanceItemInfoContainer &src);
};

inline	MeasureDistanceItemInfo::MeasureDistanceItemInfo(const MeasureDistanceItemInfo &src)
{
	Data=src.Data;
}
inline	MeasureDistanceItemInfo	&MeasureDistanceItemInfo::operator=(const MeasureDistanceItemInfo &src)
{
	Data=src.Data;
	return *this;
}
inline	bool	MeasureDistanceItemInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
inline	bool	MeasureDistanceItemInfo::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}
inline	MeasureDistanceItemInfoContainer	&MeasureDistanceItemInfoContainer::operator=(const MeasureDistanceItemInfoContainer &src)
{
	RemoveAll();
	for(MeasureDistanceItemInfo *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		MeasureDistanceItemInfo	*d=new MeasureDistanceItemInfo(*s);
		AppendList(d);
	}
	return *this;
}
inline	MeasureDistanceItemInfoContainer	&MeasureDistanceItemInfoContainer::operator+=(const MeasureDistanceItemInfoContainer &src)
{
	for(MeasureDistanceItemInfo *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		MeasureDistanceItemInfo	*d=new MeasureDistanceItemInfo(*s);
		AppendList(d);
	}
	return *this;
}

//============================================================================

class	MeasureHolePosDataList : public NPListSaveLoad<MeasureHolePosDataList>
{
public:
	struct HDataStruct
	{
		int		Page;
		int		ItemID;
		double	MasterCx,MasterCy;
		double	TargetCx,TargetCy;
		double	MasterRx,MasterRy;
		double	TargetRx,TargetRy;
	}HData;

	MeasureHolePosDataList(void){}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	MeasureHolePosDataContainer :public NPListPackSaveLoad<MeasureHolePosDataList>
{
public:
	MeasureHolePosDataContainer(void){}
	virtual	MeasureHolePosDataList	*Create(void){	return new MeasureHolePosDataList();	}
};

inline bool	MeasureHolePosDataList::Save(QIODevice *f)
{
	if(f->write((const char *)&HData,sizeof(HData))!=sizeof(HData))
		return false;
	return true;
}

inline bool	MeasureHolePosDataList::Load(QIODevice *f)
{
	if(f->read((char *)&HData,sizeof(HData))!=sizeof(HData))
		return false;
	return true;
}

class	CmdReqMeasureHolePosDataPacket : public GUIDirectMessage
{
public:
	MeasureHolePosDataContainer	Data;

	CmdReqMeasureHolePosDataPacket(LayersBase *base):GUIDirectMessage(base){}
};


#endif