/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XFileRegistry.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XFILEREGISTRY_H)
#define	XFILEREGISTRY_H

#include "NList.h"
#include <QIODevice>
#include <QString>
#include <QColor>
#include <QStringList>
#include <QImage>
#include "XDateTime.h"
#include "XTypeDef.h"

class	FileRegistry
{
	QString	FileName;

public:
	FileRegistry(const QString &filename);

	bool	Save(const QString &keyword ,int data);
	bool	Save(const QString &keyword ,const QString &data);
	bool	Save(const QString &keyword ,const QStringList &data);
	bool	Save(const QString &keyword ,bool data);
	bool	Save(const QString &keyword ,double data);
	bool	Save(const QString &keyword ,void *data ,int databyte);
	bool	Save(const QString &keyword ,const QImage &Img);
	bool	Save(const QString &keyword ,const QColor &data);
	bool	Save(const QString &keyword ,const QRect &data);
	bool	Save(const QString &keyword ,const XDateTime &data);

	int			LoadRegInt			(const QString &keyword	,int DefaultValue	=0);
	QString		LoadRegString		(const QString &keyword	,const QString &DefaultValue=QString());
	QStringList	LoadRegStringList	(const QString &keyword	,const QStringList &DefaultValue=QStringList());
	bool		LoadRegBool			(const QString &keyword	,bool DefaultValue=true);
	double		LoadRegDouble		(const QString &keyword	,double DefaultValue=0.0);
	void		*LoadRegBuffer		(const QString &keyword	,int &databyte);
	QImage		LoadRegImage		(const QString &keyword);
	QColor		LoadRegColor		(const QString &keyword	,const QColor &DefaultValue=Qt::black);
	QRect		LoadRegRect			(const QString &keyword);
	XDateTime	LoadRegDateTime		(const QString &keyword);

	QString	GetFileName(void)	{	return FileName;	}

private:
	class	RegistryLeaf : public NPList<RegistryLeaf>
	{
	public:
		enum	DataType{
			_Int			=0
			,_String		=1
			,_StringList	=2
			,_Bool			=3
			,_Double		=4
			,_BYTEAlloc		=5
			,_Image			=6
			,_Color			=7
			,_Rect			=8
			,_DateTime		=9
		}DType;
		union{
			int32		*DataInt;
			BYTE		*DataString;
			BYTE		*DataStringList;
			bool		*DataBool;
			double		*DataDouble;
			BYTE		*DataAlloc;
			BYTE		*DataImage;
			QRgb		*DataColor;
			QRect		*DataRect;
			BYTE		*DataDateTime;
		};
		//void	*Data;
		int32	DataLen;
		QString	Keyword;

		RegistryLeaf(void);
		virtual	~RegistryLeaf(void);

		void	DeleteData(void);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);

		bool	Set(int data);
		bool	Set(const QString &data);
		bool	Set(const QStringList &data);
		bool	Set(bool data);
		bool	Set(double data);
		bool	Set(void *data ,int databyte);
		bool	Set(const QImage &data);
		bool	Set(const QColor &data);
		bool	Set(const QRect &data);
		bool	Set(const XDateTime &data);

		int			GetInt			(void);
		QString		GetString		(void);
		QStringList	GetStringList	(void);
		bool		GetBool			(void);
		double		GetDouble		(void);
		void		*GetBuffer		(int &databyte);
		QImage		GetImage		(void);
		QColor		GetColor		(void);
		QRect		GetRect			(void);
		XDateTime	GetDateTime		(void);
	};
	NPListPack<RegistryLeaf>	LeafContainer;

	bool	LoadContainer(void);
	bool	SaveContainer(void);
};


#endif