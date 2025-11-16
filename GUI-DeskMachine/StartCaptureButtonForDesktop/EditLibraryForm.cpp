#include "StartCaptureButtonForDesktopResource.h"
#include "XDisplayImage.h"
#include "AutoAlignmentImagePanel.h"
#include "AutoPCBHoleAlignerImagePanel.h"
#include "XAutoAlignmentPacket.h"
#include "XAutoPCBHoleAlignerPacket.h"
#include "EditLibraryForm.h"
#include "StartCaptureButtonForDesktop.h"
#include "AutoMaskingPIImagePanel.h"
#include "XPropertyAutoMaskingPIPacket.h"
#include "DynamicClassifyImagePanel.h"
#include "XDynamicClassifyPacket.h"
#include <QMessageBox>

extern const	char	*sRoot;
extern const	char	*sName;

GUICmdGetColorLogic::GUICmdGetColorLogic(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGetColorLogic::Load(QIODevice *f)
{
	BYTE	D;

	if(::Load(f,D)==false){
		return false;
	}
	if(Area.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdGetColorLogic::Save(QIODevice *f)
{
	if(Area.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdGetColorLogic::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckColorLogic	*SendBack=GetSendBack(GUICmdAckColorLogic,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	if(Pg!=NULL){
		ImagePointerContainer Images;
		Pg->GetMasterImages(Images);
		SendBack->MakeData(Images,Area);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckColorLogic::GUICmdAckColorLogic(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAckColorLogic::Load(QIODevice *f)
{
	if(CLogic.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckColorLogic::Save(QIODevice *f)
{
	if(CLogic.Save(f)==false){
		return false;
	}
	return true;
}
void	GUICmdAckColorLogic::MakeData(ImagePointerContainer &Images,FlexArea &Area)
{
	Area.CreateColorLogic(Images, CLogic);
}

void	GUICmdAckColorLogic::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=======================================================================
EditLibraryForm::EditLibraryForm(int Numb,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
//	setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);

	pLayersBase			=NULL;

	fmLibContainer		=NULL;
	tbColor[0]			=NULL;
	tbColor[1]			=NULL;
	tbColor[2]			=NULL;
	tbColor[3]			=NULL;
	tbColor[4]			=NULL;
	tbColor[5]			=NULL;
	tbColor[6]			=NULL;
	tbColor[7]			=NULL;
	tbColor[8]			=NULL;
	lbLibName			=NULL;
	leLibName			=NULL;
	tbOutlineI			=NULL;
	tbOutlineT			=NULL;
	tbOutlineO			=NULL;
	tbAddColor			=NULL;
	tbClearColor		=NULL;
	lbNoiseShrink		=NULL;
	sbNoiseShrink		=NULL;
	lbExpandForPickup	=NULL;
	sbExpandForPickup	=NULL;
	tbGerber[0]			=NULL;
	tbGerber[1]			=NULL;
	tbGerber[2]			=NULL;
	tbGerber[3]			=NULL;

	iCLogic				=NULL;
	iPickupAddColor		=NULL;
	iPickupDeleteColor	=NULL;
	AddCLogicList		=NULL;
	tbGerberCount		=NULL;

	ActiveButtonIndex		 =-1;
	AutoAlignmentLibNumb	 =0;
	AutoPCBHoleAlignerLibNumb=0;
	DynamicClassifyLibNumb	 =0;
	//AlignLib				=NULL;
	//PCBHoleAlignLib		=NULL;
	//DClassifyLib			=NULL;
	AlignLevelLib		=NULL;
	PCBHoleLevelLib		=NULL;
	DClassifyLevelLib	=NULL;

	//画面の作成
	SetLibNumb(Numb);

	//connect
	connect(ui.rbSelectRectangle	,SIGNAL(toggled(bool))		,this,SLOT(rbSelectRectangleToggled(bool)));
	connect(ui.rbSelectPolygon		,SIGNAL(toggled(bool))		,this,SLOT(rbSelectPolygonToggled(bool)));
	connect(ui.tbShowMaskArea		,SIGNAL(clicked(bool))		,this,SLOT(tbAddColorClicked(bool)));
	connect(ui.tbEffectiveMask		,SIGNAL(clicked(bool))		,this,SLOT(tbAddColorClicked(bool)));
	connect(ui.tbIneffectiveMask	,SIGNAL(clicked(bool))		,this,SLOT(tbAddColorClicked(bool)));
	connect(ui.verticalScrollBar	,SIGNAL(valueChanged(int))	,this,SLOT(verticalScrollBarValueChanged(int)));
	connect(ui.pushButtonUpdate		,SIGNAL(clicked())			,this,SLOT(pushButtonUpdateClicked()));
	connect(ui.pushButtonStartNext	,SIGNAL(clicked())			,this,SLOT(pushButtonStartNextClicked()));
	connect(ui.pushButtonFinish		,SIGNAL(clicked())			,this,SLOT(pushButtonFinishClicked()));

	//画面表示部の言語対応
	LangSolver.SetUI(this);
}

EditLibraryForm::~EditLibraryForm()
{
	DeleteFormComponent();
}

void EditLibraryForm::SetLibNumb(int Numb,bool EnableDynamicClassify)
{
	//delete
	DeleteFormComponent();

	//QScrollBar
	int ScrollBarMaximum=0;
	if(Numb>4){
		ScrollBarMaximum=120*(Numb-4);
	}
	ui.verticalScrollBar->setMaximum(ScrollBarMaximum);

	LibNumb=Numb;

	//画面の作成
	if(LibNumb==0){
		return;
	}

	fmLibContainer		=new QFrame		*[LibNumb];
	tbColor[0]			=new QToolButton*[LibNumb];
	tbColor[1]			=new QToolButton*[LibNumb];
	tbColor[2]			=new QToolButton*[LibNumb];
	tbColor[3]			=new QToolButton*[LibNumb];
	tbColor[4]			=new QToolButton*[LibNumb];
	tbColor[5]			=new QToolButton*[LibNumb];
	tbColor[6]			=new QToolButton*[LibNumb];
	tbColor[7]			=new QToolButton*[LibNumb];
	tbColor[8]			=new QToolButton*[LibNumb];
	lbLibName			=new QLabel		*[LibNumb];
	leLibName			=new QLineEdit	*[LibNumb];
	tbOutlineI			=new QToolButton*[LibNumb];
	tbOutlineT			=new QToolButton*[LibNumb];
	tbOutlineO			=new QToolButton*[LibNumb];
	tbAddColor			=new QToolButton*[LibNumb];
	tbClearColor		=new QToolButton*[LibNumb];
	lbNoiseShrink		=new QLabel		*[LibNumb];
	sbNoiseShrink		=new QSpinBox	*[LibNumb];
	lbExpandForPickup	=new QLabel		*[LibNumb];
	sbExpandForPickup	=new QSpinBox	*[LibNumb];
	tbGerber[0]			=new QToolButton*[LibNumb];
	tbGerber[1]			=new QToolButton*[LibNumb];
	tbGerber[2]			=new QToolButton*[LibNumb];
	tbGerber[3]			=new QToolButton*[LibNumb];

	//日本語
    font1[0].setPointSize(12);
    font1[0].setBold(true);
    font1[0].setWeight(75);
	//English
    font1[1].setPointSize(9);
    font1[1].setBold(true);
    font1[1].setWeight(75);
	//簡体中文
    font1[2].setPointSize(9);
    font1[2].setBold(true);
    font1[2].setWeight(75);
	//繁体中文
	font1[3].setPointSize(9);
    font1[3].setBold(true);
    font1[3].setWeight(75);
	//Korean
    font1[4].setPointSize(9);
    font1[4].setBold(true);
    font1[4].setWeight(75);

    QFont font2[5];
	//日本語
    font2[0].setPointSize(16);
    font2[0].setBold(true);
    font2[0].setWeight(75);
	//English
    font2[1].setPointSize(9);
    font2[1].setBold(true);
    font2[1].setWeight(75);
	//簡体中文
    font2[2].setPointSize(9);
    font2[2].setBold(true);
    font2[2].setWeight(75);
	//繁体中文
	font2[3].setPointSize(9);
    font2[3].setBold(true);
    font2[3].setWeight(75);
	//Korean
    font2[4].setPointSize(9);
    font2[4].setBold(true);
    font2[4].setWeight(75);

    QFont tbColorFont;
    tbColorFont.setPointSize(10);

	QPalette P;
	P.setColor(QPalette::Base,QColor(Qt::cyan));

	for(int i=0;i<LibNumb;i++){
		fmLibContainer[i]	=new QFrame(ui.frame);
		fmLibContainer[i]	->setGeometry(QRect(10, 120*i+10, 531, 111));
	    fmLibContainer[i]	->setFrameShape(QFrame::StyledPanel);
		fmLibContainer[i]	->setFrameShadow(QFrame::Sunken);
	    tbColor[0][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[0][i]		->setGeometry(QRect(10, 10, 31, 31));
	    tbColor[0][i]		->setFont(tbColorFont);
		tbColor[0][i]		->setCheckable(true);
		tbColor[0][i]		->setAutoFillBackground(true);
		connect(tbColor[0][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[1][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[1][i]		->setGeometry(QRect(40, 10, 31, 31));
		tbColor[1][i]		->setFont(tbColorFont);
		tbColor[1][i]		->setCheckable(true);
		tbColor[1][i]		->setAutoFillBackground(true);
		connect(tbColor[1][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[2][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[2][i]		->setGeometry(QRect(70, 10, 31, 31));
		tbColor[2][i]		->setFont(tbColorFont);
		tbColor[2][i]		->setCheckable(true);
		tbColor[2][i]		->setAutoFillBackground(true);
		connect(tbColor[2][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[3][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[3][i]		->setGeometry(QRect(10, 40, 31, 31));
		tbColor[3][i]		->setFont(tbColorFont);
		tbColor[3][i]		->setCheckable(true);
		tbColor[3][i]		->setAutoFillBackground(true);
		connect(tbColor[3][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[4][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[4][i]		->setGeometry(QRect(40, 40, 31, 31));
		tbColor[4][i]		->setFont(tbColorFont);
		tbColor[4][i]		->setCheckable(true);
		tbColor[4][i]		->setAutoFillBackground(true);
		connect(tbColor[4][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[5][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[5][i]		->setGeometry(QRect(70, 40, 31, 31));
		tbColor[5][i]		->setFont(tbColorFont);
		tbColor[5][i]		->setCheckable(true);
		tbColor[5][i]		->setAutoFillBackground(true);
		connect(tbColor[5][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[6][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[6][i]		->setGeometry(QRect(10, 70, 31, 31));
		tbColor[6][i]		->setFont(tbColorFont);
		tbColor[6][i]		->setCheckable(true);
		tbColor[6][i]		->setAutoFillBackground(true);
		connect(tbColor[6][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[7][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[7][i]		->setGeometry(QRect(40, 70, 31, 31));
		tbColor[7][i]		->setFont(tbColorFont);
		tbColor[7][i]		->setCheckable(true);
		tbColor[7][i]		->setAutoFillBackground(true);
		connect(tbColor[7][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		tbColor[8][i]		=new QToolButton(fmLibContainer[i]);
		tbColor[8][i]		->setGeometry(QRect(70, 70, 31, 31));
		tbColor[8][i]		->setFont(tbColorFont);
		tbColor[8][i]		->setCheckable(true);
		tbColor[8][i]		->setAutoFillBackground(true);
		connect(tbColor[8][i],SIGNAL(clicked(bool)),this,SLOT(tbColorClicked(bool)));
		lbLibName[i]		=new QLabel(fmLibContainer[i]);
		lbLibName[i]		->setGeometry(QRect(120, 10, 81, 21));
		lbLibName[i]		->setFont(font1[LanguageCode]);
		lbLibName[i]		->setText(LangSolver.GetString(EditLibraryForm_LS,LID_95)/*"ライブラリ名"*/);
		leLibName[i]		=new QLineEdit(fmLibContainer[i]);
		leLibName[i]		->setGeometry(QRect(210, 10, 131, 21));
		leLibName[i]		->setReadOnly(true);
		leLibName[i]		->setPalette(P);
		leLibName[i]		->setFont(font1[LanguageCode]);
		tbOutlineI[i]		=new QToolButton(fmLibContainer[i]);
		tbOutlineI[i]		->setGeometry(QRect(350, 10, 52, 21));
		tbOutlineI[i]		->setCheckable(true);
		tbOutlineI[i]		->setFont(font2[LanguageCode]);
		tbOutlineI[i]		->setText(/**/"-I-");
		tbOutlineI[i]		->setStyleSheet(/**/":checked { background-color: red }");
		connect(tbOutlineI[i],SIGNAL(clicked(bool)),this,SLOT(tbAddColorClicked(bool)));
		tbOutlineT[i]		=new QToolButton(fmLibContainer[i]);
		tbOutlineT[i]		->setGeometry(QRect(409, 10, 52, 21));
		tbOutlineT[i]		->setCheckable(true);
		tbOutlineT[i]		->setFont(font2[LanguageCode]);
		tbOutlineT[i]		->setText(/**/"-T-");
		tbOutlineT[i]		->setStyleSheet(/**/":checked { background-color: red }");
		connect(tbOutlineT[i],SIGNAL(clicked(bool)),this,SLOT(tbAddColorClicked(bool)));
		tbOutlineO[i]		=new QToolButton(fmLibContainer[i]);
		tbOutlineO[i]		->setGeometry(QRect(468, 10, 52, 21));
		tbOutlineO[i]		->setCheckable(true);
		tbOutlineO[i]		->setFont(font2[LanguageCode]);
		tbOutlineO[i]		->setText(/**/"-O-");
		tbOutlineO[i]		->setStyleSheet(/**/":checked { background-color: red }");
		connect(tbOutlineO[i],SIGNAL(clicked(bool)),this,SLOT(tbAddColorClicked(bool)));
		if(i>=1 || EnableDynamicClassify==false){
			tbOutlineI[i]	->setVisible(false);
			tbOutlineT[i]	->setVisible(false);
			tbOutlineO[i]	->setVisible(false);
		}
		tbAddColor[i]		=new QToolButton(fmLibContainer[i]);
		tbAddColor[i]		->setGeometry(QRect(120, 50, 111, 51));
		tbAddColor[i]		->setCheckable(true);
		tbAddColor[i]		->setFont(font2[LanguageCode]);
		tbAddColor[i]		->setText(LangSolver.GetString(EditLibraryForm_LS,LID_96)/*"色追加"*/);
		tbAddColor[i]		->setStyleSheet(/**/":checked { background-color: red }");
		connect(tbAddColor[i],SIGNAL(clicked(bool)),this,SLOT(tbAddColorClicked(bool)));
		tbClearColor[i]		=new QToolButton(fmLibContainer[i]);
		tbClearColor[i]		->setGeometry(QRect(250, 50, 87, 51));
		tbClearColor[i]		->setCheckable(true);
		tbClearColor[i]		->setFont(font2[LanguageCode]);
		tbClearColor[i]		->setText(LangSolver.GetString(EditLibraryForm_LS,LID_97)/*"色クリア"*/);
		connect(tbClearColor[i],SIGNAL(clicked(bool)),this,SLOT(tbClearColorClicked(bool)));
		lbNoiseShrink[i]	=new QLabel(fmLibContainer[i]);
		lbNoiseShrink[i]	->setGeometry(QRect(345, 40, 112, 21));
		lbNoiseShrink[i]	->setFont(font1[LanguageCode]);
		lbNoiseShrink[i]	->setText(LangSolver.GetString(EditLibraryForm_LS,LID_98)/*"ノイズ除去ドット"*/);
		sbNoiseShrink[i]	=new QSpinBox(fmLibContainer[i]);
		sbNoiseShrink[i]	->setGeometry(QRect(460, 35, 61, 31));
		sbNoiseShrink[i]	->setFont(font1[LanguageCode]);
		lbExpandForPickup[i]=new QLabel(fmLibContainer[i]);
		lbExpandForPickup[i]->setGeometry(QRect(345, 75, 112, 21));
		lbExpandForPickup[i]->setFont(font1[LanguageCode]);
		lbExpandForPickup[i]->setText(LangSolver.GetString(EditLibraryForm_LS,LID_99)/*"膨張ドット"*/);
		sbExpandForPickup[i]=new QSpinBox(fmLibContainer[i]);
		sbExpandForPickup[i]->setGeometry(QRect(460, 70, 61, 31));
		sbExpandForPickup[i]->setFont(font1[LanguageCode]);
	    tbGerber[0][i]		=new QToolButton(fmLibContainer[i]);
		tbGerber[0][i]		->setGeometry(QRect(350, 10, 31, 21));
	    tbGerber[0][i]		->setFont(tbColorFont);
		tbGerber[0][i]		->setCheckable(true);
		tbGerber[0][i]		->setText(/**/"G1");
		tbGerber[0][i]		->setVisible(false);
		connect(tbGerber[0][i],SIGNAL(clicked(bool)),this,SLOT(tbGerberClicked(bool)));
	    tbGerber[1][i]		=new QToolButton(fmLibContainer[i]);
		tbGerber[1][i]		->setGeometry(QRect(385, 10, 31, 21));
	    tbGerber[1][i]		->setFont(tbColorFont);
		tbGerber[1][i]		->setCheckable(true);
		tbGerber[1][i]		->setText(/**/"G2");
		tbGerber[1][i]		->setVisible(false);
		connect(tbGerber[1][i],SIGNAL(clicked(bool)),this,SLOT(tbGerberClicked(bool)));
	    tbGerber[2][i]		=new QToolButton(fmLibContainer[i]);
		tbGerber[2][i]		->setGeometry(QRect(420, 10, 31, 21));
	    tbGerber[2][i]		->setFont(tbColorFont);
		tbGerber[2][i]		->setCheckable(true);
		tbGerber[2][i]		->setText(/**/"G3");
		tbGerber[2][i]		->setVisible(false);
		connect(tbGerber[2][i],SIGNAL(clicked(bool)),this,SLOT(tbGerberClicked(bool)));
	    tbGerber[3][i]		=new QToolButton(fmLibContainer[i]);
		tbGerber[3][i]		->setGeometry(QRect(455, 10, 31, 21));
	    tbGerber[3][i]		->setFont(tbColorFont);
		tbGerber[3][i]		->setCheckable(true);
		tbGerber[3][i]		->setText(/**/"G4");
		tbGerber[3][i]		->setVisible(false);
		connect(tbGerber[3][i],SIGNAL(clicked(bool)),this,SLOT(tbGerberClicked(bool)));
	}
}

void EditLibraryForm::SetDebug(bool Enable)
{
//	ui.pushButtonStartNext	->setVisible(Enable);
//	ui.pushButtonFinish		->setVisible(!Enable);
	ui.pushButtonStartNext	->setVisible(false);
	ui.pushButtonFinish		->setVisible(true);
}

static	bool EditLibraryFormFunctionDrawEnd(FunctionServerClass *Obj,GUIFormBase *TartgetForm)
{
	DisplayImage	*a=dynamic_cast<DisplayImage	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	EditLibraryForm	*Form=dynamic_cast<EditLibraryForm *>(Obj);
	if(Form!=NULL){
		FlexArea resultarea;
		a->ToFlexArea( *a->GetRawSDataPoint(),resultarea);
		Form->ExecuteDrawEnd(resultarea);
		return true;
	}
	return false;
}

bool EditLibraryForm::ShowMasterImage(void){
	for(int phase=0;phase<pLayersBase->GetPhaseNumb();phase++){
		//GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,GetTargetImagePanelName(phase));
		GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,GetImagePanelName(phase,/**/"TargetImage"));
		if(TargetImage==NULL)
			return false;
		DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
		TargetImagePanel->ChangeDisplayType(DisplayImage::__Master);
	}
	return true;
}

QString EditLibraryForm::GetImagePanelName(int phase,const QString &FormName){
	QString InstName(/**/"");
	if(pLayersBase->GetPhaseNumb()>1){
		InstName=FormName;
		if(phase>0)
			InstName.append(QString::number(phase+1));
	}
	return InstName;
}

void EditLibraryForm::Execute()
{
	//TargetImagePanelにマスター画像を表示させる
	if(ShowMasterImage()==false)
		return;
	//ライブラリ情報を取得
	AlgorithmBase	*AutoAlignmentBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(AutoAlignmentBasePointer==NULL){
		return;
	}
	AlgorithmBase	*AutoPCBHoleAlignerBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	if(AutoPCBHoleAlignerBasePointer==NULL){
		return;
	}
	bool FlgDynamicClassify=false;
	AlgorithmBase	*DynamicClassifyBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(DynamicClassifyBasePointer!=NULL){
		//PropertyDynamicClassifyの画面操作
		GUIFormBase	*PropertyDClassify=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
		if(PropertyDClassify!=NULL){
			FlgDynamicClassify=true;
		}
//		return;
	}
	//個数取得
	CmdReqAutoAlignmentEnumLibs	CmdAlignEnum(pLayersBase);
	AutoAlignmentBasePointer->TransmitDirectly(&CmdAlignEnum);
	CmdReqAutoPCBHoleAlignerEnumLibs	CmdPCBHoleAlignEnum(pLayersBase);
	AutoPCBHoleAlignerBasePointer->TransmitDirectly(&CmdPCBHoleAlignEnum);
	CmdReqDynamicClassifyEnumLibs	CmdDClassifyEnum(pLayersBase);
	if(DynamicClassifyBasePointer!=NULL){
		DynamicClassifyBasePointer->TransmitDirectly(&CmdDClassifyEnum);
	}

	SetLibNumb(CmdAlignEnum.LibIDList.GetNumber()+CmdPCBHoleAlignEnum.LibIDList.GetNumber(),FlgDynamicClassify);

	SetAutoAlignmentLibNumb		(CmdAlignEnum.LibIDList.GetNumber(),AutoAlignmentBasePointer);
	SetAutoPCBHoleAlignerLibNumb(CmdPCBHoleAlignEnum.LibIDList.GetNumber(),AutoPCBHoleAlignerBasePointer);
	if(DynamicClassifyBasePointer!=NULL){
		SetDynamicClassifyLibNumb	(CmdDClassifyEnum.LibIDList.GetNumber(),DynamicClassifyBasePointer);
	}

	iCLogic				=new int[LibNumb];
	iPickupDeleteColor	=new int[LibNumb];
	iPickupAddColor		=new int[LibNumb];
	AddCLogicList		=new NPListPack<ColorLogic>[LibNumb];
	tbGerberCount		=new int[LibNumb];
	int Index=0;
	for(IntClass *LibIDPoint=CmdAlignEnum.LibIDList.GetFirst();LibIDPoint!=NULL;LibIDPoint=LibIDPoint->GetNext()){
		int	LibID=LibIDPoint->GetValue();
		//ライブラリの中身をＩＤ番号から取得
		//ライブラリの読込コードが無くても仮想関数で読込できる
		AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,*AlignLevelLib[Index]);
		AutoAlignmentLibrary		*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[Index]->GetLibrary();
		//画面表示
		ShowLibrary(Index,pAlignLib,AutoAlignmentBasePointer);
		Index++;
	}
	Index=0;
	for(IntClass *LibIDPoint=CmdPCBHoleAlignEnum.LibIDList.GetFirst();LibIDPoint!=NULL;LibIDPoint=LibIDPoint->GetNext()){
		int	LibID=LibIDPoint->GetValue();
		//ライブラリの中身をＩＤ番号から取得
		//ライブラリの読込コードが無くても仮想関数で読込できる
		AutoPCBHoleAlignerBasePointer->GetLibraryContainer()->GetLibrary(LibID,*PCBHoleLevelLib[Index]);
		AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[Index]->GetLibrary();
		//画面表示
		ShowLibrary(Index,pPCBHoleAlignLib,AutoPCBHoleAlignerBasePointer);
		Index++;
	}
	if(DynamicClassifyBasePointer!=NULL){
		Index=0;
		for(IntClass *LibIDPoint=CmdDClassifyEnum.LibIDList.GetFirst();LibIDPoint!=NULL;LibIDPoint=LibIDPoint->GetNext()){
			int	LibID=LibIDPoint->GetValue();
			//ライブラリの中身をＩＤ番号から取得
			//ライブラリの読込コードが無くても仮想関数で読込できる
			DynamicClassifyBasePointer->GetLibraryContainer()->GetLibrary(LibID,*DClassifyLevelLib[Index]);
			DynamicClassifyLibrary		*pDClassifyLib=(DynamicClassifyLibrary *)DClassifyLevelLib[Index]->GetLibrary();
			//色の初期化
			pDClassifyLib->PickupColor.ClearBase();
			//PADのライブラリの色情報を取得する→DynamicClassifyのライブラリに適用する→DynamicClassifyのGenerateをこの処理の後に行うようにする
			AutoAlignmentLibrary		*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[0]->GetLibrary();
			if(CmdAlignEnum.LibIDList.GetNumber()>0 && AlignLevelLib[0]!=NULL){
				for(ColorLogic *c=pAlignLib->PickupColor.GetFirst();c!=NULL;c=c->GetNext()){
					pDClassifyLib->PickupColor.Add(*c);
				}
			}
			//ShrinkDotとNoiseDotの設定
			pDClassifyLib->ShrinkDot=-(sbExpandForPickup[0]	->value());
			pDClassifyLib->NoiseDot	=  sbExpandForPickup[0]	->value();
			//Update
			DynamicClassifyBasePointer->GetLibraryContainer()->Update(*DClassifyLevelLib[Index]);
			//画面表示
			ShowLibrary(Index,pDClassifyLib,DynamicClassifyBasePointer);
			Index++;
		}
	}

	//マスク領域表示ボタンを押させる
	ui.tbShowMaskArea->setChecked(true);
	tbAddColorClicked(true);
}

void EditLibraryForm::ExecuteDrawEnd(FlexArea &Area)
{
	//矩形描画後の処理
	ColorLogic	*pCLogic=NULL;
	ImagePointerContainer ImageList;

	IntList PageList;
	pLayersBase->GetLocalPageFromArea(Area,PageList);
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		int	page=P->GetValue();
		DataInPage	*pdata=pLayersBase->GetPageData(page);
		pdata->GetMasterImages(ImageList);
		FlexArea	Ar=Area;
		if(pdata->ClipMoveAreaFromGlobal(Ar)==true){
			double	LocalPixelCount=Ar.GetPatternByte();
			if(LocalPixelCount>1){
				if(ui.tbEffectiveMask->isChecked()==true || ui.tbIneffectiveMask->isChecked()==true){
					GUICmdAddAutoMaskingPIArea	Cmd(pLayersBase,QString(/**/"Inspection"),QString(/**/"AutoMaskingPIImagePanel"),pdata->GetPage());
					Cmd.MaskArea=Ar;
					if(ui.tbEffectiveMask->isChecked()==true)
						Cmd.Effective	=true;
					if(ui.tbIneffectiveMask->isChecked()==true)
						Cmd.Effective	=false;
					//Cmd.LimitedLib	=DForm->Libs.SelectedList;
					Cmd.Send(NULL,pdata->GetPage(),0);
				}
				else{
					GUICmdGetColorLogic	Cmd(pLayersBase,sRoot,sName ,page);
					GUICmdAckColorLogic	Ack(pLayersBase,sRoot,sName,page);
					Cmd.Area=Ar;
					if(Cmd.Send(page,0,Ack)==true){
//						CLogic=Ack.CLogic;
						pCLogic=new ColorLogic(Ack.CLogic);
						break;
					}
				}
			}
		}
	}

	if(pCLogic==NULL){
		return;
	}

	for(int i=0;i<LibNumb;i++){
		if(tbAddColor[i]->isChecked()==true){
			QPalette P;
			if(iCLogic[i]>=9){
				//確認メッセージ
				QMessageBox MsgBox;
				MsgBox.setFont	(font1[LanguageCode]);
				MsgBox.setText	(LangSolver.GetString(EditLibraryForm_LS,LID_100)/*"色情報の表示枠には表示しきれませんが、\n正常に色情報は取得されています。"*/);
				MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_101)/*"閉じる"*/	,QMessageBox::AcceptRole);
				MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
				MsgBox.exec();
			}
			else{
				P.setColor(QPalette::Button,QColor(((ColorSphere *)pCLogic->GetFirstBase())->GetCenter()));
				if(i>=AutoAlignmentLibNumb){
					P.setColor(QPalette::WindowText,QColor(Qt::white));
				}
				tbColor[iCLogic[i]][i]->setPalette(P);
				tbColor[iCLogic[i]][i]->setText(QString::number(iCLogic[i]+1));
			}
			AddCLogicList[i].AppendList(pCLogic);
			iPickupAddColor[i]++;
			iCLogic[i]++;
		}
	}
}

void EditLibraryForm::Update(bool Enable)
{
	for(int i=0;i<LibNumb;i++){
		if(iPickupAddColor==NULL){
			return;
		}
		if(iPickupAddColor[i]>0){
			int Numb=0;
			for(ColorLogic *c=AddCLogicList[i].GetLast();Numb<iPickupAddColor[i];Numb++,c=c->GetPrev()){
				int iNumb=iCLogic[i]-Numb-1;
				if(iNumb>=0 && iNumb<9){
					if(Enable==true){
						ColorSphere *pCSphere=(ColorSphere *)c->GetFirstBase();
						QPalette P;
						P.setColor(QPalette::Button,QColor(pCSphere->GetCenter()));
						if(i>=AutoAlignmentLibNumb){
							P.setColor(QPalette::WindowText,QColor(Qt::white));
						}
						tbColor[iNumb][i]->setPalette(P);
					}
					else{
						tbColor[iNumb][i]->setPalette(ui.pushButtonFinish->palette());
					}
				}
			}
		}
	}
}

void EditLibraryForm::ExecClose()
{
	for(int phase=0;phase<pLayersBase->GetPhaseNumb();phase++){
	//矩形描画の解除
	GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,GetImagePanelName(phase,/**/"TargetImage"));
	if(TargetImage==NULL)
		return;
	DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
	TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));

	//描画完了のフックを解除
	for(int i=0;i<LibNumb;i++){
		if(tbAddColor[i]->isChecked()==true){
			if(i<AutoAlignmentLibNumb){
				//AutoAlignmentImagePanelからの描画フックを解除
				GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,/**/"AutoAlignmentImagePanel"));
				AutoAlignmentImagePanel	*AAlignImagePanel=dynamic_cast<AutoAlignmentImagePanel *>(AAlignImage);
				TargetImage->ReleaseHook(AAlignImagePanel);
			}
			else{
				//AutoPCBHoleAlignerImagePanelからの描画フックを解除
				GUIFormBase	*APCBHoleAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoPCBHoleAlignerImagePanel" ,/**/""); // TODO: phase function
				AutoPCBHoleAlignerImagePanel	*APCBHoleAlignImagePanel=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(APCBHoleAlignImage);
				TargetImage->ReleaseHook(APCBHoleAlignImagePanel);
			}
		}
		if(tbOutlineI[i]->isChecked()==true || tbOutlineT[i]->isChecked()==true || tbOutlineO[i]->isChecked()==true){
			//DynamicClassifyImagePanelからの描画フックを解除
			GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/""); // TODO: phase function
			DynamicClassifyImagePanel	*DClassifyImagePanel=dynamic_cast<DynamicClassifyImagePanel *>(DClassifyImage);
			TargetImage->ReleaseHook(DClassifyImagePanel);
		}
///		TargetImage->ReleaseHook(this);
	}
	if(ui.tbShowMaskArea->isChecked()==true){
		//AutoAlignmentImagePanelからの描画フックを解除
		GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,/**/"AutoAlignmentImagePanel"));
		AutoAlignmentImagePanel	*AAlignImagePanel=dynamic_cast<AutoAlignmentImagePanel *>(AAlignImage);
		TargetImage->ReleaseHook(AAlignImagePanel);
	}
	if(ui.tbEffectiveMask->isChecked()==true || ui.tbIneffectiveMask->isChecked()==true){
		//AutoMaskingPIImagePanelからの描画フックを解除
		GUIFormBase	*AMaskImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoMaskingPIImagePanel" ,GetImagePanelName(phase,/**/"AutoMaskingPIImagePanel"));
		AutoMaskingPIImagePanel	*AMaskImagePanel=dynamic_cast<AutoMaskingPIImagePanel *>(AMaskImage);
		TargetImage->ReleaseHook(AMaskImagePanel);
	}

	//TargetImagePanelにの表示を検査画像に直す
	TargetImagePanel->ChangeDisplayType(DisplayImage::__Target);
	}
	DeleteFormComponent();
}

void EditLibraryForm::SetHoleGerberButton(int LibID,int Index)
{
	for(int i=AutoAlignmentLibNumb;i<LibNumb;i++){
		if(PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibID()==LibID){
			if(Index<4){
				tbGerber[Index][i]->setVisible(true);
			}
			tbGerberCount[i]++;
			return;
		}
	}
}

void EditLibraryForm::rbSelectRectangleToggled(bool checked)
{
	if(checked==true){
		//TargetImagePanelにマスター画像を表示させる
		GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/""); // TODO?: phase function
		if(TargetImage==NULL){
			return;
		}
		DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
		//矩形描画に設定
		TargetImagePanel->SetModeByOthers(mtFrameDraw::fdRectangle,QColor(Qt::red));
	}
}

void EditLibraryForm::rbSelectPolygonToggled(bool checked)
{
	if(checked==true){
		//TargetImagePanelにマスター画像を表示させる
		GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/""); // TODO?: phase function
		if(TargetImage==NULL){
			return;
		}
		DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
		//多角形描画に設定
		TargetImagePanel->SetModeByOthers(mtFrameDraw::fdPoly,QColor(Qt::red));
	}
}

void EditLibraryForm::verticalScrollBarValueChanged(int Value)
{
	for(int i=0;i<LibNumb;i++){
		fmLibContainer[i]->setGeometry(QRect(10, 120*i+10-Value, 531, 111));
	}
}

void EditLibraryForm::tbAddColorClicked(bool checked)
{
	for(int phase=0;phase<pLayersBase->GetPhaseNumb();phase++){
		pLayersBase->TF_SetCurrentScanPhaseNumber(phase);
		GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,GetImagePanelName(phase,/**/"TargetImage"));
	if(TargetImage==NULL)
		return;
	DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);

	//描画完了をフック
	TargetImagePanel->SetHookInDrawEnd(this,EditLibraryFormFunctionDrawEnd);

	int Index=ActiveButtonIndex;
	bool IsAAlignImagePanelHooked=false;
	bool IsAPCBHoleAlignImagePanelHooked=false;
	bool IsAMaskImagePanelHooked=false;
	bool IsDClassifyImagePanelHooked=false;
	int SumNumb=LibNumb+3;		//LibNumb,マスク領域表示,手動有効マスク,手動無効マスク
	for(int i=0;i<SumNumb+LibNumb*3;i++){	//Outline-I,Outline-T,Outline-O
		if(ActiveButtonIndex==i){
			if(checked==false){
				//矩形描画を解除
				TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));
				//ボタンが押し上げられた
				if(i<AutoAlignmentLibNumb || i==LibNumb){
					//AutoAlignmentImagePanelからの描画フックを解除
					GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,/**/"AutoAlignmentImagePanel"));
					AutoAlignmentImagePanel	*AAlignImagePanel=dynamic_cast<AutoAlignmentImagePanel *>(AAlignImage);
					TargetImage->ReleaseHook(AAlignImagePanel);
				}
				else if(i<LibNumb){
					//AutoPCBHoleAlignerImagePanelからの描画フックを解除
					GUIFormBase	*APCBHoleAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoPCBHoleAlignerImagePanel" ,/**/""); // TODO? : phase function
					AutoPCBHoleAlignerImagePanel	*APCBHoleAlignImagePanel=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(APCBHoleAlignImage);
					TargetImage->ReleaseHook(APCBHoleAlignImagePanel);
				}
				else if(i<SumNumb){
					//AutoMaskingPIImagePanelからの描画フックを解除
					GUIFormBase	*AMaskImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoMaskingPIImagePanel" ,GetImagePanelName(phase,/**/"AutoMaskingPIImagePanel"));
					AutoMaskingPIImagePanel	*AMaskImagePanel=dynamic_cast<AutoMaskingPIImagePanel *>(AMaskImage);
					TargetImage->ReleaseHook(AMaskImagePanel);
				}
				else{
					//DynamicClassifyImagePanelからの描画フックを解除
					GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/""); // TODO? : phase function
					DynamicClassifyImagePanel	*DClassifyImagePanel=dynamic_cast<DynamicClassifyImagePanel *>(DClassifyImage);
					TargetImage->ReleaseHook(DClassifyImagePanel);
				}
				Index=-1;
			}
			else{
				//他のボタンが押し下げられた
				if(i<AutoAlignmentLibNumb || i==LibNumb){
					//Hookされていない場合のみReleaseする
					if(IsAAlignImagePanelHooked==false){
						//AutoAlignmentImagePanelからの描画フックを解除
						GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,"AutoAlignmentImagePanel"));
						AutoAlignmentImagePanel	*AAlignImagePanel=dynamic_cast<AutoAlignmentImagePanel *>(AAlignImage);
						TargetImage->ReleaseHook(AAlignImagePanel);
					}
				}
				else if(i<LibNumb){
					//Hookされていない場合のみReleaseする
					if(IsAPCBHoleAlignImagePanelHooked==false){
						//AutoPCBHoleAlignerImagePanelからの描画フックを解除
						GUIFormBase	*APCBHoleAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoPCBHoleAlignerImagePanel" ,/**/"");
						AutoPCBHoleAlignerImagePanel	*APCBHoleAlignImagePanel=dynamic_cast<AutoPCBHoleAlignerImagePanel *>(APCBHoleAlignImage);
						TargetImage->ReleaseHook(APCBHoleAlignImagePanel);
					}
				}
				else if(i<SumNumb){
					//Hookされていない場合のみReleaseする
					if(IsAMaskImagePanelHooked==false){
						//AutoMaskingPIImagePanelからの描画フックを解除
						GUIFormBase	*AMaskImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoMaskingPIImagePanel" ,GetImagePanelName(phase,/**/"AutoMaskingPIImagePanel"));
						AutoMaskingPIImagePanel	*AMaskImagePanel=dynamic_cast<AutoMaskingPIImagePanel *>(AMaskImage);
						TargetImage->ReleaseHook(AMaskImagePanel);
					}
				}
				else{
					//Hookされていない場合のみReleaseする
					if(IsDClassifyImagePanelHooked==false){
						//DynamicClassifyImagePanelからの描画フックを解除
						GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
						DynamicClassifyImagePanel	*DClassifyImagePanel=dynamic_cast<DynamicClassifyImagePanel *>(DClassifyImage);
						TargetImage->ReleaseHook(DClassifyImagePanel);
					}
				}

				if(i<LibNumb){
					tbAddColor[i]->setChecked(false);				//色追加ボタン
				}
				else if(i<SumNumb){
					if(i==LibNumb){
						ui.tbShowMaskArea->setChecked(false);		//マスク領域表示ボタン
					}
					else if(i==LibNumb+1){
						ui.tbEffectiveMask->setChecked(false);		//手動有効マスクボタン
					}
					else if(i==LibNumb+2){
						ui.tbIneffectiveMask->setChecked(false);	//手動無効マスクボタン
					}
				}
				else{
					int MMM=(i-SumNumb)/3;
					int NNN=(i-SumNumb)%3;
					if(NNN==0){
						tbOutlineI[MMM]->setChecked(false);			//Outline-Iボタン
					}
					else if(NNN==1){
						tbOutlineT[MMM]->setChecked(false);			//Outline-Tボタン
					}
					else if(NNN==2){
						tbOutlineO[MMM]->setChecked(false);			//Outline-Oボタン
					}
				}
			}
		}
		else if(i<LibNumb){
			if(tbAddColor[i]->isChecked()==true){
				if(ui.rbSelectRectangle->isChecked()==true){
					//矩形描画に設定
					TargetImagePanel->SetModeByOthers(mtFrameDraw::fdRectangle,QColor(Qt::red));
				}
				else{
					//多角形描画に設定
					TargetImagePanel->SetModeByOthers(mtFrameDraw::fdPoly,QColor(Qt::red));
				}
				//ボタンが押し下げられた
				if(i<AutoAlignmentLibNumb){
					//PropertyAutoAlignmentFormの画面操作
					GUIFormBase	*PropertyAAlign=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
					CmdSetAutoAlignmentShowingState	CmdSetAAlignShowState(pLayersBase);
///					CmdSetAAlignShowState.ModeShowingSheet			=CmdSetAutoAlignmentShowingState::_Area;
					CmdSetAAlignShowState.ModeShowingSheet			=CmdSetAutoAlignmentShowingState::_PickupAreaTest;
					CmdSetAAlignShowState.ModeShowingMono			=false;
					CmdSetAAlignShowState.ModeShowingPicoTransArea	=false;
					CmdSetAAlignShowState.ModeShowingPicoPickupArea	=true;
					CmdSetAAlignShowState.ModeShowingPicoOtherArea	=false;
					CmdSetAAlignShowState.ModeShowingPicoFringeArea	=false;
					CmdSetAAlignShowState.ModeShowingPicoInfo		=false;
					CmdSetAAlignShowState.ShowingLibIDs.Add(AlignLevelLib[i]->GetLibID(),false);
					PropertyAAlign->TransmitDirectly(&CmdSetAAlignShowState);
					//AutoAlignmentImagePanelから描画をフック
					GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,"AutoAlignmentImagePanel"));
					DisplayImage	*AAlignImagePanel=dynamic_cast<DisplayImage *>(AAlignImage);
					AAlignImagePanel->RequireHooks(TargetImagePanel);
					IsAAlignImagePanelHooked=true;
				}
				else{
					//PropertyAutoPCBHoleAlignerFormの画面操作
					GUIFormBase	*PropertyAPCBHoleAlign=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoPCBHoleAligner" ,/**/"");
					CmdSetAutoPCBHoleAlignerShowingState	CmdSetAPCBHoleAlignShowState(pLayersBase);
					CmdSetAPCBHoleAlignShowState.ModeShowingHole	=true;
					CmdSetAPCBHoleAlignShowState.ModeShowingFringe	=false;
					CmdSetAPCBHoleAlignShowState.ShowingLibIDs.Add(PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibID());
					PropertyAPCBHoleAlign->TransmitDirectly(&CmdSetAPCBHoleAlignShowState);
					//AutoPCBHoleAlignerImagePanelから描画をフック
					GUIFormBase	*APCBHoleAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoPCBHoleAlignerImagePanel" ,/**/"");
					DisplayImage	*APCBHoleAlignImagePanel=dynamic_cast<DisplayImage *>(APCBHoleAlignImage);
					APCBHoleAlignImagePanel->RequireHooks(TargetImagePanel);
					IsAPCBHoleAlignImagePanelHooked=true;
				}
				Index=i;
			}
		}
		else if(i>=SumNumb){
			//Outlineボタン
			int MMM=(i-SumNumb)/3;
			int NNN=(i-SumNumb)%3;
			if(NNN==0){
				if(tbOutlineI[MMM]->isChecked()==true){		//Outline-Iボタン
					//矩形描画を解除
					TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));
					//ボタンが押し下げられた
					//PropertyDynamicClassifyの画面操作
					GUIFormBase	*PropertyDClassify=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
					CmdSetDynamicClassifyShowingState	CmdSetDClassifyShowState(pLayersBase);
					CmdSetDClassifyShowState.ModeCoreArea		=false;
					CmdSetDClassifyShowState.ModeMaxZone		=false;
					CmdSetDClassifyShowState.ModeBareArea		=false;
					CmdSetDClassifyShowState.ModeInsideArea		=false;
					CmdSetDClassifyShowState.ModeOutlineIArea	=true;
					CmdSetDClassifyShowState.ModeOutlineTArea	=false;
					CmdSetDClassifyShowState.ModeOutlineOArea	=false;
					PropertyDClassify->TransmitDirectly(&CmdSetDClassifyShowState);
					//DynamicClassifyImagePanelから描画をフック
					GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
					DisplayImage	*DClassifyImagePanel=dynamic_cast<DisplayImage *>(DClassifyImage);
					DClassifyImagePanel->RequireHooks(TargetImagePanel);
					Index=i;
					IsDClassifyImagePanelHooked=true;
					Index=i;
				}
			}
			else if(NNN==1){
				if(tbOutlineT[MMM]->isChecked()==true){		//Outline-Tボタン
					//矩形描画を解除
					TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));
					//ボタンが押し下げられた
					//PropertyDynamicClassifyの画面操作
					GUIFormBase	*PropertyDClassify=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
					CmdSetDynamicClassifyShowingState	CmdSetDClassifyShowState(pLayersBase);
					CmdSetDClassifyShowState.ModeCoreArea		=false;
					CmdSetDClassifyShowState.ModeMaxZone		=false;
					CmdSetDClassifyShowState.ModeBareArea		=false;
					CmdSetDClassifyShowState.ModeInsideArea		=false;
					CmdSetDClassifyShowState.ModeOutlineIArea	=false;
					CmdSetDClassifyShowState.ModeOutlineTArea	=true;
					CmdSetDClassifyShowState.ModeOutlineOArea	=false;
					PropertyDClassify->TransmitDirectly(&CmdSetDClassifyShowState);
					//DynamicClassifyImagePanelから描画をフック
					GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
					DisplayImage	*DClassifyImagePanel=dynamic_cast<DisplayImage *>(DClassifyImage);
					DClassifyImagePanel->RequireHooks(TargetImagePanel);
					Index=i;
					IsDClassifyImagePanelHooked=true;
					Index=i;
				}
			}
			else if(NNN==2){
				if(tbOutlineO[MMM]->isChecked()==true){		//Outline-Oボタン
					//矩形描画を解除
					TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));
					//ボタンが押し下げられた
					//PropertyDynamicClassifyの画面操作
					GUIFormBase	*PropertyDClassify=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
					CmdSetDynamicClassifyShowingState	CmdSetDClassifyShowState(pLayersBase);
					CmdSetDClassifyShowState.ModeCoreArea		=false;
					CmdSetDClassifyShowState.ModeMaxZone		=false;
					CmdSetDClassifyShowState.ModeBareArea		=false;
					CmdSetDClassifyShowState.ModeInsideArea		=false;
					CmdSetDClassifyShowState.ModeOutlineIArea	=false;
					CmdSetDClassifyShowState.ModeOutlineTArea	=false;
					CmdSetDClassifyShowState.ModeOutlineOArea	=true;
					PropertyDClassify->TransmitDirectly(&CmdSetDClassifyShowState);
					//DynamicClassifyImagePanelから描画をフック
					GUIFormBase	*DClassifyImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DynamicClassifyImagePanel" ,/**/"");
					DisplayImage	*DClassifyImagePanel=dynamic_cast<DisplayImage *>(DClassifyImage);
					DClassifyImagePanel->RequireHooks(TargetImagePanel);
					Index=i;
					IsDClassifyImagePanelHooked=true;
					Index=i;
				}
			}
		}
	}
	//マスク領域表示ボタン
	if(ui.tbShowMaskArea->isChecked()==true){
		//矩形描画を解除
		TargetImagePanel->SetModeByOthers(mtFrameDraw::fdNone,QColor(Qt::red));
		//ボタンが押し下げられた
		//PropertyAutoAlignmentFormの画面操作
		GUIFormBase	*PropertyAAlign=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
		CmdSetAutoAlignmentShowingState	CmdSetAAlignShowState(pLayersBase);
		CmdSetAAlignShowState.ModeShowingSheet			=CmdSetAutoAlignmentShowingState::_Area;
		CmdSetAAlignShowState.ModeShowingMono			=false;
		CmdSetAAlignShowState.ModeShowingPicoTransArea	=false;
		CmdSetAAlignShowState.ModeShowingPicoPickupArea	=false;
		CmdSetAAlignShowState.ModeShowingPicoOtherArea	=false;
		CmdSetAAlignShowState.ModeShowingPicoFringeArea	=false;
		CmdSetAAlignShowState.ModeShowingPicoInfo		=false;
		PropertyAAlign->TransmitDirectly(&CmdSetAAlignShowState);
		//AutoAlignmentImagePanelから描画をフック
		GUIFormBase	*AAlignImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoAlignmentImagePanel" ,GetImagePanelName(phase,"AutoAlignmentImagePanel"));
		DisplayImage	*AAlignImagePanel=dynamic_cast<DisplayImage *>(AAlignImage);
		AAlignImagePanel->RequireHooks(TargetImagePanel);
		Index=LibNumb;
		IsAMaskImagePanelHooked=true;
	}
	//手動有効マスクボタン
	else if(ui.tbEffectiveMask->isChecked()==true || ui.tbIneffectiveMask->isChecked()==true){
		if(ui.rbSelectRectangle->isChecked()==true){
			//矩形描画に設定
			TargetImagePanel->SetModeByOthers(mtFrameDraw::fdRectangle,QColor(Qt::red));
		}
		else{
			//多角形描画に設定
			TargetImagePanel->SetModeByOthers(mtFrameDraw::fdPoly,QColor(Qt::red));
		}
		//ボタンが押し下げられた
		//PropertyAutoMaskingPIFormの画面操作
		GUIFormBase	*PropertyAMask=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoMaskingPIForm" ,/**/"");
		CmdSetAutoMaskingPIShowingState	CmdSetAMaskShowState(pLayersBase);
		if(ui.tbEffectiveMask->isChecked()==true){
			CmdSetAMaskShowState.ModeShowingButton=CmdSetAutoMaskingPIShowingState::_EffectiveMask;
			Index=LibNumb+1;
		}
		if(ui.tbIneffectiveMask->isChecked()==true){
			CmdSetAMaskShowState.ModeShowingButton=CmdSetAutoMaskingPIShowingState::_IneffectiveMask;
			Index=LibNumb+2;
		}
		PropertyAMask->TransmitDirectly(&CmdSetAMaskShowState);
		//AutoMaskingPIImagePanelから描画をフック
		GUIFormBase	*AMaskImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"AutoMaskingPIImagePanel" ,GetImagePanelName(phase,/**/"AutoMaskingPIImagePanel"));
		DisplayImage	*AMaskImagePanel=dynamic_cast<DisplayImage *>(AMaskImage);
		AMaskImagePanel->RequireHooks(TargetImagePanel);
		IsAMaskImagePanelHooked=true;
	}
	if((pLayersBase->GetPhaseNumb()>1 && phase==1) || (pLayersBase->GetPhaseNumb()==1))
			ActiveButtonIndex = Index;
	//再描画
	TargetImagePanel->repaint();
	}
	pLayersBase->TF_SetCurrentScanPhaseNumber(0); // phase function
}

void EditLibraryForm::tbColorClicked(bool checked)
{
	for(int i=0;i<LibNumb;i++){
		for(int j=0;j<9;j++){
			if(tbColor[j][i]->isChecked()==true){
				if(j<iCLogic[i]){
					//確認メッセージ
					QMessageBox MsgBox;
					MsgBox.setFont	(font1[LanguageCode]);
					MsgBox.setText	(LangSolver.GetString(EditLibraryForm_LS,LID_6)/*"選択した色情報をクリアしますか？"*/);
					MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_7)/*"はい"*/	,QMessageBox::AcceptRole);
					MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_8)/*"キャンセル"*/		,QMessageBox::RejectRole);
					MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
					int Ret=MsgBox.exec();

					//色クリア
					if(Ret==QMessageBox::AcceptRole){
						QPalette P;
						ColorLogic *CLogic;
						if(i<AutoAlignmentLibNumb){
							AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
							CLogic=&(pAlignLib->PickupColor);
						}
						else{
							AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibrary();
							CLogic=&(pPCBHoleAlignLib->PickupHoleColor);
							P.setColor(QPalette::WindowText,QColor(Qt::white));
						}
						for(int k=j;k<CLogic->GetBaseCount() && k<9;k++){
							ColorSphere *c;
							if((c=(ColorSphere *)CLogic->GetBase(k+1))!=NULL){
								QPalette P;
								P.setColor(QPalette::Button,QColor(c->GetCenter()));
								tbColor[k][i]->setPalette(P);
							}
							else{
								if(iPickupAddColor[i]==0){
									tbColor[k][i]->setPalette(ui.pushButtonFinish->palette());
									tbColor[k][i]->setText(/**/"");
								}
								else{
									int Index;
									if((Index=CLogic->GetBaseCount()+iPickupAddColor[i]-1)<9){
										tbColor[Index][i]->setPalette(ui.pushButtonFinish->palette());
										tbColor[Index][i]->setText(/**/"");
									}
								}
							}
						}
						ColorSpace	*c=CLogic->GetBase(j);
						if(c!=NULL){
							CLogic->RemoveBase(c);
							delete c;
						}
						else{
							if(iPickupAddColor[i]>0){
								int Index=0;
								for(ColorLogic *c=AddCLogicList[i].GetFirst();c!=NULL;c=c->GetNext(),Index++){
									if(j==CLogic->GetBaseCount()+Index){
										AddCLogicList[i].RemoveList(c);
										delete c;
										break;
									}
								}
								if((Index=CLogic->GetBaseCount()+iPickupAddColor[i]-1)<9){
									tbColor[Index][i]->setPalette(ui.pushButtonFinish->palette());
									tbColor[Index][i]->setText(/**/"");
								}
								iPickupAddColor[i]--;
							}
						}
						iCLogic[i]--;
					}
				}
				tbColor[j][i]->setChecked(false);
				return;
			}
		}
	}
}

