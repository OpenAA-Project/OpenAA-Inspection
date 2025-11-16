/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\HASP\HaspCereal_1\HaspCereal_1\haspcereal_1.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "haspcereal_1.h"
#include "hasp_vcode.h"       /* contains HASP HL DEMOMA vendor code */
HaspCereal_1::HaspCereal_1(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/haspcereal_1_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);
//Widget Size
	setFixedSize(198, 130); 
	setWindowTitle (tr("Cereal file out"));
	ui.label->setText(tr("Is the preparation for HASP good?"));
	ui.pbYES->setText(tr("YES"));
	ui.pbNO->setText(tr("NO"));
}
HaspCereal_1::~HaspCereal_1()
{
}
bool HaspCereal_1::HaspLogin(hasp_handle_t &handle)
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
			QMessageBox::information(this,"HaspLogin Erro","login to default feature failed\n");
			return false;
		case HASP_CONTAINER_NOT_FOUND:
			QMessageBox::information(this,"HaspLogin Erro","no HASP HL DEMOMA key/license container found\n");
            return false;
		case HASP_OLD_DRIVER:
			QMessageBox::information(this,"HaspLogin Erro","outdated driver version installed\n");
			return false;
		case HASP_NO_DRIVER:
			QMessageBox::information(this,"HaspLogin Erro","HASP HL driver not installed\n");
			return false;
		case HASP_INV_VCODE:
			QMessageBox::information(this,"HaspLogin Erro","invalid vendor code\n");
			return false;
		default:
			QMessageBox::information(this,"HaspLogin Erro","login to default feature failed\n");
			return false;
	}
}
bool HaspCereal_1::Session(hasp_handle_t handle, QByteArray &info)
{
	hasp_status_t status;
	char *HASPinfo;
	status = hasp_get_sessioninfo(handle, HASP_KEYINFO, &HASPinfo);
	switch (status) {
	case HASP_STATUS_OK:
		info=HASPinfo;
		return true;
    case HASP_INV_HND:
		QMessageBox::information(this,"Session Erro","handle not active\n");
		return false;
    case HASP_INV_FORMAT:
			QMessageBox::information(this,"Session Erro","unrecognized format\n");
		return false;
    case HASP_CONTAINER_NOT_FOUND:
		QMessageBox::information(this,"Session Erro","key/license container not available\n");
		return false;
    default:
		QMessageBox::information(this,"Session Erro","hasp_get_sessioninfo failed\n");
		return false;
	}
}
void HaspCereal_1::GetHaspID(QByteArray haspInfo,int &haspID)
{
	QDomDocument d;
	d.setContent(QString(haspInfo));
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {	//HASPシリアルコード取得
			if (n.tagName()=="hasp_info"){
				QDomElement child = n.firstChildElement();
					while (!child.isNull()) {
							if (child.tagName()=="keyspec"){
								QDomElement child2 = child.firstChildElement();
								while (!child2.isNull()) {
									if (child2.tagName()=="hasp"){
										QDomElement child3 = child2.firstChildElement();
									while (!child3.isNull()) {
										if (child3.tagName()=="haspid"){
											haspID =child3.text().toInt();
//											hasp_free((char *)HaspID); //開放
											return ;
										}
										child3=child3.nextSiblingElement();
									}
									}
									child2=child2.nextSiblingElement();
								}
							}
							child=child.nextSiblingElement();
					}
			}
			n=n.nextSiblingElement();
	}
}
bool HaspCereal_1::Encrypt(hasp_handle_t handle, int cerealNo, QByteArray &cerealData)
{
	hasp_status_t   status;
	QByteArray cereal;
	cereal.clear();
	cereal=QByteArray::number(cerealNo) ;
	cereal.resize(cereal.size());
	unsigned char CerealCode[] = {
		cereal[0], cereal[1], cereal[2], cereal[3], cereal[4], cereal[5], cereal[6], cereal[7],	cereal[8], cereal[9],
		cereal[10], cereal[11], cereal[12], cereal[13], cereal[14], cereal[15], cereal[16], cereal[17],cereal[18], cereal[19],
		cereal[20], cereal[21], cereal[22], cereal[23], cereal[24], cereal[25], cereal[26], cereal[27],cereal[28], cereal[29],
		cereal[30], cereal[31], cereal[32], cereal[33], cereal[34], cereal[35], cereal[36], cereal[37],cereal[38], cereal[39],
		cereal[40], cereal[41], cereal[42], cereal[43], cereal[44], cereal[45], cereal[46], cereal[47],cereal[48], cereal[49],//};
		cereal[50], cereal[51], cereal[52], cereal[53], cereal[54], cereal[55], cereal[56], cereal[57],cereal[58], cereal[59],
		cereal[60], cereal[61], cereal[62], cereal[63], cereal[64], cereal[65], cereal[66], cereal[67],cereal[68], cereal[69],
		cereal[70], cereal[71], cereal[72], cereal[73], cereal[74], cereal[75], cereal[76], cereal[77],cereal[78]};//

	hasp_size_t CerealCodeLen = sizeof(CerealCode);
	status = hasp_encrypt(handle,
						  CerealCode,
					      CerealCodeLen);
	switch (status) {
		case HASP_STATUS_OK:
			//cerealDataA = QByteArray::fromRawData(CerealCode, sizeof(CerealCode));
			//cerealDataA<QByteArray(CerealCode);
			for(int i=0; i<CerealCodeLen; i++)
				cerealData.append(CerealCode[i]);
			return true;
		case HASP_INV_HND:
			QMessageBox::information(this,"Encrypt Erro","login to default feature failed\n");
			return false;
		case HASP_TOO_SHORT:
			QMessageBox::information(this,"Encrypt Erro","data length too short\n");
			return false;
		case HASP_ENC_NOT_SUPP:
			QMessageBox::information(this,"Encrypt Erro","attached key does not support AES encryption\n");
			return false;
		case HASP_CONTAINER_NOT_FOUND:
			QMessageBox::information(this,"Encrypt Erro","key/license container not available\n");
			return false;
		default:
			QMessageBox::information(this,"Encrypt Erro","encryption failed\n");
			return false;
	}
}
bool HaspCereal_1::SaveFile(QString &sfile)
{
	sfile = QFileDialog::getSaveFileName(this,
										"save",
										"/HASPID",
										"");
   	if (sfile.isEmpty()) {
        return false;
    } else {
        return true;
    }
}
bool HaspCereal_1::SaveData(QString fileName, QByteArray cerealCode)
{
    QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
	file.write(cerealCode);
    //QDataStream out(&file);
    //out << cerealCode;
	file.close();
    return true;
}
void HaspCereal_1::on_pbYES_clicked()
{
	if (HaspLogin(handle)==true){
		if (Session(handle,HaspInfo)==true){//HASPシリアルコード取得
			GetHaspID(HaspInfo,HaspID);
			if (Encrypt(handle,HaspID,CerealID)==true){
				if (SaveFile(File)==true){
					if (SaveData(File,CerealID)==true){
						hasp_logout(handle);//login→logout
						close();
					}
				}
			}
		}
	}
	hasp_logout(handle);
}
void HaspCereal_1::on_pbNO_clicked()
{
	close();
}