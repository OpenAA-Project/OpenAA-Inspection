#include "XTemplateRule.h"
#include "XGeneralFunc.h"


//===========================================
TemplateRuleInPage::TemplateRuleInPage(AlgorithmBase *parent)
:AlgorithmInPagePITemplate<TemplateRuleItem,TemplateRuleBase>(parent)
{

}
TemplateRuleInPage::~TemplateRuleInPage(void)
{
}
AlgorithmItemRoot	*TemplateRuleInPage::CreateItem(int ItemClassType)
{
	if(ItemClassType==0){
		TemplateRuleItem	*Item=new TemplateRuleItem();
		Item->SetParent(this);
		return Item;
	}
	return NULL;
}

void	TemplateRuleInPage::TransmitDirectly(GUIDirectMessage *packet)
{	
	//CmdAddAreaManual	*CmdAddAreaManualVar=dynamic_cast<CmdAddAreaManual *>(packet);
	//if(CmdAddAreaManualVar!=NULL){
	//	AngleInspectionItem	*item=(AngleInspectionItem *)CreateItem(0);
	//	item->SetArea(CmdAddAreaManualVar->Area);
	//	item->SetManualCreated(true);
	//	AppendItem(item);
	//	return;
	//}
}

//===========================================
TemplateRuleBase::TemplateRuleBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorArea		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive		=Qt::red;
	NegColorArea	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=120;

	SetParam(&ColorArea			, /**/"Color"	,/**/"ColorArea"			,"Color for area");
	SetParam(&ColorSelected		, /**/"Color"	,/**/"ColorSelected"		,"Color for Selected area");
	SetParam(&ColorActive		, /**/"Color"	,/**/"ColorActive"			,"Color for Active area");
	SetParam(&NegColorArea		, /**/"Color"	,/**/"NegColorArea"			,"Color for Negative area");
	SetParam(&NegColorSelected	, /**/"Color"	,/**/"NegColorSelected"		,"Color for Selected Negative area");
	SetParam(&TransparentLevel	, /**/"Color"	,/**/"TransparentLevel"		,"Color for Transparent display level");
}

TemplateRuleBase::~TemplateRuleBase(void)
{
}

AlgorithmDrawAttr	*TemplateRuleBase::CreateDrawAttr(void)
{
	return new TemplateRuleDrawAttr(GetLayersBase()
									,ColorArea		,TransparentLevel
									,ColorSelected	,TransparentLevel
									,ColorActive	,TransparentLevel);
}

void	TemplateRuleBase::TransmitDirectly(GUIDirectMessage *packet)
{
			
}

QString	TemplateRuleBase::GetNameByCurrentLanguage(void)
{
	return QString("ひな形規則");
}
