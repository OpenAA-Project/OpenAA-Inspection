#if	!defined(XLineEnhancerL1AlgoPacket_H)
#define	XLineEnhancerL1AlgoPacket_H

#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XIntClass.h"
#include "XDirectCommPacket.h"

class	LibraryEfectivity : public NPList<LibraryEfectivity>
{
public:
	int32	LibID;
	bool	IncludedInMask;

	LibraryEfectivity(void);
	LibraryEfectivity(int libID ,bool mask):LibID(libID),IncludedInMask(mask){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LibraryEfectivityContainer : public NPListPack<LibraryEfectivity>
{
public:
	LibraryEfectivityContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool	IsIncluded(int LibID);
};

//他のスレーブで限定マスクでライブラリを使用しているかどうか
class	SlaveCommReqLibraryInMaskOfLECerL1 : public DirectCommPacketBase
{
public:
	IntList	UsedLibraries;

	SlaveCommReqLibraryInMaskOfLECerL1(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckLibraryInMaskOfLECerL1 : public DirectCommPacketBase
{
public:
	LibraryEfectivityContainer	UsedLibraries;

	SlaveCommAckLibraryInMaskOfLECerL1(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


#endif