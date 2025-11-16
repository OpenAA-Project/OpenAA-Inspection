#include "ShowVRSOperationResource.h"
#include "AlignmentManageForm.h"
#include "InputRectInMultiImageDialog.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "CameraAlignmentSettingForm.h"
#include "VRSControlForm.h"
#include "../LiveCameraCommonPacket.h"
#include "XGUIReviewGlobal.h"

AlignmentManageForm::AlignmentManageForm(ReviewPIBase *RBase, int MoveLength, int ZDistance, bool reverse_x, bool reverse_y, QWidget *parent)
	:QDialog(parent)
	,m_RBase(RBase)
	,m_drawAlignmentList()
	,m_pixEnable(/**/":/QtRes/blueBall.png")
	,m_pixDisable(/**/":/QtRes/redBall.png")
{
	ui.setupUi(this);

#ifndef NDEBUG
	ui.gbDebugGo->setVisible(false);
#endif

	setInitMoveLength(MoveLength);
	setInitZDistance(ZDistance);
	setInitXReverse(reverse_x);
	setInitYReverse(reverse_y);

	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqMInfo );

	if(reqMInfo.Ret==false){
		reject();
		return;
	}

	if(reqMInfo.BackMasterDataInfo.isEmpty()==true){
		ui.lbSideType->setHidden(true);
		ui.cbSideType->setHidden(true);
	}

	CmdReqVRSSetting reqVRSSetting(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqVRSSetting );

	CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqVRSAlignment );

	const VRSAlignment &alingment = reqVRSAlignment.getAlignment(Review::Front);

	//setWholeAlignmentRect(alingment.getAffinSeedFromWhole().getInsAlignment());
	//setEachPageAlignmentRectList(alingment.getAffinSeedRectFromEachPage(Review::AlignmentSide::AlignmentSide_Inspection));

	bool isWhole = (alingment.getAlignmentType()==Review::VRSAlignmentType::VRSAlingmentWholeImage);
	ui.rbWholeAlignment->setChecked(isWhole);
	ui.rbEachPageAlignment->setChecked(!isWhole);

	ui.cbEachAlignmentSettingPage->clear();
	for(int i=0; i<reqMInfo.FrontMasterDataInfo.PageNumb; i++){
		ui.cbEachAlignmentSettingPage->addItem(QString(/**/"Page %1").arg(i));
	}

	if(isWhole==true){
		//setDrawAlignmentList(alingment.getAffinSeedFromWhole().getInsAlignment());
		ui.tabwSetAlignment->setCurrentIndex(0);
	}else{
		//setDrawAlignmentList(alingment.getAffinSeedRectFromEachPage(Review::AlignmentSide_Inspection, 0));
		ui.tabwSetAlignment->setCurrentIndex(1);
	}

	ui.cbEachAlignmentSettingPage->setCurrentIndex(0);

	ui.wWholeAlignmentImageEnable1->setExpandMode(true);
	ui.wWholeAlignmentImageEnable2->setExpandMode(true);
	ui.wWholeAlignmentImageEnable3->setExpandMode(true);
	ui.wWholeAlignmentCameraEnable1->setExpandMode(true);
	ui.wWholeAlignmentCameraEnable2->setExpandMode(true);
	ui.wWholeAlignmentCameraEnable3->setExpandMode(true);
	ui.wEachPageAlignmentImageEnable1->setExpandMode(true);
	ui.wEachPageAlignmentImageEnable2->setExpandMode(true);
	ui.wEachPageAlignmentImageEnable3->setExpandMode(true);
	ui.wEachPageAlignmentCameraEnable1->setExpandMode(true);
	ui.wEachPageAlignmentCameraEnable2->setExpandMode(true);
	ui.wEachPageAlignmentCameraEnable3->setExpandMode(true);
	
	ui.wWholeAlignmentImageEnable1->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wWholeAlignmentImageEnable2->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wWholeAlignmentImageEnable3->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wWholeAlignmentCameraEnable1->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wWholeAlignmentCameraEnable2->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wWholeAlignmentCameraEnable3->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentImageEnable1->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentImageEnable2->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentImageEnable3->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentCameraEnable1->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentCameraEnable2->setAspectRatioMode(Qt::KeepAspectRatio);
	ui.wEachPageAlignmentCameraEnable3->setAspectRatioMode(Qt::KeepAspectRatio);

	connect(ui.cbImageRotation, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRotate(int)));
	connect(ui.cbSideType, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePhaseComboBox()));
	connect(ui.cbPhase, SIGNAL(currentIndexChanged(int)), this, SLOT(updateImage()));
	
	updateClearButtonEnable();
	updateEnableLabel();
	updatePhaseComboBox();
	updateDrawRects();

	updateImage();
};

void AlignmentManageForm::updateRotate(int index)
{
	updateImage();
	update();
}

void AlignmentManageForm::paintEvent(QPaintEvent *event)
{
	QDialog::paintEvent(event);

	if(isUpdateImageRequire()==true){
		setUpdateImageRequire(false);
		updateDrawRects();

		int canvasWidth = ui.wWholeAlignmentImage->width();
		int canvasHeight = ui.wWholeAlignmentImage->height();

		QSize canvasSize = ui.wWholeAlignmentImage->size();

		if(canvasWidth<=2 || canvasHeight<=2){
			return;
		}

		CmdReqWholeImage reqWholeImage(m_RBase->GetLayersBase());

		int rot = rotate();

		QSize imageReqSize = Review::rotateSize(canvasSize, rot);
	
		reqWholeImage.setReqSize(imageReqSize);
		reqWholeImage.setReqPhase(currentPhase());

		m_RBase->TransmitDirectly(&reqWholeImage);

		if(reqWholeImage.getWholePic(currentSide()).isNull()==true){
			return;
		}
		
		QPainter painter;
		qreal zoom;
		QImage drawImage;
		drawImage = reqWholeImage.getWholePic(currentSide());
		zoom = reqWholeImage.getZoomRate(currentSide());

		painter.begin(&drawImage);

		QPen pen;
		QBrush brush;

		pen.setColor(QColor(150, 150, 210));
		brush.setColor(QColor(150, 150, 210));
		brush.setStyle(Qt::BrushStyle::Dense5Pattern);

		painter.setPen(pen);
		painter.setBrush(brush);

		int skipRate = reqWholeImage.getSkipMasterImageRate(currentSide());

		for(int align=0; align<getDrawAlignmentRectList().count(); align++){
			Review::ThreeValue<QRect> rects = getDrawAlignmentRect(align);
			for(int i=0; i<rects.count(); i++){
				if(rects[i].isValid()==true){
			
					painter.setPen(pen);
					painter.setBrush(brush);

					QRect rect = rects[i];
					rect.moveTopLeft( (rect.topLeft() / (skipRate+1)) * zoom * (skipRate+1));
					rect.setSize( (rect.size() / (skipRate+1)) * zoom * (skipRate+1));
					painter.drawRect(rect);

					QColor color(Qt::white);
					QPen whiltePen(color);
					QBrush noBrush;
					noBrush.setStyle(Qt::BrushStyle::NoBrush);

					QString number = QString::number(i+1);
					int numberHeight = painter.fontMetrics().height();
					int numberWidth = painter.fontMetrics().width(number);

					QPoint topCenter( rect.left() + rect.width()/2, rect.top() );
					QPoint numberTopLeft = topCenter - QPoint( numberWidth / 2, numberHeight );
					QRect numberRect(numberTopLeft, QSize(numberWidth, numberHeight));

					painter.setPen(whiltePen);
					painter.setBrush(noBrush);
					painter.drawText(numberRect, Qt::AlignCenter, QString::number(i+1));
				}
			}
		}
		painter.end();

		QTransform trans;
		trans.rotate(rot);

		ui.wWholeAlignmentImage->setImage(drawImage.transformed(trans));
	}
}

