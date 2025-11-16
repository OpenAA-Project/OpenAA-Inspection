#include "ShowVRSOperationResource.h"
#include "RadioButtonSelectWidget.h"


RadioButtonSelectWidget::RadioButtonSelectWidget(QWidget *parent)
	:QWidget(parent),m_radioButtonList(),m_mainLayout(new QVBoxLayout()),m_currentRadio(NULL),m_signalOutEnable(false)
{
	setLayout(m_mainLayout);
}

RadioButtonSelectWidget::~RadioButtonSelectWidget()
{
	clearOnWidget();

	for(int i=0; i<m_radioButtonList.count(); i++){
		disconnect(m_radioButtonList[i], SIGNAL(toggled(bool)), this, SLOT(_changeRadioCheck()));
	}

	qDeleteAll(m_radioButtonList);
}

void RadioButtonSelectWidget::setRadioList(const QStringList &list)
{
	clearOnWidget();

	for(int i=0; i<m_radioButtonList.count(); i++){
		disconnect(m_radioButtonList[i], SIGNAL(toggled(bool)), this, SLOT(_changeRadioCheck()));
	}

	qDeleteAll(m_radioButtonList);
	m_radioButtonList.clear();

	for(int i=0; i<list.count(); i++){
		QRadioButton *button = new QRadioButton(list[i], this);
		m_radioButtonList << button;
		connect(button, SIGNAL(toggled(bool)), this, SLOT(_changeRadioCheck()));
	}

	if(list.isEmpty()==false){
		setCurrentIndex(0);
		m_signalOutEnable = true;
	}else{
		m_signalOutEnable = false;
	}

	updateUi();
}

QStringList RadioButtonSelectWidget::radioList() const
{
	QStringList retList;
	for(int i=0; i<m_radioButtonList.count(); i++){
		retList << m_radioButtonList[i]->text();
	}
	return retList;
}

int RadioButtonSelectWidget::currentIndex() const
{
	for(int i=0; i<m_radioButtonList.count(); i++){
		if(m_radioButtonList[i]->isChecked()==true){
			return i;
		}
	}
	return -1;
}

void RadioButtonSelectWidget::setCurrentIndex(int index)
{
	bool oldSignalOut = m_signalOutEnable;
	m_signalOutEnable = false;
	m_currentRadio = NULL;
	for(int i=0; i<m_radioButtonList.count(); i++){
		bool ch = (i==index);
		if(m_radioButtonList[i]->isChecked()!=ch){
			if(ch==false){
				m_radioButtonList[i]->setChecked(false);
			}else{
				m_signalOutEnable = true;
				m_radioButtonList[i]->setChecked(true);
				m_signalOutEnable = false;
				m_currentRadio = m_radioButtonList[i];
			}
		}
	}
	m_signalOutEnable = oldSignalOut;
}

void RadioButtonSelectWidget::updateUi()
{
	clearOnWidget();

	for(int i=0; i<m_radioButtonList.count(); i++){
		m_mainLayout->addWidget(m_radioButtonList[i]);
	}
}

void RadioButtonSelectWidget::clearOnWidget()
{
	while(m_mainLayout->count()!=0){
		m_mainLayout->takeAt(0);
	}
}

void RadioButtonSelectWidget::_changeRadioCheck()
{
	if(m_signalOutEnable==false)return;

	for(int i=0; i<m_radioButtonList.count(); i++){
		if(m_currentRadio!=m_radioButtonList[i] && m_radioButtonList[i]->isChecked()){
			emit currentIndexChanged(i);
			m_currentRadio = m_radioButtonList[i];
			return;
		}
	}
}