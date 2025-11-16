#include "XTypeDef.h"
#include <cmath>
#include "XMemoryStream.h"
#include "XGeneralFunc.h"
#include "XDateTime.h"

const	int	MinBuffSize	=1024;

XMemoryStream::XMemoryStream(void)
{
	Point =new BYTE[MinBuffSize];
	AllocSize	=MinBuffSize;
	WCurrentPoint=0;
	RCurrentPoint=0;
}
XMemoryStream::XMemoryStream(const XMemoryStream &src)
{
	AllocSize		=src.AllocSize;
	Point =new BYTE[AllocSize];
	WCurrentPoint	=src.WCurrentPoint	;
	RCurrentPoint	=src.RCurrentPoint	;
	memcpy(Point,src.Point,AllocSize);
}
XMemoryStream::~XMemoryStream(void)
{
	if(Point!=NULL){
		delete	[]Point;
		Point=NULL;
	}
	AllocSize=0;
	WCurrentPoint=0;
	RCurrentPoint=0;
}

bool	XMemoryStream::Realloc(int AppendedSize)
{
	AllocSize	+=AppendedSize+MinBuffSize;
	BYTE	*d=new BYTE[AllocSize];
	memcpy(d,Point,WCurrentPoint);
	Point=d;
	delete	[]Point;
	return true;
}
XMemoryStream	&XMemoryStream::operator=(const XMemoryStream &src)
{
	if(this!=&src){
		if(Point!=NULL){
			delete	[]Point;
			Point=NULL;
		}
		AllocSize		=src.AllocSize;
		Point =new BYTE[AllocSize];
		WCurrentPoint	=src.WCurrentPoint	;
		RCurrentPoint	=src.RCurrentPoint	;
		memcpy(Point,src.Point,AllocSize);
	}
	return *this;
}
bool	XMemoryStream::Save(BYTE *p ,uint32 size)
{
	if(WCurrentPoint+size>AllocSize){
		Realloc(size);
	}
	memcpy(&Point[WCurrentPoint],p,size);
	WCurrentPoint+=size;
	return true;
}

bool	XMemoryStream::Save(char c)
{
	if(WCurrentPoint+1>AllocSize){
		Realloc(1);
	}
	Point[WCurrentPoint]=c;
	WCurrentPoint++;
	return true;
}

bool	XMemoryStream::Save(BYTE c)
{
	if(WCurrentPoint+1>AllocSize){
		Realloc(1);
	}
	Point[WCurrentPoint]=c;
	WCurrentPoint++;
	return true;
}

