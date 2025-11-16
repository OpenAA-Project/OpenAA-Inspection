/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XSourceGenerator.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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