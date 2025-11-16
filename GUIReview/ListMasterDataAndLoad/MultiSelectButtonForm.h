#pragma once

#include <QList>
#include <QDialog>
#include <QPushButton>

#include "ui_MultiSelectButtonForm.h"

//
// [class infomation]
//  This class is able to select multi button as checked.
//  User check some button and push OK button, therfore result() method will return buddy data.
// 
// [usage]
//  MultiSelectButtonForm<int> form; // int is buddy
//  form.addButton(0, "First");   // make button. 0 is buddy, "First" is button's name
//  form.addButton(1, "Second");  // make button. 1 is buddy, "Second" is button's name
//  form.addButton(2, "Third");   // make button. 2 is buddy, "Third" is button's name
//  if(form.exec()==QDialog::Accepted){ // user input
//		QList<int> resList = form.result(); // buddy list of all button checked return.
//		if(resList.isEmpty()==false){// If not checked all, return empty list.
//			// use the result.
//		}
//  }else{
//		// user rejected the form.
//  }
//  


template<typename T>
class MultiSelectButtonForm : public QDialog
{
public:
	MultiSelectButtonForm(QWidget *parent=NULL, Qt::WindowFlags f=0)
		:QDialog(parent, f)
	{
		ui.setupUi(this);
	};

public:
	void setButtonList(const QList<QPair<T, QString> > &buttons, const QList<bool> &initCheckList=QList<bool>()){
		_clearButtonList();
		addButtonList(buttons, initCheckList);
	};
	void setButtonList(const QList<T> &buddyList, const QList<QString> nameList, const QList<bool> &initCheckList=QList<bool>()){
		_clearButtonList();
		addButtonList(idList, nameList, initCheckList);
	};

	void addButtonList(const QList<QPair<T, QString> > &buttons, const QList<bool> &initCheckList=QList<bool>()){
		int index=0;
		for(; index<buttons.count() && index<initCheckList.count(); index++){
			addButton(buttons.at(index).first, buttons.at(index).second, initCheckList[index]);
		}
		for(; index<buttons.count(); index++){
			addButton(buttons.at(index).first, buttons.at(index).second, false);
		}
	};
	void addButtonList(const QList<T> &buddyList, const QList<QString> nameList, const QList<bool> &initCheckList=QList<bool>()){
		int index=0;
		for(; index<idList.count() && index<nameList.count() && index<initCheckList.count(); index++){
			addButton(idList.at(index), nameList.at(index), initCheckList[index]);
		}
		for(; index<idList.count() && index<nameList.count(); index++){
			addButton(idList.at(index), nameList.at(index), false);
		}
	};
	void addButton(const T &buddy, const QString &name, bool checked=false){
		QPushButton *button = new QPushButton;
		button->setText(name);
		button->setCheckable(true);
		button->setChecked(checked);
		_addButtonList(QPair<T, QPushButton*>(buddy, button));
		ui.vlMachineButtonList->addWidget(button);
	};

	void clear(){
		_clearButtonList();

		while(ui.vlMachineButtonList->count()!=0){
			delete ui.vlMachineButtonList->takeAt(0);
		}
	};

	QList<T> result() const{
		QList<T> retList;
		const QList<QPair<T, QPushButton*> > &buttons = _buttonList();
		for(int i=0; i<buttons.count(); i++){
			if(buttons[i].second->isChecked()==true){
				retList.append( buttons[i].first );
			}
		}
		return retList;
	};

private:
	inline const QList<QPair<T, QPushButton*> > &_buttonList() const { return m_buttonList; };
	inline QList<QPair<T, QPushButton*> > &_buttonList() { return m_buttonList; };
	void _addButtonList(const QPair<T, QPushButton*> buttonData){ m_buttonList.append( buttonData ); };
	void _removeButton(QPushButton *button){
		for(int i=0; i<m_buttonList.count(); i++){
			if(m_buttonList[i].second==button){
				m_buttonList.removeAt(i);
			}
		}
	};
	T _buttonBuddy(QPushButton *button, bool *ok=NULL) const {
		const QList<QPair<int, QPushButton*> > &buttons = _buttonList();
	
		for(int i=0; i<buttons.count(); i++){
			if(buttons[i].second==button){
				if(ok!=NULL){
					*ok = true;
				}
				return buttons[i].first;
			}
		}

		if(ok!=NULL){
			*ok = false;
		}
		return T();
	};
	void _clearButtonList(){
		m_buttonList.clear();
	}

private:
	Ui::MultiSelectButtonClass ui;
	QList<QPair<T, QPushButton*> > m_buttonList;
};
