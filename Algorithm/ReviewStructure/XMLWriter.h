/*
 * Copyright (C) 2022
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

#include <QThread>
#include <QMutex>
#include <QList>
#include "XReviewCommon.h"

class XMLServerHandle;
class XMLOperationHandle;
class	ReviewPIBase;

class stReqXMLWrite
{
public:
	enum WriteFlag{
		WriteChecked	=	0x01,
		WriteFKey		=	0x02,
		WriteAll		=	WriteChecked|WriteFKey
	};
public:
	stReqXMLWrite(int x=-1, int y=-1, bool checked=false, Review::FKey key=Review::NoFKey, int flags=WriteFlag::WriteAll)
	{
		m_x = x;
		m_y = y;
		m_isChecked = checked;
		m_FKey = key;
		m_flags = flags;
	};
	stReqXMLWrite(const stReqXMLWrite &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_isChecked = other.m_isChecked;
		m_FKey = other.m_FKey;
		m_flags = other.m_flags;
	};

	bool operator==(const stReqXMLWrite &other) const{
		if(x()==other.x() &&
			y()==other.y() &&
			isChecked()==other.isChecked() &&
			FKey()==other.FKey() &&
			flags()==other.flags()){
			return true;
		}else{
			return false;
		}
	};

public:
	void setX(int x){ m_x = x; };
	void setY(int y){ m_y = y; };
	void setChecked(bool checked){ m_isChecked = checked; };
	void setFKey(Review::FKey key){ m_FKey = key; };
	void setFlags(int flags){ m_flags = flags; };
	int x(void) const { return m_x; };
	int y(void) const { return m_y; };
	bool isChecked(void) const { return m_isChecked; };
	Review::FKey FKey(void) const { return m_FKey; };
	int flags() const { return m_flags; };
private:
	int m_x;
	int m_y;
	bool m_isChecked;
	Review::FKey m_FKey;
	int m_flags;


public:
	bool operator==(const stReqXMLWrite &other){
		if(x()==other.x() &&
			y()==other.y() &&
			isChecked()==other.isChecked() &&
			FKey()==other.FKey() &&
			flags()==other.flags()){
			return true;
		}else{
			return false;
		}
	};
};


class ReqXMLWrite : public QList<stReqXMLWrite >
{
public:
	ReqXMLWrite(int InspectID=-1, int Phase=-1, int Page=-1, QString TableName=/**/"")
		:m_InspectID(InspectID),m_Phase(Phase),m_Page(Page),m_TableName(TableName){};
	ReqXMLWrite(const ReqXMLWrite &other)
		:m_InspectID(other.m_InspectID),m_Phase(other.m_Phase),m_Page(other.m_Page),m_TableName(other.m_TableName){
		for(int i=0; i<other.count(); i++){
			addItem(other[i]);
		}
	};

	bool	operator==(const ReqXMLWrite &other) const{
		if(getInspectID()==other.getInspectID() &&
			getPhase()==other.getPhase() &&
			getPage()==other.getPage() &&
			getTableName()==other.getTableName() &&
			count()==other.count()){
			for(int i=0; i<count(); i++){
				if(!((*this)[i]==other[i])){
					return false;
				}
			}
			return true;
		}else{
			return false;
		}
	};

public:
	void addItem(int x, int y, bool isChecked, Review::FKey fkey, int flags=stReqXMLWrite::WriteAll){
		stReqXMLWrite item;
		item.setX(x);
		item.setY(y);
		item.setChecked(isChecked);
		item.setFKey(fkey);
		item.setFlags(flags);
		append(item);
	};
	void addItem( const stReqXMLWrite &item){
		append(item);
	};
	void setInspectID(int id){ m_InspectID = id; };
	void setPhase(int phase){ m_Phase = phase; };
	void setPage(int page){ m_Page = page; };
	void setTableName(QString TableName){ m_TableName = TableName; };
	
	int getInspectID(void) const { return m_InspectID; };
	int getPhase(void) const { return m_Phase; };
	int getPage(void) const { return m_Page; };
	QString getTableName(void) const { return m_TableName; };

private:
	int m_InspectID;
	int m_Phase;
	int m_Page;
	QString m_TableName;
};

class XMLWriter : public QThread
{
	ReviewPIBase	*ReviewPIBasePointer;
public:
	XMLWriter(ReviewPIBase *Pointer ,QObject *parent=NULL)
		:QThread(parent)
		,ReviewPIBasePointer(Pointer)
		,m_stop(false)
		,m_flash(false)
		,m_XMLServer(NULL)
		,m_IPAddress(/**/"localhost")
		,m_Port(12345)
	{};

protected:
	void run();

public:
	bool open(QString Address, int port);
	bool open();
	void push_back(ReqXMLWrite item);
	void stop(){ m_stop = true; };
	void setReady(){ m_stop = false; };
	void restart(){ stop(); wait(); setReady(); start(); };
	void setFlash(bool flash){ QMutexLocker locker(&m_Mutex); m_flash = flash; };

	void setIPAddress(QString address){ QMutexLocker locker(&m_Mutex);  m_IPAddress = address; };
	void setPort(int port){ QMutexLocker locker(&m_Mutex); m_Port = port; };
	void set(QString address, int port);

	QString getIPAddress() const { return m_IPAddress; };
	int getPort() const { return m_Port; };

	bool isEmpty(){ QMutexLocker locker(&m_Mutex); return m_ReqWriteList.isEmpty(); };
	int count(){ QMutexLocker locker(&m_Mutex); return m_ReqWriteList.count(); };

	QList<ReqXMLWrite > getReqXMLList();

private:
	bool isEnable(XMLOperationHandle *xmlOpeHdl);
	inline bool write(XMLOperationHandle *hdl, const ReqXMLWrite &reqItem);

private:
	QMutex m_Mutex;
	QMutex m_MutexServer;
	volatile bool m_stop;
	volatile bool m_flash;

	QList<ReqXMLWrite > m_ReqWriteList;

	XMLServerHandle *m_XMLServer;
	QString m_IPAddress;
	int m_Port;
};
