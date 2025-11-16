#include "ShowThumbnailResource.h"
#include "Thumbnail.h"
#include "../XGUIReviewGlobal.h"
#include "XReviewStructure.h"
#include <QPainter>
#include <QColor>
#include <QNamespace.h>
#include "ShowThumbnail.h"
#include "ReviewStructurePacket.h"

Thumbnail::Thumbnail(ShowThumbnail *p ,int row, int column, QWidget *parent)
	:QWidget(parent)
	,Parent(p)
	,m_NGItem(NGNailItem())
	,m_row(row),m_column(column)
	,m_NGSignSize(10)
	,m_drawFlag(true)
	,m_selectedColor(QColor(255, 170, 127, 255))
	,m_isSelected(false)
	,m_FKeyColor(palette().window().color())
	,m_defaultWindowColor(palette().window().color())
	,m_viewMasterImage(true)
	,m_isDummy(false)
	,m_isDrawEdge(false)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
}

Thumbnail::~Thumbnail()
{}

Thumbnail *Thumbnail::createDup() const
{
	Thumbnail *ret = new Thumbnail(Parent ,getRow(), getColumn(), dynamic_cast<QWidget*>(parent()));
	ret->setChecked(isChecked());
	ret->setSide(Side);
	ret->setData(getNGNailItem(), getMasterPieceImage());
	ret->setIndexInLocal(getIndexInLocal());
	ret->setIndexInGlobal(getIndexInGlobal());
	ret->setFKeyColor(getFKeyColor());
	ret->setSelectedColor(getSelectedColor());
	ret->setNGSignSize(getNGSignSize());
	ret->setSelected(false);
	return ret;
}

void Thumbnail::updateData(void)
{
	if(m_NGItem.image().isNull()==false){
		// NG画像の設定
		ui.lbNGImage->setPixmap(QPixmap::fromImage(m_NGItem.image()));

		// NG箇所の設定
		//QList<QPoint> pList;
		//for(int i=0; i<m_NGItem.NGPointList.count(); i++){
		//	pList.append(QPoint(m_NGItem.NGPointList[i].x - m_NGItem.TargetPosX, m_NGItem.NGPointList[i].y - m_NGItem.TargetPosY));
		//}
		ui.lbNGImage->setPoints(m_NGItem.NGPointList);
		ui.lbNGImage->setTopLeftPoint(QPoint(m_NGItem.TargetPosX, m_NGItem.TargetPosY));
		ui.lbNGImage->setRound(m_NGSignSize);
	}else{
		// NG画像の設定
		ui.lbNGImage->setPixmap(m_MasterImage);

		// NG箇所の設定
		QList<QPoint> pList;
		
		QPoint target(m_NGItem.TargetPosX, m_NGItem.TargetPosY);
		QPoint master(m_NGItem.MasterPosX, m_NGItem.MasterPosY);

		QPoint shift = master - target;

		//for(int i=0; i<m_NGItem.NGPointList.count(); i++){
		//	pList.append(QPoint(m_NGItem.NGPointList[i].x - target.x() + shift.x(), m_NGItem.NGPointList[i].y - target.y() + shift.y()));
		//}
		ui.lbNGImage->setPoints(m_NGItem.NGPointList);
		ui.lbNGImage->setTopLeftPoint(QPoint(m_NGItem.TargetPosX - shift.x(), m_NGItem.TargetPosY - shift.y()));
		ui.lbNGImage->setRound(m_NGSignSize);
	}


	ui.lbNGImage->update();
	ui.lbMasterImage->setPixmap(m_MasterImage);
	ui.lbMasterImage->setVisible(m_viewMasterImage);

	//ui.lbNGImage->update();
	//ui.lbMasterImage->update();
}

void Thumbnail::enterEvent(QEvent *event)
{
	QWidget::enterEvent(event);

	emit entered(this);
	emit entered(getRow(), getColumn());
}

void Thumbnail::leaveEvent(QEvent *event)
{
	QWidget::leaveEvent(event);

	emit leaved(this);
	emit leaved(getRow(), getColumn());
}

void Thumbnail::setSelected(bool selected)
{
	m_isSelected = selected;

	if(m_isSelected==true){
		QPalette p = palette();
		p.setColor(QPalette::ColorRole::Window, m_selectedColor);
		setPalette(p);
	}else{
		QPalette p = palette();
		p.setColor(QPalette::ColorRole::Window, m_defaultWindowColor);
		setPalette(p);
	}
}

void Thumbnail::mousePressEvent(QMouseEvent *event)
{
	QWidget::mousePressEvent(event);

	if(event->button()==Qt::LeftButton){
		emit clicked(this);
		emit clicked(getRow(), getColumn());
	}
}

void Thumbnail::paintEvent(QPaintEvent *event)
{
	// 土台の準備
	//QPainter painter;
	//if(m_BackGroundColor!=Qt::white){
	//	QPen old_pen = painter.pen();
	//	QPen new_pen;
	//	new_pen.setWidth( 2 );
	//	new_pen.setColor( m_BackGroundColor );
	//	painter.setPen( new_pen );
	//	painter.drawRect(0, 0, width()-1, height()-1);
	//	painter.setPen( old_pen );
	//}
	//painter.begin(this);
	//if(m_isChecked==true){
	//	QPen pen(QColor(255, 170, 127, 255));
	//	painter.setPen(pen);
	//	painter.drawRect(rect());
	//}else{
	//	QColor color(Qt::white);
	//	painter.setPen(color);
	//	painter.drawRect(rect());
	//}
	//painter.end();

	//QPalette palette;

	//if(m_isChecked==true){
	//	palette.setColor(QPalette::ColorRole::Window, QColor(255, 170, 127));
	//}else{
	//	palette.setColor(QPalette::ColorRole::Window, QColor(255, 255, 255));
	//}
	//ui.lbMasterImage->setPalette(palette);
	//ui.lbNGImage->setPalette(palette);

	//ui.gridLayout->update();
	//setUpdatesEnabled(false);
	
	if(isDummy()==false){
		QPainter painter(this);
		QColor color;
		
		if(isSelected()==true){
			color = QColor(0, 0, 0);
			SetNailInformation(m_NGItem);
		}else{
			color = QColor(Qt::white);
		}

		painter.fillRect(rect(), color);

		if(isChecked()==true){
			QBrush brush;
			//brush.setStyle(Qt::BrushStyle::Dense6Pattern);
			brush.setStyle(Qt::BrushStyle::SolidPattern);
			brush.setColor(m_FKeyColor);
			
			painter.setBrush(brush);

			int	FrameW=4;
			QRect	RRect(rect().left()+FrameW,rect().top()+FrameW,rect().width()-2*FrameW,rect().height()-FrameW*2);
			painter.fillRect(RRect, brush);
		}
	}else{
		QPainter painter(this);
		painter.fillRect(rect(), palette().window());
	}
	//setUpdatesEnabled(true);

	if(m_isDrawEdge==true){
		QPainter painter;
		painter.begin(ui.lbNGImage);
		painter.setPen(QColor(Qt::black));
		painter.drawRect(ui.lbNGImage->rect());
		painter.end();

		painter.begin(ui.lbMasterImage);
		painter.drawRect(ui.lbMasterImage->rect());
		painter.end();
	}

	if(m_drawFlag==false)return;
	m_drawFlag = false;

	//if((m_viewMasterImage==true) && (ui.horizontalLayout->indexOf(ui.lbMasterImage)==-1)){
	//	ui.horizontalLayout->addWidget(ui.lbMasterImage);
	//}

	//ui.horizontalLayout->update();

	//ui.horizontalLayout->removeWidget(ui.lbMasterImage);
	//ui.horizontalLayout->removeWidget(ui.lbNGImage);

	//ui.horizontalLayout->update();

	if(isDummy()==true){// ダミー(穴埋め用の場合)
		QPixmap pix;// = QPixmap(m_NGItem.NGImageWidth, m_NGItem.NGImageHeight).scaled(ui.lbNGImage->width(), ui.lbNGImage->height(), Qt::KeepAspectRatio);
		ui.lbNGImage->setPixmap(pix);
		if(m_viewMasterImage==true){
			ui.lbMasterImage->setPixmap(pix);
			ui.lbMasterImage->setVisible(true);
			ui.horizontalLayout->addWidget(ui.lbMasterImage);
			ui.horizontalLayout->addWidget(ui.lbNGImage);
			
			ui.lbMasterImage->updateGeometry();
			ui.lbNGImage->updateGeometry();
		}else{
			ui.lbMasterImage->setPixmap(QPixmap());
			ui.lbMasterImage->setVisible(false);
			//ui.horizontalLayout->addWidget(ui.lbMasterImage);
			ui.horizontalLayout->addWidget(ui.lbNGImage);

			ui.lbNGImage->updateGeometry();
		}
		return;
	}

	//if(m_NGItem.NGImage.isNull()==true){// NG画像が無い場合はマスター画像と同じ画像を表示する
	//	QPixmap pix;
	//	if(m_MasterImage.isNull()==false){
	//		pix = m_MasterImage;//.scaled(ui.lbNGImage->width(), ui.lbNGImage->height(), Qt::KeepAspectRatio);
	//	}
	//	if(pix.isNull()==false){
	//		double zoomRate = pix.width() / (double)m_MasterImage.width();// 拡大率
	//		QPoint target(m_NGItem.TargetPosX, m_NGItem.TargetPosY);
	//		QPoint master(m_NGItem.MasterPosX, m_NGItem.MasterPosY);
	//		//int ox = m_NGItem.TargetPosX;// 1
	//		//int oy = m_NGItem.TargetPosY;// 1
	//		//int sx = m_NGItem.MasterPosX - ox;// 0 - 1 = -1
	//		//int sy = m_NGItem.MasterPosY - oy;// 0 - 1 = -1

	//		QPoint shift = master - target;
	//	
	//		QPainter painter;
	//		painter.begin(&pix);

	//		QPen pen;
	//		pen.setColor( QColor(Qt::blue) );
	//		painter.setPen(pen);
	//	
	//		for(int i=0; i<m_NGItem.NGPointList.count(); i++){
	//			painter.drawEllipse(QPoint((m_NGItem.NGPointList[i].x - target.x() + shift.x()) * zoomRate, (m_NGItem.NGPointList[i].y - target.y() + shift.y()) * zoomRate), m_NGSignSize, m_NGSignSize);
	//		}

	//		painter.end();
	//	}
	//	ui.lbNGImage->setPixmap(pix);
	//}else{
	//	QPixmap pix;
	//	if(m_NGItem.NGImage.isNull()==false){
	//		pix = QPixmap::fromImage(m_NGItem.NGImage);//.scaled(ui.lbNGImage->width(), ui.lbNGImage->height(), Qt::KeepAspectRatio));
	//	}

	//	if(pix.isNull()==false){
	//		double zoomRate = pix.width() / (double)m_NGItem.NGImage.width();// 拡大率
	//		int ox = m_NGItem.TargetPosX;
	//		int oy = m_NGItem.TargetPosY;

	//		QPainter painter;
	//		painter.begin(&pix);

	//		QPen pen;
	//		pen.setColor( QColor(Qt::red) );
	//		painter.setPen(pen);

	//		for(int i=0; i<m_NGItem.NGPointList.count(); i++){
	//			painter.drawEllipse(QPoint((m_NGItem.NGPointList[i].x - ox) * zoomRate, (m_NGItem.NGPointList[i].y - oy) * zoomRate), m_NGSignSize, m_NGSignSize);
	//		}

	//		painter.end();
	//	}
	//	ui.lbNGImage->setPixmap(pix);
	//}

	//if(m_viewMasterImage==true && m_MasterImage.isNull()==false){
	//	ui.lbMasterImage->setPixmap(m_MasterImage);//.scaled(ui.lbMasterImage->width(), ui.lbMasterImage->height(), Qt::KeepAspectRatio));
	//	ui.lbMasterImage->setVisible(true);
	//	ui.horizontalLayout->addWidget(ui.lbMasterImage);
	//}else{
	//	ui.lbMasterImage->setPixmap(QPixmap());
	//	ui.lbMasterImage->setVisible(false);
	//}

	//ui.horizontalLayout->addWidget(ui.lbNGImage);

	//ui.lbMasterImage->updateGeometry();
	//ui.lbNGImage->updateGeometry();
}

