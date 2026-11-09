#pragma once

#include <QIODevice>
#include <QPoint>
#include <QString>
#include "XFlexAreaImage.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XEdgeMatchingLibrary.h"
#include "XStandardCommand.h"

#define	EdgeMatchingVersion	1

class	EdgeMatchingItem;
class	EdgeMatchingInPage;
class	EdgeMatchingBase;
class	SetThresholdEdgeMatchingInfo;
class	ExecuteInitialAfterEditInfo;

class	EdgeMatchingThreshold : public AlgorithmThreshold
{
public:
	WORD		SearchDotX;
	WORD		SearchDotY;
	WORD		SearchByPixel;
	double		ThresholdDiv;
	double		ThresholdDirection;
	WORD		FocusRadius	;
	short		Layer;		//-1:Automatic,0~:Layer

	EdgeMatchingThreshold(EdgeMatchingItem *parent);
	~EdgeMatchingThreshold(void);

	virtual	void	RegistHist(void)	override;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


#define	Hist_AlighmentLargeShiftX	1
#define	Hist_AlighmentLargeShiftY	2
#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12



class   EdgeMatchingItem : public AlgorithmItemPI
{
public:

public:
	AlignmentPacket2D	*AVector;
	float		**VMap;
	float		**RMap;
	int			MapXLen,MapYLen;

	double		MasterCx,MasterCy;
	double      ResultDx,ResultDy;	//Calculated position
	double		ResultRotation;


	EdgeMatchingItem(void);
	~EdgeMatchingItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new EdgeMatchingItem();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY) override;

    void    MoveTo(int dx ,int dy) override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	 override;
    EdgeMatchingItem &operator=(const EdgeMatchingItem &src);

	const	EdgeMatchingThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const EdgeMatchingThreshold *)GetThresholdBaseReadable(base);	}
	EdgeMatchingThreshold			*GetThresholdW(LayersBase *base=NULL){	return (EdgeMatchingThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	 override	{	return new EdgeMatchingThreshold(this);	}
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	 override;

    void    Clear(void);
    bool    Save(QIODevice *file) override;
    bool    Load(QIODevice *file,LayersBase *LBase) override;

	//bool    MakeArea(bool ReCalcBitMask=true,ImageBuffer *specialData=NULL);

	int		GetMx(void){	return(ResultDx);	}
	int		GetMy(void){	return(ResultDy);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

	void	CopyThresholdOnly(EdgeMatchingItem *src);

public:
	//bool	MakeAreaByManual(void);
	double	GetThreshLevel(ImagePointerContainer &Images ,int dx=0 ,int dy=0);
	double	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget
						,int dx,int dy,int N
						,int DotPerLine,int MaxLines);
	bool	IsImageChanged(void);
};


class   EdgeMatchingInPage : public AlgorithmInPagePI
{
public:

	EdgeMatchingInPage(AlgorithmBase *parent);
	~EdgeMatchingInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType) override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

private:
};

class	EdgeMatchingBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points

	EdgeMatchingBase(LayersBase *Base);
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new EdgeMatchingInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	//virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	QString	GetDataText(void)	 override	{		return QString("EdgeMatching");	}
	QString	GetDefaultFileName(void)	 override	{	return QString("ConfigEdgeMatching.dat");		}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	 const	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	 override;

};

//==========================================================================
