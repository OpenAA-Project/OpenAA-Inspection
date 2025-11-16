#pragma once

#include <QPoint>
#include <QDir>

#include "XReviewCommon.h"
#include "XReviewSettingFileSectionReader.h"
#include "XReviewPropertyBase.h"

class VRSSetting
{
public:
	VRSSetting();

public:
	class InspectionSideSetting
	{
	public:
		InspectionSideSetting();

	public:
		int Resolution;
		QPoint Offset;

	public:
		static QString sectionName();

	public:
		SectionBuffer toBuffer() const;
		bool fromBuffer(const SectionBuffer &buffer);
	};

	class VRSSideSetting
	{
	public:
		VRSSideSetting();

	public:
		void clear();

	public:
		Review::Rotate BoardRotation;
		int Resolution;
		QSize CameraViewRealSize;// um
		QPoint MotorOrigin;
		QPoint MotorOffset;
		QSize MotorMovableAreaSize;
		QVector3D EscapePosition;
		int ZInitialDistance;
		
	public:
		static QString sectionName();

	public:
		SectionBuffer toBuffer() const;
		bool fromBuffer(const SectionBuffer &buffer);
	};

private:
	InspectionSideSetting m_insSetting;
	VRSSideSetting m_vrsSetting;
	//AlignmentSetting m_alingmentSetting;

public:
	static QString baseName();
	static QString filename();
	static QString filePath(){ return baseName() + QDir::separator() + filename(); };

public:
	inline const InspectionSideSetting &getInspectionSizeSetting() const { return m_insSetting; };
	inline InspectionSideSetting &getInspectionSizeSetting() { return m_insSetting; };
	inline const VRSSideSetting &getVRSSideSetting() const { return m_vrsSetting; };
	inline VRSSideSetting &getVRSSideSetting() { return m_vrsSetting; };
	//inline const AlignmentSetting &getAlignmentSetting() const { return m_alingmentSetting; };
	//inline AlignmentSetting &getAlignmentSetting() { return m_alingmentSetting; };

	void setInspectionSizeSetting(const InspectionSideSetting &setting) { m_insSetting = setting; };
	void setVRSSideSetting(const VRSSideSetting &setting) { m_vrsSetting = setting; };
	//void setAlignmentSetting(const AlignmentSetting &setting){ m_alingmentSetting = setting; };

public:
	bool isValid() const;

public:
	SectionBufferList sectionBufferList() const;
	void fromSectionBufferList(const SectionBufferList &list);
};


class VRSAlignment{
public:
	VRSAlignment():m_WholeAlignPointList(),m_EachPageAlignPointList(),m_AlignmentType(Review::VRSAlignmentType::VRSAlingmentWholeImage),
		m_WholeAlignDataIsChanged(true),m_EachPageAlignDataIsChanged(true),m_MachineID(-1){};

public:
	class ThreePointAlignment
	{
	public:
		ThreePointAlignment(){};

	public:
		bool isEnable() const;
		QString toString() const{
			QList<QRect> list;

			list << getInsAlignment().first();
			list << getInsAlignment().second();
			list << getInsAlignment().third();
			list << getVRSAlignment().first();
			list << getVRSAlignment().second();
			list << getVRSAlignment().third();

			return AbstructProperty::fromList(list);
		}
		bool fromString(const QString &str){
			QList<QRect> list = AbstructProperty::toList<QRect>(str);
				
			if(list.count()<6){
				return false;
			}
				
			Review::ThreeValue<QRect> rects;
			rects.setValue(list[0], list[1], list[2]);
			setInsAlignment(rects);
				
			rects.setValue(list[3], list[4], list[5]);
			setVRSAlignment(rects);

			return true;
		}
		void fromRect(const QRect &first_1, const QRect &first_2, const QRect &second_1, const QRect &second_2, const QRect &third_1, const QRect &third_2)
		{
			Review::ThreeValue<QRect> rects;

			rects.setValue(first_1, second_1, third_1);
			setInsAlignment(rects);

			rects.setValue(first_2, second_2, third_2);
			setVRSAlignment(rects);
		}
		static QString separation() { return QString(/**/"-"); };

	public:
		QPair<QPoint, QPoint> firstPoint() const { return QPair<QPoint, QPoint>(getInsAlignment().first().center(), getVRSAlignment().first().center()); };
		QPair<QPoint, QPoint> secondPoint() const { return QPair<QPoint, QPoint>(getInsAlignment().second().center(), getVRSAlignment().second().center()); };
		QPair<QPoint, QPoint> thirdPoint() const { return QPair<QPoint, QPoint>(getInsAlignment().third().center(), getVRSAlignment().third().center()); };

