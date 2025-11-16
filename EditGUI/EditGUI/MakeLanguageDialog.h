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
