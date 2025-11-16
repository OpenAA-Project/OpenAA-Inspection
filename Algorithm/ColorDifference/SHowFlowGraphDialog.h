#ifndef SHOWFLOWGRAPHDIALOG_H
#define SHOWFLOWGRAPHDIALOG_H

#include <QDialog>
#include "XColorDifference.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"

namespace Ui {
class SHowFlowGraphDialog;
}



class SHowFlowGraphDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
	ColorDifferenceItem	*Item;

	mtLineGraph		HLGraph;
	mtGStick		HGraphColMaster;
	mtGStick		HGraphColTarget;
	mtGStick		HGraphThresh;

	mtLineGraph		SLGraph;
	mtGStick		SGraphColMaster;
	mtGStick		SGraphColTarget;
	mtGStick		SGraphThresh;

	mtLineGraph		VLGraph;
	mtGStick		VGraphColMaster;
	mtGStick		VGraphColTarget;
	mtGStick		VGraphThresh;

	mtLineGraph		ELGraph;
	mtGStick		EGraphColMaster;
	mtGStick		EGraphColTarget;
	mtGStick		EGraphThresh;

public:
    explicit SHowFlowGraphDialog(LayersBase *base,ColorDifferenceItem *Item ,QWidget *parent = 0);
    ~SHowFlowGraphDialog();
    
private:
    Ui::SHowFlowGraphDialog *ui;

	virtual	void resizeEvent ( QResizeEvent * event )	override;
	void ShowGraph(void);
};

#endif // SHOWFLOWGRAPHDIALOG_H
