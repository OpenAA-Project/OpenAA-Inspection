#if	!defined(XMERGEXLSX_H)
#define	XMERGEXLSX_H

#include "XExcelOperator.h"
#include <QFileInfo>
#include "XExcelOperator.h"
#include "XLanguageCodec.h"
#include "NList.h"

class	CombinedXLSX : public NPList<CombinedXLSX>
{
	QStringListListXLSX	Dest0;	//Sheet0
	QStringListListXLSX	Dest1;	//Sheet1
	QStringListListXLSX	Source;

	class	StringLine : public NPList<StringLine>
	{
	public:
		QString		FileLS;
		QString		ID;
		int			Row;
	};
	NPListPack<StringLine>	StringLineContainer;

	class	UILine : public NPList<UILine>
	{
	public:
		QString		ClassName;
		QString		TypeName;
		QString		ObjectName;
		QString		PropertyName;
		QString		Str1;
		int			Row;
	};
	NPListPack<UILine>	UILineContainer;

public:
	QFileInfo	DestFile;
	QFileInfo	SourceFile;
	bool		Result;

	CombinedXLSX(QFileInfo &Dest ,QFileInfo &Src);

	bool	Load(void);
	bool	Merge(int LangNo);
	bool	SaveToDest(LanguagePack &LangPack);

	QString	GetDestFileName(void);
	QString	GetSourceFileName(void);

private:
	StringLine	*SearchString(QString &FileLS ,QString &ID);
	UILine		*SearchUI( QString &ClassName
							,QString &TypeName
							,QString &ObjectName
							,QString &PropertyName
							,QString &Str1);
};

#endif