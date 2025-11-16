#if	!defined(XPASSWORD_H)
#define	XPASSWORD_H

#include <QString>
#include <QObject>
#include "NList.h"
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	GUIInstancePack;
class	PasswordFilterPointerList;
class	PasswordDropper;

class	PasswordClass : public NPList<PasswordClass>
{
	int32		PasswordClassID;
	QString		ClassName;
	bool		Passed;

public:
	PasswordClass(void){	Passed=false;	}
	PasswordClass(int32 _PasswordClassID
				,const QString &_ClassName)
				:PasswordClassID(_PasswordClassID),ClassName(_ClassName){	Passed=false;	}

	int32		GetPasswordClassID(void)	const	{	return PasswordClassID;		}
	QString		GetClassName(void)			const	{	return ClassName;			}
	void		SetClassName(const QString &name)	{	ClassName=name;		}
	bool		GetPassed(void)				const	{	return Passed;				}
	void		SetPassed(bool b)					{	Passed=b;					}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PasswordPass : public NPList<PasswordPass>
{
	int32		PasswordClassID;
	QString		Password;

public:
	PasswordPass(void){};
	PasswordPass(int32 _PasswordClassID
				,const QString &_Password);

	int32		GetPasswordClassID(void)	const	{	return PasswordClassID;		}
	QString		GetPassword(void)			const	{	return Password;			}
	void		SetPassword(const QString &password){	Password=password;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PasswordInControl : public NPList<PasswordInControl>
{
	int32	PasswordClassID;
	QString	ControlPathName;
	QString	ControlName;
	int32	ControlMode;	//0:Normal check password , 1:Expire
public:

	PasswordInControl(void){	ControlMode=0;	}
	PasswordInControl(int32 _PasswordClassID
					,const QString &_ControlPathName
					,const QString &_ControlName);


	int32	GetPasswordClassID(void)	const	{	return PasswordClassID;		}
	QString	GetControlPathName(void)	const	{	return ControlPathName;		}
	QString	GetControlName(void)		const	{	return ControlName;			}

	int		GetControlMode(void)		const	{	return ControlMode;			}
	void	SetControlMode(int c)				{	ControlMode=c;				}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	PasswordManager: public ServiceForLayers
{
	QString	DefaultPasswordFile;
	int32	CurrentPasswordClassID;

	NPListPack<PasswordClass>		PasswordClassData;
	NPListPack<PasswordPass>		PasswordPassData;
	NPListPack<PasswordInControl>	PasswordInControlData;
	int	HandlerReEntrant;

	bool	ModeOfEditPassword;
	PasswordDropper	*DropperForm;
	int32		ExpiredTimeSec;
	DWORD		LastEditTime;

public:
	explicit	PasswordManager(LayersBase *Base):ServiceForLayers(Base)
	{	
		CurrentPasswordClassID=0;	
		HandlerReEntrant=0;	
		DropperForm=NULL;
		ExpiredTimeSec=0;
		LastEditTime=0;
	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Setup(GUIInstancePack &GUIPack,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData,PasswordDropper *form);
	void	SetupOnlyPassword(GUIInstancePack &GUIPack);

	bool	GetModeOfEditPassword(void)		const	{	return ModeOfEditPassword;	}
	PasswordDropper	*GetDropperForm(void)	const	{	return DropperForm;			}

	PasswordInControl	*Search(PasswordInControl *c);

	void	AppendClass(const QString &className);
	void	RemoveClass(PasswordClass *c);
	void	AppendPassword(PasswordClass *c,const QString &password);
	bool	IsPasswordExists(const QString &Password);
	bool	NeedPasswordCheck(QObject *obj);
	bool	PasswordCheck(void);
	bool	PasswordCheck(QObject *obj);
	void	Pass(QObject *obj);
	void	Pass(void);
	bool	IsPassed(void);
	void	ResetAll(void);
	bool	NeedPasswordCheckWidget(QObject *obj);
	void	PassWidget(QObject *obj);
	void	EnablePasswordAgain(void);

	bool	SetDefaultFile(const QString &_DefaultPasswordFile);
	bool	LoadDefaultFile(void);
	bool	SaveDefaultFile(void);

	bool	IncreaseEntrant(void);
	void	DecreaseEntrant(void);

	void	SetExpiredTimeSec(int n)			{	ExpiredTimeSec=n;	}
	int		GetExpiredTimeSec(void)		const	{	return ExpiredTimeSec;	}
	void	UpdateLastTime(void);
	bool	IsExpired(void);

	NPListPack<PasswordClass>		&GetPasswordClassData(void)		{	return PasswordClassData;		}
	NPListPack<PasswordPass>		&GetPasswordPassData(void)		{	return PasswordPassData;		}
	NPListPack<PasswordInControl>	&GetPasswordInControlData(void)	{	return PasswordInControlData;	}

	int	GetPasswordClassDataCount(void)		const	{	return PasswordClassData.GetNumber();		}
	int	GetPasswordPassDataCount(void)		const	{	return PasswordPassData.GetNumber();		}
	int	GetPasswordInControlDataCount(void)	const	{	return PasswordInControlData.GetNumber();	}

	PasswordClass		*GetPasswordClassDataFirst(void)		const	{	return PasswordClassData.GetFirst();		}
	PasswordPass		*GetPasswordPassDataFirst(void)			const	{	return PasswordPassData.GetFirst();			}
	PasswordInControl	*GetPasswordInControlDataFirst(void)	const	{	return PasswordInControlData.GetFirst();	}

	PasswordClass		*GetPasswordClassDataItem(int n)		const	{	return PasswordClassData.GetItem(n);		}
	PasswordPass		*GetPasswordPassDataItem(int n)			const	{	return PasswordPassData.GetItem(n);			}
	PasswordInControl	*GetPasswordInControlDataItem(int n)	const	{	return PasswordInControlData.GetItem(n);	}

	void	AppendList(PasswordClass *c);
	void	AppendList(PasswordPass *c);
	void	AppendList(PasswordInControl *c);

	void	RemoveList(PasswordClass *c);
	void	RemoveList(PasswordPass *c);
	void	RemoveList(PasswordInControl *c);
};

class PasswordFilter : public QObject,public ServiceForLayers
{
	Q_OBJECT
public:
	PasswordFilter(LayersBase *Base,QObject *parent):QObject(parent),ServiceForLayers(Base){}

	PasswordFilter	*CreateNew(LayersBase *Base,QObject *parent);
protected:

	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void	SignalDropped(QObject *obj);
};

class	PasswordFilterPointerList : public NPList<PasswordFilterPointerList>
{
public:
	PasswordFilter	*IndexPoint;

	explicit	PasswordFilterPointerList(PasswordFilter *_IndexPoint){	IndexPoint=_IndexPoint;	}
};

inline	PasswordFilter	*PasswordFilter::CreateNew(LayersBase *Base,QObject *parent){	return new PasswordFilter(Base,parent);	}

bool checkBootupPassword(LayersBase *Base, const QString Keyword , const QString &PasswordFile);

#endif