void AlignmentManageForm::resizeEvent(QResizeEvent *event)
{
	QDialog::resizeEvent(event);

	updateImage();
}

void AlignmentManageForm::clearWholeAlignment(Review::SideType side, int phase, Review::AlignmentSide align_side, Review::AlignmentNo align_no)
{
	CmdReqVRSAlignment reqAlignment(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlignment );
	
	VRSAlignment align = reqAlignment.getAlignment(side);

	VRSAlignment::ThreePointAlignment points = align.getAffinSeedFromWhole();
	points.setAlignmentPoint(align_side, align_no, QRect());

	CmdSetVRSAlignment setAlignment(GetLayersBase());
	setAlignment.setSide(side);
	setAlignment.setWholeRects(align_side, points.getInsAlignment());
	
	_reviewAlgorithm()->TransmitDirectly( &setAlignment );
}

void AlignmentManageForm::clearEachPageAlignment(Review::SideType side, int phase, int page, Review::AlignmentSide align_side, Review::AlignmentNo align_no)
{
	CmdReqVRSAlignment reqAlignment(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlignment );
	
	VRSAlignment align = reqAlignment.getAlignment(side);

	QList<VRSAlignment::ThreePointAlignment> points = align.getAffinSeedFromEachPage();
	Review::increase(page+1, points);
	points[page].setAlignmentPoint(align_side, align_no, QRect());

	CmdSetVRSAlignment setAlignment(GetLayersBase());
	setAlignment.setSide(side);

	QList<Review::ThreeValue<QRect> > list;
	if(align_side==Review::AlignmentSide::AlignmentSide_Inspection){
		for(int i=0; i<points.count(); i++){
			list << points[i].getInsAlignment();
		}
	}else if(align_side==Review::AlignmentSide::AlignmentSide_VRSMachine){
		for(int i=0; i<points.count(); i++){
			list << points[i].getVRSAlignment();
		}
	}else{
		return;
	}

	setAlignment.setEachPageRects(align_side, list);
	
	_reviewAlgorithm()->TransmitDirectly( &setAlignment );
}

int AlignmentManageForm::rotate(void) const
{
	return Review::toIntFromRotate(static_cast<Review::Rotate>(ui.cbImageRotation->currentIndex()));
}

Review::Rotate AlignmentManageForm::rotateEnum(void) const
{
	int index = ui.cbImageRotation->currentIndex();
	if(index==-1){
		return Review::Rotate::Rotate_0;
	}else{
		return static_cast<Review::Rotate>(index);
	}
}

void AlignmentManageForm::rotateImageData(Review::Rotate rotation, const QList<QImage> &imageList, const QList<QPoint> &outlineOffsetList, const QRect &beforeRect,
		QList<QImage> &rotatedImageList, QList<QPoint> &rotatedOutlineOffsetList, QRect &rotatedBeforeRect, const QList<QSize> &imageSizeList_, QList<QSize> *rotatedImageSizeList)
{
	// 回転角度取得
	const int rot = Review::toIntFromRotate(rotation);
	
	// 回転マトリクス作成
	QTransform transform;
	transform.rotate(rot);
	
	// 回転した矩形形状を作成
	QList<QSize> imageSizeList;
	if(imageSizeList_.isEmpty()==true || imageSizeList_.count() < imageList.count()){
		for(int i=0; i<imageList.count(); i++){
			imageSizeList << imageList[i].size();
		}
		if(rotatedImageSizeList!=NULL){
			rotatedImageSizeList->clear();
			for(int i=0; i<imageSizeList.count(); i++){
				rotatedImageSizeList->append( Review::rotateSize(imageSizeList[i], rot) );
			}
		}
	}else{
		for(int i=0; i<imageSizeList_.count(); i++){
			imageSizeList << imageSizeList_[i];
		}
		if(rotatedImageSizeList!=NULL){
			rotatedImageSizeList->clear();
			for(int i=0; i<imageSizeList_.count(); i++){
				rotatedImageSizeList->append( Review::rotateSize(imageSizeList_[i], rot) );
			}
		}
	}
	QRect rotatedWholeRect = makeWholeRect(imageSizeList, outlineOffsetList, rotation);

	// 回転した画像を作成
	rotatedImageList.clear();
	for(int i=0; i<imageList.count(); i++){
		rotatedImageList << imageList[i].transformed(transform);
	}

	// 回転したアウトラインオフセットを作成
	rotatedOutlineOffsetList.clear();
	for(int i=0; i<imageList.count(); i++){
		QPoint oldOutline = outlineOffsetList[i];
		QPoint newOutline;

		QRect imgRect(oldOutline, imageList[i].size());
		QRect rotatedImgRect = Review::rotateRectRaw(imgRect, rot);
		newOutline = rotatedImgRect.topLeft();
		
		rotatedOutlineOffsetList << newOutline;
	}
	if(rotatedOutlineOffsetList.isEmpty()==false){
		QPoint shiftRotatedOutline = rotatedOutlineOffsetList.first();
		for(int i=1; i<rotatedOutlineOffsetList.count(); i++){
			if(shiftRotatedOutline.x() > rotatedOutlineOffsetList[i].x()){
				shiftRotatedOutline.setX( rotatedOutlineOffsetList[i].x() );
			}
			if(shiftRotatedOutline.y() > rotatedOutlineOffsetList[i].y()){
				shiftRotatedOutline.setY( rotatedOutlineOffsetList[i].y() );
			}
		}
		for(int i=0; i<rotatedOutlineOffsetList.count(); i++){
			rotatedOutlineOffsetList[i] -= shiftRotatedOutline;
		}
	}
	
	// 回転した現在矩形を作成
	rotatedBeforeRect = Review::rotateRectRaw(beforeRect, rot);
	rotatedBeforeRect.moveTopLeft( rotatedBeforeRect.topLeft() - rotatedWholeRect.topLeft());
}

void AlignmentManageForm::rotateImageData(Review::Rotate rotation, const QImage &image, const QPoint &outlineOffset, const QRect &beforeRect,
	QImage &rotatedImage, QPoint rotatedOutlineOffset, QRect &rotatedBeforeRect)
{
	// 回転角度取得
	const int rot = Review::toIntFromRotate(rotation);
	
	// 回転マトリクス作成
	QTransform transform;
	transform.rotate(rot);
	
	// 回転した矩形形状を作成
	QRect rotatedWholeRect = makeWholeRect(image.size(), outlineOffset, rotation);

	// 回転した画像を作成
	rotatedImage = image.transformed(transform);

	// 回転したアウトラインオフセットを作成
	//rotatedOutlineOffset = outlineOffset;
	//QRect imgRect(outlineOffset, image.size());
	//QRect rotatedImgRect = Review::rotateRectRaw(imgRect, rot);
	//rotatedOutlineOffset = rotatedImgRect.topLeft();
	rotatedOutlineOffset = QPoint(0,0);
	
	// 回転した現在矩形を作成
	rotatedBeforeRect = Review::rotateRectRaw(beforeRect, rot);
	rotatedBeforeRect.moveTopLeft( rotatedBeforeRect.topLeft() - rotatedWholeRect.topLeft());
}

