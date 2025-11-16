
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
