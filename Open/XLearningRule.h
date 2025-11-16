/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Open\XLearningRule.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XLEARNINGRULEH
#define XLEARNINGRULEH

#include "XTypeDef.h"
#include "XDoubleClass.h"
#include "XServiceForLayers.h"

class	AlgorithmItemRoot;
class	LayersBase;
class	LearningValueBase;
class	ResultInspection;
class	LearningPlanBase;
class	LearningLeafForSave;
class	LearningLeafForSaveContainer;

class	LearningRegList : public NPList<LearningRegList>
{
public:
	LearningValueBase	*Base;
	enum _DataType{
		_LearnReg_Nothing	=0
		,_LearnReg_BYTE		=1
		,_LearnReg_WORD		=2
		,_LearnReg_DWORD	=3
		,_LearnReg_int16	=4
		,_LearnReg_int32	=5
		,_LearnReg_int64	=6
		,_LearnReg_bool		=7
		,_LearnReg_double	=8
		,_LearnReg_float	=9
	}DataType;

	bool	Changed;
	QString	Name;
	void	*Data;				//Refers address
	void	*TmpDataByLoad;
	double MinData ,MaxData ,DivData;
	double	CurrentDiv;

	LearningRegList(const QString &name,LearningValueBase	*base);
	LearningRegList(void);
	virtual	~LearningRegList(void);

	LearningValueBase	*GetBase(void)	{	return Base;	}
	void	InitialTotal(void)	{	CurrentDiv=DivData;		}
	void	InitialChanged(void){	Changed=false;	}

	void	AddDiv(void);
	void	SubDiv(void);
	void	Change(double DifResult);
	void	ChangeDiv(void);

	void	Set(BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(bool *data);
	void	Set(double *data	,double MinData ,double MaxData ,double DivData);
	void	Set(float *data	,float MinData	,float MaxData	,float DivData);

	bool	Save(LearningLeafForSave *f);
	bool	Load(LearningLeafForSave *f);

	bool	IsMatchingLeaf(LearningRegList *s);
	void	CopyData(LearningRegList *s);

private:
	int		GetDataByte(void);
};

inline LearningRegList::LearningRegList(const QString &name,LearningValueBase *base)
:Name(name)
{
	Base	=base;
	DataType=_LearnReg_Nothing;
	Data	=NULL;
	MinData	=0;
	MaxData	=99999999;
	DivData	=1.0;
	CurrentDiv=1.0;
	Changed	=false;
}
inline LearningRegList::LearningRegList(void)
{
	DataType=_LearnReg_Nothing;
	Data	=NULL;
	MinData	=0;
	MaxData	=99999999;
	DivData	=1.0;
	CurrentDiv=1.0;
	Changed	=false;
}
inline	LearningRegList::~LearningRegList(void)
{
}


class	LearningRegListByLib : public NPList<LearningRegListByLib>
{
public:
	int32	LibType;
	int32	LibID;
	NPListPack<LearningRegList>	LearningRegDats;

	LearningRegListByLib(void);

	bool	Delete(LearningValueBase *data);
	void	InitialTotal(void);
	void	InitialChanged(void);
	void	AddDiv(LearningRegList *v);
	void	SubDiv(LearningRegList *v);
	void	Change(LearningRegList *v,double DifResult);
	void	ChangeDiv(void);
	LearningRegList	*GetNextValue(LearningRegList *CurrentValue);

	void	Set(LearningValueBase *Base,const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(LearningValueBase *Base,const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(LearningValueBase *Base,const QString &Name,DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,bool *data);
	void	Set(LearningValueBase *Base,const QString &Name,double *data,double MinData ,double MaxData ,double DivData);
	void	Set(LearningValueBase *Base,const QString &Name,float *data	,float MinData	,float MaxData	,float DivData);

	bool	Save(LearningLeafForSaveContainer &LearnedDatabase);
	bool	Load(LearningLeafForSaveContainer &LearnedDatabase);

	bool	IsMatching(LearningRegListByLib *src);
};

class	LearningRegListContainer : public NPListPack<LearningRegListByLib>
{
public:
	LearningRegListContainer(void){}

	void	Delete(LearningValueBase *data);
	void	InitialTotal(void);
	void	InitialChanged(void);
	void	ChangeDiv(void);

	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, bool *data);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, double *data	,double MinData ,double MaxData ,double DivData);
	void	Set(LearningValueBase *Base,const QString &Name,int LibType,int LibID, float *data	,float MinData	,float MaxData	,float DivData);

	void	BuildPlan(LearningPlanBase &Plan);

