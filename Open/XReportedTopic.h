#if	!defined(XReportedTopic_h)
#define	XReportedTopic_h

#include <QVariant>
#include <QString>
#include "NListComp.h"
#include "XTypeDef.h"

class	ReportedTopic : public NPListSaveLoad<ReportedTopic>
{
	const	void	*Pointer;
public:
	QString			Title;
	QVariant		Data;
	DirectValueType	DataType;

	ReportedTopic(void){	Pointer=NULL;	DataType=_DT_None;	}
	//ReportedTopic(const QString &title ,const QVariant &d):Title(title),Data(d),Pointer(&d){}
	ReportedTopic(const QString &title ,const char &d);
	ReportedTopic(const QString &title ,const short &d);
	ReportedTopic(const QString &title ,const int32 &d);
	ReportedTopic(const QString &title ,const int64 &d);
	ReportedTopic(const QString &title ,const BYTE &d);
	ReportedTopic(const QString &title ,const WORD &d);
	ReportedTopic(const QString &title ,const DWORD &d);
	ReportedTopic(const QString &title ,const uint64 &d);
	ReportedTopic(const QString &title ,const QString &d);
	ReportedTopic(const QString &title ,const float &d);
	ReportedTopic(const QString &title ,const double &d);

	ReportedTopic	&operator=(const ReportedTopic &src);

	bool	operator==(const ReportedTopic &src)	const;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	QString	ValueString(void);
	void	SetValue(const QVariant &d);
	DirectValueType	GetType(void);

	int64		GetValue(void);
	QString		GetString(void);
	bool		GetBool(void);
	double		GetDouble(void);
};

class	ReportedTopicContainer : public NPListPackSaveLoad<ReportedTopic>
{
public:
	ReportedTopicContainer(void){}

	virtual	ReportedTopic	*Create(void)	override	{	return new ReportedTopic();	}
	//ReportedTopic	*Add(const QString &title ,const QVariant &d);
	ReportedTopic	*Add(const QString &title ,const char &d);
	ReportedTopic	*Add(const QString &title ,const short &d);
	ReportedTopic	*Add(const QString &title ,const int32 &d);
	ReportedTopic	*Add(const QString &title ,const int64 &d);
	ReportedTopic	*Add(const QString &title ,const BYTE &d);
	ReportedTopic	*Add(const QString &title ,const WORD &d);
	ReportedTopic	*Add(const QString &title ,const DWORD &d);
	ReportedTopic	*Add(const QString &title ,const uint64 &d);
	ReportedTopic	*Add(const QString &title ,const QString &d);
	ReportedTopic	*Add(const QString &title ,const float &d);
	ReportedTopic	*Add(const QString &title ,const double &d);

	ReportedTopicContainer &operator=(const ReportedTopicContainer &src);
	ReportedTopicContainer &operator+=(const ReportedTopicContainer &src);

	bool	operator==(const ReportedTopicContainer	&src)	const;
	ReportedTopic	*FindTopic(const QString &title);
};

//-------------------------------------------------------------------------------

class	ReportedTopicsInItem : public NPListSaveLoad<ReportedTopicsInItem>
{
public:
	ReportedTopicContainer	TopicsContainer;
	int32	LibID;
	int32	ItemCount;	//After binding same value of topics

	ReportedTopicsInItem(void){	LibID=-1;	ItemCount=0;	}

	ReportedTopicsInItem	&operator=(const ReportedTopicsInItem &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	ReportedTopicsInItemContainer : public  NPListPackSaveLoad<ReportedTopicsInItem>
{
public:

	ReportedTopicsInItemContainer(void){}

	virtual	ReportedTopicsInItem	*Create(void)	override
										{	return new ReportedTopicsInItem();	}
	ReportedTopicsInItemContainer	&operator=(const ReportedTopicsInItemContainer &src);
	ReportedTopicsInItemContainer	&operator+=(const ReportedTopicsInItemContainer &src);
};


#endif