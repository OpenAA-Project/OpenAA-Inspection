#if	!defined(XLANGUAGESTOCKERLOADER_H)
#define	XLANGUAGESTOCKERLOADER_H

#include <QIODevice>
#include "NListComp.h"
#include "XTypeDef.h"

class	QTextCodec;
class	LSStringResourceDef;
class	LSUIResourceDef;


class	LanguagePackage
{
public:
	class	LanguageComponent : public NPListSaveLoad<LanguageComponent>
	{
		LanguagePackage	*Parent;

	public:
		QString		IDName;

		class	CompString : public NPListSaveLoad<CompString>
		{
		public:
			int32				FileID;
			int32				ID;
			char				**Str;
			int32				AllocStrCount;

			CompString(int32 fileID ,int32 id)	{	Str=NULL;	AllocStrCount=0;	FileID=fileID;	ID=id;	}
			CompString(void)	{	Str=NULL;	AllocStrCount=0;	FileID=-1;	ID=-1;	}
			~CompString(void);

			void	AllocStr(int count);
			void	SetStr(int n ,char *s);

			bool	Save(QIODevice *f);
			bool	Load(QIODevice *f);
		};
		class	CompStringContainer : public NPListPackSaveLoad<CompString>
		{
		public:
			CompStringContainer(void){}
			CompString	*Create(void)	{	return new CompString();	}
		};

		class	UIString : public NPListSaveLoad<UIString>
		{
		public:

			char	*UIClassName;
			char	*ClassTypeName;
			char	*ControlName;
			char	*PropertyName;

			char				**Str;
			int32				AllocStrCount;

			UIString(void);
			~UIString(void);

			void	SetName( char *_UIClassName
							,char *_ClassTypeName
							,char *_ControlName
							,char *_PropertyName);

			void	AllocStr(int count);
			void	SetStr(int n ,char *s);

			bool	Save(QIODevice *f);
			bool	Load(QIODevice *f);
		};
		class	UIStringContainer : public NPListPackSaveLoad<UIString>
		{
		public:
			UIStringContainer(void){}
			UIString	*Create(void){	return new UIString();	}
		};
	private:
		CompStringContainer		CompStringContainer;
		UIStringContainer		UIStringContainer;
	public:
		explicit    LanguageComponent(LanguagePackage *parent):Parent(parent){}

		void	Add(LanguagePackage::LanguageComponent::CompString *h);
		void	Add(LanguagePackage::LanguageComponent::UIString *h);

		QString	GetString(int FileID ,int LID);
		void	SetUIInner(QWidget *W ,const QString &UIClassName ,const QString &ObjName);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	LanguageComponentContainer : public NPListPackSaveLoad<LanguageComponent>
	{
		LanguagePackage *Parent;
	public:
		explicit  LanguageComponentContainer(LanguagePackage *parent):Parent(parent){}

		LanguageComponent	*Create(void){	return new LanguageComponent(Parent);	}
	};
private:
	LanguageComponentContainer	LanguageComponents;

	class	CodecList : public NPListSaveLoad<CodecList>
	{
	public:
		char	*CodecStr;
		QTextCodec	*CurrentCodec;

		CodecList(void){	CodecStr=NULL;	CurrentCodec=NULL;	}
		~CodecList(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	class	CodecContainer : public NPListPackSaveLoad<CodecList>
	{
	public:
		CodecContainer(void){}

		CodecList	*Create(void)	{	return new CodecList();		}

	};
	CodecContainer	CodecStocker;

	QTextCodec *FirstCodec;
	QTextCodec *CurrentCodec;

	int		LastLanguageCode;
	int		LanguageCode;	//0Å`

	QTextCodec			*DefaultCodecCString;
	QTextCodec			*DefaultCodecLocale;
	QTextCodec			*DefaultCodecTr;
	QTextCodec			*CurrentCodecCString;
	QTextCodec			*CurrentCodecLocale;
	QTextCodec			*CurrentCodecTr;
	int					CodecPushedCount;

public:
	LanguagePackage(void);
	~LanguagePackage(void);

	void	Clear(void);
	bool	SetLanguage(int LangCode);
	int		GetLanguageCode(void)		{	return LanguageCode;	}

	void	AddLanguageCodec(char *s);
	void	AddComponent(LanguagePackage::LanguageComponent	*DestL);

	bool	SaveSolution(QIODevice *f);
	bool	LoadSolution(QIODevice *f);

	bool	LoadSolutionFromFile(const QString &LNGFileName);

	LanguagePackage::LanguageComponent	*GetComponent(const QString &idName);

	void	SetDefaultCodec(void);
	void	RestoreCodec(void);

private:
	bool	InitialCodec(void);
	bool	CheckCodec(void);
};


#endif
