#ifndef DETAILSETTINGFORM_H
#define DETAILSETTINGFORM_H

#include <QDialog>
#include "ui_DetailSettingForm.h"
#include "mtImageToolButton.h"
#include "XPixelInspection.h"
#include "ThresholdSettingForm.h"

const int PLibNumb=4;

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
	void	hsNGThresholdPValueChanged			(int Value);
	void	dsbNGThresholdPValueChanged			(double Value);
	void	hsNGThresholdSValueChanged			(int Value);
	void	dsbNGThresholdSValueChanged			(double Value);
	void	hsNGThresholdRValueChanged			(int Value);
	void	dsbNGThresholdRValueChanged			(double Value);
	void	hsNGThresholdHValueChanged			(int Value);
	void	dsbNGThresholdHValueChanged			(double Value);
	void	diMinimumNGSizePValueChanged		(int Value);
	void	diMinimumNGSizeSValueChanged		(int Value);
	void	diMinimumNGSizeRValueChanged		(int Value);
	void	diMinimumNGSizeHValueChanged		(int Value);
	void	hsNGThresholdForPadValueChanged		(int Value);
	void	diMinimumNGSizeForPadValueChanged	(int Value);
	void	hsNGThresholdForSilkValueChanged	(int Value);
	void	diMinimumNGSizeForSilkValueChanged	(int Value);
	void	hsNGThresholdForResistValueChanged	(int Value);
	void	diMinimumNGSizeForResistValueChanged(int Value);
	void	hsNGThresholdForHoleValueChanged	(int Value);
	void	diMinimumNGSizeForHoleValueChanged	(int Value);

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
	int		Colored;
	int		DefaultLibraryID;
	double 	NGThresholdP				,NGThresholdS	,NGThresholdR	,NGThresholdH;
	int		MinimumNGSizeP				,MinimumNGSizeS	,MinimumNGSizeR	,MinimumNGSizeH;
	bool	CheckPadIns					,CheckSilkIns	,CheckResistIns	,CheckHoleIns;
	bool	DonePadIns					,DoneSilkIns	,DoneResistIns	,DoneHoleIns;
	int		NGThresholdForPad			,MinimumNGSizeForPad;
	int		NGThresholdForSilk			,MinimumNGSizeForSilk;
	int		NGThresholdForResist		,MinimumNGSizeForResist;
	int		NGThresholdForHole			,MinimumNGSizeForHole;
	int		BrightnessRange;
	bool	IsCalcPixelInterPorationPad	,IsCalcPixelInterPorationSilk	,IsCalcPixelInterPorationResist	,IsCalcPixelInterPorationHole;

	int		gbDetailSettingPY				,gbDetailSettingPH;
	int		gbDetailSettingSY				,gbDetailSettingSH;
	int		gbDetailSettingRY				,gbDetailSettingRH;
	int		gbDetailSettingHY				,gbDetailSettingHH;
	int		gbDetailSettingForPadY			,gbDetailSettingForPadH;
	int		gbDetailSettingForSilkY			,gbDetailSettingForSilkH;
	int		gbDetailSettingForResistY		,gbDetailSettingForResistH;
	int		gbDetailSettingForHoleY			,gbDetailSettingForHoleH;
	int		chbIsCalcPixelInterPorationPadY	,chbIsCalcPixelInterPorationSilkY,chbIsCalcPixelInterPorationResistY,chbIsCalcPixelInterPorationHoleY;
	int		gbDetailSettingY				,gbDetailSettingH;
	int		lbDecisionY;
	int		lbCancelY;
