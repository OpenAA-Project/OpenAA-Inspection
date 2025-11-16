#include "logintegratorfrontend.h"
#include <QMessageBox>
#include <QSettings>
#include "time.h"

LogIntegratorFrontEnd::LogIntegratorFrontEnd(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags), LotNoValidator(this)
{
	ui.setupUi(this);

	connect( ui.lineEdit_LotNo,          SIGNAL(returnPressed()), this, SLOT(on_pushButton_Run_clicked()) );	
	connect( ui.dateEdit_Date,           SIGNAL(returnPressed()), this, SLOT(on_pushButton_DateRun_clicked()) );	

	connect( ui.actionShowSettingDialog, SIGNAL(triggered()),  this, SLOT(ShowSettingDialog()) );
	connect( ui.actionQuit,              SIGNAL(triggered()),  this, SLOT(close()            ) );
	connect( ui.pbClose,	             SIGNAL(clicked()  ),  this, SLOT(close()            ) );

	IniFilePath = QDir::currentPath() + QDir::separator() + "LogIntegratorFrontEnd.ini";

	if( !QFile::exists(IniFilePath) ){
		QMessageBox::warning(this, QString("警告"), QString("設定を保存したファイルが存在しません。初期設定ダイアログを開きます。") );
		UpperLogHD = SettingDialog.ui.lineEdit_UpperLogHD->text();
		LowerLogHD = SettingDialog.ui.lineEdit_LowerLogHD->text();
		OutputDir  = SettingDialog.ui.lineEdit_OutputDir->text();
		ShowSettingDialog();
	}

	QSettings settings(IniFilePath, QSettings::IniFormat);
	settings.beginGroup("Window");
	this->setGeometry(
		settings.value("Left",   this->geometry().left()).toInt(),
		settings.value("Top" ,   this->geometry().top()).toInt(),
		settings.value("Width" , this->width()).toInt(),
		settings.value("Height", this->height()).toInt()
		);
	settings.endGroup();
	settings.beginGroup("IO");
	SettingDialog.ui.lineEdit_UpperLogHD->setText( settings.value("UpperLogHD", SettingDialog.ui.lineEdit_UpperLogHD->text()).toString() );
	SettingDialog.ui.lineEdit_LowerLogHD->setText( settings.value("LowerLogHD", SettingDialog.ui.lineEdit_LowerLogHD->text()).toString() );
	SettingDialog.ui.lineEdit_OutputDir ->setText( settings.value("OutputDir" , SettingDialog.ui.lineEdit_OutputDir ->text()).toString() );
	settings.endGroup();

	UpperLogHD = SettingDialog.ui.lineEdit_UpperLogHD->text();
	LowerLogHD = SettingDialog.ui.lineEdit_LowerLogHD->text();
	OutputDir  = SettingDialog.ui.lineEdit_OutputDir ->text();

	LotNoValidator.setRegExp(QRegularExpression("[a-z0-9\\-]{0,10}", Qt::CaseInsensitive));
	ui.lineEdit_LotNo->setValidator(&LotNoValidator);

	ui.dateEdit_Date->setDate(QDate::currentDate());

	//処理中画面のメモリ確保
	ProcessForm=new LogIntegratorProcessForm();
	connect(&LibObj,SIGNAL(UpdateSignal(int)),ProcessForm,SLOT(SetUpdate(int)));
}

LogIntegratorFrontEnd::~LogIntegratorFrontEnd()
{
	QSettings settings(IniFilePath, QSettings::IniFormat);
	settings.beginGroup("Window");
	settings.setValue("Left"  , this->geometry().left());
	settings.setValue("Top"   , this->geometry().top());
	settings.setValue("Width" , this->width());
	settings.setValue("Height", this->height());
	settings.endGroup();
	settings.beginGroup("IO");
	settings.setValue("UpperLogHD" , SettingDialog.ui.lineEdit_UpperLogHD->text());
	settings.setValue("LowerLogHD" , SettingDialog.ui.lineEdit_LowerLogHD->text());
	settings.setValue("OutputDir"  , SettingDialog.ui.lineEdit_OutputDir->text());
	settings.endGroup();
}


