#include "XTypeDef.h"
#include "XPassword.h"
#include "XGeneralFunc.h"
#include "XGUI.h"
#include "XCriticalFunc.h"
#include "InputPasswordForm.h"
#include "XPasswordQWidget.h"
#include "InputPasswordForm.h"
#include <QString>
#include <QDir>
#include <QLineEdit>
#include <QAbstractButton>
#include <QAbstractSpinBox>
#include <QTabWidget>
#include <QTabBar>
#include "XDataInLayer.h"


bool	PasswordClass::Save(QIODevice *f)
{
	if(::Save(f,PasswordClassID)==false){
		return false;
	}
	if(::Save(f,ClassName)==false){
		return false;
	}
	return true;
}

bool	PasswordClass::Load(QIODevice *f)
{
	if(::Load(f,PasswordClassID)==false){
		return false;
	}
	if(::Load(f,ClassName)==false){
		return false;
	}
	return true;
}

PasswordPass::PasswordPass(int32 _PasswordClassID
				,const QString &_Password)
				:PasswordClassID(_PasswordClassID),Password(_Password)
{
}

bool	PasswordPass::Save(QIODevice *f)
{
	if(::Save(f,PasswordClassID)==false){
		return false;
	}
	if(::Save(f,Password)==false){
		return false;
	}
	return true;
}

bool	PasswordPass::Load(QIODevice *f)
{
	if(::Load(f,PasswordClassID)==false){
		return false;
	}
	if(::Load(f,Password)==false){
		return false;
	}
	return true;
}

PasswordInControl::PasswordInControl(int32 _PasswordClassID
									,const QString &_ControlPathName
									,const QString &_ControlName)
:PasswordClassID(_PasswordClassID),ControlPathName(_ControlPathName),ControlName(_ControlName)
{
	ControlMode=0;
}

bool	PasswordInControl::Save(QIODevice *f)
{
	int32	Ver=100000;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,PasswordClassID)==false){
		return false;
	}
	if(::Save(f,ControlName)==false){
		return false;
	}
	if(::Save(f,ControlPathName)==false){
		return false;
	}
	if(::Save(f,ControlMode)==false){
		return false;
	}
	return true;
}

bool	PasswordInControl::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver>=100000){
		if(::Load(f,PasswordClassID)==false){
			return false;
		}
		if(::Load(f,ControlName)==false){
			return false;
		}
		if(::Load(f,ControlPathName)==false){
			return false;
		}
		if(::Load(f,ControlMode)==false){
			return false;
		}
	}
	else{
		PasswordClassID=Ver;
		if(::Load(f,ControlName)==false){
			return false;
		}
		if(::Load(f,ControlPathName)==false){
			return false;
		}
	}
	return true;
}


bool	PasswordManager::Save(QIODevice *f)
{
	int32	Ver=2;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,CurrentPasswordClassID)==false){
		return false;
	}
	int32	N=PasswordClassData.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(PasswordClass *a=PasswordClassData.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	N=PasswordPassData.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(PasswordPass *b=PasswordPassData.GetFirst();b!=NULL;b=b->GetNext()){
		if(b->Save(f)==false){
			return false;
		}
	}
	N=PasswordInControlData.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(PasswordInControl *b=PasswordInControlData.GetFirst();b!=NULL;b=b->GetNext()){
		if(b->Save(f)==false){
			return false;
		}
	}
	if(::Save(f,ExpiredTimeSec)==false){
		return false;
	}

	return true;
}

bool	PasswordManager::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(::Load(f,CurrentPasswordClassID)==false){
		return false;
	}
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	PasswordClassData.RemoveAll();
	for(int i=0;i<N;i++){
		PasswordClass *a=new PasswordClass();
		if(a->Load(f)==false){
			return false;
		}
		PasswordClassData.AppendList(a);
	}

	if(::Load(f,N)==false){
		return false;
	}
	PasswordPassData.RemoveAll();
	for(int i=0;i<N;i++){
		PasswordPass *a=new PasswordPass();
		if(a->Load(f)==false){
			return false;
		}
		PasswordPassData.AppendList(a);
	}

	if(::Load(f,N)==false){
		return false;
	}
	PasswordInControlData.RemoveAll();
	for(int i=0;i<N;i++){
		PasswordInControl *b=new PasswordInControl();
		if(b->Load(f)==false){
			return false;
		}
		PasswordInControlData.AppendList(b);
	}
	if(Ver>=2){
		if(::Load(f,ExpiredTimeSec)==false){
			return false;
		}
	}
	return true;
}

QObject	*IsTabButton(QObject *obj)
{
	if(obj==NULL){
		return NULL;
	}
	for(;;){
		QObject	*p=obj->parent();
		if(p==NULL){
			break;
		}
		QTabBar	*w=dynamic_cast<QTabBar	*>(p);
		if(w!=NULL){
			return obj;
		}
		obj=p;
	}
	return NULL;
}

bool PasswordFilter::eventFilter(QObject *obj, QEvent *event)
{
	if(GetLayersBase()->GetPasswordHolder()->IncreaseEntrant()==true){
		QAbstractButton	*vButton=dynamic_cast<QAbstractButton *>(obj);
		if(vButton!=NULL){
			if(event->type()==QEvent::DragEnter){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					ev->acceptProposedAction();
					event->setAccepted(true);
					//return true;
				}
			}
			else if(event->type()==QEvent::Drop){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					emit	SignalDropped(obj);
					event->setAccepted(true);
					GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
					return true;
				}
			}
			else
			if((event->type()==QEvent::MouseButtonPress)
			|| (event->type()==QEvent::MouseButtonRelease)
			|| (event->type()==QEvent::KeyPress && (((QKeyEvent *)event)->key()==Qt::Key_Space || ((QKeyEvent *)event)->key()==Qt::Key_Select))
			|| (event->type()==QEvent::KeyRelease && (((QKeyEvent *)event)->key()==Qt::Key_Space || ((QKeyEvent *)event)->key()==Qt::Key_Select))){
				if(GetLayersBase()->GetPasswordHolder()->NeedPasswordCheck(obj)==true){
					InputPasswordForm	Q(GetLayersBase());
					int	InputRet=Q.exec();
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
					if(InputRet==(int)true
					&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
						GetLayersBase()->GetPasswordHolder()->Pass(obj);
						GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
						if((event->type()==QEvent::MouseButtonPress)
						|| (event->type()==QEvent::KeyPress && (((QKeyEvent *)event)->key()==Qt::Key_Space || ((QKeyEvent *)event)->key()==Qt::Key_Select))){
							vButton->click();
							event->setAccepted(true);
							return true;
						}
						event->setAccepted(true);
						return false;
					}
					else{
						event->setAccepted(true);
						GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
						return true;
					}
				}
				else if(GetLayersBase()->GetPasswordHolder()->NeedPasswordCheckWidget(obj)==true){
					InputPasswordForm	Q(GetLayersBase());
					int	InputRet=Q.exec();
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
					if(InputRet==(int)true
					&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
						GetLayersBase()->GetPasswordHolder()->PassWidget(obj);
						GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
						if((event->type()==QEvent::MouseButtonPress)
						|| (event->type()==QEvent::KeyPress && (((QKeyEvent *)event)->key()==Qt::Key_Space || ((QKeyEvent *)event)->key()==Qt::Key_Select))){
							vButton->click();
							event->setAccepted(true);
							return true;
						}
						event->setAccepted(true);
						return false;
					}
					else{
						event->setAccepted(true);
						GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
						return true;
					}
				}
				else{
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
				}
			}
		}
		QLineEdit	*LEdit=dynamic_cast<QLineEdit *>(obj);
		if(LEdit!=NULL){
			if(event->type()==QEvent::DragEnter){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					ev->acceptProposedAction();
					//return true;
				}
			}
			else if(event->type()==QEvent::Drop){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					emit	SignalDropped(obj);
					//return true;
				}
			}
			else if(event->type()==QEvent::KeyPress || event->type()==QEvent::KeyRelease){
				if(GetLayersBase()->GetPasswordHolder()->NeedPasswordCheck(obj)==true){
					InputPasswordForm	Q(GetLayersBase());
					int	InputRet=Q.exec();
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
					if(InputRet==(int)true
					&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
						GetLayersBase()->GetPasswordHolder()->Pass(obj);
						//return false;
					}
					else{
						event->setAccepted(true);
						//return true;
					}
				}
				else{
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
				}
			}
		}
		QAbstractSpinBox	*SBox=dynamic_cast<QAbstractSpinBox	*>(obj);
		if(SBox!=NULL){
			if(event->type()==QEvent::DragEnter){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					ev->acceptProposedAction();
					//return true;
				}
			}
			else if(event->type()==QEvent::Drop){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					emit	SignalDropped(obj);
					//return true;
				}
			}
			else if(event->type()==QEvent::KeyPress || event->type()==QEvent::KeyRelease){
				if(GetLayersBase()->GetPasswordHolder()->NeedPasswordCheck(obj)==true){
					InputPasswordForm	Q(GetLayersBase());
					int	InputRet=Q.exec();
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
					if(InputRet==(int)true
					&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
						GetLayersBase()->GetPasswordHolder()->Pass(obj);
						//return false;
					}
					else{
						event->setAccepted(true);
						//return true;
					}
				}
				else{
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
				}
			}
		}
		QTabWidget	*vTabB=dynamic_cast<QTabWidget *>(obj);
		if(vTabB!=NULL){
			if(event->type()==QEvent::DragEnter){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					ev->acceptProposedAction();
					//return true;
				}
			}
		}
		QObject	*STabB=IsTabButton(obj);
		if(STabB!=NULL){
			if(event->type()==QEvent::DragEnter){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					ev->acceptProposedAction();
					//return true;
				}
			}
			else if(event->type()==QEvent::Drop){
				QDropEvent	*ev=dynamic_cast<QDropEvent *>(event);
				if(ev!=NULL && ev->mimeData()->hasText()==true && ev->mimeData()->text()=="PasswordTarget"){
					emit	SignalDropped(obj);
					//return true;
				}
			}
			else if(event->type()==QEvent::KeyPress || event->type()==QEvent::KeyRelease){
				if(GetLayersBase()->GetPasswordHolder()->NeedPasswordCheck(obj)==true){
					InputPasswordForm	Q(GetLayersBase());
					int	InputRet=Q.exec();
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
					if(InputRet==(int)true
					&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
						GetLayersBase()->GetPasswordHolder()->Pass(obj);
						//return false;
					}
					else{
						event->setAccepted(true);
						//return true;
					}
				}
				else{
					GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
				}
			}
		}
		GetLayersBase()->GetPasswordHolder()->DecreaseEntrant();
	}
	return false;
}


