#ifndef PANELXYCALCFORM_H
#define PANELXYCALCFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PanelXYCalcForm;
}
class	SignalOperandInt;
class	SignalOperandBit;

class PanelXYCalcForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandInt	*iRegXSize;
	SignalOperandInt	*iRegYSize;
	SignalOperandBit	*iFlagSet;

public:
	int32		LimitMaxX;
	int32		LimitMaxY;
	int32		LimitMinX;
	int32		LimitMinY;
	int			XSize;
	int			YSize;
	bool		FlagSet;
	int			XMerginPixels;
	int			YMerginPixels;
	int			XMinOverlappedPixels;
	bool		ModeIncrementStrategy;
	QString		ModeXDirection;
	QString		ModeYDirection;
	int			DelayInEvenY;
	int			DelayInOddY;
	bool		SwitchLabel;
	bool		ReflectOnlyWindowX;
	bool		ReflectOnlyWindowY;
	bool		ModeToChangePageCount;

	bool		ReleaseAutoMode;

    explicit PanelXYCalcForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelXYCalcForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
    void on_pushButtonSet_clicked();
	void	OperandChangedX();
	void	OperandChangedY();

private:
    Ui::PanelXYCalcForm *ui;
};

#endif // PANELXYCALCFORM_H
