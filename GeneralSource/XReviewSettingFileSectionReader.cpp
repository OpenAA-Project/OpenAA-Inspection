#include "XReviewSettingFileSectionReader.h"

#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QRegularExpression>
#include <QTextStream>

SectionBuffer::SectionBuffer(const QString &sectionName, const StrPairList &list)
{
	clear();

	setSectionName(sectionName);
	setValueList(list);
}

void SectionBuffer::clear()
{
	setSectionName(QString());
	setValueList(StrPairList());
}

bool SectionBuffer::isValid() const
{
	if(sectionName().isEmpty() == true ||
		sectionName().isNull() == true){
		return false;
	}else{
		return true;
	}
}


void SectionBuffer::setSectionName(const QString &sectionName)
{
	m_sectionName = sectionName;
}

QString SectionBuffer::sectionName() const
{
	return m_sectionName;
}

void SectionBuffer::setValue(const QString &key, const QString &value)
{
	StrPairList list = valueList();
	for(StrPairList::Iterator it=list.begin(); it!=list.end(); it++){
		if(it->first==key){
			it->second = value;
			setValueList(list);
			return;
		}
	}
	list.append(StrPair(key, value));
	setValueList(list);
}
QString SectionBuffer::value(const QString &key) const
{
	StrPairList list = valueList();
	for(StrPairList::ConstIterator it=list.constBegin(); it!=list.constEnd(); it++){
		if(it->first==key){
			return it->second;
		}
	}
	return QString();
}

bool SectionBuffer::hasValue(const QString &key) const
{
	StrPairList list = valueList();
	for(StrPairList::ConstIterator it=list.constBegin(); it!=list.constEnd(); it++){
		if(it->first==key){
			return true;
		}
	}
	return false;
}

void SectionBuffer::setValueList(const StrPairList &list)
{
	m_valueList = list;
}

SectionBuffer::StrPairList SectionBuffer::valueList() const
{
	return m_valueList;
}

SettingFileReader::SettingFileReader(const QString &filename_)
{
	clear();
	setFilename(filename_);
}

void SettingFileReader::clear()
{
	setFilename(QString());
}

// static
bool SettingFileReader::save(const QString &filename_, const SectionBufferList &list_)
{
	QFile file(filename_);
	QFileInfo info(filename_);
	QDir dir;

	// ディレクトリがなければ作成する
	QString fileDirName = info.absolutePath();
	dir.setPath(fileDirName);
	if(dir.isReadable()==false){
		dir.mkpath(fileDirName);
	}

	if(file.open(QIODevice::WriteOnly)==false){
		return false;
	}else{
		QTextStream stream(&file);
		for(SectionBufferList::ConstIterator it=list_.begin(); it!=list_.end(); it++){
			stream << '[' << it->sectionName() << ']' << Qt::endl;
			SectionBuffer::StrPairList pList = it->valueList();
			for(SectionBuffer::StrPairList::ConstIterator pit=pList.begin(); pit!=pList.end(); pit++){
				stream << pit->first << '=' << pit->second << Qt::endl;
			}
		}
		return true;
	}
}

// static
bool SettingFileReader::load(const QString &filename_, SectionBufferList &list_)
{
	QFile file(filename_);
	if(file.open(QIODevice::ReadOnly)==false){
		return false;
	}else{
		QTextStream stream(&file);
		QRegularExpression sectionExp(".*" + QRegularExpression::escape("[") + "(.*)" + QRegularExpression::escape("]") + ".*");
		QRegularExpression pairExp("(.*)=(.*)");
		SectionBuffer currentBuff;

		list_.clear();
		while(stream.atEnd()==false){
			QString line = stream.readLine();

			if(sectionExp.match(line).hasMatch()==true){
				if(currentBuff.isValid()==true){
					list_.append(currentBuff);
				}
				currentBuff.clear();
				currentBuff.setSectionName(sectionExp.cap(1));
			}else if(pairExp.match(line).hasMatch()==true){
				currentBuff.setValue(pairExp.cap(1), pairExp.cap(2));
			}else{
				// skip
			}
		}
		// 最後のセクションを保存
		if(currentBuff.isValid()==true){
			list_.append(currentBuff);
		}
		return true;
	}
}

bool SettingFileReader::save(const QString &filename_) const
{
	return save(filename_, sectionList());
}

bool SettingFileReader::save() const
{
	return save(filename(), sectionList());
}

bool SettingFileReader::load(const QString &filename_)
{
	SectionBufferList list;
	if(load(filename_, list)==true){
		setFilename(filename_);
		setSectionList(list);
		return true;
	}else{
		return false;
	}
}
bool SettingFileReader::load()
{
	SectionBufferList list;
	if(load(filename(), list)==true){
		setSectionList(list);
		return true;
	}else{
		return false;
	}
}

void SettingFileReader::setFilename(const QString &filename_)
{
	m_filename = filename_;
}

QString SettingFileReader::filename() const
{
	return m_filename;
}

void SettingFileReader::setSectionList(const SectionBufferList &list)
{
	m_sectionList = list;
}

SectionBufferList SettingFileReader::sectionList() const
{
	return m_sectionList;
}

SectionBuffer SettingFileReader::sectionBuffer(const QString &sectionName)
{
	SectionBuffer ret;
	const SectionBufferList list = sectionList();
	for(int i=0; i<list.count(); i++){
		if(list[i].sectionName()==sectionName){
			ret = list[i];
			break;
		}
	}

	return ret;
}