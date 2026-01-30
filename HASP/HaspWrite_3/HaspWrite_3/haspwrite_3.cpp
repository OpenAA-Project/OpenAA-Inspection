/*
 * Copyright (C) 2025
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

#include "haspwrite_3.h"
#include "hasp_vcode.h"       /* contains HASP HL DEMOMA vendor code */
#include "hasplib.h"
#include "swap.h"

HaspWrite_3::HaspWrite_3(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator translator;
	translator.load(":/haspwrite_3_ja");
	qApp->installTranslator(&translator);
	ui.setupUi(this);
//Widget Title
	setWindowTitle (tr("Copyright validation code writing"));
//TableWidget HeaderTitle
	ui.tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Usable years")<<tr("CopyrightCode"));
//Button Text
	ui.pbFILEOPEN->setText(tr("File open"));
	ui.pbINSERT->setText(tr("Insert"));
	ui.pbDELETE->setText(tr("Delete"));
	ui.pbEND->setText(tr("End"));
//Button Enable
	ui.pbFILEOPEN->setEnabled(true);
	ui.pbINSERT->setEnabled(false);
	ui.pbDELETE->setEnabled(false);
	ui.pbEND->setEnabled(true);
//Widget Size
	//setFixedSize(430, 211); 
//Label
	ui.tCpyright->setText(tr("Cpyright"));
	ui.tUsableyears->setText(tr("Usableyears"));
	ui.tCerealNo->setText(tr("CerealNumber"));
}

