#if	!defined(XNamingPacket_H)
#define	XNamingPacket_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XVector.h"
#include "XFlexAreaImage.h"
#include "NList.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XIntClass.h"
#include "XDirectCommPacket.h"

//=================================================================================

class	SlaveCommReqOverlappedIndex : public DirectCommPacketBase
{
public:
	FlexArea	GlobalArea;

	SlaveCommReqOverlappedIndex(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckOverlappedIndex : public DirectCommPacketBase
{
public:
	int		Row;
	int		Column;
	bool	Found;

	SlaveCommAckOverlappedIndex(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif