#include "GraphinDetailForm.h"
#include "windows.h"
#include "atlstr.h"
#include "ipm8540.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "XDateTime.h"
#include <QFileDialog>
#include <QMessageBox>
#include <psapi.h>

GraphinDetailForm::GraphinDetailForm(Qt::HANDLE handle, const QString &CameraConfigFileName, const QString &CameraDllName, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//初期化
	setExposureTime(0);
	setRedCustomLut(NULL);
	setGreenCustomLut(NULL);
	setBlueCustomLut(NULL);
	setProofDataFileName(QString());
	setRtoL(0);
	setEnable32bitMode(false);
	//BuffcRxLine	=NULL;
	setCameraConfigFileName(CameraConfigFileName);
/*
	//カメラDLL名を取得
	char CamDllName[_MAX_PATH];
	GetModuleFileName(NULL,CamDllName,sizeof(CamDllName));
	CameraDLL=QString(CamDllName);
*/
	// --------------------------------------------
	//	ﾊﾞｰｼﾞｮﾝ情報取得
	// --------------------------------------------
	ULONG	ulHwVer, ulDllVer, CLver;
	mgGetVersion( handle, &ulHwVer, &ulDllVer );
	QString DeviceName;
	switch( ulHwVer & 0xe0 ){
	// IPM-8530
	case TYPE30:		DeviceName = "IPM-8530";		break;
	// IPM-8530CL
	case TYPE30CL:		DeviceName = "IPM-8530CL";		break;
	// IPM-8530CLTEST
	case TYPE30CLTEST:	DeviceName = "IPM-8530CLTEST";	break;
	// IPM-8540A使用
	case TYPE40A:		DeviceName = "IPM-8540A";		break;
	// IPM-8540D使用
	case TYPE40D:		DeviceName = "IPM-8540D";		break;
	// その他
	default:			DeviceName = "その他";			break;
	}
	if(DeviceName.left(10)=="IPM-8530CL"){
		mgGetVersionEX( handle, &CLver);
		switch(CLver){
		// IPM-8530CL-B
		case TYPE30CLB:	DeviceName = "IPM-8530CL-B";	break;
		// IPM-8530CL-M
		case TYPE30CLM:	DeviceName = "IPM-8530CL-M";	break;
		// IPM-8530CL-F
		case TYPE30CLF:	DeviceName = "IPM-8530CL-F";	break;
		// IPM-8580CL-M
		case TYPE80CLM:	DeviceName = "IPM-8580CL-M";	break;
		// IPM-8580CL-F
		case TYPE80CLF:	DeviceName = "IPM-8580CL-F";	break;
		}
	}
	setDeviceName(DeviceName);
	setDeviceRevision(QString::number(ulHwVer & 0x1f));
	setDeviceDLLVersion(QString::number(ulDllVer));

	//現在のプロセスのがロードしているモジュールの一覧を表示
	HANDLE hProcess;
	HMODULE ModuleHandles[1000];
	DWORD ModuleNum;
	DWORD ReturnSize;
	wchar_t BaseName[_MAX_PATH];
	wchar_t FileName[_MAX_PATH];
	const char *DeviceDllName = "ipm8540.dll";
	//現在のプロセスのハンドルを取得
	hProcess = GetCurrentProcess();
	//現在のプロセスにロードされているモジュールのハンドルと数を取得
	EnumProcessModules(hProcess,ModuleHandles,sizeof(ModuleHandles),&ReturnSize);
	ModuleNum=ReturnSize/sizeof(HMODULE);
	//結果の表示
	/*
	for(DWORD i=0; i<ModuleNum; i++){
		//ベース名およびファイル名を取得
		GetModuleBaseName(hProcess,ModuleHandles[i],BaseName,_MAX_PATH);
		if(strcmp(BaseName,DeviceDllName)==0){
			GetModuleFileName(ModuleHandles[i],FileName,_MAX_PATH);
			setDeviceDLLFileName(FileName);
		}
		if(BaseName==CameraDllName){
			GetModuleFileName(ModuleHandles[i],FileName,_MAX_PATH);
			setCameraDLLFileName(FileName);
		}
		if(deviceDLLFileName().isEmpty()==false && cameraDLLFileName().isEmpty()==false){
			break;
		}
	}
	*/

	//デバイスの状態
	IPMGRABSTS	GrabSts;
	mgGetGrabberStatus(handle,&GrabSts);
	if(GrabSts.transfer){
		setDeviceState("画像取り込み転送中。");
	}
	else if(GrabSts.dmastatus){
		setDeviceState("画像取り込み正常完了。");
	}
	else{
		setDeviceState("画像取り込み待ち。");
	}
	if(GrabSts.overrun){
		setDeviceState("オーバーランが発生しました。");
	}
}

GraphinDetailForm::~GraphinDetailForm()
{

}

void GraphinDetailForm::on_pbClose_clicked()
{
	close();
}

void GraphinDetailForm::on_pbOutputLog_clicked()
{
	//ログを出力
	QString AppPath	=qApp->applicationDirPath();
	QString strPath	=AppPath + QDir::separator() + "CameraLog.log";
	QString FileName=QFileDialog::getSaveFileName(this,tr("Save Log File"),strPath,tr("Log File (*.log)"));
	QFile	mfile(FileName);
	if(mfile.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&mfile);
		mystream << XDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") << endl;
		mystream << QString("【カメラDLL】") << endl;
		mystream << cameraDLLFileName() << endl;
		mystream << QString("【デバイス種類】") << endl;
		mystream << deviceName() << endl;
		mystream << QString("【デバイスリビジョン】") << endl;
		mystream << deviceRevision() << endl;
		mystream << QString("【デバイスDLLバージョン】") << endl;
		mystream << deviceDLLVersion() << endl;
		mystream << QString("【デバイスDLL】") << endl;
		mystream << deviceDLLFileName() << endl;
		mystream << QString("【コンフィグファイル】") << endl;
		mystream << cameraConfigFileName() << endl;
		mystream << QString("【デバイスステータス】") << endl;
		mystream << deviceState() << endl;
		mystream << QString("【露光時間】") << endl;
		mystream << QString::number(exposureTime()) << endl;
		mystream << QString("【Redルックアップテーブル】") << endl;
		for(int i=0;i<256;i++){
			mystream << QString::number(redCustomLut(i)) << ",";
		}
		mystream << endl;
		mystream << QString("【Greenルックアップテーブル】") << endl;
		for(int i=0;i<256;i++){
			mystream << QString::number(greenCustomLut(i)) << ",";
		}
		mystream << endl;
		mystream << QString("【Blueルックアップテーブル】") << endl;
		for(int i=0;i<256;i++){
			mystream << QString::number(blueCustomLut(i)) << ",";
		}
		mystream << endl;
		mystream << QString("【校正データファイル】") << endl;
		mystream << proofDataFileName() << endl;
		mystream << QString("【左右入れ替えチェック】") << endl;
		if(isRToL()==0){
			mystream << "Off" << endl;
		}
		else{
			mystream << "On" << endl;
		}
		mystream << QString("【バス32bitモード】") << endl;
		if(isEnable32bitMode()==true){
			mystream << "On" << endl;
		}
		else{
			mystream << "Off" << endl;
		}
		mystream << QString("【カメラ内部データ】") << endl;
		mystream << cRxLineBuff() << endl;
		mystream << QString("【DLLログデータ】") << endl;

		const QStringList list = dllLogString();
		for(int i=0; i<list.count(); i++){
			mystream << list[i] << endl;
		}
		mfile.close();
	}
	else{
		QMessageBox::warning(this,tr("Error"),FileName + tr(" is open error!"));
	}
}
