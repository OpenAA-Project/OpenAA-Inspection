#ifndef LIGHTDLL8PORTFORM_H
#define LIGHTDLL8PORTFORM_H

#include <QDialog>
#include "ui_LightDLL8PortForm.h"
#include "LightDLL1.h"
#include "LED64CTRLib.h"

class LightDLL8PortForm : public QDialog
{
	Q_OBJECT

public:
	LightDLL8PortForm(LightDLL1	*p,QWidget *parent = 0);
	~LightDLL8PortForm();

	LightDLLBase	*InspectionLight;
	LightDLL1		BLight;

private:
	Ui::LightDLL8PortFormClass ui;

	QCheckBox	*ChkList[8][64];
	QLabel		*LabelList[8][64];

	virtual	void	showEvent (QShowEvent * event)	override;


private slots:
	void on_tb_8_clicked();
	void on_tb_7_clicked();
	void on_pbCancel_clicked();
	void on_pbOK_clicked();
	void on_pbClearSelect_clicked();
	void on_pbAllSelect_clicked();
	void on_tbOnOff_clicked();
	void on_pbTransport_clicked();
	void on_sbBrightness_valueChanged(int);
	void on_vsBrightness_valueChanged(int);
	void on_tbRight_15_clicked();
	void on_tbRight_14_clicked();
	void on_tbRight_13_clicked();
	void on_tbRight_12_clicked();
	void on_tbRight_11_clicked();
	void on_tbRight_10_clicked();
	void on_tbRight_9_clicked();
	void on_tbRight_8_clicked();
	void on_tbRight_7_clicked();
	void on_tbRight_6_clicked();
	void on_tbRight_5_clicked();
	void on_tbRight_4_clicked();
	void on_tbRight_3_clicked();
	void on_tbRight_2_clicked();
	void on_tbRight_1_clicked();
	void on_tbRight_0_clicked();
	void on_tbLeft_15_clicked();
	void on_tbLeft_14_clicked();
	void on_tbLeft_13_clicked();
	void on_tbLeft_12_clicked();
	void on_tbLeft_11_clicked();
	void on_tbLeft_10_clicked();
	void on_tbLeft_9_clicked();
	void on_tbLeft_8_clicked();
	void on_tbLeft_7_clicked();
	void on_tbLeft_6_clicked();
	void on_tbLeft_5_clicked();
	void on_tbLeft_4_clicked();
	void on_tbLeft_3_clicked();
	void on_tbLeft_2_clicked();
	void on_tbLeft_1_clicked();
	void on_tbLeft_0_clicked();
	void on_tb_6_clicked();
	void on_tb_5_clicked();
	void on_tb_4_clicked();
	void on_tb_3_clicked();
	void on_tb_2_clicked();
	void on_tb_1_clicked();
	void on_tbTopRight_clicked();
	void on_tbTopLeft_clicked();
};

#endif // LIGHTDLL8PORTFORM_H
