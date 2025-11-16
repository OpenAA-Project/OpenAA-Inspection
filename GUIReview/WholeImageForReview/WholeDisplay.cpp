#include "WholeImageForReviewResource.h"
#include "WholeDisplay.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QStaticText>
#include <QTransform>
#include "XDataInLayer.h"
#include "XReviewStructure.h"
#include "XGUIReviewGlobal.h"
#include "../XGUIReviewCommonPacket.h"

WholeDisplay_impl::WholeDisplay_impl(ReviewPIBase *p,Review::SideType side_, int phase_, QWidget *parent)
		:mtGraphicUnit(parent)
		,PBase(p)
		,m_History(p)
		,m_NGSingDefaultColor(Qt::cyan),
		m_NGSingCurrentColor(Qt::magenta),m_WholeImage(),m_WholeImageView(),m_NGImageSize(),m_currentIndex(-1),
		m_currentNGRectVisible(true),m_NGNailSelectIndex(-1),m_WholeImageOrgSize(0,0),m_currentNGCrossView(true),m_NGPointView(true),
		m_phase(phase_),m_side(side_),m_DragIsActive(false),m_DragTopLeftPos(),m_Rotate(0)
{
	connect(this, SIGNAL(SignalMouseRDown(int,int)), SLOT(SlotMouseRDown(int,int)));
	connect(this, SIGNAL(SignalMouseMove(int,int)), SLOT(SlotMouseMove(int,int)));
	connect(this, SIGNAL(SignalMouseLDown(int,int)), SLOT(SlotMouseLDown(int,int)));
	GetCanvas()->setImageShiftDelay(INT_MAX);
	setPCENameViewThreshold(0);
}

WholeDisplay_impl::~WholeDisplay_impl()
{}

void WholeDisplay_impl::setNGNailPosList(const HistoryItem &history, bool redraw)
{
	HistoryItem hItem = history;

	for(int i=hItem.getNGNails().count()-1; i>=0; i--){
		if(hItem.getNGNails()[i].phase!=getPhase()){// フェイズが違う場合
			hItem.NGCount -= hItem.getNGNails().at(i).NGPointList.count();// 減算
			hItem.getNGNails().removeAt(i);// 摘出
		}
	}

	setHistory(hItem);

	setNGNailSelectIndex(-1);

	if(redraw){
		updateImage();
	}
}

void WholeDisplay_impl::clearNGNailPosList(bool redraw)
{
	setHistory(HistoryItem(PBase));
	
	if(redraw){
		updateImage();
	}
}

void WholeDisplay_impl::setWholeImage(const QImage &image, const QSize *orgSize, bool redraw)
{
	m_WholeImage = QImage();
	setWholeImageView(QImage());

	if(orgSize!=NULL){
		setWholeImageOrgSize(*orgSize);
	}else{
		setWholeImageOrgSize( image.size() );
	}

	if(image.isNull()==true){
		setCurrentViewRect(QRect(0, 0, 0, 0));
		update();
		return;
	}

	int	iW=image.width();
	int	iH=image.height();

	m_WholeImage = image;

	if(image.isNull()==false){
		setWholeImageView(image);
	}else{
		int	hW=getWholeImageOrgSize().width();
		int	hH=getWholeImageOrgSize().height();
		setWholeImageView(QImage(hW, hH, QImage::Format_RGB32));
	}

	if(redraw){
		updateImage();
	}
}

void WholeDisplay_impl::mousePressEvent(QMouseEvent *event)
{
	mtGraphicUnit::mousePressEvent(event);
}

void WholeDisplay_impl::mouseMoveEvent(QMouseEvent *event)
{
	mtGraphicUnit::mouseMoveEvent(event);
}

void WholeDisplay_impl::mouseReleaseEvent(QMouseEvent *event)
{
	mtGraphicUnit::mouseReleaseEvent(event);
}

void WholeDisplay_impl::SlotMouseRDown(int x, int y)
{
	setDragActive(false);
	QRect rect = getCurrentViewRect();
	if(rect.isEmpty()==false){
		emit SignalReqWholePicOrg(getSide(), getPhase());
		setCurrentViewRect(QRect());
		updateImage();
	}else{
		updateImage();
	}
}

