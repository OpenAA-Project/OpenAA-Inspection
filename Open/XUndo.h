/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
	Undo�̗v�f��
		�p�P�b�g���ʂ��������|�A���S���Y���ɑ΂��鑀��
		GUI�ɑ΂��鑀��
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