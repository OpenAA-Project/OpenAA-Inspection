#ifndef LEDCONTROL16GTESTER_H
#define LEDCONTROL16GTESTER_H

#include <QMainWindow>
#include "ui_LEDControl16GTester.h"
#include <QMutex>

class	HidCommand;


#define	MaxCountLEDPattern	16

struct	__LEDLine
{
	int		BaseCounter;
	int		HighCounter;
    int     TargetValue;
};

struct	__LEDPattern
{
	struct	__LEDLine	LEDLine[16];
};


class LEDControl16GTester : public QMainWindow
{
	Q_OBJECT

	HidCommand	*Commander;
	QMutex		AccessHID;
	int			DipSW;

	struct	__LEDPattern	LEDPattern[MaxCountLEDPattern];
	int	AnalogData[16];

public:
	LEDControl16GTester(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LEDControl16GTester();

private slots:
    void on_pushButtonReqVersion_clicked();
    void on_pushButtonReqAttr_clicked();
    void on_pushButtonSetAttr_clicked();
    void on_pushButtonReqBaseCounter_clicked();
    void on_pushButtonSetBaseCounter_clicked();
    void on_pushButtonReqHighCounter_clicked();
    void on_pushButtonSetHighCounter_clicked();
    void on_pushButtonReqAnalog_clicked();
    void on_pushButtonReqBit_clicked();
    void on_pushButtonOutRPOut_clicked();
    void on_pushButtonOutBit_clicked();
    void on_checkBoxO_InRW_clicked();
    void on_checkBoxO_InClk_clicked();
    void on_checkBoxO_InCS_clicked();
    void on_pushButtonReqTargetValue_clicked();
    void on_pushButtonSetTargetValue_clicked();

private:
	Ui::LEDControl16GTesterClass ui;

	bool	Open(void);
};

#endif // LEDCONTROL16GTESTER_H
