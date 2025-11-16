#ifndef THRESHOLDSETTINGFORM_H
#define THRESHOLDSETTINGFORM_H

#include <QDialog>
#include "ui_ThresholdSettingForm.h"
#include "mtImageToolButton.h"
#include "mtImageSlider.h"
#include "XPixelInspection.h"

class ThresholdSettingForm : public QDialog
{
	Q_OBJECT

	mtImageToolButton	*BtnDecision;
	mtImageToolButton	*BtnDetailSetting;
	mtImageToolButton	*BtnCancel;

	mtImageSlider		*ImageSlider;

public:
	ThresholdSettingForm(QWidget *parent=0,GUIFormBase *Base=0,PixelInspectionBase *PBase=0);
	~ThresholdSettingForm();

	void	SetImageSlider			 (int Value)	{	ImageSlider->setValue(Value);	}
	void	SetInspectionLevel		 (int Value);
	int		GetInspectionLevel		 ()				{	return InspectionLevel;			}
	void	SetNGThresholdP			 (double Value)	{	NGThresholdP			=Value;	}
	void	SetNGThresholdR			 (double Value)	{	NGThresholdR			=Value;	}
	void	SetMinimumNGSizeP		 (int Value)	{	MinimumNGSizeP			=Value;	}
	void	SetDoneResistIns		 (bool Check)	{	DoneResistIns			=Check;	}
	void	SetNGThresholdForResist	 (int Value)	{	NGThresholdForResist	=Value;	}
	void	SetMinimumNGSizeForResist(int Value)	{	MinimumNGSizeForResist	=Value;	}
	void	SetDonePadIns			 (bool Check)	{	DonePadIns				=Check;	}
	void	SetNGThresholdForPad	 (int Value)	{	NGThresholdForPad		=Value;	}
	void	SetMinimumNGSizeForPad	 (int Value)	{	MinimumNGSizeForPad		=Value;	}

	GUIFormBase			*GUIBase;
	QString DecisionImageBmpFile[5];
	QString CancelImageBmpFile[5];

private slots:
	void	SlotBtnDecisionClicked		();
	void	SlotBtnDetailSettingClicked	();
	void	SlotBtnCancelClicked		();

private:
	Ui::ThresholdSettingFormClass ui;

	PixelInspectionBase	*PixelBase;

	int		InspectionLevel;
	double	NGThresholdP;
	double	NGThresholdR;
	int		MinimumNGSizeP;
	bool	DoneResistIns;
	int		NGThresholdForResist;
	int		MinimumNGSizeForResist;
	bool	DonePadIns;
	int		NGThresholdForPad;
	int		MinimumNGSizeForPad;
};

#endif // THRESHOLDSETTINGFORM_H