		inline const Review::ThreeValue<QRect> &getInsAlignment() const { return m_InsAlignment; };
		inline Review::ThreeValue<QRect> &getInsAlignment() { return m_InsAlignment; };
		inline const Review::ThreeValue<QRect> &getVRSAlignment() const { return m_VRSAlignment; };
		inline Review::ThreeValue<QRect> &getVRSAlignment() { return m_VRSAlignment; };
		void setInsAlignment(const Review::ThreeValue<QRect> &alignment){ m_InsAlignment = alignment; };
		void setVRSAlignment(const Review::ThreeValue<QRect> &alignment){ m_VRSAlignment = alignment; };


		Review::ThreeValue<QRect> m_InsAlignment;
		Review::ThreeValue<QRect> m_VRSAlignment;

	public:
		void setAlignmentPoint(Review::AlignmentSide side, Review::AlignmentNo PointNo, const QRect &rect);
		QPair<QRect, QRect> getAlignmentRectPair(Review::AlignmentNo PointNo) const;
		QPair<QPoint, QPoint> getAlignmentPointPair(Review::AlignmentNo PointNo) const;
		QPoint getAlignmentPoint(Review::AlignmentSide side, Review::AlignmentNo PointNo) const;

		QRect getInsAlignmentRect(Review::AlignmentNo PointNo) const;
		QRect getVRSAlignmentRect(Review::AlignmentNo PointNo) const;
			
		QPoint getInsAlignmentPoint(Review::AlignmentNo PointNo) const;
		QPoint getVRSAlignmentPoint(Review::AlignmentNo PointNo) const;

		void setInsAlignmentRect(Review::AlignmentNo PointNo, const QRect &rect);
		void setVRSAlignmentRect(Review::AlignmentNo PointNo, const QRect &rect);
	};

	void setAffinSeedToWhole(const ThreePointAlignment &align);
	void setAffinSeedToEachPage(const QList<ThreePointAlignment> &pointList);

	ThreePointAlignment getAffinSeedFromWhole() const;
	Review::ThreeValue<QRect> getAffinSeedRectFromWhole(Review::AlignmentSide side) const;
	QList<ThreePointAlignment> getAffinSeedFromEachPage() const;
	ThreePointAlignment getAffinSeedFromEachPage(int page) const;
	QList<Review::ThreeValue<QRect> > getAffinSeedRectFromEachPage(Review::AlignmentSide side) const;
	Review::ThreeValue<QRect> getAffinSeedRectFromEachPage(Review::AlignmentSide side, int page) const;

	bool isWholeAffinMatrixEnable() const;
	bool isEachPageAffinMatrixEnable() const;
	bool isEachPageAffinMatrixEnable(int page) const;
		
	QMatrix getWholeAffinMatrix() const;
	QList<QMatrix> getEachPageAffinMatrix() const;
	QMatrix getEachPageAffinMatrix(int page) const;

	void setAlignmentType(Review::VRSAlignmentType type){ m_AlignmentType = type; };
	Review::VRSAlignmentType getAlignmentType() const{ return m_AlignmentType; };

	QString baseName() const { return QString(/**/"%1-%2").arg(sectionName()).arg(m_MachineID); };
	QString filename() const { return QString(/**/"ReviewProperty") + QDir::separator() + baseName() + QString(".dat"); };
	static QString sectionName() { return QString(/**/"VRSAlignment"); };
	SectionBuffer toBuffer() const;
	SectionBufferList toBufferList() const;
	void fromBuffer(const SectionBuffer &buffer);

	int machineID() const { return m_MachineID; };
	void setMachineID(int id){ m_MachineID = id; };

	void setPageCount(int pageCount){
		if(pageCount!=m_EachPageAlignPointList.count()){
			Review::resize(pageCount, m_EachPageAlignPointList);
			m_EachPageAlignDataIsChanged = true;
		}
	};

private:
	static QMatrix createAffin(const QPoint &ins1, const QPoint &ins2, const QPoint ins3,
							const QPoint &mac1, const QPoint &mac2, const QPoint mac3);

private:
	ThreePointAlignment m_WholeAlignPointList;
	QList<ThreePointAlignment> m_EachPageAlignPointList;
	Review::VRSAlignmentType m_AlignmentType;

	bool m_WholeAlignDataIsChanged;
	bool m_EachPageAlignDataIsChanged;

	int m_MachineID;
};
