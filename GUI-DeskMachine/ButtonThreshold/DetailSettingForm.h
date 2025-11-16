#ifndef DETAILSETTINGFORM_H
#define DETAILSETTINGFORM_H

#include <QDialog>
#include "ui_DetailSettingForm.h"
#include "mtImageToolButton.h"
#include "XPixelInspection.h"
#include "ThresholdSettingForm.h"

class DetailSettingForm : public QDialog
{
	Q_OBJECT

	mtImageToolButton	*BtnDecision;
	mtImageToolButton	*BtnCancel;

public:
	DetailSettingForm(QWidget *parent=0,GUIFormBase *Base=0,PixelInspectionBase *PBase=0);
	~DetailSettingForm();

	int		GetInspectionLevel()					{	return InspectionLevel;				}

///protected:
///	virtual	void	paintEvent(QPaintEvent	*event);

private slots:
	void	hsNGThresholdP_BValueChanged		(int Value);
	void	hsNGThresholdP_DValueChanged		(int Value);
	void	dsbNGThresholdP_BValueChanged		(double Value);
	void	dsbNGThresholdP_DValueChanged		(double Value);
	void	hsNGThresholdS_BValueChanged		(int Value);
	void	hsNGThresholdS_DValueChanged		(int Value);
	void	dsbNGThresholdS_BValueChanged		(double Value);
	void	dsbNGThresholdS_DValueChanged		(double Value);
	void	hsNGThresholdR_BValueChanged		(int Value);
	void	hsNGThresholdR_DValueChanged		(int Value);
	void	dsbNGThresholdR_BValueChanged		(double Value);
	void	dsbNGThresholdR_DValueChanged		(double Value);
	void	hsNGThresholdH_BValueChanged		(int Value);
	void	hsNGThresholdH_DValueChanged		(int Value);
	void	dsbNGThresholdH_BValueChanged		(double Value);
	void	dsbNGThresholdH_DValueChanged		(double Value);
	void	diMinimumNGSizePValueChanged		(int Value);
	void	sbMinimumNGSizePValueChanged		(int Value);
	void	diMinimumNGSizeSValueChanged		(int Value);
	void	sbMinimumNGSizeSValueChanged		(int Value);
	void	diMinimumNGSizeRValueChanged		(int Value);
	void	sbMinimumNGSizeRValueChanged		(int Value);
	void	diMinimumNGSizeHValueChanged		(int Value);
	void	sbMinimumNGSizeHValueChanged		(int Value);
	void	hsNGThresholdForPad_BValueChanged	(int Value);
	void	hsNGThresholdForPad_DValueChanged	(int Value);
	void	sbNGThresholdForPad_BValueChanged	(int Value);
	void	sbNGThresholdForPad_DValueChanged	(int Value);
	void	diMinimumNGSizeForPadValueChanged	(int Value);
	void	sbMinimumNGSizeForPadValueChanged	(int Value);
	void	hsNGThresholdForSilk_BValueChanged	(int Value);
	void	hsNGThresholdForSilk_DValueChanged	(int Value);
	void	sbNGThresholdForSilk_BValueChanged	(int Value);
	void	sbNGThresholdForSilk_DValueChanged	(int Value);
	void	diMinimumNGSizeForSilkValueChanged	(int Value);
	void	sbMinimumNGSizeForSilkValueChanged	(int Value);
	void	hsNGThresholdForResist_BValueChanged(int Value);
	void	hsNGThresholdForResist_DValueChanged(int Value);
	void	sbNGThresholdForResist_BValueChanged(int Value);
	void	sbNGThresholdForResist_DValueChanged(int Value);
	void	diMinimumNGSizeForResistValueChanged(int Value);
	void	sbMinimumNGSizeForResistValueChanged(int Value);
	void	hsNGThresholdForHole_BValueChanged	(int Value);
	void	hsNGThresholdForHole_DValueChanged	(int Value);
	void	sbNGThresholdForHole_BValueChanged	(int Value);
	void	sbNGThresholdForHole_DValueChanged	(int Value);
	void	diMinimumNGSizeForHoleValueChanged	(int Value);
	void	sbMinimumNGSizeForHoleValueChanged	(int Value);

	void	gbDetailSettingForPadToggled	(bool checked)	{	SetLayout();	}
	void	gbDetailSettingForSilkToggled	(bool checked)	{	SetLayout();	}
	void	gbDetailSettingForResistToggled	(bool checked)	{	SetLayout();	}
	void	gbDetailSettingForHoleToggled	(bool checked)	{	SetLayout();	}

	void	chSettingForPadToggled		(bool checked)	{	SetEnabledForPad	(checked);	}
	void	chSettingForSilkToggled		(bool checked)	{	SetEnabledForSilk	(checked);	}
	void	chSettingForResistToggled	(bool checked)	{	SetEnabledForResist	(checked);	}
	void	chSettingForHoleToggled		(bool checked)	{	SetEnabledForHole	(checked);	}

	void	pbSaveInsParamClicked	();
	void	pbLoadInsParamClicked	();

	void	SlotBtnDecisionClicked	();
	void	SlotBtnCancelClicked	();

private:
	Ui::DetailSettingFormClass ui;

	const int LayoutHeight;

	ThresholdSettingForm	*ParentWidget;
	GUIFormBase				*GUIBase;
	PixelInspectionBase		*PixelBase;

	int		InspectionLevel;
	int		SearchAreaForMakeTable;
	int		SearchDotBase;
	int		Colored;
	int		DefaultLibraryID;
	int		BrightnessRange;

	int		gbDetailSettingPY			,gbDetailSettingPH;
	int		gbDetailSettingSY			,gbDetailSettingSH;
	int		gbDetailSettingRY			,gbDetailSettingRH;
	int		gbDetailSettingHY			,gbDetailSettingHH;
	int		gbDetailSettingForPadY		,gbDetailSettingForPadH;
	int		gbDetailSettingForSilkY		,gbDetailSettingForSilkH;
	int		gbDetailSettingForResistY	,gbDetailSettingForResistH;
	int		gbDetailSettingForHoleY		,gbDetailSettingForHoleH;
	int		chbIsCalcPixelInterPorationY;
	int		gbDetailSettingY			,gbDetailSettingH;
	int		lbDecisionY;
	int		lbCancelY;
///	int		chSettingForPadY;
	int		chSettingForSilkY;
	int		chSettingForResistY;
	int		chSettingForHoleY;
	int		H;

	void	SetNGThresholdP_B(double Value)			{	ui.hsNGThresholdP_B->setValue(-Value*10);			ui.dsbNGThresholdP_B->setValue(Value);			}
	double 	GetNGThresholdP_B()						{	return PixelBase->getNGThresholdP_B();				}
	void	SetNGThresholdP_D(double Value)			{	ui.hsNGThresholdP_D->setValue(Value*10);			ui.dsbNGThresholdP_D->setValue(Value);			}
	double 	GetNGThresholdP_D()						{	return PixelBase->getNGThresholdP_D();				}
	void	SetNGThresholdS_B(double Value)			{	ui.hsNGThresholdS_B->setValue(-Value*10);			ui.dsbNGThresholdS_B->setValue(Value);			}
	double 	GetNGThresholdS_B()						{	return PixelBase->getNGThresholdS_B();				}
	void	SetNGThresholdS_D(double Value)			{	ui.hsNGThresholdS_D->setValue(Value*10);			ui.dsbNGThresholdS_D->setValue(Value);			}
	double 	GetNGThresholdS_D()						{	return PixelBase->getNGThresholdS_D();				}
	void	SetNGThresholdR_B(double Value)			{	ui.hsNGThresholdR_B->setValue(-Value*10);			ui.dsbNGThresholdR_B->setValue(Value);			}
	double 	GetNGThresholdR_B()						{	return PixelBase->getNGThresholdR_B();				}
	void	SetNGThresholdR_D(double Value)			{	ui.hsNGThresholdR_D->setValue(Value*10);			ui.dsbNGThresholdR_D->setValue(Value);			}
	double 	GetNGThresholdR_D()						{	return PixelBase->getNGThresholdR_D();				}
	void	SetNGThresholdH_B(double Value)			{	ui.hsNGThresholdH_B->setValue(-Value*10);			ui.dsbNGThresholdH_B->setValue(Value);			}
	double 	GetNGThresholdH_B()						{	return PixelBase->getNGThresholdH_B();				}
	void	SetNGThresholdH_D(double Value)			{	ui.hsNGThresholdH_D->setValue(Value*10);			ui.dsbNGThresholdH_D->setValue(Value);			}
	double 	GetNGThresholdH_D()						{	return PixelBase->getNGThresholdH_D();				}
	void	SetMinimumNGSizeP(int Value)			{	ui.diMinimumNGSizeP->setValue(Value);				ui.sbMinimumNGSizeP->setValue(Value);			}
	int		GetMinimumNGSizeP()						{	return PixelBase->getMinimumNGSizeP();				}
	void	SetMinimumNGSizeS(int Value)			{	ui.diMinimumNGSizeS->setValue(Value);				ui.sbMinimumNGSizeS->setValue(Value);			}
	int		GetMinimumNGSizeS()						{	return PixelBase->getMinimumNGSizeS();				}
	void	SetMinimumNGSizeR(int Value)			{	ui.diMinimumNGSizeR->setValue(Value);				ui.sbMinimumNGSizeR->setValue(Value);			}
	int		GetMinimumNGSizeR()						{	return PixelBase->getMinimumNGSizeR();				}
	void	SetMinimumNGSizeH(int Value)			{	ui.diMinimumNGSizeH->setValue(Value);				ui.sbMinimumNGSizeH->setValue(Value);			}
	int		GetMinimumNGSizeH()						{	return PixelBase->getMinimumNGSizeH();				}
	void	SetCheckPadIns(bool Check)				{	ui.chSettingForPad->setChecked(Check);				}
	bool	GetCheckPadIns()						{	return PixelBase->getCheckPadIns();					}
	void	SetCheckSilkIns(bool Check)				{	ui.chSettingForSilk->setChecked(Check);				}
	bool	GetCheckSilkIns()						{	return PixelBase->getCheckSilkIns();				}
	void	SetCheckResistIns(bool Check)			{	ui.chSettingForResist->setChecked(Check);			}
	bool	GetCheckResistIns()						{	return PixelBase->getCheckResistIns();				}
	void	SetCheckHoleIns(bool Check)				{	ui.chSettingForHole->setChecked(Check);				}
	bool	GetCheckHoleIns()						{	return PixelBase->getCheckHoleIns();				}
	void	SetDonePadIns(bool Check)				{	ui.gbDetailSettingForPad->setChecked(Check);		}
	bool	GetDonePadIns()							{	return PixelBase->getDonePadIns();					}
	void	SetDoneSilkIns(bool Check)				{	ui.gbDetailSettingForSilk->setChecked(Check);		}
	bool	GetDoneSilkIns()						{	return PixelBase->getDoneSilkIns();					}
	void	SetDoneResistIns(bool Check)			{	ui.gbDetailSettingForResist->setChecked(Check);		}
	bool	GetDoneResistIns()						{	return PixelBase->getDoneResistIns();				}
	void	SetDoneHoleIns(bool Check)				{	ui.gbDetailSettingForHole->setChecked(Check);		}
	bool	GetDoneHoleIns()						{	return PixelBase->getDoneHoleIns();					}
	void	SetNGThresholdForPad_B(int Value)		{	ui.hsNGThresholdForPad_B->setValue(ui.hsNGThresholdForPad_B->maximum()-Value+1);		ui.sbNGThresholdForPad_B->setValue(Value);		}
	int		GetNGThresholdForPad_B()				{	return PixelBase->getNGThresholdForPad_B();			}
	void	SetNGThresholdForPad_D(int Value)		{	ui.hsNGThresholdForPad_D->setValue(Value);			ui.sbNGThresholdForPad_D->setValue(Value);		}
	int		GetNGThresholdForPad_D()				{	return PixelBase->getNGThresholdForPad_D();			}
	void	SetMinimumNGSizeForPad(int Value)		{	ui.diMinimumNGSizeForPad->setValue(Value);			ui.sbMinimumNGSizeForPad->setValue(Value);		}
	int		GetMinimumNGSizeForPad()				{	return PixelBase->getMinimumNGSizeForPad();			}
	void	SetNGThresholdForSilk_B(int Value)		{	ui.hsNGThresholdForSilk_B->setValue(ui.hsNGThresholdForSilk_B->maximum()-Value+1);		ui.sbNGThresholdForSilk_B->setValue(Value);		}
	int		GetNGThresholdForSilk_B()				{	return PixelBase->getNGThresholdForSilk_B();		}
	void	SetNGThresholdForSilk_D(int Value)		{	ui.hsNGThresholdForSilk_D->setValue(Value);			ui.sbNGThresholdForSilk_D->setValue(Value);		}
	int		GetNGThresholdForSilk_D()				{	return PixelBase->getNGThresholdForSilk_D();		}
	void	SetMinimumNGSizeForSilk(int Value)		{	ui.diMinimumNGSizeForSilk->setValue(Value);			ui.sbMinimumNGSizeForSilk->setValue(Value);		}
	int		GetMinimumNGSizeForSilk()				{	return PixelBase->getMinimumNGSizeForSilk();		}
	void	SetNGThresholdForResist_B(int Value)	{	ui.hsNGThresholdForResist_B->setValue(ui.hsNGThresholdForResist_B->maximum()-Value+1);	ui.sbNGThresholdForResist_B->setValue(Value);	}
	int		GetNGThresholdForResist_B()				{	return PixelBase->getNGThresholdForResist_B();		}
	void	SetNGThresholdForResist_D(int Value)	{	ui.hsNGThresholdForResist_D->setValue(Value);		ui.sbNGThresholdForResist_D->setValue(Value);	}
	int		GetNGThresholdForResist_D()				{	return PixelBase->getNGThresholdForResist_D();		}
	void	SetMinimumNGSizeForResist(int Value)	{	ui.diMinimumNGSizeForResist->setValue(Value);		ui.sbMinimumNGSizeForResist->setValue(Value);	}
	int		GetMinimumNGSizeForResist()				{	return PixelBase->getMinimumNGSizeForResist();		}
	void	SetNGThresholdForHole_B(int Value)		{	ui.hsNGThresholdForHole_B->setValue(ui.hsNGThresholdForHole_B->maximum()-Value+1);		ui.sbNGThresholdForHole_B->setValue(Value);		}
	int		GetNGThresholdForHole_B()				{	return PixelBase->getNGThresholdForHole_B();		}
	void	SetNGThresholdForHole_D(int Value)		{	ui.hsNGThresholdForHole_D->setValue(Value);			ui.sbNGThresholdForHole_D->setValue(Value);		}
	int		GetNGThresholdForHole_D()				{	return PixelBase->getNGThresholdForHole_D();		}
	void	SetMinimumNGSizeForHole(int Value)		{	ui.diMinimumNGSizeForHole->setValue(Value);			ui.sbMinimumNGSizeForHole->setValue(Value);		}
	int		GetMinimumNGSizeForHole()				{	return PixelBase->getMinimumNGSizeForHole();		}
	void	SetIsCalcPixelInterPoration(bool Check)	{	ui.chbIsCalcPixelInterPoration->setChecked(Check);	}
	bool	GetIsCalcPixelInterPoration()			{	return PixelBase->getIsCalcPixelInterPoration();	}

	void	SetLayout();

	void	SetEnabledForPad	(bool checked);
	void	SetEnabledForSilk	(bool checked);
	void	SetEnabledForResist	(bool checked);
	void	SetEnabledForHole	(bool checked);

	void	SearchThresholdFile(QString SearchDir,QStringList SearchStrs,QStringList &FilePathList);
	bool	CheckLoadParam();
};

#endif // DETAILSETTINGFORM_H
