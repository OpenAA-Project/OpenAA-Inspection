#if	!defined(XCOLORBLOCKALGOPACKET_H)
#define	XCOLORBLOCKALGOPACKET_H

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
class	SlaveCommReqLibraryInMaskOfColorBlock : public DirectCommPacketBase
{
public:
	IntList	UsedLibraries;

	SlaveCommReqLibraryInMaskOfColorBlock(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckLibraryInMaskOfColorBlock : public DirectCommPacketBase
{
public:
	LibraryEfectivityContainer	UsedLibraries;

	SlaveCommAckLibraryInMaskOfColorBlock(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif