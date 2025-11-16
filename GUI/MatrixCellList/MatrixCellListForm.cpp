#include "CreateMatrixCellListResource.h"
#include "MatrixCellListForm.h"
#include "CreateMatrixCellList.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "XNaming.h"
#include "XCrossObj.h"
#include <QImage>
#include "GeneralDisplayWholeImage.h"
#include "XGeneralStocker.h"
#include "swap.h"

MatrixCell::~MatrixCell(void)
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=NULL;
}

void	MatrixCell::Draw(QPainter &pnt,int movx, int movy ,double ZoomRate,DrawAttr Attr,const QColor &FrameDefaultColor)
{
	int	kx1=(x1+movx)*ZoomRate;
	int	ky1=(y1+movy)*ZoomRate;
	int	kx2=(x2+movx)*ZoomRate;
	int	ky2=(y2+movy)*ZoomRate;

	if(Attr==_Normal){
		pnt.setPen(FrameDefaultColor);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
	else if(Attr==_Active){
		pnt.setPen(Qt::cyan);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
	else if(Attr==_NGArea){
		pnt.setPen(Qt::red);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
}
void	MatrixCell::WholeDraw(QPainter &pnt,int movx, int movy ,double ZoomRate,DrawAttr Attr,const QColor &FrameDefaultColor)
{
	int	kx1=(x1+movx)*ZoomRate;
	int	ky1=(y1+movy)*ZoomRate;
	int	kx2=(x2+movx)*ZoomRate;
	int	ky2=(y2+movy)*ZoomRate;

	if(Attr==_Normal){
		pnt.setPen(FrameDefaultColor);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
	if(Attr==_Active){
		int	W=kx2-kx1;
		int	H=ky2-ky1;
		if(Img==NULL || Img->width()!=W || Img->height()!=H){
			if(Img!=NULL){
				delete	Img;
			}
			Img=new QImage	(W,H,QImage::Format_ARGB32);
			QColor	Col(128,0,0,160);
			Img->fill(Col.value());
		}
		pnt.drawImage(kx1,ky1,*Img);
		pnt.setPen(Qt::red);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
}

bool	MatrixCell::Save(QIODevice *f)
{
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,Namings)==false)
		return false;
	return true;
}
bool	MatrixCell::Load(QIODevice *f)
{
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,Namings)==false)
		return false;
	return true;
}

bool	PieceColorInfo::Save(QIODevice *f)
{
	if(::Save(f,NGPieceName)==false)
		return false;
	if(::Save(f,FrameColor)==false)
		return false;
	return true;
}

bool	PieceColorInfo::Load(QIODevice *f)
{
	if(::Load(f,NGPieceName)==false)
		return false;
	if(::Load(f,FrameColor)==false)
		return false;
	return true;
}

//---------------------------------------------

MatrixCellListForm::MatrixCellListForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),ButtonFrameColor(false)
{
	ui.setupUi(this);
	CellSizeX=500;
	CellSizeY=500;	
	GetLayersBase()->GetArea(StartX,StartY,EndX,EndY);
	ui.tableWidget->setColumnWidth ( 0, 40);
	ui.tableWidget->setColumnWidth ( 1, 40);
	ui.tableWidget->setColumnWidth ( 2, 50);
	ui.tableWidget->setColumnWidth ( 3, 50);

	MatrixCellDim=NULL;
	MatrixCellDimXNumb=0;
	MatrixCellDimYNumb=0;

	SetKeyGrab(true);
	FrameDefaultColor=Qt::green;
	ButtonFrameColor.setParent(ui.frameColor);
	ButtonFrameColor.move(0,0);
	ButtonFrameColor.resize(ui.frameColor->width()-2,ui.frameColor->height()-2);
	ButtonFrameColor.setColor(FrameDefaultColor);
	ButtonFrameColor.setCheckable(true);
	ButtonFrameColor.setChecked(true);
	connect(&ButtonFrameColor,SIGNAL(clicked()),this,SLOT(on_toolButtonPiece_clicked()));
	LogPath=/**/"D:";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

MatrixCellListForm::~MatrixCellListForm()
{
	if(MatrixCellDim!=NULL){
		for(int y=0;y<MatrixCellDimYNumb;y++){
			delete	[]MatrixCellDim[y];
		}
		MatrixCellDim=NULL;
	}
}

void	MatrixCellListForm::ResizeAction()
{
	ui.tableWidget->move(0,0);
	ui.tableWidget->resize(width()-2,height()-2-ui.frameETC->height());
}

void	MatrixCellListForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSaveMatrixCellFile	*CmdSaveMatrixCellFileVar=dynamic_cast<CmdSaveMatrixCellFile *>(packet);
	if(CmdSaveMatrixCellFileVar!=NULL){
		SaveMatrixCell(CmdSaveMatrixCellFileVar->FL);
		int32	N=NGPieces.GetNumber();
		if(::Save(CmdSaveMatrixCellFileVar->FL,N)==false){
			return;
		}
		for(NGPieceList *p=NGPieces.GetFirst();p!=NULL;p=p->GetNext()){
			PieceColorInfo	W;
			W.FrameColor=p->FrameColor;
			W.NGPieceName=p->NGPieceName;
			W.Save(CmdSaveMatrixCellFileVar->FL);
		}
		return;
	}
	CmdLoadMatrixCellFile	*CmdLoadMatrixCellFileVar=dynamic_cast<CmdLoadMatrixCellFile *>(packet);
	if(CmdLoadMatrixCellFileVar!=NULL){
		LoadMatrixCell(CmdLoadMatrixCellFileVar->FL);
		PieceColorInfoForLoad.RemoveAll();
		int32	N;
		if(::Load(CmdLoadMatrixCellFileVar->FL,N)==false){
			return;
		}
		for(int i=0;i<N;i++){
			PieceColorInfo	*w=new PieceColorInfo();
			if(w->Load(CmdLoadMatrixCellFileVar->FL)==false){
				return;
			}
			PieceColorInfoForLoad.AppendList(w);
		}

		return;
	}
	CmdCreateMatrixCell	*CmdCreateMatrixCellVar=dynamic_cast<CmdCreateMatrixCell *>(packet);
	if(CmdCreateMatrixCellVar!=NULL){
		CreateCells(CellType);
	}
}

