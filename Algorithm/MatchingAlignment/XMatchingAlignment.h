#if	!defined(XMATCHINGALIGNMENT_H)
#define	XMATCHINGALIGNMENT_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"

class	MatchingAlignmentItem;

class	MatchingAlignmentThreshold : public AlgorithmThreshold
{
public:
	double	MatchingRate;
	int		SearchDot;

	MatchingAlignmentThreshold(MatchingAlignmentItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MatchingAlignmentItem : public AlgorithmItemPLI
{
public:
	double	MatchingResult;
	int		Dx,Dy;
	FlexAreaImageListCoeffContainer	MatchingAreas;	//“Á’¥•”•ª‚¾‚¯‚ðŠÜ‚Þ—Ìˆæ
	FlexAreaImageListCoeff			*TopAreas[3];	//ã‹L—Ìˆæ‚Ì‚¤‚¿A‚RŠpŒ`‚ªÅ‘å‚Ì–ÊÏ‚É‚È‚é‚RŒÂ
	FlexAreaImageListCoeff			**AreasList;
	int								AreasListCount;

	MatchingAlignmentItem(void);
	~MatchingAlignmentItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MatchingAlignmentItem();	}
	const	MatchingAlignmentThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MatchingAlignmentThreshold *)GetThresholdBaseReadable(base);	}
	MatchingAlignmentThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MatchingAlignmentThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MatchingAlignmentThreshold(this);	}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	CreateMatchingAreas(double CoverRate=0.2, double PickUpVar=10, int BlockSize=20);
	bool	ExecuteMatch	(ImageBuffer &TargetImage,int cx, int cy ,double &Result);
private:
	double	GetCoefImage(FlexAreaImageListCoeff **AreaList,int AreaCount
						,int SearchDot,ImageBuffer &TargetImage
						,int cx,int cy);
	void	MakeInnerData(void);
};

class   MatchingAlignmentInLayer : public AlgorithmInLayerPLI
{
public:
	MatchingAlignmentInLayer(AlgorithmInPageRoot *parent):AlgorithmInLayerPLI(parent){}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
			{	
				MatchingAlignmentItem	*a=new MatchingAlignmentItem();	
				a->SetParent(this);
				return a;
			}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	ExecuteMatch	(ImageBuffer &TargetImage,int cx, int cy ,double &Result);
};

class   MatchingAlignmentInPage : public AlgorithmInPagePLI
{
public:
	MatchingAlignmentInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new MatchingAlignmentInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	ExeResult	ExecuteMatch	(ImagePointerContainer &TargetImages,int cx, int cy ,double &Result);
};

class	MatchingAlignmentBase : public AlgorithmBase
{
public:
	QColor	ColorNormal;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	MatchingAlignmentBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new MatchingAlignmentInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MatchingAlignment");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMatchingAlignment.dat");	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
class	MatchingAlignmentDrawAttr : public AlgorithmDrawAttr
{
public:
	bool	ModeSpecified;

	MatchingAlignmentDrawAttr(void){	ModeSpecified=false;	}
	MatchingAlignmentDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){	ModeSpecified=false;	}
	MatchingAlignmentDrawAttr(	 QColor ncol ,int ntranparentLevel
								,QColor scol ,int stranparentLevel
								,QColor acol ,int atranparentLevel
								,bool _ModeSpecified)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		ModeSpecified=_ModeSpecified;
	}
};

class	AddMatchingAlignmentAreaPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	double		MatchingRate;
	int			SearchDot;

	AddMatchingAlignmentAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMatchingAlignmentAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CreateSpecifiedPacket : public GUIDirectMessage
{
public:
	double	CoverRate;
	double	PickUpVar;
	int		BlockSize;

	CreateSpecifiedPacket(LayersBase *base):GUIDirectMessage(base){}
	CreateSpecifiedPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
