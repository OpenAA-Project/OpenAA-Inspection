#if	!defined(XGUIDirectMessage_h)
#define	XGUIDirectMessage_h

#include <QIODevice>
#include "XTypeDef.h"
#include "NList.h"
#include "XErrorCode.h"
#include "XUndo.h"
#include "XServiceForLayers.h"

class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	GUICmdPacketBase;
class	IntegrationCmdPacketBase;

class	GUIDirectMessage
{
protected:
	int32	IDForUndo;
public:
	explicit	GUIDirectMessage(int32 idForUndo):IDForUndo(idForUndo){}
	explicit	GUIDirectMessage(LayersBase *base);
	explicit	GUIDirectMessage(GUICmdPacketBase *base);

	virtual ~GUIDirectMessage(void){}

	int32	GetIDForUndo(void)		{	return IDForUndo;	}
	void	SetIDForUndo(int32 d)	{	IDForUndo=d;		}

	virtual	bool	Save(QIODevice *f){	return true;	}
	virtual	bool	Load(QIODevice *f){	return true;	}
};

#endif
