#pragma once

#include "NListComp.h"
#include <QIODevice>


class AlignmentBlockItemList : public NPListSaveLoad<AlignmentBlockItemList>
{
public:
	int		ItemID;
	int		X1,Y1,X2,Y2;
	int		CurrentRotationPatternNo;
	double	ResultRadian;
	int		ResultDx,ResultDy;

	AlignmentBlockItemList(void){}
	AlignmentBlockItemList(const AlignmentBlockItemList &src);

	AlignmentBlockItemList	&operator=(const AlignmentBlockItemList &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class AlignmentBlockItemListContainer : public NPListPackSaveLoad<AlignmentBlockItemList>
{
public:
	AlignmentBlockItemListContainer(void){}
	AlignmentBlockItemListContainer(const AlignmentBlockItemListContainer &src);

	AlignmentBlockItemListContainer	&operator=(const AlignmentBlockItemListContainer &src);
	virtual	AlignmentBlockItemList	*Create(void);
};
