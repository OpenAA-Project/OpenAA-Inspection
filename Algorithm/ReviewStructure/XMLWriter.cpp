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

#include "XMLWriter.h"
#include "XReviewStructure.h"
#include "ReviewStructurePacket.h"
#include "ui_XMLServerCommForm.h"
#include "XDataInLayer.h"


void XMLWriter::push_back(ReqXMLWrite item)
{
	m_Mutex.lock();
	m_ReqWriteList.push_back(item);
	m_Mutex.unlock();

	//qDebug() << "QThread:Item is appended.";
}

bool XMLWriter::isEnable(XMLOperationHandle *xmlOpeHdl)
{
	if(xmlOpeHdl==NULL){
		return false;
	}else{
		return xmlOpeHdl->GetServer()->GetState();
	}
}

bool XMLWriter::open(QString Address, int port){
	if(m_IPAddress!=Address || m_Port!=port){
		m_IPAddress = Address;
		m_Port=port;
		return open();
	}else{
		return m_XMLServer->Open();
	}
}

bool XMLWriter::open()
{
	QMutexLocker locker( &m_Mutex );
	if(isRunning()==true){
		stop();
		wait();
		setReady();
	}

	{
		QMutexLocker locker(&m_MutexServer);
		if(m_XMLServer==NULL){
			m_XMLServer = new XMLServerHandle(m_IPAddress, m_Port, this);
		}else{
			// �Z�b�g
			m_XMLServer->Close();
			m_XMLServer->Set(m_IPAddress, m_Port);
		}

		// ���݂̐ݒ��ŃI�[�v���o�����Ȃ��I��
		if(m_XMLServer->Open()==true){
			return true;
		}
	}

	return false;

	//QDialog *xmlCommDlg = new QDialog;
	//Ui::XMLServerCommClass ui;
	//ui.setupUi(xmlCommDlg);

	//ui.leAddress->setText(m_IPAddress);
	//ui.lePort->setText(QString::number(m_Port));

	//do{
	//	xmlCommDlg->exec();

	//	m_XMLServer->Set(ui.leAddress->text(), ui.lePort->text().toInt());
	//}while(m_XMLServer->Open()==false);
	//
	//m_IPAddress = ui.leAddress->text();
	//m_Port = ui.lePort->text().toInt();

	//return true;
}

void XMLWriter::set(QString address, int port)
{
	bool willRun = false;
	if(isRunning()==true){
		willRun = true;
		stop();
		wait();
	}

	setIPAddress(address);
	setPort(port);

	if(willRun==true){
		open();
		setReady();
		start();
	}
};

//void XMLWriter::setXMLOperationHandle(XMLOperationHandle *Hdl)
//{
//	if(m_XMLOpeHdlTemp==Hdl){
//		if(m_XMLOpeHdlTemp!=NULL){
//			m_waitCondition.wakeAll();
//		}
//		return;
//	}
//	if(m_XMLOpeHdlTemp!=NULL)delete m_XMLOpeHdlTemp;
//	m_XMLOpeHdlTemp = Hdl;
//	m_waitCondition.wakeAll();
//}

void XMLWriter::run()
{
	if(open()==false){
		return;
	}

	//qDebug() << "QThread:run() is started.";
	
	while(m_stop==false){

		//qDebug() << "XMLWriter is running.";

		{
			QMutexLocker locker( &m_Mutex );
			if(m_ReqWriteList.isEmpty()==true){// �����ǉ��������܂ő҂�
				msleep(20);
				if(m_flash==true){
					return;
				}
				continue;
			}
		}
		
		{
			QMutexLocker locker( &m_Mutex );
			if(m_XMLServer->Open()==false){
				if(m_XMLServer->GetState()==false){
					break;
				}
				msleep(50);
				continue;
			}
		}

		ReqXMLWrite item;
		{
		QMutexLocker locker( &m_Mutex );
		item = m_ReqWriteList.first();
		}
		
		{
		QMutexLocker locker(&m_MutexServer);
		XMLOperationHandle *xmlOpeHdl = m_XMLServer->OpenXMLOperation(item.getTableName());
		if(xmlOpeHdl==NULL){
			continue;
		}

		write(xmlOpeHdl, item);
		//qDebug() << /**/"QThread:writed";

		xmlOpeHdl->Close();
		delete xmlOpeHdl;
		}

		//for(int i=0; i<list.count(); i++){
		//	QMutexLocker locker(&m_MutexServer);
		//	ReqXMLWrite writtingItem = list[i];
		//	XMLOperationHandle *xmlOpeHdl = m_XMLServer->OpenXMLOperation(writtingItem.getTableName());
		//	if(xmlOpeHdl==NULL){
		//		continue;
		//	}

		//	write(xmlOpeHdl, writtingItem);
		//	//qDebug() << /**/"QThread:writed";

		//	xmlOpeHdl->Close();
		//	delete xmlOpeHdl;
		//	msleep(1000);
		//}

		{
		QMutexLocker locker( &m_Mutex );
		m_ReqWriteList.removeAll(item);
		}
		msleep(1);

		//m_Mutex.lock();
		//while(m_ReqWriteList.isEmpty()==false){// ���ɂȂ��܂ŌJ���Ԃ�
		//	QString retStr;
		//	ReqXMLWrite writtingItem = m_ReqWriteList.takeFirst();// �P�擪�������o��
		//	m_Mutex.unlock();

		//	XMLOperationHandle *xmlOpeHdl = m_XMLServer->OpenXMLOperation(writtingItem.getTableName());
		//	if(xmlOpeHdl==NULL){
		//		continue;
		//	}

		//	write(xmlOpeHdl, writtingItem);

		//	xmlOpeHdl->Close();
		//	delete xmlOpeHdl;

		//	m_Mutex.lock();
		//};
		//m_Mutex.unlock();
	}

	{
		QMutexLocker locker(&m_MutexServer);
		delete m_XMLServer;
		m_XMLServer = NULL;
	}
}

bool XMLWriter::write(XMLOperationHandle *hdl, const ReqXMLWrite &reqItem)
{
	if(hdl==NULL)return false;
	// ���݃|�C���^���ړ�������
	QString retStr;
	hdl->SelectFirst(/**/"<IST/>", QString(/**/"<IST><INSPECT EID=%1 /></IST>").arg(reqItem.getInspectID()), /**/"", retStr);
	if(retStr==/**/"<BOF/>")return false;
	int	WorkerID=ReviewPIBasePointer->GetLayersBase()->GetWorkerID();
	hdl->InsUpdateAttr(/**/QString("RTM=%1").arg(WorkerID));

	hdl->ChildSelectFirst(/**/"<PHASE/>", QString(/**/"<PHASE CODE=%1 */>").arg(reqItem.getPhase()), /**/"", retStr);
	if(retStr==/**/"<BOF/>")return false;
	hdl->ChildSelectFirst(/**/"<Page/>", QString(/**/"<Page CODE=%1 */>").arg(reqItem.getPage()), /**/"", retStr);
	if(retStr==/**/"<BOF/>")return false;
	hdl->XML_CopyPointerFromChild();

	// NGI���������ď�������
	for(ReqXMLWrite::ConstIterator item=reqItem.constBegin(); item!=reqItem.constEnd(); item++){
		QString NGISelStr = QString(/**/"<NGI X=%1 Y=%2 */>").arg(item->x()).arg(item->y());
		hdl->SelectFirst(/**/"<NGI/>", NGISelStr, /**/"", retStr);

		do{
			if((item->flags() & stReqXMLWrite::WriteChecked)!=0){
				if(item->isChecked()==true){
					hdl->InsUpdateAttr(/**/"Checked=1");
					//if(hdl->InsUpdateAttr(/**/"Checked=1")==false){
					//	QMessageBox::critical(NULL, /**/"Error", "XML Insert \"Checked\" is failed.");
					//}
				}else{
					hdl->DeleteAttr(/**/"Checked");
				}
			}
			if((item->flags() & stReqXMLWrite::WriteFKey)!=0){
				if(item->FKey()!=Review::NoFKey){
					hdl->InsUpdateAttr(QString(/**/"FK=%1").arg(Review::FKeyToInt(item->FKey())));
				}else{
					hdl->DeleteAttr(/**/"FK");
				}
			}
			hdl->SelectNext(retStr);
		}while(retStr!=/**/"<BOF/>" && retStr!=/**/"<EOF/>");

		//hdl_dup->Close();
		//delete hdl_dup;
	}

	return true;
}

QList<ReqXMLWrite> XMLWriter::getReqXMLList()
{ 
	QMutexLocker locker(&m_Mutex);
	return m_ReqWriteList;
};