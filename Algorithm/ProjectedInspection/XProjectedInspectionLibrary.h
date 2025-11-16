#if	!defined(XProjectedInspectionLibrary_H)
#define	XProjectedInspectionLibrary_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeProjectedInspection		49



class	ProjectedInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	PickupL;
	int32	PickupH;
    int32	MinBlockSize;
    int32	MaxBlockSize;
    int32	MinBlockDots;
    int32	MaxBlockDots;
    int32	LimitBlockSize;
	WORD	NoiseSize;			//孤立点削除
	WORD	NoiseSizePinHole;	//ピンホール削除
	int32	Priority;

	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;		//この幅以上の時NG
	float	OKWidthDiffereceH;	//暗側　平均輝度値よりこの輝度以下に暗くなったらNG
	float	OKWidthDiffereceL;	//明側　平均輝度値よりこの輝度以上に明るくなったらNG
	bool	UseAbsolute;		//輝度値を絶対値を使うか？
	bool	CircleMode	;	
	int32	EvenLength;			//平均値算出のバンド長さ
	double	PartialSwingAngle;	//振り角度(ラジアン）
public:

	ProjectedInspectionLibrary(int LibType,LayersBase *Base);
	virtual	~ProjectedInspectionLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap,const BYTE **LastOcupyMap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int Page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

	virtual	ProjectedInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;

private:
};

class	ProjectedInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ProjectedInspectionLibraryContainer(LayersBase *base);
	virtual	~ProjectedInspectionLibraryContainer(void);

	virtual	int	GetLibType(void)					override{	return DefLibTypeProjectedInspection;	}
	virtual	const char	*GetLibTypeName(void)		override{	return "ProjectedInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)	override{	return new ProjectedInspectionLibrary(GetLibType(),GetLayersBase());	}
};



#endif
