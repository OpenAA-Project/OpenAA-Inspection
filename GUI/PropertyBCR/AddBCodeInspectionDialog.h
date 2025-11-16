#ifndef ADDBCODEINSPECTIONDIALOG_H
#define ADDBCODEINSPECTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include "XServiceForLayers.h"
#include "XBCRInspection.h"
#include "XGeneralFunc.h"

namespace Ui {
class AddBCodeInspectionDialog;
}

class AddBCodeInspectionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    QCheckBox   *BarcodeTypeTableCb[100];
    QCheckBox   *BarcodeOrientationTableCb[100];
public:
    explicit AddBCodeInspectionDialog(LayersBase *Base,QWidget *parent = 0);
    ~AddBCodeInspectionDialog();
    
	int		                CheckType;		    //0:Read	1:Quality Check
	double	                QuilityGrade;
	BCRGradeListContainer	GradeList;
    BYTE					BarcodeOrientation;	//BarcodeOrientationEnum
	uint32					BarcodeType;		//BarcodeTypeEnum
    bool					BarcodeIsOnlyDigit;

    void	GetDataFromWindow(void);
    void	SetDataToWindow(void);


private slots:
    void on_comboBoxCheckType_currentIndexChanged(int index);
    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonSet_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::AddBCodeInspectionDialog *ui;

    void    ShowGradeList(BCRGradeListContainer &List);
    void    LoadGradeListFromWindow(BCRGradeListContainer &List);

};

#endif // ADDBCODEINSPECTIONDIALOG_H