QRect AlignmentManageForm::makeWholeRect(const QList<QSize> &sizeList, const QList<QPoint> &offsetList, Review::Rotate rotation)
{
	QRect result;
	for(int i=0; i<sizeList.count() && i<offsetList.count(); i++){
		QRect rect(offsetList[i], sizeList[i]);
		result = result.united( Review::rotateRectRaw(rect, Review::toIntFromRotate(rotation)) );
	}
	return result;
}
QRect AlignmentManageForm::makeWholeRect(const QSize &s, const QPoint &offset, Review::Rotate rotation)
{
	QRect r(offset, s);
	return Review::rotateRectRaw(r, Review::toIntFromRotate(rotation));
}

Review::ThreeValue<QRect> AlignmentManageForm::getWholeAlignmentRectList(){
	CmdReqVRSAlignment reqAlign(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlign );

	return reqAlign.getAlignment(currentSide()).getAffinSeedFromWhole().getInsAlignment();
}

QRect AlignmentManageForm::getWholeAlignmentRect(int index){
	Review::ThreeValue<QRect> rects = getWholeAlignmentRectList();

	return rects.value(static_cast<Review::THREE_INDEX>(index));
}

QList<Review::ThreeValue<QRect> > AlignmentManageForm::getEachPageAlignmentRectList(){
	CmdReqVRSAlignment reqAlign(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlign );

	return reqAlign.getAlignment(currentSide()).getAffinSeedRectFromEachPage(Review::AlignmentSide::AlignmentSide_Inspection);
}

Review::ThreeValue<QRect> AlignmentManageForm::getEachPageAlignmentRect(int page){
	QList<Review::ThreeValue<QRect> > list = getEachPageAlignmentRectList();

	return list[page];
}

void AlignmentManageForm::updateEnableLabel()
{
	CmdReqVRSAlignment reqAlign(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlign );

	const VRSAlignment &align = reqAlign.getAlignment(currentSide());

	QPalette orgPalette = palette();
	QPalette errPalette = orgPalette;
	errPalette.setColor(QPalette::ColorRole::WindowText, QColor(Qt::red));

	switch(currentAlignemntType()){
	case Review::VRSAlignmentType::VRSAlingmentWholeImage:
		if(align.isWholeAffinMatrixEnable()==true){
			ui.laWholeAlignmentEnable->setPalette(orgPalette);
			ui.laWholeAlignmentEnable->setText(LangSolver.GetString(AlignmentManageForm_LS,LID_0)/*"Enable"*/);
		}else{
			ui.laWholeAlignmentEnable->setPalette(errPalette);
			ui.laWholeAlignmentEnable->setText(LangSolver.GetString(AlignmentManageForm_LS,LID_1)/*"Disable"*/);
		}
		break;
	case Review::VRSAlignmentType::VRSAlingmentEachPage:
		int page = currentPage();
		if(page!=-1 && align.isEachPageAffinMatrixEnable(page)==true){
			ui.laWholeAlignmentEnable->setPalette(orgPalette);
			ui.laWholeAlignmentEnable->setText(LangSolver.GetString(AlignmentManageForm_LS,LID_2)/*"Enable"*/);
		}else{
			ui.laWholeAlignmentEnable->setPalette(errPalette);
			ui.laWholeAlignmentEnable->setText(LangSolver.GetString(AlignmentManageForm_LS,LID_3)/*"Disable"*/);
		}
	}
}

void AlignmentManageForm::updateClearButtonEnable()
{
	CmdReqVRSAlignment reqAlign(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlign );

	Review::VRSAlignmentType type = currentAlignemntType();
	Review::SideType side = currentSide();

	if(type==Review::VRSAlignmentType::VRSAlingmentWholeImage){

		bool wi[3],wc[3];
		wi[0] = wi[1] = wi[2] = wc[0] = wc[1] = wc[2] = false;
		VRSAlignment::ThreePointAlignment align = reqAlign.getAlignment(side).getAffinSeedFromWhole();

		const Review::ThreeValue<QRect> insRects = align.getInsAlignment();

		if(insRects.first().isValid()==true){
			wi[0] = true;
		}
		if(insRects.second().isValid()==true){
			wi[1] = true;
		}
		if(insRects.third().isValid()==true){
			wi[2] = true;
		}

		const Review::ThreeValue<QRect> vrsRects = align.getVRSAlignment();

		if(vrsRects.first().isValid()==true){
			wc[0] = true;
		}
		if(vrsRects.second().isValid()==true){
			wc[1] = true;
		}
		if(vrsRects.third().isValid()==true){
			wc[2] = true;
		}

		ui.pbClearWholeAlignment1->setEnabled(wi[0]==true || wc[0]==true);
		ui.pbClearWholeAlignmentOfImage1->setEnabled(wi[0]);
		ui.pbClearWholeAlignmentOfCamera1->setEnabled(wc[0]);
		ui.wWholeAlignmentImageEnable1->setImage(enablePixmap(wi[0]));
		ui.wWholeAlignmentCameraEnable1->setImage(enablePixmap(wc[0]));
		
		ui.pbClearWholeAlignment2->setEnabled((wi[1]==true || wc[1]==true));
		ui.pbClearWholeAlignmentOfImage2->setEnabled(wi[1]);
		ui.pbClearWholeAlignmentOfCamera2->setEnabled(wc[1]);
		ui.wWholeAlignmentImageEnable2->setImage(enablePixmap(wi[1]));
		ui.wWholeAlignmentCameraEnable2->setImage(enablePixmap(wc[1]));
		
		ui.pbClearWholeAlignment3->setEnabled((wi[2]==true || wc[2]==true));
		ui.pbClearWholeAlignmentOfImage3->setEnabled(wi[2]);
		ui.pbClearWholeAlignmentOfCamera3->setEnabled(wc[2]);
		ui.wWholeAlignmentImageEnable3->setImage(enablePixmap(wi[2]));
		ui.wWholeAlignmentCameraEnable3->setImage(enablePixmap(wc[2]));

		ui.pbClearWholeAlignmentAll->setEnabled(wi[0]==true || wi[1]==true || wi[2]==true || wc[0]==true || wc[1]==true || wc[2]==true);
	}else{
		int page = currentPage();

		bool wi[3],wc[3];
		wi[0] = wi[1] = wi[2] = wc[0] = wc[1] = wc[2] = false;

		const VRSAlignment::ThreePointAlignment align = reqAlign.getAlignment(side).getAffinSeedFromEachPage(page);
		
		const Review::ThreeValue<QRect> insRects = align.getInsAlignment();
		
		if(insRects.first().isValid()==true){
			wi[0] = true;
		}
		if(insRects.second().isValid()==true){
			wi[1] = true;
		}
		if(insRects.third().isValid()==true){
			wi[2] = true;
		}

		const Review::ThreeValue<QRect> vrsRects = align.getVRSAlignment();

		if(vrsRects.first().isValid()==true){
			wc[0] = true;
		}
		if(vrsRects.second().isValid()==true){
			wc[1] = true;
		}
		if(vrsRects.third().isValid()==true){
			wc[2] = true;
		}

		ui.pbClearEachPageAlignment1->setEnabled((wi[0]==true || wc[0]==true));
		ui.pbClearEachPageAlignmentOfImage1->setEnabled(wi[0]);
		ui.pbClearEachPageAlignmentOfCamera1->setEnabled(wc[0]);
		ui.wEachPageAlignmentImageEnable1->setImage(enablePixmap(wi[0]));
		ui.wEachPageAlignmentCameraEnable1->setImage(enablePixmap(wc[0]));
		
		ui.pbClearEachPageAlignment2->setEnabled((wi[1]==true || wc[1]==true));
		ui.pbClearEachPageAlignmentOfImage2->setEnabled(wi[1]);
		ui.pbClearEachPageAlignmentOfCamera2->setEnabled(wc[1]);
		ui.wEachPageAlignmentImageEnable2->setImage(enablePixmap(wi[1]));
		ui.wEachPageAlignmentCameraEnable2->setImage(enablePixmap(wc[1]));
		
		ui.pbClearEachPageAlignment3->setEnabled((wi[2]==true || wc[2]==true));
		ui.pbClearEachPageAlignmentOfImage3->setEnabled(wi[2]);
		ui.pbClearEachPageAlignmentOfCamera3->setEnabled(wc[2]);
		ui.wEachPageAlignmentImageEnable3->setImage(enablePixmap(wi[2]));
		ui.wEachPageAlignmentCameraEnable3->setImage(enablePixmap(wc[2]));

		ui.pbClearEachPageAlignmentAll->setEnabled(wi[0]==true || wi[1]==true || wi[2]==true || wc[0]==true || wc[1]==true || wc[2]==true);
	}
}

