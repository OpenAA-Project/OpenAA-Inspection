/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\XLanguageSolver.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XLANGUAGESOLVER_H)
#define	XLANGUAGESOLVER_H

//
//	１：文字列自動置換
//		"XXX"
//		LangSolver.GetString(FileBaseName_LS,LID_nn)/*"XXX"*/
//
//	２：Include自動挿入
//		#include <LangSolver.h>
//
//	３：リソースファイル自動生成
//		struct	LangSolverResourceStruct	LangSolverData[]={
//					{	FileBaseName_LS,LID_nn	,"XXX","YYY",...},

//	４：uiファイルリソース置換

#include "NList.h"
#include <QStringList>
#include <QString>
#include <QDomElement>
#include <QDomNode>
#include "XLanguageClass.h"

class	SourceAnalyzeParser;
class	LanguageStocker;



class	LanguageString : public NPList<LanguageString>
{
	friend	class	LanguageStocker;
	QStringList	Data;	//Unicode
public:
	LanguageString(void){}

	bool	SaveResource(QIODevice &File);
	char	*LoadResourceFromString(char *fp);

	bool	SaveCSVFile(QString &FStr);
	bool	LoadCSVFile(QString &FStr);
	QString	GetFirstString(void){	return Data.value(0);	}

	bool	operator==(LanguageString &src);

private:
	char	*Load1Word(char *fp ,char *kword,int kwordlen);

};

class	LanguageBase
{
	friend	class	LanguageStocker;
protected:
	QString						SourceFileName;
	NPListPack<LanguageString>	List;
public:
	LanguageBase(void){}
	QString	GetFileName(void){	return SourceFileName;	}
	LanguageString	*GetLanguageString(int langNo){	return List.GetItem(langNo);	}

};

class	LanguageStringResource : public LanguageBase , public NPList<LanguageStringResource>
{
	friend	class	LanguageStocker;
	int		ID;
public:
	LanguageStringResource(void){	ID=0;	}

	bool	SaveResource(QIODevice &File);
	bool	LoadResource(QIODevice &File ,char Key[100]);

	bool	SaveCSVFile(QStringList &FStr);
	bool	LoadCSVFile(QStringList &FStr);

	bool	SaveHeader(QIODevice &File);
	bool	Compare(LanguageStringResource *dest);

	int		GetID(void){	return ID;	}
};

class	UIStringResource : public LanguageBase , public NPList<UIStringResource>
{
	friend	class	LanguageStocker;

public:
	QString	UIClassName;
	QString	ClassTypeName;
	QString	ControlName;
	QString	PropertyName;

	UIStringResource(void){}

	bool	SaveResource(QIODevice &File);
	bool	LoadResource(QIODevice &File,char Key[100]);

	bool	SaveCSVFile(QStringList &FStr);
	bool	LoadCSVFile(QStringList &FStr);

	bool	SaveHeader(QIODevice &File);
	bool	Compare(UIStringResource *dest);
};

class	LanguageStocker
{
	friend	class	UIStringResource;

public:
	NPListPack<LanguageStringResource>	LStringR;
	NPListPack<UIStringResource>		UIStringR;

	QStringList							CPPFileList;
	QStringList							UIFileList;
	QStringList							LanguageType;

	static	const	char	*SettingFileName;
	char	*CurrentCodec;

	QString								KeywordForLangSolver;
	char	*CodecList[MAXLANGUAGECOUNT];

	LanguageStocker(QString _KeywordForLangSolver);

	bool	SaveSettingFile(void);
	bool	LoadSettingFile(void);
	void	Clear(void);
	void	CopyCodec(LanguageStocker *src);

	void	SetCurrentCodec(char *codec);

	bool	ScanLoadCPPFile(QString CPPFile ,int &ResourceNumb);
	bool	ReplaceCPPFile(QString CPPFile ,QString DstCPPFile,QString ResourceFileName);

	bool	SaveCSVFile(QString CSVFileName);
	bool	LoadCSVFile(QString CSVFileName);

	bool	SaveXLSXFile(QString XLSXFileName);
	bool	LoadXLSXFile(QString XLSXFileName);

	bool	SaveResource(QString RFileName);
	bool	LoadResource(QString RFileName);

	bool	LoadUIFile(QString RFileName);

	bool	SaveHeaderFile(QString RFileName);

private:
	bool	CopyToOld(QString SrcFileName,QString DestFileName);
	bool	MakeCPPParser(QString CPPFile ,NPListPack<SourceAnalyzeParser> &SPack);
	void	GetCommentStrings(NPListPack<LanguageString> &List ,QString &commentStr);
	int		GetEmptyStringID(void);

	void	SearchUIAddText(QDomElement &docElem ,QString &ClassName ,QString AClassStr ,QString ANameStr ,QString APropStr);
	bool	LoadCodec(QIODevice &file,char Buff[]);

	bool	CopyToBak(QString SourceFile);

	bool	ScanCPPFileForInclude(QString CPPFile ,QString ResourceFileName);
	bool	ReplaceCPPFileForInclude(QString CPPFile ,QString ResourceFileName);
};



#endif