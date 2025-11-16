#if	!defined(_XPIECELISTREVIEWSIDEPACKET_H)
#define	_XPIECELISTREVIEWSIDEPACKET_H

#include "XGUIFormBase.h"
#include "XPieceReviewSide.h"
#include "NListComp.h"


class	ItemListReviewSide : public NPListSaveLoad<ItemListReviewSide>
{
public:
	int		AreaNumber;
	QString	AreaName;

	ItemListReviewSide(void){}
	ItemListReviewSide(const ItemListReviewSide &src);

	bool	operator==(ItemListReviewSide &src);

	virtual	bool	Save(QIODevice *f)	;
	virtual	bool	Load(QIODevice *f)	;
};

class	ItemListReviewSideContainer : public NPListPackSaveLoad<ItemListReviewSide>
{
public:
	ItemListReviewSideContainer(void){}

	virtual	ItemListReviewSide	*Create(void)	{	return new ItemListReviewSide();	}
	bool	IsInclude(ItemListReviewSide *c);
};


class	GUICmdReqItemListReviewSide : public GUICmdPacketBase
{
public:

	GUICmdReqItemListReviewSide(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemListReviewSide : public GUICmdPacketBase
{
public:
	ItemListReviewSideContainer	ListData;

	GUICmdSendItemListReviewSide(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif