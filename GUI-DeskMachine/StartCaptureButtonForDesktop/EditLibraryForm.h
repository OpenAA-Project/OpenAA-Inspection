#ifndef EDITLIBRARYFORM_H
#define EDITLIBRARYFORM_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QSpinBox>
#include "XGUIFormBase.h"
#include "XAutoAlignment.h"
#include "XAutoPCBHoleAligner.h"
#include "XDisplayImage.h"
#include "ui_EditLibraryForm.h"
#include "XDynamicClassify.h"

class	GUICmdGetColorLogic : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	GUICmdGetColorLogic(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckColorLogic : public GUICmdPacketBase
{
public:
	ColorLogic	CLogic;

	GUICmdAckColorLogic(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(ImagePointerContainer &Images,FlexArea &Area);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class EditLibraryForm : public QDialog,public FunctionServerClass
{
	Q_OBJECT

public:
	EditLibraryForm(int Numb=0,QWidget *parent=0);
	~EditLibraryForm();

	Ui::EditLibraryFormClass ui;

	void	SetLayersBase	(LayersBase *Base)	{	pLayersBase=Base;	}
	void	SetLanguageCode	(int LCode)			{	LanguageCode=LCode;	}
	void	SetLibNumb		(int Numb,bool EnableDynamicClassify=false);
	void	SetDebug		(bool Enable);
	void	Execute			();
	void	ExecuteDrawEnd	(FlexArea &Area);
	void	Update			(bool Enable);
	void	ExecClose		();

	void	SetHoleGerberButton(int LibID,int Index);

public slots:
	void	pushButtonUpdateClicked			();

private slots:
	void	rbSelectRectangleToggled		(bool checked);
	void	rbSelectPolygonToggled			(bool checked);
	void	verticalScrollBarValueChanged	(int Value);
//////// test
	/*void	tbShowMaskArea_clicked			(bool checked);
	void	tbEffectiveMask_clicked			(bool checked);
	void	tbIneffectiveMask_clicked		(bool checked);*/
////////
	void	tbAddColorClicked				(bool checked);
	void	tbColorClicked					(bool checked);
	void	tbGerberClicked					(bool checked);
	void	tbClearColorClicked				(bool checked);
	void	sbNoiseShrinkValueChanged		(int Value);
	void	sbExpandForPickupValueChanged	(int Value);
	void	pushButtonStartNextClicked		();
	void	pushButtonFinishClicked			();

private:
	LayersBase	*pLayersBase;
	int			LanguageCode;

    QFont font1[5];

	QFrame		**fmLibContainer;
	QToolButton	**tbColor[9];
	QLabel		**lbLibName;
	QLineEdit	**leLibName;
	QToolButton	**tbOutlineI;
	QToolButton	**tbOutlineT;
	QToolButton	**tbOutlineO;
	QToolButton	**tbAddColor;
	QToolButton	**tbClearColor;
	QLabel		**lbNoiseShrink;
	QSpinBox	**sbNoiseShrink;
	QLabel		**lbExpandForPickup;
	QSpinBox	**sbExpandForPickup;
	QToolButton	**tbGerber[4];

	int			*iCLogic;
	int			*iPickupAddColor;
	int			*iPickupDeleteColor;
	NPListPack<ColorLogic>	*AddCLogicList;
	int			*tbGerberCount;

	int		LibNumb;			//ÉâÉCÉuÉâÉäÇÃå¬êî
	int		ActiveButtonIndex;
	int		AutoAlignmentLibNumb;
	int		AutoPCBHoleAlignerLibNumb;
	int		DynamicClassifyLibNumb;
	//AutoAlignmentLibrary		**AlignLib;
	//AutoPCBHoleAlignerLibrary	**PCBHoleAlignLib;
	//DynamicClassifyLibrary		**DClassifyLib;
	AlgorithmLibraryLevelContainer **AlignLevelLib		;
	AlgorithmLibraryLevelContainer **PCBHoleLevelLib		;
	AlgorithmLibraryLevelContainer **DClassifyLevelLib	;

	void	DeleteFormComponent();
	void	SetAutoAlignmentLibNumb		(int Numb,AlgorithmBase	*ABase);
	void	SetAutoPCBHoleAlignerLibNumb(int Numb,AlgorithmBase	*ABase);
	void	SetDynamicClassifyLibNumb	(int Numb,AlgorithmBase	*ABase);
	void	ShowLibrary(int i,AutoAlignmentLibrary *Lib		,AlgorithmBase	*AlgorithmBasePointer);
	void	ShowLibrary(int i,AutoPCBHoleAlignerLibrary *Lib,AlgorithmBase	*AlgorithmBasePointer);
	void	ShowLibrary(int i,DynamicClassifyLibrary *Lib	,AlgorithmBase	*AlgorithmBasePointer);
	bool	ShowMasterImage(void);
	QString GetImagePanelName(int phase,const QString& FormName);
};

#endif // EDITLIBRARYFORM_H
