#include "Haspviewer.h"
#include "hasplib.h"
#include <QMessageBox>
#include "swap.h"

HaspViewer::HaspViewer(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	QPalette palette;
	palette.setColor(QPalette::Base,QColor(240,240,240));
	Mbox.setPalette(palette);
	QFont font;
	font.setPointSize(12);
	font.setFamily(QString::fromUtf8("Arial"));
	Mbox.setFont(font);
	Mbox.setIcon(QMessageBox::Warning);
	View();
	hasp_logout(handle);
}

HaspViewer::~HaspViewer()
{

}
void HaspViewer::View(void){
	clearUI();

	handle = 0;
	hasp_status_t   status;
	status = Login(handle);

	if(ErrorCheck(status)==false)
		return;
	char *C = /**/"";
	status = hasp_get_sessioninfo(handle,HASP_KEYINFO,&C);
	if(ErrorCheck(status)==false)
		return;
	QString str_ID = GetID(C);
	ui.lbID->setText(str_ID);
	status = hasp_read(handle,HASP_FILEID_MAIN,0,48,C);
	if(ErrorCheck(status)==false)
		return;
//////////
	QByteArray ByteData;
	for(int i=0;i<48;i++){
		ByteData.insert(i,C[i]);
	}
//////////
	//unsigned char *Data = (unsigned char*)C;
//////////
	unsigned char UCData[48];
	for(int i=0;i<48;i++){
		UCData[i] = ByteData[i];
	}
	hasp_size_t deDatalen = sizeof(UCData);
	status = hasp_decrypt(handle,UCData,deDatalen);
	if(ErrorCheck(status)==false)
		return;
////////
	/*if(Data[0]==0xff || Data==NULL)
		return;
	status = hasp_decrypt(handle,Data,48);
	if(ErrorCheck(status)==false)
		return;*/
////////////
	ByteData.clear();
	for(int i=0;i<48;i++){
		ByteData.insert(i,UCData[i]);
	}
	QByteArray FukugouData;
	Fukugou(str_ID.toInt(),ByteData,FukugouData);
	for(int i=0;i<48;i++){
		UCData[i] = FukugouData[i];
	}
////////////
	//Fukugou(str_ID,Data);

	QStringList DateList;
	setDateList(UCData,DateList);
	QStringList TypeList;
	setTypeList(UCData,TypeList);

	for(int i=0;i<TypeList.size();i++){
		showCode(TypeList[i],DateList[i]);
	}
	ui.lbEnd->setVisible(true);
	// PlayerのハスプがEditorにも対応しているので
	if((ui.lbEditorDate->text().isEmpty()==true)&&(ui.lbPlayerDate->text().isEmpty()==false))
		ui.lbEditorDate->setText(ui.lbPlayerDate->text());
}
hasp_status_t HaspViewer::Login(hasp_handle_t &handle){
	Hasplib hasplib;
	return hasplib.Login(handle);
}
void HaspViewer::showCode(const QString &Code,const QString &Date){
	Hasplib hasplib;
	int index = hasplib.MatchHaspCode(Code);
//	HASPコード追加時には以下に追加
	switch(index){
		case -1: return;
		case 0: 
				ui.lbPlayerNO->setVisible(false);
				ui.lbPlayerOK->setVisible(true);
				ui.lbPlayerDate->setText(Date);
				// PlayerのハスプがEditorにも対応しているので
				ui.lbEditorNO->setVisible(false); 
				ui.lbEditorOK->setVisible(true);
				return;
		case 1:
				ui.lbEditorNO->setVisible(false);
				ui.lbEditorOK->setVisible(true);
				ui.lbEditorDate->setText(Date);
				return;
		case 2:
				ui.lbRepairNO->setVisible(false);
				ui.lbRepairOK->setVisible(true);
				ui.lbRepairDate->setText(Date);
				return;
	}
}
void HaspViewer::clearUI(void){
	ui.lbID		   ->clear();
	ui.lbPlayerDate->clear();
	ui.lbEditorDate->clear();
	ui.lbRepairDate->clear();
	ui.lbEnd     ->setVisible(false);
	ui.lbPlayerNO->setVisible(true);
	ui.lbEditorNO->setVisible(true);
	ui.lbRepairNO->setVisible(true);
	ui.lbPlayerOK->setVisible(false);
	ui.lbEditorOK->setVisible(false);
	ui.lbRepairOK->setVisible(false);
}
QString  HaspViewer::GetID(char *C){
	QString str;
	str.append(C);
	int first  = str.indexOf("<haspid>")+8;
	int Len    = str.indexOf('<',first) - first;
	return str.mid(first,Len);
}
//void HaspViewer::Fukugou(QString &str_ID,unsigned char *Data){
//	//シリアルコードの下3桁を使用した復号
//	int ID = str_ID.right(3).toInt();
//	//暗号化された時の最後の番号をとる
//	int iNum = ID%45+3;
//	//暗号を復号する
//	for (int i=0; i<=ID; i++){
//		if (iNum==2){iNum=47;}
//		std::swap(Data[iNum],Data[iNum-3]);
//		iNum--;
//	}
//}
////////
void HaspViewer::Fukugou(int ID,QByteArray ReData, QByteArray &fukugou)
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
		fukugou.append(List.at(iB).toUtf8());
	}
}
///////
void HaspViewer::setDateList(unsigned char *Data,QStringList &DateList){
	QString str;
	for(int i=0;i<48 && Data[i]!=' ';i++){
		str.append(QString().setNum(Data[i]).rightJustified(2,'0'));
		if(str.size()==8){
			DateList.append(str);
			str.clear();
			i+=8;
		}
	}
	for(int i=0;i<DateList.size();i++){
		DateList[i].insert(4,'/');
		DateList[i].insert(7,'/');
	}
}
void HaspViewer::setTypeList(unsigned char *Data,QStringList &TypeList){
	QString str;
	for(int i=4;i<48 && Data[i]!=0 && Data[i]!=' ';i++){
		str.append(QString::fromLocal8Bit((char *)Data[i]));
		if(str.size()==8){
			TypeList.append(str);
			str.clear();
			i+=4;
		}
	}
}
bool HaspViewer::ErrorCheck(const hasp_status_t &status){
	if(status == HASP_STATUS_OK)
		return true;

	switch (status) {
		case HASP_MEM_RANGE			   : Mbox.setText("Invalid memory address"							   ); break;
		case HASP_INV_PROGNUM_OPT	   : Mbox.setText("Unknown prognum option requested"				   ); break;
		case HASP_FEATURE_NOT_FOUND    : Mbox.setText("The requested feature isn't available"			   ); break;
		case HASP_CONTAINER_NOT_FOUND  : Mbox.setText("Hasp not  found"									   ); break;
		case HASP_FEATURE_TYPE_NOT_IMPL: Mbox.setText("The type of feature isn't implemented"			   ); break;
		case HASP_TMOF				   : Mbox.setText("Too many open handles"							   ); break;
		case HASP_INSUF_MEM			   : Mbox.setText("Out of memory"									   ); break;
		case HASP_INV_VCODE			   : Mbox.setText("invalid vendor code"								   ); break;
		case HASP_NO_DRIVER			   : Mbox.setText("Driver not installed"							   ); break;
		case HASP_OLD_DRIVER		   : Mbox.setText("Old driver installed"							   ); break;
		case HASP_TS_DETECTED		   : Mbox.setText("Program runs on a remote screen on Terminal Server" ); break;
		case HASP_INV_HND			   : Mbox.setText("Invalid session handle"							   ); break;
		case HASP_INV_FORMAT		   : Mbox.setText("Unrecognized format"								   ); break;
		case HASP_TOO_SHORT			   : Mbox.setText("The length of the data to be encrypted is too short"); break;
		case HASP_ENC_NOT_SUPP		   : Mbox.setText("Encryption type not supported by the hardware"	   ); break;
		default						   : Mbox.setText("Unknown Error"									   ); break;
	}
	Mbox.exec();
	return false;
}
void HaspViewer::on_pbUpdate_clicked()
{
	View();
	hasp_logout(handle);
}

void HaspViewer::on_pbEND_clicked()
{
	close();
}
