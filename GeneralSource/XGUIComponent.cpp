#include "XTypeDef.h"
#include "XGUIComponent.h"
#include <QDebug>
#include "XAlgorithmBase.h"

MemberComponentList::MemberComponentList (void)
{
	MemberID	=-1;
	Comp		=NULL;
	Editted		=false;
}
MemberComponentList::MemberComponentList (int _MemberID ,QWidget *e)
{
	MemberID	=_MemberID;
	Comp		=e;
	Editted		=false;
	SetEditted(false);
}
MemberComponentList::~MemberComponentList(void)
{
}

void	MemberComponentList::SetEditted(bool b)
{	
	Editted=b;
	if(b==false){
		QPalette	P=Comp->palette();
		P.setColor(QPalette::Window	,Qt::lightGray);
		P.setColor(QPalette::Base	,Qt::lightGray);
		Comp->setPalette(P);
	}
	else{
		QPalette	P=Comp->palette();
		P.setColor(QPalette::Window	,Qt::white);
		P.setColor(QPalette::Base	,Qt::white);
		Comp->setPalette(P);
	}
}
void		MemberComponentList::SetValue(const QVariant &c)
{
	Value=c;
}
QVariant	MemberComponentList::GetValue(void)
{
	return Value;
}

//===========================================
class	AlgorithmComponentEater : public QObject
{
	AlgorithmComponentWindow	*Parent;
public:
	explicit	AlgorithmComponentEater(AlgorithmComponentWindow *parent){	Parent=parent;}
protected:
	bool eventFilter(QObject *obj, QEvent *event);
};


bool AlgorithmComponentEater::eventFilter(QObject *obj, QEvent *event)
{
	int	EvType=event->type();
	//qInfo() << QString::number(EvType)<<'\n';

	if(EvType==QEvent::ContextMenu){	//QEvent::MouseButtonPress){
		//QMouseEvent	*ev=dynamic_cast<QMouseEvent *>(event);
		//if(ev!=NULL && ev->button()==Qt::RightButton){
			Parent->mouseRelease(obj);
			return true;
		//}
		//else{
		//	return QObject::eventFilter(obj, event);
		//}
	}
	else{
		return QObject::eventFilter(obj, event);
	}
}
//=============================================================================

AlgorithmComponentWindow::AlgorithmComponentWindow(QWidget *p)
	:QWidget(p)
{
	EnableChangeMode=true;
	InnerEnabled	=true;
	OpenedLogicDLL	=NULL;
}
AlgorithmComponentWindow::~AlgorithmComponentWindow()
{
}

void	AlgorithmComponentWindow::RegisterComponent(int MemberID ,QSpinBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(valueChanged(int)),this,SLOT(SlotValueChangedInt(int)));
	AlgorithmComponentEater	*ms=new AlgorithmComponentEater(this);
	e->installEventFilter(ms);
}
void	AlgorithmComponentWindow::RegisterComponent(int MemberID ,QDoubleSpinBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(valueChanged(double)),this,SLOT(SlotValueChangedDouble(double)));
	AlgorithmComponentEater	*ms=new AlgorithmComponentEater(this);
	e->installEventFilter(ms);
}
void	AlgorithmComponentWindow::RegisterComponent(int MemberID ,QLineEdit *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(textChanged(const QString &)),this,SLOT(SlotTextChanged(const QString &)));
	AlgorithmComponentEater	*ms=new AlgorithmComponentEater(this);
	e->installEventFilter(ms);
}

void	AlgorithmComponentWindow::RegisterComponent(int MemberID ,QCheckBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(stateChanged(int)),this,SLOT(SlotStateChanged(int)));
	AlgorithmComponentEater	*ms=new AlgorithmComponentEater(this);
	e->installEventFilter(ms);
}
void	AlgorithmComponentWindow::RegisterComponent(int MemberID ,QComboBox *e)
{
	MemberComponentList	*r=new MemberComponentList(MemberID,e);
	MemberComponentContainer.AppendList(r);
	connect(e,SIGNAL(currentIndexChanged(int)),this,SLOT(SlotCurrentIndexChanged(int)));
	AlgorithmComponentEater	*ms=new AlgorithmComponentEater(this);
	e->installEventFilter(ms);
}