bool	XMemoryStream::Save(short c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(int c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(int64 c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(float c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(double c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(const QColor &c)
{
	return Save(c.rgba());
}
bool	XMemoryStream::Save(const QRgb &c)
{
	if(WCurrentPoint+sizeof(c)>AllocSize){
		Realloc(sizeof(c));
	}
	memcpy(&Point[WCurrentPoint],&c,sizeof(c));
	WCurrentPoint+=sizeof(c);
	return true;
}

bool	XMemoryStream::Save(const QString &s)
{
	char	buff[10000];
	QString2Char(s ,buff ,sizeof(buff));
	int32	Len=strlen(buff);
	if(Save(Len)==false)
		return false;
	return Save((BYTE *)buff,Len);
}

bool	XMemoryStream::Save(const QStringList &c)
{
	int32	N=c.count();
	if(Save(N)==false)
		return false;
	for(int i=0;i<N;i++){
		if(Save(c[i])==false)
			return false;
	}
	return true;
}

#pragma	pack(push,1)
struct	TmpXDateTime
{
	BYTE	Year;
	BYTE	Month;
	BYTE	Day;
	BYTE	Hour;
	BYTE	Minute;
	BYTE	Second;
};
#pragma	pack(pop)

bool	XMemoryStream::Save(const XDateTime &d)
{
	struct	TmpXDateTime	TmpDT;
	TmpDT.Year		=d.year();
	TmpDT.Month		=d.month();
	TmpDT.Day		=d.day();
	TmpDT.Hour		=d.hour();
	TmpDT.Minute	=d.minute();
	TmpDT.Second	=d.second();
	if(WCurrentPoint+sizeof(TmpDT)>AllocSize){
		Realloc(sizeof(TmpDT));
	}
	memcpy(&Point[WCurrentPoint],&TmpDT,sizeof(TmpDT));
	WCurrentPoint+=sizeof(TmpDT);
	return true;
}

bool	XMemoryStream::Save(const XYData &d)
{
	if(WCurrentPoint+2*sizeof(int32)>AllocSize){
		Realloc(2*sizeof(int32));
	}
	memcpy(&Point[WCurrentPoint],&d.x,sizeof(int32));
	WCurrentPoint+=sizeof(int32);
	memcpy(&Point[WCurrentPoint],&d.y,sizeof(int32));
	WCurrentPoint+=sizeof(int32);
	return true;
}


bool	XMemoryStream::Load(BYTE *p ,uint32 size)
{
	if(RCurrentPoint+size<=WCurrentPoint){
		memcpy(p,&Point[RCurrentPoint],size);
		RCurrentPoint+=size;
		return true;
	}
	return false;
}

bool	XMemoryStream::Load(char &c)
{
	if(RCurrentPoint+1<=WCurrentPoint){
		c=(char)Point[RCurrentPoint];
		RCurrentPoint++;
		return true;
	}
	return false;
}

bool	XMemoryStream::Load(BYTE &c)
{
	if(RCurrentPoint+1<=WCurrentPoint){
		c=Point[RCurrentPoint];
		RCurrentPoint++;
		return true;
	}
	return false;
}

bool	XMemoryStream::Load(short &c)
{
	if(RCurrentPoint+sizeof(short)<=WCurrentPoint){
		memcpy(&c,&Point[RCurrentPoint],sizeof(short));
		RCurrentPoint+=sizeof(short);
		return true;
	}
	return false;
}

bool	XMemoryStream::Load(int &c)
{
	if(RCurrentPoint+sizeof(int)<=WCurrentPoint){
		memcpy(&c,&Point[RCurrentPoint],sizeof(int));
		RCurrentPoint+=sizeof(int);
		return true;
	}
	return false;
}
bool	XMemoryStream::Load(int64 &c)
{
	if(RCurrentPoint+sizeof(int64)<=WCurrentPoint){
		memcpy(&c,&Point[RCurrentPoint],sizeof(int64));
		RCurrentPoint+=sizeof(int64);
		return true;
	}
	return false;
}
bool	XMemoryStream::Load(float &c)
{
	if(RCurrentPoint+sizeof(float)<=WCurrentPoint){
		memcpy(&c,&Point[RCurrentPoint],sizeof(float));
		RCurrentPoint+=sizeof(float);
		return true;
	}
	return false;
}
bool	XMemoryStream::Load(double &c)
{
	if(RCurrentPoint+sizeof(double)<=WCurrentPoint){
		memcpy(&c,&Point[RCurrentPoint],sizeof(double));
		RCurrentPoint+=sizeof(double);
		return true;
	}
	return false;
}
bool	XMemoryStream::Load(QColor &c)
{
	QRgb	col;
	if(RCurrentPoint+sizeof(col)<=WCurrentPoint){
		memcpy(&col,&Point[RCurrentPoint],sizeof(col));
		RCurrentPoint+=sizeof(col);
		c.setRgba(col);
		return true;
	}
	return false;
}

bool	XMemoryStream::Load(QString &s)
{
	int32	Len;
	if(Load(Len)==false)
		return false;
	char	*buff=new char [Len+1];
	if(Load((BYTE *)buff,Len)==false){
		delete	[]buff;
		return false;
	}
	s=buff;
	delete	[]buff;
	return true;
}

bool	XMemoryStream::Load(QStringList &c)
{
	c.clear();
	int32	N;
	if(Load(N)==false)
		return false;
	for(int i=0;i<N;i++){
		QString	k;
		if(Load(k)==false)
			return false;
		c.append(k);
	}
	return true;
}

bool	XMemoryStream::Load(XDateTime &d)
{
	struct	TmpXDateTime	TmpDT;

	if(RCurrentPoint+sizeof(TmpDT)<=WCurrentPoint){
		memcpy(&TmpDT,&Point[RCurrentPoint],sizeof(TmpDT));
		RCurrentPoint+=sizeof(TmpDT);

		d.set(	TmpDT.Year	
				,TmpDT.Month	
				,TmpDT.Day	
				,TmpDT.Hour	
				,TmpDT.Minute
				,TmpDT.Second);

		return true;
	}
	return false;
}

bool	XMemoryStream::Load(XYData &d)
{
	if(RCurrentPoint+2*sizeof(int32)<=WCurrentPoint){
		memcpy(&d.x,&Point[RCurrentPoint],sizeof(int32));
		RCurrentPoint+=sizeof(int32);
		memcpy(&d.y,&Point[RCurrentPoint],sizeof(int32));
		RCurrentPoint+=sizeof(int32);
		return true;
	}
	return false;
}


bool	XMemoryStream::SeekR(int Pos)
{
	RCurrentPoint=Pos;
	return true;
}

bool	XMemoryStream::SeekW(int Pos)
{
	WCurrentPoint=Pos;
	return true;
}

bool	XMemoryStream::Clear(void)
{
	RCurrentPoint=0;
	WCurrentPoint=0;
	return true;
}