#pragma once

#include <ui_Setting.h>
#include <QFileDialog>
#include <QMessageBox>
#include <qmath.h>
#include "XServiceForLayers.h"

class SettingDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingDialog(LayersBase *base,QWidget *parent=NULL, Qt::WindowFlags f=Qt::Widget)
		:QDialog(parent, f),ServiceForLayers(base)
	{
		ui.setupUi(this);
		InstallOperationLog(this);
	};
	~SettingDialog(){};

public:
	void setImagePath(const QString &imgPath0, const QString &imgPath1, const QString &imgPath2){
		if(ui.leImageFilePathLayer0->text()!=imgPath0){
			ui.leImageFilePathLayer0->setText(imgPath0);
			ui.leImageFilePathLayer0->setToolTip(imgPath0);
			if(QFile::exists(imgPath0)==true){
				updateInf(0);
			}else{
				clearInf(0);
			}
		}

		if(ui.leImageFilePathLayer1->text()!=imgPath1){
			ui.leImageFilePathLayer1->setText(imgPath1);
			ui.leImageFilePathLayer1->setToolTip(imgPath1);
			updateInf(1);
			if(QFile::exists(imgPath1)==true){
				updateInf(1);
			}else{
				clearInf(1);
			}
		}

		if(ui.leImageFilePathLayer2->text()!=imgPath2){
			ui.leImageFilePathLayer2->setText(imgPath2);
			ui.leImageFilePathLayer2->setToolTip(imgPath2);
			updateInf(2);
			if(QFile::exists(imgPath2)==true){
				updateInf(2);
			}else{
				clearInf(2);
			}
		}
	};
	QString imagePath(int layer/* 0-2 */) const {
		switch(layer){
		case 0:
			return (ui.leImageFilePathLayer0->text());
			break;
		case 1:
			return (ui.leImageFilePathLayer1->text());
			break;
		case 2:
			return (ui.leImageFilePathLayer2->text());
			break;
		default:
			return QString();
			break;
		}

		return QString();
	};
public slots:
	void on_pbLoadImageLayer0_clicked()
	{
		QString imagePath = QFileDialog::getOpenFileName(this,
			/**/"Select sorce for shading on Layer 0.",
			/**/QString(),
			/**/"images (*.bmp *.png *.xpm *.jpg *.jpeg)");

		if(imagePath.isEmpty()==true){
			return;
		}

		ui.leImageFilePathLayer0->setText(imagePath);
		ui.leImageFilePathLayer0->setToolTip(imagePath);

		QImage image0(imagePath);

		if(image0.isNull()==false){
			qreal max, min, average;
			getImageMaxMinAverage(image0, 0, max, min, average);

			ui.dsbMaxLayer0->setValue(max);
			ui.dsbMinLayer0->setValue(min);
		}else{
			QMessageBox::warning(this, /**/"Load Error", /**/"File was not loaded.");
		}
	}
	void on_pbLoadImageLayer1_clicked()
	{
		QString imagePath = QFileDialog::getOpenFileName(this,
			/**/"Select sorce for shading on Layer 1.",
			/**/QString(),
			/**/"images (*.bmp *.png *.xpm *.jpg *.jpeg)");

		if(imagePath.isEmpty()==true){
			return;
		}

		ui.leImageFilePathLayer1->setText(imagePath);
		ui.leImageFilePathLayer1->setToolTip(imagePath);

		QImage image1(imagePath);
		
		if(image1.isNull()==false){
			qreal max, min, average;
			getImageMaxMinAverage(image1, 1, max, min, average);

			ui.dsbMaxLayer1->setValue(max);
			ui.dsbMinLayer1->setValue(min);
		}else{
			QMessageBox::warning(this, /**/"Load Error", /**/"File was not loaded.");
		}
	}
	void on_pbLoadImageLayer2_clicked()
	{
		QString imagePath = QFileDialog::getOpenFileName(this,
			/**/"Select sorce for shading on Layer 2.",
			/**/QString(),
			/**/"images (*.bmp *.png *.xpm *.jpg *.jpeg)");

		if(imagePath.isEmpty()==true){
			return;
		}

		ui.leImageFilePathLayer2->setText(imagePath);
		ui.leImageFilePathLayer2->setToolTip(imagePath);

		QImage image2(imagePath);
		
		if(image2.isNull()==false){
			qreal max, min, average;
			getImageMaxMinAverage(image2, 2, max, min, average);

			ui.dsbMaxLayer2->setValue(max);
			ui.dsbMinLayer2->setValue(min);
		}else{
			QMessageBox::warning(this, /**/"Load Error", /**/"File was not loaded.");
		}
	}
	void on_pbClearLayer0_clicked(){
		setImagePath( QString(), imagePath(1), imagePath(2) );
		updateInf(0);
	};
	void on_pbClearLayer1_clicked(){
		setImagePath( imagePath(0), QString(), imagePath(2) );
		updateInf(1);
	};
	void on_pbClearLayer2_clicked(){
		setImagePath( imagePath(2), imagePath(1), QString());
		updateInf(2);
	};


