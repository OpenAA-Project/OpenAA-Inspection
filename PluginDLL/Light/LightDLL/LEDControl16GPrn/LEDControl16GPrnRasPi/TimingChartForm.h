#ifndef TIMINGCHARTFORM_H
#define TIMINGCHARTFORM_H

#include <QWidget>
#include <QLabel>
#include <QScrollBar>
#include "XTypeDef.h"
#include "XGioDefineSignal.h"

namespace Ui {
class TimingChartForm;
}
class LEDControl16GPrnRasPi;
class TimingSignalPort;
class TimingChartForm;

class TitlePanelWidget : public QWidget
{
    Q_OBJECT

	TimingSignalPort	*Parent;
public:
	QLabel		LabelPortType;
	QLabel		LabelPortName;
    QLabel		LabelCurrentValue;

	TitlePanelWidget(TimingSignalPort *parent);
	~TitlePanelWidget();

	void	Initial(void);
    void    ShowTimeLine(DWORD TimeLine);
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
	TimingSignalPort	*Parent;
public:
    DWORD   TimeLine;

	SignalPanelWidget(TimingSignalPort *parent);
	~SignalPanelWidget();

    void    ShowTimeLine(DWORD TimeLine);
private:
    virtual	void paintEvent(QPaintEvent *event)     override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

class TimingSignalPort: public QObject
{
	friend	class TitlePanelWidget;
	friend	class SignalPanelWidget;
	
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
    void	RepaintSignal(void);
    void    ShowTimeLine(DWORD TimeLine);
};


class SignalScale : public QWidget
{
    TimingChartForm	*Parent;
public:
    DWORD   TimeLine;
    SignalScale(TimingChartForm *p,QWidget *parent);

private:
    virtual	void paintEvent(QPaintEvent *event)	override;
};


class TimingChartForm : public QWidget
{
    Q_OBJECT

public:
    QWidget				*WidgetSignal;
	QWidget				*WidgetTitle ;
    SignalScale         *Scale;
	TimingSignalPort	*TimingSignal[50];
    LEDControl16GPrnRasPi	*Panel;
	int					SignalCount;

    int     CurrentFirstPoint;
    DWORD   CurrrentMilisec;
    int     CurrentTimingCount;

    QScrollBar  *TimingVerticalScroller;
    QScrollBar  *TitleVerticalScroller;
public:
    explicit TimingChartForm(LEDControl16GPrnRasPi *p,QWidget *parent = 0);
    ~TimingChartForm();

    bool        GetSamplingMode(void);
    DWORD		GetStartMilisec(void);
    DWORD		GetScrollStartMilisec(void);
	int			GetTimeUnit(void);
    void	RepaintSignals(void);

    void    ShowTimeLine(DWORD TimeLine);
private slots:
    void on_pushButtonUpdate_clicked();
	void on_horizontalScrollBar_valueChanged(int value);
	void SlotVScrollChanged(int);
	void	SlotUpper(int id);
	void	SlotLower(int id);
    void on_pushButtonClear_clicked();
    void    SlotTimingValueChanged(int v);
    void    SlotTitleValueChanged(int v);
private:
    Ui::TimingChartForm *ui;

	virtual	void resizeEvent(QResizeEvent *event)	override;

};

#endif // TIMINGCHARTFORM_H
