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

#ifndef MAKELANGUAGEDIALOG_H
#define MAKELANGUAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XLanguageCodec.h"

namespace Ui {
class MakeLanguageDialog;
}

class GUILanguageContainer;
class LanguagePack;

class MakeLanguageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    LanguagePack    LPack;

public:
    explicit MakeLanguageDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~MakeLanguageDialog();

private slots:
    void on_pushButtonLoadGUILanguageFile_clicked();
    void on_pushButtonSaveGUILanguageFile_clicked();
    void on_pushButtonLoadLanguageExcel_clicked();
    void on_pushButtonSaveLanguageExcel_clicked();

private:
    Ui::MakeLanguageDialog *ui;

    void ShowGrid(void);
    bool LoadExcelFile(LanguagePack &LPack ,QString &ExcelFileName,GUILanguageContainer &LangC);
    bool SaveExcelFile(LanguagePack &LPack ,QString &ExcelFileName,GUILanguageContainer &LangC);
};

#endif // MAKELANGUAGEDIALOG_H