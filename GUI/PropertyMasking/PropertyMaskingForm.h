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


#ifndef PROPERTYMASKINGFORM_H
#define PROPERTYMASKINGFORM_H

#include <QWidget>
#include "ui_PropertyMaskingForm.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "XPropertyMaskingPacket.h"
#include "mtToolButtonColored.h"

class	MaskingBase;
class	AlgorithmLibraryLevelContainer;

class PropertyMaskingForm : public GUIFormBase
{
    Q_OBJECT
	MaskingListForPacketPack	MaskInfo;
	mtToolButtonColored			ButtonEffective;
	mtToolButtonColored			ButtonEffectiveLimited;
	mtToolButtonColored			ButtonIneffective;
	mtToolButtonColored			ButtonIneffectiveLimited;
	mtToolButtonColored			ButtonCutLine;
	int							PickupColorWidth;
	int							PickupMinSize;
	int							PickupExpandedDot;
	int							PickupNoiseSize;

	bool							PouredEffective;
	AlgorithmLibraryListContainer	PouredLimitedLib;
	QColor						ColorEffective;
	QColor						ColorEffectiveLimited;
	QColor						ColorIneffective;
	QColor						ColorIneffectiveLimited;
	QColor						ColorCutLine;
	bool	OnChanging;
public:
    PropertyMaskingForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyMaskingForm();

	virtual	void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;

	void	CreateMask(FlexArea &Area);
	void	ExpandMask(int expix);
	void	ReplaceInclusiveMask(void);

private:
    Ui::PropertyMaskingFormClass ui;
	void	ShowAreaGrid(void);
	MaskingBase	*GetMaskingBase(void);
	void	ShowPourMessage(void);
	GUIFormBase	*GetImageControlToolsPointer(void);
	void	ReflectSelectList(void);

private slots:
	void on_toolButtonGenerateOnClick_clicked();
	void on_pushButtonLimited_clicked();
	void on_toolButton_clicked();
	void on_ButtonEffective_clicked();
	void on_ButtonEffectiveLimited_clicked();
	void on_ButtonIneffective_clicked();
	void on_ButtonIneffectiveLimited_clicked();
	void on_ButtonCutLine_clicked();

	void	colorChangedEffective();
	void	colorChangedEffectiveLimited();
	void	colorChangedIneffective();
	void	colorChangedIneffectiveLimited();
	void	colorChangedCutLine();
	void on_ButtonGenerateMaskFromSameColor_clicked();
	void on_tableWidgetMaskingList_doubleClicked(QModelIndex);
	void on_tableWidgetMaskingList_clicked(const QModelIndex &);
    void on_pushButtonEditLibrary_clicked();
    void on_toolButtonGenerateExclusive_clicked();
    void on_spinBoxExpandedDot_valueChanged(int arg1);
    void on_doubleSpinBoxExpandedDotMM_valueChanged(double arg1);
    void on_spinBoxMinSize_valueChanged(int arg1);
    void on_doubleSpinBoxMinSizeMM_valueChanged(double arg1);
    void on_pushButtonMakeBackGroundMaster_clicked();
    void on_pushButtonMakeBackGroundTarget_clicked();
    void on_pushButtonClearBackGround_clicked();
    void on_toolButtonShowBackGround_clicked();
    void on_pushButtonSelectByLimited_clicked();
    void on_ButtonGenerateMaskOnSelectedItemsEdge_clicked();
    void on_pushButtonSelectAll_clicked();
    void on_ButtonGenerateMaskPatternEdgeOnSelected_clicked();
};
#endif // PROPERTYMASKINGFORM_H