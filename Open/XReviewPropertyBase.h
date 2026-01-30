/*
 * Copyright (C) 2017
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

#pragma once

#include <QObject>
#include <QString>
#include <QColor>
#include <QDir>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QVector3D>

#include "XReviewSettingFileSectionReader.h"

class AbstructProperty : public QObject
{
protected:
	AbstructProperty(QObject *parent=NULL):QObject(parent){};

// �p�����ŃI�[�o�[���C�h�K�{
public:
	virtual void initialize(void)=0;

public:
	virtual QString baseName(void) const =0;
	virtual QString sectionName(void) const =0;
	virtual QString filename(void) const =0;

public:
	QString filePath(void) const {
		return baseName() + "/" + sectionName() + ".dat";
	};

public:
	bool save(){
		SettingFileReader reader;
		reader.setFilename(filePath());
		reader.setSectionList(toList());
		return reader.save();
	};

	bool load(){
		SettingFileReader reader;
		reader.setFilename(filePath());
		if(reader.load()==false){
			return false;
		}
		return fromBuffer( reader.sectionBuffer(sectionName()) );
	};

public:
	virtual bool fromBuffer(const SectionBuffer &buffer)=0;
	virtual SectionBuffer toBuffer(void) const =0;// �o�b�t�@����

	// �I�[�o�[���C�h���p
public:
	virtual bool fromList(const SectionBufferList &list){// ���X�g���畜��
			int index = indexOf(list, sectionName());
		if(index==-1){
			return false;
		}

		return fromBuffer(list[index]);
	};
	virtual bool fromFile(const QString &filename){
		SectionBufferList list;
		SettingFileReader::load(filename, list);
		for(int i=0; i<list.count(); i++){
			if(fromBuffer(list[i])==true){
				return true;
			}
		}
		return false;
	};
	virtual bool fromFile(void){
		QString dirPath = QDir::currentPath() + "/" + baseName();

		QDir dir;

		dir.mkpath(dirPath);

		return fromFile(dirPath + "/" + sectionName() + ".dat");
	};

	virtual SectionBufferList toList(void) const { SectionBufferList list; list.append(toBuffer()); return list; };
public:
	// �ʏ���QString.toXXX�ōς܂���
	// QColor
	static QColor toColor(const QString &val){ return QColor(val); };
	static QString fromColor(const QColor &color){ return color.name(); };

	// bool
	static bool toBool(const QString &val){ return (val=="true"); };
	static QString fromBool(bool b){ return (b==true) ? "true" : "false"; };

	static QPoint toPoint(const QString &val){ QStringList list = val.split(','); if(list.count()!=2){return QPoint();}else{ return QPoint(list[0].toInt(), list[1].toInt()); } };
	static QString fromPoint(const QPoint &val){ return QString("%1,%2").arg(val.x()).arg(val.y()); };

	static QVector3D toVector3D(const QString &val){ QStringList list = val.split(','); if(list.count()!=3){return QVector3D();}else{ return QVector3D(list[0].toInt(), list[1].toInt(), list[2].toInt()); } };
	static QString fromVector3D(const QVector3D &val){ return QString("%1,%2,%3").arg(val.x()).arg(val.y()).arg(val.z()); };

	static QSize toSize(const QString &val){ QStringList list = val.split(','); if(list.count()!=2){return QSize();}else{ return QSize(list[0].toInt(), list[1].toInt()); } };
	static QString fromSize(const QSize &val){ return QString("%1,%2").arg(val.width()).arg(val.height()); };

	static QRect toRect(const QString &val){ QStringList list = val.split(','); if(list.count()!=4){return QRect();}else{ return QRect(list[0].toInt(), list[1].toInt(), list[2].toInt(), list[3].toInt()); }; };
	static QString fromRect(const QRect &val){ return QString("%1,%2,%3,%4").arg(val.left()).arg(val.top()).arg(val.width()).arg(val.height()); };

	static int indexOf(const SectionBufferList &list, const QString &sectionName_){
		for(int i=0; i<list.count(); i++){
			if(list[i].sectionName()==sectionName_){
				return i;
			}
		}

		return -1;
	};

	// String�Ή�
	static QString toString(const QString &str)	{	return str;	}
	static QString fromString(const QString &s)	{	return s;	}

	// ���X�g�Ή�
	template<class T>
	static QList<T> toList(const QString &str);

	template<class T>
	static QString fromList(const QList<T> &list);

	// int
	template<>
	static QList<int> toList(const QString &str){
		QStringList strList = str.split(',');
		QList<int> retList;

		for(int i=0; i<strList.count(); i++){
			retList << strList[i].toInt();
		}

		return retList;
	};

	template<>
	static QString fromList<int>(const QList<int> &list){
		if(list.isEmpty()==true){
			return QString();
		}

		QString ret = QString::number(list.first());

		for(int i=1; i<list.count(); i++){
			ret += "," + QString::number(list[i]);
		}

		return ret;
	};

	// QColor
	template<>
	static QList<QColor> toList(const QString &str){
		QStringList strList = str.split(',');
		QList<QColor> retList;

		for(int i=0; i<strList.count(); i++){
			retList << toColor(strList[i]);
		}

		return retList;
	};

	template<>
	static QString fromList<QColor>(const QList<QColor> &list){
		if(list.isEmpty()==true){
			return QString();
		}

		QString ret = list.first().name();

		for(int i=1; i<list.count(); i++){
			ret += "," + fromColor(list[i]);
		}

		return ret;
	};
	
	// QPoint
	template<>
	static QList<QPoint> toList(const QString &str){
		if(str.isEmpty()==true){
			return QList<QPoint>();
		}

		QStringList strList = str.split(";");
		QList<QPoint> retList;

		for(int i=0; i<strList.count(); i++){
			retList << toPoint(strList[i]);
		}

		return retList;
	};

	template<>
	static QString fromList<QPoint>(const QList<QPoint> &list){
		if(list.isEmpty()==true){
			return QString();
		}

		QStringList strList;

		for(int i=0; i<list.count(); i++){
			strList << fromPoint(list[i]);
		}

		return strList.join(";");
	};

	// QRect
	template<>
	static QList<QRect> toList(const QString &str){
		if(str.isEmpty()==true){
			return QList<QRect>();
		}

		QStringList strList = str.split(";");
		QList<QRect> retList;

		for(int i=0; i<strList.count(); i++){
			retList << toRect(strList[i]);
		}

		return retList;
	};

	template<>
	static QString fromList<QRect>(const QList<QRect> &list){
		if(list.isEmpty()==true){
			return QString();
		}

		QStringList strList;

		for(int i=0; i<list.count(); i++){
			strList << fromRect(list[i]);
		}

		return strList.join(";");
	};

};

// �t�@�C���Ő������ꂽQString�y�A�̃f�[�^���ړI�̃f�[�^�ۑ��Ώۂ֎󂯓n�����߂̃p�C�v�N���X
template<class T>
class PropertyBase : public AbstructProperty
{
private:
	PropertyBase(){};

public:
	virtual ~PropertyBase(void){};

public:
	void initialize(void){};

// �e���v���[�g�ŃI�[�o�[���C�h�K�{
public:
	virtual QString baseName(void) const =0;
	virtual QString sectionName(void) const =0;
	virtual QString filename(void) const =0;

public:
	virtual bool fromBuffer(const SectionBuffer &buffer)=0;	// �o�b�t�@�����č\�z
	virtual SectionBuffer toBuffer(void) const =0;			// �o�b�t�@�𐶐�
	virtual bool fromInstance(T *instance)=0;				// �ΏۃC���X�^���X�����擾
	virtual bool toInstance(T *instance) const =0;			// �ΏۃC���X�^���X�֏�������
};