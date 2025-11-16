#include "ReviewSequenceThread.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"

#include "XSequence.h"
#include "ThreadSequence.h"

#include "ReviewSequenceGlobal.h"

bool isSequenceThreadExist(LayersBase *base){
	if(base==NULL){
		return false;
	}
	if(base->GetSequenceInstance()==NULL){
		return false;
	}
	if(base->GetSequenceInstance()->GetMainSeqControl()==NULL){
		return false;
	}
	return true;
}

ReviewSequenceRequire::ReviewSequenceRequire()
	:m_MotorReqFlags(ReviewSequence::MotorRequireNone),m_x(0),m_y(0),m_z(0)
{}

void ReviewSequenceRequire::setMotorRequireTypeFlags(ReviewSequence::SeqMotorRequireFlags flags)
{
	m_MotorReqFlags = flags;
}

ReviewSequence::SeqMotorRequireFlags ReviewSequenceRequire::getMotorRequireTypeFlags(void) const
{
	return m_MotorReqFlags;
}

void ReviewSequenceRequire::setMoveX(int x, bool setFlag)
{
	m_x = x;
	if(setFlag==true){
		setMotorRequireTypeFlags( getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveX );
	}
}

void ReviewSequenceRequire::setMoveY(int y, bool setFlag)
{
	m_y = y;
	if(setFlag==true){
		setMotorRequireTypeFlags( getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveY );
	}
}

void ReviewSequenceRequire::setMoveXY(int x, int y, bool setFlag)
{
	setMoveX(x);
	setMoveY(y);
	if(setFlag==true){
		setMotorRequireTypeFlags( getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveXY );
	}
}

void ReviewSequenceRequire::setMoveZ(int z, bool setFlag)
{
	m_z = z;
	if(setFlag==true){
		setMotorRequireTypeFlags( getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveZ );
	}
}

void ReviewSequenceRequire::setMoveXYZ(int x, int y, int z, bool setFlag)
{
	setMoveX(x);
	setMoveY(y);
	setMoveZ(z);
	if(setFlag==true){
		setMotorRequireTypeFlags( getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveXYZ );
	}
}

int ReviewSequenceRequire::getMoveX(void) const
{
	return m_x;
}

int ReviewSequenceRequire::getMoveY(void) const
{
	return m_y;
}

int ReviewSequenceRequire::getMoveZ(void) const
{
	return m_z;
}

bool ReviewSequenceRequire::isEmpty() const
{
	return (m_MotorReqFlags==ReviewSequence::SeqMotorRequire::MotorRequireNone);
}

///////////////////////////////////////////////////////////

ReviewSequenceThread::ReviewSequenceThread(LayersBase *Base, QObject *parent)
	:QObject(parent)
	,m_stop(false)
	,m_ReqList()
	,m_mutex()
	,m_LayersBase(Base)
{
}

void ReviewSequenceThread::clear()
{
	QMutexLocker locker(&m_mutex);

	m_ReqList.clear();
}

LayersBase *ReviewSequenceThread::GetLayersBase()
{
	return m_LayersBase;
}

void ReviewSequenceThread::SetLayersBase(LayersBase *Base)
{
	m_LayersBase = Base;
}

int ReviewSequenceThread::x()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return 0;
	}
	SeqControl	*Seq=GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return Seq->GetDataSpecialOperand(Seq->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_X);
}

int ReviewSequenceThread::y()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return 0;
	}
	SeqControl	*Seq=GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return Seq->GetDataSpecialOperand(Seq->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Y);
}

int ReviewSequenceThread::z()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return 0;
	}
	SeqControl	*Seq=GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return Seq->GetDataSpecialOperand(Seq->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Z);
}

bool ReviewSequenceThread::isXEnable()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return false;
	}
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return !isWaiting(ReviewSequence::MotorRequireMoveX, seqCtrl);
}

bool ReviewSequenceThread::isYEnable()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return false;
	}
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return !isWaiting(ReviewSequence::MotorRequireMoveY, seqCtrl);
}

