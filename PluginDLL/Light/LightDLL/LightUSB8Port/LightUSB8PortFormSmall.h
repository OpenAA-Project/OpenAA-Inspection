#ifndef LIGHTUSB8PORTFORMSMALL_H
#define LIGHTUSB8PORTFORMSMALL_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include "XLightControlFromUSB.h"

namespace Ui {
    class LightUSB8PortFormSmall;
}

class LightUSB8PortFormSmall : public QDialog
{
    Q_OBJECT
	LightControlFromUSB	*BLight;
public:
    explicit LightUSB8PortFormSmall(LightControlFromUSB	*iLight ,QWidget *parent = 0);
    ~LightUSB8PortFormSmall();

	QCheckBox	*ChkList[8][64];
	QLabel		*LabelList[8][64];

	LightControlFromUSB	*GetBLight(void)	{	return BLight;	}

	virtual	void	showEvent(QShowEvent *)					override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:
    void on_tbTopLeft_clicked();
    void on_tbTopRight_clicked();
    void on_tb_1_clicked();
    void on_tb_2_clicked();
    void on_tb_3_clicked();
    void on_tb_4_clicked();
    void on_tb_5_clicked();
    void on_tb_6_clicked();
    void on_tb_7_clicked();
    void on_tb_8_clicked();
    void on_tbLeft_0_clicked();
    void on_tbLeft_1_clicked();
    void on_tbLeft_2_clicked();
    void on_tbLeft_3_clicked();
    void on_tbLeft_4_clicked();
    void on_tbLeft_5_clicked();
    void on_tbLeft_6_clicked();
    void on_tbLeft_7_clicked();
    void on_tbLeft_8_clicked();
    void on_tbLeft_9_clicked();
    void on_tbLeft_10_clicked();
    void on_tbLeft_11_clicked();
    void on_tbLeft_12_clicked();
    void on_tbLeft_13_clicked();
    void on_tbLeft_14_clicked();
    void on_tbLeft_15_clicked();
    void on_tbRight_0_clicked();
    void on_tbRight_1_clicked();
    void on_tbRight_2_clicked();
    void on_tbRight_3_clicked();
    void on_tbRight_4_clicked();
    void on_tbRight_5_clicked();
    void on_tbRight_6_clicked();
    void on_tbRight_7_clicked();
    void on_tbRight_8_clicked();
    void on_tbRight_9_clicked();
    void on_tbRight_10_clicked();
    void on_tbRight_11_clicked();
    void on_tbRight_12_clicked();
    void on_tbRight_13_clicked();
    void on_tbRight_14_clicked();
    void on_tbRight_15_clicked();
    void on_pbOK_clicked();
    void on_pbCancel_clicked();
    void on_pbAllSelect_clicked();
    void on_pbClearSelect_clicked();
    void on_pbTransport_clicked();
    void on_tbOnOff_clicked();
    void on_vsBrightness_valueChanged(int value);
    void on_sbBrightness_valueChanged(int arg1);

private:
    Ui::LightUSB8PortFormSmall *ui;
};

#endif // LIGHTUSB8PORTFORMSMALL_H
