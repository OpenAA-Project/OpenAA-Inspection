/*
 * Copyright (C) 2016
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

#include <QString>
#include <QPair>
#include <QList>

// �ݒ��t�@�C���̏������݁A�ǂݍ��݂��s���N���X
//
// �ݒ��t�@�C���͈ȉ��̃e�L�X�g�t�H�[�}�b�g�ɏ]��

// [section]
// @name=value
// @name2=value2
//
// [section2]
// @name3=value3
// @name4=value4
// @name5=value5
// ...

// 1�Z�N�V�����̃f�[�^���ێ������o�b�t�@
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

// �t�@�C�����S�������āASectionBuffer�̃��X�g���쐬�����N���X
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