/*
 * Copyright (C) 2014
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

#include "ReviewStructureVRSSetting.h"
#include "XReviewPropertyBase.h"
#include <QDebug>

#define ToStr(x) #x

VRSSetting::VRSSetting()
	:m_insSetting(),m_vrsSetting()
{
}

QString VRSSetting::baseName()
{
	return /**/"ReviewProperty";
}

QString VRSSetting::filename()
{
	return /**/"VRSSetting.dat";
}

SectionBufferList VRSSetting::sectionBufferList() const
{
	SectionBufferList list;

	list.append(getInspectionSizeSetting().toBuffer());
	list.append(getVRSSideSetting().toBuffer());
	//list.append(getAlignmentSetting().toBuffer());

	return list;
}

void VRSSetting::fromSectionBufferList(const SectionBufferList &list)
{
	for(int i=0; i<list.count(); i++){
		if(list[i].sectionName()==InspectionSideSetting::sectionName()){
			getInspectionSizeSetting().fromBuffer(list[i]);
		}
		if(list[i].sectionName()==VRSSideSetting::sectionName()){
			getVRSSideSetting().fromBuffer(list[i]);
		}
		//if(list[i].sectionName()==AlignmentSetting::sectionName()){
		//	getAlignmentSetting().fromBuffer(list[i]);
		//}
	}
}

VRSSetting::InspectionSideSetting::InspectionSideSetting()
	:Resolution(-1),Offset()
{}

QString VRSSetting::InspectionSideSetting::sectionName()
{
	return /**/"InspectionSetting";
}

SectionBuffer VRSAlignment::toBuffer() const
{
	SectionBuffer buffer;
	buffer.setSectionName( sectionName() );

	buffer.setValue("UseAlignmentType", QString::number(static_cast<int>(getAlignmentType())));
	
	buffer.setValue(/**/"WholeAlingment", getAffinSeedFromWhole().toString() );

	for(int i=0; i<getAffinSeedFromEachPage().count(); i++){
		buffer.setValue(QString(/**/"EachPageAlignment-%1").arg(i), getAffinSeedFromEachPage()[i].toString());
	}

	return buffer;
}

SectionBufferList VRSAlignment::toBufferList() const
{
	return Review::toList(toBuffer());
}

void VRSAlignment::fromBuffer(const SectionBuffer &buffer)
{
	if(sectionName()!=buffer.sectionName()){
		return;
	}

	if(buffer.hasValue("UseAlignmentType")==true){
		setAlignmentType( static_cast<Review::VRSAlignmentType>(buffer.value("UseAlignmentType").toInt()) );
	}

	ThreePointAlignment wpoint;
	if(buffer.hasValue(/**/"WholeAlingment")==true){
		wpoint.fromString(buffer.value(/**/"WholeAlingment") );
	}
	setAffinSeedToWhole(wpoint);

	QList<ThreePointAlignment> pointList;
	for(int i=0; true; i++){
		QString key = QString(/**/"EachPageAlignment-%1").arg(i);
		if(buffer.hasValue(key)==true){
			ThreePointAlignment point;
			point.fromString(buffer.value(key));
			pointList << point;
		}else{
			break;
		}
	}
	setAffinSeedToEachPage(pointList);
}

void fromBuffer(const SectionBuffer &buffer);

SectionBuffer VRSSetting::InspectionSideSetting::toBuffer() const
{
	SectionBuffer buf;
	buf.setSectionName(sectionName());
	buf.setValue(ToStr(Resolution), QString::number(Resolution));
	buf.setValue(ToStr(Offset), AbstructProperty::fromPoint(Offset));

	return buf;
}

