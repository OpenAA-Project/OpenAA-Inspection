#if	!defined(XSTATUSCONTROLLER_H)
#define	XSTATUSCONTROLLER_H

#include "XGUIFormBase.h"
#include "XServiceForLayers.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include <QIODevice>
#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

class	StatusController;

class	CommentOpinion : public NPListSaveLoad<CommentOpinion>
{
	QStringList	ObjectPath;
	QStringList	Comment;
	bool	HTMLMode;
	QStringList	ToolTip;
	bool	HTMLModeToopTip;
	bool	EnableToolTip;
public:
	CommentOpinion(void){	EnableToolTip=true;	}
	CommentOpinion(const CommentOpinion &src);
	CommentOpinion(const QStringList &_ObjectPath ,const QStringList &_Comment ,bool _HTMLMode)
		:ObjectPath(_ObjectPath),Comment(_Comment),HTMLMode(_HTMLMode),EnableToolTip(true){}

	void	SetPath(const QStringList &_ObjectPath)		{	ObjectPath=_ObjectPath;	}
	void	SetComment(const QStringList &_Comment)		{	Comment=_Comment;	HTMLMode=false;	}
	void	SetToolTip(const QStringList &Str)			{	ToolTip=Str;		HTMLModeToopTip=false;	}
	void	SetHTMLMode(const QString &HtmlStr)	;
	void	SetHTMLModeToopTip(const QString &HtmlToopTipStr)	;
	bool	MatchAll(const QStringList &_ObjectPath)	{	return (ObjectPath==_ObjectPath)?true:false;	}
	bool	operator==(const CommentOpinion &src)	const;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	const	QStringList	&GetObjectPath(void)	const{	return ObjectPath;	}
	const	QStringList	&GetComment(void)		const{	return Comment;		}
	QString	GetCommentString(void)	const;
	QString	GetToolTipString(void)	const;

	bool	IsHTML(void)			const	{	return HTMLMode;		}
	bool	IsHTMLToopTip(void)		const	{	return HTMLModeToopTip;	}
	void	SetEnableToolTip(bool b)		{	EnableToolTip=b;		}
	bool	IsEnableToolTop(void)	const	{	return EnableToolTip;	}	
};

class	StatusOpinionInGUI : public NPListSaveLoad<StatusOpinionInGUI> ,public NPListPackSaveLoad<CommentOpinion>
{
	QString	GUIRoot;
	QString	GUIName;
	QString	GUIInst;
public:
	StatusOpinionInGUI(void){}
	StatusOpinionInGUI(const StatusOpinionInGUI &src);

	virtual	CommentOpinion	*Create(void){	return new 	CommentOpinion();	}

	void	SetModes(GUIFormBase *f);
	bool	MatchAll(GUIFormBase *f);
	bool	operator==(const StatusOpinionInGUI &src)	const;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	void	Set(const QString &GUIRoot
				,const QString &GUIName
				,const QString &GUIInst);

	CommentOpinion	*Find(const QStringList &ObjectPath)	const;

	QString		GetGUIRoot(void)	const	{	return GUIRoot;		}
	QString		GetGUIName(void)	const	{	return GUIName;		}
	QString		GetGUIInst(void)	const	{	return GUIInst;		}
};

class	StatusClient : public QObject , public NPList<StatusClient>
{
    Q_OBJECT

	friend class	StatusController;

	QLocalSocket	*Sock;
	StatusController	*Parent;
	int	ID;
public:
	StatusClient(int id ,QLocalSocket *s,StatusController *parent);
	~StatusClient(void);

	bool	Send(CommentOpinion *comment);
private slots:
	void	SlotDisconnected();
};

class	StatusController : public QLocalServer ,public ServiceForLayers , public NPListPackSaveLoad<StatusOpinionInGUI>
{
    Q_OBJECT

	friend class	StatusClient;

	CommentOpinion				*LastOpinion;
	NPListPack<StatusClient>	Clients;
public:
	StatusController(LayersBase *base):ServiceForLayers(base){	LastOpinion=NULL;	}


	virtual	StatusOpinionInGUI	*Create(void){	return new StatusOpinionInGUI();	}


	QString	GetDefaultFileName(void)	const;
	void	InstallFilter(void);
	bool	LoadDef(void);
	bool	LoadDef(const QString &FileName);
	bool	SaveDef(void);
	bool	SaveDef(const QString &FileName);

	CommentOpinion	*FindComment(const QString &GUIRoot
								,const QString &GUIName
								,const QString &GUIInst
								,const QStringList &ObjectPath)	const;
	CommentOpinion	*SetComment(const QString &GUIRoot
								,const QString &GUIName
								,const QString &GUIInst
								,const QStringList &ObjectPath
								,const QStringList &Comment
								,const QStringList &ToolTip
								,bool enableToopTip);
	CommentOpinion	*SetHtml	(const QString &GUIRoot
								,const QString &GUIName
								,const QString &GUIInst
								,const QStringList &ObjectPath
								,const QStringList &Comment
								,const QStringList &ToolTip
								,bool enableToopTip);

	void	ShowComment(CommentOpinion *c);	
	void	DisconnectClient(void);
	void	ShowComment(bool HTMLMode ,const QStringList &s);	
signals:
	void	SignalShowComment(bool HTMLMode ,const QStringList &);

private slots:
	void SlotNewConnection();

private:
	void	InstallFilter(QObject *w);
	void	DeleteClient(StatusClient *s);
};

class	OperationStatusFilter : public QObject,public ServiceForLayers
{
	QStringList	ObjectPath;
	GUIFormBase	*Form;
	CommentOpinion	*s;
public:
	OperationStatusFilter(LayersBase *base, GUIFormBase	*Form ,const QStringList &ObjectPath ,CommentOpinion *s ,QObject * parent = 0 );

 protected:
     bool eventFilter(QObject *obj, QEvent *event);
};

#endif