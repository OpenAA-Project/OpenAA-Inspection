#if	!defined(XUNDO_H)
#define	XUNDO_H

#include "XTypeDef.h"
#include "XFlexArea.h"
#include "NList.h"
#include "XUndoBase.h"
#include <QBuffer>
#include "XServiceForLayers.h"
#include <QMutex>
/*
	Undoの要素は
		パケットを通じた操作－アルゴリズムに対する操作
		GUIに対する操作
*/

class	AlgorithmItemRoot;
class	UndoChainObject;


class	UndoTopic : public NPList<UndoTopic>
{
	friend	class	UndoChainObject;

	int32		IDForUndo;
	NPListPack<UndoChainObject>	FuncUndo;
	QString		UndoTopicMessage;
public:

	UndoTopic(const QString &_UndoTopicMessage,int idForUndo);
	virtual	~UndoTopic(void);

	int32		GetIDForUndo(void)		const	{	return IDForUndo;		}
	void		Add(UndoChainObject *a)			{	FuncUndo.AppendList(a);	}

	void	ExecuteUndo(void);
	void	ExecuteRedo(void);
	const QString	&GetTopicMessage(void)	{	return UndoTopicMessage;	}
};

class	UndoStocker : public NPListPack<UndoTopic>,public ServiceForLayers
{
	UndoTopic	*CurrentTopic;
	QMutex		MutexAboutUndoTopic;
public:
	int32	IDBase;

	explicit	UndoStocker(LayersBase *base);
	virtual	~UndoStocker(void);

	void		SetElementToNewTopic(UndoChainObject *elem);

	int32		SetNewTopic(const QString &UndoTopicMessage);
	void		SetLocalTopic(int idForUndo);
	UndoTopic	*SearchTopic(int idForUndo);
	UndoTopic	*GetCurrentTopic(void)	const	{	return CurrentTopic;	}
	UndoTopic	*ExecuteUndo(void);
	UndoTopic	*ExecuteRedo(void);
	UndoTopic	*UndoInMaster(void);
	UndoTopic	*RedoInMaster(void);
};


#endif