void MatrixCellListForm::on_pushButtonSet_clicked()
{
	CreateMatrixCellList	Q(GetLayersBase(),this);
	Q.ShowItem(this);
	Q.exec();

}

bool MatrixCellFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		MatrixCellListForm	*Form=dynamic_cast<MatrixCellListForm *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(pnt,DImage->GetMovx(),DImage->GetMovy(),DImage->GetZoomRate());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

bool WholeImageFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	GeneralDisplayWholeImage	*DImage=dynamic_cast<GeneralDisplayWholeImage *>(TargetObj);
	if(DImage!=NULL){
		MatrixCellListForm	*Form=dynamic_cast<MatrixCellListForm *>(Obj);
		if(Form!=NULL){
			CmdGetZoomRate	CmdGetZoomRateData(TargetObj->GetLayersBase());
			DImage->TransmitDirectly(&CmdGetZoomRateData);
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->WholeDraw(pnt,0,0,CmdGetZoomRateData.ZoomRate);
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

bool MatrixCellFunctionLClicked(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY)
{
	DisplayImageWithAlgorithm	*a=dynamic_cast<DisplayImageWithAlgorithm	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	MatrixCellListForm	*Form=dynamic_cast<MatrixCellListForm *>(Obj);
	if(Form!=NULL){
		Form->ClickImagePanel(GlobalPosX,GlobalPosY);
		return false;
	}
	return true;
}

void	MatrixCellListForm::ClickImagePanel(int GlobalPosX,int GlobalPosY)
{
	int	L=0;
	for(MatrixCell *p=MatrixCellData.GetFirst();p!=NULL;p=p->GetNext(),L++){
		if(p->x1<=GlobalPosX && GlobalPosX<=p->x2
		&& p->y1<=GlobalPosY && GlobalPosY<=p->y2){
			ui.tableWidget->selectRow(L);
			break;
		}
	}
}

void	MatrixCellListForm::Draw(QPainter &pnt,int movx ,int movy ,double ZoomRate)
{
	int	R=ui.tableWidget->currentRow();
	if(ButtonFrameColor.isChecked()==true){
		int	row=0;
		FrameDefaultColor=ButtonFrameColor.color();
		for(MatrixCell *c=MatrixCellData.GetFirst();c!=NULL;c=c->GetNext(),row++){
			if(row!=R){
				c->Draw(pnt,movx,movy,ZoomRate,MatrixCell::_Normal,FrameDefaultColor);
			}
		}
		row=0;
		for(MatrixCell *c=MatrixCellData.GetFirst();c!=NULL;c=c->GetNext(),row++){
			if(row==R){
				c->Draw(pnt,movx,movy,ZoomRate,c->Attr,Qt::white);
			}
		}
	}
	if(ui.toolButtonPiece->isChecked()==true){
		for(NGPieceList *p=NGPieces.GetFirst();p!=NULL;p=p->GetNext()){
			p->Draw(pnt,movx,movy,ZoomRate);
		}
	}
}

NGPieceList::NGPieceList(void)
{	
	NG=false;	
	FrameColor=Qt::green;	
	for(int i=0;i<sizeof(Img)/sizeof(Img[0]);i++){
		Img[i]=NULL;
	}
}
NGPieceList::~NGPieceList(void)
{
	for(int i=0;i<sizeof(Img)/sizeof(Img[0]);i++){
		if(Img[i]!=NULL){
			delete	Img[i];
			Img[i]=NULL;
		}
	}
}
QImage	*NGPieceList::GetImg(int W, int H)
{
	for(int i=0;i<sizeof(Img)/sizeof(Img[0]);i++){
		if(Img[i]!=NULL){
			if(Img[i]->width()==W && Img[i]->height()==H){
				return Img[i];
			}
		}
	}
	for(int i=0;i<sizeof(Img)/sizeof(Img[0]);i++){
		if(Img[i]==NULL){
			Img[i]=new QImage(W,H,QImage::Format_ARGB32);
			return Img[i];
		}
	}
	for(int i=0;i<sizeof(Img)/sizeof(Img[0]);i++){
		if(Img[i]!=NULL){
			delete	Img[i];
			Img[i]=NULL;
		}
	}
	return GetImg(W, H);
}
void	NGPieceList::Draw(QPainter &pnt,int movx, int movy ,double ZoomRate)
{
	int	kx1=(x1+movx)*ZoomRate;
	int	ky1=(y1+movy)*ZoomRate;
	int	kx2=(x2+movx)*ZoomRate;
	int	ky2=(y2+movy)*ZoomRate;

	if(NG==false){
		pnt.setPen(FrameColor);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
	if(NG==true){
		int	W=kx2-kx1;
		int	H=ky2-ky1;

		QImage	*img=GetImg(W,H);
		QColor	c=img->pixel(0,0);
		QColor	Col(FrameColor);
		Col.setAlpha(100);
		if(c.red()!=Col.red() || c.green()!=Col.green() || c.blue()!=Col.blue()){
			img->fill((uint)Col.rgba());
		}
		pnt.drawImage(kx1,ky1,*img);
		pnt.setPen(Qt::magenta);
		pnt.drawLine(kx1,ky1,kx2,ky1);
		pnt.drawLine(kx2,ky1,kx2,ky2);
		pnt.drawLine(kx2,ky2,kx1,ky2);
		pnt.drawLine(kx1,ky2,kx1,ky1);
	}
	pnt.drawText(kx1,ky1,kx2-kx1,ky2-ky1,Qt::AlignCenter,NGPieceName);
}

void	MatrixCellListForm::WholeDraw(QPainter &pnt,int movx ,int movy ,double ZoomRate)
{
	int	R=ui.tableWidget->currentRow();
	if(ButtonFrameColor.isChecked()==true){
		int	row=0;
		for(MatrixCell *c=MatrixCellData.GetFirst();c!=NULL;c=c->GetNext(),row++){
			if(row!=R){
				/*
				bool	NGFlag=false;
				for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->NGPieceName==c->Naming && a->NG==true){
						NGFlag=true;
						break;
					}
				}
				*/
				c->WholeDraw(pnt,movx,movy,ZoomRate,MatrixCell::_Normal,FrameDefaultColor);
			}
		}
		row=0;
		for(MatrixCell *c=MatrixCellData.GetFirst();c!=NULL;c=c->GetNext(),row++){
			if(row==R){
				c->WholeDraw(pnt,movx,movy,ZoomRate,MatrixCell::_Active,FrameDefaultColor);
			}
		}
	}

	if(ui.toolButtonPiece->isChecked()==true){
		for(NGPieceList *p=NGPieces.GetFirst();p!=NULL;p=p->GetNext()){
			p->Draw(pnt,movx,movy,ZoomRate);
		}
	}
}

void	MatrixCellListForm::BuildForShow(void)
{
	GUIFormBase	*m=GetLayersBase()->FindByName(DisplayImageRoot,DisplayImageName,DisplayImageInst);
	if(m!=NULL){
		DisplayImage	*DImg=dynamic_cast<DisplayImage *>(m);
		if(DImg!=NULL){
			DImg->SetHookInPaintLast(this,MatrixCellFunctionLater);
			DImg->SetHookInMouseLClick(this,MatrixCellFunctionLClicked);
		}
	}
	if(WholeImageInstName.isEmpty()==false){
		GUIFormBase	*W=GetLayersBase()->FindByName(WholeImageInstName);
		if(W!=NULL){
			GeneralDisplayWholeImage	*DImg=dynamic_cast<GeneralDisplayWholeImage *>(W);
			if(DImg!=NULL){
				DImg->SetHookInPaintLast(this,WholeImageFunctionLater,false);
			}
		}
	}
	for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
		a->NG=false;
	}
	for(MatrixCell *b=MatrixCellData.GetFirst();b!=NULL;b=b->GetNext()){
		b->Attr=MatrixCell::_Normal;
	}
}

void	MatrixCellListForm::CreateCells(int _CellType)
{
	CellType=_CellType;
	MatrixCellData.RemoveAll();
	AlgorithmBase	*Algo=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
	if(Algo==NULL)
		return;

	NamingPointerStock	AreaNames;
	for(int page=0;page<GetPageNumb();page++){
		ReqBuildItemPointerNamingPage	RCmd(GetLayersBase());
		RCmd.Page=page;
		NamingPointerStock	NamingPointerStocker;
		RCmd.Stocker=&NamingPointerStocker;
		Algo->TransmitDirectly(&RCmd);
		if(RCmd.Stocker!=NULL){
			for(NamingPointer *r=RCmd.Stocker->GetFirst();r!=NULL;r=r->GetNext()){
				NamingPointer *p;
				for(p=AreaNames.GetFirst();p!=NULL;p=p->GetNext()){
					if(p->AreaName==r->AreaName){
						break;
					}
				}
				if(p!=NULL){
					p->GlobalX1=min(r->GlobalX1,p->GlobalX1);
					p->GlobalY1=min(r->GlobalY1,p->GlobalY1);
					p->GlobalX2=max(r->GlobalX2,p->GlobalX2);
					p->GlobalY2=max(r->GlobalY2,p->GlobalY2);
				}
				else{
					p=new NamingPointer();
					p->GlobalX1=r->GlobalX1;
					p->GlobalY1=r->GlobalY1;
					p->GlobalX2=r->GlobalX2;
					p->GlobalY2=r->GlobalY2;
					p->AreaName=r->AreaName;
					AreaNames.AppendList(p);
				}
			}
		}
	}

NextP:;
	for(NamingPointer *p=AreaNames.GetFirst();p!=NULL;p=p->GetNext()){
		NamingPointer *q=p->GetNext();
		if(q==NULL){
			break;
		}
		bool	POk;
		bool	QOk;
		int	Pn=p->AreaName.toInt(&POk);
		int	Qn=q->AreaName.toInt(&QOk);
		if(POk==true && QOk==true){
			if(Pn>Qn){
				AreaNames.Swap(p,q);
				goto	NextP;
			}
		}
		else{
			if(p->AreaName>q->AreaName){
				AreaNames.Swap(p,q);
				goto	NextP;
			}
		}
	}

	int	Lx=EndX-StartX;
	int	Ly=EndY-StartY;
	int	XNumb=(Lx+CellSizeX-1)/CellSizeX;
	int	YNumb=(Ly+CellSizeY-1)/CellSizeY;
	int	Nx=(XNumb*CellSizeX-Lx)/2;
	int	Ny=(YNumb*CellSizeY-Ly)/2;
	int	AreaNumber=0;
	for(int ty=0;ty<YNumb;ty++){
		if(CellType==0){
			for(int tx=0;tx<XNumb;tx++){
				int	x1=StartX+CellSizeX*tx-Nx;
				int	y1=StartY+CellSizeY*ty-Ny;
				int	x2=x1+CellSizeX;
				int	y2=y1+CellSizeY;
				/*
				FlexArea	M;
				M.SetRectangle(x1,y1,x2,y2);
				for(NamingPointer *p=AreaNames.GetFirst();p!=NULL;p=p->GetNext()){
					FlexArea	S;
					S.SetRectangle(p->GlobalX1,p->GlobalY1,p->GlobalX2,p->GlobalY2);
					M-=S;
				}
				if(M.GetPatternByte()<CellSizeX){
					continue;
				}
				*/
				MatrixCell	*k=new MatrixCell();
				k->x1=x1;
				k->y1=y1;
				k->x2=x2;
				k->y2=y2;
				k->IndexX=tx;
				k->IndexY=ty;
				k->AreaName=QString::number(AreaNumber);
				AreaNumber++;
				MatrixCellData.AppendList(k);
			}
		}
		else if(CellType==1){
			if((ty&1)!=0){
				for(int tx=XNumb-1;tx>=0;tx--){
					int	x1=StartX+CellSizeX*tx-Nx;
					int	y1=StartY+CellSizeY*ty-Ny;
					int	x2=x1+CellSizeX;
					int	y2=y1+CellSizeY;
					MatrixCell	*k=new MatrixCell();
					k->x1=x1;
					k->y1=y1;
					k->x2=x2;
					k->y2=y2;
					k->IndexX=tx;
					k->IndexY=ty;
					k->AreaName=QString::number(AreaNumber);
					AreaNumber++;
					MatrixCellData.AppendList(k);
				}
			}
			else{
				for(int tx=0;tx<XNumb;tx++){
					int	x1=StartX+CellSizeX*tx-Nx;
					int	y1=StartY+CellSizeY*ty-Ny;
					int	x2=x1+CellSizeX;
					int	y2=y1+CellSizeY;
					MatrixCell	*k=new MatrixCell();
					k->x1=x1;
					k->y1=y1;
					k->x2=x2;
					k->y2=y2;
					k->IndexX=tx;
					k->IndexY=ty;
					k->AreaName=QString::number(AreaNumber);
					AreaNumber++;
					MatrixCellData.AppendList(k);
				}
			}
		}
	}
	NGPieces.RemoveAll();
	for(NamingPointer *p=AreaNames.GetFirst();p!=NULL;p=p->GetNext()){
		/*
		int	Lx=p->GlobalX2-p->GlobalX1;
		int	Ly=p->GlobalY2-p->GlobalY1;
		int	XNumb=(Lx+CellSizeX-1)/CellSizeX;
		int	YNumb=(Ly+CellSizeY-1)/CellSizeY;
		int	Nx=(XNumb*CellSizeX-Lx)/2;
		int	Ny=(YNumb*CellSizeY-Ly)/2;
		for(int ty=0;ty<YNumb;ty++){
			for(int tx=0;tx<XNumb;tx++){
				MatrixCell	*k=new MatrixCell();
				k->x1=p->GlobalX1+CellSizeX*tx-Nx;
				k->y1=p->GlobalY1+CellSizeY*ty-Ny;
				k->x2=k->x1+CellSizeX;
				k->y2=k->y1+CellSizeY;
				k->Naming=p->AreaName;
				MatrixCellData.AppendList(k);
			}
		}
		*/
		NGPieceList	*h=new NGPieceList();
		h->NGPieceName=p->AreaName;
		h->x1=p->GlobalX1;
		h->y1=p->GlobalY1;
		h->x2=p->GlobalX2;
		h->y2=p->GlobalY2;
		NGPieces.AppendList(h);
	}
	for(MatrixCell *m=MatrixCellData.GetFirst();m!=NULL;m=m->GetNext()){
		for(NGPieceList *d=NGPieces.GetFirst();d!=NULL;d=d->GetNext()){
			if(CheckOverlapRectRect(m->x1,m->y1,m->x2,m->y2 ,d->x1,d->y1,d->x2,d->y2)==true){
				m->Namings.append(d->NGPieceName);
			}
		}
	}

	//MakeIndex(CellType);
	for(PieceColorInfo *p=PieceColorInfoForLoad.GetFirst();p!=NULL;p=p->GetNext()){
		for(NGPieceList *d=NGPieces.GetFirst();d!=NULL;d=d->GetNext()){
			if(d->NGPieceName==p->NGPieceName){
				d->FrameColor=p->FrameColor;
				break;
			}
		}
	}
	ShowList();
}

int	MatrixCellSortForwardFunc(const void *a ,const void *b)
{
	MatrixCell	**am=(MatrixCell **)a;
	MatrixCell	**bm=(MatrixCell **)b;
	if((*am)->x1>(*bm)->x1)
		return 1;
	if((*am)->x1<(*bm)->x1)
		return -1;
	return 0;
}

void MatrixCellListForm::MakeIndex(int _CellType)
{
	for(MatrixCell *p=MatrixCellData.GetFirst();p!=NULL;p=p->GetNext()){
		p->IndexX=-1;
		p->IndexY=-1;
	}

	int	ICountX=0;
	int	ICountY=0;
	for(MatrixCell *p=MatrixCellData.GetFirst();p!=NULL;p=p->GetNext()){
		if(p->IndexX==-1 && p->IndexY==-1){
			int	kx,ky;
			p->GetCenter(kx,ky);
			p->IndexY=ICountY;
			int	LCountX=1;
			for(MatrixCell *q=p->GetNext();q!=NULL;q=q->GetNext()){
				if(q->IndexX==-1 && q->IndexY==-1){
					if(q->y1<=ky && ky<=q->y2){
						q->IndexY=ICountY;
						LCountX++;
					}
				}
			}
			ICountY++;
			if(ICountX<LCountX){
				ICountX=LCountX;
			}
		}
	}
	if(MatrixCellDim!=NULL){
		for(int y=0;y<MatrixCellDimYNumb;y++){
			delete	[]MatrixCellDim[y];
		}
		MatrixCellDim=NULL;
	}
	MatrixCellDimYNumb=ICountY;
	MatrixCellDimXNumb=ICountX;
	MatrixCellDim=new MatrixCell**[MatrixCellDimYNumb];
	for(int y=0;y<MatrixCellDimYNumb;y++){
		MatrixCellDim[y]=new MatrixCell*[MatrixCellDimXNumb];
		for(int x=0;x<MatrixCellDimXNumb;x++){
			MatrixCellDim[y][x]=NULL;
		}
	}

	for(int y=0;y<MatrixCellDimYNumb;y++){
		int	X=0;
		for(MatrixCell *p=MatrixCellData.GetFirst();p!=NULL;p=p->GetNext()){
			if(p->IndexY==y){
				MatrixCellDim[y][X]=p;
				X++;
			}
		}
		QSort(MatrixCellDim[y],X,sizeof(MatrixCell *),MatrixCellSortForwardFunc);
		for(int x=0;x<X;x++){
			MatrixCellDim[y][x]->IndexX=x;
		}
	}
	int	AreaNumber=0;
	for(int y=0;y<MatrixCellDimYNumb;y++){
		if(_CellType==0){
			for(int x=0;x<MatrixCellDimXNumb;x++){
				if(MatrixCellDim[y][x]!=NULL){
					MatrixCellDim[y][x]->AreaName=QString::number(AreaNumber);
					AreaNumber++;
				}
			}
		}
		else if(_CellType==1){
			if((y&1)==0){
				for(int x=0;x<MatrixCellDimXNumb;x++){
					if(MatrixCellDim[y][x]!=NULL){
						MatrixCellDim[y][x]->AreaName=QString::number(AreaNumber);
						AreaNumber++;
					}
				}
			}
			else{
				for(int x=0;x<MatrixCellDimXNumb/2;x++){
					MatrixCellData.Swap(MatrixCellDim[y][x],MatrixCellDim[y][MatrixCellDimXNumb-x-1]);
				}
				for(int x=0;x<MatrixCellDimXNumb;x++){
					if(MatrixCellDim[y][x]!=NULL){
						MatrixCellDim[y][x]->AreaName=QString::number(AreaNumber);
						AreaNumber++;
					}
				}
			}
		}
	}
}

void MatrixCellListForm::on_tableWidget_clicked(const QModelIndex &)
{
	on_tableWidget_itemSelectionChanged();
}

void MatrixCellListForm::ShowList(void)
{
	ui.tableWidget->setRowCount(MatrixCellData.GetNumber());
	int	row=0;
	for(MatrixCell *p=MatrixCellData.GetFirst();p!=NULL;p=p->GetNext(),row++){
		SetDataToTable(ui.tableWidget,0,row ,QString::number(p->IndexX));
		SetDataToTable(ui.tableWidget,1,row ,QString::number(p->IndexY));
		SetDataToTable(ui.tableWidget,2,row ,p->AreaName);
		QString	PStr;
		for(int i=0;i<p->Namings.count();i++){
			PStr=PStr+p->Namings[i];
			if((i+1)<p->Namings.count()){
				PStr+=QString(/**/" ,");
			}
		}
		SetDataToTable(ui.tableWidget,3,row ,PStr);
	}
	ui.lineEditTotalCount->setText(QString::number(row));
}

void MatrixCellListForm::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F1){
		int	R=ui.tableWidget->currentRow();
		if(R<0){
			return;
		}
		MatrixCell	*C=MatrixCellData.GetItem(R);
		if(C->Attr==MatrixCell::_NGArea){
			C->Attr=MatrixCell::_Normal;
		}
		else{
			C->Attr=MatrixCell::_NGArea;
		}

		if(C->Attr==MatrixCell::_NGArea){
			for(int i=0;i<C->Namings.count();i++){
				for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
					if(a->NGPieceName==C->Namings[i]){
						a->NG=true;
					}
				}
			}
		}
		else{
			for(int i=0;i<C->Namings.count();i++){
				bool	ShouldNG=false;
				for(MatrixCell *b=MatrixCellData.GetFirst();b!=NULL;b=b->GetNext()){
					if(b==C){
						continue;
					}
					for(int k=0;k<b->Namings.count();k++){
						if(C->Namings[i]==b->Namings[k]){
							if(b->Attr==MatrixCell::_NGArea){
								ShouldNG=true;
							}
						}
					}
				}
				if(ShouldNG==false){
					for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->NGPieceName==C->Namings[i]){
							a->NG=false;
						}
					}
				}
			}
		}

		if(WholeImageInstName.isEmpty()==false){
			GUIFormBase	*W=GetLayersBase()->FindByName(WholeImageInstName);
			if(W!=NULL){
				W->repaint();
			}
		}
		if(C->Attr==MatrixCell::_NGArea){
			for(int i=0;i<ui.tableWidget->columnCount();i++){
				QTableWidgetItem	*w=ui.tableWidget->item(R,i);
				if(w!=NULL){
					w->setBackground(QBrush(Qt::red));
				}
			}
		}
		else{
			for(int i=0;i<ui.tableWidget->columnCount();i++){
				QTableWidgetItem	*w=ui.tableWidget->item(R,i);
				if(w!=NULL){
					w->setBackground(QBrush(Qt::white));
				}
			}
		}
		if((R+1)<ui.tableWidget->rowCount()){
			ui.tableWidget->setCurrentCell(R+1,0);
		}
		WriteLog();
		event->accept();
	}
	else{
		GUIFormBase::keyPressEvent ( event );
	}
}


