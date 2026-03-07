/*
 * Copyright (C) 2025
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

#include "ButtonToShowTotalNGMapResource.h"
#include "ButtonToShowTotalNGMap.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

extern char *sRoot;
extern char *sName;

TotalNGMap::TotalNGMap(LayersBase *Base, ReviewPIBase *RBase, QWidget *parent)
	:QDialog(parent)
{
	setReviewPIBase(RBase);
	setLayersBase(Base);
	setSplitX(100);
	setSplitY(100);
	setNGDrawColor(QColor(Qt::red));
	setNGDrawSize(5);
	setNGDrawShape(TotalNGMap::NGDrawShapeType::Fill_Rectangle);
	setIgnoreErrorInspect(false);

	m_viewScene = new QGraphicsScene;
	m_viewItem = new QGraphicsPixmapItem;

	ui.setupUi(this);

	ui.gvImageView->setScene(m_viewScene);
	m_viewScene->addItem(m_viewItem);

	ui.twVautTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui.twVautTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	setWindowTitle(/**/"TotalNGMapFrom");
}

TotalNGMap::~TotalNGMap()
{
	ui.gvImageView->setScene(NULL);
	m_viewScene->removeItem(m_viewItem);

	delete m_viewItem;
	delete m_viewScene;
}

void TotalNGMap::setNGPoints(const OrganizedHistoryListPtr OrgHistoryListPtr)
{
	clearImage();
	clearPointList();

	if(OrgHistoryListPtr==NULL){
		return;
	}

	QList<QImage> FrontImageList, BackImageList;
	QList<QList<QPoint> > FrontNGPosList, BackNGPosList;

	foreach(OrganizedHistoryItem hitem, *OrgHistoryListPtr){// �e��������
		if(isIgnoreErrorInspect()==true && hitem.isErrorBoard()==true){
			continue;
		}

		if(hitem.getFront()!=NULL){
			for(NGNailList::Iterator item = hitem.getFront()->getNGNails().begin(); item!=hitem.getFront()->getNGNails().end(); item++){// �eNG�摜�P�ʏ���
				
				while(FrontNGPosList.count()<=item->phase){
					FrontNGPosList << QList<QPoint>();
				}

				for(ReviewNGPointList::Iterator NGitem = item->NGPointList.begin(); NGitem!=item->NGPointList.end(); NGitem++){// �eNG�P��
					FrontNGPosList[item->phase].append( QPoint( NGitem->x, NGitem->y ) );// NG�ʒu���P�ǉ�
				}
			}
			for(int phase=0; phase<FrontNGPosList.count(); phase++){
				uniqQPointList(FrontNGPosList[phase]);
			}
		}
		if(hitem.getBack()!=NULL){
			for(NGNailList::Iterator item = hitem.getBack()->getNGNails().begin(); item!=hitem.getBack()->getNGNails().end(); item++){// �eNG�摜�P�ʏ���
				
				while(BackNGPosList.count()<=item->phase){
					BackNGPosList << QList<QPoint>();
				}

				for(ReviewNGPointList::Iterator NGitem = item->NGPointList.begin(); NGitem!=item->NGPointList.end(); NGitem++){// �eNG�P��
					BackNGPosList[item->phase].append( QPoint( NGitem->x, NGitem->y ) );// NG�ʒu���P�ǉ�
				}
			}
			for(int phase=0; phase<BackNGPosList.count(); phase++){
				uniqQPointList(BackNGPosList[phase]);
			}
		}
	}
}

void TotalNGMap::uniqQPointList(QList<QPoint> &list)
{
	if(list.empty())return;

	std::sort(list.begin(), list.end(), compair);

	QList<QPoint> ulist;
	QPoint ch = list.front();
	ulist.append(ch);

	for(QList<QPoint>::Iterator it=list.begin()+1; it!=list.end(); it++){
		if(*it!=ch){
			ulist.append(*it);
			ch = *it;
		}
	}

	list = ulist;
}

bool TotalNGMap::isShowEnable() const
{
	for(int phase=0; phase<phaseCount(Review::Front); phase++){
		if(image(Review::Front, phase).isNull()==false){
			return true;
		}
	}

	for(int phase=0; phase<phaseCount(Review::Back); phase++){
		if(image(Review::Back, phase).isNull()==false){
			return true;
		}
	}

	return false;
}

