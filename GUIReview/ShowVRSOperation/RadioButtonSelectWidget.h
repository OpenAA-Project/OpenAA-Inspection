/*
 * Copyright (C) 2012
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