#ifndef SETTINGLOADRELEASEDIALOG_H
#define SETTINGLOADRELEASEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XLoadRelease.h"

namespace Ui {
class SettingLoadReleaseDialog;
}

class SettingLoadReleaseDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
	LoadReleaseAlgoContainer	SettingData;

    explicit SettingLoadReleaseDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SettingLoadReleaseDialog();

	void Merge(LoadReleaseAlgoContainer &SrcSettingData);
	void ReflectToWindow(void);

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SettingLoadReleaseDialog *ui;
};

#endif // SETTINGLOADRELEASEDIALOG_H