void TotalNGMap::setWholeImage(QList<QImage> &FrontImg, QList<QImage> &BackImg)
{
	setImage(Review::Front, FrontImg);
	setImage(Review::Back, BackImg);
}

void TotalNGMap::paintEvent(QPaintEvent *event)
{
	ui.twVautTable->verticalHeader()->reset();
	QDialog::paintEvent(event);
	//for(int phase=0; phase<phaseCount(Review::Front); phase++){
	//	QImage FrontPix = getImage(Review::Front, phase);
	//	if(FrontPix.isNull()==false){
	//		const StretchImageWidget *widget = getStretchImageWidget(Review::Front, phase);
	//		QPixmap FrontView = QPixmap::fromImage(FrontPix.scaled(widget->size(), Qt::KeepAspectRatio));
	//		QSize size = FrontPix.size();
	//		size.scale(widget->size(), Qt::KeepAspectRatio);
	//		double zoomRate = size.width() / (double)FrontPix.width();
	//		QPainter painter;
	//		painter.begin(&FrontView);
	//		drawNGPoints(painter, getPointList(Review::Front, phase), zoomRate);// NG�ӏ��̏�������
	//		painter.end();
	//		->setPixmap(FrontView);
	//	}
	//}
	//
	//for(int phase=0; phase<phaseCount(Review::Front); phase++){
	//	QImage BackPix = getImage(Review::Back, phase);
	//	if(BackPix.isNull()==false){
	//		QPixmap BackView = QPixmap::fromImage(BackPix.scaled(ui.BackCanvas->size(), Qt::KeepAspectRatio));
	//		QSize size = BackPix.size();
	//		size.scale(ui.BackCanvas->size(), Qt::KeepAspectRatio);
	//		double zoomRate = size.width() / (double)BackPix.width();
	//		QPainter painter;
	//		painter.begin(&BackView);
	//		drawNGPoints(painter, getPointList(Review::Back, phase), zoomRate);// NG�ӏ��̏�������
	//		painter.end();
	//		ui.BackCanvas->setPixmap(BackView);
	//	}
	//}
	//QPainter painter;

	//// �\���y�C���g

	//if(FrontPix.isNull()==false){
	//	// ���T�C�Y���̑傫���m�F
	//	QSize frontWholeSize = FrontPix.size();
	//	QSize frontScaledSize = FrontPix.size();
	//	frontScaledSize.scale(ui.FrontCanvas->size(), Qt::KeepAspectRatio);

	//	double zoomRate = frontScaledSize.width() / (double)frontWholeSize.width();// �g�嗦

	//	// ���T�C�Y
	//	QPixmap destImg = QPixmap::fromImage(FrontPix.scaled(frontScaledSize, Qt::KeepAspectRatio));

	//	// ���T�C�Y����NG�ʒu
	//	QList<QPoint> FrontScaledNGPointList;
	//	for(int i=0; i<FrontNGPosList.count(); i++){
	//		FrontScaledNGPointList.append(FrontNGPosList[i] * zoomRate);
	//	}

	//	painter.begin(&destImg);
	//	drawNGPoints(painter, FrontScaledNGPointList);// NG�ӏ��̏�������
	//	painter.end();

	//	ui.FrontCanvas->setPixmap(destImg);// �摜�̓\���t��
	//}

	//// �����y�C���g
	//// ���T�C�Y���̑傫���m�F
	//if(BackPix.isNull()==false){
	//	QSize backWholeSize = BackPix.size();
	//	QSize backScaledSize = BackPix.size();
	//	backScaledSize.scale(ui.BackCanvas->size(), Qt::KeepAspectRatio);

	//	double zoomRate = backScaledSize.width() / backWholeSize.width();// �g�嗦

	//	// ���T�C�Y
	//	QPixmap destImg = QPixmap::fromImage(BackPix.scaled(backScaledSize, Qt::KeepAspectRatio));

	//	// ���T�C�Y����NG�ʒu
	//	QList<QPoint> BackScaledNGPointList;
	//	for(int i=0; i<BackNGPosList.count(); i++){
	//		BackScaledNGPointList.append(BackNGPosList[i] * zoomRate);
	//	}

	//	painter.begin(&destImg);
	//	drawNGPoints(painter, BackScaledNGPointList);// NG�ӏ��̏�������
	//	painter.end();
	//
	//	ui.BackCanvas->setPixmap(destImg);// �摜�̓\���t��
	//}
}

