/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AlignmentLarge\XAlignmentLargeLibrary.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XAlignmentLargeLibrary_h)
#define	XAlignmentLargeLibrary_h


#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XTypeDef.h"
#include "XAlgorithmLibrary.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"

#define	DefLibTypeAlignmentLarge		33

class	AlignmentLargeLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	bool		GenerateArea;		//Generate by Pipe
	bool		GenerateMark;		//Generate by Pipe
	bool		GenerateBitBuff;	//Generate by Pipe

	int32		MinGenerationAreaDots;
	int32		MinGenerationMarkDots;

	enum _EnumPriority{
		_PriorityHigh		=1
		,_PriorityMiddle	=2
		,_PriorityLow		=3
		,_PriorityGlobal	=4
	}Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;	//For priority 1 and 2
	WORD		MoveDotY2;
	WORD		SearchAround;
	int			UsageGlobal;
	int			MaxCountHLine;
	int			MaxCountVLine;
	bool		JudgeWithBrDif;
	bool		CharacterMode;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness
public:

	AlignmentLargeLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AlignmentLargeLibrary	&operator=(const AlgorithmLibrary &src)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
private:

};

class	AlignmentLargeLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AlignmentLargeLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)					override{	return DefLibTypeAlignmentLarge;	}
	virtual	const char	*GetLibTypeName(void)		override{	return "AlignmentLargeLibrary";	}
	virtual	AlgorithmLibrary	*CreateNew(void)	override{	return new AlignmentLargeLibrary(GetLibType(),GetLayersBase());	}
};



#endif