void WholeDisplay_impl::SlotMouseMove(int x, int y)
{
	setDragCurrentMousePos(QPoint(x,y));
	if(isDragActive()==true){
		updateImage();
	}
	return;

	// 未動作
	HistoryItem hItem = getHistory();
	if(hItem.getNGNails().isEmpty()==true)return;
	
	QSize size = getWholeImage().size();
	size.scale(GetCanvas()->size(), Qt::KeepAspectRatio);
	double zoomRate = size.width() / (double)getWholeImage().size().width();
	
	for(int i=0; i<hItem.getNGNails().count(); i++){
		if((x-hItem.getNGNails()[i].MasterPosX*zoomRate)>=0 &&
			(x-hItem.getNGNails()[i].MasterPosX*zoomRate < getNGImageSize().width()*zoomRate) &&
			(x-hItem.getNGNails()[i].MasterPosY*zoomRate)>=0 &&
			(y-x-hItem.getNGNails()[i].MasterPosY*zoomRate < getNGImageSize().height()*zoomRate)){
			if(getNGNailSelectIndex()==i){
				return;
			}else{
				setNGNailSelectIndex(i);
				updateImage();
				return;
			}
		}
	}

	if(isNGNailSelected()==true){
		clearNGNailSelected();
		updateImage();
	}
}

void WholeDisplay_impl::SlotMouseLDown(int x, int y)
{
	//if(isNGNailSelected()==true){
	//	emit SignalSelectNG(phase, getNGNailSelectIndex());
	//}

	if(getCurrentViewRect().isEmpty()==false){
		setDragActive(false);
		return;
	}

	if(isDragActive()==false){
		setDragActive(true);
		setDragTopLeftPos(QPoint(x,y));
	}else{
		setDragActive(false);
		QRect	R=getDragOrgRect(getDragRect(QPoint(x,y)));
		emit SignalReqWholePicPiece(getSide(), getPhase(), R );
		updateImage();
	}
}

void WholeDisplay_impl::resizeEvent(QResizeEvent *event)
{
	mtGraphicUnit::resizeEvent(event);
	emit SignalResize();
}

