#if	!defined(XExecuteBatch_H)
#define	XExecuteBatch_H

#include <QString>
#include "NListComp.h"
#include "XDataInLayer.h"
#include <QTextStream>

class	BatchContainer;
class	BatchLine : public NPListSaveLoad<BatchLine>
{
	BatchContainer	*Parent;
public:
	enum	__DLLType
	{
		 _DLL_GUI			=1
		,_DLL_Algorithm		=2
		,_DLL_Result		=3
	}DLLType;

	QString		DLLRoot;
	QString		DLLName;
	QString		CommandStr;
	QStringList	ArgValues;

	BatchLine(BatchContainer *parent):Parent(parent){	DLLType=_DLL_GUI;	}

	bool	ExecuteLine(LayersBase *base);
	BatchLine	&operator=(BatchLine &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	SaveText(QTextStream &Txt);
	virtual	bool	LoadText(QTextStream &Txt);

	void	ReplaceParam(const QString &Keyword ,const QString &ReplacedStr);
};

class	BatchContainer : public NPListPackSaveLoad<BatchLine>
{
public:
	QStringList	ParamFromArg;	//@xx

	BatchContainer(void){}

	virtual	BatchLine	*Create(void)	{	return new BatchLine(this);	}

	virtual	bool	SaveText(QIODevice *f);
	virtual	bool	LoadText(QIODevice *f);
	virtual	bool	AppendText(QIODevice *f);

	void	ReplaceParam(const QString &Keyword ,const QString &ReplacedStr); 
};


#endif