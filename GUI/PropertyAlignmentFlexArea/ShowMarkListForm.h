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

#ifndef SHOWMARKLISTFORM_H
#define SHOWMARKLISTFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlignmentFlexArea.h"

namespace Ui {
class ShowMarkListForm;
}

class ShowMarkListForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	AlignmentFlexAreaItemListPack	*PageDim;
public:
    explicit ShowMarkListForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowMarkListForm();

	void Initial(int AreaID ,int LibID);

protected:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonClose_clicked();

private:
    Ui::ShowMarkListForm *ui;
};

#endif // SHOWMARKLISTFORM_H