#pragma once

#include <QWidget>
#include <QRadioButton>
#include <QStringList>
#include <QLayout>

class RadioButtonSelectWidget : public QWidget
{
	Q_OBJECT

public:
	RadioButtonSelectWidget(QWidget *parent=NULL);
	~RadioButtonSelectWidget();

public:
	void setRadioList(const QStringList &list);
	QStringList radioList() const;

	int currentIndex() const;

public slots:
	void setCurrentIndex(int);

private slots:
	void _changeRadioCheck();

signals:
	void currentIndexChanged(int);

public:
	QRadioButton *operator[](int i){ return m_radioButtonList[i]; };

	int count() const { return m_radioButtonList.count(); };
	int size() const { return count(); };

protected:
	virtual void updateUi();
	virtual void clearOnWidget();

private:
	QList<QRadioButton*> m_radioButtonList;
	QVBoxLayout *m_mainLayout;
	QRadioButton* m_currentRadio;
	bool m_signalOutEnable;
};
