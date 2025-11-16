#include "XTypeDef.h"
#include "XReportedTopic.h"
#include "XGeneralFunc.h"


ReportedTopic::ReportedTopic(const QString &title ,const char &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_char){}
ReportedTopic::ReportedTopic(const QString &title ,const short &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_short){}
ReportedTopic::ReportedTopic(const QString &title ,const int32 &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_int32){}
ReportedTopic::ReportedTopic(const QString &title ,const int64 &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_int64){}
ReportedTopic::ReportedTopic(const QString &title ,const BYTE &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_byte){}
ReportedTopic::ReportedTopic(const QString &title ,const WORD &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_ushort){}
ReportedTopic::ReportedTopic(const QString &title ,const DWORD &d)
	:Pointer(&d),Title(title),Data((uint32)d),DataType(_DT_uint32){}
ReportedTopic::ReportedTopic(const QString &title ,const uint64 &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_uint64){}
ReportedTopic::ReportedTopic(const QString &title ,const QString &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_QString){}
ReportedTopic::ReportedTopic(const QString &title ,const float &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_float){}
ReportedTopic::ReportedTopic(const QString &title ,const double &d)
	:Pointer(&d),Title(title),Data(d),DataType(_DT_double){}

ReportedTopic	&ReportedTopic::operator=(const ReportedTopic &src)
{
	Title	=src.Title;
	Data	=src.Data;
	return *this;
}
bool	ReportedTopic::Save(QIODevice *f)
{
	if(::Save(f,Title)==false){
		return false;
	}
	if(::Save(f,Data)==false){
		return false;
	}
	return true;
}
bool	ReportedTopic::Load(QIODevice *f)
{
	if(::Load(f,Title)==false){
		return false;
	}
	if(::Load(f,Data)==false){
		return false;
	}
	return true;
}
bool	ReportedTopic::operator==(const ReportedTopic &src)	const
{
	if(Title==src.Title && Data==src.Data)
		return true;
	return false;
}

DirectValueType	ReportedTopic::GetType(void)
{
	return DataType;
}
	
QString	ReportedTopic::ValueString(void)
{
	if(Data.type()==QVariant::Double){
		return QString::number(*((double *)Pointer),'f',2);
	}
	else
	if(Data.type()==QVariant::Int){
		return QString::number(*((int *)Pointer));
	}
	else
	if(Data.type()==QVariant::UInt){
		return QString::number(*((uint *)Pointer));
	}
	else
	if(Data.type()==QVariant::Bool){
		return (*((bool *)Pointer)==true)?/**/"true":/**/"false";
	}
	return Data.toString();
}

int64		ReportedTopic::GetValue(void)
{
	switch(DataType){
	case _DT_None			:	break;
	case _DT_bool			:	break;
	case _DT_byte			:	return *((BYTE *)Pointer);
	case _DT_char			:	return *((char *)Pointer);
	case _DT_short			:	return *((short *)Pointer);
	case _DT_ushort			:	return *((ushort *)Pointer);
	case _DT_int			:	return *((int *)Pointer);
	case _DT_int32			:	return *((int32 *)Pointer);
	case _DT_uint32			:	return *((uint32 *)Pointer);
	case _DT_int64			:	return *((int64 *)Pointer);
	case _DT_uint64			:	return *((uint64 *)Pointer);
	case _DT_QString		:	break;
	case _DT_double			:	return (int64)*((double *)Pointer);
	case _DT_longdouble		:	return (int64)*((long double *)Pointer);
	case _DT_float			:	return (int64)*((float *)Pointer);

	case _DT_enum			:
	case _DT_struct			:
	case _DT_QColor			:
	case _DT_QFont			:
	case _DT_QStringList	:
	case _DT_WidgetList		:
	case _DT_TunableList	:
	case _DT_FileName		:
	case _DT_PathName		:
	case _DT_FileNames		:
	case _DT_QImage			:
	case _DT_QByteArray		:
	case _DT_IntList		:
								break;
	}
	return 0;
}
double		ReportedTopic::GetDouble(void)
{
	switch(DataType){
	case _DT_None			:	break;
	case _DT_bool			:	break;
	case _DT_byte			:	break;
	case _DT_char			:	break;
	case _DT_short			:	break;
	case _DT_ushort			:	break;
	case _DT_int			:	break;
	case _DT_int32			:	break;
	case _DT_uint32			:	break;
	case _DT_int64			:	break;
	case _DT_uint64			:	break;
	case _DT_QString		:	break;
	case _DT_double			:	return *((double *)Pointer);
	case _DT_longdouble		:	return *((long double *)Pointer);
	case _DT_float			:	return *((float *)Pointer);

	case _DT_enum			:
	case _DT_struct			:
	case _DT_QColor			:
	case _DT_QFont			:
	case _DT_QStringList	:
	case _DT_WidgetList		:
	case _DT_TunableList	:
	case _DT_FileName		:
	case _DT_PathName		:
	case _DT_FileNames		:
	case _DT_QImage			:
	case _DT_QByteArray		:
	case _DT_IntList		:
								break;
	}
	return 0;
}

