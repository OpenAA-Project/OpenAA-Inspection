/*
 * Copyright (C) 2023
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

#ifndef LARGECOLORDIFFERENCEFORM_H
#define LARGECOLORDIFFERENCEFORM_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XPasswordQWidget.h"

namespace Ui {
class LargeColorDifferenceForm;
}

class	ThumbnailPanel;
class	LargeColorDifferenceForm;

class	FrameLargeWindowColorDifference : public QWidget
{
    Q_OBJECT
		
	friend	class LargeColorDifferenceForm;

	LargeColorDifferenceForm	*Parent;
	bool	ShowingMasterImage;
	QTimer	FlipTimer;
public:
	FrameLargeWindowColorDifference(LargeColorDifferenceForm *p);

	void	StartTimer(void);
private slots:
	void	SlotTimeOut();


private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class	FrameMasterWindowColorDifference : public QWidget
{
    Q_OBJECT
		
	friend	class LargeColorDifferenceForm;

	LargeColorDifferenceForm	*Parent;

public:
	FrameMasterWindowColorDifference(LargeColorDifferenceForm *p);

private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};


class LargeColorDifferenceForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
	friend	class	ThumbnailPanel;
	friend	class	FrameLargeWindowColorDifference;
	friend	class	FrameMasterWindowColorDifference;

	Qt::WindowFlags	SavedFlag;
	ThumbnailPanel	*Parent;
	QImage	NGImage;
	QImage	NGMarkImage;
	QImage	MasterImage;
	LearningMenu	LearningMenuDim[100];
	int				LearningMenuDimNumb;
	FrameLargeWindowColorDifference		ImagePanel;
	FrameMasterWindowColorDifference	MasterPanel;

public:
    explicit LargeColorDifferenceForm(ThumbnailPanel *p ,QWidget *parent = nullptr);
    ~LargeColorDifferenceForm();

	void	Initial(void);
	bool	ShowDrawNGMark(void);

signals:
	void	SignalShowDetail();

private slots:
    void on_PushButtonOKbyDeltaE_clicked();
    void on_PushButtonOKbyDeltaEWhole_clicked();
    void on_toolButtonShowNGMark_triggered(QAction *arg1);
    void on_pushButtonDetail_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::LargeColorDifferenceForm *ui;

	virtual	void	showEvent(QShowEvent *event) override;
	virtual	void	closeEvent ( QCloseEvent * event ) override;
};

#endif // LARGECOLORDIFFERENCEFORM_H