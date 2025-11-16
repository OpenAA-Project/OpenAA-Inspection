#ifndef SETTINGARRAYSHIFTMULINPAGEDIALOG_H
#define SETTINGARRAYSHIFTMULINPAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QByteArray>

namespace Ui {
class SettingArrayShiftMulInPageDialog;
}
class	HoleWallBase;

class SettingArrayShiftMulInPageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	HoleWallBase	*ABase;
	QByteArray	ArrayShiftMulInPage;

	explicit SettingArrayShiftMulInPageDialog(LayersBase *Base,QByteArray &_ArrayShiftMulInPage ,HoleWallBase *abase ,QWidget *parent = 0);
    ~SettingArrayShiftMulInPageDialog();

private slots:
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();

private:
    Ui::SettingArrayShiftMulInPageDialog *ui;

	virtual	void resizeEvent ( QResizeEvent * event )	override;
};

#endif // SETTINGARRAYSHIFTMULINPAGEDIALOG_H
