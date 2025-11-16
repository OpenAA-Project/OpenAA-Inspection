/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspChosaku_2\HaspChosaku_2\haspchosaku_2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "haspchosaku_2.h"
#include "hasp_vcode.h"       /* contains HASP HL DEMOMA vendor code */

HaspChosaku_2::HaspChosaku_2(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/haspchosaku_2_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);
	//Widget Size
	setFixedSize(212, 189); 
	setWindowTitle (tr("Copyright file out"));
	ui.dateEdit->setDate(QDate::currentDate());
	ui.lCopyright->setText(tr("settCopyrightattestation number(8digit)"));
	ui.lUsable->setText(tr("Usableyears"));
	ui.pbOK->setText(tr("OK"));
	ui.pbEND->setText(tr("END"));
}

HaspChosaku_2::~HaspChosaku_2()
{
}
bool HaspChosaku_2::HaspLogin(hasp_handle_t &handle)
{
	hasp_status_t   status;
	handle =0;
	status = hasp_login(HASP_PROGNUM_DEFAULT_FID,
					   (hasp_vendor_code_t *)vendorCode,
						&handle);
	switch (status) {
		case HASP_STATUS_OK:
			return true;
		case HASP_FEATURE_NOT_FOUND:
			QMessageBox::information(this,"HaspLogin Error","login to default feature failed\n");
			return false;
		case HASP_CONTAINER_NOT_FOUND:
			QMessageBox::information(this,"HaspLogin Error","no HASP HL DEMOMA key/license container found\n");
           return false;
		case HASP_OLD_DRIVER:
			QMessageBox::information(this,"HaspLogin Error","outdated driver version installed\n");
			return false;
		case HASP_NO_DRIVER:
			QMessageBox::information(this,"HaspLogin Error","HASP HL driver not installed\n");
			return false;
		case HASP_INV_VCODE:
			QMessageBox::information(this,"HaspLogin Error","invalid vendor code\n");
			return false;
		default:
			QMessageBox::information(this,"HaspLogin Error","login to default feature failed\n");
			return false;
	}
}
bool HaspChosaku_2::FileOpen(QString &sfile)
{
	sfile = QFileDialog::getOpenFileName(this,"open","","");							
	if (sfile.isEmpty()){
		return false;
	}else{
		return true;
	}
}
bool HaspChosaku_2::FileLoad(QString fileName, QByteArray &cerealData)
{
    if (!QFile::exists(fileName))
        return false;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return false;
	cerealData=file.readAll();
//cerealData = QByteArray::fromRawData(file.readAll(), sizeof(file.readAll()));
	file.close();
	//QDataStream in(&file);
	//cerealData.clear();
	//in>>cerealData; 
//QByteArray::fromRawData((char *)CerealCode, CerealCodeLen);
//	QByteArray data = QByteArray::fromRawData(mydata, sizeof(mydata));
 //QDataStream in(&data, QIODevice::ReadOnly);
	return true;
}
bool HaspChosaku_2::Decrypt(hasp_handle_t handle, QByteArray cereal, QByteArray &deCereal)
{
	hasp_status_t   destatus;
	cereal.resize(cereal.size());
	unsigned char cerealData[] = {
		cereal[0], cereal[1], cereal[2], cereal[3], cereal[4], cereal[5], cereal[6], cereal[7],	cereal[8], cereal[9],
		cereal[10], cereal[11], cereal[12], cereal[13], cereal[14], cereal[15], cereal[16], cereal[17],cereal[18], cereal[19],
		cereal[20], cereal[21], cereal[22], cereal[23], cereal[24], cereal[25], cereal[26], cereal[27],cereal[28], cereal[29],
		cereal[30], cereal[31], cereal[32], cereal[33], cereal[34], cereal[35], cereal[36], cereal[37],cereal[38], cereal[39],
		cereal[40], cereal[41], cereal[42], cereal[43], cereal[44], cereal[45], cereal[46], cereal[47] ,cereal[48],cereal[49],//};
		cereal[50], cereal[51], cereal[52], cereal[53], cereal[54], cereal[55], cereal[56], cereal[57],cereal[58], cereal[59],
		cereal[60], cereal[61], cereal[62], cereal[63], cereal[64], cereal[65], cereal[66], cereal[67],cereal[68], cereal[69],
		cereal[70], cereal[71], cereal[72], cereal[73], cereal[74], cereal[75], cereal[76], cereal[77],cereal[78]};
	hasp_size_t cerealDatalen = sizeof(cerealData);
	destatus = hasp_decrypt(handle, cerealData, cerealDatalen);
	switch (destatus) {
		case HASP_STATUS_OK:
			/*if(QByteArray((char *)cerealData).size()!=9){
				QMessageBox::information(this,"file Error","The file is wrong");
				return false;
			}*/
			deCereal=QByteArray((char *)cerealData);
			return true;
		case HASP_INV_HND:
			QMessageBox::information(this,"decrypt Error","handle not active\n");
			return false;
		case HASP_TOO_SHORT:
			QMessageBox::information(this,"decrypt Error","data length too short\n");
			return false;
		case HASP_ENC_NOT_SUPP:
			QMessageBox::information(this,"decrypt Error","attached key does not support AES encryption\n");
			return false;
		default:
			QMessageBox::information(this,"decrypt Error","decryption failed\n");
			return false;
  }
}
bool HaspChosaku_2::Encrypt(hasp_handle_t handle, QByteArray cerealcode, QString copyright, QString date,QByteArray &en)
{ 
	hasp_status_t   enstatus;
	QByteArray endata;
	endata.clear();
	endata.append(":");
	endata.append(cerealcode);
	endata.append(":");
	endata.append( copyright.toUtf8());
	endata.append(":");
	endata.append(date.toUtf8());
	endata.resize(48);
	//int S=endata.size();
	unsigned char HaspData[] = {
		endata[0], endata[1], endata[2], endata[3], endata[4], endata[5], endata[6], endata[7],	endata[8], endata[9],
		endata[10], endata[11], endata[12], endata[13], endata[14], endata[15], endata[16], endata[17],endata[18], endata[19],
		endata[20], endata[21], endata[22], endata[23], endata[24], endata[25], endata[26], endata[27],endata[28], endata[29],
		endata[30], endata[31], endata[32], endata[33], endata[34], endata[35], endata[36], endata[37],endata[38], endata[39],
		endata[40], endata[41], endata[42], endata[43], endata[44], endata[45], endata[46], endata[47]};
	
	hasp_size_t HaspDatalen = sizeof(HaspData);
	enstatus = hasp_encrypt(handle,HaspData, HaspDatalen);		   
  switch (enstatus) {
    case HASP_STATUS_OK:
		char *AA;
		for (int i=0;i<=48;i++){
			en.insert(i,HaspData[i]);
		}
        return true;
    case HASP_INV_HND:
		QMessageBox::information(this,"encrypt Error","handle not active\n");
		return false;
    case HASP_TOO_SHORT:
		QMessageBox::information(this,"encrypt Error","ddata length too short\n");
		return false;
    case HASP_ENC_NOT_SUPP:
		QMessageBox::information(this,"encrypt Error","attached key does not support AES encryption\n");
		return false;

    case HASP_CONTAINER_NOT_FOUND:
		QMessageBox::information(this,"encrypt Error","key/license container not available\n");
		return false;
    default:
		QMessageBox::information(this,"encrypt Error","encryption failed\n");
		return false;
  }
}
bool HaspChosaku_2::SaveFile(QString &sfile)
{
	sfile = QFileDialog::getSaveFileName(this,"save","/Copyright","");							 										
   	if (sfile.isEmpty()) {
        return false;
    } else {
        return true;
    }
}
bool HaspChosaku_2::SaveData(QString fileName, QByteArray HaspCode)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly )) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
		return false;
    }
    QDataStream out(&file);
	out << HaspCode ;
	file.close();
    return true;
}

