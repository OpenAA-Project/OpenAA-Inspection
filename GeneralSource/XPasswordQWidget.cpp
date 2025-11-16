#include "XTypeDef.h"
#include "XPasswordQWidget.h"
#include "XGUI.h"
#include "XDataInLayer.h"
#include "XPassword.h"
#include "SelectObjectForm.h"
#include "PasswordDropper.h"
#include "XGeneralFunc.h"
#include <QLineEdit>
#include <QAbstractButton>
#include "XDataInLayer.h"


extern	QString	GetdObjPathWidget(QObject *d);

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

PasswordInQWodget::PasswordInQWodget(LayersBase *base ,QWidget *parent)
	:Base(base)
{
	ParentWidget=parent;
	if(Base->GetEditPasswordMode()==true && parent!=NULL){
		SetAllAcceptDrops(parent,true);
	}
}



static	void	InstallEventHandlerChild(QObject *c,LayersBase *Base,PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData)
{
	PasswordFilter *k;

	QWidget	*d=dynamic_cast<QWidget	*>(c);
	if(d!=NULL){
		k=f->CreateNew(Base,c);
		PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(k));
		d->installEventFilter(k);
		d->setAcceptDrops(true);
	}

	QObjectList Q=c->children();
	for(int i=0;i<Q.count();i++){
		InstallEventHandlerChild(Q[i],Base,f,PasswordFilterPointerData);
	}
}


void	PasswordInQWodget::InstallEventHandler(PasswordFilter *f,NPListPack<PasswordFilterPointerList> &PasswordFilterPointerData)
{
	ParentWidget->installEventFilter(f);
	PasswordFilterPointerData.AppendList(new PasswordFilterPointerList(f));
	ParentWidget->setAcceptDrops(true);

	QObjectList Q=ParentWidget->children();
	for(int i=0;i<Q.count();i++){
		InstallEventHandlerChild(Q[i],Base,f,PasswordFilterPointerData);
	}
}


static	void	InstallEventHandlerOnlyPasswordChild(QObject *c,LayersBase *Base,PasswordFilter *f,PasswordInControl *m)
{
	QString	CurrentPath=GetdObjPathWidget(c);
	if(m->GetControlPathName()==CurrentPath){
		QAbstractButton	*vButton=dynamic_cast<QAbstractButton *>(c);
		if(vButton!=NULL){
			vButton->installEventFilter(f->CreateNew(Base,c));
			vButton->setAcceptDrops(true);
		}
		QLineEdit	*LEdit=dynamic_cast<QLineEdit *>(c);
		if(LEdit!=NULL){
			LEdit->installEventFilter(f->CreateNew(Base,c));
			LEdit->setAcceptDrops(true);
		}
		QAbstractSpinBox	*SBox=dynamic_cast<QAbstractSpinBox	*>(c);
		if(SBox!=NULL){
			SBox->installEventFilter(f->CreateNew(Base,c));
			SBox->setAcceptDrops(true);
		}
	}
	QObjectList Q=c->children();
	for(int i=0;i<Q.count();i++){
		InstallEventHandlerOnlyPasswordChild(Q[i],Base,f,m);
	}
}
void	PasswordInQWodget::InstallEventHandlerOnlyPassword(PasswordFilter *f,PasswordInControl *c)
{
	QString	ObjPath;
	GetObjectPath(ParentWidget,ObjPath);
	if(c->GetControlPathName()==ObjPath && c->GetControlName()==ParentWidget->objectName()){
		ParentWidget->installEventFilter(f->CreateNew(Base,ParentWidget));
		ParentWidget->setAcceptDrops(true);
	}
	QObjectList Q=ParentWidget->children();
	for(int i=0;i<Q.count();i++){
		InstallEventHandlerOnlyPasswordChild(Q[i],Base,f,c);
	}
}

void	PasswordInQWodget::SetupPassword(void)
{
	std::shared_ptr<PasswordManager>	P=Base->GetPasswordHolder();
	PasswordFilter *passwordFilter = new PasswordFilter(Base,ParentWidget);
	if(P->GetModeOfEditPassword()==true && P->GetDropperForm()!=NULL){
		NPListPack<PasswordFilterPointerList>	PasswordFilterPointerData;
		InstallEventHandler(passwordFilter,PasswordFilterPointerData);

		for(PasswordFilterPointerList *p=PasswordFilterPointerData.GetFirst();p!=NULL;p=p->GetNext()){
			P->GetDropperForm()->connect(p->IndexPoint,SIGNAL(SignalDropped(QObject*)),P->GetDropperForm(),SLOT(SlotDropped (QObject*)));
		}
	}
	else{
		for(PasswordInControl *c=P->GetPasswordInControlData().GetFirst();c!=NULL;c=c->GetNext()){
			InstallEventHandlerOnlyPassword(passwordFilter,c);
		}
	}
}
