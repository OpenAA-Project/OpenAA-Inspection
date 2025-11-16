#pragma once
#include <QtGui>
#include <QVariant>
#include <QIODevice>
#include <QLibrary>

#include "XTypeDef.h"

class	LayersBase;
class	GeneralStocker;
class	GeneralStockerContainer;
class	LanguagePackage;
class	GUIDirectMessage;
class	ResultInspection;
struct	PropertyGeneralStocker;
class	ListPhasePageLayerPack;
class	ExecuteInitialAfterEditInfo;
class	GuiAdditionalDatabase;
class	SpecifiedBroadcaster;


class	GeneralStockerItemBase :public IdentifiedClass
{
public:
	GeneralStockerItemBase(void){}
	virtual	~GeneralStockerItemBase(void){}

	virtual	void	InitialAfterParamLoaded(void)	{}
	virtual	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}

	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	bool	Load(QIODevice *f)	{	return true;	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v){}
};

