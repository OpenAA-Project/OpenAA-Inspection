#if	!defined(XLANGUAGEMANAGER_H)
#define	XLANGUAGEMANAGER_H

#include <QString>
#include <QStringList>
#include "NListComp.h"
#include <QIODevice>
#include "XLanguageStockerLoader.h"
#include "XLanguageCodec.h"
#include <QProgressBar>

class	DefaultParam
{
public:
	QString		DefaultLNGPath;

	DefaultParam(void);
};

class	ProjectLanguage : public NPListSaveLoad<ProjectLanguage>
{
	LanguagePackage		LPackage;
public:
	QString		ProjectName;
	QStringList	ExcelFiles;
	QString		OutputLNGFile;

	ProjectLanguage(void){}

	QString	GetLngFileName(void);
	bool	Execute(LanguagePack &LangPack,QProgressBar *Bar ,QString &ErrorMsg);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
private:
	bool	LoadExcel(const QString &ExcelFileName ,LanguagePack &LangPack ,LanguagePackage::LanguageComponent *DestL);
};

class	SolutionLanguage : public NPListPackSaveLoad<ProjectLanguage>
{
	static	QString	DefaultFileName;
public:

	SolutionLanguage(void){}

	int		Search(const QString &ProjName);
	ProjectLanguage	*Create(void)	{	return new ProjectLanguage();	}
	void	Clear(void);
	QString	GetDefaultFileName(void)	{	return DefaultFileName;	}

	bool	SaveDefault(void);
	bool	LoadDefault(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



#endif