void EditLibraryForm::tbGerberClicked(bool checked)
{
	//ガーバー領域の削除
	for(int i=0;i<LibNumb;i++){
		for(int j=0;j<4;j++){
			if(tbGerber[j][i]->isChecked()==true){
				//確認メッセージ
				QMessageBox MsgBox;
				MsgBox.setFont	(font1[LanguageCode]);
				MsgBox.setText	(LangSolver.GetString(EditLibraryForm_LS,LID_9)/*"このガーバー領域を削除しますか？"*/);
				MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_10)/*"はい"*/	,QMessageBox::AcceptRole);
				MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_11)/*"キャンセル"*/	,QMessageBox::RejectRole);
				MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
				int Ret=MsgBox.exec();

				//削除
				if(Ret==QMessageBox::AcceptRole){
					//AlgorithmBaseポインタを取得
					if(i<AutoAlignmentLibNumb){
						AlgorithmBase	*BasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
					}
					else{
						AlgorithmBase	*BasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
						if(BasePointer!=NULL){
							CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm	CmdPCBHoleAlignDelIndex(pLayersBase);
							CmdPCBHoleAlignDelIndex.LibID		=PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibID();
							CmdPCBHoleAlignDelIndex.DeleteIndex	=j;
							BasePointer->TransmitDirectly(&CmdPCBHoleAlignDelIndex);
						}
					}
					tbGerber[j][i]->setVisible(false);
					tbGerberCount[i]--;
				}
				tbGerber[j][i]->setChecked(false);
				return;
			}
		}
	}
}

