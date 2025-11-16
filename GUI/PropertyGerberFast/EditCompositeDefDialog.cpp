#include "PropertyGerberFastFormResource.h"
#include "EditCompositeDefDialog.h"
#include "ui_EditCompositeDefDialog.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "swap.h"
#include "XGerberFastPacket.h"
#include "XDataInLayer.h"
#include "SelectLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*AlgoRoot;
extern	const	char	*AlgoName;


ItemFrame::ItemFrame(int turn ,GerberFastBase *base ,QWidget *parent)
{
	Base=base;
	Point=NULL;
	FrameItem		.setParent(parent);
    FrameItem.setGeometry(QRect(10, 10, 421, 61));
    FrameItem.setFrameShape(QFrame::StyledPanel);
    FrameItem.setFrameShadow(QFrame::Sunken);

	LabelNo			.setParent(&FrameItem);
	LabelLayerType	.setParent(&FrameItem);
	LabelDot		.setParent(&FrameItem);
	LayerTypeLibID	.setParent(&FrameItem);
	LayerTypeLibName.setParent(&FrameItem);
	ButtonLayerType	.setParent(&FrameItem);
	SBoxDotSpr		.setParent(&FrameItem);
	checkBoxNegMode	.setParent(&FrameItem);
	ButtonRemoveLine.setParent(&FrameItem);
	ButtonUpper		.setParent(&FrameItem);
	ButtonLower		.setParent(&FrameItem);

    LabelDot.setGeometry(QRect(170, 10, 50, 21));
    LabelDot.setFrameShape(QFrame::Panel);
    LabelDot.setFrameShadow(QFrame::Sunken);
    LabelDot.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	LabelDot.setText(LangSolver.GetString(EditCompositeDefDialog_LS,LID_32)/*"Dot"*/);
    LabelNo.setGeometry(QRect(0, 0, 16, 61));
    LabelNo.setFrameShape(QFrame::Panel);
    LabelNo.setFrameShadow(QFrame::Sunken);
    LabelNo.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	LabelNo.setText(QString::number(turn));
    LabelLayerType.setGeometry(QRect(50, 10, 111, 20));
    LabelLayerType.setFrameShape(QFrame::Panel);
    LabelLayerType.setFrameShadow(QFrame::Sunken);
    LabelLayerType.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	LabelLayerType.setText(LangSolver.GetString(EditCompositeDefDialog_LS,LID_33)/*"Layer type"*/);

	//SBoxDotSpr.setObjectName(QString::fromUtf8(/**/"SBoxDotSpr"));
	SBoxDotSpr.setGeometry(QRect(340, 31, 51, 21));
	SBoxDotSpr.setMinimum(-1000);
	SBoxDotSpr.setMaximum(1000);
	//LabelLayerType.setObjectName(QString::fromUtf8(/**/"LabelLayerType"));
	LabelLayerType.setGeometry(QRect(30, 10, 231, 20));
	LabelLayerType.setFrameShape(QFrame::Panel);
	LabelLayerType.setFrameShadow(QFrame::Sunken);
	LabelLayerType.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	//LabelDot.setObjectName(QString::fromUtf8(/**/"LabelDot"));
	LabelDot.setGeometry(QRect(340, 10, 50, 21));
	LabelDot.setFrameShape(QFrame::Panel);
	LabelDot.setFrameShadow(QFrame::Sunken);
	LabelDot.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	//LabelNo.setObjectName(QString::fromUtf8(/**/"LabelNo"));
	LabelNo.setGeometry(QRect(0, 0, 16, 61));
	LabelNo.setFrameShape(QFrame::Panel);
	LabelNo.setFrameShadow(QFrame::Sunken);
	LabelNo.setAlignment(Qt::AlignCenter|Qt::AlignHCenter|Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
	//ButtonLayerType.setObjectName(QString::fromUtf8(/**/"ButtonLayerType"));
	ButtonLayerType.setGeometry(QRect(220, 30, 41, 23));
	//LayerTypeLibID.setObjectName(QString::fromUtf8(/**/"LayerTypeLibID"));
	LayerTypeLibID.setGeometry(QRect(30, 30, 51, 20));
	//LayerTypeLibName.setObjectName(QString::fromUtf8(/**/"LayerTypeLibName"));
	LayerTypeLibName.setGeometry(QRect(80, 30, 131, 20));
	checkBoxNegMode.setGeometry(QRect(280, 20, 51, 17));

	ButtonRemoveLine.setGeometry(QRect(390, 2, 20, 20));
	ButtonRemoveLine.setText(/**/"X");
	ButtonUpper		.setGeometry(QRect(390, 22, 20, 20));
	ButtonUpper		.setArrowType(Qt::UpArrow);
	ButtonLower		.setGeometry(QRect(390, 40, 20, 20));
	ButtonLower		.setArrowType(Qt::DownArrow);

	connect(&SBoxDotSpr		,SIGNAL(valueChanged(int))	,this,SLOT(on_spinBox_valueChanged(int)));
	connect(&ButtonLayerType,SIGNAL(clicked())			,this,SLOT(SlotButtonLayerType_Clicked()));
	connect(&checkBoxNegMode,SIGNAL(clicked())			,this,SLOT(SlotCheckBoxNegMode_Clicked()));
	connect(&ButtonRemoveLine,SIGNAL(clicked())			,this,SLOT(SlotButtonRemoveLine_Clicked()));
	connect(&ButtonUpper	,SIGNAL(clicked())			,this,SLOT(SlotButtonUpper_Clicked()));
	connect(&ButtonLower	,SIGNAL(clicked())			,this,SLOT(SlotButtonLower_Clicked()));

	base->GetLayersBase()->InstallOperationLog(this);
}
void	ItemFrame::SetPosition(int Y ,int turn)
{
	LabelNo.setText(QString::number(turn));
    FrameItem.setGeometry(QRect(10, Y, 421, 61));
}
void	ItemFrame::SetVisible(bool flag)
{
	FrameItem.setVisible(flag);
}

void ItemFrame::PointNullMessage(void)
{
	//QMessageBox::critical(NULL,LangSolver.GetString(EditGerberCompositeDef_LS,LID_42)/*""*/,LangSolver.GetString(EditGerberCompositeDef_LS,LID_43)/*"Select one from left list"*/);
}

void ItemFrame::on_spinBox_valueChanged(int)
{
	if(Point==NULL){
		PointNullMessage();
		return;
	}
	if(Point!=NULL){
		Point->DotSpr=SBoxDotSpr.value();
	}
}

void	ItemFrame::SlotButtonLayerType_Clicked()
{
	SelectLibraryDialog		D(Base->GetLayersBase());
	bool	ok;
	int	LibID=LayerTypeLibID.text().toInt(&ok);
	if(ok==true){
		D.SetLibID(LibID);
	}
	if(D.exec()==QDialog::Accepted){
		if(Point!=NULL){
			Point->LayerTypeLibID=D.SelectedLibID;
			SetLibID(D.SelectedLibID);
		}
	}
}
void	ItemFrame::SlotCheckBoxNegMode_Clicked()
{
	if(Point==NULL){
		PointNullMessage();
		return;
	}
	if(Point!=NULL){
		Point->NegMode=checkBoxNegMode.isChecked();
	}
}
	
void	ItemFrame::SlotButtonRemoveLine_Clicked()
{
	emit	SignalRemoveLine();
}
void	ItemFrame::SlotButtonUpper_Clicked()
{
	emit	SignalUpper();
}
void	ItemFrame::SlotButtonLower_Clicked()
{
	emit	SignalLower();
}

void	ItemFrame::SetLibID(int LibID)
{
	QString	LibName=Base->GetLibraryContainer()->GetLibraryName(LibID);
	LayerTypeLibID	.setText(QString::number(LibID));
	LayerTypeLibName.setText(LibName);
}

ConnectionFrame::ConnectionFrame(QWidget *parent)
{
	GBox		.setParent(parent);
	ButtonOr	.setParent(&GBox);
	ButtonAnd	.setParent(&GBox);
	ButtonNotAnd.setParent(&GBox);
	ButtonNotOr	.setParent(&GBox);


	GBox.setGeometry(QRect(60, 80, 211, 21));
    ButtonOr	.setGeometry(QRect(10, 0, 61, 18));
    ButtonOr	.setChecked(true);
    ButtonAnd	.setGeometry(QRect(70, 0, 61, 18));
    ButtonAnd	.setChecked(false);
    ButtonNotAnd.setGeometry(QRect(130, 0, 61, 18));
    ButtonNotOr	.setGeometry(QRect(200, 0, 61, 18));

	ButtonOr	.setText(/**/"Or");
	ButtonAnd	.setText(/**/"And");
	ButtonNotOr	.setText(/**/"NotOr");
	ButtonNotAnd.setText(/**/"NotAnd");

	ButtonNotOr .setHidden(true);

	//connect(&GBox	,SIGNAL(toggled(bool))	,this,SLOT(on_groupBoxOperation1_toggled(bool)));
	connect(&ButtonOr		,SIGNAL(toggled(bool))	,this,SLOT(on_radioButtonOr_toggled(bool)));
	connect(&ButtonAnd		,SIGNAL(toggled(bool))	,this,SLOT(on_radioButtonAnd_toggled(bool)));
	connect(&ButtonNotAnd	,SIGNAL(toggled(bool))	,this,SLOT(on_radioButtonNotAnd_toggled(bool)));
	connect(&ButtonNotOr	,SIGNAL(toggled(bool))	,this,SLOT(on_radioButtonNotOr_toggled(bool)));
}
void ConnectionFrame::PointNullMessage(void)
{
	QMessageBox::critical(NULL
						,/**/""
						,LangSolver.GetString(EditCompositeDefDialog_LS,LID_34)/*"Select one from left list"*/);
}
void	ConnectionFrame::SetPosition(int Y)
{
    //GBox.setGeometry(QRect(30, Y, 241, 21));
	GBox.setGeometry(QRect(60, Y, 211, 21));
}
void	ConnectionFrame::SetVisible(bool flag)
{
	GBox.setVisible(flag);
}

void ConnectionFrame::on_radioButtonOr_toggled(bool)
{
	if(ButtonOr.isChecked()==true){
		if(Point==NULL){
			PointNullMessage();
			return;
		}
		if(Point!=NULL){
			Point->Operation=GerberCompositeDefLayerItem::_Or;
		}
	}
}
void ConnectionFrame::on_radioButtonAnd_toggled(bool)
{
	if(ButtonAnd.isChecked()==true){
		if(Point==NULL){
			PointNullMessage();
			return;
		}
		if(Point!=NULL){
			Point->Operation=GerberCompositeDefLayerItem::_And;
		}
	}
}
void ConnectionFrame::on_radioButtonNotAnd_toggled(bool)
{
	if(ButtonNotAnd.isChecked()==true){
		if(Point==NULL){
			PointNullMessage();
			return;
		}
		if(Point!=NULL){
			Point->Operation=GerberCompositeDefLayerItem::_NotAnd;
		}
	}
}
void ConnectionFrame::on_radioButtonNotOr_toggled(bool)
{
	if(ButtonNotOr.isChecked()==true){
		if(Point==NULL){
			PointNullMessage();
			return;
		}
		if(Point!=NULL){
			Point->Operation=GerberCompositeDefLayerItem::_NotOr;
		}
	}
}

//===============================================================
LayerItemFrame::LayerItemFrame(int turn ,GerberFastBase *base ,QWidget *parent)
:QObject(parent),ItemWindows(turn,base,parent),ConnWindows(parent)
{
	Base	=base;
	Turn	=turn;
	connect(&ItemWindows,SIGNAL(SignalRemoveLine())	,this,SLOT(SlotRemoveLine()));
	connect(&ItemWindows,SIGNAL(SignalUpper())		,this,SLOT(SlotUpper()));
	connect(&ItemWindows,SIGNAL(SignalLower())		,this,SLOT(SlotLower()));
}
int	LayerItemFrame::SetPosition(int Y)
{
	if(Turn==0){
		ConnWindows.SetVisible(false);
		ItemWindows.SetPosition(Y ,Turn);
		ItemWindows.ButtonUpper.setVisible(false);
		ItemWindows.ButtonLower.setVisible(true);
		return 70;
	}
	else{
		ConnWindows.SetPosition(Y);
		ItemWindows.SetPosition(Y+30 ,Turn);
		ItemWindows.ButtonUpper.setVisible(true);
		ItemWindows.ButtonLower.setVisible(true);
		return 108;
	}
}

void	LayerItemFrame::Show(GerberCompositeDefLayerItem *G)
{
	ItemWindows.Point=G;
	ConnWindows.Point=G;
	SetVisible(true);
	ItemWindows.SetLibID(G->LayerTypeLibID);

	ItemWindows.SBoxDotSpr.setValue(G->DotSpr);
	switch(G->Operation){
		case GerberCompositeDefLayerItem::_Or:
			ConnWindows.ButtonOr.setChecked(true);
			break;
		case GerberCompositeDefLayerItem::_And:
			ConnWindows.ButtonAnd.setChecked(true);
			break;
		case GerberCompositeDefLayerItem::_NotAnd:
			ConnWindows.ButtonNotAnd.setChecked(true);
			break;
		case GerberCompositeDefLayerItem::_NotOr:
			ConnWindows.ButtonNotOr.setChecked(true);
			break;
	}
	ItemWindows.checkBoxNegMode.setChecked(G->NegMode);
}
void	LayerItemFrame::SetVisible(bool flag)
{
	ItemWindows.SetVisible(flag);
	if(Turn!=0)
		ConnWindows.SetVisible(flag);
}
void	LayerItemFrame::SlotRemoveLine()
{
	emit	SignalRemoveLine(Turn);
}
void	LayerItemFrame::SlotUpper()
{
	emit	SignalUpper(Turn);
}
void	LayerItemFrame::SlotLower()
{
	emit	SignalLower(Turn);
}

//================================================================================

EditCompositeDefDialog::EditCompositeDefDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditCompositeDefDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;

	DefLine	=NULL;
	GerberFastBase	*GBase=GetGerberFastBase();
	LibType=-1;
	if(GBase!=NULL){
		LibType=GBase->GetLibType();
		CompositeDef=GBase->CompositeDef;
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	FrameArea.setParent(this);
	FrameArea.setGeometry (ui->frameSampleBase->geometry());
	delete	ui->frameSampleBase;
	ui->frameSampleBase=NULL;

	//FrameArea.move(0,0);
	//FrameArea.resize(ui.frameFiles->width()-1,ui.frameFiles->height()-1);
	FrameArea.setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	int	Y=0;
	for(int i=0;i<sizeof(FrameDim)/sizeof(FrameDim[0]);i++){
		FrameDim[i]=new LayerItemFrame(i,GBase,&FrameAreaInside);
		connect(FrameDim[i],SIGNAL(SignalRemoveLine(int))	,this,SLOT(SlotRemoveLine(int)),Qt::QueuedConnection);
		connect(FrameDim[i],SIGNAL(SignalUpper(int))		,this,SLOT(SlotUpper(int)),Qt::QueuedConnection);
		connect(FrameDim[i],SIGNAL(SignalLower(int))		,this,SLOT(SlotLower(int)),Qt::QueuedConnection);
		Y+=FrameDim[i]->SetPosition(Y);
	}
	FrameAreaInside.resize(FrameArea.width()-1,Y);
	FrameArea.setWidget(&FrameAreaInside);

	ShowCompositeList();

	AlgorithmBase	*Ab=GetGerberFastBase();
	int	LibType=-1;
	if(Ab!=NULL){
		LibType=Ab->GetLibType();
		CmdCreateTempGerberFastLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
	}
}

EditCompositeDefDialog::~EditCompositeDefDialog()
{
	for(int i=0;i<sizeof(FrameDim)/sizeof(FrameDim[0]);i++){
		delete	FrameDim[i];
	}
    delete ui;

	delete	TempLib;
	TempLib=NULL;
}
GerberFastBase	*EditCompositeDefDialog::GetGerberFastBase(void)
{
	GerberFastBase	*Base=(GerberFastBase *)GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	return Base;
}

void	EditCompositeDefDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ShowCompositeList();
}

