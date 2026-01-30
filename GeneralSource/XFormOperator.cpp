/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "XTypeDef.h"
#include "XFormOperator.h"
#include<QAbstractButton>
#include<QTableView>
#include<QLineEdit>
#include<QSpinBox>
#include<QTableWidget>
#include <QMetaObject>
#include <QMetaMethod>

static	QWidget	*SearchWidgetReEntrant2(QWidget *W,const QString &ControlName);

static	QWidget	*SearchWidgetReEntrant(QWidget *W,const QString &FormName ,const QString &ControlName)
{
	if(W==NULL){
		return NULL;
	}
	if(W->objectName()==FormName){
		QWidget	*Ret=SearchWidgetReEntrant2(W,ControlName);
		if(Ret!=NULL){
			return Ret;
		}
	}

	QObjectList C=W->children();
	for(int i=0;i<C.count();i++){
		QObject	*k=C.at(i);
		QWidget	*w=dynamic_cast<QWidget *>(k);
		if(w!=NULL){
			QWidget	*Ret=SearchWidgetReEntrant(w,FormName ,ControlName);
			if(Ret!=NULL){
				return Ret;
			}
		}
	}
	return NULL;
}

static	QWidget	*SearchWidgetReEntrant2(QWidget *W,const QString &ControlName)
{
	if(W==NULL){
		return NULL;
	}
	if(W->objectName()==ControlName){
		return W;
	}

	QObjectList C=W->children();
	for(int i=0;i<C.count();i++){
		QObject	*k=C.at(i);
		QWidget	*w=dynamic_cast<QWidget *>(k);
		if(w!=NULL){
			QWidget	*Ret=SearchWidgetReEntrant2(w,ControlName);
			if(Ret!=NULL){
				return Ret;
			}
		}
	}
	return NULL;
}


static	QWidget	*SearchFormReEntrant(QWidget *W,const QString &FormName)
{
	if(W==NULL){
		return NULL;
	}
	if(W->objectName()==FormName){
		return W;
	}

	QObjectList C=W->children();
	for(int i=0;i<C.count();i++){
		QObject	*k=C.at(i);
		QWidget	*w=dynamic_cast<QWidget *>(k);
		if(w!=NULL){
			QWidget	*Ret=SearchFormReEntrant(w,FormName);
			if(Ret!=NULL){
				return Ret;
			}
		}
	}
	return NULL;
}


QWidget	*FormOperator::SearchWidget(const QString &FormName ,const QString &ControlName)
{
	return SearchWidgetReEntrant(MainForm,FormName ,ControlName);
}

QWidget	*FormOperator::SearchForm(const QString &FormName)
{
	return SearchFormReEntrant(MainForm,FormName);
}


bool	FormOperator::ButtonPush(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c!=NULL){
		c->click();
		return true;
	}
	return false;
}

bool	FormOperator::ButtonDown(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c==NULL){
		return false;
	}
	c->setChecked(true);
	return true;
}

bool	FormOperator::ButtonUp(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c==NULL){
		return false;
	}
	c->setChecked(false);
	return true;
}


bool	FormOperator::CheckboxChecked(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c==NULL){
		return false;
	}
	c->setChecked(true);
	return true;
}

bool	FormOperator::CheckboxUnchecked(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c==NULL){
		return false;
	}
	c->setChecked(false);
	return true;
}
bool	FormOperator::CheckboxToggle(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QAbstractButton	*c=dynamic_cast<QAbstractButton *>(W);
	if(c==NULL){
		return false;
	}
	if(c->isChecked()==true){
		c->setChecked(false);
	}
	else{
		c->setChecked(true);
	}
	return true;
}


bool	FormOperator::TableSelect		(const QString &FormName ,const QString &ControlName,int row ,int column)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QTableView	*c=dynamic_cast<QTableView *>(W);
	if(c==NULL){
		return false;
	}
	QAbstractItemView	*cc=dynamic_cast<QAbstractItemView *>(c);
	c->selectRow(row);
	c->selectColumn(column);
	QModelIndex		CIndex=c->indexAt(QPoint(column,row));
	QModelIndex		MIndex=CIndex.sibling(row,column);
	//emit	c->click(CIndex);

	const	QMetaObject *m= cc->metaObject();

	for(int i=0;i<m->methodCount();i++){
		QMetaMethod	E=m->method (i);
#if QT_VERSION <= 0x040807
		if(QString(E.signature())==QString(/**/"clicked(QModelIndex)")){
#else
		if (E.methodSignature() == QString(/**/"clicked(QModelIndex)")) {
#endif
			E.invoke(c,Q_ARG(QModelIndex,MIndex));
		}
	}

	return true;
}

bool	FormOperator::TableDoubleClick(const QString &FormName ,const QString &ControlName,int row ,int column)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QTableView	*c=dynamic_cast<QTableView *>(W);
	if(c==NULL){
		return false;
	}
	c->selectRow(row);
	c->selectColumn(column);
	return true;
}

bool	FormOperator::InputEdit(const QString &FormName ,const QString &ControlName ,const QString &Data)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QLineEdit	*c=dynamic_cast<QLineEdit *>(W);
	if(c==NULL){
		return false;
	}
	c->setText(Data);
	return true;
}

bool	FormOperator::InputValue(const QString &FormName ,const QString &ControlName ,int value)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QSpinBox	*c=dynamic_cast<QSpinBox *>(W);
	if(c==NULL){
		return false;
	}
	c->setValue(value);
	return true;
}

bool	FormOperator::ExistForm(const QString &FormName)
{
	QWidget	*W=SearchForm(FormName);
	if(W==NULL || W->isVisible()==false || W->isEnabled()==false){
		return false;
	}
	return true;
}

bool	FormOperator::SetVisible(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	W->setVisible(true);
	return true;
}
bool	FormOperator::SetInvisible(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	W->setVisible(false);
	return true;
}

bool	FormOperator::SetEnabled(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	W->setEnabled(true);
	return true;
}
bool	FormOperator::SetDisabled(const QString &FormName ,const QString &ControlName)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	W->setEnabled(false);
	return true;
}
bool	FormOperator::TableItemSearchSelect(const QString &FormName ,const QString &ControlName
											,int column,const QString &SearchStr)
{
	QWidget	*W=SearchWidget(FormName ,ControlName);
	if(W==NULL){
		return false;
	}
	QTableWidget	*c=dynamic_cast<QTableWidget *>(W);
	if(c==NULL){
		return false;
	}
	int RowCnt=c->rowCount();
	int row;
	for(row=0;row<RowCnt;row++){
		if(c->item(row,column)->text()==SearchStr){
			break;
		}
	}
	if(row==RowCnt){
		return false;
	}
	c->selectRow(row);
	c->selectColumn(column);
	return true;
}