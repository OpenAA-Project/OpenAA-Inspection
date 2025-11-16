/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XCheckDataValidation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XCheckDataValidation.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XDisplayBitImage.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlignmentLarge.h"
#include "XAlignmentLargeLibrary.h"


CheckDataValidationThresholdBase::CheckDataValidationThresholdBase(AlgorithmItemRoot *parent)
	:AlgorithmThreshold(parent)
{
	LibType		=-1;
	LibID		=-1;
}
bool	CheckDataValidationThresholdBase::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CheckDataValidationThresholdBase	*s=dynamic_cast<const CheckDataValidationThresholdBase *>(&src);
	if(s!=NULL){
		if(LibType	==s->LibType
		&& LibID	==s->LibID)
			return true;
	}
	return false;
}
void	CheckDataValidationThresholdBase::CopyFrom(const AlgorithmThreshold &src)
{
	const CheckDataValidationThresholdBase	*s=dynamic_cast<const CheckDataValidationThresholdBase *>(&src);
	if(s!=NULL){
		LibType			=s->LibType;
		LibID			=s->LibID;
	}
}
bool	CheckDataValidationThresholdBase::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(::Save(file,LibType)==false)
		return(false);
	if(::Save(file,LibID)==false)
		return(false);

	return(true);
}
bool	CheckDataValidationThresholdBase::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(::Load(file,LibType)==false)
		return(false);
	if(::Load(file,LibID)==false)
		return(false);

	return(true);
}
CheckDataValidationItemBase::CheckDataValidationItemBase(void)
{
	CheckNG=false;
}
void	CheckDataValidationItemBase::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	CheckDataValidationDrawAttr	*MAttr=(CheckDataValidationDrawAttr *)Attr;
	if(GetItemClassType()==(int)MAttr->VType){
		AlgorithmItemPITemplate<CheckDataValidationInPage,CheckDataValidationBase>::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
//=====================================================================================

CheckDataValidationExistItemAreaThreshold::CheckDataValidationExistItemAreaThreshold(CheckDataValidationExistItemAreaItem *parent)
:CheckDataValidationThresholdBase(parent)
{
	FilledPercentageInMask	=0;
	CheckExistence			=false;
}

bool	CheckDataValidationExistItemAreaThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CheckDataValidationExistItemAreaThreshold	*s=dynamic_cast<const CheckDataValidationExistItemAreaThreshold *>(&src);
	if(s!=NULL){
		if(CheckDataValidationThresholdBase::IsEqual(src)==true
		&& FilledPercentageInMask	==s->FilledPercentageInMask
		&& CheckExistence			==s->CheckExistence)
			return true;
	}
	return false;
}
void	CheckDataValidationExistItemAreaThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const CheckDataValidationExistItemAreaThreshold	*s=dynamic_cast<const CheckDataValidationExistItemAreaThreshold *>(&src);
	if(s!=NULL){
		CheckDataValidationThresholdBase::CopyFrom(src);
		FilledPercentageInMask	=s->FilledPercentageInMask;
		CheckExistence	=s->CheckExistence;
	}
}
bool	CheckDataValidationExistItemAreaThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Save(file)==false)
		return(false);
	if(::Save(file,FilledPercentageInMask)==false)
		return(false);
	if(::Save(file,CheckExistence)==false)
		return(false);
	return(true);
}
bool	CheckDataValidationExistItemAreaThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Load(file)==false)
		return(false);

	if(::Load(file,FilledPercentageInMask)==false)
		return(false);
	if(::Load(file,CheckExistence)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
CheckDataValidationExistItemAreaItem::CheckDataValidationExistItemAreaItem(void)
{
}

struct CheckDataValidationExistItemAreaItemInfo
{
	FlexArea	Area;
	int			LibID;
};

static	bool CheckDataValidationExistItemAreaItemFunc(void *caller,AlgorithmItemRoot *item)
{
	struct CheckDataValidationExistItemAreaItemInfo	*VInfo=(struct CheckDataValidationExistItemAreaItemInfo *)caller;

	if(VInfo->LibID==item->GetLibID()
	&& VInfo->Area.CheckOverlap(&item->GetArea())==true){
		return true;
	}
	return false;
}

ExeResult	CheckDataValidationExistItemAreaItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int		Phase=GetPhaseCode();
	int		Page=GetPage();
	const	CheckDataValidationExistItemAreaThreshold	*RThr=GetThresholdR();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(RThr->LibType);
	AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(Phase);
	if(APhase!=NULL){
		AlgorithmInPageRoot			*APage=APhase->GetPageData(Page);
		if(APage!=NULL){
			AlgorithmItemPointerListContainer Items;
			struct CheckDataValidationExistItemAreaItemInfo	VInfo;
			VInfo.Area	=GetArea();
			VInfo.LibID	=RThr->LibID;
			APage->EnumItems(&VInfo,Items , CheckDataValidationExistItemAreaItemFunc);
			if(RThr->CheckExistence==true){
				if(Items.GetCount()==0){
					QString	LibName=GetLayersBase()->GetLibraryName(RThr->LibType,RThr->LibID);
					NGMessage=QString("設定領域内に存在しない:")
							 +LibName;
					CheckNG=true;
				}
			}
			ConstMapBufferListContainer MaskMap;

			if(GetReflectionMap(_Reflection_Mask,MaskMap)==true){
				ConstMapBuffer Map;
				MaskMap.BindOr(Map);

				BYTE	**TmpMap=MakeMatrixBuff(Map.GetXByte() ,Map.GetYLen());
				MatrixBuffCopy	(TmpMap		,Map.GetXByte() ,Map.GetYLen()
								,Map.GetBitMap() ,Map.GetXByte() ,Map.GetYLen());
				for(AlgorithmItemPointerList *L=Items.GetFirst();L!=NULL;L=L->GetNext()){
					L->GetItem()->GetArea().MakeNotBitData(TmpMap,Map.GetXByte() ,Map.GetYLen());
				}

				int64	BitCount=GetArea().GetCrossBitCount(TmpMap);
				DeleteMatrixBuff(TmpMap,Map.GetYLen());
				double	Percentage=100.0*((double)BitCount)/((double)GetArea().GetPatternByte());
				if(Percentage<RThr->FilledPercentageInMask){
					QString	LibName=GetLayersBase()->GetLibraryName(RThr->LibType,RThr->LibID);
					NGMessage=QString("設定領域内のマスクに対しての割合が小さい:(")
							 +QString::number(Percentage,'f',1)
							 +QString("%),")
							 +LibName;
					CheckNG=true;
				}
			}
		}
	}

	return Ret;
}
QString	CheckDataValidationExistItemAreaItem::CheckedMessage(void)
{
	return NGMessage;
}

