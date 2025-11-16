#ifndef SHAREDPIO_H
#define SHAREDPIO_H

#include "sharedpio_global.h"
#include<QString>
#include <QSharedMemory>

class SharedPIO
{
public:
	QSharedMemory	PIOMemory;

	SharedPIO(const QString &Key);
	~SharedPIO();

private:

};

#endif // SHAREDPIO_H
