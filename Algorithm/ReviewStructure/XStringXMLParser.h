/*
 * Copyright (C) 2018
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

#include <QtXml/QDomElement>

// QString ������XML���̃p�[�T�[�̊����N���X
// �p������analyze�����`���A�i�[�����f�[�^�ɉ����ă����o�ϐ�����������

class StringXMLParser
{
public:
	StringXMLParser():errMsg(/**/""){};
	virtual ~StringXMLParser(){};

public:
	bool isError(){ return !errMsg.isEmpty(); };
	QString getErrorMessage(){ return errMsg; };
	bool setContent(const QString &src){
		clear();

		QDomDocument doc;
		if(doc.setContent(src)==false)
			return false;

		QDomElement elem = doc.documentElement();

		analyze(elem);

		return errMsg.isEmpty();
	};

public:
	virtual void analyze(QDomElement &elem)=0;
	virtual void clear(){ errMsg.clear(); };
	static QString getCurrentTagText(const QDomElement &elem){
		return elem.firstChild().toText().data();
	};

protected:
	QString errMsg;
};