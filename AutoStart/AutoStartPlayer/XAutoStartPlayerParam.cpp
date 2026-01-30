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



#include "XAutoStartPlayerParam.h"



ParamAutoStart::ParamAutoStart(void)
{
	SettingFileName	=/**/"AutoStart.dat";
	LoopCount=20;
	Arguments="";

	SetParam(&LoopCount	, /**/"Player" ,/**/"LoopCount"		,"Loop count"	,5,1000);
	SetParam(&Arguments	, /**/"Player" ,/**/"Arguments"		,"Argument of execute"	);
}