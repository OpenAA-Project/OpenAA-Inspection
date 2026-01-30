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

#ifndef SHOWRGBSAMPLES_H
#define SHOWRGBSAMPLES_H

#include <QWidget>
#include "XColorSpace.h"

namespace Ui {
class ShowRGBSamples;
}

class ShowRGBSamples;

class	ShowRGBSamplesPanel : public QWidget
{
    friend class	ShowRGBSamples;
    Q_OBJECT

    ShowRGBSamples	*ParentPanel;
public:
    explicit	ShowRGBSamplesPanel(ShowRGBSamples *parentPanel,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );
    
    virtual	void paintEvent ( QPaintEvent * event )			override;
    virtual	void mouseMoveEvent ( QMouseEvent * event ) 	override;
    virtual	void mousePressEvent ( QMouseEvent * event )	override;
    virtual	void closeEvent ( QCloseEvent * event ) 		override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
};

class ShowRGBSamples : public QWidget
{
    friend class	ShowRGBSamplesPanel;
    Q_OBJECT

    ShowRGBSamplesPanel	CPanel;
    int	BaseSizeW;
    int	BaseSizeH;
    int	frameZoneW;
    int	frameZoneH;
    double	ZxPanel;
    double	ZyPanel;

public:
    explicit ShowRGBSamples(QWidget *parent = 0);
    ~ShowRGBSamples();

    RGBStock	Cube;
    int			Ext;

    int		GetExtended(void);
    int		GetCurrentBrightness(void);
    void	SetColorMsg(int r ,int g ,int b);
    void	InitializedDoneCube(void);
    void	Repaint(void);
    void	Fit(QWidget *f);

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);

private slots:
    void on_VSliderBrightness_valueChanged(int value);
    void on_spinBoxExtend_valueChanged(int arg1);
    void	SlotAddEliminated(void);
    void	SlotDelEliminated(void);

private:
    Ui::ShowRGBSamples *ui;

    virtual	void closeEvent ( QCloseEvent * event ) override;
};

#endif // SHOWRGBSAMPLES_H