QString		ReportedTopic::GetString(void)
{
	switch(DataType){
	case _DT_None			:	break;
	case _DT_bool			:	break;
	case _DT_byte			:	break;
	case _DT_char			:	break;
	case _DT_short			:	break;
	case _DT_ushort			:	break;
	case _DT_int			:	break;
	case _DT_int32			:	break;
	case _DT_uint32			:	break;
	case _DT_int64			:	break;
	case _DT_uint64			:	break;
	case _DT_QString		:	return *((QString *)Pointer);
	case _DT_double			:	break;
	case _DT_longdouble		:	break;
	case _DT_float			:	break;

	case _DT_enum			:
	case _DT_struct			:
	case _DT_QColor			:
	case _DT_QFont			:
	case _DT_QStringList	:
	case _DT_WidgetList		:
	case _DT_TunableList	:
	case _DT_FileName		:
	case _DT_PathName		:
	case _DT_FileNames		:
	case _DT_QImage			:
	case _DT_QByteArray		:
	case _DT_IntList		:
								break;
	}
	return /**/"";
}
bool		ReportedTopic::GetBool(void)
{
	switch(DataType){
	case _DT_None			:	break;
	case _DT_bool			:	return *((bool *)Pointer);;
	case _DT_byte			:	break;
	case _DT_char			:	break;
	case _DT_short			:	break;
	case _DT_ushort			:	break;
	case _DT_int			:	break;
	case _DT_int32			:	break;
	case _DT_uint32			:	break;
	case _DT_int64			:	break;
	case _DT_uint64			:	break;
	case _DT_QString		:	break;
	case _DT_double			:	break;
	case _DT_longdouble		:	break;
	case _DT_float			:	break;

	case _DT_enum			:
	case _DT_struct			:
	case _DT_QColor			:
	case _DT_QFont			:
	case _DT_QStringList	:
	case _DT_WidgetList		:
	case _DT_TunableList	:
	case _DT_FileName		:
	case _DT_PathName		:
	case _DT_FileNames		:
	case _DT_QImage			:
	case _DT_QByteArray		:
	case _DT_IntList		:
								break;
	}
	return 0;
}


void	ReportedTopic::SetValue(const QVariant &d)
{
	switch(DataType){
	case _DT_None		:	return;
	case _DT_bool		:	*((bool *)Pointer)		=d.toBool();	break;
	case _DT_byte		:	*((BYTE *)Pointer)		=d.toUInt();	break;	
	case _DT_char		:	*((char *)Pointer)		=d.toInt();	break;	
	case _DT_short		:	*((short *)Pointer)		=d.toInt();	break;
	case _DT_ushort		:	*((ushort *)Pointer)	=d.toUInt();	break;
	case _DT_int		:	*((int *)Pointer)		=d.toUInt();	break;
	case _DT_int32		:	*((int32 *)Pointer)		=d.toInt();	break;
	case _DT_uint32		:	*((uint32 *)Pointer)	=d.toUInt();	break;
	case _DT_int64		:	*((int64 *)Pointer)		=d.toInt();	break;
	case _DT_uint64		:	*((uint64 *)Pointer)	=d.toUInt();	break;
	case _DT_QString	:	*((QString *)Pointer)	=d.toString();	break;
	case _DT_double		:	*((double *)Pointer)	=d.toDouble();	break;
	case _DT_longdouble	:	*((long double *)Pointer)=d.toDouble();	break;
	case _DT_float		:	*((float *)Pointer)		=d.toDouble();	break;
	}
}

//=====================================================================

ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const char &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}

ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const short &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const int32 &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const int64 &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const unsigned char &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const WORD &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const DWORD &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const uint64 &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const QString &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const float &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}
ReportedTopic	*ReportedTopicContainer::Add(const QString &title ,const double &d)
{
	ReportedTopic	*r=new ReportedTopic(title ,d);
	AppendList(r);
	return r;
}

ReportedTopicContainer &ReportedTopicContainer::operator=(const ReportedTopicContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
ReportedTopicContainer &ReportedTopicContainer::operator+=(const ReportedTopicContainer &src)
{
	for(ReportedTopic *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReportedTopic	*n=new ReportedTopic();
		*n=*a;
		AppendList(n);
	}
	return *this;
}
bool	ReportedTopicContainer::operator==(const ReportedTopicContainer	&src)	const
{
	ReportedTopic *a;
	ReportedTopic *b;
	for(a=src.GetFirst(),b=GetFirst();a!=NULL && b!=NULL;a=a->GetNext(),b=b->GetNext()){
		if(*a==*b)
			continue;
		return false;
	}
	if(a!=NULL || b!=NULL)
		return false;
	return true;
}
	
ReportedTopic	*ReportedTopicContainer::FindTopic(const QString &title)
{
	for(ReportedTopic *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Title==title){
			return a;
		}
	}
	return NULL;
}

bool	ReportedTopicsInItem::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false){
		return false;
	}
	if(::Save(f,ItemCount)==false){
		return false;
	}
	if(TopicsContainer.Save(f)==false)
		return false;

	return true;
}
	
bool	ReportedTopicsInItem::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false){
		return false;
	}
	if(::Load(f,ItemCount)==false){
		return false;
	}
	if(TopicsContainer.Load(f)==false)
		return false;

	return true;
}
ReportedTopicsInItem	&ReportedTopicsInItem::operator=(const ReportedTopicsInItem &src)
{
	TopicsContainer	=src.TopicsContainer;
	LibID=src.LibID;
	ItemCount=src.ItemCount;
	return *this;
}
ReportedTopicsInItemContainer	&ReportedTopicsInItemContainer::operator=(const ReportedTopicsInItemContainer &src)
{
	RemoveAll();
	return operator+=(src);
}
ReportedTopicsInItemContainer	&ReportedTopicsInItemContainer::operator+=(const ReportedTopicsInItemContainer &src)
{
	for(ReportedTopicsInItem *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReportedTopicsInItem	*n=Create();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		a->Save(&Buff);
		Buff.seek(0);
		n->Load(&Buff);
		AppendList(n);
	}
	return *this;
}
