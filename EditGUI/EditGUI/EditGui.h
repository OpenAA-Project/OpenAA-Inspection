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



#ifndef EDITGUI_H
#define EDITGUI_H

#include <QMainWindow>
#include "ui_EditGui.h"
#include "XGUI.h"
#include <QToolButton>
#include "XServiceForLayers.h"

class	GUIItemInstancePointer : public NPList<GUIItemInstancePointer>
{
public:
	GUIItemInstance	*Pointer;

	GUIItemInstancePointer(GUIItemInstance *f):Pointer(f){}
};

class EditGUI : public QMainWindow , public ServiceForLayers
{
    Q_OBJECT

	QToolButton	*LoadFileButton;
	QToolButton	*SaveNewButton;
	QToolButton	*OverwriteButton;

	QToolButton	*SearchButton;
	QToolButton	*Snap2GridButton;

	QToolButton	*TestButton;
	QToolButton	*UsageComponentButton;

public:
	QString PathToOpenedFile;

	EditGUI(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~EditGUI();

	Ui::EditGUIClass ui;

private:

	virtual	void closeEvent ( QCloseEvent * event )	override;
	bool SaveGUIFile(const QString &FilePath);
	void ReleaseSelected(void);

	QByteArray		ClipboardBuffer;

private slots:
	void on_actionImage_direction_on_each_page_triggered();
	void CreateNewFunc();
	void OpenGUIFileFunc();
	void SaveGUIFileFunc();
	void SaveGUIFileAsFunc();

	void TestGUIFunc();

	void Global_SettingFunc();
	void Communication_SettingFunc();
	void Scanning_settingFunc();
	void Save_settingFunc();
	void OutlineOffsetFunc();
	void SaveGlobalParamFunc();
	void EditSyncGUIFileFunc();
	void EditPhaseFunc(); 
	void UsageConponentList();
	void SearchFunc();
	void ExitFunc();
	void Snap_to_gridFunc();
	void Make_BAT_fileFunc();

	void EditFilterFunc();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionAlign_left_triggered();
    void on_actionAlign_top_triggered();
    void on_actionAlign_same_width_triggered();
    void on_actionAlign_same_height_triggered();
    void on_actionAlign_right_triggered();
    void on_actionAlign_bottom_triggered();
    void on_actionAlign_horizontal_same_gap_triggered();
    void on_actionAlign_vertical_same_gap_triggered();
    void on_actionDelete_Selected_components_triggered();
    void on_actionMake_status_Def_fike_triggered();
    void on_actionMake_GUILanguage_file_triggered();
    void on_actionEdit_order_triggered();
};

#endif // EDITGUI_H