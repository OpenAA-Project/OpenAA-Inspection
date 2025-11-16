#if	!defined(XModelPageCommander_h)
#define	XModelPageCommander_h

#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XDataModelPageLayerItem.h"

//ëºÇÃÉyÅ[ÉWÇÃRentalDataÇéÊìæ
class	SlaveCommReqRentalItems : public DirectCommPacketBase
{
public:
	int		Layer;
	int		FromGlobalPage;
	QString	AlgoRoot;
	QString	AlgoName;
	QByteArray Something;

	SlaveCommReqRentalItems(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckRentalItems : public DirectCommPacketBase
{
public:
	NPListPack<AlgorithmItemPLI>	RentalData;
	int		Layer;
	QString	AlgoRoot;
	QString	AlgoName;

	SlaveCommAckRentalItems(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif