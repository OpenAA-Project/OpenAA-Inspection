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

#ifndef PIECELISTFORM_H
#define PIECELISTFORM_H

#include "XGUIFormBase.h"
#include "XPieceReviewSide.h"
#include "NListComp.h"
#include "XPieceListReviewSidePacket.h"

namespace Ui {
    class PieceListForm;
}

class PieceListForm : public GUIFormBase
{
    Q_OBJECT

	ItemListReviewSideContainer	ListData;
public:
    explicit PieceListForm(LayersBase *Base,QWidget *parent = 0);
    ~PieceListForm();

	virtual	void	BuildForShow(void)	override;
private:
    Ui::PieceListForm *ui;

	PieceReviewSideBase	*GetResultImportanceBase(void);
protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;
};

//---------------------------------------------------------------


#endif // PIECELISTFORM_H