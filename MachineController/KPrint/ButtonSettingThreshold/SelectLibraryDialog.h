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

#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XPanelShowResultImage.h"
#include "XEachThresholdCommon.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectLibraryDialog;
}
class ButtonSettingThresholdForm;

class SelectLibraryDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

	ButtonSettingThresholdForm *Parent;
	AlgorithmLibraryListContainer	List;
public:
    explicit SelectLibraryDialog(LayersBase *base, ButtonSettingThresholdForm *p, QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	void	Initial(AlgorithmLibraryListContainer &src);

	AlgorithmLibraryList	*Selected;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonCancel_clicked();
    void on_toolButtonSelect_clicked();

private:
    Ui::SelectLibraryDialog *ui;
};

#endif // SELECTLIBRARYDIALOG_H