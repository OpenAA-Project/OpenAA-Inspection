#include "ui_CameraSettingForm.h"

class CameraSettingForm : public QDialog
{
	Q_OBJECT

public:
	CameraSettingForm(int *r, int *g, int *b, QWidget *parent=NULL);

public:
	int getRed();
	int getGreen();
	int getBlue();
	void ResetRGB(int *r, int *g, int *b);

public slots:
	void setRed(int value);
	void setGreen(int value);
	void setBlue(int value);
	void cancel();
	void ok();

private:
	Ui::CameraSettingClass ui;
	int *cur_red, *cur_green, *cur_blue;
	int old_red, old_green, old_blue;
};