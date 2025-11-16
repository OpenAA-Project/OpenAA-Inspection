/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\WEditParameterTab.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "WEditParameterTab.h"
#include "XDataInLayer.h"
#include "ShowRGBCube.h"
#include "XGeneralDialog.h"
#include <QFile>
#include "EditStringListDialog.h"

const	int		LineHeight=24;

ParamFilePathButton::ParamFilePathButton(WEditParameterTab::EditParamLine *src ,QWidget *parent)
:QPushButton(parent)
{
	Source=src;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}

void	ParamFilePathButton::SlotClicked()
{
	emit ClickedButton(Source);
}

ParamColorLogicButton::ParamColorLogicButton(WEditParameterTab::EditParamLine *src ,QWidget *parent)
:QPushButton(parent)
{
	Source=src;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void	ParamColorLogicButton::SlotClicked()
{
	emit ClickedButton(Source);
}

mtNormalPushed::mtNormalPushed(WEditParameterTab::EditParamLine *src ,QWidget *parent)
:QPushButton(parent)
{
	Line=src;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void	mtNormalPushed::SlotClicked()
{
	emit ClickedButton(Line);
}

mtByteArrayPushed::mtByteArrayPushed(WEditParameterTab::EditParamLine *src ,QWidget *parent)
:QPushButton(parent)
{
	Line=src;
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void	mtByteArrayPushed::SlotClicked()
{
	emit ClickedButton(Line);
}



WEditParameterTab::EditParamLine::EditParamLine(void)
{
	hLabel.setFrameShadow(QFrame::Sunken);
	hLabel.setFrameShape (QFrame::Panel	);
	hLabel.resize(430,20);
	DPoint				=NULL;
	hEdit				=NULL;
	hSpinB				=NULL;
	hCheckBox			=NULL;
	hQComboBox			=NULL;
	hPathFileEdit		=NULL;
	FilePathButton		=NULL;
	hColorButton		=NULL;
	hColorLogicButton	=NULL;
	hStringListButton	=NULL;
	hByteArrayButton	=NULL;
	YNumb				=0;
}
WEditParameterTab::EditParamLine::~EditParamLine(void)
{
	delete	hEdit		;
	delete	hSpinB		;
	delete	hCheckBox	;
	delete	hQComboBox	;
	delete	hPathFileEdit		;
	delete	FilePathButton		;
	delete	hColorButton		;
	delete	hColorLogicButton	;
	delete	hStringListButton	;
	delete	hByteArrayButton	;

	DPoint				=NULL;
	hSpinB				=NULL;
	hEdit				=NULL;
	hCheckBox			=NULL;
	hQComboBox			=NULL;
	hPathFileEdit		=NULL;
	FilePathButton		=NULL;
	hColorButton		=NULL;
	hColorLogicButton	=NULL;
	hStringListButton	=NULL;
	hByteArrayButton	=NULL;
}

void	WEditParameterTab::EditParamLine::SetYNumb(int Width,int ynumb)
{
	
	YNumb=ynumb;
	hLabel.move(10,10+LineHeight*YNumb);
	int	W1;
	int	W2;
	if(hPathFileEdit==NULL){
		W1=Width*0.7;
		hLabel.resize(W1,hLabel.height());
		W2=Width-10-W1-8-18;
	}
	else{
		W1=Width*0.7-100;
		hLabel.resize(W1,hLabel.height());
		W2=Width-10-W1-8-18;
	}
	int	H=LineHeight-3;

	if(hEdit!=NULL){
		hEdit->move(W1+18,10+LineHeight*YNumb);
		hEdit->resize(W2,H);
	}
	if(hSpinB!=NULL){
		hSpinB->move(W1+18,10+LineHeight*YNumb);
		hSpinB->resize(W2,H);
	}
	if(hCheckBox!=NULL){
		hCheckBox->move(W1+18,10+LineHeight*YNumb);
		hCheckBox->resize(W2,H);
	}
	if(hQComboBox!=NULL){
		hQComboBox->move(W1+18,10+LineHeight*YNumb);
		hQComboBox->resize(W2,H);
	}

	if(hPathFileEdit!=NULL){
		hPathFileEdit->move(W1+18,10+LineHeight*YNumb);
		hPathFileEdit->resize(W2-H-10,H);
	}
	if(FilePathButton!=NULL){
		FilePathButton->move(W1+18+W2-H-10+8,10+LineHeight*YNumb);
		FilePathButton->resize(H,H);
	}


	if(hColorButton!=NULL){
		hColorButton->move(W1+18,10+LineHeight*YNumb);
		hColorButton->resize(W2,H);
	}
	if(hColorLogicButton!=NULL){
		hColorLogicButton->move(W1+18,10+LineHeight*YNumb);
		hColorLogicButton->resize(W2,H);
	}
	if(hStringListButton!=NULL){
		hStringListButton->move(W1+18,10+LineHeight*YNumb);
		hStringListButton->resize(W2,H);
	}
	if(hByteArrayButton!=NULL){
		hByteArrayButton->move(W1+18,10+LineHeight*YNumb);
		hByteArrayButton->resize(W2,H);
	}
}

void	WEditParameterTab::EditParamLine::SetParent(QWidget *w)
{
	hLabel.setParent(w);
	hLabel.show();
	if(hEdit!=NULL){
		hEdit->setParent(w);
		hEdit->show();
	}
	if(hSpinB!=NULL){
		hSpinB->setParent(w);
		hSpinB->show();
	}
	if(hCheckBox!=NULL){
		hCheckBox->setParent(w);
		hCheckBox->show();
	}
	if(hQComboBox!=NULL){
		hQComboBox->setParent(w);
		hQComboBox->show();
	}
	if(hPathFileEdit!=NULL){
		hPathFileEdit->setParent(w);
		hPathFileEdit->show();
	}
	if(FilePathButton!=NULL){
		FilePathButton->setParent(w);
		FilePathButton->show();
	}
	if(hColorButton!=NULL){
		hColorButton->setParent(w);
		hColorButton->show();
	}
	if(hColorLogicButton!=NULL){
		hColorLogicButton->setParent(w);
		hColorLogicButton->show();
	}
	if(hStringListButton!=NULL){
		hStringListButton->setParent(w);
		hStringListButton->show();
	}
	if(hByteArrayButton!=NULL){
		hByteArrayButton->setParent(w);
		hByteArrayButton->show();
	}
}

WEditParameterTab::ParametersInTab::~ParametersInTab(void)
{
	ParamData.RemoveAll();
}

WEditParameterTab::WEditParameterTab(ParamBase *pbase,int _EnableCondition,QWidget *parent)
    : QTabWidget(parent)
{
	PBase=pbase;
    setObjectName(QString::fromUtf8(/**/"WEditParameterTab"));
	EnableCondition=_EnableCondition;
	
	if(parent!=NULL){
		resize(parent->width(),parent->height());
	}
	else{
		resize(580,400);
	}
	Initial(EnableCondition,15);
	move(10,16);
	setEnabled( true );
	setFocusPolicy(Qt::TabFocus);
	setTabShape(QTabWidget::Triangular);
}

WEditParameterTab::~WEditParameterTab()
{
	ParametersInTabData.RemoveAll();
}
void WEditParameterTab::closeEvent ( QCloseEvent * event )
{
	emit	SignalClose();

	QTabWidget::closeEvent (event);
	deleteLater ();
}

void	WEditParameterTab::Initial(int _EnableCondition ,int MaxRowCount)
{
	EnableCondition=_EnableCondition;

	ParametersInTabData.RemoveAll();
	for(ParamBase::ParamStruct *p=PBase->ParamData.GetFirst();p!=NULL;p=p->GetNext()){
		ParametersInTab *k;
		for(k=ParametersInTabData.GetFirst();k!=NULL;k=k->GetNext()){
			if(k->TabName==p->Category && k->ParamData.GetNumber()<=(MaxRowCount-1)){
				break;
			}
		}
		if(k==NULL){
			k=new ParametersInTab();
			k->TabName=p->Category;
			ParametersInTabData.AppendList(k);
		}
		EditParamLine	*c=new EditParamLine();
		c->DPoint=p;
		c->hLabel.setText(p->Explain);

		QColor	CBase=Qt::cyan;
		QPalette P;
		bool	Colored=false;
		if(EnableCondition!=-1 && EnableCondition!=0 && (EnableCondition & p->EnableCondition)==0){
			Colored=true;
		}
		//Colored=true;

		switch(p->rType){
			case ParamBase::__int64__:
				c->hEdit=new QLineEdit();
				c->hEdit->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hEdit->setPalette(P);
					c->hEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__WORD__:
				c->hSpinB=new QSpinBox();
				c->hSpinB->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hSpinB->palette();
					P.setColor(QPalette::Base,CBase);
					c->hSpinB->setPalette(P);
					c->hSpinB->setReadOnly(true);
				}
				break;
			case ParamBase::__int32__:
				c->hEdit=new QLineEdit();
				c->hEdit->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hEdit->setPalette(P);
					c->hEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__double__:
				c->hEdit=new QLineEdit();
				c->hEdit->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hEdit->setPalette(P);
					c->hEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__QString__:
				c->hEdit=new QLineEdit();
				c->hEdit->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hEdit->setPalette(P);
					c->hEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__QColor__:
				c->hColorButton=new mtPushButtonColored();
				c->hColorButton->resize(100,LineHeight-3);
				break;
			case ParamBase::__ColorLogic__:
				c->hColorLogicButton=new ParamColorLogicButton(c,this);
				c->hColorLogicButton->resize(30,LineHeight-3);
				c->hColorLogicButton->setText(/**/"...");
				connect(c->hColorLogicButton,SIGNAL(ClickedButton(WEditParameterTab::EditParamLine *))
					,this,SLOT(ColorLogicButtonClicked(WEditParameterTab::EditParamLine *)));
				break;
			case ParamBase::__bool__:
				c->hCheckBox=new QCheckBox();
				c->hCheckBox->setText(/**/"");
				c->hCheckBox->resize(100,LineHeight-3);
				if(Colored==true){
					P=c->hCheckBox->palette();
					P.setColor(QPalette::Base,CBase);
					c->hCheckBox->setPalette(P);
					c->hCheckBox->setEnabled(false);
				}
				break;
			case ParamBase::__FileName__:
				c->hPathFileEdit=new QLineEdit();
				c->hLabel.resize(330,LineHeight-4);
				c->hPathFileEdit->resize(180,LineHeight-3);
				c->FilePathButton=new ParamFilePathButton(c,this);
				c->FilePathButton->resize(21,LineHeight-3);
				c->FilePathButton->setText(/**/"...");
				connect(c->FilePathButton,SIGNAL(ClickedButton(WEditParameterTab::EditParamLine *))
					,this,SLOT(FileButtonClicked(WEditParameterTab::EditParamLine *)));
				if(Colored==true){
					P=c->hPathFileEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hPathFileEdit->setPalette(P);
					c->hPathFileEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__Path__:
				c->hPathFileEdit=new QLineEdit();
				c->hLabel.resize(330,LineHeight-4);
				c->hPathFileEdit->resize(180,LineHeight-3);
				c->FilePathButton=new ParamFilePathButton(c,this);
				c->FilePathButton->resize(LineHeight-3,LineHeight-3);
				c->FilePathButton->setText(/**/"...");
				connect(c->FilePathButton,SIGNAL(ClickedButton(WEditParameterTab::EditParamLine *))
					,this,SLOT(PathButtonClicked(WEditParameterTab::EditParamLine *)));
				if(Colored==true){
					P=c->hPathFileEdit->palette();
					P.setColor(QPalette::Base,CBase);
					c->hPathFileEdit->setPalette(P);
					c->hPathFileEdit->setReadOnly(true);
				}
				break;
			case ParamBase::__QStringList__:
				c->hStringListButton=new mtNormalPushed(c,this);
				c->hStringListButton->resize(30,LineHeight-3);
				c->hStringListButton->setText(/**/"...");
				connect(c->hStringListButton,SIGNAL(ClickedButton(WEditParameterTab::EditParamLine *))
					,this,SLOT(StringListButtonClicked(WEditParameterTab::EditParamLine *)));

				break;
			case ParamBase::__ByteArray__:
				c->hByteArrayButton=new mtByteArrayPushed(c,this);
				c->hByteArrayButton->resize(100,LineHeight-3);
				connect(c->hByteArrayButton,SIGNAL(ClickedButton(WEditParameterTab::EditParamLine *))
					,this,SLOT(ByteArrayButtonClicked(WEditParameterTab::EditParamLine *)));
				break;
			default:
				break;
		}
		k->ParamData.AppendList(c);
	}

	while(count()!=0){
		removeTab(0);
	}
	int	W=width();
	int	pnumb=0;
	for(ParametersInTab *k=ParametersInTabData.GetFirst();k!=NULL;k=k->GetNext(),pnumb++){
		int	n=count();
		QString	TabName=GetParamBase()->GetCategoryLabel(k->TabName);
		if(TabName.isEmpty()==true){
			TabName=k->TabName;
		}
		QWidget	*w;
		if(n<=pnumb){	
			w=new QWidget();
			w->setGeometry(0,0,500,500);
			addTab(w,TabName);
		    w->setObjectName(QString::fromUtf8(/**/"tab")+k->TabName);
		}
		else{
			w=widget(pnumb);
		}
		if(w!=NULL){
			setTabText(pnumb,TabName);
			int	YNumb=0;
			for(EditParamLine *c=k->ParamData.GetFirst();c!=NULL;c=c->GetNext() ,YNumb++){
				c->SetParent(w);
				c->SetYNumb(W,YNumb);
			}
		}
	}
    setCurrentIndex(0);
	ShowToWindow();
}

void	WEditParameterTab::Set(ParamBase *pbase,int _EnableCondition)
{
	PBase=pbase;
	EnableCondition=_EnableCondition;
	Initial(EnableCondition,15);
}

void WEditParameterTab::resizeEvent(QResizeEvent *e)
{
	ParametersInTabData.RemoveAll();

	QTabBar *Bar=tabBar();
	int	BarHight=Bar->height();
	int	H=height()-BarHight-10-2;
	int	N=H/LineHeight;
	Initial(EnableCondition ,N);
}


void	WEditParameterTab::FileButtonClicked(WEditParameterTab::EditParamLine *Src)
{
	QString	FName=QFileDialog::getOpenFileName (NULL, Src->DPoint->Name);
	if(FName.isEmpty()==false){
		Src->hPathFileEdit->setText(FName);
	}
}
void	WEditParameterTab::PathButtonClicked(WEditParameterTab::EditParamLine *Src)
{
	QString	PName=QFileDialog::getExistingDirectory (0, Src->DPoint->Name);
	if(PName.isEmpty()==false){
		Src->hPathFileEdit->setText(PName);
	}
}
void	WEditParameterTab::ColorLogicButtonClicked	(WEditParameterTab::EditParamLine *Src)
{
#if	!defined(NoColorButton)
	ShowRGBSpace	*s=new ShowRGBSpace();
	s->Cube=*Src->DPoint->pVarColorLogic;
	s->InitializedDoneCube();
	GeneralDialog	D(NULL,s,this);
	D.exec();
#endif
}
void	WEditParameterTab::StringListButtonClicked	(WEditParameterTab::EditParamLine *Src)
{
	EditStringListDialog	D(Src->hStringListButton->GetStringList());
	if(D.exec()==QDialog::Accepted){
		Src->hStringListButton->SetStringList(D.Str);
	}
}
void	WEditParameterTab::ByteArrayButtonClicked	(WEditParameterTab::EditParamLine *Src)
{
	QByteArray Data;
	Data=Src->DPoint->GetByteArray();
	Src->DPoint->Parent->ExecuteForByteArray(Src->DPoint->Category,Src->DPoint->Name,Data);
	Src->DPoint->SetValue(Data);
	if(Src->hByteArrayButton!=NULL){
		Src->hByteArrayButton->SetByteArray(Data);
	}
}

void	WEditParameterTab::ShowToWindow(void)
{
	for(ParametersInTab *k=ParametersInTabData.GetFirst();k!=NULL;k=k->GetNext()){
		for(EditParamLine *c=k->ParamData.GetFirst();c!=NULL;c=c->GetNext()){
			ParamBase::ParamStruct *p=c->DPoint;

			c->hLabel.setText(p->Explain);
			switch(p->rType){
				case ParamBase::__int64__:
					c->hEdit->setText(p->GetValue());
					break;
				case ParamBase::__WORD__:
					c->hSpinB->setValue(p->GetValue().toInt());
					break;
				case ParamBase::__int32__:
					c->hEdit->setText(p->GetValue());
					break;
				case ParamBase::__double__:
					c->hEdit->setText(p->GetValue());
					break;
				case ParamBase::__QString__:
					c->hEdit->setText(p->GetValue());
					break;
				case ParamBase::__QColor__:
					c->hColorButton->setColor(p->GetValue());
					break;
				case ParamBase::__bool__:
					if(p->GetValue().toUpper()==/**/"TRUE"){
						c->hCheckBox->setCheckState(Qt::Checked);
					}
					else{
						c->hCheckBox->setCheckState(Qt::Unchecked);
					}
					break;
				case ParamBase::__FileName__:
					c->hPathFileEdit->setText(p->GetValue());
					break;
				case ParamBase::__Path__:
					c->hPathFileEdit->setText(p->GetValue());
					break;
				case ParamBase::__QStringList__:
					c->hStringListButton->SetStringList(p->GetStringList());
					break;
				case ParamBase::__ByteArray__:
					c->hByteArrayButton->setText(/**/"Data");
					break;
				default:
					break;
			}
		}
	}
}


void	WEditParameterTab::LoadFromWindow(void)
{
	int	pnumb=0;
	for(ParametersInTab *k=ParametersInTabData.GetFirst();k!=NULL;k=k->GetNext(),pnumb++){
		QWidget	*w=widget(pnumb);
		if(w==NULL){
			continue;
		}
		int	YNumb=0;
		for(EditParamLine *c=k->ParamData.GetFirst();c!=NULL;c=c->GetNext() ,YNumb++){
			if(c->hEdit!=NULL){
				c->DPoint->SetValue(c->hEdit->text());
			}
			if(c->hSpinB!=NULL){
				c->DPoint->SetValue(QString::number(c->hSpinB->value()));
			}
			if(c->hPathFileEdit!=NULL){
				c->DPoint->SetValue(c->hPathFileEdit->text());
			}
			else if(c->hCheckBox!=NULL){
				if(c->hCheckBox->checkState()==Qt::Checked){
					c->DPoint->SetBoolValue(true);
				}
				else{
					c->DPoint->SetBoolValue(false);
				}
			}
			else if(c->hColorButton!=NULL){
				c->DPoint->SetValue(c->hColorButton->color());
			}
			else if(c->hStringListButton!=NULL){
				c->DPoint->SetValue(c->hStringListButton->GetStringList());
			}
			else if(c->hByteArrayButton!=NULL){
				c->DPoint->SetValue(c->hByteArrayButton->GetByteArray());
			}
		}
	}
}

QString	WEditParameterTab::GetDataText(void)
{
	return(PBase->GetDataText());
}

bool	WEditParameterTab::Save(QIODevice *f)
{
	return PBase->SaveParam(f);
}
bool	WEditParameterTab::Load(QIODevice *f)
{
	return PBase->LoadParam(f);
}

