#include "ResultDataManagerResource.h"
#include "ManageByDayTime.h"
#include "ui_ManageByDayTime.h"
#include "XDataInLayer.h"
#include "XFileRegistry.h"
#include "XMLGeneralFunc.h"
#include <QMessageBox>
#include <QProgressDialog>
#include <QProgressBar>
#include "XGeneralFunc.h"

ManageByDayTime::ManageByDayTime(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ManageByDayTime)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SParam=Param;

	XMLServer=new XMLServerHandle(SParam->XML_IPAddress,SParam->XML_Port,this);
	XMLServer->SetParam(&ServerParam);
	ServerParam.LoadDefault(GetLayersBase()->GetUserPath());

	if(XMLServer->Open()==false){
		QMessageBox::warning(this, /**/"Check:XMLServer"
								, LangSolver.GetString(ManageByDayTime_LS,LID_1)/*"データベースの接続に失敗しました"*/);
	}

	SQLDatabase=GetLayersBase()->GetDatabaseLoader();

	connect(ui->calendarStartDelete, SIGNAL(clicked(const QDate &)), ui->dateTimeEditStartDelete, SLOT(setDate(const QDate &)));
	connect(ui->dateTimeEditStartDelete, SIGNAL(dateChanged(const QDate &)), ui->calendarStartDelete, SLOT(setSelectedDate(const QDate &)));

	connect(ui->calendarEndDelete, SIGNAL(clicked(const QDate &)), ui->dateTimeEditEndDelete, SLOT(setDate(const QDate &)));
	connect(ui->dateTimeEditEndDelete, SIGNAL(dateChanged(const QDate &)), ui->calendarEndDelete, SLOT(setSelectedDate(const QDate &)));

	ui->dateTimeEditStartDelete->setDateTime( QDateTime::currentDateTime() );
	ui->dateTimeEditEndDelete->setDateTime( QDateTime::currentDateTime() );
}

ManageByDayTime::~ManageByDayTime()
{
    delete ui;

	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}
	delete	XMLServer;
}

void ManageByDayTime::on_pushButtonClose_clicked()
{
	done(true);
}