///	int		chSettingForPadY;
	int		chSettingForSilkY;
	int		chSettingForResistY;
	int		chSettingForHoleY;
	int		H;

	typedef	enum	_PixelType{
		_Other		=-1
		,_Pad		=0
		,_Silk		=1
		,_Resist	=2
		,_Hole		=3
	}PixelType;

	PixelType PType;
	QStringList	PLibSettingStringList;		//PixelLibrarySetting.dat‚Ì•¶Žš—ñ

	bool	InitialMultiAlgorithmSupport;	//MultiAlgorithmSupport‚Ìinitialˆ—

	QStringList	PixelLibraryIDList;
	QStringList	PixelLibraryNameList;
	QStringList	AlgorithmListName;
	QStringList	LibraryIDList;
	QStringList	LibraryNameList;

	AlgorithmLibraryListContainer	PixelAList;
	AlgorithmLibraryListContainer	AAlignAList;
	AlgorithmBase					*PixelAlgorithmBasePointer;
	AlgorithmInPageRoot				*PixelAlgorithmInPageRootPointer;

	QCheckBox		*chSetting[4];
	QDoubleSpinBox	*dsbNGThreshold[4];
	QSpinBox		*sbMinimumNGSize[4];
	QGroupBox		*gbDetailSetting[4];
	QSpinBox		*sbNGThreshold[4];
	QSpinBox		*sbDetailMinimumNGSize[4];
	QCheckBox		*chbIsCalcPixelInterPoration[4];

	AlgorithmLibraryLevelContainer	*PLibLevelList[PLibNumb];
	//PixelInspectionLibrary *PLibList[PLibNumb];

	void	InitialSetting();

	bool	LoadPixelLibrarySetting();
	bool	CheckSettingData();
	bool	LoadAlgorithmData();
	bool	CheckPixelLibrarySettingData(const QStringList &myStringList,QString &Msg);
	bool	CreateLibraryNameList(const QString AlgorithmName);
	bool	ExecMultiAlgorithmSupport();
	bool	CalcMultiAlgorithmSupport(int PixelLibID,const QString AlgorithmName,int LibID,QString &Msg);
	void	SetLibData(PixelType PType,PixelInspectionLibrary *PLib);

	void	SetNGThresholdP(double Value)					{	NGThresholdP=Value;						ui.hsNGThresholdP					->setValue(Value*10);	ui.dsbNGThresholdP			->setValue(Value);	}
	double 	GetNGThresholdP()								{	return NGThresholdP;					}
	void	SetNGThresholdS(double Value)					{	NGThresholdS=Value;						ui.hsNGThresholdS					->setValue(Value*10);	ui.dsbNGThresholdS			->setValue(Value);	}
	double 	GetNGThresholdS()								{	return NGThresholdS;					}
	void	SetNGThresholdR(double Value)					{	NGThresholdR=Value;						ui.hsNGThresholdR					->setValue(Value*10);	ui.dsbNGThresholdR			->setValue(Value);	}
	double 	GetNGThresholdR()								{	return NGThresholdR;					}
	void	SetNGThresholdH(double Value)					{	NGThresholdH=Value;						ui.hsNGThresholdH					->setValue(Value*10);	ui.dsbNGThresholdH			->setValue(Value);	}
	double 	GetNGThresholdH()								{	return NGThresholdH;					}
	void	SetMinimumNGSizeP(int Value)					{	MinimumNGSizeP=Value;					ui.diMinimumNGSizeP					->setValue(Value);		ui.sbMinimumNGSizeP			->setValue(Value);	}
	int		GetMinimumNGSizeP()								{	return MinimumNGSizeP;					}
	void	SetMinimumNGSizeS(int Value)					{	MinimumNGSizeS=Value;					ui.diMinimumNGSizeS					->setValue(Value);		ui.sbMinimumNGSizeS			->setValue(Value);	}
	int		GetMinimumNGSizeS()								{	return MinimumNGSizeS;					}
	void	SetMinimumNGSizeR(int Value)					{	MinimumNGSizeR=Value;					ui.diMinimumNGSizeR					->setValue(Value);		ui.sbMinimumNGSizeR			->setValue(Value);	}
	int		GetMinimumNGSizeR()								{	return MinimumNGSizeR;					}
	void	SetMinimumNGSizeH(int Value)					{	MinimumNGSizeH=Value;					ui.diMinimumNGSizeH					->setValue(Value);		ui.sbMinimumNGSizeH			->setValue(Value);	}
	int		GetMinimumNGSizeH()								{	return MinimumNGSizeH;					}
	void	SetCheckPadIns(bool Check)						{	CheckPadIns=Check;						ui.chSettingForPad					->setChecked(Check);	}
	bool	GetCheckPadIns()								{	return CheckPadIns;						}
	void	SetCheckSilkIns(bool Check)						{	CheckSilkIns=Check;						ui.chSettingForSilk					->setChecked(Check);	}
	bool	GetCheckSilkIns()								{	return CheckSilkIns;					}
	void	SetCheckResistIns(bool Check)					{	CheckResistIns=Check;					ui.chSettingForResist				->setChecked(Check);	}
	bool	GetCheckResistIns()								{	return CheckResistIns;					}
	void	SetCheckHoleIns(bool Check)						{	CheckHoleIns=Check;						ui.chSettingForHole					->setChecked(Check);	}
	bool	GetCheckHoleIns()								{	return CheckHoleIns;					}
	void	SetDonePadIns(bool Check)						{	DonePadIns=Check;						ui.gbDetailSettingForPad			->setChecked(Check);	}
	bool	GetDonePadIns()									{	return DonePadIns;						}
	void	SetDoneSilkIns(bool Check)						{	DoneSilkIns=Check;						ui.gbDetailSettingForSilk			->setChecked(Check);	}
	bool	GetDoneSilkIns()								{	return DoneSilkIns;						}
	void	SetDoneResistIns(bool Check)					{	DoneResistIns=Check;					ui.gbDetailSettingForResist			->setChecked(Check);	}
	bool	GetDoneResistIns()								{	return DoneResistIns;					}
	void	SetDoneHoleIns(bool Check)						{	DoneHoleIns=Check;						ui.gbDetailSettingForHole			->setChecked(Check);	}
	bool	GetDoneHoleIns()								{	return DoneHoleIns;						}
	void	SetNGThresholdForPad(int Value)					{	NGThresholdForPad=Value;				ui.hsNGThresholdForPad				->setValue(Value);		ui.sbNGThresholdForPad		->setValue(Value);	}
	int		GetNGThresholdForPad()							{	return NGThresholdForPad;				}
	void	SetMinimumNGSizeForPad(int Value)				{	MinimumNGSizeForPad=Value;				ui.diMinimumNGSizeForPad			->setValue(Value);		ui.sbMinimumNGSizeForPad	->setValue(Value);	}
	int		GetMinimumNGSizeForPad()						{	return MinimumNGSizeForPad;				}
	void	SetNGThresholdForSilk(int Value)				{	NGThresholdForSilk=Value;				ui.hsNGThresholdForSilk				->setValue(Value);		ui.sbNGThresholdForSilk		->setValue(Value);	}
	int		GetNGThresholdForSilk()							{	return NGThresholdForSilk;				}
	void	SetMinimumNGSizeForSilk(int Value)				{	MinimumNGSizeForSilk=Value;				ui.diMinimumNGSizeForSilk			->setValue(Value);		ui.sbMinimumNGSizeForSilk	->setValue(Value);	}
	int		GetMinimumNGSizeForSilk()						{	return MinimumNGSizeForSilk;			}
	void	SetNGThresholdForResist(int Value)				{	NGThresholdForResist=Value;				ui.hsNGThresholdForResist			->setValue(Value);		ui.sbNGThresholdForResist	->setValue(Value);	}
	int		GetNGThresholdForResist()						{	return NGThresholdForResist;			}
	void	SetMinimumNGSizeForResist(int Value)			{	MinimumNGSizeForResist=Value;			ui.diMinimumNGSizeForResist			->setValue(Value);		ui.sbMinimumNGSizeForResist	->setValue(Value);	}
	int		GetMinimumNGSizeForResist()						{	return MinimumNGSizeForResist;			}
	void	SetNGThresholdForHole(int Value)				{	NGThresholdForHole=Value;				ui.hsNGThresholdForHole				->setValue(Value);		ui.sbNGThresholdForHole		->setValue(Value);	}
	int		GetNGThresholdForHole()							{	return NGThresholdForHole;				}
	void	SetMinimumNGSizeForHole(int Value)				{	MinimumNGSizeForHole=Value;				ui.diMinimumNGSizeForHole			->setValue(Value);		ui.sbMinimumNGSizeForHole	->setValue(Value);	}
	int		GetMinimumNGSizeForHole()						{	return MinimumNGSizeForHole;			}
	void	SetIsCalcPixelInterPorationPad(bool Check)		{	IsCalcPixelInterPorationPad=Check;		ui.chbIsCalcPixelInterPorationPad	->setChecked(Check);	}
	bool	GetIsCalcPixelInterPorationPad()				{	return IsCalcPixelInterPorationPad;		}
	void	SetIsCalcPixelInterPorationSilk(bool Check)		{	IsCalcPixelInterPorationSilk=Check;		ui.chbIsCalcPixelInterPorationSilk	->setChecked(Check);	}
	bool	GetIsCalcPixelInterPorationSilk()				{	return IsCalcPixelInterPorationSilk;	}
	void	SetIsCalcPixelInterPorationResist(bool Check)	{	IsCalcPixelInterPorationResist=Check;	ui.chbIsCalcPixelInterPorationResist->setChecked(Check);	}
	bool	GetIsCalcPixelInterPorationResist()				{	return IsCalcPixelInterPorationResist;	}
	void	SetIsCalcPixelInterPorationHole(bool Check)		{	IsCalcPixelInterPorationHole=Check;		ui.chbIsCalcPixelInterPorationHole	->setChecked(Check);	}
	bool	GetIsCalcPixelInterPorationHole()				{	return IsCalcPixelInterPorationHole;	}

	void	SetLayout();

	void	SetEnabledForPad	(bool checked);
	void	SetEnabledForSilk	(bool checked);
	void	SetEnabledForResist	(bool checked);
	void	SetEnabledForHole	(bool checked);

	bool	CheckIsEdit();
};

#endif // DETAILSETTINGFORM_H
