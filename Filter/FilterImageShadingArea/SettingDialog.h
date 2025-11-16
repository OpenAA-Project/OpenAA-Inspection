#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}
class	FilterImageShadingArea;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	FilterImageShadingArea	*Parent;
public:
    explicit SettingDialog(LayersBase *base,FilterImageShadingArea *parent ,QWidget *p = 0);
    ~SettingDialog();

	void	Reflect(void);

	double	MagR;
	double	MagG;
	double	MagB;
	int		UsagePhaseNumber;
	int		UsagePageNumber;
	QStringList	FileList;

private slots:
    void on_pushButtonAddFiles_clicked();
    void on_pushButtonDelFiles_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	bool	AddPix(int UsePhaseNumber,int UsePageNumber,const QString &FileName,short ***MultiplePerDot ,int XLen ,int YLen);
};

#endif // SETTINGDIALOG_H