void	AlgorithmComponentWindow::SlotValueChangedInt(int n)
{
	if(InnerEnabled==true){
		if(EnableChangeMode==true){
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QSpinBox	*e=dynamic_cast<QSpinBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetEditted(true);
					}
				}
			}
		}
		else{
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QSpinBox	*e=dynamic_cast<QSpinBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetValue(n);
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::SlotValueChangedDouble(double n)
{
	if(InnerEnabled==true){
		if(EnableChangeMode==true){
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QDoubleSpinBox	*e=dynamic_cast<QDoubleSpinBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetEditted(true);
					}
				}
			}
		}
		else{
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QDoubleSpinBox	*e=dynamic_cast<QDoubleSpinBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetValue(n);
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::SlotTextChanged(const QString &text)
{
	if(InnerEnabled==true){
		if(EnableChangeMode==true){
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QLineEdit	*e=dynamic_cast<QLineEdit *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetEditted(true);
					}
				}
			}
		}
		else{
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QLineEdit	*e=dynamic_cast<QLineEdit *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetValue(text);
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::SlotStateChanged(int state)
{
	if(InnerEnabled==true){
		if(EnableChangeMode==true){
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QCheckBox	*e=dynamic_cast<QCheckBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetEditted(true);
					}
				}
			}
		}
		else{
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QCheckBox	*e=dynamic_cast<QCheckBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetValue(state);
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::SlotCurrentIndexChanged(int state)
{
	if(InnerEnabled==true){
		if(EnableChangeMode==true){
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QComboBox	*e=dynamic_cast<QComboBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetEditted(true);
					}
				}
			}
		}
		else{
			QObject *p=sender();
			if(p!=NULL){
				QString	objName=p->objectName();
				for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
					QComboBox	*e=dynamic_cast<QComboBox *>(r->GetComponent());
					//if(e!=NULL && e->hasFocus()==true){
					if(e!=NULL && e->objectName()==objName){
						r->SetValue(state);
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::GetEdittedList(IntList &EdittedMemberID)
{
	for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->IsEditted()==true && EdittedMemberID.IsInclude(r->GetMemberID())==false){
			EdittedMemberID.Add(r->GetMemberID());
		}
	}
}

void	AlgorithmComponentWindow::mouseRelease(QObject *obj)
{
	if(EnableChangeMode==true){
		if(obj!=NULL){
			QString	objName=obj->objectName();
			for(MemberComponentList *r=MemberComponentContainer.GetFirst();r!=NULL;r=r->GetNext()){
				QWidget	*e=r->GetComponent();
				//if(e!=NULL && e->hasFocus()==true){
				if(e!=NULL && e->objectName()==objName){
					r->SetEditted(false);

					QSpinBox *eSpinBox=dynamic_cast<QSpinBox *>(r->GetComponent());
					if(eSpinBox!=NULL){
						InnerEnabled=false;
						eSpinBox->setValue(r->GetValue().toInt());
						InnerEnabled=true;
						return;
					}
					QDoubleSpinBox *eDoubleSpinBox=dynamic_cast<QDoubleSpinBox *>(r->GetComponent());
					if(eDoubleSpinBox!=NULL){
						InnerEnabled=false;
						eDoubleSpinBox->setValue(r->GetValue().toDouble());
						InnerEnabled=true;
						return;
					}
					QLineEdit *eLineEdit=dynamic_cast<QLineEdit *>(r->GetComponent());
					if(eLineEdit!=NULL){
						InnerEnabled=false;
						eLineEdit->setText(r->GetValue().toString());
						InnerEnabled=true;
						return;
					}
					QCheckBox *eCheckBox=dynamic_cast<QCheckBox *>(r->GetComponent());
					if(eCheckBox!=NULL){
						InnerEnabled=false;
						eCheckBox->setChecked(r->GetValue().toBool());
						InnerEnabled=true;
						return;
					}
					QComboBox *eComboBox=dynamic_cast<QComboBox *>(r->GetComponent());
					if(eComboBox!=NULL){
						InnerEnabled=false;
						eComboBox->setCurrentIndex(r->GetValue().toInt());
						InnerEnabled=true;
						return;
					}
				}
			}
		}
	}
}

void	AlgorithmComponentWindow::EmitChangeValue(void)
{
	emit	SignalChangeValue();
}

void	AlgorithmComponentWindow::SetLogicDLL(LogicDLL *v)
{
	OpenedLogicDLL=v;
}

void	AlgorithmComponentWindow::closeEvent(QCloseEvent *event)
{
	//emit	SignalClosed();
	QWidget::closeEvent(event);
	if(OpenedLogicDLL!=NULL){
		OpenedLogicDLL->SlotShowAndSetItemsFormClosed();
	}
}