void AlignmentManageForm::updatePhaseComboBox()
{
	ui.cbPhase->clear();
	Review::SideType side = currentSide();
	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqMInfo );
	if(reqMInfo.Ret==false){
		return;
	}
	int phaseNumb = reqMInfo.getInfo(side).PhaseNumb;
	for(int phase=0; phase<phaseNumb; phase++){
		ui.cbPhase->addItem(QString::number(phase));
	}
	if(ui.cbPhase->count()!=0){
		ui.cbPhase->setCurrentIndex(0);
	}
	bool hidden = (ui.cbPhase->count()<=1);
	ui.lbPhase->setHidden(hidden);
	ui.cbPhase->setHidden(hidden);
}

void AlignmentManageForm::updateDrawRects()
{
	CmdReqVRSAlignment reqAlign(GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly( &reqAlign );

	Review::SideType side = currentSide();
	int phase = currentPhase();

	Review::ThreeValue<QRect> rects;

	if(currentAlignemntType()==Review::VRSAlignmentType::VRSAlingmentWholeImage){
		rects = reqAlign.getAlignment(side).getAffinSeedFromWhole().getInsAlignment();
	}else{
		int page = currentPage();
		VRSAlignment align = reqAlign.getAlignment(side);
		if(Review::isIndexEnable(page, align.getAffinSeedFromEachPage())==true){
			rects = align.getAffinSeedFromEachPage().at(page).getInsAlignment();
		}else{
			Q_ASSERT(/**/"AlignmentManageForm::updateDrawRects() has error!");
			return;
		}
	}

	setDrawAlignmentList(rects);
}

LayersBase *AlignmentManageForm::GetLayersBase(){
	return m_RBase->GetLayersBase();
}

void AlignmentManageForm::on_pbSetWholeAlignmentPoint1_clicked()
{
	setWholeAlignmentData(0, getWholeAlignmentRect(0));
	//QRect rect = getRect(m_wholeAlignmentList[0]);
	//if(rect.isValid()==true){
	//	m_wholeAlignmentList[0] = rect;

	//	CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
	//	_reviewAlgorithm()->TransmitDirectly(&reqVRSAlignment);
	//	//Review::ThreeValue<QRect> oldRects = reqVRSAlignment.InspectionWholeRects;
	//	Review::ThreeValue<QRect> oldRects = reqVRSAlignment.getAlignment(currentSide()).getAffinSeedFromWhole().getInsAlignment();

	//	CmdSetVRSAlignment setVRSAlignment(GetLayersBase());
	//	Review::ThreeValue<QRect> newRects;

	//	newRects.setFirst(rect);
	//	newRects.setSecond(oldRects.second());
	//	newRects.setThird(oldRects.third());

	//	setVRSAlignment.setInspectionWholeRects(newRects);

	//	_reviewAlgorithm()->TransmitDirectly(&setVRSAlignment);

	//	setDrawAlignmentList(newRects);

	//	updateImage();
	//}
}

void AlignmentManageForm::on_pbSetWholeAlignmentPoint2_clicked()
{
	setWholeAlignmentData(1, getWholeAlignmentRect(1));
	//QRect rect = getRect(m_wholeAlignmentList[1]);
	//if(rect.isValid()==true){
	//	m_wholeAlignmentList[1] = rect;

	//	CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
	//	_reviewAlgorithm()->TransmitDirectly(&reqVRSAlignment);
	//	Review::ThreeValue<QRect> oldRects = reqVRSAlignment.InspectionWholeRects;

	//	CmdSetVRSAlignment setVRSAlignment(GetLayersBase());
	//	Review::ThreeValue<QRect> newRects;

	//	newRects.setFirst(oldRects.first());
	//	newRects.setSecond(rect);
	//	newRects.setThird(oldRects.third());

	//	setVRSAlignment.setInspectionWholeRects(newRects);

	//	_reviewAlgorithm()->TransmitDirectly(&setVRSAlignment);
	//	
	//	setDrawAlignmentList(newRects);

	//	updateImage();
	//}
}

void AlignmentManageForm::on_pbSetWholeAlignmentPoint3_clicked()
{
	setWholeAlignmentData(2, getWholeAlignmentRect(2));
	//QRect rect = getRect(m_wholeAlignmentList[2]);
	//if(rect.isValid()==true){
	//	m_wholeAlignmentList[2] = rect;

	//	CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
	//	_reviewAlgorithm()->TransmitDirectly(&reqVRSAlignment);
	//	Review::ThreeValue<QRect> oldRects = reqVRSAlignment.InspectionWholeRects;

	//	CmdSetVRSAlignment setVRSAlignment(GetLayersBase());
	//	Review::ThreeValue<QRect> newRects;

	//	newRects.setFirst(oldRects.first());
	//	newRects.setSecond(oldRects.second());
	//	newRects.setThird(rect);

	//	setVRSAlignment.setInspectionWholeRects(newRects);

	//	_reviewAlgorithm()->TransmitDirectly(&setVRSAlignment);
	//	
	//	setDrawAlignmentList(newRects);

	//	updateImage();
	//}
}

void AlignmentManageForm::changeData()
{

}

void AlignmentManageForm::getWholeAlignmentRect(QRect &first, QRect &second, QRect &third)
{
	Review::ThreeValue<QRect> list = getWholeAlignmentRectList();
	first = list[0];
	second = list[1];
	third = list[2];

	//first = m_wholeAlignmentList[0];
	//second = m_wholeAlignmentList[1];
	//third = m_wholeAlignmentList[2];
}
//
//void AlignmentManageForm::setAlignmentWhole(const QRect &first, const QRect &second, const QRect &third)
//{
//	m_wholeAlignmentList[0] = first;
//	m_wholeAlignmentList[1] = second;
//	m_wholeAlignmentList[2] = third;
//
//	updateImage();
//	updateEnableLabel();
//}

void AlignmentManageForm::on_pbSetCameraWholeAlignment1_clicked()
{
	QRect oldRect = getWholeAlignmentRect(0);
	QRectF rect = getCameraRect(oldRect);
	if(rect.isValid()==true){
		CmdSetCameraAlignment setCameraAlignment(currentSide(), GetLayersBase());

		setCameraAlignment.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentWholeImage);
		setCameraAlignment.setNumber(0);
		setCameraAlignment.setRect(rect);

		_reviewAlgorithm()->TransmitDirectly( &setCameraAlignment );

		updateImage();
		updateClearButtonEnable();
		updateEnableLabel();
	}
}