bool VRSSetting::InspectionSideSetting::fromBuffer(const SectionBuffer &buffer)
{
	if(buffer.isValid()==false)return false;

	if(buffer.sectionName()!=sectionName())return false;

	QString dest;

	dest = buffer.value(ToStr(Resolution));
	if(dest.isNull()==false){
		bool ok;
		int res = dest.toInt(&ok);
		if(ok==true){
			Resolution = res;
		}
	}

	dest = buffer.value(ToStr(Offset));
	if(dest.isNull()==false){
		QPoint p = AbstructProperty::toPoint(dest);
		if(p.isNull()==false){
			Offset = p;
		}
	}

	return true;
}

VRSSetting::VRSSideSetting::VRSSideSetting()
{
	clear();
}

void VRSSetting::VRSSideSetting::VRSSideSetting::clear()
{
	BoardRotation = Review::Rotate_0;
	Resolution = -1;
	CameraViewRealSize = QSize();
	MotorOrigin = QPoint();
	MotorOffset = QPoint();
	MotorMovableAreaSize = QSize();
	EscapePosition = QVector3D();
	ZInitialDistance = 0;
}

QString VRSSetting::VRSSideSetting::sectionName()
{
	return /**/"VRSSetting";
}

SectionBuffer VRSSetting::VRSSideSetting::toBuffer() const
{
	SectionBuffer buf;
	buf.setSectionName(sectionName());
	buf.setValue(ToStr(BoardRotation), QString::number(BoardRotation));
	buf.setValue(ToStr(Resolution), QString::number(Resolution));
	buf.setValue(ToStr(CameraViewRealSize), AbstructProperty::fromSize(CameraViewRealSize));
	buf.setValue(ToStr(MotorOrigin), AbstructProperty::fromPoint(MotorOrigin));
	buf.setValue(ToStr(MotorOffset), AbstructProperty::fromPoint(MotorOffset));
	buf.setValue(ToStr(MotorMovableAreaSize), AbstructProperty::fromSize(MotorMovableAreaSize));
	buf.setValue(ToStr(EscapePosition), AbstructProperty::fromVector3D(EscapePosition));
	buf.setValue(ToStr(ZInitialDistance), QString::number(ZInitialDistance));

	return buf;
}

bool VRSSetting::VRSSideSetting::fromBuffer(const SectionBuffer &buffer)
{
	if(buffer.isValid()==false)return false;

	if(buffer.sectionName()!=sectionName())return false;
	
	QString dest;
	
	dest = buffer.value(ToStr(BoardRotation));
	if(dest.isNull()==false){
		bool ok;
		int res = dest.toInt(&ok);
		if(ok==true){
			BoardRotation = static_cast<Review::Rotate>(res);
		}
	}

	dest = buffer.value(ToStr(Resolution));
	if(dest.isNull()==false){
		bool ok;
		int res = dest.toInt(&ok);
		if(ok==true){
			Resolution = res;
		}
	}

	dest = buffer.value(ToStr(CameraViewRealSize));
	if(dest.isNull()==false){
		QSize size = AbstructProperty::toSize(dest);
		if(size.isNull()==false){
			CameraViewRealSize = size;
		}
	}
	
	dest = buffer.value(ToStr(MotorOrigin));
	if(dest.isNull()==false){
		QPoint p = AbstructProperty::toPoint(dest);
		if(p.isNull()==false){
			MotorOrigin = p;
		}
	}

	dest = buffer.value(ToStr(MotorOffset));
	if(dest.isNull()==false){
		QPoint p = AbstructProperty::toPoint(dest);
		if(p.isNull()==false){
			MotorOffset = p;
		}
	}

	dest = buffer.value(ToStr(MotorMovableAreaSize));
	if(dest.isNull()==false){
		QSize size = AbstructProperty::toSize(dest);
		if(size.isNull()==false){
			MotorMovableAreaSize = size;
		}
	}
	
	dest = buffer.value(ToStr(EscapePosition));
	if(dest.isNull()==false){
		QVector3D p = AbstructProperty::toVector3D(dest);
		if(p.isNull()==false){
			EscapePosition = p;
		}
	}
	
	dest = buffer.value(ToStr(ZInitialDistance));
	if(dest.isNull()==false){
		bool ok;
		int res = dest.toInt(&ok);
		if(ok==true){
			ZInitialDistance = static_cast<Review::Rotate>(res);
		}
	}

	return true;
}