static	void	SetAllAcceptDrops(QObject *Obj ,bool b)
{
	QWidget	*W=dynamic_cast<QWidget *>(Obj);
	if(W!=NULL){
		W->setAcceptDrops(b);
	}
	const	QObjectList &Q=Obj->children();
	int	N=Q.count();
	for(int i=0;i<N;i++){
		SetAllAcceptDrops(Q[i],b);
	}
}


void	PasswordManager::Setup(GUIInstancePack &GUIPack,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData,PasswordDropper *form)
{
	DropperForm=form;
	ModeOfEditPassword	=true;

	GUIItemInstance *L=GUIPack.NPListPack<GUIItemInstance>::GetFirst();
	if(L!=NULL){
		GUIFormBase	*LBase=L->GetForm();
		
		GUIFormBase	*LTop=LBase->GetTopClass();
		if(LTop!=NULL){
			SetAllAcceptDrops(LTop,true);
		}
	}

	for(GUIItemInstance *f=GUIPack.NPListPack<GUIItemInstance>::GetFirst();f!=NULL;f=f->GetNext()){
		PasswordFilter *passwordFilter = new PasswordFilter(GetLayersBase(),f->Handle);
		f->Handle->InstallEventHandler(passwordFilter,PasswordFilterPointerData);
	}
}

void	PasswordManager::SetupOnlyPassword(GUIInstancePack &GUIPack)
{
	DropperForm=NULL;
	ModeOfEditPassword	=false;

	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		for(GUIItemInstance *f=GUIPack.NPListPack<GUIItemInstance>::GetFirst();f!=NULL;f=f->GetNext()){
			PasswordFilter passwordFilter(GetLayersBase(),f->Handle);
			f->Handle->InstallEventHandlerOnlyPassword(&passwordFilter,c);
		}
	}
}

QString	GetdObjPath(QObject *d);

bool	PasswordManager::NeedPasswordCheck(QObject *obj)
{
	QString	ObjPath=GetdObjPath(obj);
	bool	ControlExist=false;
	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetControlPathName()==ObjPath && c->GetControlName()==obj->objectName()){
			if(c->GetControlMode()==0){
				ControlExist=true;
				for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
					if(aPass->GetPasswordClassID()==c->GetPasswordClassID()){
						if(aPass->GetPassed()==true){
							if(IsExpired()==false){
								return false;
							}
						}
					}
				}
			}
			else{
				if(c->GetControlMode()==1){
					EnablePasswordAgain();
				}
			}
		}
	}
	if(ControlExist==true){
		return true;
	}
	return false;
}

