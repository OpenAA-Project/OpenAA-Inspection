#if	!defined(XMakeDifferencialImage_H)
#define	XMakeDifferencialImage_H


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"

class	MakeDifferencialImageItem;
#define	MakeDifferencialImageVersion	1

class	MakeDifferencialImageThreshold : public AlgorithmThreshold
{
public:

	MakeDifferencialImageThreshold(MakeDifferencialImageItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
    virtual	bool	Load(QIODevice *f)					override{	return true;	}
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MakeDifferencialImageItem : public AlgorithmItemPI
{
public:

	MakeDifferencialImageItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MakeDifferencialImageItem();	}
	const	MakeDifferencialImageThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MakeDifferencialImageThreshold *)GetThresholdBaseReadable(base);	}
	MakeDifferencialImageThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MakeDifferencialImageThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override		 {	return new MakeDifferencialImageThreshold(this);	}
};


class   MakeDifferencialImageInPage : public AlgorithmInPagePI
{
public:
	MakeDifferencialImageInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			MakeDifferencialImageItem	*a=new MakeDifferencialImageItem();	
			a->SetParent(this);
			return a;
		}
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;

private:
	void	MakeDifferencial(ImageBuffer *Dst ,ImageBuffer *Src1,ImageBuffer *Src2);
};

class	MakeDifferencialImageBase : public AlgorithmBase
{
public:
	int		SourcePair1Phase;
	int		SourcePair2Phase;
	int		DestinationPhase;

	MakeDifferencialImageBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MakeDifferencialImageInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MakeDifferencialImage");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMakeDifferencialImage.dat");	}
};

#endif