	bool	Save(LearningLeafForSaveContainer &LearnedDatabase);
	bool	Load(LearningLeafForSaveContainer &LearnedDatabase);
};

class	LearningPlanBase : public ServiceForLayers
{
public:
	LearningRegListByLib	*CurrentLib;
	LearningRegList			*CurrentValue;
	DoubleList				ResultList;
	int						MaxLoopCount;
	
	LearningPlanBase(LayersBase *base);

	void	InitialTop(void);

	virtual	double	GetResult(ResultInspection &R)=0;

	void	ExeLowLevelTotalFirst(void);
	void	ExeLowLevelLoopFirst(void);
	void	ExeLowLevelLoopContent(void);

protected:
	virtual	void	ExecuteTotalLoop(void);
	virtual	void	ExecuteOneLoop(void);
	virtual	void	ExecuteOneValue(void);

};

//-----------------------------------------------------------------------------------------

class	LearningLeafForSave : public NPList<LearningLeafForSave>
{
public:
	LearningRegList::_DataType	DataType;
	QString	Name;
	void	*Data;		//Allocated
	int32	LibType;
	int32	LibID;

	LearningLeafForSave(void){	Data=NULL;	DataType=LearningRegList::_LearnReg_Nothing;	}
	~LearningLeafForSave(void);

	void	ReleaseData(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningLeafForSave	&operator=(LearningLeafForSave &src);

private:
	int		GetDataByte(void);
};

class	LearningLeafForSaveContainer: public NPListPack<LearningLeafForSave>
{
public:
	LearningLeafForSaveContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LearningLeafForSaveContainer	&operator=(LearningLeafForSaveContainer &src);
};



//-----------------------------------------------------------------------------------------

class	LearningValueBase
{
	LayersBase *Base;
public:
	LearningValueBase(void);
	virtual	~LearningValueBase(void);

	virtual	void	SetLearn(LayersBase *base){	Base=base;	}

	LayersBase *GetLayers(void){	return Base;	}
};

class	LearningValueInThreshold : public LearningValueBase
{
	class	TmpLearningValueInThreshold : public NPList<TmpLearningValueInThreshold>
	{
	public:
		LearningRegList::_DataType	DataType;
		QString	Name;
		void	*Data;
		double MinData ,MaxData ,DivData;
		TmpLearningValueInThreshold(void){};
	};
	NPListPack<TmpLearningValueInThreshold>	TmpPack;
	AlgorithmItemRoot *Item;
public:

	LearningValueInThreshold(AlgorithmItemRoot *item){	Item=item;	}

	void	Set(const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(const QString &Name,DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(const QString &Name,int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(const QString &Name,int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(const QString &Name,int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(const QString &Name,bool *data);
	void	Set(const QString &Name,double *data	,double MinData ,double MaxData ,double DivData);
	void	Set(const QString &Name,float *data	,float MinData	,float MaxData	,float DivData);

	virtual	void	SetLearn(LayersBase *base);
};

class	LearningValueByLib : public LearningValueBase
{
public:
	LearningValueByLib(void){}

	void	Set(const QString &Name,int LibType,int LibID, BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(const QString &Name,int LibType,int LibID, WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(const QString &Name,int LibType,int LibID, DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(const QString &Name,int LibType,int LibID, int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(const QString &Name,int LibType,int LibID, int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(const QString &Name,int LibType,int LibID, int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(const QString &Name,int LibType,int LibID, bool *data);
	void	Set(const QString &Name,int LibType,int LibID, double *data	,double MinData ,double MaxData ,double DivData);
	void	Set(const QString &Name,int LibType,int LibID, float *data	,float MinData	,float MaxData	,float DivData);
};

class	LearningValueByEach : public LearningValueBase
{
public:
	LearningValueByEach(void){}

	void	Set(const QString &Name,BYTE *data	,BYTE MinData	,BYTE MaxData	,BYTE DivData);
	void	Set(const QString &Name,WORD *data	,WORD MinData	,WORD MaxData	,WORD DivData);
	void	Set(const QString &Name,DWORD *data	,DWORD MinData	,DWORD MaxData	,DWORD DivData);
	void	Set(const QString &Name,int16 *data	,int16 MinData	,int16 MaxData	,int16 DivData);
	void	Set(const QString &Name,int32 *data	,int32 MinData	,int32 MaxData	,int32 DivData);
	void	Set(const QString &Name,int64 *data	,int64 MinData	,int64 MaxData	,int64 DivData);
	void	Set(const QString &Name,bool *data);
	void	Set(const QString &Name,double *data	,double MinData ,double MaxData ,double DivData);
	void	Set(const QString &Name,float *data	,float MinData	,float MaxData	,float DivData);
};


#endif