#if	!defined(XLANGUAGECODEC_H)
#define	XLANGUAGECODEC_H

#include <QString>
#include <QStringList>
#include "NListComp.h"
#include <QIODevice>

class	QTextCodec;

class	LanguageClass : public NPListSaveLoad<LanguageClass>
{
public:
	int		ColumnNo;
	QString	LanguageName;
	QString	ExcelFont;
	QString	QtCotec;

	QTextCodec	*CurrentCodec;

	LanguageClass(void){	ColumnNo=0;	CurrentCodec=NULL;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	LanguagePack : public NPListPackSaveLoad<LanguageClass>
{
	static	QString	DefaultFileName;
public:
	LanguagePack(void){}

	LanguageClass	*Create(void)	{	return new LanguageClass();		}

	bool	SaveDefault(void);
	bool	LoadDefault(void);

	void	AllocCodec(void);
	void	SetCodec(int n);
};


#endif