bool	PasswordManager::PasswordCheck(QObject *obj)
{
	QString	ObjPath=GetdObjPath(obj);
	bool	ControlExist=false;
	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetControlPathName()==ObjPath && c->GetControlName()==obj->objectName()){
			if(c->GetControlMode()==0){
				ControlExist=true;
				for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
					if(aPass->GetPasswordClassID()==c->GetPasswordClassID()){
						if(aPass->GetPassed()==true){
							if(IsExpired()==false){
								return true;
							}
						}
					}
				}
			}
			else{
				if(c->GetControlMode()==1){
					EnablePasswordAgain();
				}
			}
		}
	}
	if(ControlExist==true){
		InputPasswordForm	Q(GetLayersBase());
		int	InputRet=Q.exec();
		GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
		if(InputRet==(int)true
		&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
			GetLayersBase()->GetPasswordHolder()->Pass();
			return true;
		}
		else{
			return false;
		}
	}
	return true;
}

bool	PasswordManager::PasswordCheck(void)
{
	bool	ControlExist=false;
	for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
		ControlExist=true;
		if(aPass->GetPassed()==true){
			if(IsExpired()==false){
				return true;
			}
		}
	}

	if(ControlExist==true){
		InputPasswordForm	Q(GetLayersBase());
		int	InputRet=Q.exec();
		GetLayersBase()->GetPasswordHolder()->UpdateLastTime();
		if(InputRet==(int)true
		&& GetLayersBase()->GetPasswordHolder()->IsPasswordExists(Q.Password)==true){
			GetLayersBase()->GetPasswordHolder()->Pass();
			return true;
		}
		else{
			return false;
		}
	}
	return true;
}

void	PasswordManager::EnablePasswordAgain(void)
{
	for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
		aPass->SetPassed(false);
	}
}

bool	PasswordManager::IsPassed(void)
{
	for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
		if(aPass->GetPassed()==true){
			return true;
		}
	}
	return false;
}

QString	GetdObjPathWidget(QObject *d)
{
	QString	Ret;

	while(d!=NULL){
		if(Ret.isEmpty()==false){
			Ret=d->objectName()+::GetSeparator()+Ret;
		}
		else{
			Ret=d->objectName();
		}
		if(dynamic_cast<PasswordInQWodget *>(d)!=NULL){
			return Ret;
		}
		d=d->parent();
	}
	return "";
}

bool	PasswordManager::NeedPasswordCheckWidget(QObject *obj)
{
	QString	ObjPath=GetdObjPathWidget(obj);
	bool	ControlExist=false;
	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetControlPathName()==ObjPath && c->GetControlName()==obj->objectName()){
			ControlExist=true;
			for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
				if(aPass->GetPasswordClassID()==c->GetPasswordClassID()){
					if(aPass->GetPassed()==true){
						return false;
					}
				}
			}
		}
	}
	if(ControlExist==true){
		return true;
	}
	return false;
}

void	PasswordManager::Pass(QObject *obj)
{
	QString	ObjPath=GetdObjPath(obj);
	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetControlPathName()==ObjPath && c->GetControlName()==obj->objectName()){
			for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
				if(aPass->GetPasswordClassID()==c->GetPasswordClassID()){
					aPass->SetPassed(true);
				}
			}
		}
	}
}
void	PasswordManager::Pass(void)
{
	for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
		aPass->SetPassed(true);
	}
}

void	PasswordManager::PassWidget(QObject *obj)
{
	QString	ObjPath=GetdObjPathWidget(obj);
	for(PasswordInControl *c=PasswordInControlData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetControlPathName()==ObjPath && c->GetControlName()==obj->objectName()){
			for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
				if(aPass->GetPasswordClassID()==c->GetPasswordClassID()){
					aPass->SetPassed(true);
				}
			}
		}
	}
}
void	PasswordManager::ResetAll(void)
{
	for(PasswordClass *aPass=PasswordClassData.GetFirst();aPass!=NULL;aPass=aPass->GetNext()){
		aPass->SetPassed(true);
	}
}


PasswordInControl	*PasswordManager::Search(PasswordInControl *c)
{
	for(PasswordInControl *p=PasswordInControlData.GetFirst();p!=NULL;p=p->GetNext()){
		if(c->GetControlName()==p->GetControlName()
			&& c->GetControlPathName()==p->GetControlPathName()
			&& c->GetPasswordClassID()==p->GetPasswordClassID()){
				return p;
		}
	}
	return NULL;
}

