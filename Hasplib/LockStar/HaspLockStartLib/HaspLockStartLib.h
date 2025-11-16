#ifndef HASPLOCKSTARTLIB_H
#define HASPLOCKSTARTLIB_H

#include "hasplockstartlib_global.h"

enum	HaspErrorCode
{
	Hasp_OK			=0
	,Hasp_NoKey		=1
	,Hasp_NoDriver	=2
	,Hasp_TimeUp	=3
	,Hasp_NoLicense	=4
};


bool	CheckHasp(int ProductCode,int ProductVersion ,HaspErrorCode &ErrorCode);


#endif // HASPLOCKSTARTLIB_H