void WholeDisplay_impl::updateImage()
{
	if(hasWholeImage()==false || hasWholeImageView()==false)return;

	qreal zoom = zoomRate();

	QImage *image;
	if(hasWholeImageView()==false){
		image = new QImage(getWholeImage());
	}else{
		image = new QImage(getWholeImageView());
	}
	int	iW=image->width();
	int	iH=image->height();

	//*image = image->scaled(size, Qt::KeepAspectRatio);

	QPainter painter;
	painter.begin(image);

	QPen defNGPen;
	defNGPen.setColor(getNGSingDefaultColor());
	defNGPen.setWidth(2);

	QBrush oldBrush;
	oldBrush = painter.brush();

	QPen currentPen;
	currentPen.setColor(getNGSingCurrentColor());
	currentPen.setWidth(2);

	QPen selectedPen;
	selectedPen.setColor(Qt::GlobalColor::yellow);
	selectedPen.setWidth(2);

	QPen piecePen;
	piecePen.setColor(Qt::GlobalColor::green);
	piecePen.setWidth(2);

	QBrush pieceBrush;
	{
		QColor color(Qt::GlobalColor::gray);
		color.setAlpha(100);
		pieceBrush.setColor(color);
	}
	pieceBrush.setStyle(Qt::BrushStyle::SolidPattern);

	// PCEの描画
	PCEList pceList = getPCEList();
	painter.setPen(piecePen);
	painter.setBrush(pieceBrush);
	for(int i=0; i<pceList.count(); i++){
		QRect rect;
		QPolygon polygon;
		QPoint offset = getOutlineOffset(pceList[i].page());

		bool drawTextFlag;
		if(zoom>getPCENameViewThreshold()){
			drawTextFlag = true;
		}else{
			drawTextFlag = false;
		}
		QRect drawTextRect;

		QTransform transform;
		transform.scale(zoom, zoom);
		transform.translate((offset - getCurrentViewRect().topLeft()).x(), (offset - getCurrentViewRect().topLeft()).y());
		pceList[i].drawShape(painter, transform);

		//switch(pceList[i].areaType()){
		//case PCEItem::Rect:
		//	rect = pceList[i].rect();
		//	rect.moveTopLeft( rect.topLeft() + offset - getCurrentViewRect().topLeft());
		//	rect = QRect(rect.x() * zoomRate, rect.y() * zoomRate, rect.width() * zoomRate, rect.height() * zoomRate);
		//	painter.drawRect(rect);

		//	drawTextRect = rect;

		//	break;
		//case PCEItem::Ellipse:
		//	rect = pceList[i].rect();
		//	rect.moveTopLeft( rect.topLeft() + offset - getCurrentViewRect().topLeft());
		//	rect = QRect(rect.x() * zoomRate, rect.y() * zoomRate, rect.width() * zoomRate, rect.height() * zoomRate);
		//	painter.drawEllipse(rect);

		//	drawTextRect = rect;

		//	break;
		//case PCEItem::Polygon:
		//	polygon = pceList[i].polygon();
		//	if(polygon.isEmpty()==false){
		//		int maxx, maxy, minx, miny;

		//		maxx = maxy = minx = miny = polygon.first().x();// 初期化

		//		for(int p=0; p<polygon.count(); p++){
		//			polygon[p] += offset - getCurrentViewRect().topLeft();
		//			polygon[p] = polygon[p] * zoomRate;

		//			maxx = qMax(maxx, polygon[p].x());
		//			maxy = qMax(maxy, polygon[p].y());
		//			minx = qMin(minx, polygon[p].x());
		//			miny = qMin(miny, polygon[p].y());
		//		}
		//		painter.drawPolygon(polygon);

		//		drawTextRect = QRect(minx, miny, qAbs(maxx - minx), qAbs(maxy - miny));
		//	}
		//	break;
		//default:
		//	// none
		//	break;
		//}

		if(drawTextFlag==true){
			//QTransform trans;
			//QFontMetrics fm = painter.fontMetrics();

			//qreal val = (qreal)drawTextRect.width()/fm.width(pceList[i].pieceName());

			//trans.scale(val, 1.0);

			//QTransform oldTrance = painter.transform();
			//painter.setTransform(trans);
			//QRect tRect = drawTextRect;
			//tRect.setLeft(drawTextRect.left() / val);
			//tRect.setWidth(drawTextRect.width() / val);
			//painter.drawText(tRect, pceList[i].pieceName(), QTextOption(Qt::AlignCenter));
			//painter.setTransform(oldTrance);

			pceList[i].drawText(painter, transform, QTextOption(Qt::AlignCenter));

			//drawTextRect = pceList[i].rect();
			//drawTextRect = QRect(drawTextRect.topLeft()*zoomRate, drawTextRect.bottomLeft()*zoomRate);

			//painter.drawText(drawTextRect, pceList[i].pieceName(), QTextOption(Qt::AlignCenter));
		}
	}
	painter.setBrush(oldBrush);

	const HistoryItem hItem = getHistory();
	
	if(getNGPointView()==true){
		QPen NGPen;
		NGPen.setColor(Qt::GlobalColor::red);
		NGPen.setWidth(2);

		painter.setPen(NGPen);
		
		for(int i=0; i<hItem.getNGNails().count(); i++){
			for(int j=0; j<hItem.getNGNails()[i].NGPointList.count(); j++){
				// 元マスターデータでの位置
				QPoint p = hItem.getNGNails()[i].NGPointList[j].getMasterPos();

				// アウトライン移動
				p += getOutlineOffset(hItem.getNGNails()[i].page);

				// 左上の座標をシフト
				p -= getCurrentViewRect().topLeft();

				painter.drawPoint(p*zoom);
			}
		}
	}

	if(getCurrentNGNailOnlyView()==false){
		for(int i=0; i<hItem.getNGNails().count(); i++){
			QPoint topleft(hItem.getNGNails()[i].MasterPosX, hItem.getNGNails()[i].MasterPosY);
			topleft += getOutlineOffset(hItem.getNGNails()[i].page);
			
			// 左上の座標をシフト
			topleft -= getCurrentViewRect().topLeft();

			topleft *= zoom;
			QRect rect;
			rect.setTopLeft(topleft);
			rect.setWidth(hItem.getNGNails()[i].NGImageWidth * zoom);
			rect.setHeight(hItem.getNGNails()[i].NGImageHeight * zoom);
			if(i!=getCurrentIndex() || isCurrentNGViewEnable()==false){
				if(getNGNailSelectIndex()==i){
					painter.setPen(selectedPen);
				}else{
					painter.setPen(defNGPen);
				}
				painter.drawRect(rect);
			}
		}
	}

	if(isCurrentNGViewEnable()==true && getCurrentIndex()>=0 && getCurrentIndex()<hItem.getNGNails().count()){

		int	NaiIndex=getCurrentIndex();

		GUIFormBase *GUIForm = PBase->GetLayersBase()->FindByName(ReviewGUI::Name::Root, ReviewGUI::Name::ShowThumbnail, /**/"");
		if(GUIForm!=NULL){
			GUICmdReqCurrentNailItem	ReqCmd(PBase->GetLayersBase());
			NGNailItemRef	RRef;
			ReqCmd.NailIndex=&RRef;
			GUIForm->TransmitDirectly(&ReqCmd);
			for(int i=0;i< hItem.getNGNails().count();i++){
				 if(hItem.getNGNails()[i]==*ReqCmd.NailIndex){
					NaiIndex	=i;
					break;
				 }
			}
		}


		const NGNailItem &item = hItem.getNGNails()[NaiIndex];
		QPoint topleft(item.MasterPosX, item.MasterPosY);
		topleft += getOutlineOffset(item.page);

		QPoint NGPOffset;
		for(int i=0; i<item.NGPointList.count(); i++){
			const ReviewNGPoint &ngp = item.NGPointList[i];
			NGPOffset += QPoint(ngp.AlignedX + ngp.ItemSearchedX, ngp.AlignedY + ngp.ItemSearchedY);
		}

		if(item.NGPointList.isEmpty()==false){
			NGPOffset /= item.NGPointList.count();
		}
		
		// 左上の座標をシフト
		topleft -= getCurrentViewRect().topLeft();
		topleft -= NGPOffset;
		
		topleft *= zoom;
		QRect rect;
		rect.setTopLeft(topleft);
		rect.setWidth(item.NGImageWidth * zoom);
		rect.setHeight(item.NGImageHeight * zoom);
		painter.setPen(currentPen);
		painter.drawRect(rect);

		if(getCurrentNGCrossView()==true){// クロス表示の時
			QPen crossPen;
			crossPen.setColor(QColor(Qt::white));
			crossPen.setWidth(1);
			painter.setPen(crossPen);

			// 原点
			QPoint NGPosOrg(item.MasterPosX + item.NGImageWidth/2.0 + getOutlineOffset(item.page).x(),
				item.MasterPosY + item.NGImageHeight/2.0 + getOutlineOffset(item.page).y());
			
			// 調整後
			QPoint XStart	(0,					(NGPosOrg.y() - getCurrentViewRect().top()) * zoom);
			QPoint XEnd		(image->width()-1,	(NGPosOrg.y() - getCurrentViewRect().top()) * zoom);
			QPoint YStart	((NGPosOrg.x() - getCurrentViewRect().left()) * zoom,	0);
			QPoint YEnd		((NGPosOrg.x() - getCurrentViewRect().left()) * zoom,	image->height()-1);

			//// アウトラインによる移動
			//XStart += topleft;
			//XEnd += topleft;
			//YStart += topleft;
			//YEnd += topleft;

			//// 拡大率設定
			//XStart *= zoomRate;
			//XEnd *= zoomRate;
			//YStart *= zoomRate;
			//YEnd *= zoomRate;

			// 描画
			painter.drawLine(XStart, XEnd);
			painter.drawLine(YStart, YEnd);
		}
	}

	painter.end();

	QTransform rotateTransform;
	rotateTransform.rotate(-rotate());
	*image = image->transformed(rotateTransform);

	if(isDragActive()==true){
		painter.begin(image);

		QPen pen;
		pen.setColor(QColor(Qt::GlobalColor::red));
		painter.setPen(pen);
		painter.drawRect(getDragRect(getDragCurrentMousePos()));

		//QPen pen2;
		//pen2.setColor(QColor(140, 140, 245));
		//painter.setPen(pen2);
		//painter.drawRect(getDragNoRotateRect(getDragRect(getDragCurrentMousePos())));

		painter.end();
	}


	GetCanvas()->SetImage(image);
}