/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Hasplib\Hasplib\hasplib.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "hasplib.h"
#include "hasp_vcode.h"
#include  <QDomDocument>
#include <QDate>
#include "swap.h"

Hasplib::Hasplib() //  HASPコードの変更や追加は以下
	:HaspCodeList(QStringList() << "je8398hw" << "k38fj306" <<"mk923yhd")
// 	ハスプの種類[SoftNumber]	:	Player[0]     Editor[1]    Repair[2]
{

}

Hasplib::~Hasplib()
{

}

QString Hasplib::GetHaspCode(int SoftNumber){
	if(SoftNumber >= HaspCodeList.size())
		return "";
	return HaspCodeList.at(SoftNumber);
}

int Hasplib::MatchHaspCode(const QString &HaspCode){
	return HaspCodeList.indexOf(HaspCode);
}

bool Hasplib::HaspCheck(int SoftNumber){
	QString strKey = GetHaspCode(SoftNumber);
	if(strKey.isEmpty()==true)
		return false;
	QStringList RetList;
	if(HaspExecute(RetList)==false)
		return false;
	for(int Cnt=0;Cnt<RetList.count();Cnt++){
		if(RetList.at(Cnt)==strKey){
			if(QDate::currentDate()<=QDate::fromString(RetList.at(Cnt-1),/**/"yyyyMMdd"))
				return true;
		}
	}
	return false;
}
bool Hasplib::HaspExecute(QStringList &Ret)
{	
	if(HaspLogin(Handle)==true){
		if (Session(Handle,Info)==true){
			GetHaspID(Info,HaspID);
			if (ReadHasp(Handle,ReData)==true){
				unsigned char WORD=ReData[0];
				if (WORD==0xff){
					Ret.append("");
					return false;					
					hasp_logout(Handle);//login→logout
				}
				if (ReData=="" ){
					Ret.append("");
					return false;
					hasp_logout(Handle);//login→logout
				}
				if(Decrypt(Handle,ReData,DeData)==true){
					Fukugou(HaspID,DeData,Fuku);
					Return(Fuku,Ret);
					hasp_logout(Handle);//login→logout					
					return true;
				}
			}
		}
	}
	hasp_logout(Handle);//login→logout
	return false;
}
hasp_status_t Hasplib::Login(hasp_handle_t &handle){
	return hasp_login(HASP_PROGNUM_DEFAULT_FID,(hasp_vendor_code_t *)vendorCode,&handle);
}
bool Hasplib::HaspLogin(hasp_handle_t &handle)
{
	//HASPLogin
	hasp_status_t   status;
	handle =0;
	status = hasp_login(HASP_PROGNUM_DEFAULT_FID,(hasp_vendor_code_t *)vendorCode,&handle);
	switch (status) {
		case HASP_STATUS_OK:
			return true;
		default:
			return false;
	}
}
bool Hasplib::Session(hasp_handle_t handle, QByteArray &info)
{
	//HASP固有情報の取得
	info.clear();
	char *HASPinfo;
	hasp_status_t status;
	status = hasp_get_sessioninfo(handle, HASP_KEYINFO, &HASPinfo);
	switch (status) {
		case HASP_STATUS_OK:
			info=HASPinfo;
			return true;
		default:
			return false;
	}
}
void Hasplib::GetHaspID(QByteArray haspInfo,int &haspID)
{
//HASPシリアルコード取得
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
///											hasp_free((char *)HaspID); //開放
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
bool Hasplib::ReadHasp(hasp_handle_t handle, QByteArray &readData)
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
      default:
		return false;
	}
}
void Hasplib::Fukugou(int ID,QByteArray ReData, QByteArray &fukugou)
{
	//シリアルコードの下3桁を使用した複合化
	fukugou.clear();
	QStringList List;
	List.clear();
	//QByteArray→QStringList(swap関数を使う為)
	for (int iA=0; iA<=47; iA++){
		List.append(ReData.mid(iA,1));
	}
	//暗号化された時の最後の番号をとる
	int iNum=0;
	for (int iAn=0; iAn<=QByteArray().setNum(ID).mid(6,3).toInt(); iAn++){
		if (iNum==45){iNum=0;}	
		iNum++;
	}
	iNum=iNum+2;
	//暗号化されたものを複合化する
	for (int iFu=0; iFu<=QByteArray().setNum(ID).mid(6,3).toInt(); iFu++){
		if (iNum==2){iNum=47;}
		Swap(List,iNum,iNum-3);
		iNum--;
	}
	//QStringList→QByteArrayに戻す
	for (int iB=0; iB<=47; iB++){
		QString	s=List.at(iB);
		fukugou.append(s.toUtf8());
	}
}
bool Hasplib::Decrypt(hasp_handle_t handle, QByteArray hasp, QByteArray &deCereal)
{
	//データ複合化
	deCereal.clear();
	hasp_status_t   destatus;
	hasp.resize(hasp.size());
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
			for (int i=0;i<48;i++){
				deCereal.insert(i,deData[i]);
			}
			return true;
		default:
			return false;
	}
}
void Hasplib::Return(QByteArray InData,QStringList &RetData)
{
	QString sHYOUJI1;
	QString sHYOUJI4;
	QString sHYOUJI7;
	QString sHYOUJI10;
	//日付を型変換で戻す
	unsigned char WORD0=InData[0];
	unsigned char WORD1=InData[1];
	unsigned char WORD2=InData[2];
	unsigned char WORD3=InData[3];
	sHYOUJI1.append(QString().setNum(WORD0).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD1).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD2).rightJustified(2, '0'));
	sHYOUJI1.append(QString().setNum(WORD3).rightJustified(2, '0'));

	unsigned char WORD12=InData[12];
	unsigned char WORD13=InData[13];
	unsigned char WORD14=InData[14];
	unsigned char WORD15=InData[15];
	sHYOUJI4.append(QString().setNum(WORD12).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD13).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD14).rightJustified(2, '0'));
	sHYOUJI4.append(QString().setNum(WORD15).rightJustified(2, '0'));

	unsigned char WORD24=InData[24];
	unsigned char WORD25=InData[25];
	unsigned char WORD26=InData[26];
	unsigned char WORD27=InData[27];
	sHYOUJI7.append(QString().setNum(WORD24).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD25).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD26).rightJustified(2, '0'));
	sHYOUJI7.append(QString().setNum(WORD27).rightJustified(2, '0'));

	unsigned char WORD36=InData[36];
	unsigned char WORD37=InData[37];
	unsigned char WORD38=InData[38];
	unsigned char WORD39=InData[39];
	sHYOUJI10.append(QString().setNum(WORD36).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD37).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD38).rightJustified(2, '0'));
	sHYOUJI10.append(QString().setNum(WORD39).rightJustified(2, '0'));
	
	//データが入っている場合のみQStringへ移す
	RetData.clear();
	if (sHYOUJI1.right(6)!="000000"){
		RetData.append(sHYOUJI1);
		RetData.append(InData.mid(4,8));
		if (sHYOUJI4.right(6)!="323232"){
			RetData.append(sHYOUJI4);
			RetData.append(InData.mid(16,8));
			if (sHYOUJI7.right(6)!="323232"){
				RetData.append(sHYOUJI7);
				RetData.append(InData.mid(28,8));
				if (sHYOUJI10.right(6)!="323232"){
					RetData.append(sHYOUJI10);
					RetData.append(InData.mid(40,8));
				}
			}
		}
	}
}