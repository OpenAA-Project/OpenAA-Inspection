#ifndef EDITALIGNMENTSHIFTROTATIONFORM_H
#define EDITALIGNMENTSHIFTROTATIONFORM_H

#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentShiftRotationCommon.h"
#include "XAlignmentShiftRotation.h"

namespace Ui {
class EditAlignmentShiftRotationForm;
}

class EditAlignmentShiftRotationForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit EditAlignmentShiftRotationForm(LayersBase *Base,QWidget *parent = nullptr);
    ~EditAlignmentShiftRotationForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);
    void	ShowDataToWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonAddAngle_clicked();
    void on_pushButtonSubAngle_clicked();
    void on_tableWidgetAngleList_cellDoubleClicked(int row, int column);
    void on_pushButtonReflectOnly_clicked();
    void on_pushButtonReflectAll_clicked();
    void on_pushButtonClose_clicked();
    void on_listWidgetAngleImage_itemSelectionChanged();

private:
    Ui::EditAlignmentShiftRotationForm *ui;

    int     GlobalPage;
    bool	OnChanging;
    RotationRangeContainer	Rotation;
};

#endif // EDITALIGNMENTSHIFTROTATIONFORM_H