void TotalNGMap::drawNGPoints(QPainter &painter, QList<QPoint> &posList, double zoomRate)
{
	QPen pen;
	QPen oldPen = painter.pen();

	pen.setColor( NGDrawColor() );
	pen.setWidth( 1 );
	painter.setPen(pen);
	
	Q_FOREACH(QPoint p, posList){
		painter.drawEllipse(p * zoomRate, NGDrawSize()/2, NGDrawSize()/2);// �Ƃ肠�����ۂ���
	}

	painter.setPen(oldPen);
}

void TotalNGMap::on_pbClose_clicked()
{
	m_targetPoint = QPoint();
	accept();
}

void TotalNGMap::resizeEvent(QResizeEvent *event)
{
	updateData();
	updateVautMapList();
	//ui.twVautTable->verticalHeader()->reset();
	ui.twVautTable->horizontalHeader()->reset();
	updateImage();
}

void TotalNGMap::showEvent(QShowEvent *event)
{
	static bool block = false;

	if(block==true){
		return;
	}

	block = true;

	QScreen *screen = QGuiApplication::primaryScreen();

	qreal fillWid = 0.6;
	qreal fillHei = 0.8;
	m_targetPoint = QPoint();

	resize(screen->geometry().width()*fillWid, screen->geometry().height()*fillHei);

	QRect r = geometry();

	r.moveTopLeft( QPoint(screen->geometry().width()*(1-fillWid)/2.0
						, screen->geometry().height()*(1-fillHei)/2.0 ) );

	setGeometry( r );

	updateData();
	updateVautMapList();
	updateVautTable();
	updateImage();

	setHidden(true);
	setHidden(false);

	//ui.twVautTable->verticalHeader()->reset();
	ui.twVautTable->horizontalHeader()->reset();

	//int wid = ui.twVautTable->horizontalHeader()->width();
	//int wid2 = ui.twVautTable->verticalHeader()->width();
	//int wid3 = ui.twVautTable->verticalScrollBar()->width();
	//int wid4 = ui.twVautTable->lineWidth()*5;
	////int offset = 100;

	//ui.twVautTable->setMinimumWidth( wid + wid2 + wid3 + wid4 );
	//ui.twVautTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	//ui.twVautTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	ui.twVautTable->repaint();
	ui.gvImageView->repaint();

	block = false;
}

void TotalNGMap::closeEvent(QCloseEvent *event)
{
	m_targetPoint = QPoint();
}

void TotalNGMap::on_cbPhase_currentIndexChanged(int index)
{
	m_targetPoint = QPoint();
	updateVautTable();
	updateImage();
}

void TotalNGMap::on_cbSide_currentIndexChanged(int index)
{
	m_targetPoint = QPoint();
	updateVautTable();
	updateImage();
}

void TotalNGMap::on_twVautTable_cellClicked(int row, int column)
{
	QString str = ui.twVautTable->item(row, 1)->text();
	QString pattern = "\\((.+),(.+)\\)-\\((.+),(.+)\\)";

	// anchoredPattern で完全一致化し、オプションで最小マッチを有効にする
	QRegularExpression exp (QRegularExpression::anchoredPattern(pattern),
							QRegularExpression::InvertedGreedinessOption);

	QRegularExpressionMatch match = exp.match(str);

	if (match.hasMatch()) {
		qreal x = (match.captured(1).toInt() + match.captured(3).toInt())/2.0;
		qreal y = (match.captured(2).toInt() + match.captured(4).toInt())/2.0;

		CmdReqWholeImageInfo winfo(layersBase());
		reviewPIBase()->TransmitDirectly(&winfo);

		const QSizeF wholeSize = winfo.getWholeOriginalSize(currentSide(), currentPhase());

		if(wholeSize.isValid()==true){
			int xp = (int)(x / wholeSize.width() * splitX());
			int yp = (int)(y / wholeSize.height() * splitY());

			m_targetPoint = QPoint(xp, yp);
		}else{
			m_targetPoint = QPoint();
		}

		updateImage();
	}else{
		m_targetPoint = QPoint();
		updateImage();
	}
}