void EditLibraryForm::tbClearColorClicked(bool checked)
{
	for(int i=0;i<LibNumb;i++){
		if(tbClearColor[i]->isChecked()==true){
			//確認メッセージ
			QMessageBox MsgBox;
			MsgBox.setFont	(font1[LanguageCode]);
			MsgBox.setText	(LangSolver.GetString(EditLibraryForm_LS,LID_102)/*"登録されている色情報をクリアします。"*/);
			MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_103)/*"末尾の色をクリア"*/	,QMessageBox::AcceptRole);
			MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_104)/*"全ての色をクリア"*/	,QMessageBox::RejectRole);
			MsgBox.addButton(LangSolver.GetString(EditLibraryForm_LS,LID_105)/*"キャンセル"*/		,QMessageBox::DestructiveRole);
//			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
			MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
			int Ret=MsgBox.exec();

			//色クリア
			if(Ret==QMessageBox::AcceptRole){	//末尾の色をクリア
				ColorLogic *CLogic;
				if(i<AutoAlignmentLibNumb){
					AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
					CLogic=&(pAlignLib->PickupColor);
				}
				else{
					AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibrary();
					CLogic=&(pPCBHoleAlignLib->PickupHoleColor);
				}
				int Numb=iCLogic[i]-1;
				if(Numb>=0){
					if(Numb<9){
						tbColor[Numb][i]->setPalette(ui.pushButtonFinish->palette());
						tbColor[Numb][i]->setText(/**/"");
					}
					if(iPickupAddColor[i]>0){
						iPickupAddColor[i]--;
						ColorLogic *c=AddCLogicList[i].GetLast();
						if(c!=NULL){
							AddCLogicList[i].RemoveList(c);
							delete c;
						}
					}
					else{
						ColorSpace	*c=CLogic->GetBase(Numb);
						if(c!=NULL){
							CLogic->RemoveBase(c);
							delete c;
						}
					}
					iCLogic[i]--;
				}
			}
			else if(Ret==QMessageBox::RejectRole){	//全ての色をクリア
				ColorLogic *CLogic;
				if(i<AutoAlignmentLibNumb){
					AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
					CLogic=&(pAlignLib->PickupColor);
				}
				else{
					AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibrary();
					CLogic=&(pPCBHoleAlignLib->PickupHoleColor);
				}
				for(int Numb=0;Numb<iCLogic[i] && Numb<9;Numb++){
					tbColor[Numb][i]->setPalette(ui.pushButtonFinish->palette());
					tbColor[Numb][i]->setText(/**/"");
				}
				AddCLogicList[i].RemoveAll();
				iPickupAddColor[i]=0;

				int Numb;
				for(Numb=CLogic->GetBaseCount()-1;Numb>=0;Numb--){
					ColorSpace	*c=CLogic->GetBase(Numb);
					if(c!=NULL){
						CLogic->RemoveBase(c);
						delete c;
					}
				}
				iCLogic[i]=0;
			}
			tbClearColor[i]->setChecked(false);
		}
	}
}