void	EditCompositeDefDialog::ShowCompositeLayer(int Row)
{
	DefLine=GerberCompositeDefLayerPointerContainer[Row]->Point;
	if(DefLine!=NULL){
		ui->lineEditName->setText(DefLine->Name);
		int	N=0;
		for(GerberCompositeDefLayerItem *item=DefLine->Combination.GetFirst();item!=NULL && N<sizeof(FrameDim)/sizeof(FrameDim[0]);item=item->GetNext(),N++){
			FrameDim[N]->Show(item);
		}
		for(;N<sizeof(FrameDim)/sizeof(FrameDim[0]);N++){
			FrameDim[N]->SetVisible(false);
		}
		ShowDataToWindow(DefLine);
	}
	else{
		ui->lineEditName->clear();
		for(int N=0;N<sizeof(FrameDim)/sizeof(FrameDim[0]);N++){
			FrameDim[N]->SetVisible(false);
		}
		ShowDataToWindow(NULL);
	}
}

void EditCompositeDefDialog::ShowCompositeList(void)
{
	if(ui->listComposite->count()>0){
		ui->listComposite->clear();
	}
	GerberCompositeDefLayerPointerContainer.RemoveAll();
	for(GerberCompositeDefLayer *g=CompositeDef.GetFirst();g!=NULL;g=g->GetNext()){
		if(g->LibFolderID==LibFolderID){
			GerberCompositeDefLayerPointerContainer.AppendList(new GerberCompositeDefLayerPointerList(g));
			ui->listComposite->addItem(g->Name);
		}
	}
}
void EditCompositeDefDialog::on_pushButtonClose_clicked()
{
	//GerberSaveCompositeDefPacket	Cmd(GetLayersBase());
	//GerberFastBase	*GBase=GetGerberFastBase();
	//GBase->TransmitDirectly(&Cmd);
	if(QMessageBox::question(NULL, "Choose"
						, "Do you close?"
						, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
		close();
	}
}

void EditCompositeDefDialog::on_pushButtonSaveNew_clicked()
{
	GerberFastBase	*GBase=GetGerberFastBase();
	GerberCompositeDefLayer *g=new GerberCompositeDefLayer();
	int	MaxID=0;
	for(GerberCompositeDefLayer *m=CompositeDef.GetFirst();m!=NULL;m=m->GetNext()){
		MaxID=max(MaxID,m->CompositeID);
	}
	g->LibFolderID=LibFolderID;
	g->CompositeID=MaxID+1;
	bool	ok;
	int	LibID=ui->lineEditLibID->text().toInt(&ok);
	if(ok==true){
		g->LibID	=LibID;
	}
	g->Name=ui->lineEditName->text();
	g->NegMode=ui->checkBoxNegModeInContainer->isChecked();

	if(DefLine!=NULL && QMessageBox::question(NULL	,LangSolver.GetString(EditCompositeDefDialog_LS,LID_96)/*"Select"*/
									,LangSolver.GetString(EditCompositeDefDialog_LS,LID_97)/*"Do you copy definition items?"*/
									,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		g->Combination=DefLine->Combination;
	}
	CompositeDef.AppendList(g);
	ShowCompositeList();
	ui->listComposite->setCurrentRow(GerberCompositeDefLayerPointerContainer.GetCount()-1);
	ShowCompositeLayer(GerberCompositeDefLayerPointerContainer.GetCount()-1);

	GBase->CompositeDef=CompositeDef;
	GerberSaveCompositeDefPacket	Cmd(GetLayersBase());
	GBase->TransmitDirectly(&Cmd);
	DefLine=g;
	ShowCompositeList();
	int	Index=ui->listComposite->count();
	ui->listComposite->setCurrentRow(Index-1);
}

void EditCompositeDefDialog::on_pushButtonUpdate_clicked()
{
	GerberFastBase	*GBase=GetGerberFastBase();
	if(DefLine!=NULL){
		DefLine->LibFolderID	=LibFolderID;
		DefLine->Name			=ui->lineEditName->text();
		bool	ok;
		int	LibID=ui->lineEditLibID->text().toInt(&ok);
		if(ok==true){
			DefLine->LibID	=TempLib->GetLibID();
		}
		DefLine->NegMode=ui->checkBoxNegModeInContainer->isChecked();
		if(DefLine->LibID<0){
			QMessageBox::warning(NULL
								,LangSolver.GetString(EditCompositeDefDialog_LS,LID_98)/*"Alert"*/
								,LangSolver.GetString(EditCompositeDefDialog_LS,LID_99)/*"No library is allocated"*/);
		}
	}
	GerberSaveCompositeDefPacket	Cmd(GetLayersBase());
	GBase->TransmitDirectly(&Cmd);

	ShowCompositeList();
}

void EditCompositeDefDialog::on_pushButtonDelete_clicked()
{
	if(ui->listComposite->count()>0){
		int	Row=ui->listComposite->currentRow();
		if(Row<0)
			return;
		GerberFastBase	*GBase=GetGerberFastBase();
		GerberCompositeDefLayer *g=GerberCompositeDefLayerPointerContainer[Row]->Point;
		if(g!=NULL){
			CompositeDef.RemoveList(g);
			delete	g;
		}
		GerberSaveCompositeDefPacket	Cmd(GetLayersBase());
		GBase->TransmitDirectly(&Cmd);

		ShowCompositeList();
	}
}

void EditCompositeDefDialog::on_listComposite_clicked(const QModelIndex &Index)
{
	ShowCompositeLayer(Index.row());
}

void EditCompositeDefDialog::on_ButtonPlus_clicked()
{
	if(ui->listComposite->count()>0){
		int	Row=ui->listComposite->currentRow();
		GerberCompositeDefLayer *g=GerberCompositeDefLayerPointerContainer[Row]->Point;
		if(g!=NULL){
			if(g->Combination.GetNumber()<sizeof(FrameDim)/sizeof(FrameDim[0])){
				g->Combination.AppendList(new GerberCompositeDefLayerItem());
				ShowCompositeLayer(Row);
			}
		}
	}
}

void EditCompositeDefDialog::on_ButtonMinus_clicked()
{
	if(ui->listComposite->count()>0){
		int	Row=ui->listComposite->currentRow();
		GerberCompositeDefLayer *g=GerberCompositeDefLayerPointerContainer[Row]->Point;
		if(g!=NULL){
			GerberCompositeDefLayerItem	*t=g->Combination.GetLast();
			if(t!=NULL){
				g->Combination.RemoveList(t);
				delete	t;
				ShowCompositeLayer(Row);
			}
		}
	}
}


void EditCompositeDefDialog::ShowDataToWindow(GerberCompositeDefLayer *Attr)
{
	bool	Success=false;
	if(Attr!=NULL){
		AlgorithmBase	*Ab=GetGerberFastBase();
		if(Ab!=NULL){
			TempLib->SetLibID(Attr->LibID);
			CmdLoadGerberFastLibraryPacket	Packet(GetLayersBase());
			Packet.Point=TempLib;
			Ab->TransmitDirectly(&Packet);
			Success=Packet.Success;
		}
	}
	if(Success==true){
		GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(TempLib->GetLibrary());
		ui->lineEditLibID				->setText(QString::number(TempLib->GetLibID()));
		ui->lineEditLibName				->setText(TempLib->GetLibName());
		ui->spinBoxMaxEnlargeDot		->setValue(ALib->MaxEnlargeDot);
		ui->spinBoxMaxShrinkageDot		->setValue(ALib->MaxShrinkDot);
		ui->spinBoxMaxShiftDot			->setValue(ALib->MaxShiftDot);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(ALib->MaxAngleRadius);
		ui->doubleSpinBoxMaxUnstableZone->setValue(ALib->UnstableZone);
	}
	else{
		ui->lineEditLibID				->setText(/**/"");
		ui->lineEditLibName				->setText(/**/"");
		ui->spinBoxMaxEnlargeDot		->setValue(1);
		ui->spinBoxMaxShrinkageDot		->setValue(1);
		ui->spinBoxMaxShiftDot			->setValue(1);
		ui->doubleSpinBoxMaxAngleRadius	->setValue(1);
		ui->doubleSpinBoxMaxUnstableZone->setValue(1);
	}
	ui->checkBoxNegModeInContainer->setChecked(Attr->NegMode);
}


void EditCompositeDefDialog::on_pushButtonSelectLib_clicked()
{
	SelectLibraryDialog		D(GetLayersBase());
	bool	ok;
	int	LibID=ui->lineEditLibID->text().toInt(&ok);
	if(ok==true){
		D.SetLibID(LibID);
	}
	if(D.exec()==QDialog::Accepted){
		int	LibID=D.SelectedLibID;
		ui->lineEditLibID				->setText(QString::number(LibID));
		AlgorithmBase	*Ab=GetGerberFastBase();
		if(Ab!=NULL){
			TempLib->SetLibID(LibID);
			CmdLoadGerberFastLibraryPacket	Packet(GetLayersBase());
			Packet.Point=TempLib;
			Ab->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				GerberFastLibrary	*ALib=dynamic_cast<GerberFastLibrary *>(TempLib->GetLibrary());
				ui->lineEditLibName				->setText (TempLib->GetLibName());
				ui->spinBoxMaxEnlargeDot		->setValue(ALib->MaxEnlargeDot);
				ui->spinBoxMaxShrinkageDot		->setValue(ALib->MaxShrinkDot);
				ui->spinBoxMaxShiftDot			->setValue(ALib->MaxShiftDot);
				ui->doubleSpinBoxMaxAngleRadius	->setValue(ALib->MaxAngleRadius);
				ui->doubleSpinBoxMaxUnstableZone->setValue(ALib->UnstableZone);
			}
		}
	}
}

void	EditCompositeDefDialog::SlotRemoveLine(int Turn)
{
	GerberCompositeDefLayerItem	*t=FrameDim[Turn]->ItemWindows.Point;
	if(DefLine!=NULL){
		DefLine->Combination.RemoveList(t);
		delete	t;
	}

	delete	FrameDim[Turn];
	for(int i=Turn;i<sizeof(FrameDim)/sizeof(FrameDim[0])-1;i++){
		FrameDim[i]=FrameDim[i+1];
	}
	int	k=sizeof(FrameDim)/sizeof(FrameDim[0])-1;
	GerberFastBase	*GBase=GetGerberFastBase();
	FrameDim[k]=new LayerItemFrame(k,GBase,&FrameAreaInside);

	int	Y=0;
	for(int i=0;i<sizeof(FrameDim)/sizeof(FrameDim[0]);i++){
		FrameDim[i]->Turn=i;
		Y+=FrameDim[i]->SetPosition(Y);
	}
}
void	EditCompositeDefDialog::SlotUpper(int Turn)
{
	if(DefLine==NULL || Turn==0){
		return;
	}
	GerberCompositeDefLayerItem	*t2=FrameDim[Turn]->ItemWindows.Point;
	GerberCompositeDefLayerItem	*t1=FrameDim[Turn-1]->ItemWindows.Point;
	DefLine->Combination.Swap(t1,t2);

	LayerItemFrame	*k=FrameDim[Turn];
	FrameDim[Turn]=FrameDim[Turn-1];
	FrameDim[Turn-1]=k;

	int	Y=0;
	for(int i=0;i<sizeof(FrameDim)/sizeof(FrameDim[0]);i++){
		FrameDim[i]->Turn=i;
		Y+=FrameDim[i]->SetPosition(Y);
	}
}
void	EditCompositeDefDialog::SlotLower(int Turn)
{
	if(DefLine==NULL){
		return;
	}
	int	N=DefLine->Combination.GetCount();
	if(Turn+1>=N){
		return;
	}
	GerberCompositeDefLayerItem	*t1=FrameDim[Turn]->ItemWindows.Point;
	GerberCompositeDefLayerItem	*t2=FrameDim[Turn+1]->ItemWindows.Point;
	DefLine->Combination.Swap(t1,t2);

	LayerItemFrame	*k=FrameDim[Turn];
	FrameDim[Turn]=FrameDim[Turn+1];
	FrameDim[Turn+1]=k;

	int	Y=0;
	for(int i=0;i<sizeof(FrameDim)/sizeof(FrameDim[0]);i++){
		FrameDim[i]->Turn=i;
		Y+=FrameDim[i]->SetPosition(Y);
	}
}

void EditCompositeDefDialog::on_pushButtonSaveFile_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL	,"Save Gerber composite definition into File"
														,QString()
														,/**/"DefFile(*.dat);;All file(*.*)");

	GerberFastBase	*GBase=GetGerberFastBase();
	GerberSaveCompositeDefIntoFilePacket	Cmd(GetLayersBase());
	Cmd.FileName	=FileName;
	GBase->TransmitDirectly(&Cmd);
	if(Cmd.RetSuccess==false){
		QMessageBox::warning(NULL	,"Error"	,"Fails to save");
	}
}

void EditCompositeDefDialog::on_pushButtonLoadFile_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL	,"Load Gerber composite definition into File"
														,QString()
														,/**/"DefFile(*.dat);;All file(*.*)");

	GerberFastBase	*GBase=GetGerberFastBase();
	GerberLoadCompositeDefIntoFilePacket	Cmd(GetLayersBase());
	Cmd.FileName	=FileName;
	GBase->TransmitDirectly(&Cmd);
	ShowCompositeList();
	if(Cmd.RetSuccess==false){
		QMessageBox::warning(NULL	,"Error"	,"Fails to load");
	}
}

void EditCompositeDefDialog::on_pushButtonAppendFile_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL	,"Append Gerber composite definition into File"
														,QString()
														,/**/"DefFile(*.dat);;All file(*.*)");

	GerberFastBase	*GBase=GetGerberFastBase();
	GerberAppendCompositeDefIntoFilePacket	Cmd(GetLayersBase());
	Cmd.FileName	=FileName;
	GBase->TransmitDirectly(&Cmd);
	ShowCompositeList();
	if(Cmd.RetSuccess==false){
		QMessageBox::warning(NULL	,"Error"	,"Fails to append");
	}
}
