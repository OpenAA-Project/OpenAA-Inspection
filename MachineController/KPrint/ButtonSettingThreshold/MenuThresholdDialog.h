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

#ifndef MENUTHRESHOLDDIALOG_H
#define MENUTHRESHOLDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XEachThresholdCommon.h"

namespace Ui {
class MenuThresholdDialog;
}
class ButtonSettingThresholdForm;
class MenuThresholdDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	QWidget	*ChildWindow;
	int		Phase;
	int		Page;
	int		GlobalX,GlobalY;
	IntList ItemID;
	bool	FreePosition;
public:
    explicit MenuThresholdDialog(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent = 0);
    ~MenuThresholdDialog();

	void	SetActiveArea(EachThresholdCommon::__AreaType areatype);
    void	SetActivePosition(int Phase ,int Page ,int GlobalX,int GlobalY,IntList &ItemID);
private slots:
    void on_PushButtonClosed_clicked();
    void on_PushButtonSettingEasy_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_PushButtonBlade_clicked();
    void on_PushButtonCADLine_clicked();

	void	SlotMonoFaint();
	void	SlotMonoRed();
	void	SlotMonoOozing();
	void	SlotMonoMultiSpot();

	void	SlotGradVariable();
	void	SlotGradRed();
	void	SlotGradOozing();
	void	SlotGradMultiSpot();
	
	void	SlotCharVariable();
	void	SlotCharRed();
	void	SlotCharOozing();
	void	SlotCharMultiSpot();

	void	SlotMujiFaint();
	void	SlotMujiRed();
	void	SlotMujiMultispot();

    void on_PushButtonWhole_clicked();

private:
    Ui::MenuThresholdDialog *ui;
};

#endif // MENUTHRESHOLDDIALOG_H