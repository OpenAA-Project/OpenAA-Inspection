#include "CameraSettingDialog.h"
#include "ui_CameraSettingDialog.h"
#include "XGeneralFunc.h"
#include "VienexCIS.h"
#include "XDLLType.h"
#include "CameraXtiumCISVienex.h"

CameraSettingDialog::CameraSettingDialog(CameraXtiumCISVienex *v ,QWidget *parent) :
    QDialog(parent),
    V(v),
    ui(new Ui::CameraSettingDialog)
{
    ui->setupUi(this);

    ShowDataToWindow();
}


void CameraSettingDialog::ShowDataToWindow(void)
{

    ui->checkBoxSHADING             ->setChecked(((V->CISVienexData.CISVienexData.SHADING)!=0)?true:false);
    ui->checkBoxDARK                ->setChecked(((V->CISVienexData.CISVienexData.DARK)!=0)?true:false);
    ui->spinBoxSHADING_TARGET_VAL   ->setValue(V->CISVienexData.CISVienexData.SHADING_TARGET_VAL);

    ui->comboBoxCL_CONFIG           ->setCurrentIndex(V->CISVienexData.CISVienexData.CL_CONFIG);
    ui->comboBoxCL_FREQ             ->setCurrentIndex(V->CISVienexData.CISVienexData.CL_FREQ);

    ui->spinBoxTRIG_CYCLE           ->setValue(V->CISVienexData.CISVienexData.TRIG_CYCLE);
    ui->comboBoxSYNC_MODE           ->setCurrentIndex(V->CISVienexData.CISVienexData.SYNC_MODE);

    ui->spinBoxLED_ON_1_CYCLE       ->setValue(V->CISVienexData.CISVienexData.LED_ON_1_CYCLE);
    ui->spinBoxLED_ON_2_CYCLE       ->setValue(V->CISVienexData.CISVienexData.LED_ON_2_CYCLE);
    ui->spinBoxLED_CTRL_1           ->setValue(V->CISVienexData.CISVienexData.LED_CTRL_1);
    ui->spinBoxLED_CTRL_2           ->setValue(V->CISVienexData.CISVienexData.LED_CTRL_2);
    ui->checkBoxLED1_ON             ->setChecked(((V->CISVienexData.CISVienexData.LED1_ON)!=0)?true:false);
    ui->checkBoxLED2_ON             ->setChecked(((V->CISVienexData.CISVienexData.LED2_ON)!=0)?true:false);
    ui->comboBoxCONTINUOUS          ->setCurrentIndex(V->CISVienexData.CISVienexData.CONTINUOUS);

    ui->comboBoxLINE_ADJUST_DIRECTION   ->setCurrentIndex(V->CISVienexData.CISVienexData.LINE_ADJUST_DIRECTION);
    ui->comboBoxLINE_ADJUST_ON_OFF      ->setCurrentIndex(V->CISVienexData.CISVienexData.LINE_ADJUST_ON_OFF);

    ui->comboBoxD_RANGE             ->setCurrentIndex(V->CISVienexData.CISVienexData.D_RANGE);
    ui->comboBoxRES_SEL             ->setCurrentIndex(V->CISVienexData.CISVienexData.RES_SEL);

    ui->spinBoxGAIN_R               ->setValue(V->CISVienexData.CISVienexData.GAIN_R);
    ui->spinBoxOFFSET_R             ->setValue(V->CISVienexData.CISVienexData.OFFSET_R);
    ui->spinBoxGAIN_G               ->setValue(V->CISVienexData.CISVienexData.GAIN_G);
    ui->spinBoxOFFSET_G             ->setValue(V->CISVienexData.CISVienexData.OFFSET_G);
    ui->spinBoxGAIN_B               ->setValue(V->CISVienexData.CISVienexData.GAIN_B);
    ui->spinBoxOFFSET_B             ->setValue(V->CISVienexData.CISVienexData.OFFSET_B);

    ui->checkBoxControlOnStart      ->setChecked(V->Setting.CameraControl);

    //ui->comboBoxCUT_5PIX            ->setCurrentIndex(v->CISVienexData.CISVienexData.CUT_5PIX);
    //ui->comboBoxSTAGGERED_DIRECTION ->setCurrentIndex(v->CISVienexData.CISVienexData.STAGGERED_DIRECTION);
    //ui->comboBoxSTAGGERED_ON_OFF    ->setCurrentIndex(v->CISVienexData.CISVienexData.STAGGERED_ON_OFF);
    //
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 0 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_1,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 2 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_3,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 4 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_5,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 6 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_7,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 8 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_9,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 10, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_11,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 12, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_13,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 14, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_15,0,2);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 16, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_17,0,2);
    //
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 1 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_2,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 3 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_4,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 5 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_6,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 7 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_8,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 9 , v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_10,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 11, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_12,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 13, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_14,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 15, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_16,0,20);
    //::SetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 17, v->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_18,0,20);

}

CameraSettingDialog::~CameraSettingDialog()
{
    delete ui;
}

void CameraSettingDialog::on_pushButtonOK_clicked()
{
    V->Setting.CameraControl    =ui->checkBoxControlOnStart      ->isChecked();

    V->CISVienexData.CISVienexData.SHADING            =(ui->checkBoxSHADING   ->isChecked()==true)?1:0;
    V->CISVienexData.CISVienexData.DARK               =(ui->checkBoxDARK      ->isChecked()==true)?1:0;
    V->CISVienexData.CISVienexData.SHADING_TARGET_VAL =ui->spinBoxSHADING_TARGET_VAL->value();

    V->CISVienexData.CISVienexData.CL_CONFIG          =ui->comboBoxCL_CONFIG  ->currentIndex();
    V->CISVienexData.CISVienexData.CL_FREQ            =ui->comboBoxCL_FREQ    ->currentIndex();

    V->CISVienexData.CISVienexData.TRIG_CYCLE         =ui->spinBoxTRIG_CYCLE  ->value();
    V->CISVienexData.CISVienexData.SYNC_MODE          =ui->comboBoxSYNC_MODE  ->currentIndex();

    V->CISVienexData.CISVienexData.LED_ON_1_CYCLE     =ui->spinBoxLED_ON_1_CYCLE  ->value();
    V->CISVienexData.CISVienexData.LED_ON_2_CYCLE     =ui->spinBoxLED_ON_2_CYCLE  ->value();
    V->CISVienexData.CISVienexData.LED_CTRL_1         =ui->spinBoxLED_CTRL_1      ->value();
    V->CISVienexData.CISVienexData.LED_CTRL_2         =ui->spinBoxLED_CTRL_2      ->value();
    V->CISVienexData.CISVienexData.LED1_ON            =(ui->checkBoxLED1_ON       ->isChecked()==true)?1:0;
    V->CISVienexData.CISVienexData.LED2_ON            =(ui->checkBoxLED2_ON       ->isChecked()==true)?1:0;
    V->CISVienexData.CISVienexData.CONTINUOUS         =ui->comboBoxCONTINUOUS    ->currentIndex();

    V->CISVienexData.CISVienexData.LINE_ADJUST_DIRECTION  =ui->comboBoxLINE_ADJUST_DIRECTION  ->currentIndex(); 
    V->CISVienexData.CISVienexData.LINE_ADJUST_ON_OFF     =ui->comboBoxLINE_ADJUST_ON_OFF     ->currentIndex(); 

    V->CISVienexData.CISVienexData.D_RANGE            =ui->comboBoxD_RANGE    ->currentIndex(); 
    V->CISVienexData.CISVienexData.RES_SEL            =ui->comboBoxRES_SEL    ->currentIndex(); 

    V->CISVienexData.CISVienexData.GAIN_R             =ui->spinBoxGAIN_R      ->value();
    V->CISVienexData.CISVienexData.OFFSET_R           =ui->spinBoxOFFSET_R    ->value();
    V->CISVienexData.CISVienexData.GAIN_G             =ui->spinBoxGAIN_G      ->value();
    V->CISVienexData.CISVienexData.OFFSET_G           =ui->spinBoxOFFSET_G    ->value();
    V->CISVienexData.CISVienexData.GAIN_B             =ui->spinBoxGAIN_B      ->value();
    V->CISVienexData.CISVienexData.OFFSET_B           =ui->spinBoxOFFSET_B    ->value();

    //V->CISVienexData.CISVienexData.CUT_5PIX           =ui->comboBoxCUT_5PIX           ->currentIndex(); 
    //V->CISVienexData.CISVienexData.STAGGERED_DIRECTION=ui->comboBoxSTAGGERED_DIRECTION->currentIndex(); 
    //V->CISVienexData.CISVienexData.STAGGERED_ON_OFF   =ui->comboBoxSTAGGERED_ON_OFF   ->currentIndex(); 
    //
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_1   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 0 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_3   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 2 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_5   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 4 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_7   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 6 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_9   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 8 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_11  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 10);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_13  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 12);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_15  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 14);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_17  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 16);
    //
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_2   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 1 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_4   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 3 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_6   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 5 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_8   =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 7 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_10  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 9 );
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_12  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 11);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_14  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 13);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_16  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 15);
    //V->CISVienexData.CISVienexData.STAGGRED_LINES_NUM_18  =::GetDataToTableSpinBox(ui->tableWidgetSTAGGRED_LINES_NUM, 0, 17);

    V->CISVienexData.StoreToCam();

    done(true);
}


void CameraSettingDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void CameraSettingDialog::on_pushButtonLoadFromCamera_clicked()
{
    V->CISVienexData.LoadFromCam();
    ShowDataToWindow();
}