bool VRSSetting::isValid() const
{
	const VRSSetting::InspectionSideSetting insSet = getInspectionSizeSetting();

	if(insSet.Resolution<=0){
		return false;
	}

	const VRSSetting::VRSSideSetting vrsSet = getVRSSideSetting();

	if(vrsSet.CameraViewRealSize.isValid()==false || vrsSet.Resolution<=0){
		return false;
	}

	return true;
}

VRSAlignment::ThreePointAlignment VRSAlignment::getAffinSeedFromWhole() const
{
	return m_WholeAlignPointList;
}

Review::ThreeValue<QRect> VRSAlignment::getAffinSeedRectFromWhole(Review::AlignmentSide side) const
{
	Review::ThreeValue<QRect> ret;
	if(side==Review::AlignmentSide_Inspection){
		ret = m_WholeAlignPointList.getInsAlignment();
	}else{
		ret = m_WholeAlignPointList.getVRSAlignment();
	}
	return ret;
}

QList<VRSAlignment::ThreePointAlignment> VRSAlignment::getAffinSeedFromEachPage() const
{
	return m_EachPageAlignPointList;
}

VRSAlignment::ThreePointAlignment VRSAlignment::getAffinSeedFromEachPage(int page) const
{
	VRSAlignment::ThreePointAlignment align;
	if(Review::isIndexEnable(page, m_EachPageAlignPointList)==true){
		align = m_EachPageAlignPointList[page];
	}
	return align;
}

QList<Review::ThreeValue<QRect> > VRSAlignment::getAffinSeedRectFromEachPage(Review::AlignmentSide side) const
{
	QList<Review::ThreeValue<QRect> >  ret;
	if(side==Review::AlignmentSide_Inspection){
		for(int i=0; i<getAffinSeedFromEachPage().count(); i++){
			ret << getAffinSeedFromEachPage()[i].getInsAlignment();
		}
	}else{
		for(int i=0; i<getAffinSeedFromEachPage().count(); i++){
			ret << getAffinSeedFromEachPage()[i].getVRSAlignment();
		}
	}
	return ret;
}

Review::ThreeValue<QRect> VRSAlignment::getAffinSeedRectFromEachPage(Review::AlignmentSide side, int page) const
{
	QList<Review::ThreeValue<QRect> > list = getAffinSeedRectFromEachPage(side);

	if(Review::isIndexEnable(page, list)==true){
		return list[page];
	}else{
		return Review::ThreeValue<QRect>();
	}
}

bool VRSAlignment::isWholeAffinMatrixEnable() const
{
	return m_WholeAlignPointList.isEnable();
}

bool VRSAlignment::isEachPageAffinMatrixEnable() const
{
	for(int i=0; i<m_EachPageAlignPointList.count(); i++){
		if(m_EachPageAlignPointList[i].isEnable()==false){
			return false;
		}
	}

	return true;
}

bool VRSAlignment::isEachPageAffinMatrixEnable(int page) const
{
	if(Review::isIndexEnable(page, m_EachPageAlignPointList)==true){
		return m_EachPageAlignPointList[page].isEnable();
	}else{
		return false;
	}
}

void VRSAlignment::setAffinSeedToWhole(const ThreePointAlignment &alignPoint)
{
	m_WholeAlignPointList = alignPoint;
}

void VRSAlignment::setAffinSeedToEachPage(const QList<ThreePointAlignment> &alignPointList)
{
	m_EachPageAlignPointList = alignPointList;
}