void HaspChosaku_2::on_pbOK_clicked()
{
	if (HaspLogin(Handle)==true){
		if (ui.lineEdit->text().isEmpty()==true){
			QMessageBox::information(this,"Data Error","Data null");
			hasp_logout(Handle);
			return ;
		}else if(ui.lineEdit->text().size()!=8){
			QMessageBox::information(this,"Data Error","Eight digit input");
			hasp_logout(Handle);
			return ;
		}
		if (QDate::currentDate()>=ui.dateEdit->date()){
			QMessageBox::information(this,"Date Error","Usableyears error");
			hasp_logout(Handle);
			return ;
		}
		QString Usabl=ui.dateEdit->date().toString("yyMMdd");
		QMessageBox::information(this,"Open File",tr("Open the HASPID file"));
		if (FileOpen(FileName)==false){
			QMessageBox::information(this,"FileOpen Error","Select not file");
			hasp_logout(Handle);
			return ;
		}else if(FileLoad(FileName,CerealData)==false){
			hasp_logout(Handle);
			return;
		}
		if (Decrypt(Handle,CerealData,DeCereal)==true){
			QString Copyright=ui.lineEdit->text();
			if (Encrypt(Handle,DeCereal,Copyright,Usabl,HaspData)){
				QMessageBox::information(this,"Save File",tr("save the HASPlisencefile"));
				if (SaveFile(File)==true){
					if (SaveData(File,HaspData)==true){
					hasp_logout(Handle);//loginÅ®logout
					close();
					}
				}
			}
		}
	}
	hasp_logout(Handle);
}

void HaspChosaku_2::on_pbEND_clicked()
{
	close();
}