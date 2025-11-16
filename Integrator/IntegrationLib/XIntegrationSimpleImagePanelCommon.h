#pragma once

#include "NListComp.h"
#include <QString>

class	SelectedItemsInfo : public NPListSaveLoad<SelectedItemsInfo>
{
public:
	int	Phase;
	int	Page;
	int	Layer;
	int	ItemID;
	QString	ItemName;
	QString	Comment;
	QByteArray	SomethingData;

	SelectedItemsInfo(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	SelectedItemsInfo	&operator=(const SelectedItemsInfo &src);
};

class	SelectedItemsInfoContainer : public NPListPackSaveLoad<SelectedItemsInfo>
{
public:
	SelectedItemsInfoContainer(void){}

	virtual	SelectedItemsInfo	*Create(void)	{	return new SelectedItemsInfo();	}

	SelectedItemsInfoContainer	&operator=(const SelectedItemsInfoContainer &src);
};