bool ReviewSequenceThread::isZEnable()
{
	if(isSequenceThreadExist(GetLayersBase())==false){
		return false;
	}
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return !isWaiting(ReviewSequence::MotorRequireMoveZ, seqCtrl);
}

bool ReviewSequenceThread::isXYEnable()
{
	return (isXEnable()==true && isYEnable()==true);
}

bool ReviewSequenceThread::isXYZEnable()
{
	return (isXYEnable()==true && isZEnable()==true);
}

bool ReviewSequenceThread::setX(int val)
{
	if(isXEnable()==false){
		return false;
	}

	ReviewSequenceRequire item;
	item.setMoveX(val);
	item.setMotorRequireTypeFlags( ReviewSequence::SeqMotorRequire::MotorRequireMoveX );

	append(item);

	return true;
}

bool ReviewSequenceThread::setY(int val)
{
	if(isXEnable()==false){
		return false;
	}

	ReviewSequenceRequire item;
	item.setMoveX(val);
	item.setMotorRequireTypeFlags( ReviewSequence::SeqMotorRequire::MotorRequireMoveY );

	append(item);

	return true;
}

bool ReviewSequenceThread::setZ(int val)
{
	if(isXEnable()==false){
		return false;
	}

	ReviewSequenceRequire item;
	item.setMoveX(val);
	item.setMotorRequireTypeFlags( ReviewSequence::SeqMotorRequire::MotorRequireMoveZ );

	append(item);

	return true;
}

bool ReviewSequenceThread::setXY(int val_x, int val_y)
{
	return (setX(val_x)==true && setY(val_y));
}

bool ReviewSequenceThread::setXYZ(int val_x, int val_y, int val_z)
{
	return (setXY(val_x, val_y) && setZ(val_z));
}

int ReviewSequenceThread::pulsePerMM_x()
{
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_PULUS_PER_MM_X);
}

int ReviewSequenceThread::pulsePerMM_y()
{
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_PULUS_PER_MM_Y);
}

int ReviewSequenceThread::pulsePerMM_z()
{
	SeqControl *seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	return seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_PULUS_PER_MM_Z);
}

void ReviewSequenceThread::update()
{
	append(ReviewSequenceRequire());
}

void ReviewSequenceThread::append(const ReviewSequenceRequire &reqItem)
{
	static QTimer *timer= new QTimer(this);
	static bool first = true;
	if(first==true){
		timer->setSingleShot(true);
		timer->setInterval(500);
		connect(timer, SIGNAL(timeout()), this, SLOT(update()));
		first=false;
	}
	//QMutexLocker locker(&m_mutex);

	//m_ReqList.append(reqItem);

	ReviewSequenceRequire remainItem;// 残った実行コマンドのバッファ
	ReviewSequenceRequire ReqItem;

	if(reqItem.isEmpty()==false){
		m_ReqList.append(reqItem);
	}
	if(m_ReqList.isEmpty()==true){
		return;
	}

	//ReqItem = compressRequire(m_ReqList);// 圧縮して一つの実行コマンドにする
	ReqItem = compressRequire(m_ReqList);

	m_ReqList.clear();// 要求アイテムをクリア

	if(ReqItem.isEmpty()==true){
		return;
	}

	// シーケンス処理実行
	bool ok = execSequence(ReqItem, remainItem);
	if(ok==false){// 残りがある
		QMutexLocker locker(&m_mutex);
		m_ReqList.push_front(remainItem);// 最優先位置に追加
		if(timer->isActive()==true){
			timer->stop();
		}
		timer->start();
	}

	debugOut();
}

