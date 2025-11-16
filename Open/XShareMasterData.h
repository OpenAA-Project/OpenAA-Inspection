#if	!defined(XShareMasterData_H)
#define	XShareMasterData_H

#include "NListComp.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	ShareMasterFromSource : public NPListSaveLoad<ShareMasterFromSource>,public ServiceForLayers
{
public:
	int	SourceMachineID;
	int	Dx;
	int	Dy;
	double	MultiplyLayer[256];

	ShareMasterFromSource(LayersBase *base);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	ShareMasterDestination : public NPListPackSaveLoad<ShareMasterFromSource> ,public ServiceForLayers
								,public NPList<ShareMasterDestination>
{
public:
	int		DestinationMachineID;

	ShareMasterDestination(LayersBase *base);

	virtual	ShareMasterFromSource	*Create(void);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	SortItems(void);
	ShareMasterFromSource	*GetSource(int machineID);
};

class	ShareMasterContainer : public NPListPack<ShareMasterDestination>,public ServiceForLayers
{
public:
	ShareMasterContainer(LayersBase *base);

	ShareMasterDestination	*FindDestination(int DestMachineID);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

#endif