void Thumbnail::SetNailInformation(NGNailItem NGItem)
{
	ReviewPIBase *RBase = Parent->GetReviewBase();

	CmdReqWholeImageInfo CmdReqWInfo(Parent->GetLayersBase());
	RBase->TransmitDirectly(&CmdReqWInfo);

	CmdReqForSaveNGList	hCmdReqForSaveNGList(Parent->GetLayersBase());

	QList<QList<QPoint> > outlineOffset;
	switch(Side){
	case Review::Front:
		outlineOffset = CmdReqWInfo.FrontOutlineOffset;
		hCmdReqForSaveNGList.Top=true;
		break;
	case Review::Back:
		outlineOffset = CmdReqWInfo.BackOutlineOffset;
		hCmdReqForSaveNGList.Top=false;
		break;
	default:
		return;
		break;
	}

	int		XPos;
	int		YPos;
	if(NGItem.NGPointList.count()>0){
		XPos=NGItem.NGPointList[0].x+ outlineOffset[NGItem.phase][NGItem.page].x();
		YPos=NGItem.NGPointList[0].y+ outlineOffset[NGItem.phase][NGItem.page].y();
	}
	else{
		XPos=NGItem.TargetPosX + outlineOffset[NGItem.phase][NGItem.page].x();
		YPos=NGItem.TargetPosY + outlineOffset[NGItem.phase][NGItem.page].y();
	}

	CmdReqCSVOffset	ViewOffset(Parent->GetLayersBase());
	RBase->TransmitDirectly(&ViewOffset);

	QString	Message;

	if(ViewOffset.CSVUnitMM==false){
		QString xyStr = QString(/**/"%1,%2").arg(XPos).arg(YPos);
		Message=QString("Position｣ｺ")+xyStr;
	}
	else{
		XPos=XPos*ViewOffset.CSVMagnificationX+ViewOffset.CSVOffsetX;
		YPos=YPos*ViewOffset.CSVMagnificationY+ViewOffset.CSVOffsetY;
		if(ViewOffset.CSVReverseX==true){
			XPos=-XPos;
		}
		if(ViewOffset.CSVReverseY==true){
			YPos=-YPos;
		}
		QString xyStr = QString::number(Parent->GetParamGlobal()->TransformPixelToUnit(XPos),'f',Parent->GetParamGlobal()->SmallNumberFigure)
					   +QString(/**/",")
					   +QString::number(Parent->GetParamGlobal()->TransformPixelToUnit(YPos),'f',Parent->GetParamGlobal()->SmallNumberFigure);
		Message=QString("Position｣ｺ")+xyStr;
	}
	
	CmdReqInsLib Send(Parent->GetLayersBase());
	RBase->TransmitDirectly(&Send);

	QString LibName = /**/"";
	QList<InsLibraryItem> list = Send.FrontInsLibHash.values(NGItem.getLibraryRal());

	for(QList<InsLibraryItem>::Iterator LibItem=list.begin(); LibItem!=list.end(); LibItem++){
		if(LibItem->LibCode==NGItem.getLibraryCode()){
			LibName = LibItem->LibName;
			break;
		}
	}
	Message = Message + QString("  ,Lib:")+LibName;
	Message = Message + QString("  ,NGCount:")+QString::number(NGItem.NGPointList.count());

	QStringList	PieceNameList;
	QString	PieceName;
	for(int ng=0; ng<NGItem.NGPointList.count(); ng++){
		for(int pci=0; pci<NGItem.NGPointList[ng].PCEItems.count(); pci++){
			if(NGItem.NGPointList[ng].PCEItems[pci].pieceName().isEmpty()==false){
				QString	AName=NGItem.NGPointList[ng].PCEItems[pci].pieceName();
				bool	Found=false;
				for(int i=0;i<PieceNameList.count();i++){
					if(PieceNameList[i]==AName){
						Found=true;
						break;
					}
				}
				if(Found==false){
					PieceNameList.append(AName);
					PieceName = PieceName + QString(/**/" ")+AName;
				}
			}
		}
	}
	if(PieceName.isEmpty()==false){
		Message = Message + QString(" ,Piece name :")+PieceName;
	}

	Parent->ShowLabelInfo(Message);
}