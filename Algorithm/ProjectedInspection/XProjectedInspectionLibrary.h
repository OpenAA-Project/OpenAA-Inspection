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
	WORD	NoiseSize;			//�Ǘ��_�폜
	WORD	NoiseSizePinHole;	//�s���z�[���폜
	int32	Priority;

	double	Angle;
	bool	ExcludeDynamicMask;
	int32	TransitWidth;		//���̕��ȏ��̎�NG
	float	OKWidthDiffereceH;	//�Ñ��@���ϋP�x�l���肱�̋P�x�ȉ��ɈÂ��Ȃ�����NG
	float	OKWidthDiffereceL;	//�����@���ϋP�x�l���肱�̋P�x�ȏ��ɖ��邭�Ȃ�����NG
	bool	UseAbsolute;		//�P�x�l�����Βl���g�����H
	bool	CircleMode	;	
	int32	EvenLength;			//���ϒl�Z�o�̃o���h����
	double	PartialSwingAngle;	//�U���p�x(���W�A���j
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