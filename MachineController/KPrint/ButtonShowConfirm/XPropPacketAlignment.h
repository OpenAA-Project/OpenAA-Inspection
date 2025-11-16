#pragma once

#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
#include "XAlignmentLargeLibrary.h"
#include "XAlignmentLarge.h"
#include "NListComp.h"

//===============================================================================

class	IntegrationReqAlignmentAreaInfo: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	IntegrationReqAlignmentAreaInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class AlignmentAreaList : public NPListSaveLoad<AlignmentAreaList>
{
public:
	int		AreaID;
	int		Layer;
	XAlignmentLargeArea::_EnumPriority	Priority;

	AlignmentAreaList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	QString	GetPriorityString(void);

	AlignmentAreaList	&operator=(const AlignmentAreaList &src);
};

class AlignmentAreaListContainer : public NPListPackSaveLoad<AlignmentAreaList>
{
public:
	AlignmentAreaListContainer(void){}

	virtual	AlignmentAreaList	*Create(void)	{	return new AlignmentAreaList();	}
	AlignmentAreaListContainer	&operator=(const AlignmentAreaListContainer &src);
};

class	IntegrationAckAlignmentAreaInfo: public IntegrationCmdPacketBase
{
public:
	AlignmentAreaListContainer	Container;

	IntegrationAckAlignmentAreaInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//===============================================================================

class	IntegrationReqAlignmentMarkInfo: public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		Layer;
	int		AreaID;

	IntegrationReqAlignmentMarkInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class AlignmentMarkList : public NPListSaveLoad<AlignmentMarkList>
{
public:
	struct MarkThreshold
	{
		int		ItemID;
		int		x1,y1,x2,y2;
		WORD	MoveDotX;
		WORD	MoveDotY;
		WORD	MoveDotX2;	//For priority 1 and 2
		WORD	MoveDotY2;
		WORD	SearchAround;
		int		UsageGlobal;
		int		MaxCountHLine;
		int		MaxCountVLine;
		bool	JudgeWithBrDif;
	}MarkThresholdData;
	double	MatchingRate;

	AlignmentMarkList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	AlignmentMarkList	&operator=(const AlignmentMarkList &src);
};

class AlignmentMarkListContainer : public NPListPackSaveLoad<AlignmentMarkList>
{
public:
	AlignmentMarkListContainer(void){}

	virtual	AlignmentMarkList	*Create(void)	{	return new AlignmentMarkList();	}
	AlignmentMarkListContainer	&operator=(const AlignmentMarkListContainer &src);
};

class	IntegrationAckAlignmentMarkInfo: public IntegrationCmdPacketBase
{
public:
	AlignmentMarkListContainer	Container;

	IntegrationAckAlignmentMarkInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};
//===============================================================================

class	IntegrationReqAlignmentPointResult: public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		localX ,localY;

	IntegrationReqAlignmentPointResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckAlignmentPointResult: public IntegrationCmdPacketBase
{
public:
	int		ShiftX,ShiftY;
	double	RotationRadian;

	IntegrationAckAlignmentPointResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//===============================================================================

class	IntegrationReqAlignmentItem: public IntegrationCmdPacketBase
{
public:
	int		Phase;
	int		Layer;
	int		ItemID;

	IntegrationReqAlignmentItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckAlignmentItem: public IntegrationCmdPacketBase
{
public:
	int		AreaID;

	IntegrationAckAlignmentItem(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};
