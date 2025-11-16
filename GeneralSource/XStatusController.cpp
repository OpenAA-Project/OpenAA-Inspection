#include <cmath>
#include "XTypeDef.h"
#include "XStatusController.h"
#include "XGeneralFunc.h"
#include "XParamGlobal.h"

CommentOpinion::CommentOpinion(const CommentOpinion &src)
{
	ObjectPath		=src.ObjectPath;
	Comment			=src.Comment;
	HTMLMode		=src.HTMLMode;
	ToolTip			=src.ToolTip;
	HTMLModeToopTip	=src.HTMLModeToopTip;
	EnableToolTip	=src.EnableToolTip;
}
bool	CommentOpinion::operator==(const CommentOpinion &src)	const
{
	if(ObjectPath!=src.ObjectPath)
		return false;
	if(Comment	!=src.Comment)
		return false;
	if(HTMLMode!=src.HTMLMode)
		return false;
	if(ToolTip!=src.ToolTip)
		return false;
	if(HTMLModeToopTip!=src.HTMLModeToopTip)
		return false;
	if(EnableToolTip!=src.EnableToolTip)
		return false;
	return true;
}
void	CommentOpinion::SetHTMLMode(const QString &HtmlStr)	
{	
	Comment.clear();
	Comment.append(HtmlStr);
	HTMLMode=true;	
}
void	CommentOpinion::SetHTMLModeToopTip(const QString &HtmlToopTipStr)
{
	ToolTip.clear();
	ToolTip.append(HtmlToopTipStr);
	HTMLModeToopTip=true;	
}

QString	CommentOpinion::GetCommentString(void)	const
{
	QString	Str;
	for(int i=0;i<Comment.count();i++){
		Str+=Comment[i];
		if(i<(Comment.count()-1)){
			Str+=/**/"\r\n";
		}
	}
	return Str;
}

QString	CommentOpinion::GetToolTipString(void)	const
{
	QString	Str;
	for(int i=0;i<ToolTip.count();i++){
		Str+=ToolTip[i];
		if(i<(ToolTip.count()-1)){
			Str+=/**/"\r\n";
		}
	}
	return Str;
}

bool	CommentOpinion::Save(QIODevice *f)
{
	int32	Ver=4;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ObjectPath)==false)
		return false;
	int32	Count=Comment.count();
	if(::Save(f,Count)==false)
		return false;
	wchar_t *PArray=new wchar_t[1000000];
	for(int i=0;i<Count;i++){
		int32	Len=Comment[i].toWCharArray ( PArray );
		if(::Save(f,Len)==false)
			return false;
		if(f->write((const char *)PArray,sizeof(wchar_t)*Len)!=sizeof(wchar_t)*Len)
			return false;
	}
	delete	[]PArray;
	if(::Save(f,HTMLMode)==false)
		return false;
	if(::Save(f,ToolTip)==false)
		return false;
	if(::Save(f,HTMLModeToopTip)==false)
		return false;
	if(::Save(f,EnableToolTip)==false)
		return false;
	return true;
}
bool	CommentOpinion::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ObjectPath)==false)
		return false;
	int32	Count;
	if(::Load(f,Count)==false)
		return false;
	Comment.clear();
	wchar_t *PArray=new wchar_t[1000000];
	for(int i=0;i<Count;i++){
		int32	Len;
		if(::Load(f,Len)==false)
			return false;
		if(f->read((char *)PArray,sizeof(wchar_t)*Len)!=sizeof(wchar_t)*Len)
			return false;
		QString	s=QString::fromWCharArray (PArray,Len);
		Comment.append(s);
	}
	delete	[]PArray;
	if(::Load(f,HTMLMode)==false)
		return false;
	if(Ver==2){
		QString	tmp;
		if(::Load(f,tmp)==false)
			return false;
		SetHTMLModeToopTip(tmp);
	}
	if(Ver>=3){
		if(::Load(f,ToolTip)==false)
			return false;
		if(::Load(f,HTMLModeToopTip)==false)
			return false;
	}
	EnableToolTip=true;
	if(Ver>=4){
		if(::Load(f,EnableToolTip)==false)
			return false;
	}
	return true;
}
//------------------------------------------------------------