void MatrixCellListForm::on_tableWidget_itemSelectionChanged()
{
	int	R=ui.tableWidget->currentRow();
	if(R<0){
		return;
	}
	bool	ShouldSkip=true;
	MatrixCell	*C=MatrixCellData.GetItem(R);
	if(C->Attr!=MatrixCell::_NGArea){
		for(int i=0;i<C->Namings.count();i++){
			for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->NGPieceName==C->Namings[i]){
					if(a->NG==false){
						ShouldSkip=false;
						break;
					}
				}
			}
		}
		if(C->Namings.count()==0){
			ShouldSkip=false;
		}
		if(ShouldSkip==true){
			R++;
			while(R<ui.tableWidget->rowCount()){
				C=MatrixCellData.GetItem(R);
				if(C==NULL){
					break;
				}
				ShouldSkip=true;
				for(int i=0;i<C->Namings.count();i++){
					for(NGPieceList *a=NGPieces.GetFirst();a!=NULL;a=a->GetNext()){
						if(a->NGPieceName==C->Namings[i]){
							if(a->NG==false){
								ShouldSkip=false;
								break;
							}
						}
					}
				}
				if(C->Namings.count()==0 || ShouldSkip==false){
					ui.tableWidget->setCurrentCell(R,0);
					return;
				}
				R++;
			}
		}
	}
	C=MatrixCellData.GetItem(R);
	if(C!=NULL){
		GUIFormBase	*m=GetLayersBase()->FindByName(DisplayImageRoot,DisplayImageName,DisplayImageInst);
		if(m!=NULL){
			DisplayImage	*DImg=dynamic_cast<DisplayImage *>(m);
			if(DImg!=NULL){
				DImg->ShowCenter((C->x1+C->x2)/2, (C->y1+C->y2)/2);
			}
		}

		if(WholeImageInstName.isEmpty()==false){
			GUIFormBase	*W=GetLayersBase()->FindByName(WholeImageInstName);
			if(W!=NULL){
				W->repaint();
			}
		}
	}
}
bool	MatrixCellListForm::SaveMatrixCell(QIODevice *f)
{
	if(::Save(f,CellSizeX)==false){
		return false;
	}
	if(::Save(f,CellSizeY)==false){
		return false;
	}	
	if(::Save(f,StartX)==false){
		return false;
	}
	if(::Save(f,StartY)==false){
		return false;
	}
	if(::Save(f,EndX)==false){
		return false;
	}
	if(::Save(f,EndY)==false){
		return false;
	}
	if(::Save(f,CellType)==false){
		return false;
	}
	return true;
}

bool	MatrixCellListForm::LoadMatrixCell(QIODevice *f)
{
	if(::Load(f,CellSizeX)==false){
		return false;
	}
	if(::Load(f,CellSizeY)==false){
		return false;
	}	
	if(::Load(f,StartX)==false){
		return false;
	}
	if(::Load(f,StartY)==false){
		return false;
	}
	if(::Load(f,EndX)==false){
		return false;
	}
	if(::Load(f,EndY)==false){
		return false;
	}
	if(::Load(f,CellType)==false){
		return false;
	}
	return true;
}


void MatrixCellListForm::on_toolButtonPiece_clicked()
{
	BroadcastShowInEdit();	
}

void MatrixCellListForm::WriteLog(void)
{
	struct	MatrixStruct	*M=new struct	MatrixStruct[MatrixCellData.GetNumber()];
	struct	PieceStruct		*P=new struct	PieceStruct[NGPieces.GetNumber()];

	int	n=0;
	for(MatrixCell *m=MatrixCellData.GetFirst();m!=NULL;m=m->GetNext()){
		M[n].x1=m->x1;
		M[n].y1=m->y1;
		M[n].x2=m->x2;
		M[n].y2=m->y2;
		::QString2Char(m->AreaName,M[n].AreaName,sizeof(M[0].AreaName));
		memset(M[n].Namings,0,sizeof(M[0].Namings));
		for(int i=0;i<m->Namings.count();i++){
			::QString2Char(m->Namings[i],M[n].Namings[i],sizeof(M[n].Namings[0]));
		}
		M[n].Attr=(int)m->Attr;
		n++;
	}
	QVariantList	ArgV;

	ArgV<<QVariant(LogPath);
	ArgV<<QVariant(n);
	QByteArray	Ar((char *)M,n*sizeof(M[0]));
	ArgV<<QVariant(Ar);

	n=0;
	for(NGPieceList *p=NGPieces.GetFirst();p!=NULL;p=p->GetNext()){
		P[n].x1=p->x1;
		P[n].y1=p->y1;
		P[n].x2=p->x2;
		P[n].y2=p->y2;
		::QString2Char(p->NGPieceName,P[n].NGPieceName,sizeof(P[0].NGPieceName));
		P[n].NG=p->NG;
		n++;
	}
	ArgV<<QVariant(n);
	QByteArray	Pr((char *)P,n*sizeof(P[0]));
	ArgV<<QVariant(Pr);
	
	QVariantList	RetV;
	GetLayersBase()->GetGeneralStocker()->GetData(/**/"MatrixCellSaveLog",RetV,ArgV);
}
