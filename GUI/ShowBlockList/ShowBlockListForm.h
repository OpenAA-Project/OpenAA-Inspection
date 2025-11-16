#ifndef SHOWBLOCKLISTFORM_H
#define SHOWBLOCKLISTFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XStatusController.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class ShowBlockListForm;
}

class ShowBlockListForm : public GUIFormBase
{
    Q_OBJECT

	int	tableWidgetLibWidth;
	int	stackedWidgetModeWidth;
	int	tableWidgetLibHeight;
	int	stackedWidgetModeHeight;
public:
	bool	EasyMode;

	enum	InfoType{
		 BroadDark_BrightnessWidth		=1
		,BroadDark_NGSize				=2
		,BroadDark_NGLength				=3
		,BroadDark_MaxSize				=4
		,BroadDark_ClusterCount			=5
		,BroadDark_Connection			=6

		,BroadLight_BrightnessWidth		=11
		,BroadLight_NGSize				=12
		,BroadLight_NGLength			=13
		,BroadLight_MaxSize				=14
		,BroadLight_ClusterCount		=15
		,BroadLight_Connection			=16

		,NarrowDark_BrightnessWidth		=21
		,NarrowDark_NGSize				=22
		,NarrowDark_NGLength			=23
		,NarrowDark_MaxSize				=24
		,NarrowDark_ClusterCount		=25
		,NarrowDark_Connection			=26

		,NarrowLight_BrightnessWidth	=31
		,NarrowLight_NGSize				=32
		,NarrowLight_NGLength			=33
		,NarrowLight_MaxSize			=34
		,NarrowLight_ClusterCount		=35
		,NarrowLight_Connection			=36

		,BrightAdjustment_Enable		=41
		,BrightAdjustment_DarkSide		=42
		,BrightAdjustment_LightSide		=43

		,Attribute_InspectionEffective	=51
		,Attribute_AbsoluteBrightness	=52
		,Attribute_Clusterize			=53
		,Attribute_Differential			=54
		,Attribute_FollowOutline		=55
		,Attribute_OnlyMaxNGSize		=56
		,Attribute_NoOutput				=57
		,Attribute_WhiteMask			=58
		,Attribute_BlackMask			=59
		,Attribute_PickupFromParts		=60
		,Attribute_ReverseLogic			=61
		,Attribute_DetailSearch			=62
		,Attribute_DynamicMask			=63
		,Attribute_UseMasterImage		=64

		,Search_EnableWholeSearch		=71
		,Search_SelfSearchDot			=72
		,Search_WholeSearchDot			=73
	};
	double	HistTable[256];
	int		BrightWidthBL;
	int		BrightWidthBH;
	int		BrightWidthNL;
	int		BrightWidthNH;
	int		NGSizeBL;
	int		NGSizeBH;
	int		NGSizeNL;
	int		NGSizeNH;
	int		SearchDot;
	int		Count;


    explicit ShowBlockListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowBlockListForm();

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
private slots:
    void on_listWidgetValueType_clicked(const QModelIndex &index);
    void on_listWidgetBroadDark_clicked(const QModelIndex &index);
    void on_listWidgetBroadLight_clicked(const QModelIndex &index);
    void on_listWidgetNarrowDark_clicked(const QModelIndex &index);
    void on_listWidgetNarrowLight_clicked(const QModelIndex &index);
    void on_listWidgetBrightAdjustment_clicked(const QModelIndex &index);
    void on_listWidgetAttribute_clicked(const QModelIndex &index);
    void on_listWidgetSearch_clicked(const QModelIndex &index);
    void on_pushButtonSaveCSV_clicked();

    void on_horizontalSliderBrightnessN_valueChanged(int value);
    void on_horizontalSizeN_valueChanged(int value);
    void on_horizontalSliderBrightnessB_valueChanged(int value);
    void on_horizontalSizeB_valueChanged(int value);
    void on_horizontalSliderSearch_valueChanged(int value);
    void on_tableWidgetLib_clicked(const QModelIndex &index);

    void on_pushButtonSetEasyOperation_clicked();

	void	ResizeAction();

private:
    Ui::ShowBlockListForm *ui;

	AlgorithmLibraryListContainer	LibIDs;
	void	ShowValue(InfoType RType);
	void	ShowCurrentPosition(int LibType,int LibID);
	bool	CalcAveSigma(double HistTable[256],double &Average ,double &Sigma);
};

//--------------------------------------------------------------------------

class	LayerValueCount : public NPListSaveLoad<LayerValueCount>
{
public:
	int32	Layer;
	int32	ValueInt;
	double	ValueDouble;
	bool	ValueBool;
	enum	EnumValueType
	{
		 _ValueInt		=1
		,_ValueDouble	=2
		,_ValueBool		=3
	}ValueType;
	int32	Count;


	LayerValueCount(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	LayerValueCountContainer : public NPListPackSaveLoad<LayerValueCount>
{
public:
	LayerValueCountContainer(void){}

	virtual	LayerValueCount	*Create(void){	return new LayerValueCount();	}

	void	Add(int Layer ,int d);
	void	Add(int Layer ,double d);
	void	Add(int Layer ,bool d);
};

//--------------------------------------------------------------------------
class	GUIReqUsedLibrary: public GUICmdPacketBase
{
public:

	GUIReqUsedLibrary(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckUsedLibrary: public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	LibIDs;

	GUIAckUsedLibrary(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//--------------------------------------------------------------------------
class	GUIReqLayerValueCount: public GUICmdPacketBase
{
public:
	int							LibType;
	int							LibID;
	ShowBlockListForm::InfoType	ReqType;

	GUIReqLayerValueCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckLayerValueCount: public GUICmdPacketBase
{
public:
	LayerValueCountContainer	ItemCounts;

	GUIAckLayerValueCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};
//--------------------------------------------------------------------------
class	GUIReqStatisticByLib: public GUICmdPacketBase
{
public:
	int		LibType;
	int		LibID;

	GUIReqStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckStatisticByLib: public GUICmdPacketBase
{
public:
	double	HistTable[256];
	int		BrightWidthBL;
	int		BrightWidthBH;
	int		BrightWidthNL;
	int		BrightWidthNH;
	int		NGSizeBL;
	int		NGSizeBH;
	int		NGSizeNL;
	int		NGSizeNH;
	int		SearchDot;

	GUIAckStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUISetStatisticByLib: public GUICmdPacketBase
{
public:
	int		LibType;
	int		LibID;
	int		BrightWidthBL;
	int		BrightWidthBH;
	int		BrightWidthNL;
	int		BrightWidthNH;
	int		NGSizeBL;
	int		NGSizeBH;
	int		NGSizeNL;
	int		NGSizeNH;
	int		SearchDot;

	GUISetStatisticByLib(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SHOWBLOCKLISTFORM_H