void TotalNGMap::updateData()
{
	if(reviewPIBase()!=NULL){
		m_FrontImageList.clear();
		m_FrontNGPosList.clear();
		m_BackImageList.clear();
		m_BackNGPosList.clear();

		// ���݂̃}�X�^�[�f�[�^�������擾
		CmdReqMasterDataInfo minfo(layersBase());
		reviewPIBase()->TransmitDirectly(&minfo);

		CmdReqWholeImageInfo winfo(layersBase());
		reviewPIBase()->TransmitDirectly(&winfo);

		if(minfo.Ret==false){
			ui.cbPhase->setCurrentIndex(-1);
			ui.cbPhase->setEnabled(false);
			ui.cbSide->setCurrentIndex(-1);
			ui.cbSide->setEnabled(false);
			return;
		}else{
			ui.cbPhase->setEnabled(true);
			ui.cbSide->setEnabled(true);
		}

		for(int phase=0; phase<minfo.FrontMasterDataInfo.PhaseNumb || phase<minfo.BackMasterDataInfo.PhaseNumb; phase++){
			QSize reqFImgSize = winfo.FrontWholeOrizinalSize[phase];
			reqFImgSize.scale(ui.gvImageView->viewport()->size(), Qt::KeepAspectRatio);

			QSize reqBImgSize = winfo.BackWholeOrizinalSize[phase];
			reqBImgSize.scale(ui.gvImageView->viewport()->size(), Qt::KeepAspectRatio);

			// �S�̉摜���擾 �\ //
			CmdReqWholeImage wi(m_LBase);
			wi.setReqSize( reqFImgSize );
			wi.setReqPhase( phase );

			reviewPIBase()->TransmitDirectly(&wi);

			m_FrontImageList << wi.getWholePic(Review::Front);
			
			// �S�̉摜���擾 ��
			wi.setReqSize( reqBImgSize );
			wi.setReqPhase( phase );

			reviewPIBase()->TransmitDirectly(&wi);

			m_BackImageList << wi.getWholePic(Review::Back);

			m_FrontNGPosList << QList<QPoint>();
			m_BackNGPosList << QList<QPoint>();
		}

		// �\������NG�|�C���g�̍X�V
		CmdReqOrganizedHistoryList reqOrgHist(layersBase());
		reviewPIBase()->TransmitDirectly(&reqOrgHist);

		for(int i=0; i<reqOrgHist.listPtr->count(); i++){
			const OrganizedHistoryItem &currentHistory = reqOrgHist.listPtr->at(i);
			if(isIgnoreErrorInspect()==true && currentHistory.isErrorBoard()==true){
				continue;
			}
			if(currentHistory.hasFront()){
				const NGNailList &fNGNailList = currentHistory.getFront()->getNGNails();
				for(int n=0; n<fNGNailList.count(); n++){
					const NGNailItem &fitem = fNGNailList.at(n);
					for(int p=0; p<fitem.NGPointList.count(); p++){
						qreal fZoomRate = m_FrontImageList.at(fitem.phase).width() / (qreal)winfo.FrontWholeOrizinalSize.at(fitem.phase).width();
						QPoint ngp = fitem.NGPointList.at(p).getMasterPos();
						ngp += winfo.FrontOutlineDrawOffset.at(fitem.phase).at(fitem.page);
						ngp *= fZoomRate;
						m_FrontNGPosList[fitem.phase] << ngp;
					}
				}
				
			}
			if(currentHistory.hasBack()){
				const NGNailList &bNGNailList = reqOrgHist.listPtr->at(i).getBack()->getNGNails();
				for(int n=0; n<bNGNailList.count(); n++){
					const NGNailItem &bitem = bNGNailList.at(n);
					for(int p=0; p<bitem.NGPointList.count(); p++){
						qreal bZoomRate = m_BackImageList.at(bitem.phase).width() / (qreal)winfo.BackWholeOrizinalSize.at(bitem.phase).width();
						QPoint ngp = bitem.NGPointList.at(p).getMasterPos();
						ngp += winfo.BackOutlineDrawOffset.at(bitem.phase).at(bitem.page);
						ngp *= bZoomRate;
						m_BackNGPosList[bitem.phase] << ngp;
					}
				}
			}
		}
	}
}