StatusOpinionInGUI::StatusOpinionInGUI(const StatusOpinionInGUI &src)
{
	GUIRoot		=src.GUIRoot;
	GUIName		=src.GUIName;
	GUIInst		=src.GUIInst;
	for(CommentOpinion *s=src.NPListPackSaveLoad<CommentOpinion>::GetFirst();s!=NULL;s=s->GetNext()){
		CommentOpinion	*d=new CommentOpinion(*s);
		AppendList(d);
	}
}

void	StatusOpinionInGUI::SetModes(GUIFormBase *f)
{
	if(f!=NULL){
		GUIRoot	=f->GetDLLRoot();
		GUIName	=f->GetDLLName();
		GUIInst	=f->GetName();
	}
}
	
void	StatusOpinionInGUI::Set( const QString &_GUIRoot
								,const QString &_GUIName
								,const QString &_GUIInst)
{
	GUIRoot		=_GUIRoot;	
	GUIName		=_GUIName;
	GUIInst		=_GUIInst;
}

bool	StatusOpinionInGUI::MatchAll(GUIFormBase *f)
{
	if(f!=NULL){
		if(GUIRoot	!=f->GetDLLRoot()){
			return false;
		}
		if(GUIName	!=f->GetDLLName()){
			return false;
		}
		if(GUIInst	!=f->GetName()){
			return false;
		}
		return true;
	}
	return false;
}
bool	StatusOpinionInGUI::operator==(const StatusOpinionInGUI &src)	const
{
	if(GUIRoot!=src.GUIRoot){
		return false;
	}
	if(GUIName!=src.GUIName){
		return false;
	}
	if(GUIInst!=src.GUIInst){
		return false;
	}
	for(CommentOpinion *s=src.NPListPackSaveLoad<CommentOpinion>::GetFirst();s!=NULL;s=s->GetNext()){
		if(Find(s->GetObjectPath())==NULL){
			return false;
		}
	}
	for(CommentOpinion *s=NPListPackSaveLoad<CommentOpinion>::GetFirst();s!=NULL;s=s->GetNext()){
		if(((StatusOpinionInGUI *)&src)->Find(s->GetObjectPath())==NULL){
			return false;
		}
	}
	return true;
}

CommentOpinion	*StatusOpinionInGUI::Find(const QStringList &ObjectPath)	const
{
	for(CommentOpinion *s=NPListPackSaveLoad<CommentOpinion>::GetFirst();s!=NULL;s=s->GetNext()){
		if(s->GetObjectPath().count()>0 && ObjectPath.count()>0){
			if(s->GetObjectPath()[0]==ObjectPath[0]){
				return s;
			}
		}
	}
	return NULL;
}

bool	StatusOpinionInGUI::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,GUIRoot)==false){
		return false;
	}
	if(::Save(f,GUIName)==false){
		return false;
	}
	if(::Save(f,GUIInst)==false){
		return false;
	}
	if(NPListPackSaveLoad<CommentOpinion>::Save(f)==false){
		return false;
	}
	return true;
}

bool	StatusOpinionInGUI::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,GUIRoot)==false){
		return false;
	}
	if(::Load(f,GUIName)==false){
		return false;
	}
	if(::Load(f,GUIInst)==false){
		return false;
	}
	if(NPListPackSaveLoad<CommentOpinion>::Load(f)==false){
		return false;
	}
	return true;
}


//===========================================================================

QString	StatusController::GetDefaultFileName(void)	const
{
	QString	FileName=GetLayersBase()->GetUserPath()+GetSeparator()+GetParamGlobal()->CommentFileName;
	return FileName;
}

bool	StatusController::LoadDef(void)
{
	return LoadDef(GetDefaultFileName());
}
bool	StatusController::LoadDef(const QString &FileName)
{
	QFile	File(FileName);

	if(File.open(QIODevice::ReadOnly)==true){
		if(NPListPackSaveLoad<StatusOpinionInGUI>::Load(&File)==false){
			return false;
		}
	}
	return true;
}
bool	StatusController::SaveDef(void)
{
	return SaveDef(GetDefaultFileName());
}

bool	StatusController::SaveDef(const QString &FileName)
{
	QFile	File(FileName);

	if(File.open(QIODevice::WriteOnly)==true){
		if(NPListPackSaveLoad<StatusOpinionInGUI>::Save(&File)==false){
			return false;
		}
	}
	return true;
}

