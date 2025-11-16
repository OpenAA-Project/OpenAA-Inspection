#ifndef FILTERNOTHING_H
#define FILTERNOTHING_H

#include "filterimageshading_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"

#include <QFileInfo>
#include <QDateTime>
#include <QFile>
#include <QPair>

class	ImageBuffer;

class	ImageStatus{
public:
	ImageStatus(const QString &filename=/**/QString()){
		setFile(filename);
	};

public:
	void setSize(qint64 _size){
		m_size = _size;
	};

	void setLastModified(const QDateTime &date){
		m_lastModified = date;
	};

	qint64 size() const { return m_size; };
	QDateTime lastModified() const { return m_lastModified; };

	bool isNull() const { return m_lastModified.isNull(); };

public:
	void setFile(const QString &filename){
		QFileInfo info(filename);
		
		if(info.isFile()==true){
			m_size = info.size();
			m_lastModified = info.lastModified();
		}else{
			m_size = 0;
			m_lastModified = QDateTime();
		}
	};

private:
	qint64 m_size;
	QDateTime m_lastModified;

public:
	bool operator==(const ImageStatus &other) const {
		return (size()==other.size() && lastModified()==other.lastModified());
	};
	bool operator!=(const ImageStatus &other) const {
		return !(*this==other);
	};
};

QDataStream& operator<<(QDataStream& s, const ImageStatus &finf)
{
    s << finf.size();
	s << finf.lastModified();
    return s;
}

QDataStream& operator>>(QDataStream& s, ImageStatus &finf)
{
	qint64 size;
	QDateTime date;
	
	finf = ImageStatus();
    
	s >> size;

	if(s.status()==QDataStream::Status::Ok){
		finf.setSize(size);
	}else{
		finf = ImageStatus();
		return s;
	}

	s >> date;

	if(s.status()==QDataStream::Status::Ok){
		finf.setLastModified(date);
	}else{
		finf = ImageStatus();
	}

    return s;
}

class	FilterImageShading : public FilterClassBase
{
public:
	FilterImageShading(LayersBase *base);
	~FilterImageShading(void);

public:
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts);
	virtual	bool	Initial(void);
	virtual	bool	Release(void);
	virtual	QString	GetDataText(void);
	virtual	QString	GetDefaultFileName(void);
	QString imagePath(int number) const;

private:
	void _calcMultiply(ImageBuffer *buff, const qreal * const data, qreal preOffset, qreal aftOffset, const int MaxLines, const int DotPerLine);
	void _makeShadingData();
	void _makeShadingData(int layer);
	void _makeAverageData(const QImage &image, int layer, qreal *buffer, int bufferLen);
	void _makeShadingData(qreal *averageArray, int arrayLen, qreal *resultArray, qreal target, qreal preOffset);
	bool _isImageModified(int layer) const;
	void _updateArrayLength(int length);
	static QList<QPair<int/* light level */, int/* vote count */> > _noiseCutting(const QImage &image, int x, int layer, qreal cutLevel=20.0/* % */);
	void BuildTable(BYTE *Table[256],const qreal * const data, qreal preOffset, qreal aftOffset, const int MaxLines, const int DotPerLine);

public:
	void setImagePath(const QString &imgPathR, const QString &imgPathG, const QString &imgPathB);
	void setTarget(qreal targetR, qreal targetG, qreal targetB);
	void setPreOffset(qreal offsetR, qreal offsetG, qreal offsetB);
	void setAftOffset(qreal offsetR, qreal offsetG, qreal offsetB);
	qreal target(int layer);
	qreal preOffset(int layer);
	qreal aftOffset(int layer);

private:
	qint64 m_arrayLength;

	QString m_imagePathLayerR;
	QString m_imagePathLayerG;
	QString m_imagePathLayerB;

	ImageStatus m_imageStatusLayerR;
	ImageStatus m_imageStatusLayerG;
	ImageStatus m_imageStatusLayerB;

	qreal *m_multiplyListR;
	qreal *m_multiplyListG;
	qreal *m_multiplyListB;

	BYTE	*m_TableListR[256];
	BYTE	*m_TableListG[256];
	BYTE	*m_TableListB[256];

	qreal m_targetValueR;
	qreal m_targetValueG;
	qreal m_targetValueB;

	qreal m_preOffsetValueR;
	qreal m_preOffsetValueG;
	qreal m_preOffsetValueB;
	
	qreal m_aftOffsetValueR;
	qreal m_aftOffsetValueG;
	qreal m_aftOffsetValueB;
};

#endif // FILTERNOTHING_H
