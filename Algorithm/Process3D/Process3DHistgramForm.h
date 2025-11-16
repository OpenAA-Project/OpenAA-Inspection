#ifndef PROCESS3DHISTGRAMFORM_H
#define PROCESS3DHISTGRAMFORM_H

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
class Process3DHistgramForm;
}

class Process3DHistgramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

	int	GlobalPage;
public:
    explicit Process3DHistgramForm(LayersBase *Base,QWidget *parent = 0);
    ~Process3DHistgramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
	void	SlotStartCalc();
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_ButtonCalc_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();
    void on_doubleSpinBoxBaseCycleDot_valueChanged(double arg1);
    void on_doubleSpinBoxHeightPerShift_valueChanged(double arg1);
    void on_doubleSpinBoxLargeTilt_valueChanged(double arg1);
    void on_doubleSpinBoxLargeFlatness_valueChanged(double arg1);
    void on_doubleSpinBoxSmallFlatness_valueChanged(double arg1);
    void on_spinBoxSmallAreaSize_valueChanged(int arg1);
    void on_toolButtonSimShowBlock_clicked();

    void on_toolButtonSimShowBright_clicked();

signals:
	void	SignalStartCalc();
private:
    Ui::Process3DHistgramForm *ui;

	DisplaySimPanel		SimPanel;
	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmBase *InstBase;
	bool	OnChanging;

	void	GetActiveLayerList(IntList &LayerList);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	ShowLibrary(void);

	int		OldLibID;
	double	OldBaseCycleDot		;
	double	OldHeightPerShift	;
	double	OldLargeTilt		;
	double	OldLargeFlatness	;
	double	OldSmallFlatness	;
	int		OldSmallAreaSize	;

	int		NewLibID;
	double	NewBaseCycleDot		;
	double	NewHeightPerShift	;
	double	NewLargeTilt		;
	double	NewLargeFlatness	;
	double	NewSmallFlatness	;
	int		NewSmallAreaSize	;
};

#endif // PROCESS3DHISTGRAMFORM_H
