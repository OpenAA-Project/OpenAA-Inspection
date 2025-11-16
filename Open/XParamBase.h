/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XParamBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XGLOBALPARAM_H)
#define	XGLOBALPARAM_H

#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XTypeDef.h"
#include <QColor>
//#include "XServiceForLayers.h"
#include "XColorSpace.h"

class	WEditParameterTab;
class	LayersBase;

#define	ParamEnableDefault			0
#define	ParamEnableInAll			-1
#define	ParamEnableInTransfer		0x1
#define	ParamEnableInLoadOnMaster	0x2
#define	ParamEnableInLoadOnSlave	0x4
#define	ParamEnableInWeakest		0x4000000


class	ParamBase
{
	friend	class	WEditParameterTab;

protected:
	QString	DefaultFileName;
public:
	enum	ParamType{
			 __int64__
			,__int32__
			,__double__
			,__QString__
			,__bool__
			,__FileName__
			,__Path__
			,__QColor__
			,__WORD__
			,__ColorLogic__
			,__QStringList__
			,__ByteArray__
			,__int16__
	};

private:
	//static	char	*DefaultFileName;
public:
	ParamBase(void);
	virtual ~ParamBase(void);

	void	SetParam(WORD    *Value			,const char *Category ,const char *name ,const char *explain=NULL ,WORD MinData=0						,WORD  MaxData=65535					,int EnableCondition=-1);
	void	SetParam(int64   *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int64 MinData=-0x7FFFFFFFFFFFFFFFLU	,int64 MaxData=0x7FFFFFFFFFFFFFFFLU ,int EnableCondition=-1);
	void	SetParam(int32   *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int32 MinData=-0x7FFFFFFFLU			,int32 MaxData=0x7FFFFFFFLU			,int EnableCondition=-1);
	void	SetParam(int16   *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int16 MinData=-0x7FFF				,int16 MaxData=0x7FFF			,int EnableCondition=-1);
	void	SetParam(double  *Value			,const char *Category ,const char *name ,const char *explain=NULL ,double MinData=-99999999				,double MaxData=99999999			,int EnableCondition=-1);
	void	SetParam(QString *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParam(bool    *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParam(QColor	 *Value			,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParam(ColorLogic *Value		,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParamFileName(QString *Value ,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParamPath	(QString *Value ,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParam(QStringList *Value		,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);
	void	SetParam(QByteArray *Value		,const char *Category ,const char *name ,const char *explain=NULL ,int EnableCondition=-1);

	void	SetParam(WORD* Value			,const char* Category, const char* name, const QString &explain, WORD MinData = 0, WORD MaxData = 65535, int EnableCondition = -1);
	void	SetParam(int64* Value			,const char* Category, const char* name, const QString &explain, int64 MinData = -0x7FFFFFFFFFFFFFFFLU, int64 MaxData = 0x7FFFFFFFFFFFFFFFLU, int EnableCondition = -1);
	void	SetParam(int32* Value			,const char* Category, const char* name, const QString &explain, int32 MinData = -0x7FFFFFFFLU, int32 MaxData = 0x7FFFFFFFLU, int EnableCondition = -1);
	void	SetParam(int16* Value			,const char* Category, const char* name, const QString &explain, int16 MinData = -0x7FFF, int16 MaxData = 0x7FFF, int EnableCondition = -1);
	void	SetParam(double* Value			,const char* Category, const char* name, const QString &explain, double MinData = -99999999, double MaxData = 99999999, int EnableCondition = -1);
	void	SetParam(QString* Value			,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParam(bool* Value			,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParam(QColor* Value			,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParam(ColorLogic* Value		,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParamFileName(QString* Value	,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParamPath(QString* Value		,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParam(QStringList* Value		,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);
	void	SetParam(QByteArray* Value		,const char* Category, const char* name, const QString &explain, int EnableCondition = -1);

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1);
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1);
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1);

	bool	SaveDefault(const QString &UserPath);
	bool	LoadDefault(const QString &UserPath);
	bool	LoadDefault(const QString &UserPath,int StartPoint ,int EndPoint);
	bool	LoadFromFile(const QString &filename);
	bool	LoadFromFile(const QString &filename,int StartPoint ,int EndPoint);
	bool	SaveToFile(const QString &filename);
	virtual	bool	WriteEnableToDefaultFile(void){	return true;	}

	virtual	QString	GetDataText(void)=0;
	virtual	QString	GetSavedFileName(void);
	virtual	void	SetDefaultFileName(const QString &defaultfilename);

	void	CopyFrom(ParamBase &src);
	int		GetCount(void);

	virtual	void	Push(void);
	virtual	void	Pop(void);
	virtual	bool	IsChangedCritically(const QString &name);

	void	SetCategoryLanguage(const QString &OriginalCategory,const QString &CurrentCategory);
	QString	GetCategoryLabel(const QString &OriginalCategory);

	class	ParamStruct : public NPList<ParamStruct>
	{
		bool		DeleteMode;
		union{
			int64		VarInt64;
			int32		VarInt32;
			int16		VarInt16;
			WORD		VarWord;
			double		VarDouble;
			bool		VarBool;
		};
		QString		VarString;
		QColor		VarColor;
		ColorLogic	VarColorLogic;
		QStringList	VarStringList;
		QByteArray	VarByteArray;
	public:
		//void		*pVar;
		union{
			int64		*pVarInt64;
			int32		*pVarInt32;
			int16		*pVarInt16;
			WORD		*pVarWord;
			double		*pVarDouble;
			QString		*pVarString;
			bool		*pVarBool;
			QColor		*pVarColor;
			ColorLogic	*pVarColorLogic;
			QStringList	*pVarStringList;
			QByteArray	*pVarByteArray;
		};

		ParamType	rType;
		QString		Category;
		QString		Name;
		QString		Explain;
		int			EnableCondition;
		long	double	MinData;
		long	double	MaxData;
		ParamBase	*Parent;

		ParamStruct(ParamBase *parent,int64	*value		,const char *Category ,const char *name ,int64  minData ,int64  maxData,const char *explain);
		ParamStruct(ParamBase *parent,int32	*value		,const char *Category ,const char *name ,int32  minData ,int32  maxData,const char *explain);
		ParamStruct(ParamBase *parent,int16	*value		,const char *Category ,const char *name ,int16  minData ,int16  maxData,const char *explain);
		ParamStruct(ParamBase *parent,WORD	*value		,const char *Category ,const char *name ,WORD   minData ,WORD   maxData,const char *explain);
		ParamStruct(ParamBase *parent,double*value		,const char *Category ,const char *name ,double minData ,double maxData,const char *explain);
		ParamStruct(ParamBase *parent,QString *value	,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,bool	*value		,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,QColor*value		,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,ColorLogic  *Value,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,QStringList *value,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,QByteArray *value	,const char *Category ,const char *name ,const char *explain);
		ParamStruct(ParamBase *parent,char *TxBuff);
		ParamStruct(ParamBase *parent,ParamStruct &src);

		ParamStruct(ParamBase* parent,int64* value		,const char* Category ,const char* name, int64  minData, int64  maxData, const QString &explain);
		ParamStruct(ParamBase* parent,int32* value		,const char* Category ,const char* name, int32  minData, int32  maxData, const QString& explain);
		ParamStruct(ParamBase* parent,int16* value		,const char* Category ,const char* name, int16  minData, int16  maxData, const QString& explain);
		ParamStruct(ParamBase* parent,WORD* value		,const char* Category ,const char* name, WORD   minData, WORD   maxData, const QString& explain);
		ParamStruct(ParamBase* parent,double* value		,const char* Category ,const char* name, double minData, double maxData, const QString& explain);
		ParamStruct(ParamBase* parent,QString* value	,const char* Category ,const char* name, const QString& explain);
		ParamStruct(ParamBase* parent,bool* value		,const char* Category ,const char* name, const QString& explain);
		ParamStruct(ParamBase* parent,QColor* value		,const char* Category ,const char* name, const QString& explain);
		ParamStruct(ParamBase* parent,ColorLogic* Value	,const char* Category ,const char* name, const QString& explain);
		ParamStruct(ParamBase* parent,QStringList* value,const char* Category ,const char* name, const QString& explain);
		ParamStruct(ParamBase* parent,QByteArray* value	,const char* Category ,const char* name, const QString& explain);
		~ParamStruct(void);

		QString	GetValue(void);
		QStringList	GetStringList(void);

		bool	GetString(char buff[],int Len);
		bool	SetValue(ParamStruct &Dest);
		void	SetValue(const QString &str);
		void	SetValue(const QColor &col);
		void	SetValue(const ColorLogic &col);
		void	SetBoolValue(bool value);
		void	SetValue(const QStringList &str);
		void	SetValue(const QByteArray &barray);

		QByteArray	GetByteArray(void);

		long	double	Clip(long double data);
	};
protected:
	class	CategoryLanguageList : public NPList<CategoryLanguageList>
	{
		QString	OriginalCategory;
		QString	CurrentCategory;

	public:
		CategoryLanguageList(const QString &OriginalCategory,const QString &CurrentCategory);
		QString	GetCurrentCategory(void);
		QString	GetOriginalCategory(void);
	};

	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data){}

protected:
	NPListPack<ParamStruct>				ParamData;
	NPListPack<ParamStruct>				LastParamData;
	NPListPack<CategoryLanguageList>	CategoryContainer;

	ParamStruct	*Search(const QString &Category ,const QString &Name);
	virtual	QString	GetDefaultFileName(void)=0;
public:
	int		GetParamCount(void)	{	return ParamData.GetCount();	}
};

inline	int		ParamBase::GetCount(void)
{
	return ParamData.GetCount();
}



class	ParamBaseForAlgorithm : public ParamBase
{
public:
	ParamBaseForAlgorithm(void);
	virtual ~ParamBaseForAlgorithm(void);
	virtual	QString	GetDataText(void)			override;
	virtual	QString	GetDefaultFileName(void)	override;
};

#endif