//void ReviewSequenceThread::run()
//{
//	ReviewSequenceRequire remainItem;// 残った実行コマンドのバッファ
//	ReviewSequenceRequire ReqItem;
//
//	while(m_stop==false){
//
//		{// MutexLocker
//			QMutexLocker locker(&m_mutex);
//			if(m_ReqList.isEmpty()==true){
//				msleep(100);
//				debugOut();
//				continue;
//			}
//
//
//			ReqItem = compressRequire(m_ReqList);// 圧縮して一つの実行コマンドにする
//
//			m_ReqList.clear();// 要求アイテムをクリア
//		}
//
//		// シーケンス処理実行
//		bool ok = execSequence(ReqItem, remainItem);
//		if(ok==false){// 残りがある
//			QMutexLocker locker(&m_mutex);
//			m_ReqList.push_front(remainItem);// 最優先位置に追加
//		}
//
//		qDebug() << "Seq is updated.";
//	}
//}

void ReviewSequenceThread::debugOut()
{
	//static qlonglong counter = 0;
	//if(GetLayersBase()!=NULL && GetLayersBase()->GetSequenceInstance()!=NULL && GetLayersBase()->GetSequenceInstance()->GetMainSeqControl()!=NULL){
	//	qDebug() << "[" << counter << "]";
	//	qDebug() << "Seq X:" << x();
	//	qDebug() << "Seq Y:" << y();
	//	qDebug() << "Seq Z:" << z();
	//	qDebug() << "";
	//	
	//	counter++;
	//}
}

// モーター動作を実行する
// シーケンス側の設定によって動作不可能状態になる場合があるので、その場合はremainRequireに保存される
bool ReviewSequenceThread::execSequence(const ReviewSequenceRequire &reqItem, ReviewSequenceRequire &remainRequire)
{
	bool ret = true;
	bool originMode = false;
	remainRequire = ReviewSequenceRequire();

	const ReviewSequence::SeqMotorRequireFlags reqType = reqItem.getMotorRequireTypeFlags();
	ReviewSequence::SeqMotorRequireFlags sendType = ReviewSequence::MotorRequireNone;
	ReviewSequence::SeqMotorRequireFlags remainType = ReviewSequence::MotorRequireNone;

	SeqControl *seqCtrl;
	if(GetLayersBase()!=NULL && GetLayersBase()->GetSequenceInstance()!=NULL && GetLayersBase()->GetSequenceInstance()->GetMainSeqControl()!=NULL){
		seqCtrl = GetLayersBase()->GetSequenceInstance()->GetMainSeqControl();
	}else{
		remainRequire = reqItem;
		return false;
	}
	
	if(ReviewSequence::isIncludeFlags(reqType, ReviewSequence::MotorRequireMoveOrigin)==true){
		seqCtrl->SetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_MOTER_REQUIRE, ReviewSequence::MotorRequireMoveOrigin);
		sendType |= ReviewSequence::MotorRequireMoveOrigin;
		originMode = true;
	}

	if(ReviewSequence::isIncludeFlags(reqType, ReviewSequence::MotorRequireMoveX)==true){
		if(originMode==true || isWaiting(SEQ_REVIEW_P_MOTER_FLAG_X, seqCtrl)==true){
			remainRequire.setMoveX(reqItem.getMoveX());
			remainRequire.setMotorRequireTypeFlags( remainRequire.getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveX);
			remainType |= ReviewSequence::MotorRequireMoveX;
			ret = false;
		}else{
			seqCtrl->SetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_X, reqItem.getMoveX());
			sendType |= ReviewSequence::MotorRequireMoveX;
		}
	}
	if(ReviewSequence::isIncludeFlags(reqType, ReviewSequence::MotorRequireMoveY)==true){
		if(originMode==true || isWaiting(SEQ_REVIEW_P_MOTER_FLAG_Y, seqCtrl)==true){
			remainRequire.setMoveY(reqItem.getMoveY());
			remainRequire.setMotorRequireTypeFlags( remainRequire.getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveY);
			remainType |= ReviewSequence::MotorRequireMoveY;
			ret = false;
		}else{
			seqCtrl->SetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Y, reqItem.getMoveY());
			sendType |= ReviewSequence::MotorRequireMoveY;
		}
	}
	if(ReviewSequence::isIncludeFlags(reqType, ReviewSequence::MotorRequireMoveZ)==true){
		if(originMode==true || isWaiting(SEQ_REVIEW_P_MOTER_FLAG_Z, seqCtrl)==true){
			remainRequire.setMoveZ(reqItem.getMoveZ());
			remainRequire.setMotorRequireTypeFlags( remainRequire.getMotorRequireTypeFlags() | ReviewSequence::MotorRequireMoveZ);
			remainType |= ReviewSequence::MotorRequireMoveZ;
			ret = false;
		}else{
			seqCtrl->SetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Z, reqItem.getMoveZ());
			sendType |= ReviewSequence::MotorRequireMoveZ;
		}
	}
	qDebug() << seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_X);
	qDebug() << seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Y);
	qDebug() << seqCtrl->GetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_POSITION_Z);

	seqCtrl->SetDataSpecialOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_S_MOTER_REQUIRE, static_cast<int>(sendType));

	return ret;
}

