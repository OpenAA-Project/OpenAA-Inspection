/*
 * Copyright (C) 2026
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

#include "EditWizardParameter.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include "XOpenAA.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QLibrary>
#include <QMessageBox>
#include <QPushButton>

EditWizardParameter::EditWizardParameter(LayersBase *base
					,const QString &targetDir
					,QWidget *parent
					,Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, ServiceForLayers(base)
	, CurrentParam(base)
	, MachineInfoRegistry(nullptr)
	, CurrentCameraIndex(0)
	, CurrentAllocPageIndex(0)
	, CurrentStrategyPageIndex(0)
{
	ui.setupUi(this);

	TargetDir = targetDir.isEmpty() ? QDir::currentPath() : targetDir;
	AppBaseDir = QDir::currentPath();

	QDir dir(TargetDir);
	GlobalDatFilePath	= dir.filePath(QStringLiteral("Global.dat"));
	MachineInfoFilePath	= dir.filePath(QStringLiteral("MachineInfo.dat"));

	MachineInfoRegistry = new FileRegistry(MachineInfoFilePath);

	ui.labelTargetDir->setText(QStringLiteral("設定ディレクトリ: ") + QDir::toNativeSeparators(TargetDir));
	setWindowTitle(QStringLiteral("EditWizardParameter : ") + QDir::toNativeSeparators(TargetDir));

	// 全ページの「前」「次」ボタンを一括接続
	const QList<QPushButton *> buttons = ui.stackedWidget->findChildren<QPushButton *>();
	for(QPushButton *btn : buttons){
		if(btn->objectName().startsWith(QStringLiteral("pushButtonPrev_"))){
			connect(btn, &QPushButton::clicked, this, &EditWizardParameter::SlotPrevPage);
		}
		else if(btn->objectName().startsWith(QStringLiteral("pushButtonNext_"))){
			connect(btn, &QPushButton::clicked, this, &EditWizardParameter::SlotNextPage);
		}
	}

	ui.pushButtonPrev_0->setEnabled(false);
	ui.pushButtonNext_31->setEnabled(false);

	InitPluginComboBoxes();
	LoadInitialValues();

	ui.stackedWidget->setCurrentIndex(Page_Language);
	UpdateStepProgress();
}

EditWizardParameter::~EditWizardParameter()
{
	delete MachineInfoRegistry;
	MachineInfoRegistry = nullptr;
}

QString EditWizardParameter::GetPluginDLLFolder() const
{
	QString dirPath = QDir(AppBaseDir).filePath(QStringLiteral("PluginDLL"));
	if(QDir(dirPath).exists()){
		return dirPath;
	}
	return QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("PluginDLL"));
}

QString EditWizardParameter::GetPluginFileFilter() const
{
#ifdef Q_OS_WIN
	return QStringLiteral("Plugin DLL (*.dll);;All Files (*.*)");
#else
	return QStringLiteral("Plugin Shared Object (*.so);;All Files (*)");
#endif
}

QStringList EditWizardParameter::ScanPluginDLLs(const QString &searchDir, WORD targetDLLType, bool relativeToBase) const
{
	QStringList result;
	QDir dir(searchDir);
	if(!dir.exists()){
		return result;
	}

	QStringList nameFilters;
#ifdef Q_OS_WIN
	nameFilters << QStringLiteral("*.dll");
#else
	nameFilters << QStringLiteral("*.so");
#endif

	const QFileInfoList entries = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	const QDir baseDir(AppBaseDir);

	for(const QFileInfo &fi : entries){
		const QString absPath = fi.absoluteFilePath();
		QLibrary lib(absPath);
		if(!lib.load()){
			continue;
		}
		using DLLGetDLLTypeFunc = WORD (*)(void);
		DLLGetDLLTypeFunc getDLLType = reinterpret_cast<DLLGetDLLTypeFunc>(lib.resolve("DLL_GetDLLType"));
		if(getDLLType != nullptr){
			WORD dllType = getDLLType();
			if(dllType == targetDLLType){
				if(relativeToBase){
					result.append(baseDir.relativeFilePath(absPath));
				}
				else{
					result.append(fi.fileName());
				}
			}
		}
		lib.unload();
	}
	return result;
}

void EditWizardParameter::PopulateComboBox(QComboBox *combo, const QStringList &items, const QString &currentValue)
{
	combo->clear();
	combo->addItem(QString());
	combo->addItems(items);
	combo->setCurrentText(currentValue);
}

void EditWizardParameter::InitPluginComboBoxes()
{
	const QString pluginDir = GetPluginDLLFolder();
	const QString appDir    = QCoreApplication::applicationDirPath();

	PopulateComboBox(ui.comboBoxCameraPlugin,
					 ScanPluginDLLs(pluginDir, DLLCameraMode, true),
					 QString());
	PopulateComboBox(ui.comboBoxLightPlugin,
					 ScanPluginDLLs(pluginDir, DLLLightMode, true),
					 QString());
	PopulateComboBox(ui.comboBoxPIOPlugin,
					 ScanPluginDLLs(pluginDir, DLLPIOMode, true),
					 QString());

	// 結果・GeneralStocker はプログラム起動フォルダー内を検索
	QStringList resultPlugins = ScanPluginDLLs(appDir, DLLResultMode, false);
	if(resultPlugins.isEmpty() && QDir(appDir) != QDir(AppBaseDir)){
		resultPlugins = ScanPluginDLLs(AppBaseDir, DLLResultMode, false);
	}
	PopulateComboBox(ui.comboBoxResultPlugin, resultPlugins, QString());

	QStringList stockerPlugins = ScanPluginDLLs(appDir, DLLGeneralStockerMode, false);
	if(stockerPlugins.isEmpty() && QDir(appDir) != QDir(AppBaseDir)){
		stockerPlugins = ScanPluginDLLs(AppBaseDir, DLLGeneralStockerMode, false);
	}
	PopulateComboBox(ui.comboBoxGeneralStockerPlugin, stockerPlugins, QString());
}

void EditWizardParameter::LoadInitialValues()
{
	// 1. MachineInfo.dat の読み込み
	int language = MachineInfoRegistry->LoadRegInt(QStringLiteral("Language"), 0);
	if(language < 0 || language >= ui.comboBoxLanguage->count()){
		language = 0;
	}
	ui.comboBoxLanguage->setCurrentIndex(language);

	// 2. Global.dat の読み込み
	QFile globalFile(GlobalDatFilePath);
	if(globalFile.open(QIODevice::ReadOnly)){
		CurrentParam.LoadParam(&globalFile);
		globalFile.close();
	}

	// カメラ台数・各カメラ設定の初期化
	int totalCam = CurrentParam.TotalCameraNumb;
	if(totalCam < 0){
		totalCam = 0;
	}
	ui.spinBoxTotalCameraNumb->setValue(totalCam);

	CameraEntries.clear();
	EnsureCameraEntriesSize(qMax(totalCam, 4));

	auto parseCamNo = [](const QString &allocStr, int defaultNo) -> int {
		bool ok = false;
		int val = allocStr.section(QLatin1Char(','), 0, 0).trimmed().toInt(&ok);
		return (ok && val >= 0) ? val : defaultNo;
	};

	CameraEntries[0].PluginFileName = CurrentParam.CameraDLL_FileName;
	CameraEntries[0].ParamStr       = CurrentParam.CameraParameter;
	CameraEntries[0].CameraNo       = parseCamNo(CurrentParam.CameraAllocation, 0);

	CameraEntries[1].PluginFileName = CurrentParam.CameraDLL_FileName2;
	CameraEntries[1].ParamStr       = CurrentParam.CameraParameter2;
	CameraEntries[1].CameraNo       = parseCamNo(CurrentParam.CameraAllocation2, 1);

	CameraEntries[2].PluginFileName = CurrentParam.CameraDLL_FileName3;
	CameraEntries[2].ParamStr       = CurrentParam.CameraParameter3;
	CameraEntries[2].CameraNo       = parseCamNo(CurrentParam.CameraAllocation3, 2);

	CameraEntries[3].PluginFileName = CurrentParam.CameraDLL_FileName4;
	CameraEntries[3].ParamStr       = CurrentParam.CameraParameter4;
	CameraEntries[3].CameraNo       = parseCamNo(CurrentParam.CameraAllocation4, 3);

	// 画像サイズ・分解能・レイヤー・ページ
	ui.spinBoxDotPerLine->setValue(CurrentParam.DotPerLine);
	ui.spinBoxMaxLines->setValue(CurrentParam.MaxLines);
	ui.spinBoxResolutionYNano->setValue(CurrentParam.ResolutionYNano);
	ui.spinBoxResolutionXNano->setValue(CurrentParam.ResolutionXNano);
	ui.spinBoxLayerNumb->setValue(qMax(1, static_cast<int>(CurrentParam.LayerNumb)));

	int pageNumb = qMax(1, static_cast<int>(CurrentParam.PageNumb));
	ui.spinBoxPageNumb->setValue(pageNumb);

	// ページごとのカメラ割り当て
	PageCameraAllocList.clear();
	PageCameraAllocList.resize(pageNumb);
	for(int p = 0; p < pageNumb; ++p){
		int camNo = CurrentParam.GetCameraNo(p);
		if(camNo < 0){
			camNo = (totalCam > 0) ? qMin(p, totalCam - 1) : 0;
		}
		PageCameraAllocList[p] = camNo;
	}

	// 画像の並べ方
	int arrange = CurrentParam.DefaultImageArrange;
	if(arrange < 0 || arrange >= ui.comboBoxImageArrange->count()){
		arrange = 0;
	}
	ui.comboBoxImageArrange->setCurrentIndex(arrange);

	// シーケンス戦略数・ページごとの戦略番号
	int maxStrategy = qMax(1, CurrentParam.GetMaxStrategyCount());
	ui.spinBoxMaxStrategyCount->setValue(maxStrategy);

	PageStrategyList.clear();
	PageStrategyList.resize(pageNumb);
	for(int p = 0; p < pageNumb; ++p){
		int s = CurrentParam.GetStrategyCode(p, 0);
		if(s < 0 || s >= maxStrategy){
			s = 0;
		}
		PageStrategyList[p] = s;
	}

	// 照明
	ui.comboBoxLightPlugin->setCurrentText(CurrentParam.LightDLLFileName);
	ui.lineEditLightParam->setText(CurrentParam.LightParamStr);
	ui.checkBoxInitialLightON->setChecked(CurrentParam.InitialLightON);

	// PIO
	ui.comboBoxPIOPlugin->setCurrentText(CurrentParam.IODLL_FileName);
	ui.lineEditPIOParam->setText(CurrentParam.IOSomething);

	// データベース
	ui.lineEditDBHost->setText(
		CurrentParam.LocalDatabase_HostName.isEmpty()
			? QStringLiteral("127.1.1.1")
			: CurrentParam.LocalDatabase_HostName);
	ui.spinBoxDBPort->setValue(
		CurrentParam.LocalDatabase_Port > 0
			? CurrentParam.LocalDatabase_Port
			: 3050);
	ui.lineEditDBFile->setText(CurrentParam.LocalDatabase_FileName);

	// マスターデータ保存先
	ui.lineEditMasterFolder->setText(CurrentParam.ImageFilePath);

	// 結果プラグイン / GeneralStocker
	ui.comboBoxResultPlugin->setCurrentText(CurrentParam.ResultDLLFileName);
	ui.comboBoxGeneralStockerPlugin->setCurrentText(CurrentParam.GeneralStockerFileName1);
	ui.lineEditGeneralStockerParam->setText(CurrentParam.GeneralStockerFileName);

	// マルチコア使用 (CalcSingleThread の反転)
	ui.checkBoxMultiCore->setChecked(!CurrentParam.CalcSingleThread);

	// シーケンスファイル名
	ui.lineEditSequenceFile->setText(
		CurrentParam.Sequence_FileName.isEmpty()
			? QStringLiteral("Sequence.dat")
			: CurrentParam.Sequence_FileName);

	// 最大検査時間・最大NG個数
	ui.spinBoxMaxInspectMilisec->setValue(CurrentParam.MaxInspectMilisec);
	ui.spinBoxMaxNGCountsPerCam->setValue(CurrentParam.MaxNGCountsPerCam);
}

void EditWizardParameter::EnsureCameraEntriesSize(int count)
{
	int oldSize = CameraEntries.size();
	if(count > oldSize){
		CameraEntries.resize(count);
		for(int i = oldSize; i < count; ++i){
			CameraEntries[i].CameraNo = i;
		}
	}
}

void EditWizardParameter::EnsurePageArraysSize(int pageCount)
{
	int maxCam = qMax(0, ui.spinBoxTotalCameraNumb->value() - 1);
	int oldAllocSize = PageCameraAllocList.size();
	if(pageCount > oldAllocSize){
		PageCameraAllocList.resize(pageCount);
		for(int p = oldAllocSize; p < pageCount; ++p){
			PageCameraAllocList[p] = qMin(p, maxCam);
		}
	}

	int oldStratSize = PageStrategyList.size();
	if(pageCount > oldStratSize){
		PageStrategyList.resize(pageCount);
		for(int p = oldStratSize; p < pageCount; ++p){
			PageStrategyList[p] = 0;
		}
	}
}

void EditWizardParameter::LoadCameraUI(int camIdx)
{
	EnsureCameraEntriesSize(camIdx + 1);
	const int dispNo = camIdx + 1;

	ui.labelCameraPluginTitle->setText(
		QStringLiteral("カメラ %1 台目のプラグインファイル名").arg(dispNo));
	ui.labelCameraParamTitle->setText(
		QStringLiteral("カメラ %1 台目の設定（無設定あるいはIPアドレスなど）").arg(dispNo));
	ui.labelCameraNoTitle->setText(
		QStringLiteral("カメラ %1 台目のカメラ番号（0から）").arg(dispNo));

	ui.comboBoxCameraPlugin->setCurrentText(CameraEntries[camIdx].PluginFileName);
	ui.lineEditCameraParam->setText(CameraEntries[camIdx].ParamStr);
	ui.spinBoxCameraNo->setValue(CameraEntries[camIdx].CameraNo);
}

void EditWizardParameter::SaveCameraUI(int camIdx)
{
	EnsureCameraEntriesSize(camIdx + 1);
	CameraEntries[camIdx].PluginFileName = ui.comboBoxCameraPlugin->currentText().trimmed();
	CameraEntries[camIdx].ParamStr       = ui.lineEditCameraParam->text().trimmed();
	CameraEntries[camIdx].CameraNo       = ui.spinBoxCameraNo->value();
}

void EditWizardParameter::LoadPageCameraAllocUI(int pageIdx)
{
	int pageCount = ui.spinBoxPageNumb->value();
	EnsurePageArraysSize(pageCount);

	int maxCamNo = qMax(0, ui.spinBoxTotalCameraNumb->value() - 1);
	ui.spinBoxPageCameraNo->setMinimum(0);
	ui.spinBoxPageCameraNo->setMaximum(maxCamNo);

	ui.labelPageCameraAllocTitle->setText(
		QStringLiteral("画像ページ %1 に割り当てるカメラ番号（0 ～ %2）")
			.arg(pageIdx + 1)
			.arg(maxCamNo));

	int val = qBound(0, PageCameraAllocList[pageIdx], maxCamNo);
	PageCameraAllocList[pageIdx] = val;
	ui.spinBoxPageCameraNo->setValue(val);
}

void EditWizardParameter::SavePageCameraAllocUI(int pageIdx)
{
	EnsurePageArraysSize(pageIdx + 1);
	PageCameraAllocList[pageIdx] = ui.spinBoxPageCameraNo->value();
}

void EditWizardParameter::LoadPageStrategyUI(int pageIdx)
{
	int pageCount = ui.spinBoxPageNumb->value();
	EnsurePageArraysSize(pageCount);

	int maxStratNo = qMax(0, ui.spinBoxMaxStrategyCount->value() - 1);
	ui.spinBoxPageStrategyNo->setMinimum(0);
	ui.spinBoxPageStrategyNo->setMaximum(maxStratNo);

	ui.labelPageStrategyTitle->setText(
		QStringLiteral("ページ番号 %1 に設定するシーケンス戦略番号（0 ～ %2）")
			.arg(pageIdx + 1)
			.arg(maxStratNo));

	int val = qBound(0, PageStrategyList[pageIdx], maxStratNo);
	PageStrategyList[pageIdx] = val;
	ui.spinBoxPageStrategyNo->setValue(val);
}

void EditWizardParameter::SavePageStrategyUI(int pageIdx)
{
	EnsurePageArraysSize(pageIdx + 1);
	PageStrategyList[pageIdx] = ui.spinBoxPageStrategyNo->value();
}

void EditWizardParameter::SlotNextPage()
{
	const int cur = ui.stackedWidget->currentIndex();
	const int totalCam = ui.spinBoxTotalCameraNumb->value();
	const int pageNumb = ui.spinBoxPageNumb->value();
	const int maxStrat = ui.spinBoxMaxStrategyCount->value();

	switch(cur){
	case Page_CameraCount:
		EnsureCameraEntriesSize(totalCam);
		if(totalCam >= 1){
			CurrentCameraIndex = 0;
			LoadCameraUI(CurrentCameraIndex);
			ui.stackedWidget->setCurrentIndex(Page_CameraPlugin);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_DotPerLine);
		}
		break;

	case Page_CameraPlugin:
		SaveCameraUI(CurrentCameraIndex);
		ui.stackedWidget->setCurrentIndex(Page_CameraParam);
		break;

	case Page_CameraParam:
		SaveCameraUI(CurrentCameraIndex);
		ui.stackedWidget->setCurrentIndex(Page_CameraNo);
		break;

	case Page_CameraNo:
		SaveCameraUI(CurrentCameraIndex);
		if(CurrentCameraIndex + 1 < totalCam){
			CurrentCameraIndex++;
			LoadCameraUI(CurrentCameraIndex);
			ui.stackedWidget->setCurrentIndex(Page_CameraPlugin);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_DotPerLine);
		}
		break;

	case Page_PageNumb:
		EnsurePageArraysSize(pageNumb);
		CurrentAllocPageIndex = 0;
		LoadPageCameraAllocUI(CurrentAllocPageIndex);
		ui.stackedWidget->setCurrentIndex(Page_PageCameraAlloc);
		break;

	case Page_PageCameraAlloc:
		SavePageCameraAllocUI(CurrentAllocPageIndex);
		if(CurrentAllocPageIndex + 1 < pageNumb){
			CurrentAllocPageIndex++;
			LoadPageCameraAllocUI(CurrentAllocPageIndex);
		}
		else if(pageNumb >= 2){
			ui.stackedWidget->setCurrentIndex(Page_ImageArrange);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_StrategyCount);
		}
		break;

	case Page_StrategyCount:
		if(maxStrat >= 2 && pageNumb >= 2){
			EnsurePageArraysSize(pageNumb);
			CurrentStrategyPageIndex = 0;
			LoadPageStrategyUI(CurrentStrategyPageIndex);
			ui.stackedWidget->setCurrentIndex(Page_PageStrategy);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_LightPlugin);
		}
		break;

	case Page_PageStrategy:
		SavePageStrategyUI(CurrentStrategyPageIndex);
		if(CurrentStrategyPageIndex + 1 < pageNumb){
			CurrentStrategyPageIndex++;
			LoadPageStrategyUI(CurrentStrategyPageIndex);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_LightPlugin);
		}
		break;

	case Page_MaxNGCount:
		ui.labelSaveInfo->setText(
			QStringLiteral("以下のファイルに上書き保存します:\n%1\n%2")
				.arg(QDir::toNativeSeparators(GlobalDatFilePath))
				.arg(QDir::toNativeSeparators(MachineInfoFilePath)));
		ui.stackedWidget->setCurrentIndex(Page_Save);
		break;

	default:
		if(cur + 1 < ui.stackedWidget->count()){
			ui.stackedWidget->setCurrentIndex(cur + 1);
		}
		break;
	}

	UpdateStepProgress();
}

void EditWizardParameter::SlotPrevPage()
{
	const int cur = ui.stackedWidget->currentIndex();
	const int totalCam = ui.spinBoxTotalCameraNumb->value();
	const int pageNumb = ui.spinBoxPageNumb->value();
	const int maxStrat = ui.spinBoxMaxStrategyCount->value();

	switch(cur){
	case Page_Language:
		break;

	case Page_CameraPlugin:
		SaveCameraUI(CurrentCameraIndex);
		if(CurrentCameraIndex > 0){
			CurrentCameraIndex--;
			LoadCameraUI(CurrentCameraIndex);
			ui.stackedWidget->setCurrentIndex(Page_CameraNo);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_CameraCount);
		}
		break;

	case Page_CameraParam:
		SaveCameraUI(CurrentCameraIndex);
		ui.stackedWidget->setCurrentIndex(Page_CameraPlugin);
		break;

	case Page_CameraNo:
		SaveCameraUI(CurrentCameraIndex);
		ui.stackedWidget->setCurrentIndex(Page_CameraParam);
		break;

	case Page_DotPerLine:
		if(totalCam >= 1){
			CurrentCameraIndex = totalCam - 1;
			LoadCameraUI(CurrentCameraIndex);
			ui.stackedWidget->setCurrentIndex(Page_CameraNo);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_CameraCount);
		}
		break;

	case Page_PageCameraAlloc:
		SavePageCameraAllocUI(CurrentAllocPageIndex);
		if(CurrentAllocPageIndex > 0){
			CurrentAllocPageIndex--;
			LoadPageCameraAllocUI(CurrentAllocPageIndex);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_PageNumb);
		}
		break;

	case Page_ImageArrange:
		CurrentAllocPageIndex = pageNumb - 1;
		LoadPageCameraAllocUI(CurrentAllocPageIndex);
		ui.stackedWidget->setCurrentIndex(Page_PageCameraAlloc);
		break;

	case Page_StrategyCount:
		if(pageNumb >= 2){
			ui.stackedWidget->setCurrentIndex(Page_ImageArrange);
		}
		else{
			CurrentAllocPageIndex = pageNumb - 1;
			LoadPageCameraAllocUI(CurrentAllocPageIndex);
			ui.stackedWidget->setCurrentIndex(Page_PageCameraAlloc);
		}
		break;

	case Page_PageStrategy:
		SavePageStrategyUI(CurrentStrategyPageIndex);
		if(CurrentStrategyPageIndex > 0){
			CurrentStrategyPageIndex--;
			LoadPageStrategyUI(CurrentStrategyPageIndex);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_StrategyCount);
		}
		break;

	case Page_LightPlugin:
		if(maxStrat >= 2 && pageNumb >= 2){
			CurrentStrategyPageIndex = pageNumb - 1;
			LoadPageStrategyUI(CurrentStrategyPageIndex);
			ui.stackedWidget->setCurrentIndex(Page_PageStrategy);
		}
		else{
			ui.stackedWidget->setCurrentIndex(Page_StrategyCount);
		}
		break;

	default:
		if(cur > 0){
			ui.stackedWidget->setCurrentIndex(cur - 1);
		}
		break;
	}

	UpdateStepProgress();
}

int EditWizardParameter::CalcTotalDynamicSteps() const
{
	const int totalCam = ui.spinBoxTotalCameraNumb->value();
	const int pageNumb = ui.spinBoxPageNumb->value();
	const int maxStrat = ui.spinBoxMaxStrategyCount->value();

	int steps = 2;                          // Language, CameraCount
	steps += totalCam * 3;                  // Camera (Plugin, Param, No) x N
	steps += 6;                             // DotPerLine, MaxLines, ResY, ResX, LayerNumb, PageNumb
	steps += pageNumb;                      // PageCameraAlloc x PageNumb
	if(pageNumb >= 2){
		steps += 1;                         // ImageArrange
	}
	steps += 1;                             // StrategyCount
	if(maxStrat >= 2 && pageNumb >= 2){
		steps += pageNumb;                  // PageStrategy x PageNumb
	}
	steps += 17;                            // Light(3) + PIO(2) + DB(3) + Master(1) + Result(1) + Stocker(2) + MultiCore(1) + Seq(1) + MaxTime(1) + MaxNG(1) + Save(1)
	return steps;
}

int EditWizardParameter::CalcCurrentDynamicStep() const
{
	const int cur      = ui.stackedWidget->currentIndex();
	const int totalCam = ui.spinBoxTotalCameraNumb->value();
	const int pageNumb = ui.spinBoxPageNumb->value();
	const int maxStrat = ui.spinBoxMaxStrategyCount->value();

	if(cur <= Page_CameraCount){
		return cur + 1;
	}
	int base = 2;
	if(cur >= Page_CameraPlugin && cur <= Page_CameraNo){
		return base + CurrentCameraIndex * 3 + (cur - Page_CameraPlugin) + 1;
	}
	base += totalCam * 3;
	if(cur >= Page_DotPerLine && cur <= Page_PageNumb){
		return base + (cur - Page_DotPerLine) + 1;
	}
	base += 6;
	if(cur == Page_PageCameraAlloc){
		return base + CurrentAllocPageIndex + 1;
	}
	base += pageNumb;
	if(cur == Page_ImageArrange){
		return base + 1;
	}
	if(pageNumb >= 2){
		base += 1;
	}
	if(cur == Page_StrategyCount){
		return base + 1;
	}
	base += 1;
	if(cur == Page_PageStrategy){
		return base + CurrentStrategyPageIndex + 1;
	}
	if(maxStrat >= 2 && pageNumb >= 2){
		base += pageNumb;
	}
	return base + (cur - Page_LightPlugin) + 1;
}

void EditWizardParameter::UpdateStepProgress()
{
	const int totalSteps = CalcTotalDynamicSteps();
	const int curStep    = qBound(1, CalcCurrentDynamicStep(), totalSteps);

	ui.progressBar->setMinimum(1);
	ui.progressBar->setMaximum(totalSteps);
	ui.progressBar->setValue(curStep);
	ui.labelStep->setText(QStringLiteral("ステップ %1 / %2").arg(curStep).arg(totalSteps));
}

void EditWizardParameter::on_pushButtonBrowseCameraPlugin_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("カメラプラグインファイルの選択"),
		GetPluginDLLFolder(),
		GetPluginFileFilter());
	if(!filePath.isEmpty()){
		ui.comboBoxCameraPlugin->setCurrentText(QDir(AppBaseDir).relativeFilePath(filePath));
	}
}

void EditWizardParameter::on_pushButtonBrowseLightPlugin_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("照明プラグインファイルの選択"),
		GetPluginDLLFolder(),
		GetPluginFileFilter());
	if(!filePath.isEmpty()){
		ui.comboBoxLightPlugin->setCurrentText(QDir(AppBaseDir).relativeFilePath(filePath));
	}
}

void EditWizardParameter::on_pushButtonBrowsePIOPlugin_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("PIOプラグインファイルの選択"),
		GetPluginDLLFolder(),
		GetPluginFileFilter());
	if(!filePath.isEmpty()){
		ui.comboBoxPIOPlugin->setCurrentText(QDir(AppBaseDir).relativeFilePath(filePath));
	}
}

void EditWizardParameter::on_pushButtonBrowseDBFile_clicked()
{
	QString startDir = QFileInfo(ui.lineEditDBFile->text()).absolutePath();
	if(startDir.isEmpty()){
		startDir = TargetDir;
	}
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("データベースファイルの選択"),
		startDir,
		QStringLiteral("Firebird Database (*.fdb *.gdb);;All Files (*.*)"));
	if(!filePath.isEmpty()){
		ui.lineEditDBFile->setText(QDir::toNativeSeparators(QFileInfo(filePath).absoluteFilePath()));
	}
}

void EditWizardParameter::on_pushButtonBrowseMasterFolder_clicked()
{
	QString startDir = ui.lineEditMasterFolder->text();
	if(startDir.isEmpty()){
		startDir = TargetDir;
	}
	QString dirPath = QFileDialog::getExistingDirectory(
		this,
		QStringLiteral("マスターデータ保存先フォルダーの選択"),
		startDir);
	if(!dirPath.isEmpty()){
		ui.lineEditMasterFolder->setText(QDir::toNativeSeparators(QDir(dirPath).absolutePath()));
	}
}

void EditWizardParameter::on_pushButtonBrowseSequenceFile_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("シーケンスファイルの選択"),
		TargetDir,
		QStringLiteral("Sequence File (*.dat);;All Files (*.*)"));
	if(!filePath.isEmpty()){
		ui.lineEditSequenceFile->setText(QDir(TargetDir).relativeFilePath(filePath));
	}
}

void EditWizardParameter::on_pushButtonSave_clicked()
{
	// 保存先ディレクトリを保証
	QDir().mkpath(TargetDir);

	const int totalCam  = ui.spinBoxTotalCameraNumb->value();
	const int pageNumb  = ui.spinBoxPageNumb->value();
	const int layerNumb = ui.spinBoxLayerNumb->value();
	const int maxStrat  = ui.spinBoxMaxStrategyCount->value();

	EnsureCameraEntriesSize(qMax(totalCam, 4));
	EnsurePageArraysSize(pageNumb);

	// 基本画像・構成パラメーター
	CurrentParam.TotalCameraNumb = totalCam;
	CurrentParam.DotPerLine      = ui.spinBoxDotPerLine->value();
	CurrentParam.MaxLines        = ui.spinBoxMaxLines->value();
	CurrentParam.ResolutionYNano = ui.spinBoxResolutionYNano->value();
	CurrentParam.ResolutionXNano = ui.spinBoxResolutionXNano->value();
	CurrentParam.LayerNumb       = layerNumb;
	CurrentParam.PageNumb        = pageNumb;

	// カメラ設定 (ParamGlobal の 4 スロットへ反映)
	auto applyCameraSlot = [&](int idx, QString &dllName, QString &paramStr, QString &allocStr) {
		if(idx < totalCam){
			dllName  = CameraEntries[idx].PluginFileName;
			paramStr = CameraEntries[idx].ParamStr;
			allocStr = QString::number(CameraEntries[idx].CameraNo);
		}
		else{
			dllName.clear();
			paramStr.clear();
			allocStr.clear();
		}
	};
	applyCameraSlot(0, CurrentParam.CameraDLL_FileName,  CurrentParam.CameraParameter,  CurrentParam.CameraAllocation);
	applyCameraSlot(1, CurrentParam.CameraDLL_FileName2, CurrentParam.CameraParameter2, CurrentParam.CameraAllocation2);
	applyCameraSlot(2, CurrentParam.CameraDLL_FileName3, CurrentParam.CameraParameter3, CurrentParam.CameraAllocation3);
	applyCameraSlot(3, CurrentParam.CameraDLL_FileName4, CurrentParam.CameraParameter4, CurrentParam.CameraAllocation4);

	// 画像ページへのカメラ割り当て
	CurrentParam.ReallocCamAllocInPages();
	const int maxCamNo = qMax(0, totalCam - 1);
	for(int p = 0; p < pageNumb; ++p){
		int camNo = (totalCam > 0) ? qBound(0, PageCameraAllocList[p], maxCamNo) : -1;
		CurrentParam.SetCameraNo(p, camNo);
	}

	// 画像の並べ方
	if(pageNumb >= 2){
		CurrentParam.DefaultImageArrange = ui.comboBoxImageArrange->currentIndex();
	}

	// シーケンス戦略
	CurrentParam.SetMaxStrategyCount(maxStrat);
	CurrentParam.ReallocStrategy();
	for(int p = 0; p < pageNumb; ++p){
		int stratCode = (maxStrat >= 2 && pageNumb >= 2)
			? qBound(0, PageStrategyList[p], maxStrat - 1)
			: 0;
		for(int layer = 0; layer < layerNumb; ++layer){
			CurrentParam.SetStrategyCode(p, layer, stratCode);
		}
	}

	// 照明
	CurrentParam.LightDLLFileName = ui.comboBoxLightPlugin->currentText().trimmed();
	CurrentParam.LightParamStr    = ui.lineEditLightParam->text().trimmed();
	CurrentParam.InitialLightON   = ui.checkBoxInitialLightON->isChecked();

	// PIO
	CurrentParam.IODLL_FileName = ui.comboBoxPIOPlugin->currentText().trimmed();
	CurrentParam.IOSomething    = ui.lineEditPIOParam->text().trimmed();

	// データベース
	CurrentParam.LocalDatabase_HostName = ui.lineEditDBHost->text().trimmed();
	CurrentParam.LocalDatabase_Port     = ui.spinBoxDBPort->value();
	CurrentParam.LocalDatabase_FileName = ui.lineEditDBFile->text().trimmed();

	// マスターデータ保存先
	CurrentParam.ImageFilePath = ui.lineEditMasterFolder->text().trimmed();

	// 結果プラグイン / GeneralStocker
	CurrentParam.ResultDLLFileName       = ui.comboBoxResultPlugin->currentText().trimmed();
	CurrentParam.GeneralStockerFileName1 = ui.comboBoxGeneralStockerPlugin->currentText().trimmed();
	CurrentParam.GeneralStockerFileName  = ui.lineEditGeneralStockerParam->text().trimmed();

	// マルチコア使用 (チェックON = マルチコア使用 -> CalcSingleThread = false)
	CurrentParam.CalcSingleThread = !ui.checkBoxMultiCore->isChecked();

	// シーケンスファイル・検査制限
	CurrentParam.Sequence_FileName = ui.lineEditSequenceFile->text().trimmed();
	CurrentParam.MaxInspectMilisec = ui.spinBoxMaxInspectMilisec->value();
	CurrentParam.MaxNGCountsPerCam = ui.spinBoxMaxNGCountsPerCam->value();

	// Global.dat への上書き保存
	QFile globalFile(GlobalDatFilePath);
	if(!globalFile.open(QIODevice::WriteOnly)){
		QMessageBox::critical(this, QStringLiteral("保存エラー"),
			QStringLiteral("Global.dat を開けませんでした:\n") + GlobalDatFilePath);
		return;
	}
	bool savedGlobal = CurrentParam.SaveParam(&globalFile);
	globalFile.close();
	if(!savedGlobal){
		QMessageBox::critical(this, QStringLiteral("保存エラー"),
			QStringLiteral("Global.dat の書き込みに失敗しました。"));
		return;
	}

	// MachineInfo.dat への上書き保存
	const int language = ui.comboBoxLanguage->currentIndex();
	if(!MachineInfoRegistry->Save(QStringLiteral("Language"), language)){
		QMessageBox::critical(this, QStringLiteral("保存エラー"),
			QStringLiteral("MachineInfo.dat の書き込みに失敗しました:\n") + MachineInfoFilePath);
		return;
	}

	QMessageBox::information(this, QStringLiteral("保存完了"),
		QStringLiteral("Global.dat と MachineInfo.dat に保存しました。"));
}