void TotalNGMap::updateVautMapList()
{
	if(reviewPIBase()!=NULL){
		//
		CmdReqMasterDataInfo minfo(layersBase());
		reviewPIBase()->TransmitDirectly(&minfo);

		// �S�̉摜�����̎擾
		CmdReqWholeImageInfo winfo(layersBase());
		reviewPIBase()->TransmitDirectly(&winfo);

		// ���������擾
		CmdReqOrganizedHistoryList reqOrgHist(layersBase());
		reviewPIBase()->TransmitDirectly(&reqOrgHist);

		m_FrontVautMapList.clear();
		m_BackVautMapList.clear();

		createVautMap(minfo.FrontMasterDataInfo.PhaseNumb, splitX(), splitY());

		// NG�|�C���g���瓊�[
		for(int i=0; i<reqOrgHist.listPtr->count(); i++){
			const OrganizedHistoryItem &currentHistory = reqOrgHist.listPtr->at(i);
			if(isIgnoreErrorInspect()==true && currentHistory.isErrorBoard()==true){
				continue;
			}
			if(currentHistory.hasFront()){
				const NGNailList &fNGNailList = currentHistory.getFront()->getNGNails();
				for(int n=0; n<fNGNailList.count(); n++){
					const NGNailItem &fitem = fNGNailList.at(n);
					for(int p=0; p<fitem.NGPointList.count(); p++){
						QPoint ngp = fitem.NGPointList.at(p).getMasterPos();
						ngp += winfo.FrontOutlineDrawOffset.at(fitem.phase).at(fitem.page);

						int x = ngp.x() / (qreal)winfo.FrontWholeOrizinalSize[fitem.phase].width() * splitX();
						int y = ngp.y() / (qreal)winfo.FrontWholeOrizinalSize[fitem.phase].height() * splitY();

						m_FrontVautMapList[fitem.phase][y][x] += 1;
					}
				}
			}
			if(currentHistory.hasBack()){
				const NGNailList &bNGNailList = reqOrgHist.listPtr->at(i).getBack()->getNGNails();
				for(int n=0; n<bNGNailList.count(); n++){
					const NGNailItem &bitem = bNGNailList.at(n);
					for(int p=0; p<bitem.NGPointList.count(); p++){
						QPoint ngp = bitem.NGPointList.at(p).getMasterPos();
						ngp += winfo.BackOutlineDrawOffset.at(bitem.phase).at(bitem.page);

						int x = ngp.x() / (qreal)winfo.BackWholeOrizinalSize[bitem.phase].width() * splitX();
						int y = ngp.y() / (qreal)winfo.BackWholeOrizinalSize[bitem.phase].height() * splitY();

						m_BackVautMapList[bitem.phase][y][x] += 1;
					}
				}
			}
		}
	}
}