QMatrix VRSAlignment::createAffin(const QPoint &ins1, const QPoint &ins2, const QPoint ins3,
								const QPoint &mac1, const QPoint &mac2, const QPoint mac3)
{
	/********** �A�t�B���ϊ�
	int		MX1,MY1,MX2,MY2,MX3,MY3;	�@�B���W
	int		IX1,IY1,IX2,IY2,IX3,IY3;	�摜���W
	double	a,b,c,d,e,f;
	���L�ϐ����g�p���ăA�t�B���ϊ������āA�摜���W���@�B���W�ɕϊ�����
	�^X�_�@�@�^a b c�_  �^x�_
	| Y | �� | d e f |�E| y |	���L�ϐ�����������
	�_1�^�@�@�_0 0 1�^  �_1�^	MX1 = IX1*a + IY1*b + c �E�E�E(1)
	�s����������				MY1 = IX1*d + IY1*e + f �E�E�E(2)
	X = a*x + b*y + c	  ��	MX2 = IX2*a + IY2*b + c �E�E�E(3)
	Y = d*x + e*y + f	  ��	MY2 = IX2*d + IY2*e + f �E�E�E(4)
								MX3 = IX3*a + IY3*b + c �E�E�E(5)
								MY3 = IX3*d + IY3*e + f �E�E�E(6)
	(1)��(3)����c��������
	(IX1-IX2)*a + (IY1-IY2)*b = MX1-MX2 �E�E�E(7)
	(3)��(5)����c��������
	(IX3-IX2)*a + (IY3-IY2)*b = MX3-MX2 �E�E�E(8)
	(7)��(8)����b��������
	�^IX1-IX2	IX3-IX2�_		 MX1-MX2   MX3-MX2
	|�������� - ��������| * a = �������� - ��������
	�_IY1-IY2	IY3-IY2�^		 IY1-IY2   IY3-IY2
	������
		�^MX1-MX2	MX3-MX2�_	�^			 (IY1-IY2)*(IY3-IY2)		 �_
	a = |�������� - ��������| * |������������������������������������������|
		�_IY1-IY2	IY3-IY2�^	�_(IX1-IX2)*(IY3-IY2)-(IX3-IX2)*(IY1-IY2)�^
	(7)����
		  �^IX1-IX2�_		MX1-MX2
	b = - |�������� | *a + ��������
		  �_IY1-IY2�^		IY1-IY2
	(1)����
	c = MX1 - IX1*a - IY1*b
	���l��
		�^MY1-MY2	MY3-MY2�_	�^			 (IY1-IY2)*(IY3-IY2)		 �_
	d = |�������� - ��������| * |������������������������������������������|
		�_IY1-IY2	IY3-IY2�^	�_(IX1-IX2)*(IY3-IY2)-(IX3-IX2)*(IY1-IY2)�^
		  �^IX1-IX2�_		MY1-MY2
	e = - |�������� | *d + ��������
		  �_IY1-IY2�^		IY1-IY2
	f = MY1 - IX1*d - IY1*e


	�⑫:
		 �^			 (IY1-IY2)*(IY3-IY2)		  �_
	�� = |������������������������������������������|
		 �_(IX1-IX2)*(IY3-IY2)-(IX3-IX2)*(IY1-IY2)�^
		   �^IX1-IX2�_
	�� = - |�������� |
		   �_IY1-IY2�^

	�Ƃ����΁A

		 �^MX1-MX2	MX3-MX2�_
	a =  |�������� - ��������| * ��
		 �_IY1-IY2	IY3-IY2�^
				  MX2-MX3
	b = �� * a + ��������
				  IY2-IY3
	c = MX1 - IX1*a - IY1*b
		�^MY1-MY2	MY3-MY2�_
	d = |�������� - ��������| * ��
		�_IY1-IY2	IY3-IY2�^
				  MY2-MY3
	e = �� * d + ��������
		  		  IY2-IY3
	f = MY1 - IX1*d - IY1*e
	**********/

	QMatrix matrix;

	qreal IX1 = ins1.x();
	qreal IY1 = ins1.y();
	qreal IX2 = ins2.x();
	qreal IY2 = ins2.y();
	qreal IX3 = ins3.x();
	qreal IY3 = ins3.y();

	qreal MX1 = mac1.x();
	qreal MY1 = mac1.y();
	qreal MX2 = mac2.x();
	qreal MY2 = mac2.y();
	qreal MX3 = mac3.x();
	qreal MY3 = mac3.y();

	/*
		 �^			 (IY1-IY2)*(IY3-IY2)		  �_
	�� = |������������������������������������������|
		 �_(IX1-IX2)*(IY3-IY2)-(IX3-IX2)*(IY1-IY2)�^
		   �^IX1-IX2�_
	�� = - |�������� |
		   �_IY1-IY2�^
	*/
	//qreal alpha = (IY1-IY2)*(IY3-IY2) / (IX1-IX2)*(IY3-IY2)-(IX3-IX2)*(IY1-IY2);
	//qreal beta = - (IX1-IX2) / (IY1-IY2);
	qreal alpha = (IX2-IX3)/(IY2-IY3) - (IX1-IX2)/(IY1-IY2);
	alpha = 1.0 / alpha;
	qreal beta = (-1) * (IX2-IX3)/(IY2-IY3);

	/*
		 �^MX1-MX2	MX3-MX2�_
	a =  |�������� - ��������| * ��
		 �_IY1-IY2	IY3-IY2�^
				 MX1-MX2
	b = �� *a + ��������
				 IY1-IY2
	c = -IX1*a - IY1*b + MX1
		�^MY1-MY2	MY3-MY2�_
	d = |�������� - ��������| * ��
		�_IY1-IY2	IY3-IY2�^
				   MY1-MY2
	e = - �� *d + ��������
		  		   IY1-IY2
	f = -IX1*d - IY1*e + MY1
	*/

	//qreal a = ((MX1-MX2)/(IY1-IY2) - (MX3-MX2)/(IY3-IY2)) * alpha;
	//qreal b = beta*a + (MX1-MX2)/(IY1-IY2);
	//qreal c = -IX1*a - IY1*b + MX1;
	//qreal d = ((MY1-MY2)/(IY1-IY2) - (MY3-MY2)/(IY3-IY2)) * alpha;
	//qreal e = -beta*d+(MY1-MY2)/(IY1-IY2);
	//qreal f = -IX1*d - IY1*e + MY1;

	qreal a = ( (MX2-MX3)/(IY2-IY3) - (MX1-MX2)/(IY1-IY2) ) * alpha;
	qreal b = (MX2-MX3)/(IY2-IY3) + beta*a;
	qreal c = MX1 - IX1*a - IY1*b;

	qreal d = ( (MY2-MY3)/(IY2-IY3) - (MY1-MY2)/(IY1-IY2) ) * alpha;
	qreal e = (MY2-MY3)/(IY2-IY3) + beta*d;
	qreal f = MY1 - IX1*d - IY1*e;

	matrix.setMatrix(	a, b,
						d, e,
						c, f);

	//qreal Mx1 = IX1 * a + IY1 * b + c;
	//qreal My1 = IX1 * d + IY1 * e + f;
	//qreal Mx2 = IX2 * a + IY2 * b + c;
	//qreal My2 = IX2 * d + IY2 * e + f;
	//qreal Mx3 = IX3 * a + IY3 * b + c;
	//qreal My3 = IX3 * d + IY3 * e + f;

	return matrix;
}

