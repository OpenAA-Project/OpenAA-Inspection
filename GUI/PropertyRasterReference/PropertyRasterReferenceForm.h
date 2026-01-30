/*
 * Copyright (C) 2024
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

#ifndef PROPERTYRASTERREFERENCEFORM_H
#define PROPERTYRASTERREFERENCEFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XGUIFormBase.h"
#include <QDialog>
#include <QScrollArea>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "XGUIPacketForDLL.h"
#include "mtPushButtonColored.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"
#include "XRaster.h"
#include "XRasterPacket.h"
#include "XGUIRasterPacket.h"
#include "XColorConvert.h"

namespace Ui {
class PropertyRasterReferenceForm;
}

class PropertyRasterReferenceForm : public GUIFormBase
{
    Q_OBJECT

    ColorProfileContainer   ColorProfiler;
public:
    explicit PropertyRasterReferenceForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyRasterReferenceForm();

    RasterBase	    *GetRasterBase(void);
    virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonModeShowPDF_clicked();
    void on_toolButtonModeShowReference_clicked();
    void on_pushButtonAutoPickUp_clicked();
    void on_pushButtonSaveColorProfile_clicked();

    void	SlotImageClicked(int Line);
    void	SlotRasterClicked(int Line);


    void on_pushButtonSaveDefaultColorProfile_clicked();

private:
    Ui::PropertyRasterReferenceForm *ui;

    DisplayImageWithAlgorithm	*GetImagePanel(void);
    void	RepaintImage(void);
    void	ShowGrid(void);
};

//----------------------------------------------------------------------
class	ColorProfileColorButton : public mtPushButtonColored
{
    Q_OBJECT

    int Line;
public:
    ColorProfileColorButton(int Line);
private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int Line);
};

#endif // PROPERTYRASTERREFERENCEFORM_H