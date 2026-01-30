/*
 * Copyright (C) 2024
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

#ifndef TIMINGCHARTFORM_H
#define TIMINGCHARTFORM_H

#include <QWidget>
#include <QLabel>
#include "XJioDefineSignal.h"
#include "LEDControl16JioPrn.h"

namespace Ui {
class TimingChartForm;
}
class LEDControl16JioPanel;
class TimingSignalPort;
class TimingChartForm;

class TitlePanelWidget : public QWidget
{
    Q_OBJECT

public:
	TimingSignalPort	*Parent;
public:
	QLabel		LabelPortType;
	QLabel		LabelPortName;

	TitlePanelWidget(TimingSignalPort *parent);
	~TitlePanelWidget();

	void	Initial(void);
protected:
	virtual	void mouseReleaseEvent(QMouseEvent *event)	override;

signals:
	void	SignalUpper(int id);
	void	SignalLower(int id);

private slots:
	void	SlotUpper();
	void	SlotLower();
};

class SignalPanelWidget : public QWidget
{
public:
	TimingSignalPort	*Parent;
public:
	SignalPanelWidget(TimingSignalPort *parent);
	~SignalPanelWidget();

private:
	virtual	void paintEvent(QPaintEvent *event)	override;
};

class TimingSignalPort: public QObject
{
public:
	TimingChartForm	*Parent;
public:
	int		ID;
	int		PortType;
	int		BitNo;
	int		TurnN;
public:
	TitlePanelWidget	TitlePanel;
	SignalPanelWidget	SignalPanel;

	TimingSignalPort(TimingChartForm *p,int id,int _PortType ,int _BitNo);
	~TimingSignalPort();

	void	Initial(void);
	void	SetTurn(int n ,QWidget *WidgetSignal ,QWidget *WidgetTitle);
	void	Resize(void);
	void	Repaint(void);
};

class TimingChartForm : public QWidget
{
    Q_OBJECT

public:
    QWidget				*WidgetSignal;
	QWidget				*WidgetTitle ;
	TimingSignalPort	*TimingSignal[50];
	LEDControl16JioPanel	*Panel;
	int					SignalCount;
public:
    explicit TimingChartForm(LEDControl16JioPanel *p,QWidget *parent = 0);
    ~TimingChartForm();

	DWORD		GetStartTime(void);
	int			GetTimeUnit(void);
private slots:
    void on_pushButtonUpdate_clicked();
	void on_horizontalScrollBar_valueChanged(int value);
	void SlotVScrollChanged(int);
	void	SlotUpper(int id);
	void	SlotLower(int id);

private:
    Ui::TimingChartForm *ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;

};

#endif // TIMINGCHARTFORM_H