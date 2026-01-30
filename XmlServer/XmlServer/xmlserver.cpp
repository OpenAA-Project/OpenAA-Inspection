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



#include "xmlserver.h"
#include "settingform.h"
#include "QFileDialog"
#include "XGeneralFunc.h"
#include "XLogOut.h"

//extern	LogOutClass	LogData;

ServerMain *Main;
bool ENDflag;
QString Ver="Ver2.6";
QString	CurrPath;
XmlServer::XmlServer(QWidget *parent, Qt::WindowFlags flags)
  //  : QWidget(parent, flags)
{
	CurrPath=QCoreApplication::applicationDirPath();
	ui.setupUi(this);
	setWindowTitle(tr("Xml Server ")+ Ver);
	Base=NULL;
	Base = new ServerBase();//ServerXmlClass���w�b�_�[�ł̓|�C���^�Ŏ����Ă����̂ŁA���Ԃ�����this
	socket=NULL;
	PortFileOpen(Port,Timer);
	ui.lTime->setText(QString::number(Timer));
	tcpServer = new QTcpServer(this);    
	if (!tcpServer->listen(QHostAddress::Any,Port)) {//�T�[�o�[���J���Ă��邩�̊m�F
		QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
	}
	ui.statusLabel->setText(tr("The server is running on port %1.\n"
                               "Run the Fortune Client example now.")
                             .arg(tcpServer->serverPort()));//Form��Port�ԍ����\��������
	PPORT =tr("%1\n").arg(tcpServer->serverPort());
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
	//�N���C�A���g�������v������������newConnection�ɓ����AsendFortune�֐����Ăяo��

	ui.tableWidget->setColumnCount(4);
	ui.tableWidget->setRowCount(0);	
	ui.tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("ClientNo")<<tr("DatabaseNo")<<tr("DatabaseName")<<tr("AccessTime"));
	ui.tableWidget->horizontalHeader()->resizeSection (0,100);
	ui.tableWidget->horizontalHeader()->resizeSection (1,100);
	ui.tableWidget->horizontalHeader()->resizeSection (2,120);
	ui.tableWidget->horizontalHeader()->resizeSection (3,200);

	ui.SaveWidget->setColumnCount(2);
	ui.SaveWidget->setRowCount(0);	
	ui.SaveWidget->setHorizontalHeaderLabels(QStringList()<<tr("DatabaseNo")<<tr("DatabaseName"));
	ui.SaveWidget->horizontalHeader()->resizeSection (0,100);
	ui.SaveWidget->horizontalHeader()->resizeSection (1,250);

	bool Ret2=(connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(on_Button_clicked())))?true:false;
	//bool Ret3=(connect(this->window(), SIGNAL(),this,SLOT(Exit())))?true:false;
	//connect(ui.SaveB,SIGNAL(clicked()),this,SLOT(on_SaveB_clicked()));
	//connect(ui.CreateB,SIGNAL(clicked()),this,SLOT(on_CreateB_clicked()));
	ui.CreateB->setVisible(false);	
	ui.SaveB->setVisible(false);	
	ui.pushButton->setText(tr("Set"));
	ui.SaveB->setText(tr("Save"));
	ui.CutB->setText(tr("Disconnect"));
	ui.ENDB->setText(tr("END"));
	ENDflag=true;
}

XmlServer::~XmlServer()
{
	int Row=ui.tableWidget->rowCount();
	//ENDflag=false;
	for(int i=0; i<Row; i++){
		int Row=ui.tableWidget->rowCount();
		if(0<Row){
			QByteArray CNum=ui.tableWidget->item(Row-1, 0)->text().toLocal8Bit().data();
			Main->Server_Cont(CNum);
		}
	}
	ui.tableWidget->setRowCount(0);
/*	if(_CrtCheckMemory()==false)
		return;
	ENDflag=false;
	int Row=ui.SaveWidget->rowCount();
	for(int i=0; i<Row; i++){
		int DBNum=ui.SaveWidget->item(i, 0)->text().toInt();
		QString DBName=ui.SaveWidget->item(i, 1)->text();
		Base->Server_End(DBNum, DBName);
	}*/
	delete Base;
	delete socket;
	Base=NULL;
	socket =NULL;
//	delete Main;
}
void XmlServer::Exit()
{
close();
}
void XmlServer::sendFortune()
{
	try {
		clientConnection = tcpServer->nextPendingConnection();//�N���C�A���g���̃\�P�b�g�Ď擾
//�����U��
		Main = new ServerMain(clientConnection,Base, ui);//�V�N���X�Ƀ\�P�b�g���n��Base���n��//this,,serverName,PPORT
	} catch(int) {//XmlException  
//		QMessageBox::information(this,"XmlServer Error", e.what());
		tcpServer->close();
	}
}

