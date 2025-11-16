#pragma once

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XDataAlgorithmConfirm.h"

//=======================================================================

class AlgorithmLibTypeWithAttrData : public NPListSaveLoad<AlgorithmLibTypeWithAttrData>
{
public:
	int		LibType;
	bool	ShowOnlyNG;
	bool	ShowNGItem;
	bool	ShowResultItem;

	AlgorithmLibTypeWithAttrData(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	void	Add(int _typelib ,bool _ShowOnlyNG ,bool _ShowNGItem ,bool _ShowResultItem);

	AlgorithmLibTypeWithAttrData	&operator=(const AlgorithmLibTypeWithAttrData &src);
};

class AlgorithmLibTypeWithAttrDataContainer : public NPListPackSaveLoad<AlgorithmLibTypeWithAttrData>
{
public:
	AlgorithmLibTypeWithAttrDataContainer(void){}

	void	Add(int _typelib ,bool _ShowOnlyNG ,bool _ShowNGItem,bool _ShowResultItem);
	virtual	AlgorithmLibTypeWithAttrData	*Create(void)	override;
	AlgorithmLibTypeWithAttrDataContainer	&operator=(const AlgorithmLibTypeWithAttrDataContainer &src);
};

//-------------------------------------------------------------------------------------

class	IntegrationReqConfirmPanelImage: public IntegrationCmdPacketBase
{
	friend	class ButtonSettingThresholdForm;
public:
	struct ImageStruct
	{
		double	ZoomRate;
		int		movx,movy;
		int		ImageW,ImageH;
		int		Phase;
		bool	MasterImage;
	}ImageStructData;
	AlgorithmLibTypeWithAttrDataContainer	ALgorithmLibTypeContainer;

	IntegrationReqConfirmPanelImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);

private:

};

class	IntegrationAckConfirmPanelImage: public IntegrationCmdPacketBase
{
	friend	class ButtonSettingThresholdForm;
public:

	IntegrationAckConfirmPanelImage(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationConfirmRetry: public IntegrationCmdPacketBase
{
public:
	IntegrationConfirmRetry(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};

//-------------------------------------------------------------------------------------

class	IntegrationSetSelectedArea: public IntegrationCmdPacketBase
{
public:
	FlexArea	SelectedArea;

	IntegrationSetSelectedArea(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationSetActivateItem: public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		localX,localY;
	int		LibType;
	IntList LayerList;

	IntegrationSetActivateItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

//-------------------------------------------------------------------------------------

class	IntegrationReqThresholdLibID: public IntegrationCmdPacketBase
{
public:
	int			FilterLibType;
	FlexArea	Area;
	int			Phase;

	IntegrationReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);

private:

};
class	IntegrationAckThresholdLibID: public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryListContainer	Libs;

	IntegrationAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	GUICmdReqThresholdLibID: public GUICmdPacketBase
{
public:
	int			FilterLibType;
	FlexArea	Area;
	int			Phase;

	GUICmdReqThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckThresholdLibID: public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	Libs;

	GUICmdAckThresholdLibID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//-------------------------------------------------------------------------------------

class	IntegrationReqSelectItems: public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryList	SelectedLib;
	FlexArea	GlobalArea;
	int			Phase;
	int			GlobalX,GlobalY;
	int			Mode;	//0:Area ,1:XY	2:Whole

	IntegrationReqSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationAckSelectItems: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack	Items;

	IntegrationAckSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqSelectItems: public GUICmdPacketBase
{
public:
	AlgorithmLibraryList	SelectedLib;
	FlexArea	LocalArea;
	int			Phase;
	int			LocalX,LocalY;
	int			Mode;	//0:Area ,1:XY	2:Whole

	GUICmdReqSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckSelectItems: public GUICmdPacketBase
{
public:
	ListPhasePageLayerItemPack	Items;

	GUICmdAckSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationReqSelectItemsByGroupID: public IntegrationCmdPacketBase
{
public:
	int		LibType;
	int		Phase;
	int		ErrorGroupID;

	IntegrationReqSelectItemsByGroupID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationAckSelectItemsByGroupID: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack	Items;

	IntegrationAckSelectItemsByGroupID(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};
//-------------------------------------------------------------------------------------

class	IntegrationReqItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;

	IntegrationReqItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int			ItemClass;
	QByteArray	ThresholdData;
	int			LibID;

	IntegrationAckItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 LocalPage,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationSetItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;
	QByteArray	ThresholdData;

	IntegrationSetItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

//-------------------------------------------------------------------------------------

class	IntegrationSetSelectItems: public IntegrationCmdPacketBase
{
public:
	int							LibType;
	ListPhasePageLayerItemPack	Items;

	IntegrationSetSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

//-------------------------------------------------------------------------------------

class	IntegrationClearSelectItems: public IntegrationCmdPacketBase
{
public:
	int							LibType;

	IntegrationClearSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

//-------------------------------------------------------------------------------------

class ResultForConfirmList : public NPListSaveLoad<ResultForConfirmList>
{
public:
	struct	NGInfo{
		int		cx,cy;
		int		NGErrorGroupID;
		int		NGPhase;
		int		NGGlobalPage;
		int		NGLibType;
		int		NGLayer;
		int		NGItemID;
		int		NGIntResult;
		double	NGDoubleResult;
		int		NGType;
	}NGInfoData;
	QString	Name;
	QString	Cause;
	QString	Message;

	ResultForConfirmList(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	ResultForConfirmList	&operator=(const ResultForConfirmList &src);
};

class ResultForConfirmListContainer : public NPListPackSaveLoad<ResultForConfirmList>
{
public:
	ResultForConfirmListContainer(void){}

	virtual	ResultForConfirmList	*Create(void)	override	{	return new ResultForConfirmList();	}

	ResultForConfirmListContainer	&operator=(const ResultForConfirmListContainer &src);
	ResultForConfirmListContainer	&operator+=(const ResultForConfirmListContainer &src);
};


class	IntegrationReqCurrentResult: public IntegrationCmdPacketBase
{
public:
	IntegrationReqCurrentResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckCurrentResult: public IntegrationCmdPacketBase
{
public:
	ResultForConfirmListContainer	ResultContainer;

	IntegrationAckCurrentResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//-------------------------------------------------------------------------------------

class	IntegrationReqCurrentProcessTime: public IntegrationCmdPacketBase
{
public:
	IntegrationReqCurrentProcessTime(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}	
	virtual	bool	Save(QIODevice *f)	{	return true;	}	

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckCurrentProcessTime: public IntegrationCmdPacketBase
{
public:
	DWORD	MiliSec;

	IntegrationAckCurrentProcessTime(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);	
	virtual	bool	Save(QIODevice *f);	

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};


//============================================================================
class	IntegrationCmdReqConfirmItemList : public IntegrationCmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	IntegrationCmdReqConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 SlaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationCmdAckConfirmItemList : public IntegrationCmdPacketBase
{
public:
	ConfirmItemListContainer	ItemList;

	IntegrationCmdAckConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 SlaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===============================================================================

class	IntegrationReqConfirmItemInfo: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;

	IntegrationReqConfirmItemInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckConfirmItemInfo: public IntegrationCmdPacketBase
{
public:
	struct ConfirmItemInfo
	{
		int	x1,y1,x2,y2;
		int	LibID;
	}Data;

	IntegrationAckConfirmItemInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1 );

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};