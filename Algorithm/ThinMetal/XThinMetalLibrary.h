#if	!defined(XThinMetalLibrary_H)
#define	XThinMetalLibrary_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeThinMetal		47



class	ThinMetalLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
//生成データ
#pragma	pack(push,1)
	int32					PickupL;
	int32					PickupH;
    int32					MinSize;
    int32					MaxSize;
    int32					MinDots;
    int32					MaxDots;
    int32					LimitSize;
#pragma	pack(pop)

#pragma	pack(push,1)
	WORD		NoiseSize;			//孤立点削除
	WORD		NoiseSizePinHole;	//ピンホール削除
    short		SpaceToOutline;
    WORD		Priority;
#pragma	pack(pop)

//検査データ
#pragma	pack(push,1)
	WORD	BrightWidthL;	//暗側輝度幅
	WORD	BrightWidthH;	//明側輝度幅
	DWORD	OKDotL;			//暗側ＯＫドット数
	DWORD	OKDotH;			//明側ＯＫドット数
	WORD	OKLengthL;		//暗側で、この長さ以下の時ＯＫ
	WORD	OKLengthH;		//明側で、この長さ以下の時ＯＫ
	DWORD	MaxNGDotL;		//暗側最大ＮＧドット数
	DWORD	MaxNGDotH;		//明側最大ＮＧドット数
	BYTE	ShrinkDot;
	BYTE	EnlargeDot;
#pragma	pack(pop)

public:

	ThinMetalLibrary(int LibType,LayersBase *Base);
	virtual	~ThinMetalLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	ThinMetalLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int page
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	Make(
			 BYTE **CurrentMap,BYTE **OcupyMap
			 ,int page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpVIAData);

private:
};

class	ThinMetalLibraryContainer : public AlgorithmLibraryContainer
{
public:
	ThinMetalLibraryContainer(LayersBase *base);
	virtual	~ThinMetalLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeThinMetal;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "ThinMetal Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new ThinMetalLibrary(GetLibType(),GetLayersBase());	}
};



#endif