void EditLibraryForm::sbNoiseShrinkValueChanged(int Value)
{
	for(int i=0;i<LibNumb;i++){
		if(i<AutoAlignmentLibNumb){
			AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
			pAlignLib->NoiseShrink=sbNoiseShrink[i]->value();
		}
	}
}

void EditLibraryForm::sbExpandForPickupValueChanged(int Value)
{
	for(int i=0;i<LibNumb;i++){
		if(i<AutoAlignmentLibNumb){
			AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
			pAlignLib->ExpandForPickup=sbExpandForPickup[i]->value();
		}
		else{
			AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibrary();
			pPCBHoleAlignLib->ExpandForPickup=sbExpandForPickup[i]->value();
		}
	}
}

void EditLibraryForm::pushButtonUpdateClicked()
{
	//ライブラリ情報を取得
	AlgorithmBase	*AutoAlignmentBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(AutoAlignmentBasePointer==NULL){
		return;
	}
	AlgorithmBase	*AutoPCBHoleAlignerBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	if(AutoPCBHoleAlignerBasePointer==NULL){
		return;
	}
	AlgorithmBase	*DynamicClassifyBasePointer=pLayersBase->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(DynamicClassifyBasePointer==NULL){
//		return;
	}

	pLayersBase->ShowProcessingForm("Update library");
	pLayersBase->AddMaxProcessing(0,0);

	//ライブラリの中身をデータベースに保存
	//ライブラリの上書保存コードが無くても仮想関数で上書保存できる
	for(int i=0;i<LibNumb;i++){
		if(i<AutoAlignmentLibNumb){
			AutoAlignmentLibrary	*pAlignLib=(AutoAlignmentLibrary *)AlignLevelLib[i]->GetLibrary();
			int Numb=pAlignLib->PickupColor.GetBaseCount()-1;
			int j=iCLogic[i]-1;
			for(ColorLogic *c=AddCLogicList[i].GetFirst();c!=NULL;c=c->GetNext(),j--){
				//画面表示の設定
				if(j<9){
					QPalette P;
					P.setColor(QPalette::Button,QColor(((ColorSphere *)c->GetFirstBase())->GetCenter()));
					tbColor[j][i]->setPalette(P);
				}
				pAlignLib->PickupColor.Add(*c);
			}
			AutoAlignmentBasePointer->GetLibraryContainer()->Update(*AlignLevelLib[i]);

			//DynamicClassifyライブラリ
			if(i<DynamicClassifyLibNumb){
				//色登録
				DynamicClassifyLibrary		*pDClassifyLib=(DynamicClassifyLibrary *)DClassifyLevelLib[i]->GetLibrary();
				Numb=pDClassifyLib->PickupColor.GetBaseCount()-1;
				for(int k=0;k<iPickupDeleteColor[i];k++,Numb--){
					ColorSpace	*c=pDClassifyLib->PickupColor.GetBase(Numb);
					if(c!=NULL){
						pDClassifyLib->PickupColor.RemoveBase(c);
						delete c;
					}
				}
				j=iCLogic[i]-1;
				for(ColorLogic *c=AddCLogicList[i].GetFirst();c!=NULL;c=c->GetNext(),j--){
					pDClassifyLib->PickupColor.Add(*c);
				}
				//ShrinkDotとNoiseDotの設定
				pDClassifyLib->ShrinkDot	=-(sbExpandForPickup[i]->value());
				pDClassifyLib->NoiseDot	=sbExpandForPickup[i]->value();
				//Update
				DynamicClassifyBasePointer->GetLibraryContainer()->Update(*DClassifyLevelLib[i]);
			}

			//クリア
			iPickupAddColor[i]		=0;
			iPickupDeleteColor[i]	=0;
			AddCLogicList[i].RemoveAll();
		}
		else{
			AutoPCBHoleAlignerLibrary	*pPCBHoleAlignLib=(AutoPCBHoleAlignerLibrary *)PCBHoleLevelLib[i-AutoAlignmentLibNumb]->GetLibrary();
			int Numb=pPCBHoleAlignLib->PickupHoleColor.GetBaseCount()-1;
			int j=iCLogic[i]-1;
			for(ColorLogic *c=AddCLogicList[i].GetFirst();c!=NULL;c=c->GetNext(),j--){
				//画面表示の設定
				if(j<9){
					QPalette P;
					P.setColor(QPalette::Button,QColor(((ColorSphere *)c->GetFirstBase())->GetCenter()));
					if(i>=AutoAlignmentLibNumb){
						P.setColor(QPalette::WindowText,QColor(Qt::white));
					}
					tbColor[j][i]->setPalette(P);
				}
				pPCBHoleAlignLib->PickupHoleColor.Add(*c);
			}
			AutoPCBHoleAlignerBasePointer->GetLibraryContainer()->Update(*PCBHoleLevelLib[i-AutoAlignmentLibNumb]);
			iPickupAddColor[i]		=0;
			iPickupDeleteColor[i]	=0;
			AddCLogicList[i].RemoveAll();

			//Gerberボタン表示の設定
			for(int k=0;k<4;k++){
				if(k<tbGerberCount[i]){
					tbGerber[k][i]->setVisible(true);
				}
				else{
					tbGerber[k][i]->setVisible(false);
				}
			}
		}
	}

	//PropertyAutoAlignmentFormの画面操作
	GUIFormBase	*PropertyAAlign=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
	CmdSetAutoAlignmentShowingState	CmdSetAAlignShowState(pLayersBase);
	CmdSetAAlignShowState.ModeShowingSheet			=CmdSetAutoAlignmentShowingState::_Default;
	CmdSetAAlignShowState.ModeShowingMono			=false;
	CmdSetAAlignShowState.ModeShowingPicoTransArea	=false;
	CmdSetAAlignShowState.ModeShowingPicoPickupArea	=false;
	CmdSetAAlignShowState.ModeShowingPicoOtherArea	=false;
	CmdSetAAlignShowState.ModeShowingPicoFringeArea	=false;
	CmdSetAAlignShowState.ModeShowingPicoInfo		=false;
	CmdSetAAlignShowState.ModeClickPickupAreaTest	=true;
	PropertyAAlign->TransmitDirectly(&CmdSetAAlignShowState);
	//PropertyAutoMaskingPIFormのテーブル表示
	GUIFormBase	*PropertyAMask=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyAutoMaskingPIForm" ,/**/"");
	CmdSetAutoMaskingPIShowingState	CmdSetAMaskShowState(pLayersBase);
	if(ui.tbShowMaskArea->isChecked())
		CmdSetAMaskShowState.ModeShowingButton=CmdSetAutoMaskingPIShowingState::_AutoMask;
	else if(ui.tbEffectiveMask->isChecked())
		CmdSetAMaskShowState.ModeShowingButton=CmdSetAutoMaskingPIShowingState::_EffectiveMask;
	else if(ui.tbIneffectiveMask->isChecked())
		CmdSetAMaskShowState.ModeShowingButton=CmdSetAutoMaskingPIShowingState::_IneffectiveMask;
	PropertyAMask->TransmitDirectly(&CmdSetAMaskShowState);

	CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit	CmdPCBHoleAlignExecInitAfterEdit(pLayersBase);
	AutoPCBHoleAlignerBasePointer->TransmitDirectly(&CmdPCBHoleAlignExecInitAfterEdit);

	////ExecuteInitialAfterEditを発行して反映
	//NPListPack<GUICmdPacketDim>	GUICmdDim;
	//GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
	//GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
	//for(int page=0;page<pLayersBase->GetPageNumb();page++){
	//	CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (pLayersBase,sRoot,sName,page);
	//	CmdReq [page]->CurrentMasterCounter=2;
	//	CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(pLayersBase,sRoot,sName,page);
	//	GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
	//}
	//pLayersBase->PacketSender(GUICmdDim);
	//pLayersBase->CloseProcessingForm();
/*
	//GUICmdPushGenerateDynamicClassifysを発行
	for(int page=0;page<pLayersBase->GetPageNumb();page++){
		GUICmdPushGenerateDynamicClassifys	Cmd(pLayersBase,sRoot,sName,page);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,page,0);
	}
*/
	//PropertyDynamicClassifyFormにTransmitDirectlyしてGenerateしてやる
	GUIFormBase	*PropertyDCForm=NULL;
	PropertyDCForm=pLayersBase->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
	if(PropertyDCForm!=NULL){
		CmdDynamicClassifyGenerate	CmdDCGenerate(pLayersBase);
		PropertyDCForm->TransmitDirectly(&CmdDCGenerate);
	}

	//ExecuteStartByInspectionを実行してstateを設定してやる -> 後のExecuteAlignmentの為に
///	pLayersBase->ExecuteStartByInspection(pLayersBase->GetEntryPoint());

	//再描画
	GUIFormBase	*TargetImage=pLayersBase->FindByName(/**/"Inspection" ,/**/"DisplayTargetImage" ,/**/"");
	if(TargetImage==NULL){
		return;
	}
	DisplayImage	*TargetImagePanel=dynamic_cast<DisplayImage *>(TargetImage);
	TargetImagePanel->repaint();
}

