#if	!defined(XEachThresholdCommon_h)
#define	XEachThresholdCommon_h

#include <QObject>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XDotColorMatching.h"
#include "XServiceForLayers.h"
#include "XPanelShowResultImage.h"
#include "SetThresholdLevelForm.h"

class	ButtonSettingThresholdForm;
class	QSlider;

class	EachThresholdCommon : public QWidget ,public ServiceForLayers 
{
    Q_OBJECT

	DotColorMatchingBase	*AlgoBase;
public:
	int		SlaveNo;
	enum	__AreaType{
		 _AreaTypeNothing	=0
		,_Mono				=1
		,_Gradation			=2
		,_Character			=3
		,_NoPrint			=4
		,_AreaCADLine		=5
		,_AreaBlade			=6
	}AreaType;
	enum	__InspectionType
	{
		 _InspectionTypeNothing	=0
		,_BrightnessInspection	=1
		,_RedInspection			=2
		,_OozingInspection		=3
		,_MultiSpotInspection	=4
		,_CADLine				=5
		,_Blade					=6
		,_InspectionEnable		=7
	}InspectionType;
	int	RepresentativePhase;
	int	RepresentativePage;
	IntList	RepresentativeItemID;
	bool	FreePosition;

	DotColorMatchingItem	*DItem;
	PanelShowResultImage	PanelResultImage;
	SetThresholdLevelForm	*ThreForm;

	EachThresholdCommon(int slaveno ,ButtonSettingThresholdForm *p
						,LayersBase *base,__AreaType areatype, __InspectionType inspectiontype);
	~EachThresholdCommon(void);

	void	SetThresholdFrame(QFrame *v);
    void	SetActivePosition(int Phase,int Page ,int GlobalX,int GlobalY,IntList &ItemID);

	int		GetThresholdOrder(void);
	int		GetThresholdLevelID(void);

	bool	GetItemThreshold(int LevelID);
	bool	GetItemByLibID(int LibID,int LevelID);
	bool	GetItemByLibIDArea(int Phase,int LibID,int LevelID ,FlexArea &Area);
	DotColorMatchingBase	*GetAlgorithmBase(void){	return AlgoBase;	}
	virtual	void	MouseLDoubleClick(int gx,int gy ,int LevelID);

