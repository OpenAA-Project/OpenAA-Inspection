#ifndef EDITEDGEMATCHINGFORM_H
#define EDITEDGEMATCHINGFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XEdgeMatching.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class EditEdgeMatchingForm;
}

class EditEdgeMatchingForm;


class	DisplaySimPanelEdgeMatching	: public DisplaySimPanel
{
	EditEdgeMatchingForm	*ParentWidget;
	int32     DividedAreaNumber;

public:
	DisplaySimPanelEdgeMatching(LayersBase *base ,EditEdgeMatchingForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt)	override;
	void     SetDividedAreaNumber(int Number);

protected:
	virtual void	mouseMoveEvent ( QMouseEvent * e )	override;
	virtual	void	GetDrawInformation(QByteArray &Something)	override;
};

class EditEdgeMatchingForm : public QWidget, public ServiceForLayers, public PasswordInQWodget
{
    Q_OBJECT

    DisplaySimPanelEdgeMatching		SimPanel;
    bool    Preparing;
public:
    explicit EditEdgeMatchingForm(LayersBase *Base, QWidget *parent = nullptr);
    ~EditEdgeMatchingForm();

    void Initial(AlgorithmBase *InstBase, AlgorithmItemIndependentPack &Data);
    void GetDataFromWindow(void);
    void ShowDataToWindow(void);

    AlgorithmItemIndependentPack *IData;

private slots:
    void on_EditFocusRadius_valueChanged(int arg1);
    void on_EditLayer_valueChanged(int arg1);
    void on_EditSearchDotX_valueChanged(int arg1);
    void on_EditSearchDotY_valueChanged(int arg1);
    void on_EditSearchByPixel_valueChanged(int arg1);
    void on_EditThresholdDiv_valueChanged(double arg1);
    void on_EditThresholdDirection_valueChanged(double arg1);
    void on_pushButtonReflectOnly_clicked();
    void on_pushButtonReflectAll_clicked();
    void on_pushButtonClose_clicked();
    void on_listWidgetCoef_itemSelectionChanged();
    void on_listWidgetCoef_itemClicked(QListWidgetItem *item);

    void on_checkBoxUseDivided_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::EditEdgeMatchingForm *ui;

    int GlobalPage;
    bool OnChanging;

    void CalcFunc();

    virtual void	showEvent ( QShowEvent * event )    override;
};

#endif // EDITEDGEMATCHINGFORM_H
