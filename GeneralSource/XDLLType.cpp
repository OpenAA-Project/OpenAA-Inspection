#include "XTypeDef.h"
#include "XDLLType.h"
#include <QStringList>
#include "Regulus64System.h"

ComponentList::ComponentList(void)
{}
ComponentList::ComponentList(const ComponentList &s)
{
	DLLType	=s.DLLType;
	DLLRoot	=s.DLLRoot;
	DLLName	=s.DLLName;
}
ComponentList::ComponentList(int dllType,const QString &dllRoot, const QString &dllName)
	:DLLType(dllType),DLLRoot(dllRoot),DLLName(dllName){}

ComponentList &ComponentList::operator=(const ComponentList &src)
{
	DLLType	=src.DLLType;
	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
	return *this;
}
bool	ComponentList::operator==(const ComponentList &s)	const
{
	if(DLLType==s.DLLType
	&& DLLRoot==s.DLLRoot
	&& DLLName==s.DLLName){
		return true;
	}
	return false;
}
bool	ComponentList::operator!=(const ComponentList &s)	const
{
	return !operator==(s);
}
QString	ComponentList::GetPropertyString(void)
{
	QString	DLLTypeStr;
	switch(DLLType){
		case DLLAlgorithmMode			:	DLLTypeStr=/**/"Algorithm";		break;
		case DLLCameraMode				:	DLLTypeStr=/**/"Camera";		break;
		case DLLArrangement				:	DLLTypeStr=/**/"Arrangement";	break;
		case DLLResultMode				:	DLLTypeStr=/**/"Result";		break;
		case DLLLightMode				:	DLLTypeStr=/**/"Light";			break;
		case DLLFilterMode				:	DLLTypeStr=/**/"Filter";		break;
		case DLLGeneralStockerMode		:	DLLTypeStr=/**/"GeneralStocker";break;
		case DLLExecuteVisualizerMode	:	DLLTypeStr=/**/"ExecuteVisualizer";	break;
		case DLLPIOMode					:	DLLTypeStr=/**/"PIO";			break;
		case DLLSeqDLLVarMode			:	DLLTypeStr=/**/"SeqDLLVar";		break;
		case DLLPQSystemRunner			:	DLLTypeStr=/**/"PQSystemRunner";break;
		case DLLDFSFilterMode			:	DLLTypeStr=/**/"DFSFilter";		break;
		case DLLPrinterMode				:	DLLTypeStr=/**/"Printer";		break;
		case DLLResultAnalizerMode		:	DLLTypeStr=/**/"ResultAnalizer";break;
		case DLLHaspMode				:	DLLTypeStr=/**/"Hasp";			break;
		case DLLShadowControl			:	DLLTypeStr=/**/"ShadowControl";	break;
		default							:	DLLTypeStr=/**/"";				break;
	}
	if(DLLRoot.isEmpty()==false){
		return DLLTypeStr+QString(/**/"DLL :")+DLLRoot+QString(/**/",")+DLLName;
	}
	return DLLTypeStr+QString(/**/"DLL :")+DLLName;
}

ComponentListContainer::ComponentListContainer(void)
{}

