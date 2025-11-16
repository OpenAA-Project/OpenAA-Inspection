#ifndef HOLEWALLHISTGRAMFORM_H
#define HOLEWALLHISTGRAMFORM_H

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
class HoleWallHistgramForm;
}
class	HoleWallHistgramForm;

class	DisplaySimPanelHoleWall	: public DisplaySimPanel
{
	HoleWallHistgramForm	*ParentWidget;
public:
	DisplaySimPanelHoleWall(LayersBase *base ,HoleWallHistgramForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt);
};


class HoleWallHistgramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

	int	GlobalPage;
public:
    explicit HoleWallHistgramForm(LayersBase *Base,QWidget *parent = 0);
    ~HoleWallHistgramForm();

	bool	ModeShowBlock;
	bool	ModeShowMask;
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_pushButtonRestore_clicked();
    void on_ButtonClose_clicked();
    void on_ButtonCalc_clicked();
    void on_toolButtonSimShowBlock_clicked();
    void on_toolButtonSimShowNGMark_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
	void	SlotStartCalc();
	void	SlotLayerClicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();

    void on_EditSearchDot_valueChanged(int arg1);

    void on_EditNGSize_valueChanged(int arg1);

signals:
	void	SignalStartCalc();
private:
    Ui::HoleWallHistgramForm *ui;

	DisplaySimPanelHoleWall			SimPanel;
	QToolBar						LayerBar;
	QToolButton						**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	AlgorithmItemIndependentPack	*IData;

	int32	NGSize;		//For ring brightness
	WORD	SearchDot;

	void	CreateThreshld(void);
	void	ShowLibrary(void);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	GetActiveLayerList(IntList &LayerList);

	int		LastLayer;

	HistgramTypeListInAlgoContainer	HContainer;
	bool	OnChanging;
};

#endif // HOLEWALLHISTGRAMFORM_H