void AlignmentManageForm::on_pbSetCameraWholeAlignment2_clicked()
{
	QRect oldRect = getWholeAlignmentRect(1);
	QRectF rect = getCameraRect(oldRect);
	if(rect.isValid()==true){
		CmdSetCameraAlignment setCameraAlignment(currentSide(), GetLayersBase());
		
		setCameraAlignment.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentWholeImage);
		setCameraAlignment.setNumber(1);
		setCameraAlignment.setRect(rect);

		_reviewAlgorithm()->TransmitDirectly( &setCameraAlignment );

		updateImage();
		updateClearButtonEnable();
		updateEnableLabel();
	}
}

void AlignmentManageForm::on_pbSetCameraWholeAlignment3_clicked()
{
	QRect oldRect = getWholeAlignmentRect(2);
	QRectF rect = getCameraRect(oldRect);
	if(rect.isValid()==true){
		CmdSetCameraAlignment setCameraAlignment(currentSide(), GetLayersBase());
		
		setCameraAlignment.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentWholeImage);
		setCameraAlignment.setNumber(2);
		setCameraAlignment.setRect(rect);

		_reviewAlgorithm()->TransmitDirectly( &setCameraAlignment );

		updateImage();
		updateClearButtonEnable();
		updateEnableLabel();
	}
}

void AlignmentManageForm::on_pbClearWholeAlignment1_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfImage1_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage();
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfCamera1_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignment2_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfImage2_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfCamera2_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignment3_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfImage3_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentOfCamera3_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearWholeAlignmentAll_clicked()
{
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);
	clearWholeAlignment(currentSide(), currentPhase() ,Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
	
void AlignmentManageForm::on_pbClearEachPageAlignment1_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfImage1_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfCamera1_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignment2_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfImage2_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfCamera2_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignment3_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfImage3_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentOfCamera3_clicked()
{
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);
	updateImage();

	updateClearButtonEnable();
	updateEnableLabel();
	updateImage(true);
}
void AlignmentManageForm::on_pbClearEachPageAlignmentAll_clicked()
{

	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_First);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_First);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Second);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Second);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_Inspection, Review::AlignmentNo::Alignment_Third);
	clearEachPageAlignment(currentSide(), currentPhase() , currentPage(), Review::AlignmentSide::AlignmentSide_VRSMachine, Review::AlignmentNo::Alignment_Third);
	
	updateClearButtonEnable();
	updateEnableLabel();
	updateDrawRects();
	updateImage(true);
}

void AlignmentManageForm::on_cbEachAlignmentSettingPage_currentIndexChanged(int index)
{
	if(index==-1)return;

	QList<Review::ThreeValue<QRect> > list;

	if(ui.rbWholeAlignment->isChecked()==true){
		list << getWholeAlignmentRectList();
	}else{
		list << getEachPageAlignmentRect(index);
	}

	//for(int i=0; i<list.count(); i++){
	//	qDebug() << i;
	//	qDebug() << 1 << ":" << list[i].first();
	//	qDebug() << 2 << ":" << list[i].second();
	//	qDebug() << 3 << ":" << list[i].third();
	//}

	setDrawAlignmentList(list);

	updateImage();
	updateEnableLabel();
	updateClearButtonEnable();
}

void AlignmentManageForm::on_cbSideType_currentIndexChanged(int index)
{
	if(Review::isBetween(0, index, 1)==false)return;

	CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());

	_reviewAlgorithm()->TransmitDirectly( &reqVRSAlignment );

	//setWholeAlignmentRect(reqVRSAlignment.getAlignment(side).getAffinSeedRectFromWhole(Review::AlignmentSide::AlignmentSide_Inspection));
	//setEachPageAlignmentRectList(reqVRSAlignment.getAlignment(side).getAffinSeedRectFromEachPage(Review::AlignmentSide::AlignmentSide_Inspection));
	
	if(reqVRSAlignment.getAlignment(currentSide()).getAlignmentType()==Review::VRSAlignmentType::VRSAlingmentWholeImage){
		setDrawAlignmentList(getWholeAlignmentRectList());
		ui.rbWholeAlignment->setChecked(true);
		ui.rbEachPageAlignment->setChecked(false);
	}else{
		int page = currentPage();
		setDrawAlignmentList(getEachPageAlignmentRect(page));
		ui.rbWholeAlignment->setChecked(false);
		ui.rbEachPageAlignment->setChecked(true);
	}

	updateImage();
	updateEnableLabel();
	updateClearButtonEnable();
}

void AlignmentManageForm::on_rbWholeAlignment_toggled(bool checked)
{
	if(ui.rbEachPageAlignment->isChecked()!=!checked){
		ui.rbEachPageAlignment->setChecked(!checked);
	}
	ui.tabwSetAlignment->setCurrentIndex(0);

	if(checked==true){
		CmdSetVRSAlignment setAlign(GetLayersBase());
		setAlign.setSide(currentSide());
		setAlign.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentWholeImage);
		_reviewAlgorithm()->TransmitDirectly( &setAlign );

		setDrawAlignmentList(getWholeAlignmentRectList());
	}

	updateImage();
	updateClearButtonEnable();
	updateEnableLabel();
}

void AlignmentManageForm::on_rbEachPageAlignment_toggled(bool checked)
{
	if(ui.rbWholeAlignment->isChecked()!=!checked){
		ui.rbWholeAlignment->setChecked(!checked);
	}
	ui.tabwSetAlignment->setCurrentIndex(1);
	
	if(checked==true){
		CmdSetVRSAlignment setAlign(GetLayersBase());
		setAlign.setSide(currentSide());
		setAlign.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentEachPage);
		_reviewAlgorithm()->TransmitDirectly( &setAlign );
	}
	
	int page = currentPage();
	if(page!=-1){
		setDrawAlignmentList(getEachPageAlignmentRect(page));
	}

	updateImage();
	updateClearButtonEnable();
	updateEnableLabel();
}

void AlignmentManageForm::on_pbSetEachPageAlignmentPoint1_clicked()
{
	int page = currentPage();
	setEachPageAlignmentData(currentSide(), page, 0, getEachPageAlignmentRect(page).first());
	updateClearButtonEnable();
}

void AlignmentManageForm::on_pbSetEachPageAlignmentPoint2_clicked()
{
	int page = currentPage();
	setEachPageAlignmentData(currentSide(), page, 1, getEachPageAlignmentRect(page).second());
}