CommentOpinion	*StatusController::FindComment(const QString &GUIRoot
												,  const QString &GUIName
												,  const QString &GUIInst
												,  const QStringList &ObjectPath)	const
{
	for(StatusOpinionInGUI *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(GUIRoot==L->GetGUIRoot()
		&& GUIName==L->GetGUIName()
		&& GUIInst==L->GetGUIInst()){
			CommentOpinion	*C=L->Find(ObjectPath);
			if(C!=NULL){
				return C;
			}
		}
	}
	return NULL;
}

CommentOpinion	*StatusController::SetComment(const QString &GUIRoot
											, const QString &GUIName
											, const QString &GUIInst
											, const QStringList &ObjectPath
											, const QStringList &Comment
											, const QStringList &ToolTip
											, bool enableToopTip)
{
	for(StatusOpinionInGUI *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(GUIRoot==L->GetGUIRoot()
		&& GUIName==L->GetGUIName()
		&& GUIInst==L->GetGUIInst()){
			CommentOpinion	*C=L->Find(ObjectPath);
			if(C!=NULL){
				C->SetComment(Comment);
				C->SetToolTip(ToolTip);
				C->SetEnableToolTip(enableToopTip);
				return C;
			}
			C=new CommentOpinion(ObjectPath,Comment,false);
			C->SetToolTip(ToolTip);
			C->SetEnableToolTip(enableToopTip);
			L->AppendList(C);
			return C;
		}
	}
	StatusOpinionInGUI	*L=new StatusOpinionInGUI();
	L->Set(GUIRoot ,GUIName ,GUIInst);
	AppendList(L);

	CommentOpinion	*C=new CommentOpinion(ObjectPath,Comment,false);
	C->SetToolTip(ToolTip);
	C->SetEnableToolTip(enableToopTip);
	L->AppendList(C);
	return C;
}
CommentOpinion	*StatusController::SetHtml	(const QString &GUIRoot
											,const QString &GUIName
											,const QString &GUIInst
											,const QStringList &ObjectPath
											,const QStringList &Comment
											,const QStringList &ToolTip
											,bool enableToopTip)
{
	for(StatusOpinionInGUI *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(GUIRoot==L->GetGUIRoot()
		&& GUIName==L->GetGUIName()
		&& GUIInst==L->GetGUIInst()){
			CommentOpinion	*C=L->Find(ObjectPath);
			if(C!=NULL){
				C->SetComment(Comment);
				C->SetToolTip(ToolTip);
				C->SetEnableToolTip(enableToopTip);
				return C;
			}
			C=new CommentOpinion(ObjectPath,Comment,true);
			C->SetToolTip(ToolTip);
			C->SetEnableToolTip(enableToopTip);
			L->AppendList(C);
			return C;
		}
	}
	StatusOpinionInGUI	*L=new StatusOpinionInGUI();
	L->Set(GUIRoot ,GUIName ,GUIInst);
	AppendList(L);

	CommentOpinion	*C=new CommentOpinion(ObjectPath,Comment,true);
	C->SetToolTip(ToolTip);
	C->SetEnableToolTip(enableToopTip);
	L->AppendList(C);
	return C;
}

void	StatusController::ShowComment(CommentOpinion *c)
{
	if(LastOpinion!=c){
		if(c!=NULL){
			emit	SignalShowComment(c->IsHTML(),c->GetComment());
		}
		else{
			QStringList	List;
			emit	SignalShowComment(false,List);
		}
		for(StatusClient *s=Clients.GetFirst();s!=NULL;s=s->GetNext()){
			s->Send(c);
		}
	}
	LastOpinion=c;
}
void	StatusController::ShowComment(bool HTMLMode ,const QStringList &s)
{
	emit	SignalShowComment(HTMLMode,s);
}
void	StatusController::InstallFilter(void)
{
	QWidget	*w=GetLayersBase()->GetMainWidget();
	InstallFilter(w);
	connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	listen (/**/"StatusComment");
}