void EditLibraryForm::pushButtonStartNextClicked()
{
	ExecClose();
	reject();
}

void EditLibraryForm::pushButtonFinishClicked()
{
//	//確認メッセージを表示
//	QMessageBox MsgBox;
//	MsgBox.setFont	(font1[LanguageCode]);
//	MsgBox.setText	("学習を終了しますか？\n学習を続ける場合はキャンセルボタンを押して基板を読み込んでください。");
//	MsgBox.addButton("学習を終了"	,QMessageBox::AcceptRole);
//	MsgBox.addButton("キャンセル"	,QMessageBox::RejectRole);
////	MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint);	//常に前面に表示
//	MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
//	int Ret=MsgBox.exec();
//
//	//学習を終了
//	if(Ret==QMessageBox::AcceptRole){
//		ExecClose();
//		accept();
//	}

//////分類確定//////
	if(pLayersBase->GetPhaseNumb()>1)
	 pLayersBase->TF_SetCurrentScanPhaseNumber(0); // phase function
	//ExecuteInitialAfterEditを発行して反映
	pLayersBase->ShowProcessingForm ("Finish edit");
	NPListPack<GUICmdPacketDim>	GUICmdDim;
/*
	GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
	GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
	for(int page=0;page<pLayersBase->GetPageNumb();page++){
		CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (pLayersBase,sRoot,sName,page);
		CmdReq [page]->CurrentMasterCounter=2;
		CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(pLayersBase,sRoot,sName,page);
		GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
	}
*/
	GUICmdReqExecuteInitialAfterEdit	*CmdReq;
	GUICmdSendExecuteInitialAfterEdit	*CmdSend;
	CmdReq =new GUICmdReqExecuteInitialAfterEdit (pLayersBase,sRoot,sName,0);
	CmdReq ->CurrentMasterCounter=2;
	CmdSend=new GUICmdSendExecuteInitialAfterEdit(pLayersBase,sRoot,sName,0);
	GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq,CmdSend,0,0));
	pLayersBase->PacketSender(GUICmdDim);
	pLayersBase->CloseProcessingForm();