//=====================================================================================

CheckDataValidationExistItemVectorThreshold::CheckDataValidationExistItemVectorThreshold(CheckDataValidationExistItemVectorItem *parent)
:CheckDataValidationThresholdBase(parent)
{
}

bool	CheckDataValidationExistItemVectorThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CheckDataValidationExistItemVectorThreshold	*s=dynamic_cast<const CheckDataValidationExistItemVectorThreshold *>(&src);
	if(s!=NULL){
		if(CheckDataValidationThresholdBase::IsEqual(src)==true)
			return true;
	}
	return false;
}
void	CheckDataValidationExistItemVectorThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const CheckDataValidationExistItemVectorThreshold	*s=dynamic_cast<const CheckDataValidationExistItemVectorThreshold *>(&src);
	if(s!=NULL){
		CheckDataValidationThresholdBase::CopyFrom(src);
	}
}
bool	CheckDataValidationExistItemVectorThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Save(file)==false)
		return(false);

	return(true);
}
bool	CheckDataValidationExistItemVectorThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Load(file)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
CheckDataValidationExistItemVectorItem::CheckDataValidationExistItemVectorItem(void)
{
}

struct CheckDataValidationExistItemVectorItemInfo
{
	FlexArea	Area;
	int			LibID;
};

static	bool CheckDataValidationExistItemVectorItemFunc(void *caller,AlgorithmItemRoot *item)
{
	struct CheckDataValidationExistItemVectorItemInfo	*VInfo=(struct CheckDataValidationExistItemVectorItemInfo *)caller;

	if(VInfo->LibID==item->GetLibID()){
		VectorLineBase	*V=item->GetVector();
		if(V!=NULL){
			if(V->CheckOverlap(VInfo->Area)==true){
				return true;
			}
		}
	}
	return false;
}