HaspWrite_3::~HaspWrite_3()
{
}
bool HaspWrite_3::HaspLogin(hasp_handle_t &handle)
{
	//HASPLogin
	hasp_status_t   status;
	handle =0;
	status = hasp_login(HASP_PROGNUM_DEFAULT_FID,(hasp_vendor_code_t *)vendorCode,&handle);
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
bool HaspWrite_3::Session(hasp_handle_t handle, QByteArray &info)
{
	//HASP�ŗL�����̎擾
	info.clear();
	char *HASPinfo;
	hasp_status_t status;
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

void HaspWrite_3::GetHaspID(QByteArray haspInfo,int &haspID)
{
//HASP�V���A���R�[�h�擾
	QDomDocument d;
	d.setContent(QString(haspInfo));
	QDomElement n = d.firstChildElement();
	while (!n.isNull()) {	
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
//											hasp_free((char *)HaspID); //�J��
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
bool HaspWrite_3::FileOpen(QString &sfile)
{
	//File���̎擾
	sfile = QFileDialog::getOpenFileName(this,"open","","");							
	if (sfile.isEmpty()){
		return false;
	}else{
		return true;
	}
}
bool HaspWrite_3::FileLoad(QString fileName, QByteArray &haspData)
{
	//File���f�[�^�̎擾
    if (!QFile::exists(fileName))
        return false;
    QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
        return false;
	QDataStream in(&file);
	haspData.clear();
	in>>haspData; 
	return true;
}
bool HaspWrite_3::Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal)
{
	//�f�[�^������
	deCereal.clear();
	hasp_status_t   destatus;
	hasp.resize(48);//hasp.size()
	unsigned char deData[] = {
		hasp[0], hasp[1], hasp[2], hasp[3], hasp[4], hasp[5], hasp[6], hasp[7],	hasp[8], hasp[9],
		hasp[10], hasp[11], hasp[12], hasp[13], hasp[14], hasp[15], hasp[16], hasp[17],hasp[18], hasp[19],
		hasp[20], hasp[21], hasp[22], hasp[23], hasp[24], hasp[25], hasp[26], hasp[27],hasp[28], hasp[29],
		hasp[30], hasp[31], hasp[32], hasp[33], hasp[34], hasp[35], hasp[36], hasp[37],hasp[38], hasp[39],
		hasp[40], hasp[41], hasp[42], hasp[43], hasp[44], hasp[45], hasp[46], hasp[47]};
	hasp_size_t deDatalen = sizeof(deData);
	destatus = hasp_decrypt(handle,deData, deDatalen);	
	switch (destatus) {
		case HASP_STATUS_OK:
			for (int i=0;i<=48;i++){
				deCereal.insert(i,deData[i]);
			}
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
void HaspWrite_3::Angou(int ID, QByteArray DeData, QByteArray &angou)
{
	//�V���A���R�[�h�̉�3�����g�p�����Í���
	angou.clear();
	QStringList List;
	List.clear();
	//QByteArray��QStringList(swap�֐����g����)
	for (int iA=0; iA<=47; iA++){
		List.append(DeData.mid(iA,1));
	}
	//���ԂƁ��ԁ{3�Ԃ������ւ��鎖���V���A���ԍ��̉�3�����̉񐔍s��
	int iNum=0;
	for (int iAn=0; iAn<=QByteArray().setNum(ID).mid(6,3).toInt(); iAn++){
		if (iNum==45){iNum=0;}
		Swap(List,iNum,iNum+3);
		iNum++;
	}
	//QStringList��QByteArray�ɖ߂�
	for (int iB=0; iB<=47; iB++){
		angou.append(List.at(iB).toUtf8());
	}
}
bool HaspWrite_3::Encrypt(hasp_handle_t handle,QByteArray DeHaspData,QByteArray &enHaspData)
{ 
	//�f�[�^�Í���
	enHaspData.clear();
	hasp_status_t   enstatus;
	DeHaspData.resize(DeHaspData.size());
	unsigned char enData[] = {
		DeHaspData[0], DeHaspData[1], DeHaspData[2], DeHaspData[3], DeHaspData[4], DeHaspData[5], DeHaspData[6], DeHaspData[7],	DeHaspData[8], DeHaspData[9],
		DeHaspData[10], DeHaspData[11], DeHaspData[12], DeHaspData[13], DeHaspData[14], DeHaspData[15], DeHaspData[16], DeHaspData[17],DeHaspData[18], DeHaspData[19],
		DeHaspData[20], DeHaspData[21], DeHaspData[22], DeHaspData[23], DeHaspData[24], DeHaspData[25], DeHaspData[26], DeHaspData[27],DeHaspData[28], DeHaspData[29],
		DeHaspData[30], DeHaspData[31], DeHaspData[32], DeHaspData[33], DeHaspData[34], DeHaspData[35], DeHaspData[36], DeHaspData[37],DeHaspData[38], DeHaspData[39],
		DeHaspData[40], DeHaspData[41], DeHaspData[42], DeHaspData[43], DeHaspData[44], DeHaspData[45], DeHaspData[46], DeHaspData[47]};
	hasp_size_t enDatalen = sizeof(enData);
	enstatus = hasp_encrypt(handle,enData, enDatalen);		   
	switch (enstatus) {
		case HASP_STATUS_OK:
			for (int i=0;i<=48;i++){
				enHaspData.insert(i,enData[i]);
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
bool HaspWrite_3::WriteHasp(hasp_handle_t handle, QByteArray writeData)
{
//HASP�Ƀf�[�^����������
	hasp_status_t   status=HASP_STATUS_OK;
	writeData.resize(writeData.size());
	unsigned char WData[] = {
		writeData[0], writeData[1], writeData[2], writeData[3], writeData[4], writeData[5], writeData[6], writeData[7],	writeData[8], writeData[9],
		writeData[10], writeData[11], writeData[12], writeData[13], writeData[14], writeData[15], writeData[16], writeData[17],writeData[18], writeData[19],
		writeData[20], writeData[21], writeData[22], writeData[23], writeData[24], writeData[25], writeData[26], writeData[27],writeData[28], writeData[29],
		writeData[30], writeData[31], writeData[32], writeData[33], writeData[34], writeData[35], writeData[36], writeData[37],writeData[38], writeData[39],
		writeData[40], writeData[41], writeData[42], writeData[43], writeData[44], writeData[45], writeData[46], writeData[47]};
	hasp_size_t WDatalen = sizeof(WData);
	status = hasp_write(handle,HASP_FILEID_MAIN,0,WDatalen,WData);
	switch (status) {
		case HASP_STATUS_OK:
			return true;
		case HASP_INV_HND:
			QMessageBox::information(this,"write Error","handle not active\n");
			return false;
		case HASP_INV_FILEID:
			QMessageBox::information(this,"write Error","invalid file id\n");
			return false;
		case HASP_MEM_RANGE:
			QMessageBox::information(this,"write Error","beyond memory range of attached HASP HL key\n");
			return false;
		case HASP_CONTAINER_NOT_FOUND:
			QMessageBox::information(this,"write Error","key/license container not available\n");
			return false;
		default:
			QMessageBox::information(this,"write Error","write memory failed\n");
			return false;
	}
}

bool HaspWrite_3::ReadHasp(hasp_handle_t handle, QByteArray &readData)
{
	char ReadHaspData[49];
	for(int i=0; i<=48; i++){
		ReadHaspData[i]=NULL;
	}
	readData.clear();
	hasp_status_t status;
	status = hasp_read(handle,HASP_FILEID_MAIN,0,48,ReadHaspData);
	int iA;
    switch (status) {
      case HASP_STATUS_OK:
		for (iA=0;iA<=48;iA++){
			readData.insert(iA,ReadHaspData[iA]);
		}
        return true;
      case HASP_INV_HND:
		QMessageBox::information(this,"read Error","handle not active\n");
		return false;
      case HASP_INV_FILEID:
		QMessageBox::information(this,"read Error","invalid file id\n");
        return false;
      case HASP_MEM_RANGE:
		QMessageBox::information(this,"read Error","beyond memory range of attached HASP HL key\n");
        return false;
      case HASP_CONTAINER_NOT_FOUND:
		QMessageBox::information(this,"read Error","key/license container not available\n");
        return false;
      default:
		QMessageBox::information(this,"read Error","read memory failed\n");
		return false;
	}
}
void HaspWrite_3::Fukugou(int ID,QByteArray ReData, QByteArray &fukugou)
{
	//�V���A���R�[�h�̉�3�����g�p����������
	fukugou.clear();
	QStringList List;
	List.clear();
	//QByteArray��QStringList(swap�֐����g����)
	for (int iA=0; iA<=47; iA++){
		List.append(ReData.mid(iA,1));
	}
	//�Í������ꂽ���̍Ō��̔ԍ����Ƃ�
	int iNum=0;
	for (int iAn=0; iAn<=QByteArray().setNum(ID).mid(6,3).toInt(); iAn++){
		if (iNum==45){iNum=0;}	
		iNum++;
	}
	iNum=iNum+2;
	//�Í������ꂽ���̂𕡍�������
	for (int iFu=0; iFu<=QByteArray().setNum(ID).mid(6,3).toInt(); iFu++){
		if (iNum==2){iNum=47;}
		Swap(List,iNum,iNum-3);
		iNum--;
	}
	//QStringList��QByteArray�ɖ߂�
	for (int iB=0; iB<=47; iB++){
		fukugou.append(List.at(iB).toUtf8());
	}
}
void HaspWrite_3::WidgetRead(QByteArray &widgetData)
{
//TableWidget�ɕ\�������Ă������̂��擾����
	widgetData.clear();	
	QByteArray WORD;
	for (int i=0; i<=ui.tableWidget->rowCount()-1; i++){//�����ς��łȂ������������̃f�[�^��������
		WORD=QByteArray().setNum(ui.tableWidget->item(i,0)->text().toInt());
		unsigned char WORD1 =WORD.mid(0,2).toInt();
		unsigned char WORD2 =WORD.mid(2,2).toInt();
		unsigned char WORD3 =WORD.mid(4,2).toInt();
		unsigned char WORD4 =WORD.mid(6,2).toInt();

		widgetData.append(WORD1);
		widgetData.append(WORD2);
		widgetData.append(WORD3);
		widgetData.append(WORD4);
		widgetData.append(ui.tableWidget->item(i,1)->text().toUtf8());
	}
}
void HaspWrite_3::WidgetShow(QByteArray Hyouji)
{
	char Data[48];
	QString sHYOUJI;
	QString sHYOUJI1;
	QString sHYOUJI4;
	QString sHYOUJI7;
	QString sHYOUJI10;
	QTableWidgetItem *item;
	//���t���^�ϊ��Ŗ߂�
	unsigned char WORD0=Hyouji[0];
	unsigned char WORD1=Hyouji[1];
	unsigned char WORD2=Hyouji[2];
	unsigned char WORD3=Hyouji[3];
	sHYOUJI1.append(QString().setNum(WORD0).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD1).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD2).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD3).rightJustified(2, '0'));

	unsigned char WORD12=Hyouji[12];
	unsigned char WORD13=Hyouji[13];
	unsigned char WORD14=Hyouji[14];
	unsigned char WORD15=Hyouji[15];
	sHYOUJI4.append(QString().setNum(WORD12).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD13).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD14).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD15).rightJustified(2, '0'));

	unsigned char WORD24=Hyouji[24];
	unsigned char WORD25=Hyouji[25];
	unsigned char WORD26=Hyouji[26];
	unsigned char WORD27=Hyouji[27];
	sHYOUJI7.append(QString().setNum(WORD24).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD25).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD26).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD27).rightJustified(2, '0'));

	unsigned char WORD36=Hyouji[36];
	unsigned char WORD37=Hyouji[37];
	unsigned char WORD38=Hyouji[38];
	unsigned char WORD39=Hyouji[39];
	sHYOUJI10.append(QString().setNum(WORD36).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD37).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD38).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD39).rightJustified(2, '0'));
	
	//�f�[�^�������Ă����ꍇ�̂�QStringList�ֈڂ�
	int Num;
	Num=-1;
	if (sHYOUJI1.right(6)!="000000"){
		sHYOUJI.append(sHYOUJI1);
		sHYOUJI.append(Hyouji.mid(4,8));
		QString A1=Hyouji.mid(4,8);
		Num=1;
		if (sHYOUJI4.right(6)!="323232"){
			sHYOUJI.append(sHYOUJI4);
			sHYOUJI.append(Hyouji.mid(16,8));
			QString A2=Hyouji.mid(4,8);
			Num=3;
			if (sHYOUJI7.right(6)!="323232"){
				sHYOUJI.append(sHYOUJI7);
				sHYOUJI.append(Hyouji.mid(28,8));
				QString A3=Hyouji.mid(4,8);
				Num=5;
				if (sHYOUJI10.right(6)!="323232"){
					sHYOUJI.append(sHYOUJI10);
					sHYOUJI.append(Hyouji.mid(40,8));
					QString A4=Hyouji.mid(4,8);
					Num=7;
				}
			}
		}
	}
	//TableWidget�ւ̕\��
	int setRow=1;
	int Row=0;
	ui.tableWidget->setColumnCount(2);
	int AA=Hyouji.size();
	for(int iN=0;iN<=Num;iN++){
		item =new QTableWidgetItem(sHYOUJI.mid(iN*8,8));
		ui.tableWidget->setRowCount(setRow);		
		ui.tableWidget->setItem(Row,0,item);
		iN++;
		item =new QTableWidgetItem(sHYOUJI.mid(iN*8,8));
		ui.tableWidget->setItem(Row,1,item);
		Row++;
		setRow++;
	}
	ui.tableWidget->setHorizontalHeaderLabels(QStringList()<<"Use period"<<"CopyrightCode");
}
void HaspWrite_3::on_pbFILEOPEN_clicked()
{
	if (HaspLogin(Handle)==true){										//HASPLogin
		if (Session(Handle,HaspInfo)==true){							//HASP�����擾
			GetHaspID(HaspInfo,HaspID);									//HASP�V���A���R�[�h�擾
			QMessageBox::information(this,tr("The file is opened"),tr("Please open Hasplisencefile"));
			if (FileOpen(FileName)==false){								//File���擾
				QMessageBox::information(this,"FileOpen Error","Select not file");
				hasp_logout(Handle);
				return ;			
			}else if(FileLoad(FileName,HaspData)==false){				//File�������擾
				hasp_logout(Handle);
				return;
			}
			if (Decrypt(Handle,HaspData,DeHaspData)==true){				//�擾�����̕�����
				if (QString(strchr(DeHaspData, ':')).isEmpty()==true){	//���������ꂽ�f�[�^�̃`�F�b�N
					QMessageBox::information(this,tr("Open file error"),tr("It doesn't know the file"));
					hasp_logout(Handle);
					return ;  
				}
				QString sCereal=QString(DeHaspData).split(":").at(1);	//�V���A���R�[�h
				QString sChasaku=QString(DeHaspData).split(":").at(2);	//���쌠�R�[�h
				QString sDay=QString(DeHaspData).split(":").at(3);		//�g�p����	
				if (HaspID!=sCereal.toInt()){							//�t�@�C��������HASP�V���A���R�[�h�̏ƍ�
					QMessageBox::information(this,tr("Cereal code Error"),tr("The cereal code is not suitable"));
					hasp_logout(Handle);
					return ;
				}
				if (ReadHasp(Handle, ReadData)==true){					//HASP���f�[�^�̎擾		
					unsigned char WORD=ReadData[0];						//HASP���f�[�^�̃`�F�b�N
					if (ReadData==""){	
						ui.lCopyright->setText(sChasaku);		
						ui.lUsableyears->setText("20"+sDay.mid(0,2)+"/"+sDay.mid(2,2)+"/"+sDay.mid(4,2));
						ui.lCerealNo->setText(sCereal);
						ui.pbFILEOPEN->setEnabled(true);
						ui.pbINSERT->setEnabled(true);
						ui.pbDELETE->setEnabled(true);
						ui.pbEND->setEnabled(true);
						hasp_logout(Handle);
						return ;
					}else if (WORD==0xff){	
						ui.lCopyright->setText(sChasaku);		
						ui.lUsableyears->setText("20"+sDay.mid(0,2)+"/"+sDay.mid(2,2)+"/"+sDay.mid(4,2));
						ui.lCerealNo->setText(sCereal);
						ui.pbFILEOPEN->setEnabled(true);
						ui.pbINSERT->setEnabled(true);
						ui.pbDELETE->setEnabled(true);
						ui.pbEND->setEnabled(true);
						hasp_logout(Handle);//login��logout
						return;	
					}else{
						if (Decrypt(Handle,ReadData,DeWriteData)==true){//HASP���f�[�^�̕�����
							Fukugou(HaspID,DeWriteData,Fuku);
							WidgetShow(Fuku);							//TableWidget�֕\��
						}
					}
					ui.lCopyright->setText(sChasaku);		
					ui.lUsableyears->setText("20"+sDay.mid(0,2)+"/"+sDay.mid(2,2)+"/"+sDay.mid(4,2));
					ui.lCerealNo->setText(sCereal);
					ui.pbFILEOPEN->setEnabled(true);
					ui.pbINSERT->setEnabled(true);
					ui.pbDELETE->setEnabled(true);
					ui.pbEND->setEnabled(true);
				}
			}
		}
	}
	hasp_logout(Handle);//login��logout
}
void HaspWrite_3::on_pbINSERT_clicked()
{
	if (HaspLogin(Handle)==true){											//HASPLogin
		if (Session(Handle,HaspInfo)==true){								//HASP�����擾
			GetHaspID(HaspInfo,HaspID);										//HASP�V���A���R�[�h�擾
			if (ui.lCerealNo->text().isEmpty()==true){						//�}���������񂪓Ǎ��܂��Ă��邩�̊m�F
				hasp_logout(Handle);
				return ;
			}
			if (HaspID!=ui.lCerealNo->text().toInt()){						//�t�@�C��������HASP�V���A���R�[�h�̏ƍ�
				QMessageBox::information(this,tr("Cereal code Error"),tr("The cereal code is not suitable"));
				hasp_logout(Handle);
				return ;
			}
			if (ui.tableWidget->rowCount()!=0){								//HASP�������L���̊m�F
				for (int i=0; i<=ui.tableWidget->rowCount()-1; i++){		//HASP�ɏ�������������HASP���̏��񂪓������ۂ�
					if (ui.lCopyright->text()==ui.tableWidget->item(i,1)->text()){
						QMessageBox::information(this,"Insert Error","It has already broken out");
						hasp_logout(Handle);
						return;
					}
				}
			}
			if (ui.tableWidget->rowCount()==4){								//HASP���������ς����ǂ���
				QMessageBox::information(this,tr("HASP data full"),tr("HASP data full"));
				hasp_logout(Handle);
				return ;
			}
			if (ui.tableWidget->rowCount()!=0){								//HASP�������̎擾
				WidgetRead(DeHasp);
			}
			QString sCopy=ui.lCopyright->text()+"\n";						//���쌠�̎擾
			QByteArray WORD;
			QString KIGEN;
			KIGEN.append(ui.lUsableyears->text().mid(0,4));
			KIGEN.append(ui.lUsableyears->text().mid(5,2));
			KIGEN.append(ui.lUsableyears->text().mid(8,2));
			WORD=QByteArray().setNum(KIGEN.toInt());		//�g�p������8������4�����\��
			unsigned char WORD1 =WORD.mid(0,2).toInt();						//int��unsigned char:�^�ϊ�
			unsigned char WORD2 =WORD.mid(2,2).toInt();
			unsigned char WORD3 =WORD.mid(4,2).toInt();
			unsigned char WORD4 =WORD.mid(6,2).toInt();
			DeHasp.append(WORD1);
			DeHasp.append(WORD2);
			DeHasp.append(WORD3);
			DeHasp.append(WORD4);
			DeHasp.append(sCopy.toUtf8());

			Angou(HaspID,DeHasp,DataAngou);										//�f�[�^���V���A���R�[�h�ňÍ���
			if (Encrypt(Handle,DataAngou,EnHaspData)==true){					//�V���A���R�[�h�ňÍ��������f�[�^�̈Í���
				if (WriteHasp(Handle,EnHaspData)==true){						//HASP�֏�������
					if (ReadHasp(Handle, ReadData)==true){						//HASP�����̓ǂݍ���
						if (Decrypt(Handle, ReadData, DeWriteData)==true){	//HASP���f�[�^�̕�����
							Fukugou(HaspID,DeWriteData,Fuku);					//�����������f�[�^���V���A���R�[�h�ŕ�����
							WidgetShow(Fuku);									//TableWidget�֕\��
						}
					}
				}	
			}
		}
	}
	hasp_logout(Handle);//login��logout
}
void HaspWrite_3::on_pbDELETE_clicked()
{
	if (HaspLogin(Handle)==true){												//HASPLogin
		if (Session(Handle,HaspInfo)==true){									//HASP�����擾
			GetHaspID(HaspInfo,HaspID);											//HASP�V���A���R�[�h�擾
			if (ui.lCerealNo->text().isEmpty()==true){							//�}���������񂪓Ǎ��܂��Ă��邩�̊m�F
				QMessageBox::information(this,"select Error","unkuown HASPceraldata\n");
				hasp_logout(Handle);
				return;
			}
			if (HaspID!=ui.lCerealNo->text().toInt()){							//�t�@�C��������HASP�V���A���R�[�h�̏ƍ�
				QMessageBox::information(this,"select Error","Error HASPceraldata\n");
				hasp_logout(Handle);
				return;
			}
			if (ui.tableWidget->currentRow()==-1){								//TableWidget�̃f�[�^���I�����Ă��邩�̊m�F
				QMessageBox::information(this,"select Error","delete data not select\n");
				hasp_logout(Handle);
				return;
			}
			ui.tableWidget->removeRow(ui.tableWidget->currentRow());			//TableWidget�̃f�[�^�̍폜
			if (ui.tableWidget->rowCount()==0){									//TableWidget�̃f�[�^�̎擾
				WriteHasp(Handle,"");											//HASP�֏�������
				ReadHasp(Handle, DeWriteData);									//HASP�����̓ǂݍ���
				WidgetShow(DeWriteData);										//TableWidget�֕\��
			}else{
				WidgetRead(DeHasp);												//TableWidget�ɕ\�������Ă������̂��擾����
				Angou(HaspID,DeHasp,DataAngou);									//�f�[�^���V���A���R�[�h�ňÍ���
				if (Encrypt(Handle,DataAngou,EnHaspData)==true){				//�V���A���R�[�h�ňÍ��������f�[�^�̈Í���
					if (WriteHasp(Handle,EnHaspData)==true){					//HASP�֏�������
						if (ReadHasp(Handle, ReadData)==true){					//HASP���f�[�^�̎擾
							if (Decrypt(Handle,ReadData, Fuku)==true){			//HASP���f�[�^�̕�����
								Fukugou(HaspID,Fuku,DeWriteData);				//�����������f�[�^���V���A���R�[�h�ŕ�����
								WidgetShow(DeWriteData);						//TableWidget�֕\��
							}
						}
					}
				}
			}
		}
	}
	hasp_logout(Handle);//login��logout
}

void HaspWrite_3::on_pbEND_clicked()
{
	close();
}