//////分類終了//////
	ExecClose();
	reject();
}

void EditLibraryForm::DeleteFormComponent()
{
	if(fmLibContainer!=NULL){
		for(int i=0;i<LibNumb;i++){
//			disconnect(tbAddColor[i]	,SIGNAL(clicked(bool)),this,SLOT(tbAddColorClicked(bool)));
//			disconnect(tbClearColor[i]	,SIGNAL(clicked(bool)),this,SLOT(tbClearColorClicked(bool)));
			delete fmLibContainer[i];
		}
		delete []fmLibContainer;
		fmLibContainer=NULL;
	}
	if(iCLogic!=NULL){
		delete []iCLogic;
		iCLogic=NULL;
	}
	if(iPickupAddColor!=NULL){
		delete []iPickupAddColor;
		iPickupAddColor=NULL;
	}
	if(iPickupDeleteColor!=NULL){
		delete []iPickupDeleteColor;
		iPickupDeleteColor=NULL;
	}
	if(AddCLogicList!=NULL){
		delete []AddCLogicList;
		AddCLogicList=NULL;
	}
	if(tbGerberCount!=NULL){
		delete []tbGerberCount;
		tbGerberCount=NULL;
	}

	if(AlignLevelLib!=NULL){
		for(int i=0;i<AutoAlignmentLibNumb;i++){
			delete AlignLevelLib[i];
		}
		delete []AlignLevelLib;
		AlignLevelLib=NULL;
	}
	AutoAlignmentLibNumb=0;

	if(PCBHoleLevelLib!=NULL){
		for(int i=0;i<AutoPCBHoleAlignerLibNumb;i++){
			delete PCBHoleLevelLib[i];
		}
		delete []PCBHoleLevelLib;
		PCBHoleLevelLib=NULL;
	}
	AutoPCBHoleAlignerLibNumb=0;

	if(DClassifyLevelLib!=NULL){
		for(int i=0;i<DynamicClassifyLibNumb;i++){
			delete DClassifyLevelLib[i];
		}
		delete []DClassifyLevelLib;
		DClassifyLevelLib=NULL;
	}
	DynamicClassifyLibNumb=0;
}