void TotalNGMap::updateVautTable()
{
	ui.twVautTable->setRowCount(0);

	if(reviewPIBase()!=NULL){
		const _vautMap &map = currentVautMap();

		if(map.isEmpty()==true){
			return;
		}

		int row = map.count();
		int column = map.first().count();
		if(column==0){
			return;
		}
		for(int y=1; y<map.count(); y++){
			if(column!=map.at(y).count()){
				return;
			}
		}

		CmdReqWholeImageInfo winfo(layersBase());
		reviewPIBase()->TransmitDirectly(&winfo);

		Review::SideType side = currentSide();
		int phase = currentPhase();

		qreal unitWidth = winfo.getWholeOriginalSize(side,phase).width() / (qreal)splitX();
		qreal unitHeight = winfo.getWholeOriginalSize(side,phase).height() / (qreal)splitY();

		QList<VautNGListItem> list;
		for(int y=0; y<row; y++){
			for(int x=0; x<column; x++){
				int cnt = map.at(y).at(x);
				if(cnt==0){
					continue;
				}
				
				int top = y*unitHeight;
				int bottom = top + unitHeight;
				int left = x*unitWidth;
				int right = left + unitWidth;

				list << VautNGListItem(cnt, QRect(QPoint(left, top), QPoint(right, bottom)));
			}
		}

		std::sort(list.begin(), list.end(), VautNGListItem::DescendingOrder);

		ui.twVautTable->setRowCount(list.count());

		for(int i=0; i<list.count(); i++){
			const int cnt = list.at(i).NGCount();
			const QRect r = list.at(i).rect();

			QString aStr = QString(/**/"(%1,%2)-(%3,%4)")
				.arg(r.left()).arg(r.top())
				.arg(r.right()).arg(r.bottom());
			
			QTableWidgetItem *nItem = new TableWidgetIntItem(cnt);

			ui.twVautTable->setItem(i, 0, nItem);

			QTableWidgetItem *aItem = new QTableWidgetItem(aStr);

			ui.twVautTable->setItem(i, 1, aItem);
		}
		
		int maxNGCountStringLength;
		int maxAreaStringLength;

		{
			QFontMetrics h0met(ui.twVautTable->horizontalHeaderItem(0)->font());
			QFontMetrics h1met(ui.twVautTable->horizontalHeaderItem(1)->font());
			maxNGCountStringLength = h0met.horizontalAdvance(ui.twVautTable->horizontalHeaderItem(0)->text());
			maxAreaStringLength = h1met.horizontalAdvance(ui.twVautTable->horizontalHeaderItem(1)->text());
		}

		for(int row=0; row<ui.twVautTable->rowCount(); row++){
			QString nTxt = ui.twVautTable->item(row, 0)->text();
			QString aTxt = ui.twVautTable->item(row, 1)->text();

			int nlen = ui.twVautTable->fontMetrics().horizontalAdvance(nTxt);
			if(maxNGCountStringLength<nlen){
				maxNGCountStringLength = nlen;
			}

			int alen = ui.twVautTable->fontMetrics().horizontalAdvance(aTxt);
			if(maxAreaStringLength<alen){
				maxAreaStringLength = alen;
			}
		}

		/*int vwid = ui.twVautTable->verticalHeader()->

		int wid = ui.twVautTable->verticalHeader()->width() + maxAreaStringLength + maxNGCountStringLength
			+ ui.twVautTable->verticalHeader()->lineWidth()*2 + ui.twVautTable->lineWidth()*3;
		ui.twVautTable->setMinimumWidth( wid );*/
		//ui.twVautTable->setMinimumWidth(maxNGCountStringLength + maxAreaStringLength + ui.twVautTable->verticalHeader()->width());
		//ui.twVautTable->sortByColumn(0, Qt::SortOrder::DescendingOrder);
		//ui.twVautTable->verticalHeader()->reset();
		//ui.twVautTable->horizontalHeader()->reset();

		ui.twVautTable->update();
	}
}

void TotalNGMap::updateImage()
{
	int phase = ui.cbPhase->currentIndex();
	int side = ui.cbSide->currentIndex();

	// ���݂̑Ώۂ̉摜���I��
	QImage img;
	if(side==0){
		if(phase>=m_FrontImageList.count() || phase>=m_FrontNGPosList.count()){
			m_viewItem->setPixmap( QPixmap::fromImage( img ) );
			ui.gvImageView->viewport()->update();
			return;
		}
		img = m_FrontImageList[phase];
		img = addNGPoint(Review::Front, phase, img, m_FrontNGPosList[phase]);
	}else if(side==1){
		if(phase>=m_BackImageList.count() || phase>=m_BackNGPosList.count()){
			m_viewItem->setPixmap( QPixmap::fromImage( img ) );
			ui.gvImageView->viewport()->update();
			return;
		}
		img = m_BackImageList[phase];
		img = addNGPoint(Review::Back, phase, img, m_BackNGPosList[phase]);
	}else{
		m_viewItem->setPixmap( QPixmap() );
		ui.gvImageView->viewport()->update();
		return;
	}

	ui.gvImageView->setImage( img );
	ui.gvImageView->update();

	update();
}