QMatrix VRSAlignment::getWholeAffinMatrix() const
{
	static QMatrix matrix = QMatrix();

	if(isWholeAffinMatrixEnable()==false){
		return QMatrix( 1, 0,
						0, 1,
						0, 0);
	}

	if(m_WholeAlignDataIsChanged==false){
		return matrix;
	}

	QPoint i[3] = {
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_First),
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Second),
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Third)
	};

	QPoint m[3] = {
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_First),
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Second),
		m_WholeAlignPointList.getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Third)
	};

	matrix = createAffin(i[0],i[1],i[2],m[0],m[1],m[2]);

	return matrix;
}

QList<QMatrix> VRSAlignment::getEachPageAffinMatrix() const
{
	QList<QMatrix> list;

	for(int i=0; i<m_EachPageAlignPointList.count(); i++){
		if(m_EachPageAlignPointList[i].isEnable()==true){
			list << createAffin(
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_First),
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Second),
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Third),
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_First),
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Second),
				m_EachPageAlignPointList[i].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Third)
			);
		}else{
			list << QMatrix(	1, 0,
								0, 1,
								0, 0);
		}
	}

	return list;
}

QMatrix VRSAlignment::getEachPageAffinMatrix(int page) const
{
	if(m_EachPageAlignPointList[page].isEnable()==true){
		return createAffin(
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_First),
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Second),
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_Inspection, Review::Alignment_Third),
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_First),
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Second),
				m_EachPageAlignPointList[page].getAlignmentPoint(Review::AlignmentSide_VRSMachine, Review::Alignment_Third)
			);
	}else{
		return QMatrix(	1, 0,
						0, 1,
						0, 0);
	}
}

