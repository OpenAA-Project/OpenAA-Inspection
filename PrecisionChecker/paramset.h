#ifndef PARAMSET_H
#define PARAMSET_H

#include <QWidget>
#include "ui_paramset.h"

class ParamSet : public QWidget
{
	Q_OBJECT

public:
	ParamSet(QWidget *parent = 0);
	~ParamSet();

	void getThreshValue(int &min, int &max, bool &mode);

	bool getAxisVal(double &val);
	int  getZScale(int idx);
	bool getChartType(int idx);
	void getInitRotation(int &x, int &y, int &z);
	void getPadValueRange(int &min, int &max);
	void getAvgXY(int &x, int &y);
	QString getOutDir();

	void getBrightMode(bool &mode);

private:
	Ui::ParamSetClass ui;

	bool bAxisFlg;

	bool saveParam(QString fnam);
	bool loadParam(QString fnam);

	QString defParamFnam;

private slots:
	void on_pushButton_3_clicked();
	void on_pushButton_2_clicked();
	void on_btnSelect_clicked();
	void on_rbAxis_2_toggled(bool);
	void on_rbAxis_1_toggled(bool);
	void on_pushButton_clicked(); 
};

#endif // PARAMSET_H
