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
#include<QPushButton>
#include<QStringList>

#include"XTypeDef.h"
#include"XYCross.h"
#include<QVariant>
#include<QCheckBox>
#include "XGeneralFuncCore.h"

class	QStackedWidget;
class	QTableWidget;
class	QTableWidgetItem;
class	QTreeWidget;
class	QListWidget;
class	QSpinBox;
class	QDoubleSpinBox;
class	QIODevice;
class	QString;
class	IntList;
class	IntListContainer;
class	QDateTime;
class	XDateTime;
class	QChar;
class	QComboBox;

#ifndef __Random

#define	__Random(N)	((N)*rand()/RAND_MAX)

#endif // __Random


bool		Save(QIODevice* f, const QColor& d);
bool		Save(QIODevice* f, const QImage& d);
bool		Save(QIODevice* f, const QVariant& d);

bool		Load(QIODevice* f, QColor& d);
bool		Load(QIODevice* f, QImage& d);
bool		Load(QIODevice* f, QVariant& d);

int			QString2Char(const QString& str, char* buff, int buffsize);
int64		StrToInt64(char* buff);
void		Int64ToStr(int64, char* buff);
int32		StrToInt32(char* buff);
int16		StrToInt16(char* buff);
void		Int32ToStr(int32, char* buff);
void		Int16ToStr(int16, char* buff);
double		StrToDouble(char* buff);
QString		QColor2QString(const QColor& c);
QColor		QString2QColor(const QString& str);
QColor		GetReverseColor(const QColor& c);
QByteArray	QString2ByteArray(const QString& str);
QString		QByteArray2QString(QByteArray& B);
int			matchscanf(char* buff, char* form, ...);
bool		IsEqual(const QDateTime& d1, const QDateTime& d2);
bool		IsEqual(const QStringList& L1, const QStringList& L2);
void		ChangePathSeparator(char Dest, char Src, char* PathName);
void		RemoveFiles(const QString& FileNameWithWildcard);
qint64		StringToLongLong(char* Str, bool& Ok);
double		GetRGBBrightness(QRgb a);

void	ClearImage(QImage& image, int alpha=0);
void	AddAlphaChannel(QImage& image, int alpha);
void	MultiplyImage(QImage& image, double Multiply);
void	CopyPixels(QImage& dest, QImage& src, int OffsetX, int OffsetY ,int NumThreads=0);
void	MoveZoomImage(QImage& dest, QImage& src, int OffsetX, int OffsetY ,double ZoomRate);
void	ExtendImage(QImage& dest, QImage& src, double zx, double zy);
void	RotateImage(QImage& dest, QImage& src, double s);
void	ExtendImage(QImage& dest, QImage& src, double zx, double zy, int cx, int cy);
void	RotateImage(QImage& dest, QImage& src, double s, int cx, int cy);
void	SlopeXImage(QImage& dest, QImage& src, double s, int cx, int cy);
void	SlopeYImage(QImage& dest, QImage& src, double s, int cx, int cy);
bool	MakeTransformReverse(double d[6],double s[6]);
void	TransformImage(QImage& dest, QImage& src, double m[6]);
void	CopyPixelsWithAlpha(QImage& dest, QImage& src);
void	CopyPixelsWithAlpha(QImage& dest, QImage& src, int alpha);
void	DrawLine(QImage& dest, QRgb col, int x1, int y1, int x2, int y2);
void	DrawRect(QImage& dest, QRgb col, int x1, int y1, int x2, int y2);
void	CombinePixels(QImage& dest, QImage& src, int OffsetX, int OffsetY, int Alpha);
void	AddPixels(QImage& dest, QImage& src, int OffsetX, int OffsetY);
void	DrawImage(QPainter &Pnt ,int PanelXLen ,int PanelYLen
					,const QImage &Img ,int movx ,int movy ,double ZoomRate);
void	DrawImageAlpha(QImage &Pnt
					,const QImage &Img ,int movx ,int movy ,double ZoomRate);
QColor	GetAvrDivColor(const QImage &img ,double dispersion[]);

class	CheckBoxInTable : public QCheckBox
{
	Q_OBJECT
		
	int	Row,Column;
public:
	CheckBoxInTable(int column ,int row);
signals:
	void	SignalChecked(int column,int row ,bool b);
private slots:
	void	SlotChecked(bool b);
};

