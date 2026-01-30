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

#ifndef PROPERTYCOUNTERFORM_H
#define PROPERTYCOUNTERFORM_H

#include "XGUIFormBase.h"
#include "XCounter.h"
#include "XStandardPropertyForm.h"
#include <QTimer>
#include "XDoubleClass.h"

namespace Ui {
class PropertyCounterForm;
}

#define		CounterDebugMode


class PropertyCounterForm : public GUIFormBase
{
    Q_OBJECT
    
	QTimer	BlinkMaskTimer;
	bool	FlipMask;
	int		ResultCount;
    bool	FoundItemImage;
    ButtonRightClickEnabler *MaskingButtonEnabler;
public:
    explicit PropertyCounterForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyCounterForm();

    virtual void	ReadyParam(void)                        override;
	virtual	void	BuildForShow(void)						override;
  	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
   
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
	void	AddCount(int n);
private slots:
    void on_toolButtonRegisterItem_clicked();
    void on_toolButtonRegisterBackGround_clicked();
    void on_horizontalSliderThreshold_valueChanged(int value);
	void	SlotBlinkMask();
    void on_tableWidgetAngle_itemSelectionChanged();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_toolButtonFilter_clicked();
    void on_horizontalSliderAdoptPixelsRate_valueChanged(int value);
    void on_horizontalSliderFocusLevel_valueChanged(int value);
    void on_checkBoxOutsideCalc_clicked();
    void on_tabWidgetItem_currentChanged(int index);
    void on_toolButtonMaskArea_clicked();
    void	SlotMaskRightClicked(QAbstractButton *obj);
private:
    Ui::PropertyCounterForm *ui;

	QImage		ItemImage;
	QImage		ItemImageWithMask;
	QImage		ItemBackGround;

	DoubleList	Angles;
	QList<QImage>	RotatedImages;

	void	ShowItemImage(void);
	void	ReqThreshold(void);
};

#endif // PROPERTYCOUNTERFORM_H