void XmlServer::PortFileOpen(quint16 &PORT,int &TIMER)
{
	QString	ServerFileName=CurrPath+QString("\\XmlServer.dat");
	char	FileName[200];
	QString2Char(ServerFileName ,FileName,sizeof(FileName));

	QFile	file(FileName);
	if(file.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&file);
		QString myString;
		int i=1;
		while (mystream.atEnd()==0){
			myString=mystream.readLine();
			switch(i){
				case 1:
					PORT=myString.toInt();		//PORT
					break;
				case 2:
					TIMER=myString.toInt();		//TIMER
					break;
			}
			i++;
		}
		file.close();
	}else{
		/*
		QMessageBox::critical(0, QObject::tr("Cannot open file"),
		QObject::tr("Cannot open XmlServer.dat\n"
					"Click Cancel to exit."), QMessageBox::Cancel,
					QMessageBox::NoButton);
					*/
		PORT=12345;
		TIMER=24;
		QFile	file(FileName);
		file.open(QIODevice::WriteOnly);
		QTextStream mystream(&file);
		mystream<<QString::number(PORT)<<Qt::endl;
		mystream<<QString::number(TIMER)<<Qt::endl;
		file.close();
	}
}
void XmlServer::on_Button_clicked()
{	
	SettingForm *dialog=new SettingForm;	
	dialog->show();
	 QString BackupPass;
    QString FileName;
	QString	File=CurrPath+QString("\\XmlServer.dat");
	QFile datFile(File);//�ۑ����E�t�@�C�����̕ۑ�	
	if(datFile.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&datFile);
		int i=1;
		while (mystream.atEnd()==0){
			switch(i){
			case 1:
				BackupPass=mystream.readLine();	//�ۑ���
				break;
			case 2:
				FileName=mystream.readLine();		//�t�@�C����
				break;
			}
			i++;
		}
		datFile.close();
		dialog->ui.LEPort->setText(BackupPass);
		dialog->ui.LETime->setValue(FileName.toInt());		
		return ;
	}
}
void XmlServer::on_SaveB_clicked()
{
	int iRow;
	if(ui.SaveWidget->rowCount()==0)
		return;
	iRow=ui.SaveWidget->currentRow();
	if (iRow!=-1)
		if(Base->Server_Save(ui.SaveWidget->item(iRow, 0)->text(), ui.SaveWidget->item(iRow, 1)->text())==false)
			return;
}
void  XmlServer::on_CutB_clicked()
{
	/*int Row=ui.tableWidget->currentRow();
	if (Row==-1)
		return;
	QByteArray CNum=ui.tableWidget->item(Row, 0)->text().toLocal8Bit().data();*/

	if(ui.tableWidget->rowCount()==0)
		return;
	int Row;
	Row=ui.tableWidget->currentRow();
	if(Row==-1)
		return;
	if(QMessageBox::information(0, tr("Disconnect"),tr("Disconnect OK?"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		return;
	QByteArray CNum=ui.tableWidget->item(Row, 0)->text().toLocal8Bit().data();
	Main->CutB_clicked(CNum);
	
}
void XmlServer::on_CreateB_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName( 0, QString("Create XML File"),  "",("XML (*.DBXML)"));
	if(FileName.isEmpty()==false){
		Base->Server_CreateFile(FileName);		
	}
}
void XmlServer::on_ENDB_clicked()
{
	//dialog->close();
	if(QMessageBox::information(0, tr("Server END"),tr("Server end OK?\nAll disconnect Please\n"),QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		return;
	close();
}