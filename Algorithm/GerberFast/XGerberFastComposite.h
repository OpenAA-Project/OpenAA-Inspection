/*
 * Copyright (C) 2021
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

#if	!defined(XGerberFastComposite_h)
#define	XGerberFastComposite_h

#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "NListComp.h"

#define	CommonID_GerberCompositeDefinition	2100


class	GerberCompositeDefLayerItem : public NPListSaveLoad<GerberCompositeDefLayerItem>
{
public:
	enum	_Operation{
		_Or			=0
		,_And		=2
		,_NotAnd	=1
		,_NotOr		=3
	}Operation;
	int32	LayerTypeLibID;
	int32	DotSpr;
	bool	NegMode;

	GerberCompositeDefLayerItem(void){	Operation=_Or;	LayerTypeLibID=0;	LayerTypeLibID=0;	DotSpr=0;	NegMode=false;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	GerberCompositeDefLayerItem	&operator=(GerberCompositeDefLayerItem &src);
};

class	GerberCompositeDefLayerItemContainer : public NPListPackSaveLoad<GerberCompositeDefLayerItem>
{
public:
	virtual	GerberCompositeDefLayerItem	*Create(void){	return new GerberCompositeDefLayerItem();	}

	GerberCompositeDefLayerItemContainer	&operator=(GerberCompositeDefLayerItemContainer &src);
};

class	GerberCompositeDefLayer : public NPList<GerberCompositeDefLayer>
{
public:
	QString	Name;
	int		LibFolderID;
	int32	CompositeID;
	int		LibID;
	bool	NegMode;
	int		SourceCompositeID;

	GerberCompositeDefLayerItemContainer	Combination;

	GerberCompositeDefLayer(void){	LibFolderID=-1;	Name="Example 1";	NegMode=false;	LibID=-1;	CompositeID=-1;	SourceCompositeID=-1;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	GerberCompositeDefLayer	&operator=(GerberCompositeDefLayer &src);
};

class	GerberCompositeDefPack : public NPListPack<GerberCompositeDefLayer>
{
public:
	GerberCompositeDefPack(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	Append(QIODevice *f);
	GerberCompositeDefPack	&operator=(GerberCompositeDefPack &src);
	int32	GetMaxID(void);
	GerberCompositeDefLayer	*Search(int compositeDefID);
	bool	CopyCompositeIntoFolder(int NewLibFolderID , int OriginalLibFolderID);

	void	EnumChildren(int CompositeID ,IntList &RetID);
};

class	GerberLayerBase
{
public:
	GerberLayerBase(void){}

};

class	GerberCompositeLayer : public GerberLayerBase,public NPList<GerberCompositeLayer>
{
public:
	int32	CompositeID;
	QColor	LayerColor;
	QString	Remark;
	bool	Visible;
	bool	Operational;

	GerberCompositeLayer(int compsiteIndex);
	GerberCompositeLayer	&operator=(GerberCompositeLayer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

};

inline	GerberCompositeLayer::GerberCompositeLayer(int compsiteid)
{	
	CompositeID=compsiteid;
	Visible=false;	
	Operational=true;
	LayerColor	=Qt::cyan;
}

class	GerberCompositeLayerContainer : public NPListPack<GerberCompositeLayer>
{
public:
	GerberCompositeLayerContainer(void);

	GerberCompositeLayerContainer	&operator=(GerberCompositeLayerContainer &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//========================================================================================


#endif