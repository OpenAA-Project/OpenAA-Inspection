#if	!defined(XGUIPIECEFORREVIEW_H)
#define	XGUIPIECEFORREVIEW_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPieceForReview.h"
#include "XColorSpace.h"
#include "XAlgorithmLibrary.h"
#include "XGUIPacketForDLL.h"
#include "XPieceForReviewPacket.h"


class	CmdPieceForReviewDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdPieceForReviewDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdPieceForReviewDrawAttr : public GUIDirectMessage
{
public:
	PieceForReviewDrawAttr	*Attr;

	CmdPieceForReviewDrawAttr(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddItemPieceForReview : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	GUICmdAddItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemListPieceForReview : public GUICmdPacketBase
{
public:
	GUICmdReqItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemListPieceForReview : public GUICmdPacketBase
{
public:
	ItemsContainerPieceForReview	ListData;

	GUICmdAckItemListPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeList(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//======================================================================================

class	GUICmdChangeItemPieceForReview : public GUICmdPacketBase
{
public:
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	GUICmdChangeItemPieceForReview(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif