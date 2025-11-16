#if	!defined(XMACROEXECUTER_H)
#define	XMACROEXECUTER_H

#include<QString>
#include<QStringList>
#include"NList.h"
#include <QIODevice>
#include "XTypeDef.h"

class	LayersBase;


class	MacroSentenseBase : public NPList<MacroSentenseBase>
{
public:
	MacroSentenseBase(void){}

	virtual	bool	LoadFromMacro(const QString &TextBuff)=0;
	virtual	QString	GetTextLine(void)=0;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)=0;

	bool	ExecuteMacro(LayersBase *Base);
};

class	MacroFunction : public MacroSentenseBase
{
	QString	DLLRoot;
	QString	DLLName;
	QString	InstName;
	QString	FuncName;

	QStringList	Args;

public:
	MacroFunction(void){}

	virtual	bool	LoadFromMacro(const QString &TextBuff)			override;
	virtual	QString	GetTextLine(void)								override;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)	override;
};

class	MacroWait : public MacroSentenseBase
{
	QString	WaitCount;
public:

	MacroWait(void){}
	virtual	bool	LoadFromMacro(const QString &TextBuff)			override;
	virtual	QString	GetTextLine(void)								override;
	virtual	bool	ExecuteLine(LayersBase *Base,bool &ExeReturn)	override;
};

class	MacroSentenseContainer : public NPListPack<MacroSentenseBase>
{
public:
	MacroSentenseContainer(void){}

	virtual	bool	LoadFromMacro(QIODevice &TextFile,QString &ErrorLine);
};


#endif