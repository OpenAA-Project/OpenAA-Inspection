#ifndef CHECKSHIFTMARKFORM_H
#define CHECKSHIFTMARKFORM_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class CheckShiftMarkForm;
}

class CheckShiftMarkForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    bool    EnableCalc;
public:
    explicit CheckShiftMarkForm(LayersBase *Base,QWidget *parent = nullptr);
    ~CheckShiftMarkForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_EditSearchDotEdge_valueChanged(int arg1);
    void on_EditSearchDotMark_valueChanged(int arg1);
    void on_checkBoxNGByLosingMark_clicked();
    void on_EditThresholdLost_valueChanged(int arg1);
    void on_ButtonReflectOnlyShiftMark_clicked();
    void on_ButtonReflectAllShiftMark_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_checkBoxEnableMark_clicked();
    void on_checkBoxColorMatch_clicked();

    void on_EditSearchDotMarkMin_valueChanged(int arg1);

    void on_EditSearchDotMarkMax_valueChanged(int arg1);

private:
    Ui::CheckShiftMarkForm *ui;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmLibraryListContainer	LibIDList;

    void	GetDataFromWindow(void);
    void	ShowThreshold(void);
    void	Calc(void);
};

#endif // CHECKSHIFTMARKFORM_H
