#if	!defined(XDentLibrary_h)
#define	XDentLibrary_h

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeDent		81

class	DentLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	PickupRL;
	int32	PickupRH;
	int32	PickupGL;
	int32	PickupGH;
	int32	PickupBL;
	int32	PickupBH;
    int32	MinDentSize;
    int32	MaxDentSize;
    int32	MinDentDots;
    int32	MaxDentDots;
    int32	LimitDentSize;
	WORD	NoiseSize;			//孤立点削除
	WORD	NoiseSizePinHole;	//ピンホール削除
    WORD	SpaceToOutline;
	int32	IgnoreAroundHole;

	double	Difference	;
	int		BandWidth	;
	int		MinNGSize;
	int		MaxNGSize;
	double	MaxDiffCoef		;
	int		BaseWaveLength	;
	int		LinesForAverage	;

public:

	DentLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DentLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer *ImageList[]
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeDent(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpDentData);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	DentLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DentLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeDent;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DentLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DentLibrary(GetLibType(),GetLayersBase());	}
};




#endif