public:
	void updateInf(int layer){
		if(layer==0){
			qreal max = 0;
			qreal min = 0;
			qreal average = 0;

			if(QFile::exists(ui.leImageFilePathLayer0->text())==true){
				getImageMaxMinAverage(QImage(ui.leImageFilePathLayer0->text()), 0, max, min, average);
			}

			ui.dsbMaxLayer0->setValue(max);
			ui.dsbMinLayer0->setValue(min);
		}else if(layer==1){
			qreal max = 0;
			qreal min = 0;
			qreal average = 0;

			if(QFile::exists(ui.leImageFilePathLayer1->text())==true){
				getImageMaxMinAverage(QImage(ui.leImageFilePathLayer1->text()), 1, max, min, average);
			}

			ui.dsbMaxLayer1->setValue(max);
			ui.dsbMinLayer1->setValue(min);
		}else if(layer==2){
			qreal max = 0;
			qreal min = 0;
			qreal average = 0;

			if(QFile::exists(ui.leImageFilePathLayer2->text())==true){
				getImageMaxMinAverage(QImage(ui.leImageFilePathLayer2->text()), 2, max, min, average);
			}

			ui.dsbMaxLayer2->setValue(max);
			ui.dsbMinLayer2->setValue(min);
		}
	};

	void updateInf(){
		updateInf(0);
		updateInf(1);
		updateInf(2);
	};

	void clearInf(int layer){
		if(layer==0 && QFile::exists(ui.leImageFilePathLayer0->text())==true){
			ui.dsbMaxLayer0->setValue(0);
			ui.dsbMinLayer0->setValue(0);
		}else if(layer==1 && QFile::exists(ui.leImageFilePathLayer1->text())==true){
			ui.dsbMaxLayer1->setValue(0);
			ui.dsbMinLayer1->setValue(0);
		}else if(layer==2 && QFile::exists(ui.leImageFilePathLayer2->text())==true){
			ui.dsbMaxLayer2->setValue(0);
			ui.dsbMinLayer2->setValue(0);
		}
	};

	void clearInf(){
		clearInf(0);
		clearInf(1);
		clearInf(2);
	};

public:
	void getImageMaxMinAverage(const QImage &img, int layer, qreal &max, qreal &min, qreal &average){
		qreal MaxValue = -1;
		qreal MinValue = 256;
		qreal sum_all = 0.0;
		if(layer==0){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qRed(img.pixel(x, y));
				}
				sum_x /= img.height();
				sum_all += sum_x;
				if(sum_x>MaxValue){
					MaxValue = sum_x;
				}
				if(sum_x<MinValue){
					MinValue = sum_x;
				}
			}
		}else if(layer==1){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qGreen(img.pixel(x, y));
				}
				sum_x /= img.height();
				sum_all += sum_x;
				if(sum_x>MaxValue){
					MaxValue = sum_x;
				}
				if(sum_x<MinValue){
					MinValue = sum_x;
				}
			}
		}else if(layer==2){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qBlue(img.pixel(x, y));
				}
				sum_x /= img.height();
				sum_all += sum_x;
				if(sum_x>MaxValue){
					MaxValue = sum_x;
				}
				if(sum_x<MinValue){
					MinValue = sum_x;
				}
			}
		}

		max = MaxValue;
		min = MinValue;
		average = sum_all / img.width();
	};
	qreal getDispose(const QImage &img, int layer, int average)
	{
		qreal MaxValue = -1;
		qreal MinValue = 256;
		qreal sum_all = 0.0;
		if(layer==0){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qRed(img.pixel(x, y));
				}
				qreal ave = sum_x / img.height();
				qreal v = (ave - average);
				sum_all += v*v;
			}
		}else if(layer==1){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qGreen(img.pixel(x, y));
				}
				qreal ave = sum_x / img.height();
				qreal v = (ave - average);
				sum_all += v*v;
			}
		}else if(layer==2){
			for(int x=0; x<img.width(); x++){
				qreal sum_x = 0.0;
				for(int y=0; y<img.height(); y++){
					sum_x += qBlue(img.pixel(x, y));
				}
				qreal ave = sum_x / img.height();
				qreal v = (ave - average);
				sum_all += v*v;
			}
		}

		return qSqrt(sum_all);
	};

	void setTarget(qreal target0, qreal target1, qreal target2){
		ui.dsbTargetValueLayer0->setValue(target0);
		ui.dsbTargetValueLayer1->setValue(target1);
		ui.dsbTargetValueLayer2->setValue(target2);
	};

	qreal target(int layer){
		switch(layer){
		case 0:
			return ui.dsbTargetValueLayer0->value();
		case 1:
			return ui.dsbTargetValueLayer1->value();
		case 2:
			return ui.dsbTargetValueLayer2->value();
		default:
			return -1;
		}

		return -1;
	};
	
	void setPreOffset(qreal offset0, qreal offset1, qreal offset2){
		ui.dsbPreOffsetLayer0->setValue(offset0);
		ui.dsbPreOffsetLayer1->setValue(offset1);
		ui.dsbPreOffsetLayer2->setValue(offset2);
	};

	qreal preOffset(int layer){
		switch(layer){
		case 0:
			return ui.dsbPreOffsetLayer0->value();
		case 1:
			return ui.dsbPreOffsetLayer1->value();
		case 2:
			return ui.dsbPreOffsetLayer2->value();
		default:
			return -1;
		}

		return -1;
	};
	
	void setAftOffset(qreal offset0, qreal offset1, qreal offset2){
		ui.dsbAftOffsetLayer0->setValue(offset0);
		ui.dsbAftOffsetLayer1->setValue(offset1);
		ui.dsbAftOffsetLayer2->setValue(offset2);
	};

	qreal aftOffset(int layer){
		switch(layer){
		case 0:
			return ui.dsbAftOffsetLayer0->value();
		case 1:
			return ui.dsbAftOffsetLayer1->value();
		case 2:
			return ui.dsbAftOffsetLayer2->value();
		default:
			return -1;
		}

		return -1;
	};

	QString imagePath(int layer){
		switch(layer){
		case 0:
			return ui.leImageFilePathLayer0->text();
		case 1:
			return ui.leImageFilePathLayer1->text();
		case 2:
			return ui.leImageFilePathLayer2->text();
		default:
			return QString();
		}
	};

private:
	Ui::FilterImageShadingClass ui;
};