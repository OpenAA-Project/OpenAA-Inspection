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

#ifndef EDITWIZARDPARAMETER_H
#define EDITWIZARDPARAMETER_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QVector>
#include "ui_EditWizardParameter.h"
#include "XServiceForLayers.h"
#include "XParamGlobal.h"
#include "XFileRegistry.h"

class EditWizardParameter : public QMainWindow, public ServiceForLayers
{
	Q_OBJECT

public:
	EditWizardParameter(LayersBase *base
					,const QString &targetDir
					,QWidget *parent = nullptr
					,Qt::WindowFlags flags = Qt::Widget);
	~EditWizardParameter();

private slots:
	void SlotPrevPage();
	void SlotNextPage();

	void on_pushButtonBrowseCameraPlugin_clicked();
	void on_pushButtonBrowseLightPlugin_clicked();
	void on_pushButtonBrowsePIOPlugin_clicked();
	void on_pushButtonBrowseDBFile_clicked();
	void on_pushButtonBrowseMasterFolder_clicked();
	void on_pushButtonBrowseSequenceFile_clicked();
	void on_pushButtonSave_clicked();

private:
	enum WizardPageIndex
	{
		Page_Language				= 0,
		Page_CameraCount			= 1,
		Page_CameraPlugin			= 2,
		Page_CameraParam			= 3,
		Page_CameraNo				= 4,
		Page_DotPerLine				= 5,
		Page_MaxLines				= 6,
		Page_ResolutionY			= 7,
		Page_ResolutionX			= 8,
		Page_LayerNumb				= 9,
		Page_PageNumb				= 10,
		Page_PageCameraAlloc		= 11,
		Page_ImageArrange			= 12,
		Page_StrategyCount			= 13,
		Page_PageStrategy			= 14,
		Page_LightPlugin			= 15,
		Page_LightParam				= 16,
		Page_InitialLightON			= 17,
		Page_PIOPlugin				= 18,
		Page_PIOParam				= 19,
		Page_DBHost					= 20,
		Page_DBPort					= 21,
		Page_DBFile					= 22,
		Page_MasterFolder			= 23,
		Page_ResultPlugin			= 24,
		Page_GeneralStockerPlugin	= 25,
		Page_GeneralStockerParam	= 26,
		Page_MultiCore				= 27,
		Page_SequenceFile			= 28,
		Page_MaxInspectTime			= 29,
		Page_MaxNGCount				= 30,
		Page_Save					= 31
	};

	struct CameraEntry
	{
		QString	PluginFileName;
		QString	ParamStr;
		int		CameraNo;

		CameraEntry() : CameraNo(0) {}
	};

	Ui::EditWizardParameterClass	ui;
	ParamGlobal						CurrentParam;
	FileRegistry					*MachineInfoRegistry;

	QString		TargetDir;
	QString		GlobalDatFilePath;
	QString		MachineInfoFilePath;
	QString		AppBaseDir;

	QVector<CameraEntry>	CameraEntries;
	QVector<int>			PageCameraAllocList;
	QVector<int>			PageStrategyList;

	int		CurrentCameraIndex;
	int		CurrentAllocPageIndex;
	int		CurrentStrategyPageIndex;

	void		InitPluginComboBoxes();
	QStringList	ScanPluginDLLs(const QString &searchDir, WORD targetDLLType, bool relativeToBase) const;
	QString		GetPluginDLLFolder() const;
	QString		GetPluginFileFilter() const;
	void		PopulateComboBox(QComboBox *combo, const QStringList &items, const QString &currentValue);

	void		LoadInitialValues();
	void		EnsureCameraEntriesSize(int count);
	void		EnsurePageArraysSize(int pageCount);

	void		LoadCameraUI(int camIdx);
	void		SaveCameraUI(int camIdx);
	void		LoadPageCameraAllocUI(int pageIdx);
	void		SavePageCameraAllocUI(int pageIdx);
	void		LoadPageStrategyUI(int pageIdx);
	void		SavePageStrategyUI(int pageIdx);

	void		UpdateStepProgress();
	int			CalcTotalDynamicSteps() const;
	int			CalcCurrentDynamicStep() const;
};

#endif // EDITWIZARDPARAMETER_H