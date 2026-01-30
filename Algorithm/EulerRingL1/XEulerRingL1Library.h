/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#if	!defined(XEulerRingL1LIBRARY_H)
#define	XEulerRingL1LIBRARY_H


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageLayerItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeEulerRingL1		69

class	EulerRingL1Library : public AlgorithmLibrary , public ServiceForLayers
{
public:
//For generation
	bool	LockFirst;		
	int32	PickupL;
	int32	PickupH;
    int32	MinBlockSize;
    int32	MaxBlockSize;
    int32	MinBlockDots;
    int32	MaxBlockDots;

	WORD	NoiseSize;			//�Ǘ��_�폜
	WORD	NoiseSizePinHole;	//�s���z�[���폜
	int32	SpaceToOutline;		//Plus:Shrink Plus:Expand
    WORD	Priority;
	WORD	OutlineGeneration;	//�֊s�ɐ��������h�b�g��	1000�ȏ��Œʏ퐶��
	WORD	ExpandedDotToPad;	//Expanded dot from hole to pad

//For inspection
	double	StandardHoleDiameter;
	double	MerginForRing;

	struct{
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeMakeDynamicMask:1;
		bool	ModeEnableHoleCheck:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeEnableOpenRingCheck:1;
		bool	ModeEnableInRound:1;			//When hole is round in generation , it's TRUE
		int		Dummy:25;
	}PointMove;

	short		DarkWidth;		//For ring brightness
	short		LightWidth;
	int32		MinHoleDiameter;
	int32		MaxHoleDiameter;
	double		MaxShiftHole;
	int8		ConnectLen;		//�m�f�ڑ�����
	int32		ExpandForDynamicMask;

    WORD		AdjustBlack;	//For ring brightness
    WORD		AdjustWhite; 
	WORD		SearchDot;
	short		HoleBrightnessAsReference;

public:

	EulerRingL1Library(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	EulerRingL1Library	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(int localpage
						,ImageBuffer &IBuff 
						,const BYTE **MaskBitmap
						,BYTE **BmpPoint 
						,BYTE **OcupyMap
						,int XByte ,int XLen ,int YLen
						,int OmitZoneDot);
	void	MakeBlock(int localpage
			,BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,int tExpandedDotToPad);
	void	MakeBlockOnly(int localpage
			,BYTE **CurrentMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &TmpBlockData
			,double RoundRateInHole);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	EulerRingL1LibraryContainer : public AlgorithmLibraryContainer
{
public:
	EulerRingL1LibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeEulerRingL1;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "EulerRingL1Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new EulerRingL1Library(GetLibType(),GetLayersBase());	}
};


#endif