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
