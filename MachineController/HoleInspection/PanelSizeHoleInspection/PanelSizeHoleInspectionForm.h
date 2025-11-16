#ifndef PANELSIZEHOLEINSPECTIONFORM_H
#define PANELSIZEHOLEINSPECTIONFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PanelSizeHoleInspectionForm;
}
class	SignalOperandInt;
class	SignalOperandBit;
class PanelSizeHoleInspectionForm : public GUIFormBase
{
    Q_OBJECT
	SignalOperandInt	*iRegXSize;
	SignalOperandInt	*iRegYSize;
	SignalOperandInt	*iRegScanCount;
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
	bool		ReflectOnlyWindow;

	int			AllocCamera1ToPage;
	int			AllocCamera2ToPage;
	int			AllocCamera3ToPage;
	int			AllocCamera4ToPage;

	int			OutlineOffsetL0;
	int			OutlineOffsetL1;
	int			OutlineOffsetL2;
	int			OutlineOffsetL3;
	int			OutlineOffsetL4;
	int			OutlineOffsetL5;
	int			OutlineOffsetL6;
	int			OutlineOffsetL7;


	bool		ReleaseAutoMode;

	explicit PanelSizeHoleInspectionForm(LayersBase *Base,QWidget *parent = 0);
    ~PanelSizeHoleInspectionForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	//virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::PanelSizeHoleInspectionForm *ui;

	void	SetOutlineOffset(void);
};

#endif // PANELSIZEHOLEINSPECTIONFORM_H
