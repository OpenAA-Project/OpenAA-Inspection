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

#ifndef LARGEFLATINSPECTIONFORM_H
#define LARGEFLATINSPECTIONFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XLearningRegist.h"
#include "XPasswordQWidget.h"

namespace Ui {
class	LargeFlatInspectionForm;
}

class	ThumbnailPanel;
class	LargeFlatInspectionForm;

class	LFIFrameLargeWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeFlatInspectionForm;

	LargeFlatInspectionForm	*Parent;
	bool	ShowingMasterImage;
	QTimer	FlipTimer;
public:
	LFIFrameLargeWindow(LargeFlatInspectionForm *p);

	void	StartTimer(void);
private slots:
	void	SlotTimeOut();


private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class	LFIFrameMasterWindow : public QWidget
{
    Q_OBJECT
		
	friend	class LargeFlatInspectionForm;

	LargeFlatInspectionForm	*Parent;

public:
	LFIFrameMasterWindow(LargeFlatInspectionForm *p);

private:
	virtual	void	paintEvent(QPaintEvent *event) override;
};

class LargeFlatInspectionForm : public QWidget,public ServiceForLayers,public PasswordInQWodget
{
    Q_OBJECT
	friend	class	ThumbnailPanel;
	friend	class	LFIFrameLargeWindow;
	friend	class	LFIFrameMasterWindow;

	Qt::WindowFlags	SavedFlag;
	ThumbnailPanel	*Parent;
	QImage	NGImage;
	QImage	NGMarkImage;
	QImage	MasterImage;
	LearningMenu	LearningMenuDim[100];
	int				LearningMenuDimNumb;
	LFIFrameLargeWindow	ImagePanel;
	LFIFrameMasterWindow	MasterPanel;

public:
    explicit LargeFlatInspectionForm(ThumbnailPanel *p ,QWidget *parent = nullptr);
    ~LargeFlatInspectionForm();

	void	Initial(void);
	bool	ShowDrawNGMark(void);

signals:
	void	SignalShowDetail();

private slots:
    void on_PushButtonOKbyColorWhole_clicked();
    void on_PushButtonOKbyShiftWhole_clicked();
    void on_PushButtonOKbySizeWhole_clicked();
    void on_toolButtonShowNGMark_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::LargeFlatInspectionForm *ui;

	virtual	void	showEvent(QShowEvent *event) override;
	virtual	void	closeEvent ( QCloseEvent * event ) override;
};

#endif // LARGEFLATINSPECTIONFORM_H