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

#if	!defined(XALGORITHMLIBNGTYPE_H)
#define	XALGORITHMLIBNGTYPE_H

#include <QIODevice>
#include <QColor>
#include <QPainter>
#include "XTypeDef.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"

class	ResultPosList;
class	AlgorithmItemRoot;


class	LibNGTypeItem : public NPList<LibNGTypeItem>,public ServiceForLayers
{
public:
	int32	TypeUniqueCode;	//�f�[�^�x�[�X���ŗB���̒l
	int32	TypeCode;
	QColor	NGColor;
	bool	Blink;
	enum	NGShapeType
	{
		 NG_Circle		=0	//�� �h���Ԃ��Ȃ���
		,NG_FilledCircle=1	//�� �h���Ԃ�����
		,NG_Rectangle	=2	//�� �h���Ԃ��Ȃ��l�p
		,NG_FilledRect	=3	//�� �h���Ԃ����l�p
		,NG_X			=4	//�w �o�b�e��
		,NG_Star		=5	//��
		,NG_FilledStar	=6	//��
		,NG_Cross		=7	//�{
		,NG_Sharp		=8	//��
	}NGShape;
	int32	Priority;
	int		NextJumpMilisec;
	QString	NGName;

	LibNGTypeItem(LayersBase *base);

	LibNGTypeItem	&operator=(const LibNGTypeItem &src);

	virtual	int32	GetVersion(void)	{	return 1;	}
	int32	GetTypeUniqueCode(void)		{	return TypeUniqueCode;	}

	bool	SaveCommon(QIODevice *f);
	bool	LoadCommon(QIODevice *f);
	virtual	bool	Save(QIODevice *f)	=0;
	virtual	bool	Load(QIODevice *f)	=0;

	virtual	bool	ShowSetting(void){		return true;	}

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

class	LibNGTypeInAlgorithm : public NPListPack<LibNGTypeItem>
{
public:
	LibNGTypeInAlgorithm(void){}

	LibNGTypeItem	*GetTypeItem(int TypeCode);

	virtual	LibNGTypeItem	*CreateNewItem(void){	return NULL;	}

	void	SortInPriority(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

//------------------------------------------------------------------------
class	LibraryListWithNGType : public NPList<LibraryListWithNGType>
{
public:
	int		LibID;
	LibNGTypeInAlgorithm	NGList;

	explicit	LibraryListWithNGType(int libId){	LibID=libId;	}
	LibNGTypeInAlgorithm	*GetLibNGTypeInAlgorithm(void){	return &NGList;	}

	virtual	void	Draw(QPainter &pnt ,int x ,int y ,int size);
};

class	LibraryListWithNGTypeContainer : public NPListPack<LibraryListWithNGType>
{
public:
	LibraryListWithNGTypeContainer(void){}

	void	SortInPriority(void);
	LibraryListWithNGType	*GetNGTypeList(int libID);

	void	ExecuteInitialAfterEdit(void);
};


#endif