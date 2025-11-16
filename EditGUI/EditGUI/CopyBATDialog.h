#ifndef COPYBATDIALOG_H
#define COPYBATDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "NList.h"
#include "NListComp.h"

namespace Ui {
class CopyBATDialog;
}

class	EditGUI;

class	AdditionalFile : public NPListSaveLoad<AdditionalFile>
{
public:
	QString	SrcFile;
	QString	Dest;

	AdditionalFile(void){}
	AdditionalFile(const QString &s , const QString &d):SrcFile(s),Dest(d){}

	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,SrcFile)==false)
			return false;
		if(::Save(f,Dest)==false)
			return false;
		return true;
	}
	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,SrcFile)==false)
			return false;
		if(::Load(f,Dest)==false)
			return false;
		return true;
	}
};

class	AdditionalFileContainer : public NPListPackSaveLoad<AdditionalFile>
{
public:
	virtual	AdditionalFile	*Create(void){	return new AdditionalFile();	}
};

class CopyBATDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	EditGUI					*EditGUIParent;
	AdditionalFileContainer	AdditionalFiles;
public:
    explicit CopyBATDialog(EditGUI *eP ,LayersBase *base, QWidget *parent = 0);
    ~CopyBATDialog();

private slots:
    void on_pushButtonSelectGlobalDat_clicked();
    void on_pushButtonSelectBATFile_clicked();
    void on_pushButtonMakeBAT_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSelecGUIFolder_clicked();
    void on_pushButtonSelectAlgorithmFolder_clicked();
    void on_pushButtonSelectPIOFile_clicked();
    void on_pushButtonSelectCameraFile_clicked();
    void on_pushButtonSelectLightFile_clicked();
    void on_pushButtonSelectSequenceDLL_clicked();
    void on_pushButtonSelectGeneralStockers_clicked();
    void on_pushButtonSelectFilterPath_clicked();
    void on_pushButtonSelectResultDLL_clicked();
    void on_pushButtonSaveSetting_clicked();
    void on_pushButtonLoadSetting_clicked();
    void on_pushButtonPlus_clicked();
    void on_pushButtonMinus_clicked();

private:
    Ui::CopyBATDialog *ui;

	void	ShowParam(void);

	bool SaveSetting(QIODevice *f);
	bool LoadSetting(QIODevice *f);

	void GetAdditionalFilesFromWindow(void);
	void SetAdditionalFilesToWindow(void);
};

#endif // COPYBATDIALOG_H