void LogIntegratorFrontEnd::on_pushButton_Run_clicked()
{
	//退避したエラーの発生したログデータをクリアする
	LibObj.ClearErrLog();
	//関数化
	QString LotNo = ui.lineEdit_LotNo->text();
	//実行総数をセット
	ProcessForm->SetExecCount(1);
	//現在の実行数をセット
	ProcessForm->SetExecNo(1);
	//実行
	ExecuteIntegration(LotNo);
	//ErrDialogにエラーの発生したログがあればデータを退避する
	LibObj.makeErrLog();
	if(LibObj.IsErrLog()==true){
		//ファイルにも落とす
		if ( LibObj.outErrLog(LotNo) == false ) {
			QMessageBox::critical(this, QString("エラー"), QString("なんらかの原因で発生したファイルの入出力エラーにより、エラーログの出力に失敗しました。再度処理を実行してみるか、出力先フォルダ名・HD・ログファイルなどを確認してください。"));
		}
	}
}

bool LogIntegratorFrontEnd::ExecuteIntegration(QString LotNo)
{
	//処理中画面の表示
	ProcessForm->move(x()+(width()-ProcessForm->width())/2,y()+(height()-ProcessForm->height())/2);	//処理中画面の表示位置の設定
	ProcessForm->SetLotNo(LotNo);
	ProcessForm->SetUpdate(0);
	ProcessForm->show();
	ProcessForm->SetUpdate(20);

	LibObj.ClearErrDialogLogs();

	LibObj.setPath1(UpperLogHD);
	LibObj.setPath2(LowerLogHD);
	LibObj.setOutPath(OutputDir);
	LibObj.setLotNo(LotNo);
	LibObj.setBaseNo(0);

	// check invalid values
	QFile QFileUpperLogHD(UpperLogHD);
	if( !QFileUpperLogHD.exists() ){
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("上面ログのあるHDを読み込めませんでした。ハードウェアの接続や「初期設定」内のドライブ名などを確認してください。処理は中止されました。"));
		return false;
	}
	QFile QFileLowerLogHD(LowerLogHD);
	if( !QFileLowerLogHD.exists() ){
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("下面ログのあるHDを読み込めませんでした。ハードウェアの接続や「初期設定」内のドライブ名などを確認してください。処理は中止されました。"));
		return false;
	}
	QDir QDirOutputDir(OutputDir);
	//存在しないが、作成できるとき
	if( !QDirOutputDir.exists() ){
		if( QMessageBox::question(this, QString("エラー"), QString("出力先フォルダが存在しません。作成しますか？"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes)
		    == QMessageBox::Cancel ){
			ProcessForm->close();
			QMessageBox::critical( this, QString("エラー"), QString("処理を中止しました。") );
			return false;
		}
		if( QDirOutputDir.path() != ForceDirectories( QDirOutputDir.path() ) ){
			ProcessForm->close();
			QMessageBox::critical(this, QString("エラー"), QString("出力先フォルダを作成できませんでした。出力先フォルダ名に使用できない文字が使用されていないかどうかなどを確認してください。"));
			return false;
		}
		SettingDialog.ui.lineEdit_OutputDir->setText( QDir::toNativeSeparators( QDirOutputDir.path() ) );
	}

	if( LotNo.isEmpty() ){
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("ロット番号が指定されていません。"));
		return true;
	}
	if( LotNo.size() != MAX_LOTNOLENGTH ){
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("ロット番号が")+QString::number(MAX_LOTNOLENGTH)+QString("桁ではありません"));
		return true;
	}

	// exec
	if( LibObj.makeLogIntegrate() == false ){
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("ログの読み込み中にエラーが発生しました。指定されたドライブに所定のフォーマットでログが存在するかなどを確認してください。"));
		return true;
	}
	if ( LibObj.outLog() == false ) {
		ProcessForm->close();
		QMessageBox::critical(this, QString("エラー"), QString("なんらかの原因で発生したファイルの入出力エラーにより、ログの出力に失敗しました。再度処理を実行してみるか、出力先フォルダ名・HD・ログファイルなどを確認してください。"));
		return true;
	}
	ProcessForm->close();

	LibObj.errChk();
	LibObj.showErrDialog();
	return true;
}