ExeResult	CheckDataValidationExistItemVectorItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int		Phase=GetPhaseCode();
	int		Page=GetPage();
	const	CheckDataValidationExistItemVectorThreshold	*RThr=GetThresholdR();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(RThr->LibType);
	AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(Phase);
	if(APhase!=NULL){
		AlgorithmInPageRoot			*APage=APhase->GetPageData(Page);
		if(APage!=NULL){
			AlgorithmItemPointerListContainer Items;
			struct CheckDataValidationExistItemVectorItemInfo	VInfo;
			VInfo.Area	=GetArea();
			VInfo.LibID	=RThr->LibID;
			APage->EnumItems(&VInfo,Items , CheckDataValidationExistItemVectorItemFunc);
			if(Items.GetCount()==0){
				CheckNG=true;
			}
		}
	}

	return Ret;
}
QString	CheckDataValidationExistItemVectorItem::CheckedMessage(void)
{
	const	CheckDataValidationExistItemVectorThreshold	*RThr=GetThresholdR();
	QString	LibName=GetLayersBase()->GetLibraryName(RThr->LibType,RThr->LibID);

	return QString("設定領域内に存在しない:")
		  +LibName;
}

//=====================================================================================

CheckDataValidationCheckMinMaxThreshold::CheckDataValidationCheckMinMaxThreshold(CheckDataValidationCheckMinMaxItem *parent)
:CheckDataValidationThresholdBase(parent)
{
	ParamID	=-1;
}

bool	CheckDataValidationCheckMinMaxThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CheckDataValidationCheckMinMaxThreshold	*s=dynamic_cast<const CheckDataValidationCheckMinMaxThreshold *>(&src);
	if(s!=NULL){
		if(CheckDataValidationThresholdBase::IsEqual(src)==true
		&& ParamID	==s->ParamID
		&& Value	==s->Value){
			return true;
		}
	}
	return false;
}
void	CheckDataValidationCheckMinMaxThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const CheckDataValidationCheckMinMaxThreshold	*s=dynamic_cast<const CheckDataValidationCheckMinMaxThreshold *>(&src);
	if(s!=NULL){
		CheckDataValidationThresholdBase::CopyFrom(src);
		ParamID	=s->ParamID;
		Value	=s->Value;
	}
}
bool	CheckDataValidationCheckMinMaxThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Save(file)==false)
		return(false);
	if(::Save(file,ParamID)==false)
		return(false);
	if(Value.Save(file)==false)
		return(false);
	return(true);
}
bool	CheckDataValidationCheckMinMaxThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Load(file)==false)
		return(false);
	if(::Load(file,ParamID)==false)
		return(false);
	if(Value.Load(file)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
ThresholdVariableMinMax::ThresholdVariableMinMax(void)
{
	MinValueDouble	=0;
	MaxValueDouble	=0;
	MinValueInt64	=0;
	MaxValueInt64	=0;
	FixedValueBool	=true;
	ValueType=_DT_None;
}
ThresholdVariableMinMax::ThresholdVariableMinMax(const ThresholdVariableMinMax &src)
{
	MinValueDouble	=src.MinValueDouble	;
	MaxValueDouble	=src.MaxValueDouble	;
	MinValueInt64	=src.MinValueInt64	;
	MaxValueInt64	=src.MaxValueInt64	;
	FixedValueBool	=src.FixedValueBool	;
	ValueType		=src.ValueType		;
}

ThresholdVariableMinMax	&ThresholdVariableMinMax::operator=(const ThresholdVariableMinMax &src)
{
	MinValueDouble	=src.MinValueDouble	;
	MaxValueDouble	=src.MaxValueDouble	;
	MinValueInt64	=src.MinValueInt64	;
	MaxValueInt64	=src.MaxValueInt64	;
	FixedValueBool	=src.FixedValueBool	;
	ValueType		=src.ValueType		;
	return *this;
}
bool	ThresholdVariableMinMax::operator==(const ThresholdVariableMinMax &src)	const
{
	switch(ValueType){
	case _DT_bool				:
		return (FixedValueBool==src.FixedValueBool)?true:false;
	case _DT_byte				:
	case _DT_char			:
	case _DT_short			:
	case _DT_ushort			:
	case _DT_int			:
	case _DT_int32			:
	case _DT_uint32			:
	case _DT_int64			:
	case _DT_uint64			:
		return (MinValueInt64==src.MinValueInt64 && MaxValueInt64==src.MaxValueInt64)?true:false;
	case _DT_QString		:
		return false;
	case _DT_double			:
	case _DT_longdouble		:
	case _DT_float			:
		return (MinValueDouble==src.MinValueDouble && MaxValueDouble==src.MaxValueDouble)?true:false;
	}
	return false;
}

bool	ThresholdVariableMinMax::Save(QIODevice *f)
{
	if(::Save(f,MinValueDouble	)==false)	return false;
	if(::Save(f,MaxValueDouble	)==false)	return false;
	if(::Save(f,MinValueInt64	)==false)	return false;
	if(::Save(f,MaxValueInt64	)==false)	return false;
	if(::Save(f,FixedValueBool	)==false)	return false;
	int32	d=(int32)ValueType;
	if(::Save(f,d)==false)	return false;
	return true;
}
bool	ThresholdVariableMinMax::Load(QIODevice *f)
{
	if(::Load(f,MinValueDouble	)==false)	return false;
	if(::Load(f,MaxValueDouble	)==false)	return false;
	if(::Load(f,MinValueInt64	)==false)	return false;
	if(::Load(f,MaxValueInt64	)==false)	return false;
	if(::Load(f,FixedValueBool	)==false)	return false;
	int32	d;
	if(::Load(f,d)==false)	return false;
	ValueType=(DirectValueType)d;
	return true;
}

CheckDataValidationCheckMinMaxItem::CheckDataValidationCheckMinMaxItem(void)
{
}

struct CheckDataValidationMinMaxItemInfo
{
	FlexArea	Area;
	int			LibID;
	
	int32	ParamID;
	ThresholdVariableMinMax	Value;
};

static	bool CheckDataValidationMinMaxFunc(void *caller,AlgorithmItemRoot *item)
{
	struct CheckDataValidationMinMaxItemInfo	*VInfo=(struct CheckDataValidationMinMaxItemInfo *)caller;

	if(VInfo->LibID==item->GetLibID()
	&& VInfo->Area.CheckOverlap(&item->GetArea())==true){
		const	CheckDataValidationCheckMinMaxThreshold	*RThr=dynamic_cast<const CheckDataValidationCheckMinMaxThreshold *>(item->GetThresholdBaseReadable());
		ReportedTopicContainer RetContainer;
		RThr->MakeReportedTopics(RetContainer);
		ReportedTopic	*t=RetContainer[VInfo->ParamID];
		BYTE	tByte;
		char	tChar;
		short	tShort;
		short	tUShort;
		int		tInt;
		int32	tInt32;
		uint32	tUInt32;
		int64	tInt64;
		uint64	tUInt64;
		double	tDouble;
		long double	tLongDouble;
		float	tFloat;
		if(t!=NULL){
			switch(t->GetType()){
			case _DT_bool			:
				if(t->GetBool()==RThr->Value.FixedValueBool)
					return true;
				else
					break;
			case _DT_byte			:
				tByte=t->GetValue();
				if(RThr->Value.MinValueInt64<=tByte && tByte<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_char			:
				tChar=t->GetValue();
				if(RThr->Value.MinValueInt64<=tChar && tChar<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_short			:
				tShort=t->GetValue();
				if(RThr->Value.MinValueInt64<=tShort && tShort<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_ushort			:
				tUShort=t->GetValue();
				if(RThr->Value.MinValueInt64<=tUShort && tUShort<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_int			:
				tInt=t->GetValue();
				if(RThr->Value.MinValueInt64<=tInt && tInt<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_int32			:
				tInt32=t->GetValue();
				if(RThr->Value.MinValueInt64<=tInt32 && tInt32<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_uint32			:
				tUInt32=t->GetValue();
				if(RThr->Value.MinValueInt64<=tUInt32 && tUInt32<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_int64			:
				tInt64=t->GetValue();
				if(RThr->Value.MinValueInt64<=tInt64 && tInt64<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_uint64			:
				tUInt64=t->GetValue();
				if(RThr->Value.MinValueInt64<=tUInt64 && tUInt64<=RThr->Value.MaxValueInt64)
					return true;
				else
					break;
			case _DT_QString		:
				break;
			case _DT_double			:
				tDouble=t->GetDouble();
				if(RThr->Value.MinValueDouble<=tDouble && tDouble<=RThr->Value.MaxValueDouble)
					return true;
				else
					break;
			case _DT_longdouble		:
				tLongDouble=t->GetDouble();
				if(RThr->Value.MinValueDouble<=tLongDouble && tLongDouble<=RThr->Value.MaxValueDouble)
					return true;
				else
					break;
			case _DT_float			:
				tFloat=t->GetDouble();
				if(RThr->Value.MinValueDouble<=tFloat && tFloat<=RThr->Value.MaxValueDouble)
					return true;
				else
					break;
			}
		}
	}
	return false;
}
ExeResult	CheckDataValidationCheckMinMaxItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int		Phase=GetPhaseCode();
	int		Page=GetPage();
	const	CheckDataValidationCheckMinMaxThreshold	*RThr=GetThresholdR();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(RThr->LibType);
	AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(Phase);
	if(APhase!=NULL){
		AlgorithmInPageRoot			*APage=APhase->GetPageData(Page);
		if(APage!=NULL){
			AlgorithmItemPointerListContainer Items;
			struct CheckDataValidationExistItemVectorItemInfo	VInfo;
			VInfo.Area	=GetArea();
			VInfo.LibID	=RThr->LibID;
			APage->EnumItems(&VInfo,Items , CheckDataValidationExistItemVectorItemFunc);
			if(Items.GetCount()==0){
				CheckNG=true;
			}
		}
	}

	return Ret;
}
QString	CheckDataValidationCheckMinMaxItem::CheckedMessage(void)
{
	const	CheckDataValidationCheckMinMaxThreshold	*RThr=GetThresholdR();
	QString	LibName=GetLayersBase()->GetLibraryName(RThr->LibType,RThr->LibID);

	return QString("設定領域内の設定値がチェックの範囲外:")
		  +LibName;
}

//=====================================================================================

CheckDataValidationProhibiteItemThreshold::CheckDataValidationProhibiteItemThreshold(CheckDataValidationProhibiteItemItem *parent)
:CheckDataValidationThresholdBase(parent)
{
}

bool	CheckDataValidationProhibiteItemThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const CheckDataValidationProhibiteItemThreshold	*s=dynamic_cast<const CheckDataValidationProhibiteItemThreshold *>(&src);
	if(s!=NULL){
		if(CheckDataValidationThresholdBase::IsEqual(src)==true)
			return true;
	}
	return false;
}
void	CheckDataValidationProhibiteItemThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const CheckDataValidationProhibiteItemThreshold	*s=dynamic_cast<const CheckDataValidationProhibiteItemThreshold *>(&src);
	if(s!=NULL){
		CheckDataValidationThresholdBase::CopyFrom(src);
	}
}
bool	CheckDataValidationProhibiteItemThreshold::Save(QIODevice *file)
{
	WORD	Ver=1;

	if(::Save(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Save(file)==false)
		return(false);

	return(true);
}
bool	CheckDataValidationProhibiteItemThreshold::Load(QIODevice *file)
{
	WORD	Ver;
	if(::Load(file,Ver)==false)
		return(false);
	if(CheckDataValidationThresholdBase::Load(file)==false)
		return(false);

	return(true);
}

//-----------------------------------------------------------------
CheckDataValidationProhibiteItemItem::CheckDataValidationProhibiteItemItem(void)
{
}
struct CheckDataValidationProhibiteItemInfo
{
	FlexArea	Area;
	int			LibID;
};

static	bool CheckDataValidationProhibiteItemFunc(void *caller,AlgorithmItemRoot *item)
{
	struct CheckDataValidationProhibiteItemInfo	*VInfo=(struct CheckDataValidationProhibiteItemInfo *)caller;

	if(VInfo->LibID==item->GetLibID()
	&& VInfo->Area.CheckOverlap(&item->GetArea())==true){
		return true;
	}
	return false;
}

ExeResult	CheckDataValidationProhibiteItemItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);
	int		Phase=GetPhaseCode();
	int		Page=GetPage();
	const	CheckDataValidationProhibiteItemThreshold	*RThr=GetThresholdR();
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(RThr->LibType);
	AlgorithmInPageInOnePhase	*APhase=ABase->GetPageDataPhase(Phase);
	if(APhase!=NULL){
		AlgorithmInPageRoot			*APage=APhase->GetPageData(Page);
		if(APage!=NULL){
			AlgorithmItemPointerListContainer Items;
			struct CheckDataValidationProhibiteItemInfo	VInfo;
			VInfo.Area	=GetArea();
			VInfo.LibID	=RThr->LibID;
			APage->EnumItems(&VInfo,Items , CheckDataValidationProhibiteItemFunc);
			if(Items.GetCount()!=0){
				CheckNG=true;
			}
		}
	}

	return Ret;
}
QString	CheckDataValidationProhibiteItemItem::CheckedMessage(void)
{
	const	CheckDataValidationProhibiteItemThreshold	*RThr=GetThresholdR();
	QString	LibName=GetLayersBase()->GetLibraryName(RThr->LibType,RThr->LibID);

	return QString("設定領域内に存在してはならない:")
		  +LibName;
}
