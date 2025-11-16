#if	!defined(XPIECEFORREVIEWPACKET_H)
#define	XPIECEFORREVIEWPACKET_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPieceForReview.h"
#include "XAlgorithmLibrary.h"
#include "XGUIPacketForDLL.h"


class	ItemsListPieceForReview : public NPList<ItemsListPieceForReview>
{
public:
	int			GlobalPage;
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;
	int			X1,Y1,X2,Y2;

	ItemsListPieceForReview(void);

	ItemsListPieceForReview	&operator=(ItemsListPieceForReview &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ItemsContainerPieceForReview : public NPListPack<ItemsListPieceForReview>
{
public:
	ItemsContainerPieceForReview(void){}

	ItemsContainerPieceForReview	&operator+=(ItemsContainerPieceForReview &src);
	ItemsContainerPieceForReview	&operator=(ItemsContainerPieceForReview &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//====================================================================================
class	CmdAddItemPieceForReview : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdAddItemPieceForReview(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdMakePieceForReviewList : public GUIDirectMessage
{
public:
	ItemsContainerPieceForReview	*ListData;

	CmdMakePieceForReviewList(LayersBase *base):GUIDirectMessage(base){	ListData=NULL;	}
};

class	CmdChangeItemPieceForReview : public GUIDirectMessage
{
public:
	int			ItemID;
	int			AreaNumber;
	QString		AreaName;
	int			SysRegNumber;

	CmdChangeItemPieceForReview(LayersBase *base):GUIDirectMessage(base){}
};

#endif