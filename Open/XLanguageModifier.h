#if	!defined(XLANGUAGEMODIFIER_H)
#define	XLANGUAGEMODIFIER_H

#include <QObject>
class	GUIFormBase;

class	LangDialogModifier
{
public:
	LangDialogModifier(QObject *parent);

	static	void	Register(LangDialogModifier *ObjDialog ,GUIFormBase *RootInstance);

	void	Setup(void);
	void	Reset(void);
};

class	LangMessageModifier
{
public:
	LangMessageModifier(LangDialogModifier *parent	);
	LangMessageModifier(GUIFormBase *parent			);
	
	void	SetMessageString(int ID ,const QString &Str);
	QString	GetMessageString(int ID);
};


#endif