/*
 * Copyright (C) 2017
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

#include "CreateMatrixCellListResource.h"
#include "FormMatrixPieceColor.h"
#include <QColorDialog>

FormMatrixPieceColor::FormMatrixPieceColor(LayersBase *base, MatrixCellListForm *form,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	MainForm=form;
	for(NGPieceList *pn=MainForm->NGPieces.GetFirst();pn!=NULL;pn=pn->GetNext()){
		ui.listWidget->addItem(pn->NGPieceName);
	}
	InstallOperationLog(this);
}

FormMatrixPieceColor::~FormMatrixPieceColor()
{

}


void FormMatrixPieceColor::on_listWidget_clicked(const QModelIndex &)
{
	int	R=ui.listWidget->currentRow();
	if(R<0){
		return;
	}
	NGPieceList *pn=MainForm->NGPieces.GetItem(R);
	
	QPalette P=ui.pushButtonColor->palette();
	P.setColor(QPalette::Button,pn->FrameColor);
	ui.pushButtonColor->setPalette(P);
}

void FormMatrixPieceColor::on_pushButtonColor_clicked()
{
	int	R=ui.listWidget->currentRow();
	if(R<0){
		return;
	}
	NGPieceList *pn=MainForm->NGPieces.GetItem(R);
	QColor	Col=QColorDialog::getColor(pn->FrameColor);
	if(Col.isValid()==true){
		pn->FrameColor=Col;

		QPalette P=ui.pushButtonColor->palette();
		P.setColor(QPalette::Button,pn->FrameColor);
		ui.pushButtonColor->setPalette(P);
	}
}

void FormMatrixPieceColor::on_pushButtonOK_clicked()
{
	done(0);
}