/*
 * Copyright (C) 2023
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



#ifndef MTXMLLIB_H
#define MTXMLLIB_H

#include "mtxmllib_global.h"
#include <QDateTime>
#include <QString>
#include <QIODevice>
#include <QFile>
#include <QThread>
#include <QMutex>

#include "NList.h"

#pragma	pack(push)
#pragma	pack(1)


class	XMLTag;
class	XMLElement;
class	XMLMainStock;

class	StringStokerItem : public NPList<StringStokerItem>
{
	char	*Str;
public:
	int		IndexCount;

	StringStokerItem(void);
	StringStokerItem(char *str);
	~StringStokerItem(void);

	char	*GetString(void){	return Str;	}
};

class	StringStoker
{
	NPListPack<StringStokerItem>	Data[65536];
	QMutex							DataMutex;
public:
	StringStoker(void){}

	StringStokerItem	*GetItem(char *str);
	StringStokerItem	*GetItem(QString &str);
	StringStokerItem	*GetPointer(StringStokerItem *nowpointer);

	StringStokerItem	*RemoveReference(StringStokerItem *ref);
};

class	XMLOrderList : public NPList<XMLOrderList>
{
public:
	char	*TagAttrName;
	bool	Ascendant;
};

//=================================================================

class	XMLTagAttr : public NPList<XMLTagAttr>
{
public:
	XMLTag					*Parent;
	StringStokerItem		*AttrName;
	union{
		StringStokerItem		*AttrData;
		qint64					iAttrData;
	};
	bool					IsNumOK;
	enum{
		_Equal			=1
		,_GreaterEqual	=2
		,_SmallEqual	=3
		,_Greater		=4
		,_Small			=5
	}CompareType;

	XMLTagAttr(XMLTag *parent){	AttrName=NULL; Parent=parent;	iAttrData=0; IsNumOK=true; CompareType=_Equal;}
	~XMLTagAttr(void);

	char	*Analyze(char *fp);
	int		MakeStr(char buff[] ,int buffsize);
	bool	Delete(void);

	XMLTagAttr	&operator=(XMLTagAttr &src);
	bool	hCompare(XMLTagAttr &src);	//�������葊�肪�傫�����͏������Ŕ��f
	bool	operator==(XMLTagAttr &src);
	bool	operator>(XMLTagAttr &src);			//�s�����̏���
	bool	operator>=(XMLTagAttr &src);
	bool	operator<(XMLTagAttr &src);
	bool	operator<=(XMLTagAttr &src);

	XMLMainStock	*GetTop();
	int 	Size(void);

	bool	Save(QIODevice &Buff);
	bool	Load(QIODevice &Buff);
};

class	XMLTag
{
public:
	XMLElement				*Parent;
	StringStokerItem		*TagName;
	NPListPack<XMLTagAttr>	Attrs;

	XMLTag(XMLElement *parent){	TagName=NULL;	Parent=parent;	}
	~XMLTag(void);

	char	*Analyze(char *fp,bool &Finished);
	int		MakeStr(char buff[] ,int buffsize);
	bool	Delete(void);

	XMLMainStock	*GetTop();
	XMLTag	&operator=(XMLTag &src);
	bool	Match(XMLTag &MatchPoint, XMLElement *e);
	bool	Matched(XMLTag &MatchPoint);
	bool	AddTag(XMLTag &Src);

	int		Size(void);
	bool	Save(QIODevice &Buff);
	bool	Load(QIODevice &Buff);
	char	*GetTagName(void);

	bool	CheckNextTag(XMLElement *Src,QList<XMLTag*> MatchPoint);
	bool	FindTagAttr(XMLElement *Src,QString TagName,QString AttrName,QString &strRet);
	bool	AnalyzeXMLElement(char *fp,QString strTagName,QString strAttrName,QString &strRet);
private:
	char	*GotoTagEnd(char *fp,char *buff);
};

class	XMLElement : public NPList<XMLElement>
{
public:
	qint64					ID;
	XMLElement				*Parent;
	XMLTag					StartTag;
	//XMLTag					LastTag;
	NPListPack<XMLElement>	Datas;
	//QString				StrData;
	StringStokerItem		*StrData;
	int			InsertedNumb;	//�e��Datas�̒��̔ԍ�

	XMLElement(XMLElement *parent);
	~XMLElement(void);
	char	*Analyze(char *fp);
	int		MakeStr(char buff[] ,int buffsize);
	bool	Append(char *xmlStr);
	bool	Delete(void);

	XMLElement	&operator=(XMLElement &src);
	XMLMainStock	*GetTop();
	void	RebuildInsertedNumb(int InsertedNumb);

	int		Size(void);

	XMLElement	*SearchByID(qint64 ID);

	bool	Save(QIODevice &Buff);
	bool	Load(QIODevice &Buff);

	XMLElement *FindFirstByTag(char *tagName);
	XMLElement *FindLastByTag(char *tagName);
	XMLElement *FindNextByTag(XMLElement *PrevData, char *tagName);

	bool	AddElement(XMLElement &Src);

	virtual	XMLElement *MatchFirst(XMLTag &MatchPoint);
	virtual	XMLElement *MatchFirst(XMLElement **Answer ,XMLTag &MatchPoint ,int iParent);
	virtual	XMLElement	*MatchNext(XMLTag &MatchPoint,XMLElement *PrevData);
	virtual	XMLElement	*MatchNext(XMLTag &MatchPoint,XMLElement *PrevData ,XMLElement **AnswerPrev, int iParent);
	void		ErrorLog(int &Num);

	XMLElement	*SearchAndMatch(XMLElement &SearchElement);
	bool	MatchOnly(XMLElement &SearchElement);

private:
	XMLElement	*MatchNextFromChild(XMLTag &MatchPoint, int ChildInsertedNumb);
	XMLElement	*FindFirstByTagRoot(char *tagName);
	XMLElement	*FindLastByTagRoot(char *tagName);

	XMLElement	*MatchFirstRoot(XMLTag &MatchPoint);
	XMLElement	*FindNextByTagFromChild(char *tagName, int ChildInsertedNumb);
	XMLElement	*MatchNextRoot(XMLTag &MatchPoint,XMLElement *PrevData);
};

class	XMLElementWithIncrementalID : public XMLElement
{
public:
	XMLElementWithIncrementalID(XMLElement *parent);
	XMLElementWithIncrementalID(XMLElement *parent,int);
};

//------------------------------------------------

class	XMLThreadCommandItemBase : public NPList<XMLThreadCommandItemBase>
{
public:
	XMLThreadCommandItemBase(void){}
	virtual	~XMLThreadCommandItemBase(void){}

	virtual	void	Run(void)=0;
};

class	XMLThreadCommandItemDelete : public XMLThreadCommandItemBase
{
public:
	XMLElement	*Item;

	XMLThreadCommandItemDelete(XMLElement *item){	Item=item;	}

	virtual	void	Run(void);
};

class	XMLThreadCommander : public QThread
{
	NPListPack<XMLThreadCommandItemBase>	CommandData;
	QMutex	DataMutex;
public:
	volatile	bool	FinishMode;

	XMLThreadCommander(void){	FinishMode=false;	}
	virtual void run ();

	void	AppendList(XMLThreadCommandItemBase *d);
private:
	XMLThreadCommandItemBase	*PopFromList(void);
};

//------------------------------------------------

class	XMLMainStock : public XMLElement
{
	static	StringStoker		StrStocker;
public:
	qint64						BaseID;
	QList<XMLTag*>				*MatchXMLTag;
	XMLThreadCommander			XMLThreadCommand;

#if 1 // 20100223
	QString DDB;
#endif

	//XMLMainStock(QString fileName);
	XMLMainStock(char *fileName);
	~XMLMainStock(void);

	static	StringStoker	&GetStringStoker(void);
	char	*GetFileName(void);
	bool	Create(void);
	bool	UpdateToStream(void);
	bool	LoadFromStream(void);
	void	XMLGetData(const QByteArray &Info, QString &NGJ);//Delete�����̒���NGJ�̏������Ԃ�
	bool	Append(qint64 AppID, char *xmlStr);
	//bool	Delete(qint64 DelID, QString &Data);//Delete����ID,NGJ���Ԃ�
	bool	Delete(qint64 DelID, QString &Data);

private:
	//void	CreateDeletedList(int filesize);
};

#pragma	pack(pop)


#endif // MTXMLLIB_H