class	PushButtonInTable : public QPushButton
{
	Q_OBJECT
		
	int	Row,Column;
public:
	PushButtonInTable(int column ,int row);
signals:
	void	SignalClicked(int column,int row);
private slots:
	void	SlotClicked();
};

void			GSleep(unsigned int milisec);
QTableWidgetItem	*SetDataToTable(QTableWidget* W, int col, int row, const QVariant& value, Qt::ItemFlags flags = Qt::NoItemFlags);
QString			GetDataToTable(QTableWidget* W, int col, int row);
CheckBoxInTable	*SetDataToTableCheckable(QTableWidget* W, int col, int row, const QVariant& value, bool Checked);
PushButtonInTable	*SetDataColorToTable(QTableWidget* W, int col, int row, const QColor &Col);
bool			GetCheckedFromTable(QTableWidget* W, int col, int row);
QComboBox		*SetDataToTableComboBox(QTableWidget* W, int col, int row, QStringList& List, int CurrnetIndex);
bool			SetDataToTableComboBoxIndex(QTableWidget* W, int col, int row, int Index);
int				GetDataToTableComboBoxIndex(QTableWidget* W, int col, int row);
QSpinBox		*SetDataToTableSpinBox(QTableWidget* W, int col, int row, int value ,int MinValue=0,int MaxValue=99);
QDoubleSpinBox		*SetDataToTableDoubleSpinBox(QTableWidget* W, int col, int row, double value ,double MinValue=0,double MaxValue=99);
int				GetDataToTableSpinBox(QTableWidget* W, int col, int row);
double			GetDataToTableDoubleSpinBox(QTableWidget* W, int col, int row);
void			SetTableColor(QTableWidget* W, int col, int row, const QColor& Col);
QColor			GetTableColor(QTableWidget* W, int col, int row);
void			SetListColor(QListWidget* W, int row, const QColor& Col);
int				GetSelectedCurrentRow(QTableWidget* W);
int				GetSelectedRows(QTableWidget* W, IntList& Rows);
void			SetCurrentRow(QTableWidget *W, int row);
int				GetSelectedRows(QListWidget *W, IntList& Rows);
void			SetSelectedRows(QTableWidget *W, IntList& Rows);
void			SetSelectedRows(QListWidget *W, IntList& Rows);
void			GetSelectedItems(QTreeWidget *W, IntListContainer &ItemNumber);
void			SetSelectedItems(QTreeWidget *W, IntListContainer &ItemNumber);
int				GetBitCount(BYTE* p, int bytelen);
int				GetBitCount(BYTE p);
bool			SetCurrentIndex(QStackedWidget* W, const QString& TabName);
QStringList		GetDataFromListWidget(QListWidget* W);
void			SetColumnWidthInTable(QTableWidget *table ,int column, int Percentage);

void	SetEnabledForChildren(QObject *b,bool flag);

void    DeleteHair(BYTE** bmpdata, int xbyte, int YLen);
void    DeleteCornerDot(BYTE** bmpdata, int xbyte, int YLen);
void    DeleteManyArm(BYTE** data, int xbyte, int YLen);
void    DeleteIsolatedDot(BYTE** bmpdata, int xbyte, int YLen);

void	SetWidgetCenter(QWidget* f);
void	GetObjectPath(QObject* newTarget, QString& name);
void	GetObjectPath(QObject* newTarget, QStringList& name);
void	XReverseAsm(BYTE* Src, BYTE* Dst, int Len);

bool	CheckHidden(QWidget* v);

void	ErrorOccurs(void);

char	*ToStr(char Text[], int N);
char	*ToStr(char Text[], double N, int Decimal = 6);

inline  int GetHalfUpDown(double k)
{
    return((k>0)?(int)(k+0.5):(int)(k-0.5));
}

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
char *ItoA(int value,char *string,int radix);

#ifndef _MSC_VER
#include <string.h>
inline	int stricmp(const char *s1, const char *s2){	return strcasecmp(s1,s2);	}
inline	int strnicmp(const char *s1, const char *s2, size_t n)	{	return strncasecmp(s1,s2,n);	}

#define	_MAX_DRIVE	3
#define	_MAX_EXT	256
#define	_MAX_FNAME	256
#define	_MAX_DIR	256

#endif

#endif