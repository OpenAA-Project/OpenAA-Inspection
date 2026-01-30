/*
 * Copyright (C) 2020
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

#include "SharedPIOLib.h"
#include "SharedPIOCommon.h"
#include <memory.h>
#include "swap.h"

SharedPIOLib::SharedPIOLib(const QString &Key)
	:PIOMemory(Key)
{
	PIOMemory.create (sizeof(struct	SharedPIOInfo));
	struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIOMemory.data();
	SetBitCount(16,16);
}
SharedPIOLib::~SharedPIOLib(void)
{
}
void	SharedPIOLib::SetBitCount(int InBitCount ,int OutBitCount)
{
	struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIOMemory.data();
	memset(p,0,sizeof(struct SharedPIOInfo));
	p->InBitCount	=InBitCount;
	p->OutBitCount	=OutBitCount;
}

void	SharedPIOLib::SetInData(BYTE IData[],int InByte)
{
	PIOMemory.lock();
	struct	SharedPIOInfo	*p=(struct	SharedPIOInfo *)PIOMemory.data();
	memcpy(p->InData,IData,min(InByte,(p->InBitCount+7)>>3));
	PIOMemory.unlock();
}