void AlignmentManageForm::on_pbSetEachPageAlignmentPoint3_clicked()
{
	int page = currentPage();
	setEachPageAlignmentData(currentSide(), page, 2, getEachPageAlignmentRect(page).third());
}

void AlignmentManageForm::on_pbSetCameraEachPageAlignment1_clicked()
{
	int page = currentPage();
	setEachPageCameraAlignmentData(currentSide(), page, 0, getEachPageAlignmentRect(page).first());
}

void AlignmentManageForm::on_pbSetCameraEachPageAlignment2_clicked()
{
	int page = currentPage();
	setEachPageCameraAlignmentData(currentSide(), page, 1, getEachPageAlignmentRect(page).second());
}

void AlignmentManageForm::on_pbSetCameraEachPageAlignment3_clicked()
{
	int page = currentPage();
	setEachPageCameraAlignmentData(currentSide(), page, 2, getEachPageAlignmentRect(page).third());
}

void AlignmentManageForm::on_pbDebugGo_clicked()
{
	bool ok;
	int x,y;
	x = ui.leGoX->text().toInt(&ok);
	if(ok==false)return;
	y = ui.leGoY->text().toInt(&ok);
	if(ok==false)return;

	CmdMoveVRSWithAlignment moveCmd(GetLayersBase());

	moveCmd.side = currentSide();

	moveCmd.x = x;
	moveCmd.y = y;

	if(ui.rbWholeAlignment->isChecked()==true){
		moveCmd.type = Review::VRSAlignmentType::VRSAlingmentWholeImage;
		moveCmd.phase = 0;
		moveCmd.page = 0;
	}else{
		moveCmd.type = Review::VRSAlignmentType::VRSAlingmentEachPage;
		moveCmd.phase = 0;
		moveCmd.page = currentPage();
	}

	_reviewAlgorithm()->TransmitDirectly( &moveCmd );
}