void EditLibraryForm::SetAutoAlignmentLibNumb(int Numb,AlgorithmBase	*ABase)
{
	for(int i=0;i<AutoAlignmentLibNumb;i++){
		delete AlignLevelLib[i];
	}
	delete []AlignLevelLib;

	AutoAlignmentLibNumb=Numb;

	AlignLevelLib=new AlgorithmLibraryLevelContainer*[AutoAlignmentLibNumb];
	for(int i=0;i<AutoAlignmentLibNumb;i++){
		AlignLevelLib[i]=new AlgorithmLibraryLevelContainer(ABase);
	}
}

void EditLibraryForm::SetAutoPCBHoleAlignerLibNumb(int Numb,AlgorithmBase	*ABase)
{
	for(int i=0;i<AutoPCBHoleAlignerLibNumb;i++){
		delete PCBHoleLevelLib[i];
	}
	delete []PCBHoleLevelLib;

	AutoPCBHoleAlignerLibNumb=Numb;

	PCBHoleLevelLib=new AlgorithmLibraryLevelContainer*[AutoPCBHoleAlignerLibNumb];
	for(int i=0;i<AutoPCBHoleAlignerLibNumb;i++){
		PCBHoleLevelLib[i]=new AlgorithmLibraryLevelContainer(ABase);
	}
}

