#if	!defined(XParamCustomized_h)
#define	XParamCustomized_h

#include "XParamBase.h"
#include "XServiceForLayers.h"
#include "XAllocationLibByColor.h"
#include "XLibraryUsage.h"
#include "XGUIPacketForDLL.h"

#define	CountOfLevel	10
#define	CountOfSides	2

class	ParamLevel
{
public:
	int		LevelID;
	QString	LevelName;

	ParamLevel(void){	LevelID=0;	}

	ParamLevel	&operator=(const ParamLevel &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	ParamLevel	&ParamLevel::operator=(const ParamLevel &src)
{
	LevelID		=src.LevelID;
	LevelName	=src.LevelName;
	return *this;
}

class	ParamCustomized : public ParamBase ,public ServiceForLayers 
{
public:
	int32	MaskAutoPickupRL;
	int32	MaskAutoPickupRH;
	int32	MaskAutoPickupGL;
	int32	MaskAutoPickupGH;
	int32	MaskAutoPickupBL;
	int32	MaskAutoPickupBH;
	int32	MaskAutoLayer;
	int32	MaskAutoMinPickupSize;
	int32	MaskAutoMaxPickupSize;
	int32	MaskAutoMinPickupDots;
	int32	MaskAutoMaxPickupDots;
	int32	MaskAutoErosion;
	int32	MaskAutoOutsideXPos;
	int32	MaskAutoOutsideYPos;
	int32	MaskAutoExcludeLeftX	;
	int32	MaskAutoExcludeRightX	;
	int32	MaskNoisePinhole ;
	int32	MaskNoiseSmallDot;

	int32	Mask2AutoPickupRL;
	int32	Mask2AutoPickupRH;
	int32	Mask2AutoPickupGL;
	int32	Mask2AutoPickupGH;
	int32	Mask2AutoPickupBL;
	int32	Mask2AutoPickupBH;
	int32	Mask2AutoMinPickupSize;
	int32	Mask2AutoMaxPickupSize;
	int32	Mask2AutoMinPickupDots;
	int32	Mask2AutoMaxPickupDots;
	int32	Mask2AutoErosion;
	int32	Mask2AutoOutsideXPos;
	int32	Mask2AutoOutsideYPos;
	int32	Mask2NoisePinhole ;
	int32	Mask2NoiseSmallDot;

	int32	Mask3AutoPickupRL;
	int32	Mask3AutoPickupRH;
	int32	Mask3AutoPickupGL;
	int32	Mask3AutoPickupGH;
	int32	Mask3AutoPickupBL;
	int32	Mask3AutoPickupBH;
	int32	Mask3AutoMinPickupSize;
	int32	Mask3AutoMaxPickupSize;
	int32	Mask3AutoMinPickupDots;
	int32	Mask3AutoMaxPickupDots;
	int32	Mask3AutoErosion;
	int32	Mask3AutoOutsideXPos;
	int32	Mask3AutoOutsideYPos;
	int32	Mask3NoisePinhole ;
	int32	Mask3NoiseSmallDot;

	int32	Mask4AutoPickupRL;
	int32	Mask4AutoPickupRH;
	int32	Mask4AutoPickupGL;
	int32	Mask4AutoPickupGH;
	int32	Mask4AutoPickupBL;
	int32	Mask4AutoPickupBH;
	int32	Mask4AutoMinPickupSize;
	int32	Mask4AutoMaxPickupSize;
	int32	Mask4AutoMinPickupDots;
	int32	Mask4AutoMaxPickupDots;
	int32	Mask4AutoErosion;
	int32	Mask4AutoOutsideXPos;
	int32	Mask4AutoOutsideYPos;
	int32	Mask4NoisePinhole ;
	int32	Mask4NoiseSmallDot;

	int32	DotColorMatchLibPattern1;
	int32	DotColorMatchLibPattern2;
	int32	DotColorMatchLibPattern3;
	int32	DotColorMatchLibPattern4;
	int32	DotColorMatchLibPattern5;
	int32	DotColorMatchLibFlat1;
	int32	DotColorMatchLibFlat2;
	int32	DotColorMatchLibFlat3;
	int32	DotColorMatchLibFlat4;
	int32	DotColorMatchLibFlat5;
	int32	DotColorMatchCADLib1;
	int32	DotColorMatchCADLib2;
	int32	DotColorMatchCADLib3;
	int32	DotColorMatchCADLib4;
	int32	DotColorMatchCADLib5;
	int32	DotColorMatchBladeLib1;
	int32	DotColorMatchBladeLib2;
	int32	DotColorMatchBladeLib3;
	int32	DotColorMatchBladeLib4;
	int32	DotColorMatchBladeLib5;
	int32	DotColorMatchRedInspection1;
	int32	DotColorMatchRedInspection2;
	int32	DotColorMatchRedInspection3;
	int32	DotColorMatchRedInspection4;
	int32	DotColorMatchRedInspection5;

	int32	DotColorMatchMonoInspection1;
	int32	DotColorMatchMonoInspection2;
	int32	DotColorMatchMonoInspection3;
	int32	DotColorMatchMonoInspection4;
	int32	DotColorMatchMonoInspection5;
	int32	DotColorMatchMonoFlat1;
	int32	DotColorMatchMonoFlat2;
	int32	DotColorMatchMonoFlat3;
	int32	DotColorMatchMonoFlat4;
	int32	DotColorMatchMonoFlat5;

	bool	GeneratePartialAlignment;
	int32	AlignmentLib1;
	int32	AlignmentLib2;
	int32	AlignmentLib3;
	int32	AlignmentLib4;
	int32	AlignmentLib5;
	int32	AlignmentLib6;
	int32	AlignmentLib7;
	int32	AlignmentLib8;
	int32	AlignmntAreaErosion;
	int32	AlignmntPointSize;
	int32	AlignmntSearchAreaDot	;
	int32	AlignmntSearchAreaDot2	;
	int32	AlignmntSearchAreaDotY	;
	int32	AlignmntSearchAreaDot2Y	;
	int32	AlignmntSearchAreaDotMiddle	;
	int32	AlignmntSearchAreaDotMiddleY;
	int32	AlignmntGeneratedLayer;
	bool	AlignmntJudgeWithBrDif;
	bool	AlignmentUseCharacterMode;

	int32	BladeBottomPickupRL;
	int32	BladeBottomPickupRH;
	int32	BladeBottomPickupGL;
	int32	BladeBottomPickupGH;
	int32	BladeBottomPickupBL;
	int32	BladeBottomPickupBH;
	int32	BladeBottomLeft ;
	int32	BladeBottomRight;
	int32	BladeTopPickupRL;
	int32	BladeTopPickupRH;
	int32	BladeTopPickupGL;
	int32	BladeTopPickupGH;
	int32	BladeTopPickupBL;
	int32	BladeTopPickupBH;
	int32	BladeTopLeft;
	int32	BladeTopRight;
	QString	BradeDefFileNameTop		;
	QString	BradeDefFileNameBottom	;
	int32	MaskLibIDForBlade;
	int32	BladeHoleMinArea;
	int32	BladeHoleErosionDot;

	bool	GenerateBradeTop	;
	bool	GenerateBradeBottom	;
	int32	DentLib1;
	int32	DentLib2;
	int32	DentLib3;
	int32	DentLib4;
	int32	DentLib5;
	int32	DentLib6;
	int32	DentLib7;
	int32	DentLib8;

	int32	BladeLineLib;
	int32	BladeRxLineLib;
	int32	BladeDistanceLib;

	int32	ColorDifferenceLibID1;	//Default

	LibraryUsageContainer	UsageTopSide;
	LibraryUsageContainer	UsageBottomSide;
	LibraryUsageContainer	UsageMonoSide;
	LibraryUsageContainer	UsageMonoSide2;

	int32	LevelTopCharBrightness		;
	int32	LevelTopCharSize			;
	int32	LevelTopFlatBrightness		;
	int32	LevelTopFlatSize			;
	int32	LevelBottomCharBrightness	;
	int32	LevelBottomCharSize			;
	int32	LevelBottomFlatBrightness	;
	int32	LevelBottomFlatSize			;

	int32	SearchDotForPhase;

	int32	Printout_MaxCountfNGImage;

	double	CADTopZoomX			;
	double	CADTopZoomY			;
	int		CADTopGenLibType	;
	int		CADTopGenLibID		;
	double	CADTopEnfatLine		;
	double	CADBottomZoomX		;
	double	CADBottomZoomY		;
	int		CADBottomGenLibType	;
	int		CADBottomGenLibID	;
	double	CADBottomEnfatLine	;
	double	CADTopYShear		;
	double	CADBottomYShear		;
	double	CADMonoZoomX		;
	double	CADMonoZoomY		;
	int		CADMonoGenLibType	;
	int		CADMonoGenLibID		;
	double	CADMonoEnfatLine	;
	double	CADMonoYShear		;
	bool	SyncAllSides		;

	ParamLevel	Level[CountOfLevel];
	//AllocationLibByColorContainer	AllocationLibByColorContainerInst[CountOfSides][CountOfLevel];

	QString	SystemTriggerIPAddress;
	int32	TriggerTiming1;
	int32	TriggerTiming2;
	int32	TriggerTiming3;
	int32	TriggerTiming4;
	int32	DropTiming	  ;
	double	TriggerMMPerPulse;
	bool	UseBeltSpeed;
	bool	CommToOldController;

	int		SystemBeltLength;	//下流カメラ下からリジェクトまでの距離
	int		AddedTimeoutMilisec;

	ParamCustomized(LayersBase *base);

	virtual	QString	GetDataText(void){	return("fx0 Data");	};
	virtual	QString	GetDefaultFileName(void){	return("PrintInspection.dat");	}

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1);
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1);
};

class	ParamForEachMaster
{
public:
	IntList	Slave0LibID;	//0:Print pattern	1:Flat
	IntList	Slave1LibID;	//0:Print pattern	1:Flat
	IntList	Slave2LibID;	//0:Print pattern	1:Flat
	IntList	Slave3LibID;	//0:Print pattern	1:Flat

	int32	TriggerTiming1;	//使用しない
	int32	TriggerTiming2;	//使用しない
	int32	DropTiming	  ;	//使用しない
	int32	TriggerTiming3;	//使用しない
	int32	TriggerTiming4;	//使用しない

	ParamForEachMaster(void);

	void	ClearInInitial(void)
	{
		//Slave0LibID=0;
		//Slave1LibID=0;
		//Slave2LibID=0;
	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif