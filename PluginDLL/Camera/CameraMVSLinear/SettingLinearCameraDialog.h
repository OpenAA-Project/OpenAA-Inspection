#ifndef SETTINGLINEARCAMERADIALOG_H
#define SETTINGLINEARCAMERADIALOG_H

#include <QDialog>
#include "CameraMVSLinear.h"

namespace Ui {
class SettingLinearCameraDialog;
}

class  CameraMVSLinear;

class SettingLinearCameraDialog : public QDialog
{
    Q_OBJECT

    int         EnumExposureAutoData[64];
    int         EnumExposureModeData[64];
    int         EnumLineTriggerSourceData[64];
    int         EnumLineTriggerModeData[64];
    int         EnumFrameTriggerSourceData[64];
    int         EnumFrameTriggerModeData[64];
	int		    EnumLineFormatData[6][64];
    int		    EnumLineModeData[6][64];

    CameraMVSLinear   *Parent;
public:
    int         ExposureAuto;
    int         ExposureMode;
	float		ExposureTime;
    float		Gain;
	float		GainR;
    float		GainG;
    float		GainB;
	float		FrameRate;
    bool		LineTriggerMode;   
    int			LineTriggerSource; 
    bool        FrameTriggerMode;   
    int			FrameTriggerSource;
	int		    Line0Format;
	int		    Line1Format;
	int		    Line2Format;
	int		    Line3Format;
	int		    Line4Format;
    unsigned int    BinningHMode;
    unsigned int    BinningVMode;
    unsigned int    DecimationH ;
    unsigned int    DecimationV ;

    bool    ReverseX;
    bool    ReverseTDIY;

    bool    AOIMode;
    unsigned int     AOIOffsetX;
    unsigned int     AOIWidth;

public:
    explicit SettingLinearCameraDialog(CameraMVSLinear *p,QWidget *parent = nullptr);
    ~SettingLinearCameraDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingLinearCameraDialog *ui;
};

#endif // SETTINGLINEARCAMERADIALOG_H
