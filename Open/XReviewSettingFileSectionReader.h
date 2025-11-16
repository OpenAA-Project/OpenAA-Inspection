#pragma once

#include <QString>
#include <QPair>
#include <QList>

// 設定ファイルの書き込み、読み込みを行うクラス
//
// 設定ファイルは以下のテキストフォーマットに従う

// [section]
// @name=value
// @name2=value2
//
// [section2]
// @name3=value3
// @name4=value4
// @name5=value5
// ...

// 1セクションのデータを保持するバッファ
class SectionBuffer
{
public:
	typedef QPair<QString, QString> StrPair;
	typedef QList<StrPair> StrPairList;

public:
	SectionBuffer(const QString &sectionName=/**/"", const StrPairList &list=StrPairList());

public:
	void clear();
	bool isValid() const;

public:
	void setSectionName(const QString &sectionName);
	QString sectionName() const;

	void setValue(const QString &key, const QString &value);
	QString value(const QString &key) const;
	bool hasValue(const QString &key) const;

	void setValueList(const StrPairList &);
	StrPairList valueList() const;

private:
	QString m_sectionName;
	StrPairList m_valueList;
};

typedef QList<SectionBuffer> SectionBufferList;

// ファイルを全検索して、SectionBufferのリストを作成するクラス
class SettingFileReader
{
public:
	SettingFileReader(const QString &filename=/**/"");

public:
	void clear(void);
	
public:// static save & load
	static bool save(const QString &filename, const SectionBufferList &list);
	static bool load(const QString &filename, SectionBufferList &list);

public:// instance save & load
	bool save(const QString &) const;
	bool save() const;

	bool load(const QString &);
	bool load();

public:// getset buffer
	void setFilename(const QString &filename);
	QString filename() const;

	void setSectionList(const SectionBufferList &filename);
	SectionBufferList sectionList() const;
	SectionBuffer sectionBuffer(const QString &sectionName);

private:// member variable
	QString m_filename;
	QList<SectionBuffer> m_sectionList;
};