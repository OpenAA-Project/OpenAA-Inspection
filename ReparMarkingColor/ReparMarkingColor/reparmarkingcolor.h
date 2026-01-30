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

#ifndef REPARMARKINGCOLOR_H
#define REPARMARKINGCOLOR_H

#include "reparmarkingcolor_global.h"
#include "colorform.h"
class RepairBase;
#define	DEFFUNCEX		__declspec(dllexport) 

extern	"C"{
//RepairBase		*PClass;
DEFFUNCEX	bool		_cdecl	DLL_GetName(QString &str);
DEFFUNCEX   void	    _cdecl  DLL_FormShow(void);
colorForm *cform;

};

#endif