void ManageByDayTime::on_pushButtonExecuteDelete_clicked()
{
	if(ui->dateTimeEditStartDelete->dateTime() > ui->dateTimeEditEndDelete->dateTime()){
		QMessageBox::warning(this, /**/"Range Error"
									, LangSolver.GetString(ManageByDayTime_LS,LID_2)/*"開始時刻は終了時刻より前に設定してください"*/);
		return;
	}

	QDateTime	sStartTime		=ui->dateTimeEditStartDelete->dateTime();
	QString		sStartTimeStr	=sStartTime.toString(/**/"yyMMddhhmmss");
	QDateTime	sEndTime		=ui->dateTimeEditEndDelete->dateTime();
	QString		sEndTimeStr		=sEndTime.toString(/**/"yyMMddhhmmss");

	QStringList deleteTableList;
	
	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		QMessageBox::warning(this, /**/"XMLServerError"
									, LangSolver.GetString(ManageByDayTime_LS,LID_3)/*"データベースの接続に失敗しました"*/);
		return;
	}

	// すべてのロットから指定時間に該当する検査履歴をすべて削除する
	bool	Ret=XMLServer->EnumTables(/**/"*",EnumResultList);
	if(Ret==true){
		ui->progressBarDelete->setRange(0, EnumResultList.count());
		ui->progressBarDelete->setValue(0);
		qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		int	N=EnumResultList.count();
		for(int i=0;i<N;i++){
			QString	TableStr=EnumResultList[i];
			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
			if(OpeHandle!=NULL){
				QString	OutputStr	=QString(/**/"<COUNT/>");
				QString	SearchStr	=QString(/**/"<IST */>");
				QString	OrderStr	=QString(/**/"");
				QStringList	ResultListStr;
				bool countRet = OpeHandle->Select(OutputStr,SearchStr,OrderStr,ResultListStr);
				if(countRet==false || ResultListStr.isEmpty()){
					XMLServer->CloseXMLOperation(OpeHandle);
					OpeHandle->Close();
					delete OpeHandle;
					ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
					continue;
				}
				QString countStr = ResultListStr.first();
				countStr = countStr.mid(countStr.indexOf(/**/"\"")+1);
				countStr = countStr.left(countStr.lastIndexOf(/**/"\""));
				bool ok;
				int count = countStr.toInt(&ok);
				if(ok && count==0){
					if(ui->cbDeleteEmptyDXML->isChecked()==true){
						deleteTableList.append(TableStr);
					}
					XMLServer->CloseXMLOperation(OpeHandle);
					OpeHandle->Close();
					delete OpeHandle;
					ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
					continue;
				}

				int LotAutoCount = ReadLotAutoCount(TableStr, XMLServer);
				int LotMasterCode = ReadLotMasterCode(TableStr, XMLServer, *GetLayersBase()->GetDataBase());

				// 削除指定時間範囲内にある検査履歴をリストアップ
				OutputStr	=QString(/**/"<IST NGJ />");
				SearchStr	=QString(/**/"<IST DAY>=\"")+sStartTimeStr+QString(/**/"\" DAY<=\"")+sEndTimeStr+QString(/**/"\" />");
				OrderStr	=QString(/**/"DAY");
				bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,OrderStr,ResultListStr);
				//if(ResultListStr.isEmpty()){// なければ次へ
				//	XMLServer->CloseXMLOperation(OpeHandle);
				//	OpeHandle->Close();
				//	delete OpeHandle;
				//	ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
				//	continue;
				//}
				// 削除
				if(SelectRet1==true){
					QProgressDialog progress(this);
					progress.setRange(0, ResultListStr.count());
					progress.setValue(0);
					progress.setCancelButton(0);
					progress.setLabelText(LangSolver.GetString(ManageByDayTime_LS,LID_4)/*"NG画像ファイルを削除中"*/
										+ /**/"\n" + TableStr);

					QString filepath;
					DeleteJDT(ResultListStr, SParam);
					progress.setValue(progress.value()+ResultListStr.count());
				}


				// 逐次削除
				QStringList DeleteXMLList;
				QString DeleteXML;
				bool	SelectRet2=false;
				SelectRet2 = OpeHandle->SelectFirst(/**/"<IST/>", SearchStr, /**/"", DeleteXML);
				if(SelectRet2==true && DeleteXML.isEmpty()==false && DeleteXML!=/**/"<BOF/>"){
					do{
						SelectRet2 = OpeHandle->DeleteXML();
						if(SelectRet2==false){
							break;
						}
						SelectRet2 = OpeHandle->SelectFirst(/**/"<IST/>", SearchStr, /**/"", DeleteXML);
					}while(SelectRet2==true && DeleteXML!=/**/"<BOF/>" && DeleteXML!=/**/"<EOF/>");
				}

				// XML文を削除(一括)
				//bool	SelectRet2=OpeHandle->DeleteXML(SearchStr);
				// 削除後に検査履歴がない場合はロットファイルを削除する
				if(SelectRet2==true){
					QStringList	CountListStr;
					bool	SelectRet3=OpeHandle->Select(/**/"<COUNT/>",/**/"<IST */>",/**/"",CountListStr);
					if(SelectRet3==true){
						int RetCount;
						if(CountListStr.isEmpty()==true || CountListStr.count()>1 || CountListStr.first().count(/**/'\"')!=2){
							XMLServer->CloseXMLOperation(OpeHandle);
							OpeHandle->Close();
							delete OpeHandle;
							ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
							qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
							continue;
						}
						QString countStr = CountListStr.first();
						countStr = countStr.mid(countStr.indexOf(/**/"\"")+1);
						countStr = countStr.left(countStr.lastIndexOf(/**/"\""));
						bool ok;
						RetCount = countStr.toInt(&ok);
						//if(GetXMLCountValue(CountListStr[0],"COUNT",RetCount)==true && RetCount==0){
						qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
						XMLServer->CloseXMLOperation(OpeHandle);
						OpeHandle->Close();
						delete OpeHandle;
						if(ok==true && RetCount==0 && ui->cbDeleteEmptyDXML->isChecked()==true){
							QString filepath;
							//DeleteTable(TableStr
							//	,XMLServer
							//	,GetLayersBase()->GetDatabaseLoader(),*GetLayersBase()->GetDataBase()
							//	,SParam, &filepath);
							DeleteTable(TableStr, LotAutoCount, LotMasterCode
								,XMLServer
								,GetLayersBase()->GetDatabaseLoader(),*GetLayersBase()->GetDataBase()
								,SParam);
							deleteTableList.append(TableStr);
						}
					}else{
						qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
						XMLServer->CloseXMLOperation(OpeHandle);
						OpeHandle->Close();
						delete OpeHandle;
					}
				}else{
					qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
					XMLServer->CloseXMLOperation(OpeHandle);
					OpeHandle->Close();
					delete OpeHandle;
				}
			}
			ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
		}
	}
	ui->progressBarDelete->setValue(ui->progressBarDelete->value()+1);
	qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}

	if(deleteTableList.isEmpty()==false){
		if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
								, LangSolver.GetString(ManageByDayTime_LS,LID_5)/*"ロットデータ削除エラー"*/);
			return;
		}else{
			for(int i=0; i<deleteTableList.count(); i++){
				XMLServer->DeleteTable(deleteTableList[i]);
			}
			XMLServer->Close();
		}
	}

	QMessageBox::about(this, LangSolver.GetString(ManageByDayTime_LS,LID_6)/*"Delete Operation Complete"*/
							, LangSolver.GetString(ManageByDayTime_LS,LID_7)/*"削除作業は終了しました"*/);
}

