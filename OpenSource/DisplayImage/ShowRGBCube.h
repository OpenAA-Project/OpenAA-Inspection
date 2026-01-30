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

#ifndef SHOWRGBCUBE_H
#define SHOWRGBCUBE_H

#include <QWidget>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include "XColorSpace.h"

namespace Ui {
class ShowRGBCube;
}

class	ShowRGBCube;
class	ShowRGBSpace;

class	ShowRGBColorPanel : public QWidget
{
    friend class	ShowRGBSpace;
    Q_OBJECT

    ShowRGBSpace	*ParentPanel;
public:
    explicit	ShowRGBColorPanel(ShowRGBSpace *parentPanel,QWidget * parent = 0, Qt::WindowFlags f = Qt::Widget );
    virtual	void paintEvent ( QPaintEvent * event )			override;
    virtual	void mouseMoveEvent ( QMouseEvent * event ) 	override;
    virtual	void mousePressEvent ( QMouseEvent * event )	override;
    virtual	void closeEvent ( QCloseEvent * event ) 		override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
};

class ShowRGBSpace : public QWidget
{
    friend class	ShowRGBColorPanel;
    Q_OBJECT

    ShowRGBColorPanel	CPanel;
    int	BaseSizeW;
    int	BaseSizeH;
    int	frameZoneW;
    int	frameZoneH;
    double	ZxPanel;
    double	ZyPanel;
public:
    explicit ShowRGBSpace(QWidget *parent = 0);
    ~ShowRGBSpace();

    ColorLogic	Cube;

    int		GetCurrentBrightness(void);
    void	SetColorMsg(int r ,int g ,int b);
    void	InitializedDoneCube(void);
    void	Repaint(void);
    void	Fit(QWidget *f);
    void	Set(RGBStock &data);

    virtual	void closeEvent ( QCloseEvent * event )	override;

signals:
    void	AddEliminated(void);
    void	DelEliminated(void);
private:
    Ui::ShowRGBCube *ui;

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
private slots:
    void on_VSliderBrightness_valueChanged(int);
    void	SlotAddEliminated(void);
    void	SlotDelEliminated(void);
};

#endif // SHOWRGBCUBE_H