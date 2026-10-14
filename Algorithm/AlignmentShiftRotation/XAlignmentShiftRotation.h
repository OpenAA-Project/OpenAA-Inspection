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
#include "XAlignmentShiftRotationLibrary.h"
#include "XAlignmentShiftRotationCommon.h"
#include "XStandardCommand.h"

#define	AlignmentShiftRotationVersion	1

class	AlignmentShiftRotationItem;
class	AlignmentShiftRotationInPage;
class	AlignmentShiftRotationBase;
class	SetThresholdAlignmentShiftRotationInfo;
class	ExecuteInitialAfterEditInfo;

class	AlignmentShiftRotationThreshold : public AlgorithmThreshold
{
public:
	WORD		Threshold;
	WORD		LineCount;
	short		TargetLayer;
	WORD		LineLen		;
	WORD		SearchDotX	;
	WORD		SearchDotY	;
	DWORD		SparseAngle	;
	RotationRangeContainer	Rotation;

	AlignmentShiftRotationThreshold(AlignmentShiftRotationItem *parent);
	~AlignmentShiftRotationThreshold(void);

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



class   AlignmentShiftRotationItem : public AlgorithmItemPI
{
public:

	class	AlignmentVLine : public NPList<AlignmentVLine>
	{
	public:
		int		AddedS;
		int		AddedSS;
		int		VLineX,VLineY1,VLineY2;
		BYTE	*VDot;
	
		AlignmentVLine(void);
		AlignmentVLine(const AlignmentVLine &srv);
		~AlignmentVLine(void);
	
		AlignmentVLine	&operator=(const AlignmentVLine &src);
		bool	Allocate(ImageBuffer &Images);
		double	Match(int dx ,int dy ,ImageBuffer &Images); 
		void	Move(int Dx ,int Dy);
	
		void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	
	class	AlignmentHLine :public NPList<AlignmentHLine>
	{
	public:
		int		AddedS;
		int		AddedSS;
		int		HLineX1,HLineX2,HLineY;
		BYTE	*HDot;
	
		AlignmentHLine(void);
		AlignmentHLine(const AlignmentHLine &srv);
		~AlignmentHLine(void);
	
		AlignmentHLine	&operator=(const AlignmentHLine &src);
		bool	Allocate(ImageBuffer &Images);
		void	Move(int Dx ,int Dy);
		double	Match(int dx ,int dy ,ImageBuffer &Images); 

		void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	class	VHLineGroup : public NPList<VHLineGroup>
	{
	public:
		int	Layer;
		NPListPack<AlignmentVLine>	VLines;
		NPListPack<AlignmentHLine>	HLines;

		VHLineGroup(void){}
		VHLineGroup(int layer);
		VHLineGroup(const VHLineGroup &src);

		double	Calc(ImageBuffer &ImageBuff,int dx ,int dy);
		bool	Allocate(const FlexArea &area ,ImageBufferListContainer &Images
						,const AlignmentShiftRotationThreshold *RThr);
		VHLineGroup &operator=(const VHLineGroup &src);
		void	Move(int Dx ,int Dy);
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
		double	Match(int dx ,int dy ,ImagePointerContainer &Images); 

		double	CalcVarH(int x1,int x2,int y,ImageBuffer *SrcBuff);
		double	CalcVarV(int x,int y1,int y2,ImageBuffer *SrcBuff);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};

	class   VHLines : public NPList<VHLines>
	{
	public:
		NPListPack<VHLineGroup>		LineGroup;
		double						AngleRadian;
		FlexAreaColorImage			Image;
		double						MasterCx,MasterCy;

		VHLines(void){}
		VHLines(double angleradian);
		VHLines(const VHLines &src);

		VHLines	&operator=(const VHLines &src);
		bool	Allocate(const FlexArea &area ,ImagePointerContainer &Images 
						,const AlignmentShiftRotationThreshold *RThr);
		void	Release(void);
		void	Move(int Dx ,int Dy);
		double	Match(int mx ,int my ,int &rx ,int &ry ,ImagePointerContainer &Images 
						,const AlignmentShiftRotationThreshold *RThr);

		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
		void	DrawImage(QImage &pnt, int movx ,int movy ,double ZoomRate);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};


public:
	AlignmentPacket2D	*AVector;

	NPListPack<VHLines>		VHLinesRotation;

	double		MasterCx,MasterCy;
	int			ShiftByGlobalX,ShiftByGlobalY;
	double		ResultMatch;
	double      ResultDx,ResultDy;	//Calculated position
	double		ResultRotation;


	AlignmentShiftRotationItem(void);
	~AlignmentShiftRotationItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AlignmentShiftRotationItem();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY) override;

    void    MoveTo(int dx ,int dy) override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	 override;
    AlignmentShiftRotationItem &operator=(const AlignmentShiftRotationItem &src);

	const	AlignmentShiftRotationThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AlignmentShiftRotationThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentShiftRotationThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AlignmentShiftRotationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	 override	{	return new AlignmentShiftRotationThreshold(this);	}
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

	void	CopyThresholdOnly(AlignmentShiftRotationItem *src);

public:
	//bool	MakeAreaByManual(void);
	double	GetThreshLevel(ImagePointerContainer &Images ,int dx=0 ,int dy=0);
	double	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget
						,int dx,int dy,int N
						,int DotPerLine,int MaxLines);
	bool	IsImageChanged(void);
};


class   AlignmentShiftRotationInPage : public AlgorithmInPagePI
{
public:
	class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
	{
	public:
		AlignmentShiftRotationItem	*Item;
		AlignmentPacket2DList(void){	Item=NULL;	}
	};
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;

	AlignmentShiftRotationInPage(AlgorithmBase *parent);
	~AlignmentShiftRotationInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType) override;
	AlignmentPacket2D	*AppendAlignmentShiftRotationPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY ,bool FromGlobal);
	bool	GetAlignmentShiftRotation(AlignmentPacket2D &Point);

	void	GenerateAreaWithItemLibFromMask(int Priority ,int ItemLibID);

	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res) override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res) override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info) override;

	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
											;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my) override{}
	void	MoveFromPipe(GeneralPipeInfo &Info);

	void	GetMasterBuffForMakeArea(bool ReCalcBitMask ,ImagePointerContainer &ImageList);

private:
	double	GetThreshLevel(AlgorithmLibrary *Lib,FlexArea &Area ,ImagePointerContainer &Images ,int dx ,int dy);
};

class	AlignmentShiftRotationBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points

	AlignmentShiftRotationBase(LayersBase *Base);
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new AlignmentShiftRotationInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	//virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	QString	GetDataText(void)	 override	{		return QString("AlignmentShiftRotation");	}
	QString	GetDefaultFileName(void)	 override	{	return QString("ConfigAlignmentShiftRotation.dat");		}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	 const	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	 override;

};

//==========================================================================