bool VRSAlignment::ThreePointAlignment::isEnable() const
{
	bool ret = false;
	do{
		if(getInsAlignmentRect(Review::Alignment_First).isNull())break;
		if(getInsAlignmentRect(Review::Alignment_Second).isNull())break;
		if(getInsAlignmentRect(Review::Alignment_Third).isNull())break;
		
		if(getVRSAlignmentRect(Review::Alignment_First).isNull())break;
		if(getVRSAlignmentRect(Review::Alignment_Second).isNull())break;
		if(getVRSAlignmentRect(Review::Alignment_Third).isNull())break;

		if(getInsAlignmentPoint(Review::Alignment_First)==getInsAlignmentPoint(Review::Alignment_Second))break;
		if(getInsAlignmentPoint(Review::Alignment_Second)==getInsAlignmentPoint(Review::Alignment_Third))break;
		if(getInsAlignmentPoint(Review::Alignment_Third)==getInsAlignmentPoint(Review::Alignment_First))break;
		if(getVRSAlignmentPoint(Review::Alignment_First)==getVRSAlignmentPoint(Review::Alignment_Second))break;
		if(getVRSAlignmentPoint(Review::Alignment_Second)==getVRSAlignmentPoint(Review::Alignment_Third))break;
		if(getVRSAlignmentPoint(Review::Alignment_Third)==getVRSAlignmentPoint(Review::Alignment_First))break;

		if(getVRSAlignmentPoint(Review::Alignment_First).x()==getVRSAlignmentPoint(Review::Alignment_Third).x())break;
		if(getVRSAlignmentPoint(Review::Alignment_First).x()==getVRSAlignmentPoint(Review::Alignment_Second).x())break;
		if(getVRSAlignmentPoint(Review::Alignment_First).y()==getVRSAlignmentPoint(Review::Alignment_Third).y())break;
		if(getVRSAlignmentPoint(Review::Alignment_First).y()==getVRSAlignmentPoint(Review::Alignment_Second).y())break;

		ret = true;
	}while(false);

	return ret;
}

void VRSAlignment::ThreePointAlignment::setAlignmentPoint(Review::AlignmentSide side, Review::AlignmentNo PointNo, const QRect &rect)
{
	switch(side){
	case Review::AlignmentSide_Inspection:
		switch(PointNo){
		case Review::Alignment_First:
			getInsAlignment().setFirst(rect);
			break;
		case Review::Alignment_Second:
			getInsAlignment().setSecond(rect);
			break;
		case Review::Alignment_Third:
			getInsAlignment().setThird(rect);
			break;
		default:
			break;
		}
	case Review::AlignmentSide_VRSMachine:
		switch(PointNo){
		case Review::Alignment_First:
			getVRSAlignment().setFirst(rect);
			break;
		case Review::Alignment_Second:
			getVRSAlignment().setSecond(rect);
			break;
		case Review::Alignment_Third:
			getVRSAlignment().setThird(rect);
			break;
		default:
			break;
		}
	}
};

