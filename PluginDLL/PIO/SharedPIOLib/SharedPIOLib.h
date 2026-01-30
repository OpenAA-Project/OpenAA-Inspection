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

#ifndef SHAREDPIOLIB_H
#define SHAREDPIOLIB_H

#include <QSharedMemory>
#include <QString>
#include "XTypeDef.h"

class	SharedPIOLib
{
	QSharedMemory	PIOMemory;
public:
	SharedPIOLib(const QString &Key=/**/"SharedPIO");
	~SharedPIOLib(void);

	void	SetBitCount(int InBitCount ,int OutBitCount);
	void	SetInData(BYTE IData[],int InByte);
};

#endif // SHAREDPIOLIB_H