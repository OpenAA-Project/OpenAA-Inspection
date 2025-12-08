#include "XTypeDef.h"
#include "XGeneralFuncCore.h"
#include <stdio.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include "XYCross.h"
#include <omp.h>
//#include "swap.h"
#include <QTextCodec>
#include <QDateTime>
#include <QBitArray>
#include <QBuffer>
#include <QDir>
#include <QRegularExpression>
#include "XIntClass.h"
#include "XDateTime.h"


QString	FuncCall	GetDynamicFileExt(void)
{
#ifdef Q_OS_WIN
	return("DLL");
#else
	return("so");
#endif
}

//============================================================================
QObject	* FuncCall	SearchNested(QObject *Root ,const QString &objectName)
{
	if(Root->objectName()==objectName){
		return Root;
	}
	for(int i=0;i<Root->children().count();i++){
		QObject	*ret=SearchNested(Root->children()[i],objectName);
		if(ret!=NULL){
			return ret;
		}
	}
	return NULL;
}

QString	FuncCall	TransformPathName(const QString &Str)
{
	QString	s=Str;
	return s.replace(QString(/**/"\\"),::GetSeparator());
}
//============================================================================
bool	FuncCall	Save(QIODevice *f,int8 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,int32 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,uint32 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *f,int64 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,WORD d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,short d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,DWORD d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,BYTE d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,char d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,float d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,double d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *f,bool d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,bool3 d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const char *d,int64 Len)
{
	if(f->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(f->write((const char *)d,Len)!=Len){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *file,const QString &d)
{
	int32	Len=d.length()*2;
	if(file->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(file->write((const char *)d.constData(),Len)!=Len){
		return(false);
	}
	return(true);
}

bool	FuncCall	Save(QIODevice *f,const XYData &d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return(true);
}
bool	FuncCall	Save(QIODevice *f,const QDateTime &d)
{
	WORD	wyear	=d.date().year();
	BYTE	wmonth	=d.date().month();
	BYTE	wday	=d.date().day();
	BYTE	whour	=d.time().hour();
	BYTE	wminute	=d.time().minute();
	BYTE	wsec	=d.time().second();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const XDateTime &d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const QPoint &d)
{
	int32	P[2];
	P[0]=d.x();
	P[1]=d.y();

	if(f->write((const char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const QPointF &d)
{
	double	P[2];
	P[0]=d.x();
	P[1]=d.y();

	if(f->write((const char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,const QSize &d)
{
	int32	P[2];
	P[0]=d.width();
	P[1]=d.height();

	if(f->write((const char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	return true;
}



bool	FuncCall	Save(QIODevice *f,const QDate &d)
{
	WORD	wyear	=d.year();
	BYTE	wmonth	=d.month();
	BYTE	wday	=d.day();

	if(::Save(f,wyear)==false){
		return false;
	}
	if(::Save(f,wmonth)==false){
		return false;
	}
	if(::Save(f,wday)==false){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *f,const QTime &d)
{
	BYTE	whour	=d.hour();
	BYTE	wminute	=d.minute();
	BYTE	wsec	=d.second();

	if(::Save(f,whour)==false){
		return false;
	}
	if(::Save(f,wminute)==false){
		return false;
	}
	if(::Save(f,wsec)==false){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *f,const QChar &d)
{
	ushort	unicode=d.unicode();
	if(::Save(f,unicode)==false)
		return false;
	return true;
}

/*
bool	FuncCall	Save(QIODevice *f,QRgb &d)
{
	if(f->write((const char *)&d,sizeof(d))!=sizeof(d))
		return(false);
	return true;
}
*/

bool	FuncCall	Save(QIODevice *f,const QByteArray &d)
{
	int64	Len=d.size();
	if(::Save(f,Len)==false){
		return false;
	}
	if(f->write(d)!=Len){
		return false;
	}
	return true;
}

bool	FuncCall	Save(QIODevice *f,const QByteArrayList &d)
{
	int32	Count=d.count();
	if(::Save(f,Count)==false){
		return false;
	}
	for(int i=0;i<Count;i++){
		QByteArray	a=d[i];
		int64	Len=a.size();
		if(::Save(f,Len)==false){
			return false;
		}
		if(f->write(a)!=Len){
			return false;
		}
	}
	return true;
}
bool	FuncCall	Save(QIODevice *f,BYTE **Point ,int XLen ,int YLen)
{
	for(int y=0;y<YLen;y++){
		if(f->write((const char *)Point[y],XLen)!=XLen){
			return false;
		}
	}
	return true;
}
bool	FuncCall	SaveText(QIODevice *f,char *s)
{
	int	Len=strlen(s);
	if(f->write((const char *)s,Len)!=Len){
		return false;
	}
	return true;
}


bool	FuncCall	Load(QIODevice *file,QString &d)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	
	char	LocalBuff[2000];
	char	*Buff;
	if((Len+1)>=2000){
		Buff=new char[Len+10];
	}
	else{
		Buff=LocalBuff;
	}
	if(file->read((char *)Buff,Len)!=Len){
		if(Buff!=LocalBuff){
			delete	[]Buff;
		}
		return(false);
	}
	Buff[Len]=0;
	d=/**/"";
	QChar *p=(QChar *)Buff;
	for(int i=0;i<Len;i+=2,p++){ 
		d+=*p;
	}
	if(Buff!=LocalBuff){
		delete	[]Buff;
	}
	return(true);
}

bool	FuncCall	Save(QIODevice *file,const char *d)
{
	int32	Len=strlen(d);
	if(file->write((const char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(file->write((const char *)d,Len)!=Len){
		return(false);
	}
	return true;
}
char	* FuncCall	LoadStringInQString(QIODevice *file)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return NULL;
	}
	
	char	*Buff=new char[Len+1];
	if(file->read((char *)Buff,Len)!=Len){
		delete	[]Buff;
		return NULL;
	}
	char	*RetBuff=new char[Len/2+1];
	QChar *p=(QChar *)Buff;
	for(int i=0;i<Len;i+=2,p++){ 
		RetBuff[i/2]=p->cell();
	}
	delete	[]Buff;
	RetBuff[Len/2]=0;
	return RetBuff;
}
char	* FuncCall	LoadString(QIODevice *file)
{
	int32	Len=0;
	if(file->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return NULL;
	}
	
	char	*Buff=new char[Len+1];
	if(file->read((char *)Buff,Len)!=Len){
		delete	[]Buff;
		return NULL;
	}
	Buff[Len]=0;
	return Buff;
}

bool	FuncCall	Save(QIODevice *file,const QStringList &d)
{
	int32	N=d.count();
	if(file->write((const char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	for(int i=0;i<N;i++){
		QString	A=d.value(i);
		if(::Save(file,A)==false){
			return false;
		}
	}
	return(true);
}
bool	FuncCall	Load(QIODevice *file,QStringList &d)
{
	int32	N;
	if(file->read((char *)&N,sizeof(N))!=sizeof(N)){
		return(false);
	}
	d.clear();
	for(int i=0;i<N;i++){
		QString	A;
		if(::Load(file,A)==false){
			return false;
		}
		d.append(A);
	}
	return(true);
}
bool	FuncCall	Load(QIODevice *f,int8 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,int32 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,long &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	FuncCall	Load(QIODevice *f,uint32 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}

bool	FuncCall	Load(QIODevice *f,int64 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,WORD &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,short &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,DWORD &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,float &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,double &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,BYTE &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,QChar &d)
{
	ushort	unicode;
	if(::Load(f,unicode)==false){
		return false;
	}
	d=QChar(unicode);
	return true;
}
bool	FuncCall	Load(QIODevice *f,char &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,bool &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,bool3 &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return false;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,char *d,int64 &Len ,int64 maxbuffsize)
{
	if(f->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len>maxbuffsize){
		return false;
	}
	if(f->read((char *)d,Len)!=Len){
		return false;
	}
	if(Len+1<maxbuffsize){
		d[Len]=0;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,char *d,int32 &Len ,int32 maxbuffsize)
{
	if(f->read((char *)&Len,sizeof(Len))!=sizeof(Len)){
		return(false);
	}
	if(Len>maxbuffsize){
		return false;
	}
	if(f->read((char *)d,Len)!=Len){
		return false;
	}
	if(Len+1<maxbuffsize){
		d[Len]=0;
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,XYData &d)
{
	if(f->read((char *)&d,sizeof(d))!=sizeof(d)){
		return(false);
	}
	return(true);
}
bool	FuncCall	Load(QIODevice *f,QDateTime &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;
	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	QDate	D(wyear,wmonth,wday);
	QTime	T(whour,wminute,wsec);

	d.setDate(D);
	d.setTime(T);

	return true;
}
bool	FuncCall	Load(QIODevice *f,QDate &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;

	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	d.setDate(wyear,wmonth,wday);

	return true;
}
bool	FuncCall	Load(QIODevice *f,QTime &d)
{
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;

	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	d.setHMS(whour,wminute,wsec);

	return true;
}
bool	FuncCall	Load(QIODevice *f,XDateTime &d)
{
	WORD	wyear	;
	BYTE	wmonth	;
	BYTE	wday	;
	BYTE	whour	;
	BYTE	wminute	;
	BYTE	wsec	;
	if(::Load(f,wyear)==false){
		return false;
	}
	if(::Load(f,wmonth)==false){
		return false;
	}
	if(::Load(f,wday)==false){
		return false;
	}
	if(::Load(f,whour)==false){
		return false;
	}
	if(::Load(f,wminute)==false){
		return false;
	}
	if(::Load(f,wsec)==false){
		return false;
	}
	d.set(wyear,wmonth,wday,whour ,wminute,wsec);
	return true;
}

bool	FuncCall	Load(QIODevice *f,QByteArray &d)
{
	int64	Len;
	if(::Load(f,Len)==false){
		return false;
	}
	d=f->read(Len);
	if(d.size()!=Len){
		return false;
	}
	return true;
}

bool	FuncCall	Load(QIODevice *f,QByteArrayList &d)
{
	d.clear();
	int32	Count;
	if(::Load(f,Count)==false){
		return false;
	}
	for(int i=0;i<Count;i++){
		int64	Len;
		if(::Load(f,Len)==false){
			return false;
		}
		QByteArray	a=f->read(Len);
		if(a.size()!=Len){
			return false;
		}
		d.append(a);
	}
	return true;
}

bool	FuncCall	Load(QIODevice *f,BYTE **Point ,int XLen ,int YLen)
{
	for(int y=0;y<YLen;y++){
		if(f->read((char *)Point[y],XLen)!=XLen){
			return false;
		}
	}
	return true;
}
bool	FuncCall	Load(QIODevice *f,QPoint &d)
{
	int32	P[2];

	if(f->read((char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	d.setX(P[0]);
	d.setY(P[1]);
	return true;
}
bool	FuncCall	Load(QIODevice *f,QPointF &d)
{
	double	P[2];

	if(f->read((char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	d.setX(P[0]);
	d.setY(P[1]);
	return true;
}
bool	FuncCall	Load(QIODevice *f,QSize &d)
{
	int32	P[2];

	if(f->read((char *)P,sizeof(P))!=sizeof(P)){
		return false;
	}
	d.setWidth (P[0]);
	d.setHeight(P[1]);
	return true;
}

QString FuncCall	ForceDirectories( const QString &path )
{
	const	char delim = '/';
	QStringList dirs = (path).split(QRegularExpression("[/\\\\]"), Qt::SkipEmptyParts);
	if(dirs.count()==0)
		return path;
	if(path.left(2)=="//" || path.left(2)=="\\\\"){
		QString	sDir=QString("//")+dirs[0];
		for(int i=1; i<dirs.count(); i++){
			QDir dir(sDir);
			sDir+=delim;
			sDir+=dirs[i];
			dir.mkdir(dirs[i]);
		}
		return sDir;
	}
	else{
		//QDir dir(dirs[0] + delim);
		QDir dir;
		for(int i=0; i<dirs.count(); i++){
			if(!dir.exists(dirs[i])){
				if(!dir.mkdir(dirs[i])){
					return dir.path();
				}
			}
			if(!dir.cd(dirs[i])){
				return dir.path();
			}
		}
		return dir.path();
	}
}

QStringList	FuncCall	FindFiles(const QString &dir ,const QString &FileFilter)
{
	QStringList	Ret;

	QString	NowCD;
	NowCD=QDir::currentPath();

	QDir	LDir(dir);
	if(LDir.cd(dir)==true){

		QStringList	FileFilterList;
		FileFilterList.append(FileFilter);
		QStringList	List=LDir.entryList(FileFilterList,QDir::NoDotAndDotDot | QDir::Files);
		for(int i=0;i<List.count();i++){
			Ret+=dir+QDir::separator()+List[i];
		}

		QStringList	Filter;
		Filter.append("*");
		QStringList	DirList=LDir.entryList(Filter,QDir::NoDotAndDotDot | QDir::Dirs);
		for(int i=0;i<DirList.count();i++){
			QString	PathName=dir+QDir::separator()+DirList[i];
			QStringList	r=FindFiles(PathName,FileFilter);
			Ret.append(r);
		}
		QDir::setCurrent(NowCD);
	}
	return Ret;
}

bool	FuncCall	RemoveAllInFolder(const QString& folder, bool DeleteSubFolder)
{
	bool	Ret=true;

	QDir	cd(folder);
	QStringList	List=cd.entryList(QDir::Files | QDir::NoDotAndDotDot);
	for(int i=0;i<List.count();i++){
		QString	FileName= folder
						+ QDir::separator()
						+ List[i];
		if(QFile::remove(FileName)==false){
			Ret=false;
		}
	}
	if(DeleteSubFolder==true){
		QStringList	SList = cd.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
		for (int i = 0; i < SList.count(); i++) {
			QString	SubFolder=folder
							+ QDir::separator()
							+ SList[i];
			if(RemoveAllInFolder(SubFolder, DeleteSubFolder)==false){
				Ret=false;
			}
			else{
				if(cd.rmdir(SList[i])==false){
					Ret = false;
				}
			}
		}
	}
	return Ret;
}

char *ItoA(int value,char *str,int radix)
{
	if(value<0){
		value=-value;
		*str='-';
		str++;
	}
	int	d=1;
	int	Comp=0;
	for(int	i=0;i<32;i++){
		if(d>value){
			break;
		}
		Comp=d;
		d*=radix;
	}
	while(Comp>0){
		int	k=value/Comp;
		*str = "0123456789abcdef"[k];
		value-=k*Comp;
		str++;
		Comp/=radix;
	}
	return str;
}