#ifndef PRECISIONCHECKER_H
#define PRECISIONCHECKER_H

#include <QMainWindow>
#include "ui_PrecisionChecker.h"
#include "mtGraphicUnit.h"
#include "PrecisionCheckerLib.h"
#include "XServiceForLayers.h"

class PrecisionChecker : public QMainWindow ,public PrecisionCheckerLib,public ServiceForLayers
{
	Q_OBJECT

public:
	PrecisionChecker(LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PrecisionChecker();


	mtGraphicUnit	ImagePanel;

	int nThreshValue;

private:
	Ui::PrecisionCheckerClass ui;

	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);

private slots:
	void on_pushButton_7_clicked();
	void on_btnHistgram_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_clicked();
	void on_chkFlexArea_stateChanged(int);
	void on_chkViewBit_stateChanged(int);
	void on_comboBoxPage_currentIndexChanged(int);
	void on_pushButtonLoadImage_clicked();
	void	SlotOnPaint(QPainter &pnt);
	void	SlotMouseWheel(int delta ,int globalX,int globalY);
};

#endif // PRECISIONCHECKER_H
