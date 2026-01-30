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

#ifndef SHOWPIECERESULTLISTFORM_H
#define SHOWPIECERESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XShowPieceResultListPacket.h"

namespace Ui {
    class ShowPieceResultListForm;
}

class ShowPieceResultListForm : public GUIFormBase
{
    Q_OBJECT

	ResultPieceListContainer	ResData;
	ResultPieceList				**ResPointer;
	int							ResPointerCount;
public:
    explicit ShowPieceResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowPieceResultListForm();

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::ShowPieceResultListForm *ui;
protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;
};

#endif // SHOWPIECERESULTLISTFORM_H