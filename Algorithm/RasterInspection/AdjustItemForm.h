#ifndef ADJUSTITEMFORM_H
#define ADJUSTITEMFORM_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include <QSpinBox>
#include <QString>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketForDLL.h"
#include "XRasterInspection.h"

namespace Ui {
class AdjustItemForm;
}

class AdjustItemForm;

class	DisplayAdjustPanel : public DisplaySimPanel
{
	AdjustItemForm	*Parent;
public:
	DisplayAdjustPanel (LayersBase *base ,AdjustItemForm *p ,QWidget *parent = 0);

	virtual	void	GetDrawInformation(QByteArray &Something);
};

class AdjustItemForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    DisplayAdjustPanel  DPanel;
public:
    explicit AdjustItemForm(LayersBase *Base,QWidget *parent = nullptr);
    ~AdjustItemForm();

    void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
    int     GetItemID(void);
    void	GetDrawInformation(QByteArray &Something);
	void	ShowResult(double ResultMaxD ,double ResultWaveLen);

private slots:
    void on_pushButtonReferencePDF_clicked();
    void on_ButtonRelrectOnlyItem_clicked();
    void on_ButtonReflectAllItems_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_spinBoxSearchAreaDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchWaveDiv_valueChanged(double arg1);
    void on_doubleSpinBoxWaveDistance_valueChanged(double arg1);
    void on_spinBoxOKDot_valueChanged(int arg1);
    void on_toolButtonSimShowBlock_clicked();
    void on_toolButtonShowResult_clicked();
    void on_doubleSpinBoxGenColorDistance_valueChanged(double arg1);
    void	SlotStartCalc();

private:
    Ui::AdjustItemForm *ui;

	AlgorithmLibraryListContainer	LibIDList;
	AlgorithmItemIndependentPack	*IData;
	AlgorithmBase *InstBase;
	bool	OnChanging;
	int		OldLibID;
	int		NewLibID;

	void	GetDataFromWindow(void);
	void	ShowLibrary(void);
};

#endif // ADJUSTITEMFORM_H