QRect AlignmentManageForm::getRect(const QRect &beforeRect)
{
	CmdReqMasterImageList reqMImgList(m_RBase->GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly(&reqMImgList);

	if(reqMImgList.FrontImageList==NULL || reqMImgList.FrontImageList->getImageList().count()==0){
		QMessageBox::warning(this
							, LangSolver.GetString(AlignmentManageForm_LS,LID_5)/*"Master Image Load Error"*/
							, LangSolver.GetString(AlignmentManageForm_LS,LID_6)/*"Master Image would not be loaded."*/);
		return QRect();
	}

	int rot = rotate();
	Review::SideType side = currentSide();
	int phase = currentPhase();

	InputRectInMultiImageDialog dialog;
	QList<QImage> imageList = reqMImgList.getImageList(side, phase);
	QList<QPoint> outlines = reqMImgList.getOutlineOffsetList(side, phase);

	QList<QSize> sizeList;
	for(int i=0; i<imageList.count(); i++){
		sizeList << imageList[i].size();
	}
	for(int i=0; i<outlines.count(); i++){
		outlines[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	}
	QRect rotatedWholeRect = makeWholeRect(sizeList, outlines, rotateEnum());

	QRect scaledBeforeRect = beforeRect;
	scaledBeforeRect.moveTopLeft( scaledBeforeRect.topLeft() / reqMImgList.MasterImageNormalizeZoomRate );
	scaledBeforeRect.setSize( scaledBeforeRect.size() / reqMImgList.MasterImageNormalizeZoomRate );

	QList<QImage> rotatedImageList;
	QList<QPoint> rotatedOutlines;
	QRect rotatedBeforeRect;

	rotateImageData(rotateEnum(), imageList, outlines, scaledBeforeRect,
		rotatedImageList, rotatedOutlines, rotatedBeforeRect);

	dialog.setImageList(rotatedImageList, rotatedOutlines);
	dialog.setZoomStepLimit(100);
	dialog.setResultRect(rotatedBeforeRect);

	dialog.setFirstExpand(true);

	QRect ret, rect;
	if(dialog.exec()==QDialog::Accepted){
		rect = dialog.resultRect();
		if(rect.isValid()){
			rect.moveTopLeft( rect.topLeft() + rotatedWholeRect.topLeft() );
			rect.setSize( rect.size() * reqMImgList.MasterImageNormalizeZoomRate );
			rect.moveTopLeft( rect.topLeft() * reqMImgList.MasterImageNormalizeZoomRate );
			ret = Review::rotateRectRaw(rect, -rot);
		}
	}
	
	return ret;
}

QRectF AlignmentManageForm::getCameraRect(const QRect &imageAlignment)
{
	CmdReqMasterImageList reqMImgList(m_RBase->GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly(&reqMImgList);

	if(reqMImgList.FrontImageList==NULL || reqMImgList.FrontImageList->getImageList().count()==0){
		QMessageBox::warning(this
							, LangSolver.GetString(AlignmentManageForm_LS,LID_7)/*"Master Image Load Error"*/
							, LangSolver.GetString(AlignmentManageForm_LS,LID_8)/*"Master Image would not be loaded."*/);
		return QRect();
	}

	GUIFormBase *CameraGUI = NULL;
	do{
		CameraGUI = GetReviewGUIForm(ReviewGUI::Name::LiveCameraAlgoNTSC);
		if(CameraGUI!=NULL)break;
		CameraGUI = GetReviewGUIForm(ReviewGUI::Name::LiveCameraDFK31AF03);
		if(CameraGUI!=NULL)break;
		//CameraGUI = GetReviewGUIForm(ReviewGUI::Name::LiveCameraArtCam_035IMX_WOM);
		CameraGUI = GetReviewGUIForm(ReviewGUI::Name::LiveCameraMightexUSB3);
		if(CameraGUI!=NULL)break;
		CameraGUI = GetReviewGUIForm(ReviewGUI::Name::LiveCameraMightexUSB2);
		if(CameraGUI!=NULL)break;
	}while(false);

	if(CameraGUI==NULL){
		return QRectF();
	}
	
	int rot = rotate();
	Review::SideType side = currentSide();
	int phase = currentPhase();

	InputRectInMultiImageDialog dialog;
	QList<QImage> imageList = reqMImgList.getImageList(side, phase);
	QList<QPoint> outlines = reqMImgList.getOutlineOffsetList(side, phase);

	QList<QSize> sizeList;
	for(int i=0; i<imageList.count(); i++){
		sizeList << imageList[i].size();
	}
	for(int i=0; i<outlines.count(); i++){
		outlines[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	}
	QRect rotatedWholeRect = makeWholeRect(sizeList, outlines, rotateEnum());

	QRect scaledBeforeRect = imageAlignment;
	scaledBeforeRect.moveTopLeft( scaledBeforeRect.topLeft() / reqMImgList.MasterImageNormalizeZoomRate );
	scaledBeforeRect.setSize( scaledBeforeRect.size() / reqMImgList.MasterImageNormalizeZoomRate );

	QList<QImage> rotatedImageList;
	QList<QPoint> rotatedOutlines;
	QRect rotatedBeforeRect;

	rotateImageData(rotateEnum(), imageList, outlines, scaledBeforeRect,
		rotatedImageList, rotatedOutlines, rotatedBeforeRect);

	/*
	QList<QImage> imageList;
	QList<QPoint> outlines;
	
	if(currentSide()==Review::Front){
		imageList = reqMImgList.FrontImageList->getImageList().first();
		outlines = reqMImgList.FrontOutlineList.first();
	}else{
		imageList = reqMImgList.BackImageList->getImageList().first();
		outlines = reqMImgList.BackOutlineList.first();
	}

	int rot = rotate();

	QTransform transform;
	transform.rotate(rot);
	
	QRect wholeRect;
	for(int i=0; i<imageList.count(); i++){
		QRect currentRect = QRect(outlines[i], imageList[i].size());
		wholeRect = wholeRect.united(currentRect);
	}

	QList<QImage> rotatedImageList;
	for(int i=0; i<imageList.count(); i++){
		rotatedImageList << imageList[i].transformed(transform);
	}

	QList<QPoint> rotatedOutlines;
	QRect rrect = Review::rotateRectRaw(wholeRect, rot);
	for(int i=0; i<imageList.count(); i++){
		QPoint oldOutline = outlines[i];
		QPoint newOutline;

		QRect imgRect(oldOutline, imageList[i].size());
		QRect rotatedImgRect = Review::rotateRectRaw(imgRect, rot);
		newOutline = rotatedImgRect.topLeft() - rrect.topLeft();
		
		rotatedOutlines << newOutline;
	}
	
	QRect rotatedBeforeRect = Review::rotateRectRaw(imageAlignment, rot);

	rotatedBeforeRect.moveTopLeft( rotatedBeforeRect.topLeft() - rrect.topLeft() );

	for(int i=0; i<rotatedOutlines.count(); i++){
		rotatedOutlines[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	}
	
	QRect befRectScaled = rotatedBeforeRect;
	befRectScaled.moveTopLeft( befRectScaled.topLeft() / reqMImgList.MasterImageNormalizeZoomRate );
	befRectScaled.setSize( befRectScaled.size() / reqMImgList.MasterImageNormalizeZoomRate );*/
	
	CameraAlignmentSettingForm form(_reviewAlgorithm(), initMoveLength(), initZDistance(), initXReverse(), initYReverse(), this);
	
	GUICmdSetCameraWindow setCameraWindow(GetLayersBase());
	setCameraWindow.label = form.cameraLabel();

	CameraGUI->TransmitDirectly( &setCameraWindow );

	form.setImageData(rotatedImageList, rotatedOutlines, rotatedBeforeRect, true);

	QRectF ret;
	if(form.exec()==QDialog::Accepted){
		ret = form.resultNormalizationRect();
	}else{
		ret = QRectF();
	}

	GUICmdResetCameraWindow resetCameraCmd(GetLayersBase());
	CameraGUI->TransmitDirectly( &resetCameraCmd );

	return ret;
}

QRect AlignmentManageForm::getRect(int page, const QRect &beforeRect)
{
	if(page<0 || currentPhase()<0)return QRect();

	CmdReqMasterImageList reqMImgList(m_RBase->GetLayersBase());
	_reviewAlgorithm()->TransmitDirectly(&reqMImgList);

	if(reqMImgList.FrontImageList==NULL || reqMImgList.FrontImageList->getImageList().count()==0){
		QMessageBox::warning(this
							, LangSolver.GetString(AlignmentManageForm_LS,LID_9)/*"Master Image Load Error"*/
							, LangSolver.GetString(AlignmentManageForm_LS,LID_10)/*"Master Image would not be loaded."*/);
		return QRect();
	}

	int rot = rotate();
	Review::SideType side = currentSide();
	int phase = currentPhase();

	QList<QImage> imageList = reqMImgList.getImageList(side, phase);
	QList<QPoint> outlineList = reqMImgList.getOutlineOffsetList(side, phase);

	if(Review::isIndexEnable(page, imageList)==false){
		QMessageBox::warning(this
							, LangSolver.GetString(AlignmentManageForm_LS,LID_11)/*"Master Image Load Error"*/
							, LangSolver.GetString(AlignmentManageForm_LS,LID_12)/*"Page images is less number than master data has."*/);
		return QRect();
	}
	if(Review::isIndexEnable(page, outlineList)==false){
		QMessageBox::warning(this
							, LangSolver.GetString(AlignmentManageForm_LS,LID_13)/*"Master OutlineOffset Load Error"*/
							, LangSolver.GetString(AlignmentManageForm_LS,LID_14)/*"Master data don't have outline offset data."*/);
		return QRect();
	}

	QList<QSize> sizeList;
	for(int i=0; i<imageList.count(); i++){
		sizeList << imageList[i].size();
	}

	for(int i=0; i<imageList.count(); i++){
		if(i!=page){
			imageList[i] = QImage();
		}
	}
	
	for(int i=0; i<outlineList.count(); i++){
		outlineList[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	}
	QRect rotatedWholeRect = makeWholeRect(sizeList, outlineList, rotateEnum());

	QRect scaledBeforeRect = beforeRect;
	scaledBeforeRect.moveTopLeft( scaledBeforeRect.topLeft() / reqMImgList.MasterImageNormalizeZoomRate );
	scaledBeforeRect.setSize( scaledBeforeRect.size() / reqMImgList.MasterImageNormalizeZoomRate );

	QList<QImage> rotatedImageList;
	QList<QPoint> rotatedoutlineList;
	QRect rotatedBeforeRect;
	
	rotateImageData(rotateEnum(), imageList, outlineList, scaledBeforeRect,
		rotatedImageList, rotatedoutlineList, rotatedBeforeRect, sizeList);

	InputRectInMultiImageDialog dialog;
	dialog.setImageList(rotatedImageList, rotatedoutlineList);
	dialog.setZoomStepLimit(100);
	dialog.setResultRect(rotatedBeforeRect);

	dialog.setFirstExpand(true);

	QRect ret, rect;
	if(dialog.exec()==QDialog::Accepted){
		rect = dialog.resultRect();
		if(rect.isValid()){
			rect.moveTopLeft( rect.topLeft() + rotatedWholeRect.topLeft() );
			rect.setSize( rect.size() * reqMImgList.MasterImageNormalizeZoomRate );
			rect.moveTopLeft( rect.topLeft() * reqMImgList.MasterImageNormalizeZoomRate );
			ret = Review::rotateRectRaw(rect, -rot);
		}
	}
	
	return ret;

	//QImage currentImage = imageList.at(page);
	//QPoint currentOutline = outlines.at(page);

	//// 回転角度
	//int rot = rotate();

	//// 回転マトリクス
	//QTransform transform;
	//transform.rotate(rot);
	//
	//// 全体画像サイズ
	//QRect wholeRect;
	//for(int i=0; i<outlineList.count(); i++){
	//	outlines[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	//}
	//QList<QSize> sizeList;
	//for(int i=0; i<imageList.count(); i++){
	//	sizeList << imageList[i].size();
	//}

	//QRect rotatedWholeRect = makeWholeRect(sizeList, outlineList, rotateEnum());

	//// 全体画像の回転後のサイズ
	//QRect rrect = Review::rotateRectRaw(wholeRect, rot);

	//// 対象ページの回転した画像作成
	//QList<QImage> rotatedImageList;
	//rotatedImageList << imageList[page].transformed(transform);

	//// 対象ページの画像のアウトラインオフセット
	//QPoint oldOutline = outlines[page];
	//QPoint newOutline;

	//// 回転した画像矩形を表示した場合のアウトラインオフセットの取得
	//QRect imgRect(oldOutline, imageList[page].size());
	//QRect rotatedImgRect = Review::rotateRectRaw(imgRect, rot);
	//newOutline = rotatedImgRect.topLeft() - rrect.topLeft();
	//QList<QPoint> rotatedOutlineList = Review::toList(newOutline);

	//// 間引き量による回転後アライメント矩形の調整
	//for(int i=0; i<rotatedOutlines.count(); i++){
	//	rotatedOutlineList[i] /= reqMImgList.MasterImageNormalizeZoomRate;
	//}

	//// 現在のアライメント矩形の回転
	//QRect rotatedBeforeRect = Review::rotateRectRaw(beforeRect, rot);
	//rotatedBeforeRect.moveTopLeft( rotatedBeforeRect.topLeft() - rrect.topLeft() );
	//
	//// 現在のアライメントを間引き量でスケーリング
	//QRect befRectScaled = rotatedBeforeRect;
	//befRectScaled.moveTopLeft( befRectScaled.topLeft() / reqMImgList.MasterImageNormalizeZoomRate );
	//befRectScaled.setSize( befRectScaled.size() / reqMImgList.MasterImageNormalizeZoomRate );

	//// イメージとアウトラインオフセットを設定
	//dialog.setImageList(rotatedImageList, rotatedOutlineList);
	//dialog.setZoomStepLimit(100);
	//dialog.setResultRect(befRectScaled);

	//// 初期全体表示を設定
	//dialog.setFirstExpand(true);

	//// 実行
	//QRect ret, rect;
	//if(dialog.exec()==QDialog::Accepted){
	//	rect = dialog.resultRect();
	//	if(rect.isValid()){
	//		rect.moveTopLeft( rect.topLeft() * reqMImgList.MasterImageNormalizeZoomRate );
	//		rect.setSize( rect.size() * reqMImgList.MasterImageNormalizeZoomRate );
	//		rect.moveTopLeft( rect.topLeft() + rrect.topLeft() );
	//		ret = Review::rotateRectRaw(rect, -rot);
	//	}
	//}
	//
	//return ret;
}

void AlignmentManageForm::setWholeAlignmentData(int index, const QRect &beforeRect)
{
	if(Review::isBetween(0, index, 2)==false){
		return;
	}
	QRect rect = getRect(beforeRect);
	if(rect.isValid()==true){
		CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
		_reviewAlgorithm()->TransmitDirectly(&reqVRSAlignment);
		//Review::ThreeValue<QRect> oldRects = reqVRSAlignment.InspectionWholeRects;
		Review::ThreeValue<QRect> oldRects = reqVRSAlignment.getAlignment(currentSide()).getAffinSeedFromWhole().getInsAlignment();

		CmdSetVRSAlignment setVRSAlignment(GetLayersBase());
		setVRSAlignment.setSide(currentSide());
		Review::ThreeValue<QRect> newRects = oldRects;

		setVRSAlignment.setSide(currentSide());

		if(index==0){
			newRects.setFirst(rect);
		}else if(index==1){
			newRects.setSecond(rect);
		}else if(index==2){
			newRects.setThird(rect);
		}

		setVRSAlignment.setInspectionWholeRects(newRects);

		_reviewAlgorithm()->TransmitDirectly(&setVRSAlignment);

		setDrawAlignmentList(newRects);

		updateImage();
		updateClearButtonEnable();
		updateEnableLabel();
	}
}

void AlignmentManageForm::setEachPageAlignmentData(Review::SideType side, int page, int index, const QRect &beforeRect)
{
	QRect rect = getRect(page, beforeRect);
	if(rect.isValid()==true){
		Review::ThreeValue<QRect> rects = getEachPageAlignmentRect(page);

		CmdReqVRSAlignment reqVRSAlignment(GetLayersBase());
		_reviewAlgorithm()->TransmitDirectly(&reqVRSAlignment);
		//QList<Review::ThreeValue<QRect> > oldRects = reqVRSAlignment.InspectionEachPageRects;
		QList<Review::ThreeValue<QRect> > oldRects;
		
		const QList<VRSAlignment::ThreePointAlignment> &list = reqVRSAlignment.getAlignment(currentSide()).getAffinSeedFromEachPage();
		for(int i=0; i<list.count(); i++){
			oldRects << list[i].getInsAlignment();
		}

		while(oldRects.count()<page+1){
			oldRects << Review::ThreeValue<QRect>();
		}

		QList<Review::ThreeValue<QRect> > newRects = oldRects;


		if(index==0){
			newRects[page].setFirst(rect);
		}else{
			newRects[page].setFirst(oldRects[page].first());
		}
		
		if(index==1){
			newRects[page].setSecond(rect);
		}else{
			newRects[page].setSecond(oldRects[page].second());
		}

		if(index==2){
			newRects[page].setThird(rect);
		}else{
			newRects[page].setThird(oldRects[page].third());
		}

		CmdSetVRSAlignment setVRSAlignment(GetLayersBase());
		setVRSAlignment.setSide(currentSide());

		setVRSAlignment.setSide(side);
		setVRSAlignment.setInspectionEachPageRects(newRects);
		_reviewAlgorithm()->TransmitDirectly(&setVRSAlignment);

		setDrawAlignmentList(newRects[page]);

		updateImage();
		updateEnableLabel();
		updateClearButtonEnable();
	}
}


void AlignmentManageForm::moveVRS(int movex, int movey, int movez)
{
	AlgorithmBase *RBase = _reviewAlgorithm();
	if(RBase==NULL)return;

	CmdReqVRSMotorState reqVRSPosition(_reviewAlgorithm()->GetLayersBase());
	RBase->TransmitDirectly(&reqVRSPosition);

	CmdSetVRSMotorState setVRSPosition(_reviewAlgorithm()->GetLayersBase());
	setVRSPosition.setX(movex, movex!=0);
	setVRSPosition.setY(movey, movey!=0);
	setVRSPosition.setZ(reqVRSPosition.z);

	RBase->TransmitDirectly( &setVRSPosition );
}

void AlignmentManageForm::setEachPageCameraAlignmentData(Review::SideType side, int page, int index, const QRect &beforeRect)
{
	CmdReqCameraAlignment getCameraAlignment(currentSide(), GetLayersBase());

	getCameraAlignment.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentEachPage);
	getCameraAlignment.setPage(page);
	getCameraAlignment.setNumber(index);

	_reviewAlgorithm()->TransmitDirectly( &getCameraAlignment );
	moveVRS(getCameraAlignment.point().x(), getCameraAlignment.point().y(), 0);

	QRectF rect = getCameraRect(getEachPageAlignmentRect(page)[index]);
	if(rect.isValid()==true){
		CmdSetCameraAlignment setCameraAlignment(currentSide(), GetLayersBase());

		setCameraAlignment.setVRSAlignmentType(Review::VRSAlignmentType::VRSAlingmentEachPage);
		setCameraAlignment.setPage(page);
		setCameraAlignment.setNumber(index);
		setCameraAlignment.setRect(rect);

		_reviewAlgorithm()->TransmitDirectly( &setCameraAlignment );

		updateImage();
		updateClearButtonEnable();
		updateEnableLabel();
	}
}