ReviewSequenceRequire ReviewSequenceThread::compressRequire(const QList<ReviewSequenceRequire> &reqList)
{
	ReviewSequenceRequire retItem;
	ReviewSequence::SeqMotorRequireFlags moveFlags = ReviewSequence::MotorRequireNone;

	for(QList<ReviewSequenceRequire>::ConstIterator it=reqList.constBegin(); it!=reqList.constEnd(); it++){
		const ReviewSequence::SeqMotorRequireFlags reqFlags = it->getMotorRequireTypeFlags();

		if(ReviewSequence::isIncludeFlags(reqFlags, ReviewSequence::MotorRequireMoveX)==true){
			retItem.setMoveX(it->getMoveX());
			moveFlags |= ReviewSequence::MotorRequireMoveX;
		}
		if(ReviewSequence::isIncludeFlags(reqFlags, ReviewSequence::MotorRequireMoveY)==true){
			retItem.setMoveY(it->getMoveY());
			moveFlags |= ReviewSequence::MotorRequireMoveY;
		}
		if(ReviewSequence::isIncludeFlags(reqFlags, ReviewSequence::MotorRequireMoveZ)==true){
			retItem.setMoveZ(it->getMoveZ());
			moveFlags |= ReviewSequence::MotorRequireMoveZ;
		}
		if(ReviewSequence::isIncludeFlags(reqFlags, ReviewSequence::MotorRequireMoveOrigin)==true){
			moveFlags |= ReviewSequence::MotorRequireMoveOrigin;
		}
	}
	retItem.setMotorRequireTypeFlags( moveFlags );

	return retItem;
}

bool ReviewSequenceThread::isWaiting(ReviewSequence::SeqMotorRequireFlags flags, SeqControl *seqCtrl)
{
	bool ret = false;

	if((ReviewSequence::isIncludeFlags(flags, ReviewSequence::MotorRequireMoveX)==true) && seqCtrl->GetDataSpecialBitOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_P_MOTER_FLAG_X)==ReviewSequence::MotorIsLocked){
		ret = true;
	}
	if(ret==false && (ReviewSequence::isIncludeFlags(flags, ReviewSequence::MotorRequireMoveY)==true) && seqCtrl->GetDataSpecialBitOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_P_MOTER_FLAG_Y)==ReviewSequence::MotorIsLocked){
		ret = true;
	}
	if(ret==false && (ReviewSequence::isIncludeFlags(flags, ReviewSequence::MotorRequireMoveZ)==true) && seqCtrl->GetDataSpecialBitOperand(seqCtrl->GetLocalParamPointer(),SEQ_REVIEW_P_MOTER_FLAG_Z)==ReviewSequence::MotorIsLocked){
		ret = true;
	}

	return ret;
}

void ReviewSequenceThread::setStop(bool stop_)
{
	m_stop = stop_;
}

void ReviewSequenceThread::stop(void)
{
	setStop(true);
}
