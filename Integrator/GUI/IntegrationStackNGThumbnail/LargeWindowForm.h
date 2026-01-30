/*
 * Copyright (C) 2025
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

#ifndef LARGEWINDOWFORM_H
#define LARGEWINDOWFORM_H

#include <QWidget>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XPasswordQWidget.h"

namespace Ui {
class	LargeWindowForm;
}
namespace LargeWindow{
class	FrameLargeWindow;
class	FrameMasterWindow;
}

class	ThumbnailPanel;
class	LargeWindowForm;

class	LargeWindow::FrameLargeWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeWindowForm;

	LargeWindowForm	*Parent;
	bool	ShowingMasterImage;
	QTimer	FlipTimer;
public:
	FrameLargeWindow(LargeWindowForm *p);

	void	StartTimer(void);
private slots:
	void	SlotTimeOut();


private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class	LargeWindow::FrameMasterWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeWindowForm;

	LargeWindowForm	*Parent;

public:
	FrameMasterWindow(LargeWindowForm *p);

private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};


class LargeWindowForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
    
	friend	class	ThumbnailPanel;
	friend	class	LargeWindow::FrameLargeWindow;
	friend	class	LargeWindow::FrameMasterWindow;

	Qt::WindowFlags	SavedFlag;
	ThumbnailPanel	*Parent;
	QImage	NGImage;
	QImage	NGMarkImage;
	QImage	MasterImage;
	LearningMenu	LearningMenuDim[100];
	int				LearningMenuDimNumb;
	LargeWindow::FrameLargeWindow	ImagePanel;
	LargeWindow::FrameMasterWindow	MasterPanel;

public:
    explicit LargeWindowForm(ThumbnailPanel *p ,QWidget *parent = 0);
    ~LargeWindowForm();
    
	bool	ShowDrawNGMark(void);

signals:
	void	SignalShowDetail();

private slots:
    void on_toolButtonShowNGMark_clicked();
    void on_pushButtonClose_clicked();
    void on_PushButtonOKbyColor_clicked();
    void on_PushButtonOKbyShift_clicked();
    void on_PushButtonOKbySize_clicked();
    void on_PushButtonOKbyColorWhole_clicked();
    void on_PushButtonOKbyShiftWhole_clicked();
    void on_PushButtonOKbySizeWhole_clicked();
    void on_pushButtonDetail_clicked();

private:
    Ui::LargeWindowForm *ui;

	virtual	void	showEvent(QShowEvent *event) override;
	virtual	void	closeEvent ( QCloseEvent * event ) override;
};

#endif // LARGEWINDOWFORM_H