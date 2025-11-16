/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XGeneralFunc.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XGENERALFUNC_H
#define XGENERALFUNC_H

#include<QtGui>
#include<QIODevice>
#include<QByteArray>
#include<QThread>
#include<QStackedWidget>
#include"XTypeDef.h"
#include"XYCross.h"
#include<QTableWidget>
#include<QVariant>
#include<QListWidget>

class	QIODevice;
class	QString;
class	IntList;
class	QDateTime;
class	XDateTime;
class	QChar;

#define	mhypot(x,y)		sqrt((double)((x)*(x)+(y)*(y)))

bool	Save(QIODevice *f,int8 d);
bool	Save(QIODevice *f,int32 d);
bool	Save(QIODevice *f,uint32 d);
bool	Save(QIODevice *f,short d);
bool	Save(QIODevice *f,WORD d);
bool	Save(QIODevice *f,DWORD d);
bool	Save(QIODevice *f,float d);
bool	Save(QIODevice *f,double d);
bool	Save(QIODevice *f,BYTE d);
bool	Save(QIODevice *f,const QChar &d);
bool	Save(QIODevice *f,char d);
bool	Save(QIODevice *f,bool d);
bool	Save(QIODevice *f,bool3 d);
bool	Save(QIODevice *f,char *d);
bool	Save(QIODevice *f,const QString &d);
bool	Save(QIODevice *f,const QStringList &d);
bool	Save(QIODevice *f,const XYData &d);
bool	Save(QIODevice *f,const QDateTime &d);
bool	Save(QIODevice *f,const QDate &d);
bool	Save(QIODevice *f,const QTime &d);
bool	Save(QIODevice *f,const XDateTime &d);
bool	Save(QIODevice *f,const QColor &d);
//bool	Save(QIODevice *f,QRgb &d);
bool	Save(QIODevice *f,const QByteArray &d);
bool	Save(QIODevice *f,BYTE **Point ,int XLen ,int YLen);
bool	Save(QIODevice *f,const QImage &d);
bool	SaveText(QIODevice *f,char *s);
bool	Save(QIODevice *f,const QVariant &d);
bool	Save(QIODevice *f,const QPoint &d);

bool	Load(QIODevice *f,int8 &d);
bool	Load(QIODevice *f,int32 &d);
bool	Load(QIODevice *f,long &d);
bool	Load(QIODevice *f,uint32 &d);
bool	Load(QIODevice *f,short &d);
bool	Load(QIODevice *f,WORD &d);
bool	Load(QIODevice *f,float &d);
bool	Load(QIODevice *f,double &d);
bool	Load(QIODevice *f,QChar &d);
bool	Load(QIODevice *f,DWORD &d);
bool	Load(QIODevice *f,BYTE &d);
bool	Load(QIODevice *f,char &d);
bool	Load(QIODevice *f,bool &d);
bool	Load(QIODevice *f,bool3 &d);
bool	Load(QIODevice *f,char *d,int32 &len ,int32 maxbuffsize);		//Save(QIODevice *file,char *d)に対するLoad
bool	Load(QIODevice *f,QString &d);
char	*LoadStringInQString(QIODevice *file);
char	*LoadString(QIODevice *file);			//Load data which is saved by "Save(QIODevice *f,char *d);"
bool	Load(QIODevice *f,QStringList &d);
bool	Load(QIODevice *f,XYData &d);
bool	Load(QIODevice *f,QDateTime &d);
bool	Load(QIODevice *f,QDate &d);
bool	Load(QIODevice *f,QTime &d);
bool	Load(QIODevice *f,XDateTime &d);
bool	Load(QIODevice *f,QColor &d);
bool	Load(QIODevice *f,QImage &d);
//bool	Load(QIODevice *f,QRgb &d);
bool	Load(QIODevice *f,QByteArray &d);
bool	Load(QIODevice *f,BYTE **Point ,int XLen ,int YLen);
bool	Load(QIODevice *f,QVariant &d);
bool	Load(QIODevice *f,QPoint &d);

QString ForceDirectories( QString path ); 
    //Delphiの関数と動作は同じ 返値は違う
    //引数のパスを自動的に作る
    //成功の可否に関わらず作成できたところまでのパスを返す
QStringList	FindFiles(const QString &dir ,const QString &FileFilter);

