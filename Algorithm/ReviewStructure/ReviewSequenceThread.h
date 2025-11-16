#pragma once

#include <QThread>
#include <QMutex>

#include "ThreadSequence.h"
#include "ReviewSequenceGlobal.h"

class ReviewSequenceRequire
{
public:
	ReviewSequenceRequire();

public:
	void setMotorRequireTypeFlags(ReviewSequence::SeqMotorRequireFlags flags);
	ReviewSequence::SeqMotorRequireFlags getMotorRequireTypeFlags(void) const;

public:
	void setMoveX(int x, bool setFlag = true);
	void setMoveY(int y, bool setFlag = true);
	void setMoveXY(int x, int y, bool setFlag = true);
	void setMoveZ(int z, bool setFlag = true);
	void setMoveXYZ(int x, int y, int z, bool setFlag = true);

	int getMoveX(void) const;
	int getMoveY(void) const;
	int getMoveZ(void) const;

	bool isEmpty() const;

private:
	ReviewSequence::SeqMotorRequireFlags m_MotorReqFlags;

	int m_x;
	int m_y;
	int m_z;
};

class ReviewSequenceThread : public QObject// : public QThread
{
	Q_OBJECT

public:
	ReviewSequenceThread(LayersBase *Base, QObject *parent=NULL);

protected:
	//void run(void);
	bool execSequence(const ReviewSequenceRequire &reqItem, ReviewSequenceRequire &remainRequire);
	void debugOut();

public slots:
	void update();
	void append(const ReviewSequenceRequire &reqItem);
	void clear(void);
	void stop(void);
	void setStop(bool);

public:
	static ReviewSequenceRequire compressRequire(const QList<ReviewSequenceRequire> &reqList);
	static bool isWaiting(ReviewSequence::SeqMotorRequireFlags flags, SeqControl *seqCtrl);

public:
	LayersBase *GetLayersBase();
	void SetLayersBase(LayersBase *Base);
	int x();
	int y();
	int z();
	bool isXEnable();
	bool isYEnable();
	bool isZEnable();
	bool isXYEnable();
	bool isXYZEnable();
	bool setX(int);
	bool setY(int);
	bool setZ(int);
	bool setXY(int, int);
	bool setXYZ(int, int, int);

	int pulsePerMM_x();
	int pulsePerMM_y();
	int pulsePerMM_z();

public:
	//inline const ReviewSequenceControl *getSeqControlParamPtr() const;
	//inline ReviewSequenceControl *getSeqControlParamPtr();

private:
	volatile bool m_stop;
	QList<ReviewSequenceRequire> m_ReqList;
	QMutex m_mutex;
	//ReviewSequenceControl m_seqControl;
	LayersBase *m_LayersBase;
};

