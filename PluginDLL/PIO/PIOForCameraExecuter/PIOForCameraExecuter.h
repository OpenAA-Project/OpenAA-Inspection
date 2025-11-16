#ifndef PIOFORCAMERAEXECUTER_H
#define PIOFORCAMERAEXECUTER_H

#include "pioforcameraexecuter_global.h"
#include<QSharedMemory>
#include "XTypeDef.h"

class PIOForCameraExecuter
{
public:
	QSharedMemory	MemoryMapIN;
	QSharedMemory	MemoryMapOUT;

	BYTE	*PointerIN;
	BYTE	*PointerOUT;

	PIOForCameraExecuter(int n);
	~PIOForCameraExecuter();

	bool	Start(void);
private:

};

#endif // PIOFORCAMERAEXECUTER_H
