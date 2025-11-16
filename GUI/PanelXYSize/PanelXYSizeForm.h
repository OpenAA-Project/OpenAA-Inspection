#ifndef PANELXYSIZEFORM_H
#define PANELXYSIZEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PanelXYSizeForm;
}
class	SignalOperandInt;


class PanelXYSizeForm : public GUIFormBase
{
    Q_OBJECT
    
	SignalOperandInt	*iRegXSize;
	SignalOperandInt	*iRegYSize;
public:
	int32		LimitMaxX;
	int32		LimitMaxY;
	int			XSize;
	int			YSize;

    explicit PanelXYSizeForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelXYSizeForm();
    
	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::PanelXYSizeForm *ui;
};

#endif // PANELXYSIZEFORM_H