void LogIntegratorFrontEnd::ShowSettingDialog(void)
{
	SettingDialog.ui.lineEdit_UpperLogHD->setText(UpperLogHD);
	SettingDialog.ui.lineEdit_LowerLogHD->setText(LowerLogHD);
	SettingDialog.ui.lineEdit_OutputDir ->setText(OutputDir );
	if( SettingDialog.exec() == QDialog::Accepted ){
		LowerLogHD = SettingDialog.ui.lineEdit_LowerLogHD->text();
		UpperLogHD = SettingDialog.ui.lineEdit_UpperLogHD->text();
		OutputDir  = SettingDialog.ui.lineEdit_OutputDir ->text();
	}
}

void LogIntegratorFrontEnd::on_pushButton_DateRun_clicked()
{
	//日付指定
	QStringList Result;
	QDir rootdir(UpperLogHD);
	if ( rootdir.exists() == false ){
		QMessageBox::critical(this, QString("エラー"), QString("上面ログのあるHDを読み込めませんでした。ハードウェアの接続や「初期設定」内のドライブ名などを確認してください。処理は中止されました。"));
		return;
	}
	QString Date = ui.dateEdit_Date->text();
	Date.remove('/');
	if( rootdir.cd(Date) == false ){
		QMessageBox::warning( NULL, QString("エラー"), QString("上面HDに日付「")+Date+QString("」のフォルダが見つかりませんでした。日付やファイルなどを確認してください。処理を中止します。") );
		return;
	}
	QStringList filters;
	filters << "??????????*";	//ロット番号（10桁orそれ以上）
	rootdir.setNameFilters(filters);
	Result = rootdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name );

	//退避したエラーの発生したログデータをクリアする
	LibObj.ClearErrLog();
	//実行総数をセット
	ProcessForm->SetExecCount(Result.size());
	//指定された日付フォルダの中にあるロット番号フォルダの数だけループで回しながら統合する
	for( int i=0; i<Result.size(); i++ ) {
		//現在の実行数をセット
		ProcessForm->SetExecNo(i+1);

		//実行
		if(ExecuteIntegration(Result.at(i))==false){
			return;
		}

		//Waitを置く
		for(time_t t=time(NULL);time(NULL)-t<2;){}

		//ErrDialogにエラーの発生したログがあればデータを退避する
		LibObj.makeErrLog();

//		//ErrDialogのスクリーンショットを撮る
//		LibObj.saveErrDialogImage();

		//ErrDialogを閉じる
		LibObj.dialog.close();
	}
	if(LibObj.IsErrLog()==false){
		QMessageBox::information(this, QString("メッセージ"), QString("正常に処理が終了しました。"));
	}
	else{
		//ErrDialogにエラーの発生したログを表示する
		LibObj.ClearErrDialogLogs();
		QMessageBox::warning(this, QString("警告"), QString("エラーの発生したログがあります！"));
		LibObj.showErrLog();

		//ファイルにも落とす
		if ( LibObj.outErrLog(Date) == false ) {
			QMessageBox::critical(this, QString("エラー"), QString("なんらかの原因で発生したファイルの入出力エラーにより、エラーログの出力に失敗しました。再度処理を実行してみるか、出力先フォルダ名・HD・ログファイルなどを確認してください。"));
		}
	}
}