QImage TotalNGMap::addNGPoint(Review::SideType side, int phase, const QImage &image, const QList<QPoint> &pointList) const
{
	if(pointList.isEmpty()==true){
		return image;
	}

	//QList<QList<int> > vautList;
	//for(int y=0; y<splitY(); y++){
	//	vautList << QVector<int>(splitX(), 0).toList();
	//}

	//for(int i=0; i<pointList.count(); i++){
	//	const QPoint p = pointList.at(i);
	//	int y = (int)(p.y() / (qreal)image.height() * splitY());
	//	int x = (int)(p.x() / (qreal)image.width() * splitX());

	//	vautList[y][x] = vautList[y][x] + 1;
	//}

	int nMax = 0;
	//for(int y=0; y<vautList.count(); y++){
	//	for(int x=0; x<vautList[y].count(); x++){
	//		if(nMax<vautList[y][x]){
	//			nMax = vautList[y][x];
	//		}
	//	}
	//}
	_vautMap map;
	if(side==Review::Front){
		map = m_FrontVautMapList[phase];
	}else if(side==Review::Back){
		map = m_BackVautMapList[phase];
	}
	for(int y=0; y<map.count(); y++){
		for(int x=0; x<map.at(y).count(); x++){
			if(nMax<map[y][x]){
				nMax = map[y][x];
			}
		}
	}

	QImage img = image;

	int drawSize = NGDrawSize();
	QColor color = NGDrawColor();

	QPainter painter;
	painter.begin(&img);

	NGDrawShapeType shape = NGDrawShape();

	qreal unitAlpha = 255.0/nMax;
	qreal unitWidth = img.width()/(qreal)splitX();
	qreal unitHeight = img.height()/(qreal)splitY();

	QBrush brush;
	brush.setColor(color);
	brush.setStyle(Qt::BrushStyle::SolidPattern);


	//QPen pen;
	//pen.setColor(color);

	//painter.setPen(pen);
	bool firstRectDrawed = false;
	for(int y=0; y<map.count(); y++){
		for(int x=0; x<map[y].count(); x++){
			if(map[y][x]>0){
				QColor currentColor = color;
				currentColor.setAlpha(map[y][x]*unitAlpha);

				brush.setColor(currentColor);
				painter.setBrush(brush);

				QRect r;
				QPoint topLeft(QPoint(x*unitWidth, y*unitHeight));
				//QPoint center(QPoint(x*unitWidth + unitWidth/2, y*unitHeight + unitHeight/2));

				r.setTopLeft(topLeft);
				r.setSize(QSize(unitWidth, unitHeight));

				painter.drawRect(r);

				if(firstRectDrawed==false){
					qDebug() << r;
					firstRectDrawed = true;
				}
			}
		}
	}

	
	if(m_targetPoint.isNull()==false){
		int x = m_targetPoint.x() * unitWidth + unitWidth/2;
		int y = m_targetPoint.y() * unitHeight + unitHeight/2;
		
		QPen wpen(Qt::GlobalColor::white);
		painter.setPen(wpen);
		painter.drawLine(QPoint(0, y), QPoint(img.width(), y));
		painter.drawLine(QPoint(x, 0), QPoint(x, img.height()));
	}


	//for(int y=0; y<vautList.count(); y++){
	//	for(int x=0; x<vautList[y].count(); x++){
	//		if(vautList[y][x]!=0){
	//			QColor currentColor = color;
	//			currentColor.setAlpha(unitAlpha*vautList[y][x]);

	//			QPen pen(currentColor);
	//			painter.setPen(pen);

	//			QBrush brush;
	//			brush.setColor(currentColor);
	//			painter.setBrush(brush);

	//			QPointF topLeft(QPointF(x*unitWidth, y*unitHeight));
	//			QPointF center(QPointF(x*unitWidth + unitWidth/2, y*unitHeight + unitHeight/2));
	//			QRectF r;
	//			r.setTopLeft(topLeft);
	//			r.setSize(QSize(unitWidth, unitHeight));

	//			switch(NGDrawShape()){
	//			case TotalNGMap::NGDrawShapeType::Fill_Rectangle:
	//				brush.setStyle(Qt::BrushStyle::SolidPattern);
	//				painter.setBrush(brush);
	//				painter.drawRect(r);
	//				break;
	//			case TotalNGMap::NGDrawShapeType::Circle:
	//				brush.setStyle(Qt::BrushStyle::NoBrush);
	//				painter.setBrush(brush);
	//				painter.drawEllipse(center, unitWidth, unitHeight);
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}

	//painter.setPen(pen);
	//painter.setBrush(brush);

	//for(int i=0; i<pointList.count(); i++){
	//	QRect r;
	//	QPoint center = pointList.at(i);
	//	r.setTop(center.y()-drawSize);
	//	r.setBottom(center.y()+drawSize);
	//	r.setLeft(center.x()-drawSize);
	//	r.setRight(center.x()+drawSize);
	//	painter.drawRect(r);
	//}

	painter.end();
	
	return img;
}