#include "XTypeDef.h"
#include "XQuickBuffer.h"
#include "swap.h"

QuickBuffer::MemoryInBuffer::MemoryInBuffer(int Len)
{
	Pointer=new BYTE[Len];
	AllocSize=Len;
	WSize=0;
}
QuickBuffer::MemoryInBuffer::~MemoryInBuffer(void)
{
	delete	[]Pointer;
	Pointer=NULL;
	AllocSize=0;
	WSize=0;
}


QuickBuffer::QuickBuffer(QByteArray *buff)
{
	CurrentBuff	=NULL;
	Current		=0;
	Mode			=QIODevice::NotOpen;

	int	Len=buff->size();
	MemoryInBuffer	*b=new MemoryInBuffer(Len);
	CurrentBuff=b;
	Current	=Len;
	BuffStock.AppendList(b);
}
QuickBuffer::QuickBuffer(void)
{
	CurrentBuff	=NULL;
	Current		=0;
	Mode			=QIODevice::NotOpen;
}
QuickBuffer::~QuickBuffer()
{
	BuffStock.RemoveAll();
	CurrentBuff	=NULL;
	Current		=0;
}

bool QuickBuffer::open ( QIODevice::OpenMode mode )
{
	Mode=mode;
	CurrentBuff	=BuffStock.GetFirst();
	Current		=0;
	return QIODevice::open (mode | QIODevice::Unbuffered);
}
void QuickBuffer::close ()
{
	Mode	=QIODevice::NotOpen;
	 QIODevice::close();
}

qint64 QuickBuffer::pos () const
{
	qint64	n=0;
	for(MemoryInBuffer *a=BuffStock.GetFirst();a!=NULL;a=a->GetNext()){
		if(a==CurrentBuff){
			n+=Current;
			break;
		}
		else{
			n+=a->WSize;
		}
	}
	return n;
}

bool QuickBuffer::reset ()
{
	CurrentBuff=BuffStock.GetFirst();
	Current=0;
	return QIODevice::reset();
}
bool QuickBuffer::seek ( qint64 pos )
{
	QIODevice::seek(pos);
	for(MemoryInBuffer *a=BuffStock.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->WSize>=pos){
			CurrentBuff=a;
			Current=pos;
			return true;
		}
		pos-=a->WSize;
	}
	return false;
}
qint64 QuickBuffer::size () const
{
	qint64 Ret=0;
	for(MemoryInBuffer *a=BuffStock.GetFirst();a!=NULL;a=a->GetNext()){
		Ret+=a->WSize;
	}
	return Ret;
}

qint64 QuickBuffer::readData ( char * data, qint64 maxSize )
{
	qint64	n=0;
	for(MemoryInBuffer *a=CurrentBuff;a!=NULL;a=a->GetNext()){
		int	Len=a->WSize-Current;
		if(Len>maxSize)
			Len=maxSize;
		memcpy(data,&a->Pointer[Current],Len);
		Current+=Len;
		data+=Len;
		n+=Len;
		maxSize-=Len;
		CurrentBuff=a;
		if(maxSize<=0)
			break;
		Current=0;
	}
	return n;
}
qint64 QuickBuffer::readLineData ( char * data, qint64 maxSize )
{
	return readData (data, maxSize );

}
qint64 QuickBuffer::writeData ( const char * data, qint64 maxSize )
{
	qint64	n=0;
	for(MemoryInBuffer *a=CurrentBuff;a!=NULL;a=a->GetNext()){
		int	Len=a->AllocSize-Current;
		if(Len>maxSize)
			Len=maxSize;
		memcpy(&a->Pointer[Current],data,Len);
		Current+=Len;
		data+=Len;
		n+=Len;
		maxSize-=Len;
		CurrentBuff=a;
		a->WSize+=Len;
		if(maxSize<=0){
			return n;
		}
		Current=0;
	}
	if(maxSize!=0){
		if(CurrentBuff==NULL){
			MemoryInBuffer	*a=new MemoryInBuffer(max(maxSize,(qint64)QuickBufferFirstSize));
			CurrentBuff=a;
			BuffStock.AppendList(a);
		}
		else{
			int	Size=CurrentBuff->AllocSize*1.5+max(maxSize,(qint64)QuickBufferFirstSize);
			MemoryInBuffer	*a=new MemoryInBuffer(Size);
			BuffStock.AppendList(a);
			CurrentBuff=a;
		}
		memcpy(&CurrentBuff->Pointer[Current],data,maxSize);
		CurrentBuff->WSize=maxSize;
		Current+=maxSize;
		n+=maxSize;
	}
	return n;
}
