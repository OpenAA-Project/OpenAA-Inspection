/*
 * Copyright (C) 2022
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

#ifndef LENSWINDOWFORM_H
#define LENSWINDOWFORM_H

#include <QWidget>
#include <QImage>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XDisplayImage.h"

namespace Ui {
class LensWindowForm;
}
class	LayersBase;

class LensWindowForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	GUICmdSendBmp	**BmpReceiver;
	GUICmdReqBmp	**BmpRequester;
	int				AllocedBmp;
	DisplayType		DType;
	int				CurrentGlobalX,CurrentGlobalY;
	double			ZoomRate;
	DisplayImage	*TargetPanel;
	QTimer			TM;
public:
    explicit LensWindowForm(LayersBase *base,QWidget *parent = 0);
    ~LensWindowForm();

	void	AllocInnerBuff(void);
	void	ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY , DisplayType dtype);
private:
    Ui::LensWindowForm *ui;

	virtual	void paintEvent ( QPaintEvent * event ) override;
	void	ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy);
	void	ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy);
	
	virtual	void hideEvent ( QHideEvent * event )	override;
	virtual	void closeEvent ( QCloseEvent * event )	override;
	virtual	void resizeEvent ( QResizeEvent * event ) override;
signals:
	void	SignalClose();
private slots:
	void	SlotTimeout();
	void	SlotCloseEvent();
};

#endif // LENSWINDOWFORM_H