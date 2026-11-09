/*
 * Copyright (C) 2025
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

#include "XTypeDef.h"
#include "XDLLType.h"


class	PIODLLBaseClass :public IdentifiedClass
{
public:
	PIODLLBaseClass(void){}
	virtual	~PIODLLBaseClass(void){}

	virtual	void	InitialPrepare(void)	{}
	virtual	void	Prepare(void)			{}
	virtual	void	AfterPrepare(void)		{}
	virtual	void	ReadyParam(void)		{}
	virtual	void	AfterStartSequence(void){}
};
