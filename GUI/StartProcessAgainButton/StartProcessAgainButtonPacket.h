#pragma once

#include <QString>
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GUICmdPushed : public GUICmdPacketBase
{
public:
	int64	InspectionID;
	bool	IsExecInitialAfterEdit;
	QString	ImageType;	//"Master" "Target"
	int32	MaxInspectMilisec;
	bool	ForceBindAllPhase;

	int	RepeatCount_StartByInspection;
	int	RepeatCount_Captured;
	int	RepeatCount_PreAlignent;
	int	RepeatCount_Alignent;
	int	RepeatCount_PreProcessing;
	int	RepeatCount_Processing;
	int	RepeatCount_PostProcessing;

	GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdInspectionAgainReplied : public GUICmdPacketBase
{
public:
	enum	__Result
	{
		_OK			=1
		,_NG		=2
		,_Nothing	=3
	}Result;
	int64		NGCounts;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	int			ExecuterID;

	CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