ComponentListContainer	&ComponentListContainer::operator=(const ComponentListContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
ComponentListContainer	&ComponentListContainer::operator+=(const ComponentListContainer &src)
{
	for(ComponentList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ComponentList	*d=new ComponentList(*s);
		AppendList(d);
	}
	return *this;
}
void	ComponentListContainer::Add(int	DLLType,const QString &Root ,const QString &Name)
{
	ComponentList	*d=new ComponentList(DLLType,Root ,Name);
	AppendList(d);
}

void	ComponentListContainer::Merge(const ComponentList &d)
{
	for(ComponentList *s=GetFirst();s!=NULL;s=s->GetNext()){
		if(*s==d){
			return;
		}
	}
	ComponentList	*h=new ComponentList(d);
	AppendList(h);
}

void	ComponentListContainer::GetPropertyStringList(QStringList &Str)
{
	for(ComponentList *s=GetFirst();s!=NULL;s=s->GetNext()){
		Str.append(s->GetPropertyString());
	}
}

//===========================================================
DetailResultValueList::DetailResultValueList(void)
{
	ResultType=_ResultTypeNone;
}
DetailResultValueList::DetailResultValueList(const DetailResultValueList &src)
{
	ResultType			=src.ResultType			;
	MessageString		=src.MessageString		;
	ResultValueBool		=src.ResultValueBool	;
	ResultValueInt		=src.ResultValueInt		;
	ResultValueULong	=src.ResultValueULong	;
	ResultValueDouble	=src.ResultValueDouble	;
	ResultValueString	=src.ResultValueString	;
}

void	DetailResultValueList::SetResultValue(bool b)			{	ResultValueBool=b;	ResultType=_ResultTypeBool;		}
void	DetailResultValueList::SetResultValue(int d)			{	ResultValueInt=d;	ResultType=_ResultTypeInt;		}
void	DetailResultValueList::SetResultValue(unsigned long d)	{	ResultValueULong=d;	ResultType=_ResultTypeULong;		}
void	DetailResultValueList::SetResultValue(double d)			{	ResultValueDouble=d;ResultType=_ResultTypeDouble;	}
void	DetailResultValueList::SetResultValue(const QString &s)	{	ResultValueString=s;ResultType=_ResultTypeQString;	}

DetailResultValueList	&DetailResultValueList::operator=(const DetailResultValueList &src)
{
	ResultType			=src.ResultType			;
	MessageString		=src.MessageString		;
	ResultValueBool		=src.ResultValueBool	;
	ResultValueInt		=src.ResultValueInt		;
	ResultValueULong	=src.ResultValueULong	;
	ResultValueDouble	=src.ResultValueDouble	;
	ResultValueString	=src.ResultValueString	;
	return *this;
}
QString	DetailResultValueList::GetResultValue(void)
{
	switch(ResultType){
		case _ResultTypeNone	:	return /**/"";
		case _ResultTypeBool	:	return QString((ResultValueBool==true)?/**/"true":/**/"false");
		case _ResultTypeInt		:	return QString::number(ResultValueInt);
		case _ResultTypeULong	:	return QString::number(ResultValueULong);
		case _ResultTypeDouble	:	return QString::number(ResultValueDouble,'f',3);
		case _ResultTypeQString	:	return ResultValueString;
	}
}

DetailResultInfoList::DetailResultInfoList(void)
{
}
DetailResultInfoList::DetailResultInfoList(const QString &s)
{
	MessageString=s;
}

DetailResultInfoList::DetailResultInfoList(const DetailResultInfoList &src)
{
	MessageString		=src.MessageString		;
	NGColor				=src.NGColor			;
	for(DetailResultValueList *L=src.ResultValueContainer.GetFirst();L!=NULL;L=L->GetNext()){
		DetailResultValueList	*d=new DetailResultValueList(*L);
		ResultValueContainer.AppendList(d);
	}
}

DetailResultInfoList	&DetailResultInfoList::operator=(const DetailResultInfoList &src)
{
	MessageString		=src.MessageString		;
	NGColor				=src.NGColor			;
	for(DetailResultValueList *L=src.ResultValueContainer.GetFirst();L!=NULL;L=L->GetNext()){
		DetailResultValueList	*d=new DetailResultValueList(*L);
		ResultValueContainer.AppendList(d);
	}

	return *this;
}
void	DetailResultInfoList::Add(DetailResultValueList *L)
{
	ResultValueContainer.AppendList(L);
}
void	DetailResultInfoList::Add(const QString &msg ,bool b)
{
	DetailResultValueList	*L=new DetailResultValueList();
	L->SetMessage(msg);
	L->SetResultValue(b);
	ResultValueContainer.AppendList(L);
}
void	DetailResultInfoList::Add(const QString &msg ,int d)
{
	DetailResultValueList	*L=new DetailResultValueList();
	L->SetMessage(msg);
	L->SetResultValue(d);
	ResultValueContainer.AppendList(L);
}
void	DetailResultInfoList::Add(const QString &msg ,unsigned long d)
{
	DetailResultValueList	*L=new DetailResultValueList();
	L->SetMessage(msg);
	L->SetResultValue(d);
	ResultValueContainer.AppendList(L);
}
void	DetailResultInfoList::Add(const QString &msg ,double d)
{
	DetailResultValueList	*L=new DetailResultValueList();
	L->SetMessage(msg);
	L->SetResultValue(d);
	ResultValueContainer.AppendList(L);
}
void	DetailResultInfoList::Add(const QString &msg ,const QString &s)
{
	DetailResultValueList	*L=new DetailResultValueList();
	L->SetMessage(msg);
	L->SetResultValue(s);
	ResultValueContainer.AppendList(L);
}
QString	DetailResultInfoList::GetInfoString(void)
{
	QString	s=MessageString;
	for(DetailResultValueList *L=ResultValueContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->MessageString.isEmpty()==false){
			s+=L->MessageString+QString(/**/":")+L->GetResultValue();
		}
		else{
			s+=L->GetResultValue();
		}
	}
	return s;
}
QString	DetailResultInfoList::GetMessageOnly(void)
{
	QString	s=MessageString;
	for(DetailResultValueList *L=ResultValueContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->MessageString.isEmpty()==false){
			s+=L->MessageString;
		}
	}
	return s;
}
void	DetailResultInfoList::GetInfoStringList(QStringList &RetList)
{
	if(MessageString.isEmpty()==false){
		RetList.append(MessageString);
	}
	for(DetailResultValueList *L=ResultValueContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->MessageString.isEmpty()==false){
			RetList.append(L->MessageString+QString(/**/":")+L->GetResultValue());
		}
		else{
			RetList.append(L->GetResultValue());
		}
	}
}

DetailResultInfoListContainer::DetailResultInfoListContainer(void)
{
	Data.LibType=-1;
	Data.Phase	=-1;
	Data.Page	=-1;
	Data.Layer	=-1;
	Data.ItemID	=-1;
	Data.LibID	=-1;
}

DetailResultInfoListContainer	&DetailResultInfoListContainer::operator=(const DetailResultInfoListContainer &src)
{
	RemoveAll();
	Data=src.Data;
	return operator+=(src);
}
DetailResultInfoListContainer	&DetailResultInfoListContainer::operator+=(const DetailResultInfoListContainer &src)
{
	for(DetailResultInfoList *s=src.NPListPack<DetailResultInfoList>::GetFirst();s!=NULL;s=s->GetNext()){
		DetailResultInfoList	*d=new DetailResultInfoList(*s);
		AppendList(d);
	}
	return *this;
}

void	DetailResultInfoListContainer::GetInfoStringList(QStringList &RetList)
{
	for(DetailResultInfoList *s=NPListPack<DetailResultInfoList>::GetFirst();s!=NULL;s=s->GetNext()){
		s->GetInfoStringList(RetList);
	}
}