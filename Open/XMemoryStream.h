#if	!defined(XMemoryStream_h)
#define	XMemoryStream_h

#include "XTypeDef.h"
#include <QColor>
#include <QString>
#include <QStringList>
#include "XYCross.h"

class	XDateTime;

class	XMemoryStream
{
	BYTE	*Point;
	uint32	AllocSize;
	uint32	WCurrentPoint;
	uint32	RCurrentPoint;

public:
	XMemoryStream(void);
	XMemoryStream(const XMemoryStream &src);
	~XMemoryStream(void);

	XMemoryStream	&operator=(const XMemoryStream &src);

	bool	Save(BYTE *p ,uint32 size);
	bool	Save(char c);
	bool	Save(BYTE c);
	bool	Save(short c);
	bool	Save(int c);
	bool	Save(int64 c);
	bool	Save(float c);
	bool	Save(double c);
	bool	Save(const QColor &c);
	bool	Save(const QRgb &s);
	bool	Save(const QString &s);
	bool	Save(const QStringList &c);
	bool	Save(const XDateTime &d);
	bool	Save(const XYData &d);

	bool	Load(BYTE *p ,uint32 size);
	bool	Load(char &c);
	bool	Load(BYTE &c);
	bool	Load(short &c);
	bool	Load(int &c);
	bool	Load(int64 &c);
	bool	Load(float &c);
	bool	Load(double &c);
	bool	Load(QColor &c);
	bool	Load(QRgb &s);
	bool	Load(QString &s);
	bool	Load(QStringList &c);
	bool	Load(XDateTime &d);
	bool	Load(XYData &d);

	bool	SeekR(int Pos);
	bool	SeekW(int Pos);
	bool	Clear(void);

private:
	bool	Realloc(int AppendedSize);
};


#endif