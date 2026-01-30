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

#if	!defined(XLOGO_H)
#define	XLOGO_H

#include "NList.h"
#include <QString>
#include "XTypeDef.h"

class	LayersBase;
class	QWidget;
class	GUIFormBase;

class	LogoLeaf : public NPList<LogoLeaf>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	QString	Name;
	QString	ClassName;
	int		XPos;
	int		YPos;
	QString	FileName;

	LogoLeaf(void){}

	bool	Analyze(QString &LineData);
	void	Execute(QWidget *W);
};

class	LogoStocker : public NPListPack<LogoLeaf>
{
public:
	LogoStocker(void){}

	bool	LoadFromLogoListFile(LayersBase *base);

	void	ExecuteInGUIForm(GUIFormBase *W ,const QString &dllroot ,const QString &dllname);
	void	ExecuteInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname);
};


#endif