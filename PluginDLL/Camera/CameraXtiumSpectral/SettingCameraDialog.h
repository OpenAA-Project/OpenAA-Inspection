#ifndef SETTINGCAMERADIALOG_H
#define SETTINGCAMERADIALOG_H

#include <QDialog>
#include "XCameraCommon.h"

namespace Ui {
class SettingCameraDialog;
}
class	CLHS_PX8Setting;
class	featureCtrl;

class SettingCameraDialog : public QDialog
{
    Q_OBJECT

	CLHS_PX8Setting	*Setting;
	featureCtrl		*Feature;

public:
    explicit SettingCameraDialog(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent = nullptr);
    ~SettingCameraDialog();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::SettingCameraDialog *ui;
};

#endif // SETTINGCAMERADIALOG_H