int	QString2Char(const QString &str ,char *buff ,int buffsize);
int32	StrToInt32(char *buff);
void	Int32ToStr(int32 ,char *buff);
double	StrToDouble(char *buff);
QString	QColor2QString(const QColor &c);
QColor	QString2QColor(const QString &str);
QByteArray	QString2ByteArray(const QString &str);
QString		QByteArray2QString(QByteArray &B);
int matchscanf(char *buff,char *form,...);
bool	IsEqual(const QDateTime &d1 ,const QDateTime &d2);
bool	IsEqual(const QStringList &L1,const QStringList &L2);
void	ChangePathSeparator(char Dest ,char Src ,char *PathName);
void	RemoveFiles(const QString &FileNameWithWildcard);
double	GetRGBBrightness(QRgb a);

void	AddAlphaChannel(QImage &image, int alpha);
void	MultiplyImage(QImage &image, double Multiply);
void	CopyPixels(QImage &dest, QImage &src ,int OffsetX ,int OffsetY);
void	ExtendImage(QImage &dest, QImage &src ,double zx ,double zy);
void	RotateImage(QImage &dest, QImage &src ,double s);
void	SlopeXImage(QImage &dest, QImage &src ,double s ,int cx ,int cy);
void	SlopeYImage(QImage &dest, QImage &src ,double s ,int cx ,int cy);
void	CopyPixelsWithAlpha(QImage &dest, QImage &src);
void	CopyPixelsWithAlpha(QImage &dest, QImage &src,int alpha);
void	DrawLine(QImage &dest,QRgb col ,int x1, int y1 ,int x2 ,int y2);

void	GSleep(unsigned int milisec);
QTableWidgetItem	*SetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value ,Qt::ItemFlags flags=Qt::NoItemFlags);
QString	GetDataToTable(QTableWidget *W ,int col ,int row);
void	SetDataToTableCheckable(QTableWidget *W ,int col ,int row ,const QVariant &value ,bool Checked);
bool	GetCheckedFromTable(QTableWidget *W ,int col ,int row);
void	SetTableColor(QTableWidget *W ,int col ,int row ,const QColor &Col);
int		GetSelectedCurrentRow(QTableWidget *W);
int		GetSelectedRows(QTableWidget *W ,IntList &Rows);
int		GetSelectedRows(QListWidget *W,IntList &Rows);
void	SetSelectedRows(QTableWidget *W ,IntList &Rows);
int		GetBitCount(BYTE *p ,int bytelen);
int		GetBitCount(BYTE p);
bool	SetCurrentIndex(QStackedWidget *W ,const QString &TabName);
QStringList	GetDataFromListWidget(QListWidget *W);

void    DeleteHair(BYTE **bmpdata ,int xbyte,int YLen);
void    DeleteCornerDot(BYTE **bmpdata ,int xbyte ,int YLen);
void    DeleteManyArm(BYTE **data,int xbyte ,int YLen);
void    DeleteIsolatedDot(BYTE **bmpdata ,int xbyte ,int YLen);

void	SetWidgetCenter(QWidget *f);
void	GetObjectPath(QObject * newTarget ,QString &name);
void	XReverseAsm(BYTE *Src ,BYTE *Dst ,int Len);

QString	GetDynamicFileExt(void);
QString	GetSeparator(void);
QObject	*SearchNested(QObject *Root ,const QString &objectName);
void QSort(void* parray, int lenArray ,int datasize,int (*func)(const void *a ,const void *b),bool3 ThreadMode=none3);
QString	TransformPathName(const QString &Str);

void	ErrorOccurs(void);


class	QThreadForWait : public QThread
{
public:
	QThreadForWait(QObject *parent=0):QThread(parent){}

	static	void	MSWait(int milisec){	msleep(milisec);	}
};

int matchscanf(char *buff,char *form,...);
/*	マッチングしながらデータの値を得る

	buff に被抽出文字列バッファを入れる
	form の形式
		%hd	%d	%ld	%c	%lE	%s
		%hi	%i	%li	%f	%lF
		%ho	%o	%lo	%e
		%hu	%u	%lu	%lf
		%hx	%x	%lx	%le
				%D	%F
				%I	%E
				%O
				%U
				%X
		スペース ・・・ １個以上のスペースかタブとマッチングする
		タブ・・・・・	０個以上のスペースかタブとマッチングする
		それ以外の文字	大文字小文字の区別をして１文字ずつマッチングして行く

	リターン
		正：	正常にマッチング終了した。格納した数値の個数が返る
		負：	マッチングが正常に行われなかった。
			格納した数値の個数にー１を掛けたもの ー１ になる。

	正常終了の条件
		抽出した数値が数値の範囲内にある
		文字列がマッチングする
		数値が必要な場所に数値がある
	    これらの条件が form の終わりまで満たされた場合、正常終了となる
*/

#endif