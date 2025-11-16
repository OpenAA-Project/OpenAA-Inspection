#if	!defined(XQuickBuffer_h)
#define	XQuickBuffer_h

#include "NList.h"
#include <QIODevice>
#include <QByteArray>
#include "XTypeDef.h"

#define	QuickBufferFirstSize	1000


class	QuickBuffer : public QIODevice
{
	class	MemoryInBuffer : public NPList<MemoryInBuffer>
	{
	public:
		BYTE		*Pointer;
		int			AllocSize;
		int			WSize;

		MemoryInBuffer(int Len);
		~MemoryInBuffer(void);
	};
	NPListPack<MemoryInBuffer>	BuffStock;

	MemoryInBuffer	*CurrentBuff;
	int				Current;
	QIODevice::OpenMode Mode;
public:
	QuickBuffer(QByteArray *buff);
	QuickBuffer(void);
	virtual	~QuickBuffer();

	virtual bool open ( QIODevice::OpenMode mode );
	virtual	void close ();
	
	virtual qint64 pos () const;
	virtual bool reset ();
	virtual bool seek ( qint64 pos );
	virtual qint64 size () const;

protected:
	virtual qint64 readData ( char * data, qint64 maxSize );
	virtual qint64 readLineData ( char * data, qint64 maxSize );
	virtual qint64 writeData ( const char * data, qint64 maxSize );

};


#endif