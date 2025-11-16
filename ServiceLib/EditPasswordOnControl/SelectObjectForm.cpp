#include "XTypeDef.h"
#include "SelectObjectForm.h"
#include "ui_SelectObjectForm.h"
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QString>
#include <QRadioButton>
#include "XGeneralFuncCore.h"

SelectObjectForm::SelectObjectForm(QWidget *_StartObject, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectObjectForm)
{
    ui->setupUi(this);

	StartObject=_StartObject;
	QTreeWidgetItem	*Top=new QTreeWidgetItem(ui->treeWidget);
	ui->treeWidget->addTopLevelItem(Top);
	SetObjectText(0,Top,StartObject);
	AddChild(0,Top,StartObject);
}

SelectObjectForm::~SelectObjectForm()
{
    delete ui;
}

bool	SelectObjectForm::SetObjectText(int Index,QTreeWidgetItem *ThisTree,QObject *thisObj)
{
	QPushButton	*d1=dynamic_cast<QPushButton *>(thisObj);
	if(d1!=NULL){
		if(d1->text().isEmpty()==false)
			ThisTree->setText(0,QString("QPushButton : ")+d1->text());
		else
			ThisTree->setText(0,QString("QPushButton : ")+d1->objectName());
		ThisTree->setFlags(Qt::ItemIsSelectable | ThisTree->flags());
		return true;
	}
	QToolButton *d2=dynamic_cast<QToolButton *>(thisObj);
	if(d2!=NULL){
		if(d2->text().isEmpty()==false)
			ThisTree->setText(0,QString("QToolButton : ")+d2->text());
		else
			ThisTree->setText(0,QString("QToolButton : ")+d2->objectName());
		ThisTree->setFlags(Qt::ItemIsSelectable | ThisTree->flags());
		return true;
	}
	QCheckBox *d3=dynamic_cast<QCheckBox *>(thisObj);
	if(d3!=NULL){
		if(d3->text().isEmpty()==false)
			ThisTree->setText(0,QString("QCheckBox : ")+d3->text());
		else
			ThisTree->setText(0,QString("QCheckBox : ")+d3->objectName());
		ThisTree->setFlags(Qt::ItemIsSelectable | ThisTree->flags());
		return true;
	}
	QRadioButton *d4=dynamic_cast<QRadioButton *>(thisObj);
	if(d4!=NULL){
		ThisTree->setText(0,QString("QRadioButton : ")+d4->text());
		ThisTree->setFlags(Qt::ItemIsSelectable | ThisTree->flags());
		return true;
	}
	QWidget	*dxx=dynamic_cast<QWidget *>(thisObj);
	if(dxx!=NULL){
		ThisTree->setText(0,QString("Widget no selectable : ")+dxx->objectName());
		//ThisTree->setFlags(Qt::NoItemFlags);
		return false;
	}

	ThisTree->setText(0,QString("Object no selectable : ")+thisObj->objectName());
	//ThisTree->setFlags(Qt::NoItemFlags);

	return false;
}

void	SelectObjectForm::AddChild(int Index,QTreeWidgetItem *ParentTree,QObject *ParentObject)
{
	for(int i=0;i<ParentObject->children().count();i++){
		QObject	*d=ParentObject->children()[i];
		QTreeWidgetItem	*C=new QTreeWidgetItem(ParentTree);
		if(SetObjectText(Index,C,d)==true){
			C->setData(1,Qt::UserRole,GetSelectedObjPath(d));
		}
		ParentTree->addChild(C);
		AddChild(Index+1,C,d);
	}
}

void SelectObjectForm::on_pushButtonSelect_clicked()
{
	QTreeWidgetItem *C=ui->treeWidget->currentItem ();
	if(C!=NULL){
		SelectedObjPath=C->data(1,Qt::UserRole).toString();
		ControlMode	=ui->comboBoxControlMode->currentIndex();
		done(true);
	}
}

QString	SelectObjectForm::GetSelectedObjPath(QObject *d)
{
	QString	Ret;

	while(d!=NULL){
		if(Ret.isEmpty()==false){
			Ret=d->objectName()+::GetSeparator()+Ret;
		}
		else{
			Ret=d->objectName();
		}
		if(d==dynamic_cast<QObject*>(StartObject)){
			return Ret;
		}
		d=d->parent();
	}
	return /**/"";
}

void SelectObjectForm::on_pushButtonCancel_clicked()
{
	done(false);
}

QObject *SelectObjectForm::GetChildObject(const QStringList &ObjList ,int Index ,QObject *CurrentObject)
{
	if(CurrentObject->objectName()!=ObjList[Index]){
		return NULL;
	}
	if(Index<ObjList.count()-1){
		for(int j=0;j<CurrentObject->children().count();j++){
			QObject *ret=GetChildObject(ObjList ,Index+1 ,CurrentObject->children()[j]);
			if(ret!=NULL){
				return ret;
			}
		}
		return NULL;
	}
	return CurrentObject;
}

void SelectObjectForm::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	QTreeWidgetItem *C=ui->treeWidget->currentItem ();
	QString	SelectPath=C->data(1,Qt::UserRole).toString();
	QStringList	ObjList=SelectPath.split(QChar('/'));
	QObject	*Obj=GetChildObject(ObjList ,0,StartObject);
	if(Obj!=NULL){
		QPushButton	*d1=dynamic_cast<QPushButton *>(Obj);
		if(d1!=NULL){
			ui->lineEditType	->setText("QPushButton");
			ui->lineEditObject	->setText(d1->objectName());
			ui->lineEditText	->setText(d1->text());
			return;
		}
		QToolButton *d2=dynamic_cast<QToolButton *>(Obj);
		if(d2!=NULL){
			ui->lineEditType	->setText("QToolButton");
			ui->lineEditObject	->setText(d2->objectName());
			ui->lineEditText	->setText(d2->text());
			return;
		}
		QCheckBox *d3=dynamic_cast<QCheckBox *>(Obj);
		if(d3!=NULL){
			ui->lineEditType	->setText("QCheckBox");
			ui->lineEditObject	->setText(d3->objectName());
			ui->lineEditText	->setText(d3->text());
			return;
		}
		QRadioButton *d4=dynamic_cast<QRadioButton *>(Obj);
		if(d4!=NULL){
			ui->lineEditType	->setText("QRadioButton");
			ui->lineEditObject	->setText(d4->objectName());
			ui->lineEditText	->setText(d4->text());
			return;
		}
	}
}