void EditLibraryForm::SetDynamicClassifyLibNumb(int Numb,AlgorithmBase	*ABase)
{
	for(int i=0;i<DynamicClassifyLibNumb;i++){
		delete DClassifyLevelLib[i];
	}
	delete []DClassifyLevelLib;

	DynamicClassifyLibNumb=Numb;

	DClassifyLevelLib=new AlgorithmLibraryLevelContainer*[DynamicClassifyLibNumb];
	for(int i=0;i<DynamicClassifyLibNumb;i++){
		DClassifyLevelLib[i]=new AlgorithmLibraryLevelContainer(ABase);
	}
}

void EditLibraryForm::ShowLibrary(int i,AutoAlignmentLibrary *Lib,AlgorithmBase	*AlgorithmBasePointer)
{
	leLibName[i]		->setText	(Lib->GetLibName());
	QPalette P;
	int Numb=0;
	for(ColorSphere *pPickupColor=(ColorSphere *)Lib->PickupColor.GetFirstBase();pPickupColor!=NULL && Numb<9;pPickupColor=(ColorSphere *)pPickupColor->GetNext()){
		P.setColor(QPalette::Button,QColor(pPickupColor->GetCenter()));
		tbColor[Numb][i]->setPalette(P);
		tbColor[Numb][i]->setText(QString::number(Numb+1));
		Numb++;
	}
	sbNoiseShrink[i]	->setValue	(Lib->NoiseShrink);
	sbExpandForPickup[i]->setValue	(Lib->ExpandForPickup);
	iCLogic[i]=Numb;
	iPickupAddColor[i]=iPickupDeleteColor[i]=0;
	tbGerberCount[i]=0;

	connect(sbNoiseShrink[i]	,SIGNAL(valueChanged(int)),this,SLOT(sbNoiseShrinkValueChanged(int)));
	connect(sbExpandForPickup[i],SIGNAL(valueChanged(int)),this,SLOT(sbExpandForPickupValueChanged(int)));
}

void EditLibraryForm::ShowLibrary(int i,AutoPCBHoleAlignerLibrary *Lib,AlgorithmBase	*AlgorithmBasePointer)
{
	leLibName[AutoAlignmentLibNumb+i]			->setText	(Lib->GetLibName());
	QPalette P;
	P.setColor(QPalette::WindowText,QColor(Qt::white));
	int Numb=0;
	for(ColorSphere *pPickupHoleColor=(ColorSphere *)Lib->PickupHoleColor.GetFirstBase();pPickupHoleColor!=NULL && Numb<9;pPickupHoleColor=(ColorSphere *)pPickupHoleColor->GetNext()){
		P.setColor(QPalette::Button,QColor(pPickupHoleColor->GetCenter()));
		tbColor[Numb][AutoAlignmentLibNumb+i]	->setPalette(P);
		tbColor[Numb][AutoAlignmentLibNumb+i]	->setText(QString::number(Numb+1));
		Numb++;
	}
//	sbNoiseShrink[AutoAlignmentLibNumb+i]		->setValue	(PCBHoleAlignLib[i]->NoiseShrink);
	lbNoiseShrink[AutoAlignmentLibNumb+i]		->setVisible(false);
	sbNoiseShrink[AutoAlignmentLibNumb+i]		->setVisible(false);
	sbExpandForPickup[AutoAlignmentLibNumb+i]	->setValue	(Lib->ExpandForPickup);
	iCLogic[AutoAlignmentLibNumb+i]=Numb;
	iPickupAddColor[AutoAlignmentLibNumb+i]=iPickupDeleteColor[AutoAlignmentLibNumb+i]=0;
	tbGerberCount[AutoAlignmentLibNumb+i]=0;

///	connect(sbNoiseShrink[AutoAlignmentLibNumb+i]	 ,SIGNAL(valueChanged(int)),this,SLOT(sbNoiseShrinkValueChanged(int)));
	connect(sbExpandForPickup[AutoAlignmentLibNumb+i],SIGNAL(valueChanged(int)),this,SLOT(sbExpandForPickupValueChanged(int)));
}

void EditLibraryForm::ShowLibrary(int i,DynamicClassifyLibrary *Lib,AlgorithmBase	*AlgorithmBasePointer)
{
/*
	leLibName[i]		->setText	(DClassifyLib[i]->GetLibName());
	QPalette P;
	int Numb=0;
	for(ColorSphere *pPickupColor=(ColorSphere *)DClassifyLib[i]->PickupColor.Base.GetFirst();pPickupColor!=NULL && Numb<9;pPickupColor=(ColorSphere *)pPickupColor->GetNext()){
		P.setColor(QPalette::Button,QColor(pPickupColor->GetCenter()));
		tbColor[Numb][i]->setPalette(P);
		tbColor[Numb][i]->setText(QString::number(Numb+1));
		Numb++;
	}
	sbNoiseShrink[i]	->setValue	(DClassifyLib[i]->NoiseShrink);
	sbExpandForPickup[i]->setValue	(DClassifyLib[i]->ExpandForPickup);
	iCLogic[i]=Numb;
	iPickupAddColor[i]=iPickupDeleteColor[i]=0;

	connect(sbNoiseShrink[i]	,SIGNAL(valueChanged(int)),this,SLOT(sbNoiseShrinkValueChanged(int)));
	connect(sbExpandForPickup[i],SIGNAL(valueChanged(int)),this,SLOT(sbExpandForPickupValueChanged(int)));
*/
}
