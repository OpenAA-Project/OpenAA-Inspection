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

#if	!defined(XARRANGEMENTFROMFILE_H)
#define	XARRANGEMENTFROMFILE_H

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"

class	ArrangementItem	: public NPList<ArrangementItem>
{
public:
	double	CenterX	 ,CenterY;
	double	ItemWidth,ItemHeight;

	ArrangementItem &operator=(const ArrangementItem &src);
};

inline	ArrangementItem &ArrangementItem::operator=(const ArrangementItem &src)
{
	CenterX		=src.CenterX;
	CenterY		=src.CenterY;
	ItemWidth	=src.ItemWidth;
	ItemHeight	=src.ItemHeight;
	return *this;
}


class	ArrangementDLLClass : public NPList<ArrangementDLLClass> ,public DLLManager,public ServiceForLayers
{
	QLibrary 		DllLib;
protected:

	bool		(*DLL_GetOrganization)(QString &str);
	WORD		(*DLL_GetDLLType)(void);
	bool		(*DLL_GetName)(QString &Root ,QString &Name);
	WORD		(*DLL_GetVersion)(void);
	const char	*(*DLL_GetExplain)(void);

	bool		(*DLL_Initial)(LayersBase *Base);

	bool		(*DLL_GetFileExtType)(QString &ExtTypeStr);
	bool		(*DLL_LoadFromFile  )(QString &FileName ,NPListPack<ArrangementItem> &RetList);
	bool		(*DLL_LoadFromStream)(QIODevice *DevStr ,NPListPack<ArrangementItem> &RetList);

public:
	QString			FileName;
	QString			Organization;
	QString			DLLRoot;
	QString			DLLName;
	WORD			Ver;

	ArrangementDLLClass(LayersBase *base);
	~ArrangementDLLClass(void);

	bool		LoadDLL(QString &filename);
	bool		IsArrangementDLL(void);
	bool		Initial(LayersBase *Base);
	bool		CheckSystemVersion(QStringList &Str);

	bool		GetFileExtType(QString &ExtTypeStr);
	bool		LoadFile(QString &FileName ,NPListPack<ArrangementItem> &RetList);

	void	CopyPointerFrom(ArrangementDLLClass &src);
};

class	ArrangementDLLBase : public NPListPack<ArrangementDLLClass>,public ServiceForLayers
{
public:
	ArrangementDLLBase(LayersBase *Base);

	int		SearchAddDLL(QString path);
	bool	CheckSystemVersion(QStringList &Str);

	void	CopyPointerFrom(ArrangementDLLBase &src);
};

#endif