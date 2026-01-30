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



#if	!defined(XSOURCEGENERATOR_H)
#define	XSOURCEGENERATOR_H

#include <QTextStream>
#include <QPoint>
#include <QString>
#include <QColor>
#include <QPainter>
#include "NList.h"

class	ItemVariable;
class	NetSystem;


class	CommentData
{
public:
	QString		Comment;
	enum	_CommentType{	
			_Single			//
			,_Multiple		/* */
	}CommentType;

	CommentData(void);
};

class	EnumElement : public NPList<EnumElement>
{
public:
	QString		ElementName;
	int			Value;
	CommentData	Comment;

	EnumElement(void){}
};

class	ItemDefinition : public NPList<ItemDefinition>
{
public:
	enum EnumDataType{
		 _None
		,_BYTE
		,_Char
		,_UnsignedChar
		,_Int16
		,_UInt16		
		,_Int32
		,_UInt32
		,_Int64
		,_UInt64
		,_Bool
		,_Float
		,_Double
		,_QString
		,_QFont
		,_QColor
		,_QDateTime
		,_QPoint
		,_QRect
		,_Struct
		,_Enum
		,_UserDefined
	}DataType;

	QString						TypeName;
	NPListPack<EnumElement>		EnumParams;
	NPListPack<ItemVariable>	StructParams;
	QString						UserDefinedTypeName;

	ItemDefinition(void){}
};

class	ItemVariable : public NPList<ItemVariable>
{
public:
	ItemDefinition	TypeDef;
	QString			VarName;
	int				DimCount;
	int				DimNumb[5];
	CommentData		Comment;

	ItemVariable(void){	DimCount=0;	}
};

class	MessageClass : public NPList<MessageClass>
{
public:
	CommentData		HeaderComment;
	NPListPack<ItemVariable>	Vars;
	QString						MessageName;

	QString						ContentConstructor;
	QString						ReceiverFunction;

	

	MessageClass(void){}

	char	*LoadFromSource(char *fp);
	bool	SaveFromSource(QTextStream &os);
};

//=====================================================================

class	NetItem : public NPList<NetItem>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	QString	IDName;
	QString	SourceFileName;
	QPoint	Position;
	QColor	FrameColor;
	QColor	InnerColor;
	QString	Remark;
	int		Radius;
	NetSystem	*Parent;

	NetItem(NetSystem *parent);

	bool	Save(QTextStream &txt);
	bool	Load(QTextStream &txt);

	bool	IsInclude(QPoint &pos);
	void	Draw(QPainter &Pnt);

	NetItem	&operator=(NetItem &src);
};

class	NetArrow : public NPList<NetArrow>
{
public:
	QString		RootFrom;
	QString		NameFrom;
	QString		IDFrom;
	QString		RootTo;
	QString		NameTo;
	QString		IDTo;
	QPoint		StartPoint;
	QPoint		EndPoint;
	NetSystem	*Parent;

	NetArrow(NetSystem *parent){	Parent=parent;	}
	bool	Save(QTextStream &txt);
	bool	Load(QTextStream &txt);

	bool	IsInclude(QPoint &pos);
	void	Draw(QPainter &Pnt);
};

class	NetSystem
{
public:
	NPListPack<NetItem>		Items;
	NPListPack<NetArrow>	Arrows;

	NetSystem(void){}
	NetItem	*SearchItem(QString root ,QString name ,QString ID);
};

extern	NetSystem	NetSystemData;

#endif