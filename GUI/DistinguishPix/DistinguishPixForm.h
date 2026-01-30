/*
 * Copyright (C) 2022
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

#ifndef DISTINGUISHPIXFORM_H
#define DISTINGUISHPIXFORM_H

#include <QWidget>
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDistinguishPixCommon.h"
#include "mtPushButtonColored.h"
#include <QListWidgetItem>
#include <QColor>
#include <QString>

namespace Ui {
class DistinguishPixForm;
}



class	FileListLeafPointer
{
public:
	FileListLeaf *Pointer;

	FileListLeafPointer(FileListLeaf *a):Pointer(a){}
};

class DistinguishPixForm : public GUIFormBase
{
    Q_OBJECT

	FileListContainer		FileData;
	FileListLeafPointer		**FileDim;
	int						FileDimNumb;

	mtPushButtonColored		*ButtonNG1;
	mtPushButtonColored		*ButtonNG2;
	mtPushButtonColored		*ButtonNG3;
	mtPushButtonColored		*ButtonNG4;

	QColor		NG1Color;
	QColor		NG2Color;
	QColor		NG3Color;
	QColor		NG4Color;

public:
	QString		NG1Str;
	QString		NG2Str;
	QString		NG3Str;
	QString		NG4Str;
	int32		PhaseToLoad;
	QString		AbsScanPath;

    explicit DistinguishPixForm(LayersBase *Base ,QWidget *parent = 0);
    ~DistinguishPixForm();

	virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	QString	GetJudgeStr(int d);
	bool LoadImageData(const QString &FileName);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSaveList_clicked();
    void on_pushButtonClearList_clicked();
    void on_pushButtonScanFolder_clicked();
    void on_pushButtonLoadList_clicked();
    void on_pushButtonSearchFolder_clicked();
    void on_pushButtonNG1_clicked();
    void on_pushButtonNG2_clicked();
    void on_pushButtonNG3_clicked();
    void on_pushButtonNG4_clicked();
    void on_pushButtonOKForNone_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_pushButtonReleaseOne_clicked();

private:
    Ui::DistinguishPixForm *ui;

	void	ShowList(QString &FolderName);
};

#endif // DISTINGUISHPIXFORM_H