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