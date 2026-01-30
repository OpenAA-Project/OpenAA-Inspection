/*
 * Copyright (C) 2022
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


#ifdef _MSC_VER
#include "Windows.h"

bool	GetMemoryInfo(
	 unsigned long		&dwMemoryLoad
	,unsigned long long	&ullTotalPhys
	,unsigned long long	&ullAvailPhys
	,unsigned long long	&ullTotalPageFile
	,unsigned long long	&ullAvailPageFile
	,unsigned long long	&ullTotalVirtual
	,unsigned long long	&ullAvailVirtual
	,unsigned long long	&ullAvailExtendedVirtual
	)
{
	MEMORYSTATUSEX	MemoryInfo;
	MemoryInfo.dwLength=sizeof(MemoryInfo);
	if(::GlobalMemoryStatusEx(&MemoryInfo)==TRUE){
		dwMemoryLoad			=MemoryInfo.dwMemoryLoad;
		ullTotalPhys			=MemoryInfo.ullTotalPhys;
		ullAvailPhys			=MemoryInfo.ullAvailPhys;
		ullTotalPageFile		=MemoryInfo.ullTotalPageFile;
		ullAvailPageFile		=MemoryInfo.ullAvailPageFile;
		ullTotalVirtual			=MemoryInfo.ullTotalVirtual;
		ullAvailVirtual			=MemoryInfo.ullAvailVirtual;
		ullAvailExtendedVirtual	=MemoryInfo.ullAvailExtendedVirtual;
		return true;
	}
	return false;
}
#else
bool	GetMemoryInfo(
	 unsigned long		&dwMemoryLoad
	,unsigned long long	&ullTotalPhys
	,unsigned long long	&ullAvailPhys
	,unsigned long long	&ullTotalPageFile
	,unsigned long long	&ullAvailPageFile
	,unsigned long long	&ullTotalVirtual
	,unsigned long long	&ullAvailVirtual
	,unsigned long long	&ullAvailExtendedVirtual
	)
{
	return true;
}

#endif