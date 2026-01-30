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

#pragma once

#include "rwdevyrc1000_global.h"
#include "XRWDevice.h"

class RWDevYRC1000 : public RWDeviceBaseClass
{
public:
    RWDevYRC1000(LayersBase *base ,const QString &Parameter ,QWidget *parent);
	~RWDevYRC1000(void);

	virtual	void	Prepare(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	void	LoopOnIdle(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSettingDialog(QWidget *parent);
};