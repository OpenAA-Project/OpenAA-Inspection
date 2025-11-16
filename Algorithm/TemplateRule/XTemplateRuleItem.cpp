#include "XTemplateRule.h"
#include "XGeneralFunc.h"

PLRuleValue::PLRuleValue(void)
{
	RuleType=RType_Int;
	ChangeMode=0;
	ThresholdID	=-1;
	ValueInt	=0;
	ValueWord	=0;
	ValueByte	=0;
	ValueDouble	=0;
	ValueFloat	=0;
	ValueBool	=true;
}
bool	PLRuleValue::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver	)==false)	return false;

	int32	d=(int32)RuleType;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,ThresholdID	)==false)	return false;
	if(::Save(f,ChangeMode	)==false)	return false;
	if(::Save(f,ValueInt	)==false)	return false;
	if(::Save(f,ValueWord	)==false)	return false;
	if(::Save(f,ValueByte	)==false)	return false;
	if(::Save(f,ValueDouble	)==false)	return false;
	if(::Save(f,ValueFloat	)==false)	return false;
	if(::Save(f,ValueBool	)==false)	return false;
	return true;
}
bool	PLRuleValue::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver	)==false)	return false;

	int32	d;
	if(::Load(f,d			)==false)	return false;
	RuleType	=(_RuleType)d;
	if(::Load(f,ThresholdID	)==false)	return false;
	if(::Load(f,ChangeMode	)==false)	return false;
	if(::Load(f,ValueInt	)==false)	return false;
	if(::Load(f,ValueWord	)==false)	return false;
	if(::Load(f,ValueByte	)==false)	return false;
	if(::Load(f,ValueDouble	)==false)	return false;
	if(::Load(f,ValueFloat	)==false)	return false;
	if(::Load(f,ValueBool	)==false)	return false;
	return true;
}

//==========================================================================

TemplateRuleThreshold::TemplateRuleThreshold(TemplateRuleItem *parent)
	:AlgorithmThreshold(parent)
{
}

void	TemplateRuleThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const TemplateRuleThreshold *s=(const TemplateRuleThreshold *)&src;
}
bool	TemplateRuleThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const TemplateRuleThreshold *d=(const TemplateRuleThreshold *)&src;
	return true;
}
bool	TemplateRuleThreshold::Save(QIODevice *f)
{
	WORD	Ver=TemplateRuleVersion;

	if(::Save(f,Ver)==false)
		return false;

	return true;
}
bool	TemplateRuleThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	return true;
}

//==========================================================================

TemplateRuleItem::TemplateRuleItem(void)
{
	TargetAlgorithmType	=-1;
	TargetLibID			=-1;
}


bool	TemplateRuleItem::Save(QIODevice *f)
{
	int32	Ver=TemplateRuleVersion;

	if(::Save(f,Ver	)==false)	return false;

	if(::Save(f,TargetAlgorithmType	)==false)	return false;
	if(::Save(f,TargetLibID	)	==false)	return false;
	if(TargetItemID.Save(f)		==false)	return false;
	if(::Save(f,TargetItemName	)==false)	return false;
	if(PLRules.Save(f)			==false)	return false;
	return true;
}

bool	TemplateRuleItem::Load(QIODevice *f,LayersBase *LBase)
{
	int32	Ver;

	if(::Load(f,Ver	)==false)	return false;

	if(::Load(f,TargetAlgorithmType	)==false)	return false;
	if(::Load(f,TargetLibID	)	==false)	return false;
	if(TargetItemID.Load(f)		==false)	return false;
	if(::Load(f,TargetItemName	)==false)	return false;
	if(PLRules.Load(f)			==false)	return false;
	return true;
}

ExeResult	TemplateRuleItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	return _ER_true;
}
