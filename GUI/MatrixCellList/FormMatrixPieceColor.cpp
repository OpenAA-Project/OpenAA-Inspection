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