	void	ReflectAll(int LevelID);
	void	ReflectAllOnlySize(int OKDotB,int OKLengthB,int OKDotN ,int OKLengthN,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectRedAllOnlySize(int RedOKDot				,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectMultiAllOnlySize(int OKDot ,int NGCount	,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectOozingAllOnlySize(int Shift				,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectAreaSearchAllOnlySize(int AreaSearcgX,int AreaSearchY,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectEnable			(bool InspectionEnable	,int LevelID ,const FlexArea &Area=FlexArea());
	void	ReflectBrightness(int	AddBrightness ,int AddOffset ,int AddShift,int LevelID ,const FlexArea &Area=FlexArea());

	void	RGBRange2HSVRange(int CR,int CG,int CB
							,int RL,int RH ,int GL ,int GH ,int BL ,int BH
							, double &CH ,double &CS ,double &CV
							, double &HL ,double &HH ,double &SL ,double &SH ,double &VL ,double &VH);

	void	HSVRange2RGBRange(int &CR,int &CG,int &CB
							,int &RL,int &RH ,int &GL ,int &GH ,int &BL ,int &BH
							, double CH ,double CS ,double CV
							, double HL ,double HH ,double SL ,double SH ,double VL ,double VH);

	void	AddRGBInThresholdB(int R ,int G ,int B ,int Level);
	void	SubRGBInThresholdB(int R ,int G ,int B ,int Level);
	void	AddRGBInThresholdN(int R ,int G ,int B ,int Level);
	void	SubRGBInThresholdN(int R ,int G ,int B ,int Level);

	void	AddRGBInThresholdInside(DotColorMatchingThreshold::MThreshold *MThr,int R ,int G ,int B ,int LevelID);
	void	SubRGBInThresholdInside(DotColorMatchingThreshold::MThreshold *MThr,int R ,int G ,int B ,int LevelID);

	bool	CheckNG( int BRL,int BRH ,int BGL, int BGH ,int BBL ,int BBH
					,int NRL,int NRH ,int NGL, int NGH ,int NBL ,int NBH
						,int Mergin
						,int &Error
						,int &NGSizeB ,int &NGLengthB
						,int &NGSizeN ,int &NGLengthN
						,int LevelID);

	virtual	void	ChangeThresholdLevelID(int value){}
private slots:
    void SlotChangeThresholdLevelID(int value);
};

//===========================================================================

class	IntegrationReqRepresentative: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;
	QByteArray	CartonParam;
	IntList		LibIDs;

	IntegrationReqRepresentative(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckRepresentative: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;
	QByteArray	ItemData;

	IntegrationAckRepresentative(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationReqRepresentativeByLib: public IntegrationCmdPacketBase
{
public:
	int			LibID;

	IntegrationReqRepresentativeByLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckRepresentativeByLib: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;
	QByteArray	ItemData;

	IntegrationAckRepresentativeByLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationReqItemByAreaLib: public IntegrationCmdPacketBase
{
public:
	int			Phase;
	int			LevelID;
	int			LibID;
	FlexArea	Area;

	IntegrationReqItemByAreaLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckItemByAreaLib: public IntegrationCmdPacketBase
{
public:
	int			Page;
	int			ItemID;
	QByteArray	ItemData;

	IntegrationAckItemByAreaLib(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};
class	IntegrationReqTryInspection: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	IntList	ItemID;
	QByteArray	ItemThreshold;
	double	ZoomRate;
	int		movx,movy;
	int		ImageW,ImageH;
	bool	OverlapNG;
	bool	DrawMode;
	int		DrawGx,DrawGy;
	QColor	DrawColor;

	IntegrationReqTryInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckTryInspection: public IntegrationCmdPacketBase
{
	friend	class ButtonSettingThresholdForm;
public:
	//QImage	TargetImageWithNG;
	int32	SlaveNo;
	int		Error;
	int		NGCount;
	int		NGSizeB;
	int		NGLengthB;
	int		NGSizeN;
	int		NGLengthN;

	IntegrationAckTryInspection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationReqItemID: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;
	int	Phase;
	int	Page;
	int	GlobalX,GlobalY;
	QByteArray	CartonParam;

	IntegrationReqItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckItemID: public IntegrationCmdPacketBase
{
public:
	IntList	ItemID;

	IntegrationAckItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationReqItemData: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	ItemID;

	IntegrationReqItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckItemData: public IntegrationCmdPacketBase
{
public:

	QByteArray	ItemData;

	IntegrationAckItemData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};



class	IntegrationReqReflectThreshold: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;
	int			LibID;
	QByteArray	ThresholdData;

	IntegrationReqReflectThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	CopyThreshold(DotColorMatchingThreshold *Dst 
						 ,DotColorMatchingThreshold *src
						 ,EachThresholdCommon::__InspectionType IType);
};

class	IntegrationReqReflectOnlySize: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;

	int			LibID;
	int			OKDotB;
	int			OKLengthB;
	int			OKDotN;
	int			OKLengthN;
	int			RedOKDot;
	int			MultiOKDot;
	int			MultiNGCount;
	int			SelfSearch;
	FlexArea	SelectedArea;

	IntegrationReqReflectOnlySize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	SetSize(DotColorMatchingThreshold *Dst);
};

class	IntegrationReqReflectOnlyAreaSearch: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;

	int			LibID;
	int			AreaSearchX;
	int			AreaSearchY;
	FlexArea	SelectedArea;

	IntegrationReqReflectOnlyAreaSearch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	Set(DotColorMatchingThreshold *Dst);
};

class	IntegrationReqReflectEnable: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;

	int			LibID;
	bool		InspectionEnable;
	FlexArea	SelectedArea;

	IntegrationReqReflectEnable(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	SetEnable(DotColorMatchingThreshold *Dst);
};


class	IntegrationReqColor: public IntegrationCmdPacketBase
{
public:
	int	GlobalX,GlobalY;
	int	Phase;
	int	AreaSize;

	IntegrationReqColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckColor: public IntegrationCmdPacketBase
{
public:
	int	BRL,BRH,BGL,BGH,BBL,BBH;
	int	NRL,NRH,NGL,NGH,NBL,NBH;

	IntegrationAckColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	IntegrationReqAreaType: public IntegrationCmdPacketBase
{
public:
	IntList	ItemID	;
	int	Phase	;
	int	Page	;

	IntegrationReqAreaType(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckAreaType: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	int	GlobalX,GlobalY;

	IntegrationAckAreaType(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationSetBrightnessShift: public IntegrationCmdPacketBase
{
public:
	EachThresholdCommon::__AreaType AreaType;
	EachThresholdCommon::__InspectionType InspectionType;
	int			LibID;
	int	AddBrightness;
	int	AddOffset;
	int	AddShift;
	FlexArea	SelectedArea;

	IntegrationSetBrightnessShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif