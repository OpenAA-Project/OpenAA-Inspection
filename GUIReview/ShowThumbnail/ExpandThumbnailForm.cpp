#include "ShowThumbnailResource.h"
#include "ExpandThumbnailForm.h"

#include "Thumbnail.h"
#include "../XGUIReviewCommon.h"
#include "ShowThumbnail.h"

#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

ExpandThumbnailDialog::ExpandThumbnailDialog(ShowThumbnail *_MainParent ,QWidget *parent, Qt::WindowFlags flags)
	:QDialog(parent, flags),myThumbnail(NULL),reqUpdate(false),drawNG(true)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setModal(false);
	setWindowFlags( windowFlags() | Qt::WindowStaysOnTopHint );
	MainParent=_MainParent;
	//bool	ret=(connect(ui.pushButtonSetKey,SIGNAL(clicked()),this,SLOT(on_pushButtonSetKey_clicked())))?true:false;


	KeyCode	=0;
	KeyType	=true;
}

void ExpandThumbnailDialog::mousePressEvent(QMouseEvent *event)
{
	if((event->buttons() & Qt::LeftButton)!=0){
		setVisible(false);
	}
}

void	ExpandThumbnailDialog::Initial(void)
{
	if(MainParent->isViewMaster()==false){
		if(ui.lbMasterPos!=NULL){
			delete	ui.lbMasterPos;
			ui.lbMasterPos=NULL;
		}
		if(ui.lbMaster!=NULL){
			delete	ui.lbMaster;
			ui.lbMaster=NULL;
		}
	}

}

void ExpandThumbnailDialog::setThumbnail(Thumbnail *thumbnail)
{
	if(myThumbnail==thumbnail)return;

	reqUpdate = true;

	if(myThumbnail!=NULL){
		delete myThumbnail;
	}
	//qDebug() << "ExpThumbnail updated";

	if(MainParent->isViewMaster()==false){
		if(ui.lbMasterPos!=NULL){
			delete	ui.lbMasterPos;
			ui.lbMasterPos=NULL;
		}
		if(ui.lbMaster!=NULL){
			delete	ui.lbMaster;
			ui.lbMaster=NULL;
		}
	}
	myThumbnail = thumbnail;
	if(thumbnail==NULL){
		ui.lbNG->setPixmap( QPixmap() );
		if(MainParent->isViewMaster()==true){
			ui.lbMaster->setPixmap( QPixmap() );
		}

		ui.lbTargetPos->setText( LangSolver.GetString(ExpandThumbnailForm_LS,LID_0)/*"NoData"*/ );
		if(MainParent->isViewMaster()==true){
			ui.lbMasterPos->setText( LangSolver.GetString(ExpandThumbnailForm_LS,LID_1)/*"NoData"*/ );
		}
		ui.lbNGCount->setText( LangSolver.GetString(ExpandThumbnailForm_LS,LID_2)/*"NoData"*/ );
		ui.lbFKeyType->setText( LangSolver.GetString(ExpandThumbnailForm_LS,LID_3)/*"NoData"*/ );
	}else{
		ui.lbTargetPos->setText( QString(/**/"(%1, %2)").arg(thumbnail->getNGNailItem().TargetPosX).arg(thumbnail->getNGNailItem().TargetPosY) );
		if(MainParent->isViewMaster()==true){
			ui.lbMasterPos->setText( QString(/**/"(%1, %2)").arg(thumbnail->getNGNailItem().MasterPosX).arg(thumbnail->getNGNailItem().MasterPosY) );
		}
		ui.lbNGCount->setText( QString::number( thumbnail->getNGNailItem().NGPointList.count() ) );
		KeyType=true;
		if(thumbnail->getNGNailItem().FKey == Review::NoFKey ){
			ui.lbFKeyType->setText( LangSolver.GetString(ExpandThumbnailForm_LS,LID_4)/*"No FKey"*/ );
			KeyCode=0;
		}else{
			ui.lbFKeyType->setText( QString(/**/"F%1").arg( Review::FKeyToInt( thumbnail->getNGNailItem().FKey ) + 1 ) );
			KeyCode=Review::FKeyToInt( thumbnail->getNGNailItem().FKey ) + 1;
		}
	}

	//update();
}

void ExpandThumbnailDialog::resizeEvent(QResizeEvent *event)
{
	QDialog::resizeEvent(event);

	//qDebug() << "Old:" << event->oldSize();
	//qDebug() << "New:" << event->size(); 

	//layout()->update();

	//updateImage();
}

void ExpandThumbnailDialog::keyPressEvent(QKeyEvent *event)
{
	//qDebug() << event->key();
	if(event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter){
		setVisible(false);
		return;
	}

	if(event->key()==Qt::Key_Control || event->key()==Qt::Key_Asterisk){
		drawNG = !drawNG;
		updateImage();
		return;
	}
}

void ExpandThumbnailDialog::updateImage()
{
	if(MainParent->isViewMaster()==false){
		if(ui.lbMasterPos!=NULL){
			delete	ui.lbMasterPos;
			ui.lbMasterPos=NULL;
		}
		if(ui.lbMaster!=NULL){
			delete	ui.lbMaster;
			ui.lbMaster=NULL;
		}
	}
	if(myThumbnail->getNGNailItem().image().isNull()==true){
		// NG??????????????
		QPixmap NGPix;
		NGPix = myThumbnail->getMasterPieceImage();//.scaled(ScaledSize.width(), ScaledSize.height(), Qt::KeepAspectRatio);

		double zoomRate = NGPix.width() / (double)myThumbnail->getMasterPieceImage().width();// ?g??
		QPoint target(myThumbnail->getNGNailItem().TargetPosX, myThumbnail->getNGNailItem().TargetPosY);
		QPoint master(myThumbnail->getNGNailItem().MasterPosX, myThumbnail->getNGNailItem().MasterPosY);
		//int ox = myThumbnail->getNGNailItem().TargetPosX;
		//int oy = myThumbnail->getNGNailItem().TargetPosY;
		//int sx = myThumbnail->getNGNailItem().MasterPosX - ox;
		//int sy = myThumbnail->getNGNailItem().MasterPosY - oy;

		QPoint shift = master - target;
		
		QPainter painter;
		QPen pen;
		painter.begin(&NGPix);

		pen.setColor( QColor(Qt::blue) );
		painter.setPen(pen);
		
		if(drawNG==true){
			ReviewNGPointList NGPoints = myThumbnail->getNGNailItem().NGPointList;
			for(int i=0; i<NGPoints.count(); i++){
				
				QPoint center = (QPoint(NGPoints[i].x - target.x(), NGPoints[i].y - target.y())) * zoomRate;

				int NGSingSize = myThumbnail->getNGSignSize();

				Review::DrawNGShapeToPainter(&painter, NGPoints[i].Tag.NGColor, NGPoints[i].Tag.NGShape, center, NGSingSize/2);

				//switch(NGPoints[i].Tag.NGShape){
				//case LibNGTypeItem::NGShapeType::NG_Circle:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2);
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_Cross:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawLine(center - QPoint(0, NGSingSize/2), center + QPoint(0, NGSingSize/2));
				//	painter.drawLine(center - QPoint(NGSingSize/2, 0), center + QPoint(NGSingSize/2, 0));
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_FilledCircle:
				//	painter.setBrush(Qt::BrushStyle::SolidPattern);
				//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2);
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_FilledRect:
				//	painter.setBrush(Qt::BrushStyle::SolidPattern);
				//	painter.drawRect(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize);
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_FilledStar:
				//	painter.setBrush(Qt::BrushStyle::SolidPattern);
				//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"??");
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_Rectangle:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawRect(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize);
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_Sharp:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"#");
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_Star:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawText(center.x()-NGSingSize/2, center.y()-NGSingSize/2, NGSingSize, NGSingSize, Qt::AlignCenter, /**/"??");
				//	break;
				//case LibNGTypeItem::NGShapeType::NG_X:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawLine(center - QPoint(NGSingSize/2, NGSingSize/2), center + QPoint(-NGSingSize/2, -NGSingSize/2));
				//	painter.drawLine(center - QPoint(-NGSingSize/2, NGSingSize/2), center + QPoint(NGSingSize/2, -NGSingSize/2));
				//	break;
				//default:
				//	painter.setBrush(Qt::BrushStyle::NoBrush);
				//	painter.drawEllipse(center, NGSingSize/2, NGSingSize/2); 
				//	break;
				//}

				//painter.drawEllipse(QPoint((myThumbnail->getNGNailItem().NGPointList[i].x - target.x() + shift.x()) * zoomRate,
				//	(myThumbnail->getNGNailItem().NGPointList[i].y - target.y() + shift.y()) * zoomRate),
				//	myThumbnail->getNGSignSize(), myThumbnail->getNGSignSize());
			}
		}

		painter.end();
		
		//// ??????????NG???ã€???t????
		//painter.begin(&pix);
		//painter.drawPixmap(fillWidth/2, fillHeight/2, NGPix);
		//painter.end();

		//ui.lbNG->setPixmap(pix);
		ui.lbNG->setPixmap(NGPix);
		ui.lbNG->setMinimumSize(NGPix.width(), NGPix.height());
		ui.lbNG->setMaximumSize(NGPix.width(), NGPix.height());
	}else{
		// NG??????????????
		QPixmap NGPix;
		NGPix = QPixmap::fromImage(myThumbnail->getNGNailItem().image()/*.scaled(ScaledSize.width(), ScaledSize.height(), Qt::KeepAspectRatio)*/);

		double zoomRate = NGPix.width() / (double)myThumbnail->getNGNailItem().image().width();// ?g??
		int ox = myThumbnail->getNGNailItem().TargetPosX;
		int oy = myThumbnail->getNGNailItem().TargetPosY;

		QPainter painter;
		painter.begin(&NGPix);

		QPen pen;
		pen.setColor( QColor(Qt::red) );
		painter.setPen(pen);
		
		if(drawNG==true){
			for(int i=0; i<myThumbnail->getNGNailItem().NGPointList.count(); i++){

				QPoint center = QPoint((myThumbnail->getNGNailItem().NGPointList[i].x - ox) * zoomRate, (myThumbnail->getNGNailItem().NGPointList[i].y - oy) * zoomRate);
				ReviewNGPointList NGPoints = myThumbnail->getNGNailItem().NGPointList;
				int NGSingSize = myThumbnail->getNGSignSize();

				Review::DrawNGShapeToPainter(&painter, myThumbnail->getNGNailItem().NGPointList[i].Tag.NGColor, NGPoints[i].Tag.NGShape, center, NGSingSize/2);
			}
		}

		painter.end();

		//ui.lbNG->setPixmap( pix );
		ui.lbNG->setPixmap(NGPix);
		ui.lbNG->setMinimumSize(NGPix.width(), NGPix.height());
		ui.lbNG->setMaximumSize(NGPix.width(), NGPix.height());
	}

	QPixmap pix = myThumbnail->getMasterPieceImage();
	if(MainParent->isViewMaster()==true){
		ui.lbMaster->setPixmap(pix);
		ui.lbMaster->setMinimumSize(pix.width(), pix.height());
		ui.lbMaster->setMaximumSize(pix.width(), pix.height());
	}
}

void ExpandThumbnailDialog::paintEvent(QPaintEvent *event)
{
	QDialog::paintEvent(event);

	if(reqUpdate==false){
		return;
	}else{
		reqUpdate = false;
	}

	updateImage();
}
void ExpandThumbnailDialog::on_pushButtonSetKey_clicked()
{
	QString	Str=ui.comboBoxKeyCode->currentText();
	if(Str==/**/"F1"){
		KeyCode=1;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F1);
		myThumbnail->setFKey(Review::F1);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F2"){
		KeyCode=2;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F2);
		myThumbnail->setFKey(Review::F2);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F3"){
		KeyCode=3;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F3);
		myThumbnail->setFKey(Review::F3);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F4"){
		KeyCode=4;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F4);
		myThumbnail->setFKey(Review::F4);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F5"){
		KeyCode=5;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F5);
		myThumbnail->setFKey(Review::F5);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F6"){
		KeyCode=6;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F6);
		myThumbnail->setFKey(Review::F6);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F7"){
		KeyCode=7;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F7);
		myThumbnail->setFKey(Review::F7);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F8"){
		KeyCode=8;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F8);
		myThumbnail->setFKey(Review::F8);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F9"){
		KeyCode=9;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F9);
		myThumbnail->setFKey(Review::F9);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F10"){
		KeyCode=10;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F10);
		myThumbnail->setFKey(Review::F10);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F11"){
		KeyCode=11;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F11);
		myThumbnail->setFKey(Review::F11);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else if(Str==/**/"F12"){
		KeyCode=12;
		KeyType=true;
		//MainParent->SetFKeyIndex(myThumbnail->getIndexInGlobal() ,Review::F12);
		myThumbnail->setFKey(Review::F12);
		QColor FKeyColor = MainParent->setFKey(Review::convertFKeyQtToReview((Qt::Key)(Qt::Key_F1+KeyCode-1)));
		myThumbnail->setFKeyColor(FKeyColor);
		MainParent->getThumbnail(myThumbnail->getIndexInGlobal())->setFKeyColor(FKeyColor);
		done(true);
	}
	else{
		bool	ok;
		KeyCode=Str.toInt(&ok);
		if(ok==true){
			KeyType=false;
			done(true);
		}
	}
}