void	PasswordManager::AppendClass(const QString &className)
{
	CurrentPasswordClassID++;
	PasswordClass	*c=new PasswordClass(CurrentPasswordClassID,className);
	PasswordClassData.AppendList(c);
}
void	PasswordManager::RemoveClass(PasswordClass *c)
{
	PasswordClassData.RemoveList(c);
	for(PasswordPass *p=PasswordPassData.GetFirst();p!=NULL;){
		if(p->GetPasswordClassID()==c->GetPasswordClassID()){
			PasswordPass *PNext=p->GetNext();
			PasswordPassData.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
	for(PasswordInControl *p=PasswordInControlData.GetFirst();p!=NULL;){
		if(p->GetPasswordClassID()==c->GetPasswordClassID()){
			PasswordInControl *PNext=p->GetNext();
			PasswordInControlData.RemoveList(p);
			delete	p;
			p=PNext;
		}
		else{
			p=p->GetNext();
		}
	}
}

void	PasswordManager::AppendPassword(PasswordClass *c,const QString &password)
{
	PasswordPass	*p=new PasswordPass(c->GetPasswordClassID(),password);
	PasswordPassData.AppendList(p);
}

bool	PasswordManager::IsPasswordExists(const QString &Password)
{
	for(PasswordPass *p=PasswordPassData.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetPassword()==Password){
			return true;
		}
	}
	return false;
}

bool	PasswordManager::SetDefaultFile(const QString &_DefaultPasswordFile)
{
	QFileInfo	FInfo(_DefaultPasswordFile);
	DefaultPasswordFile=FInfo.path()+::GetSeparator()+FInfo.completeBaseName()+QString(".pwd");
	return true;
}

bool	PasswordManager::LoadDefaultFile(void)
{
	QFile	FL(DefaultPasswordFile);
	if(FL.open(QIODevice::ReadOnly)==false){
		return false;
	}
	if(Load(&FL)==false){
		return false;
	}
	return true;
}
bool	PasswordManager::SaveDefaultFile(void)
{
	QFile	FL(DefaultPasswordFile);
	if(FL.open(QIODevice::WriteOnly)==false){
		return false;
	}
	if(Save(&FL)==false){
		return false;
	}
	return true;
}
bool	PasswordManager::IncreaseEntrant(void)
{
	if(HandlerReEntrant==0){
		HandlerReEntrant++;
		return true;
	}
	return false;
}
void	PasswordManager::DecreaseEntrant(void)
{
	HandlerReEntrant--;
}

void	PasswordManager::AppendList(PasswordClass *c)
{
	PasswordClassData.AppendList(c);
}
void	PasswordManager::AppendList(PasswordPass *c)
{
	PasswordPassData.AppendList(c);
}
void	PasswordManager::AppendList(PasswordInControl *c)
{
	PasswordInControlData.AppendList(c);
}

void	PasswordManager::RemoveList(PasswordClass *c)
{
	PasswordClassData.RemoveList(c);
}
void	PasswordManager::RemoveList(PasswordPass *c)
{
	PasswordPassData.RemoveList(c);
}
void	PasswordManager::RemoveList(PasswordInControl *c)
{
	PasswordInControlData.RemoveList(c);
}

void	PasswordManager::UpdateLastTime(void)
{
	LastEditTime=::GetComputerMiliSec();
}
bool	PasswordManager::IsExpired(void)
{
	if(ExpiredTimeSec==0)
		return false;
	if(::GetComputerMiliSec()-LastEditTime>=ExpiredTimeSec*1000){
		EnablePasswordAgain();
		return true;
	}
	return false;
}

bool checkBootupPassword(LayersBase *Base, const QString Keyword ,const QString &PasswordFile)
{
	QDir::setCurrent(QCoreApplication::applicationFilePath());
	QFile	file(PasswordFile);
	if(file.open(QIODevice::ReadOnly)==true){
		QTextStream	Txt(&file);
		QStringList	List[100];
		int	N=0;
		while(Txt.atEnd()==false){
			QString	Password=Txt.readLine(256);
			if(Password.isEmpty()==false){
				List[N]=Password.split(':');
				N++;
			}
		}
		bool	Flag=false;
		for(int i=0;i<N;i++){
			QString	KWord=(List[i])[0];
			if(KWord==Keyword){
				Flag=true;
			}
		}
		if(Flag==true){
			InputPasswordForm	D(Base);
			if(D.exec()==(int)true){
				for(int i=0;i<N;i++){
					QString	PWord=(List[i])[1];
					QString	KWord=(List[i])[0];
					if(D.Password==PWord && KWord==Keyword){
						return true;
					}
				}
			}
			return false;
		}
	}
	return true;
}