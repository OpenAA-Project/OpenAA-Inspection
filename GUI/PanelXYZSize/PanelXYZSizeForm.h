#ifndef PANELXYZSIZEFORM_H
#define PANELXYZSIZEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PanelXYZSizeForm;
}

class	SignalOperandInt;

class PanelXYZSizeForm : public GUIFormBase
{
    Q_OBJECT
	SignalOperandInt	*iRegXSize;
	SignalOperandInt	*iRegYSize;
	SignalOperandInt	*iRegZSize;
public:
	int32		LimitMaxX;
	int32		LimitMaxY;
	int32		LimitMaxZ;
	int			XSize;
	int			YSize;
	int			ZSize;
	
	explicit PanelXYZSizeForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelXYZSizeForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();
	void	OperandChangedX();
	void	OperandChangedY();
	void	OperandChangedZ();
private:
    Ui::PanelXYZSizeForm *ui;
};

#endif // PANELXYZSIZEFORM_H
