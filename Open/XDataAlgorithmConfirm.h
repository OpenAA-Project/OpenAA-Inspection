#pragma once

#include "NListComp.h"
#include <QString>
#include <QIODevice>

enum ConfirmType
{
	CF_Emergency		=1
	,CF_Alert			=2
	,CF_NG				=3
	,CF_ReqConfirm		=4
};

class ConfirmItemList : public NPListSaveLoad<ConfirmItemList>
{
public:
	int		Phase	;
	int		Page	;
	int		Layer	;
	int		ItemID	;
	QString	Cause	;
	ConfirmType	CType;

	ConfirmItemList(void);
	ConfirmItemList(const ConfirmItemList &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	ConfirmItemList	&operator=(const ConfirmItemList &src);
};

class ConfirmItemListContainer : public NPListPackSaveLoad<ConfirmItemList>
{
public:
	ConfirmItemListContainer(void);
	ConfirmItemListContainer(const ConfirmItemListContainer &src);

	virtual	ConfirmItemList	*Create(void);

	ConfirmItemListContainer	&operator=(const ConfirmItemListContainer &src);
};
