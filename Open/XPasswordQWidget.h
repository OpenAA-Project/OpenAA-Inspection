/*
 * Copyright (C) 2016
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

#if	!defined(XPASSWORDQWIDGET_H)
#define	XPASSWORDQWIDGET_H

#include <QObject>
#include "NList.h"
#include "XServiceForLayers.h"

class	PasswordFilterPointerList;
class	PasswordFilter;
class	PasswordInControl;


class	PasswordInQWodget
{
	QWidget	*ParentWidget;
	LayersBase	*Base;
public:
	PasswordInQWodget(LayersBase *base ,QWidget *parent);

	void	SetupPassword(void);

public:
	void	InstallEventHandler(PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData);
	void	InstallEventHandlerOnlyPassword(PasswordFilter *f,PasswordInControl *c);

};


#endif