void	StatusController::InstallFilter(QObject *w)
{
	if(w==NULL)
		return;
	QWidget	*Wid=dynamic_cast<QWidget *>(w);
	if(Wid!=NULL){
		QStringList	ObjectPath;
		GUIFormBase	*Form=NULL;
		for(QWidget *m=Wid;m!=NULL;m=m->parentWidget()){
			if(Form==NULL){
				GUIFormBase	*F=dynamic_cast<GUIFormBase *>(m);
				if(F!=NULL){
					Form=F;
				}
			}
			QString	ObjName=m->objectName();
			ObjectPath.append(ObjName);
		}
		if(Form!=NULL){
			CommentOpinion	*s=GetLayersBase()->GetStatusController()->FindComment(  Form->GetDLLRoot()
																					,Form->GetDLLName()
																					,Form->GetName()
																					,ObjectPath);
			if(s!=NULL){
				QWidget	*WDest=Wid;
				if(ObjectPath.count()>=1 && ObjectPath[0].left(3)==/**/"qt_"){
					WDest=Wid->parentWidget();
				}
				if(WDest!=NULL){
					OperationStatusFilter	*filter=new OperationStatusFilter(GetLayersBase(),Form,ObjectPath,s);
					WDest->installEventFilter(filter);
					if(WDest->toolTip().isEmpty()==false && s->GetToolTipString().isEmpty()==true){
						s->SetHTMLModeToopTip(WDest->toolTip());
					}
					else{
						if(s->IsEnableToolTop()==true){
							WDest->setToolTip(s->GetToolTipString());
						}
						else{
							WDest->setToolTip(/**/"");
						}
					}
					WDest->setMouseTracking (true);
				}
			}
		}
	}
	const QObjectList	&Q=w->children();
	int	ChildCount=Q.count();
	for(int i=0;i<ChildCount;i++){
		InstallFilter(Q[i]);
	}
}

void	StatusController::DeleteClient(StatusClient *s)
{
	Clients.RemoveList(s);
}

void StatusController::SlotNewConnection()
{
	QLocalSocket	*s=nextPendingConnection ();
	int	id=Clients.GetCount();
	StatusClient	*Cli=new StatusClient(id,s,this);
	Clients.AppendList(Cli);
}

void	StatusController::DisconnectClient(void)
{
	StatusClient	*Cli;
	while((Cli=Clients.GetFirst())!=NULL){
		Clients.RemoveList(Cli);
		delete	Cli;
	}
}

//-------------------------------------------------------------------

StatusClient::StatusClient(int id ,QLocalSocket *s,StatusController *parent)
	:QObject(parent) 
	,Sock(s)
	,Parent(parent)
	,ID(id)
{
	connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

StatusClient::~StatusClient(void)
{
	delete	Sock;
	Sock=NULL;
}

bool	StatusClient::Send(CommentOpinion *Comment)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);

	if(Comment->Save(&Buff)==false)
		return false;

	if(Sock->isValid() && Sock->state()==QLocalSocket::ConnectedState){
		QByteArray	A=Buff.buffer();
		int32	Len=A.size();
		if(Sock->write((const char *)&Len,sizeof(Len))!=sizeof(Len))
			return false;
		if(Sock->write(A)!=Len)
			return false;
		if(Sock->flush()==false)
			return false;
	}
	return true;
}

void	StatusClient::SlotDisconnected()
{
	Parent->DeleteClient(this);
	deleteLater();
}

//-------------------------------------------------------------------
OperationStatusFilter::OperationStatusFilter(LayersBase *base, GUIFormBase	*_Form ,const QStringList &_ObjectPath , CommentOpinion	*_s,QObject * parent)
	:ServiceForLayers(base)
{
	Form		=_Form;
	ObjectPath	=_ObjectPath;
	s			=_s;
}

bool OperationStatusFilter::eventFilter(QObject *obj, QEvent *event)
{
	QMouseEvent	*ev=dynamic_cast<QMouseEvent *>(event);
	if(ev!=NULL && Form->GetEditMode()==false){
		int	type=ev->type();
		if(type==QEvent::Enter || type==QEvent::MouseMove){
			//CommentOpinion	*s=GetLayersBase()->GetStatusController()->FindComment(  Form->GetDLLRoot()
			//																		,Form->GetDLLName()
			//																		,Form->GetName()
			//																		,ObjectPath);
			if(s!=NULL){
				GetLayersBase()->GetStatusController()->ShowComment(s);
			}
		}
		else if(type==QEvent::Leave){
			GetLayersBase()->GetStatusController()->ShowComment(NULL);
		}
	}
	return false;
}