QPair<QPoint, QPoint> VRSAlignment::ThreePointAlignment::getAlignmentPointPair(Review::AlignmentNo PointNo) const
{
	switch(PointNo){
	case Review::Alignment_First:
		return firstPoint();
		break;
	case Review::Alignment_Second:
		return secondPoint();
		break;
	case Review::Alignment_Third:
		return thirdPoint();
		break;
	default:
		return QPair<QPoint, QPoint>();
		break;
	}
}

QPoint VRSAlignment::ThreePointAlignment::getAlignmentPoint(Review::AlignmentSide side, Review::AlignmentNo PointNo) const
{
	QPair<QPoint, QPoint> pp = getAlignmentPointPair(PointNo);
	switch(side){
	case Review::AlignmentSide_Inspection:
		return pp.first;
		break;
	case Review::AlignmentSide_VRSMachine:
		return pp.second;
		break;
	default:
		return QPoint();
		break;
	}
}

QRect VRSAlignment::ThreePointAlignment::getInsAlignmentRect(Review::AlignmentNo PointNo) const
{
	switch(PointNo){
	case Review::AlignmentNo::Alignment_First:
		return getInsAlignment().first();
		break;
	case Review::AlignmentNo::Alignment_Second:
		return getInsAlignment().second();
		break;
	case Review::AlignmentNo::Alignment_Third:
		return getInsAlignment().third();
		break;
	default:
		return QRect();
		break;
	}
	return QRect();
}

QRect VRSAlignment::ThreePointAlignment::getVRSAlignmentRect(Review::AlignmentNo PointNo) const
{
	switch(PointNo){
	case Review::AlignmentNo::Alignment_First:
		return getVRSAlignment().first();
		break;
	case Review::AlignmentNo::Alignment_Second:
		return getVRSAlignment().second();
		break;
	case Review::AlignmentNo::Alignment_Third:
		return getVRSAlignment().third();
		break;
	default:
		return QRect();
		break;
	}
	return QRect();
}

QPoint VRSAlignment::ThreePointAlignment::getInsAlignmentPoint(Review::AlignmentNo PointNo) const
{
	QRect rect = getInsAlignmentRect(PointNo);
	QPoint ret;
	if(rect.isValid()==true){
		ret = rect.center();
	}
	return ret;
}

QPoint VRSAlignment::ThreePointAlignment::getVRSAlignmentPoint(Review::AlignmentNo PointNo) const
{
	QRect rect = getVRSAlignmentRect(PointNo);
	QPoint ret;
	if(rect.isValid()==true){
		ret = rect.center();
	}
	return ret;
}

void VRSAlignment::ThreePointAlignment::setInsAlignmentRect(Review::AlignmentNo PointNo, const QRect &rect)
{
	Review::ThreeValue<QRect> setVal = getInsAlignment();
	switch(PointNo){
	case Review::AlignmentNo::Alignment_First:
		setVal.setFirst(rect);
		break;
	case Review::AlignmentNo::Alignment_Second:
		setVal.setSecond(rect);
		break;
	case Review::AlignmentNo::Alignment_Third:
		setVal.setThird(rect);
		break;
	default:
		return;
		break;
	}
	setInsAlignment(setVal);
}

void VRSAlignment::ThreePointAlignment::setVRSAlignmentRect(Review::AlignmentNo PointNo, const QRect &rect)
{
	Review::ThreeValue<QRect> setVal = getVRSAlignment();
	switch(PointNo){
	case Review::AlignmentNo::Alignment_First:
		setVal.setFirst(rect);
		break;
	case Review::AlignmentNo::Alignment_Second:
		setVal.setSecond(rect);
		break;
	case Review::AlignmentNo::Alignment_Third:
		setVal.setThird(rect);
		break;
	default:
		return;
		break;
	}
	setVRSAlignment(setVal);
}