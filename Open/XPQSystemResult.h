#if	!defined(XPQSystemResult_h)
#define	XPQSystemResult_h

#include <QString>
#include <QPainter>
#include <QColor>
#include "NList.h"
#include "XTypeDef.h"
#include "XParamBase.h"

class	ParamBase;

class	PQSystemXMLDLLBaseRoot : public ParamBase 
{
public:
	QString	ResultXML_HostName;
	int32	ResultXML_Port;
	QString	PathNGImage;

	PQSystemXMLDLLBaseRoot(void);

	virtual	QString	GetDataText(void)		{	return("PQSystemXML Result");	};
	virtual	QString	GetDefaultFileName(void){	return DefaultFileName.isEmpty() ? "PQSystemXML.dat" : DefaultFileName;	}

};

//======================================================================

class	PQResultObject
{
public:
	PQResultObject(void){}

	virtual	void	ShowWindow(QPainter &Pnt, int XSize ,int YSize
								,int movx ,int movy , double ZoomRate);
	virtual	void	Print(QPrinter &Pnt);
};


class	PQGraphNode : public NPList<PQGraphNode>
{
public:
	double	XValue;
	double	YValue;
	QString	Label;

	PQGraphNode(void){	XValue=0.0;	YValue=0.0;	}

	PQGraphNode	&operator=(PQGraphNode &src);
};

class	PQGraphXAxis : public NPList<PQGraphXAxis>
{
public:
	double	XValue;
	QString	Label;

	PQGraphXAxis(void){}
};

class	PQGraphOne : public NPListPack<PQGraphNode> , public NPList<PQGraphOne>
{
public:
	QColor	Color;
	QString	GraphName;
	NPListPack<PQGraphXAxis>	XAxis;

	PQGraphOne(void){}

	PQGraphOne	&operator=(PQGraphOne &src);
};

class	PQGraphData : public PQResultObject ,public NPListPack<PQGraphOne>
{
public:
	QString	GraphName;

	PQGraphData(void);

	PQGraphData	&operator=(PQGraphData &src);
};


#endif
