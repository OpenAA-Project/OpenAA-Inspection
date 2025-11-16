#ifndef REGULATEBRIGHTNESSFORM_H
#define REGULATEBRIGHTNESSFORM_H

#include <QDialog>
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	HistgramListContainer;
class	AvrVarListByLayerContainer;

namespace Ui {
class RegulateBrightnessForm;
}

class RegulateBrightnessForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    QToolBar		LayerBar;
    int				LNumb;
    mtToolButtonColored		**LButtonList;

    mtLineGraph		LGraph;
    mtGStick		GraphCol;
    int				YMax;

public:
    explicit RegulateBrightnessForm(	IntList &EffectiveLayerList
                                        ,HistgramListContainer		&_HistDatas
                                        ,AvrVarListByLayerContainer	&_AvrDatas
                                        ,LayersBase *base
                                        ,QWidget *parent = 0);
    ~RegulateBrightnessForm();

    HistgramListContainer		HistDatas;
    AvrVarListByLayerContainer	AvrDatas;
    int		BlockSize;

private:
    Ui::RegulateBrightnessForm *ui;

    int	GetCurrentNo(void);

    void ShowData(void);
    void GetData(int No);
    int	LastLayer;

private slots:
    void	SlotLayerClicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();
};

#endif // REGULATEBRIGHTNESSFORM_H
