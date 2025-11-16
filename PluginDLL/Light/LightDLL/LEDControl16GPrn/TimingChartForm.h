#ifndef TIMINGCHARTFORM_H
#define TIMINGCHARTFORM_H

#include <QWidget>
#include <QLabel>
#include "XGioDefineSignal.h"
#include "LEDControl16GPrn.h"

namespace Ui {
class TimingChartForm;
}
class LEDControl16GPanel;
class TimingSignalPort;
class TimingChartForm;

class TitlePanelWidget : public QWidget
{
    Q_OBJECT

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
	int		ID;
	int		PortType;
	int		BitNo;
	int		TurnN;
	TimingChartForm	*Parent;
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
	LEDControl16GPanel	*Panel;
	int					SignalCount;
public:
    explicit TimingChartForm(LEDControl16GPanel *p,QWidget *parent = 0);
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
