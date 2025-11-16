#ifndef SETTINGRECORDDIALOG_H
#define SETTINGRECORDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingRecordDialog;
}
class	RecordMovie;

class SettingRecordDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RecordMovie *RecordParent;
public:
    QString AVFormatStr;
    int     MovieSizeMode;
	float	TargetFrameRate;
	bool	DivideMovieFile;

    explicit SettingRecordDialog(RecordMovie *p,QWidget *parent = nullptr);
    ~SettingRecordDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_radioButtonAVI_clicked();
    void on_radioButtonMPEG1_clicked();

private:
    Ui::SettingRecordDialog *ui;
};

#endif // SETTINGRECORDDIALOG_H
