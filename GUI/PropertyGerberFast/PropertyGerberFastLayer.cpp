#include "PropertyGerberFastFormResource.h"
#include "PropertyGerberFastForm.h"
#include "XGerberFast.h"
#include "XGeneralDialog.h"
#include "SelectLibraryDialog.h"
#include "XAlgorithmLibrary.h"
#include "XImageStocker.h"
#include <QColorDialog>
#include <QMenu>
#include "swap.h"
#include "XEntryPoint.h"

void mtToolButtonColoredWithRightClick::mousePressEvent(QMouseEvent * event )
{
	if((event->button() & Qt::RightButton)!=0){
		emit	ClickRight();
	}
	QToolButton::mousePressEvent(event);
}

GerberLayerListOnScreen::ScreenDataInPhase::ScreenDataInPhase(void)
{
	LibID		=-1;
	Selected	=false;
	Operation	=false;
}

GerberLayerListOnScreen::ScreenDataInPhase	&GerberLayerListOnScreen::ScreenDataInPhase::operator=(GerberLayerListOnScreen::ScreenDataInPhase &src)
{
	LibID		=src.LibID;
	Selected	=src.Selected;
	Operation	=src.Operation;
	FileName	=src.FileName;
	Remark		=src.Remark;
	return *this;
}

bool	GerberLayerListOnScreen::ScreenDataInPhase::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,Selected)==false)
		return false;
	if(::Save(f,Operation)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	return true;
}
bool	GerberLayerListOnScreen::ScreenDataInPhase::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,Selected)==false)
		return false;
	if(::Load(f,Operation)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	return true;
}
//===============================================================================================

GerberLayerListOnScreen::GerberLayerListOnScreen(int layerNo,PropertyGerberFastForm *formbase ,QWidget *parent)
:GerberInLayerBase(parent),ServiceForLayers(formbase->GetLayersBase()),FormParent(formbase)
{
	LangSolver.SetUI(this);
	FileLayerNo	=layerNo;

	AllocatedPhaseCount	=GetLayersBase()->GetPhaseNumb()+5;
	DataInPhase			=new ScreenDataInPhase[AllocatedPhaseCount];
	LastCurrentPhase	=0;


	ButtonSelected		.setParent(this);
	CheckBoxOperation	.setParent(this);
	EditLibID			.setParent(this);
	EditLibName			.setParent(this);
	ButtonChooseLib		.setParent(this);
	EditFileName		.setParent(this);
	ButtonChooseFile	.setParent(this);
	EditRemark			.setParent(this);
	ButtonGerber	    .setParent(this);

	ButtonGerber		.setText(/**/"D");
	ButtonChooseLib		.setText(/**/"L");

	ButtonSelected.setAutoExclusive(true);
	ButtonSelected.setCheckable(true);
	ButtonSelected.setAutoRaise(true);
	ButtonSelected.setColor(FormParent->GetLayerColor(layerNo));
	CheckBoxOperation.setAutoExclusive(false);
	CheckBoxOperation.setCheckable(true);
	CheckBoxOperation.setChecked(true);

	connect(&ButtonSelected		,SIGNAL(ClickRight())				,this,SLOT(SlotSelectedButtonRightClicked()));
	connect(&ButtonSelected		,SIGNAL(clicked())					,this,SLOT(SlotSelectedButtonClicked()));
	connect(&CheckBoxOperation	,SIGNAL(clicked())					,this,SLOT(SlotCheckBoxOperationClicked()));
	connect(&ButtonChooseLib	,SIGNAL(clicked())					,this,SLOT(SlotButtonChooseLibClicked()));
	connect(&ButtonChooseFile	,SIGNAL(clicked())					,this,SLOT(SlotChooseFileClicked()));
	connect(&EditFileName		,SIGNAL(textChanged (const QString &))	,this,SLOT(EditFilenameChanged(const QString &)));
	connect(&ButtonGerber		,SIGNAL(clicked())					,this,SLOT(SlotButtonGerberClicked()));

	SignalEnabled=true;
	SetComboBLayerType();

	setAutoFillBackground(true);
	QPalette	P=palette();
	if((layerNo&1)==0)
		P.setColor(QPalette::Window,Qt::lightGray);
	else
		P.setColor(QPalette::Window,Qt::darkGray);
	setPalette(P);
}
GerberLayerListOnScreen::~GerberLayerListOnScreen(void)
{
	delete	[]DataInPhase;
	DataInPhase=NULL;
}
	
void	GerberLayerListOnScreen::StoreFromWindow(void)
{
	//DataInPhase[LastCurrentPhase].LibID		=ui->EditLibID.();
	DataInPhase[LastCurrentPhase].Selected	=ButtonSelected.isChecked();
	DataInPhase[LastCurrentPhase].Operation	=CheckBoxOperation.isChecked();
	DataInPhase[LastCurrentPhase].FileName	=EditFileName.text();
	DataInPhase[LastCurrentPhase].Remark	=EditRemark.text();
}
void	GerberLayerListOnScreen::StoreToWindow(void)
{
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	ButtonSelected		.setChecked(DataInPhase[CurrentPhase].Selected);
	CheckBoxOperation	.setChecked(DataInPhase[CurrentPhase].Operation);
	EditFileName.setText(DataInPhase[CurrentPhase].FileName);
	EditRemark.setText(DataInPhase[CurrentPhase].Remark);
	LastCurrentPhase=CurrentPhase;
	SetComboBLayerType();
}

void	GerberLayerListOnScreen::SetComboBLayerType(void)
{
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	if(DataInPhase[CurrentPhase].LibID>=0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"GerberFast");
		if(Ab!=NULL){
			CmdGetGerberFastLibraryNamePacket	Cmd(GetLayersBase());
			Cmd.LibID	=DataInPhase[CurrentPhase].LibID;
			Ab->TransmitDirectly(&Cmd);
			EditLibID	.setText(QString::number(Cmd.LibID));
			EditLibName	.setText(Cmd.LibName);
		}
	}
	else{
		EditLibID	.setText(/**/"");
		EditLibName	.setText(/**/"");
	}
	SignalEnabled=true;
}

int	GerberLayerListOnScreen::ShowPosition(int Y)
{
	int	TopGap=3;
	int	ItemHeight=20;
	int	LineHeight=ItemHeight+TopGap*2+TopGap;
	int	X=1;
	ButtonSelected		.move(X,TopGap);
	ButtonSelected		.resize(24,ItemHeight);
	X+=24;
	X+=4;
	CheckBoxOperation	.move(X,TopGap);
	CheckBoxOperation	.resize(16,ItemHeight);

	X+=16;
	X+=4;

	EditFileName		.move(X,TopGap);
	EditFileName		.resize(310,ItemHeight);
	X+=310;
	X+=4;
	ButtonChooseFile	.move(X,TopGap);
	ButtonChooseFile	.resize(20,ItemHeight);
	ButtonChooseFile	.setIcon(QIcon(QPixmap::fromImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/"::Resources/OpenFolder.png"))));
	X+=20;
	X+=4;

	X=49;
	EditLibID			.move(X,LineHeight);
	EditLibID			.resize(48,ItemHeight);
	X+=48;
	X+=4;
	EditLibName			.move(X,LineHeight);
	EditLibName			.resize(100,ItemHeight);
	X+=100;
	X+=4;
	ButtonChooseLib		.move(X,LineHeight);
	ButtonChooseLib		.resize(20,ItemHeight);
	X+=20;
	X+=8;
	EditRemark			.move(X,LineHeight);
	EditRemark			.resize(130,ItemHeight);
	X+=130;
	X+=4;
	ButtonGerber		.move(X,LineHeight);
	ButtonGerber		.resize(20,ItemHeight);
	X+=20;
	X+=4;

	PosY=Y;
	move(0,Y);
	int	YLen=(ItemHeight+TopGap*2)*2;
	if(parentWidget()!=NULL){
		resize((parentWidget())->width(),YLen);
	}
	return YLen;
}
void	GerberLayerListOnScreen::Resize(void)
{
	int	TopGap=3;
	int	ItemHeight=20;
	int	YLen=(ItemHeight + TopGap * 2) * 2;
	if(parentWidget() != NULL) {
		resize((parentWidget())->width(), YLen);
	}
}

void	GerberLayerListOnScreen::resizeEvent(QResizeEvent *event)
{
	int	TopGap=3;
	int	ItemHeight=20;
	int	LineHeight=ItemHeight + TopGap * 2 + TopGap;
	int	W=width();

	int	X=1;
	X+=24;
	X+=4;
	X+=16;
	X+=4;

	EditFileName.resize(W-100-8, ItemHeight);
	X+=W-100-8;
	X+=4;
	ButtonChooseFile.move(X, TopGap);
	ButtonChooseFile.resize(20, ItemHeight);

	X=49;
	X+=48;
	X+=4;
	EditLibName.move(X, LineHeight);
	int	W1=(W - 49) / 2 - 52 - 20 - 4;
	EditLibName.resize(W1, ItemHeight);
	X+=W1;
	X+=4;
	ButtonChooseLib.move(X, LineHeight);
	ButtonChooseLib.resize(20, ItemHeight);
	X+=20;
	X+=8;
	EditRemark.move(X, LineHeight);
	EditRemark.resize(W1, ItemHeight);
	X+=W1;
	X+=4;
	ButtonGerber.move(X, LineHeight);
	ButtonGerber.resize(20, ItemHeight);
}

GerberLayerListOnScreen	&GerberLayerListOnScreen::operator=(GerberLayerListOnScreen &src)
{
	for(int i=0;i<AllocatedPhaseCount && i<src.AllocatedPhaseCount;i++){
		DataInPhase[i]=src.DataInPhase[i];
	}
	//LibID	=src.LibID;
	FileLayerNo	=src.FileLayerNo;
	ButtonSelected.setColor(src.ButtonSelected.color());

	EditLibID	.setText(src.EditLibID	.text());
	EditLibName	.setText(src.EditLibName.text());
	EditFileName.setText(src.EditFileName.text());
	EditRemark	.setText(src.EditRemark	.text());

	return *this;
}

void	GerberLayerListOnScreen::Swap(GerberLayerListOnScreen &src)
{
	for(int i=0;i<AllocatedPhaseCount && i<src.AllocatedPhaseCount;i++){
		ScreenDataInPhase	Tmp;
		Tmp=DataInPhase[i];
		DataInPhase[i]		=src.DataInPhase[i];
		src.DataInPhase[i]	=DataInPhase[i];
	}
	//swap(LibID ,src.LibID);
	swap(FileLayerNo,src.FileLayerNo);

	QColor	Col=ButtonSelected.color();
	ButtonSelected.setColor(src.ButtonSelected.color());
	src.ButtonSelected.setColor(Col);

	QString	tEditLibID		=EditLibID	.text();
	QString	tEditLibName	=EditLibName.text();
	QString	tEditFileName	=EditFileName.text();
	QString	tEditRemark		=EditRemark	.text();

	EditLibID	.setText(src.EditLibID	.text());
	EditLibName	.setText(src.EditLibName.text());
	EditFileName.setText(src.EditFileName.text());
	EditRemark	.setText(src.EditRemark	.text());

	src.EditLibID	.setText(tEditLibID		);
	src.EditLibName	.setText(tEditLibName	);
	src.EditFileName.setText(tEditFileName	);
	src.EditRemark	.setText(tEditRemark	);
}

void	GerberLayerListOnScreen::DeliverAllPhases(int SrcPhase)
{
	for(int i=0;i<AllocatedPhaseCount;i++){
		if(i==SrcPhase)
			continue;
		DataInPhase[i]=DataInPhase[SrcPhase];
	}
}

void	GerberLayerListOnScreen::SlotSelectedButtonClicked()
{
	if(EditFileName.text().isEmpty()==false){
		emit	ClickedSelected(FileLayerNo);
	}
}
void	GerberLayerListOnScreen::SlotButtonGerberClicked()
{
	emit	ClickedApertured(FileLayerNo);
}
void	GerberLayerListOnScreen::SlotSelectedButtonRightClicked(void)
{
	QColor Col=QColorDialog::getColor ( ButtonSelected.color());
	SetColor(Col);
}

void		GerberLayerListOnScreen::ClearLibID(void)
{
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	DataInPhase[CurrentPhase].LibID=-1;
	SetComboBLayerType();
}
	
int		GerberLayerListOnScreen::GetLibID(void)
{	
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	return DataInPhase[CurrentPhase].LibID;
}

void	GerberLayerListOnScreen::SetLibID(int id)
{	
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	DataInPhase[CurrentPhase].LibID=id;
}

void	GerberLayerListOnScreen::DragTransferDirently(GUIDirectMessage *packet)
{
	CmdSetLayerLibID	*CmdSetLayerLibIDVar=dynamic_cast<CmdSetLayerLibID *>(packet);
	if(CmdSetLayerLibIDVar!=NULL){
		if(GetParamGlobal()->CommonOperationInAllPhases==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				DataInPhase[phase].LibID=CmdSetLayerLibIDVar->LibID;
			}
		}
		else{
			int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
			DataInPhase[CurrentPhase].LibID=CmdSetLayerLibIDVar->LibID;
		}
		SetComboBLayerType();
	}
}
void	GerberLayerListOnScreen::SetFileLayerNo(int n)
{
	FileLayerNo=n;
}

int		GerberLayerListOnScreen::GetFileLayerNo(void)
{
	if(EditFileName.text().isEmpty()==false || GetEntryPoint()->IsMasterPC()==false){
		return FileLayerNo;
	}
	return -1;
}

void		GerberLayerListOnScreen::SetColor(QColor &Col)
{
	if(Col.isValid()==true){
		ButtonSelected.setColor(Col);
		emit ChangedColor(FileLayerNo ,Col);
	}
}
void	GerberLayerListOnScreen::SlotChooseFileClicked()
{
	QString fname=GetLayersBase()->LGetOpenFileName (this, /**/"Layer file name");
	if(fname.isNull()!=true){
		EditFileName.setText(fname);
	}
}
void	GerberLayerListOnScreen::SlotCheckBoxOperationClicked()
{
	if(SignalEnabled==true){
		emit	DataChanged(FileLayerNo);
	}
}

void	GerberLayerListOnScreen::EditFilenameChanged(const QString &)
{
	if(SignalEnabled==true){
		emit	DataChanged(FileLayerNo);
	}
}

void	GerberLayerListOnScreen::SlotButtonChooseLibClicked()
{
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	SelectLibraryDialog	D(GetLayersBase());
	int	Ret=D.exec();
	if(Ret==QDialog::Accepted){
		if(GetParamGlobal()->CommonOperationInAllPhases==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				DataInPhase[phase].LibID=D.SelectedLibID;
			}
		}
		else{
			DataInPhase[CurrentPhase].LibID=D.SelectedLibID;
		}
	}
	else if(Ret==3){
		if(GetParamGlobal()->CommonOperationInAllPhases==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				DataInPhase[phase].LibID=-1;
			}
		}
		else{
			DataInPhase[CurrentPhase].LibID=-1;
		}
	}
	SetComboBLayerType();
}

QString		GerberLayerListOnScreen::GetLibName(void)
{
	if(FormParent->GetGerberFastBase()->GetLibraryContainer()!=NULL){
		return FormParent->GetGerberFastBase()->GetLibraryContainer()->GetLibraryName(GetLibID());
	}
	return /**/"";
}

void	GerberLayerListOnScreen::mousePressEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton){
         QDrag *drag = new QDrag(this);
         QMimeData *mimeData = new QMimeData;

         mimeData->setText(EditFileName.text());
         drag->setMimeData(mimeData);

         Qt::DropAction dropAction = drag->exec();
	}
}

void	GerberLayerListOnScreen::mouseReleaseEvent ( QMouseEvent * event )
{
	if(event->button()==Qt::RightButton){
		QMenu	Menu(this);
		Menu.addAction (LangSolver.GetString(PropertyGerberFastLayer_LS,LID_0)/*"Select line"*/			, this, SLOT(SlotSelectLine()));
		Menu.addSeparator();
		Menu.addAction (LangSolver.GetString(PropertyGerberFastLayer_LS,LID_70)/*"Remove line"*/			, this, SLOT(SlotRemoveLine()));
		Menu.addAction (LangSolver.GetString(PropertyGerberFastLayer_LS,LID_71)/*"Swap to next line"*/		, this, SLOT(SlotSwapNext()));
		Menu.addAction (LangSolver.GetString(PropertyGerberFastLayer_LS,LID_100)/*"Duplicate line"*/		, this, SLOT(SlotDuplicate()));
		Menu.addAction (LangSolver.GetString(PropertyGerberFastLayer_LS,LID_101)/*"Add empty layer"*/		, this, SLOT(SlotAddLayer()));
		QPoint	Q=mapToGlobal(event->pos());
		Menu.exec(Q);
	}
}

void	GerberLayerListOnScreen::SlotSelectLine()
{
	emit	SignalSelectLine(FileLayerNo);
}

void	GerberLayerListOnScreen::SlotRemoveLine()
{
	emit	SignalRemoveLine(FileLayerNo);
}

void	GerberLayerListOnScreen::SlotSwapNext()
{
	emit	SignalSwapNext(FileLayerNo);
}
void	GerberLayerListOnScreen::SlotDuplicate()
{
	emit	SignalDuplicateLine(FileLayerNo);
}

void	GerberLayerListOnScreen::SlotAddLayer()
{
	emit	SignalAddLayer(FileLayerNo);
}

QColor	GerberLayerListOnScreen::GetColor(void)
{
	return ButtonSelected.pressedColor();
}
void		GerberLayerListOnScreen::SetEmpty(void)
{
	EditFileName.setText(/**/"Added Layer");
	EditRemark.setText(/**/"Added by manual");
}

bool		GerberLayerListOnScreen::IsValidLine(void)
{
	if(EditFileName.text().isEmpty()==false || GetEntryPoint()->IsMasterPC()==false)
		return true;
	return false;
}

QString		GerberLayerListOnScreen::GetTypeName(void)
{
	return EditLibName.text();
}

QString		GerberLayerListOnScreen::GetFileName(void)
{
	return EditFileName.text();
}

bool		GerberLayerListOnScreen::IsOperational(void)
{
	return CheckBoxOperation.isChecked();
}
void		GerberLayerListOnScreen::SetOperational(bool b)
{
	CheckBoxOperation.setChecked(b);
}
void		GerberLayerListOnScreen::SetSelection(bool b)
{
	ButtonSelected.setChecked(b);
	SlotSelectedButtonClicked();
}
bool	GerberLayerListOnScreen::SaveContent(QIODevice *f)
{
	if(::Save(f,FileLayerNo)==false)
		return false;
	/*
	if(::Save(f,LibID)==false)
		return false;
	QString	FileName=EditFileName.text();
	if(::Save(f,FileName)==false)
		return false;
	QString	Remark=EditRemark.text();
	if(::Save(f,Remark)==false)
		return false;
	*/
	int	Ver=-99999999;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,AllocatedPhaseCount)==false)
		return false;
	for(int i=0;i<AllocatedPhaseCount;i++){
		DataInPhase[i].Save(f);
	}

	return true;
}
bool	GerberLayerListOnScreen::LoadContent(QIODevice *f)
{
	if(::Load(f,FileLayerNo)==false)
		return false;
	int	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(Ver!=-99999999){
		DataInPhase[0].LibID=Ver;

		QString	FileName;
		if(::Load(f,FileName)==false)
			return false;
		EditFileName.setText(FileName);
			
		QString	Remark;
		if(::Load(f,Remark)==false)
			return false;
		EditRemark.setText(Remark);
	}
	else{
		int	iAllocatedPhaseCount;
		if(::Load(f,iAllocatedPhaseCount)==false)
			return false;
		for(int i=0;i<iAllocatedPhaseCount && i<AllocatedPhaseCount;i++){
			if(DataInPhase[i].Load(f)==false){
				return false;
			}
		}
		for(int i=AllocatedPhaseCount;i<iAllocatedPhaseCount;i++){
			ScreenDataInPhase	Dummy;
			if(Dummy.Load(f)==false){
				return false;
			}
		}
		StoreToWindow();
	}
	
	return true;
}
//======================================================================================================

GerberCompositeLayerListOnScreen::ScreenDataInPhase::ScreenDataInPhase(void)
{
	CompositeID	=-1;
	Selected	=false;
	Operation	=false;
}

GerberCompositeLayerListOnScreen::ScreenDataInPhase	&GerberCompositeLayerListOnScreen::ScreenDataInPhase::operator=(GerberCompositeLayerListOnScreen::ScreenDataInPhase &src)
{
	CompositeID	=src.CompositeID;
	Selected	=src.Selected;
	Operation	=src.Operation;
	Remark		=src.Remark;
	return *this;
}

bool	GerberCompositeLayerListOnScreen::ScreenDataInPhase::Save(QIODevice *f)
{
	if(::Save(f,CompositeID)==false)
		return false;
	if(::Save(f,Selected)==false)
		return false;
	if(::Save(f,Operation)==false)
		return false;
	if(::Save(f,Remark)==false)
		return false;
	return true;
}
bool	GerberCompositeLayerListOnScreen::ScreenDataInPhase::Load(QIODevice *f)
{
	if(::Load(f,CompositeID)==false)
		return false;
	if(::Load(f,Selected)==false)
		return false;
	if(::Load(f,Operation)==false)
		return false;
	if(::Load(f,Remark)==false)
		return false;
	return true;
}
//===============================================================================================
GerberCompositeLayerListOnScreen::GerberCompositeLayerListOnScreen(int layerNo,PropertyGerberFastForm *formbase ,QWidget *parent)
:GerberInLayerBase(parent)
,ServiceForLayers(formbase->GetLayersBase())
,FormParent(formbase)
{
	LayerNo	=layerNo;
	AllocatedPhaseCount	=GetLayersBase()->GetPhaseNumb()+5;
	DataInPhase			=new ScreenDataInPhase[AllocatedPhaseCount];
	LastCurrentPhase	=0;

	ButtonSelected		.setParent(this);
	ButtonOperation		.setParent(this);
	ComboBComposite		.setParent(this);
	EditRemark			.setParent(this);

	ButtonSelected.setAutoExclusive(true);
	ButtonSelected.setCheckable(true);
	ButtonSelected.setAutoRaise(true);
	ButtonSelected.setColor(FormParent->GetLayerColor(layerNo));
	ButtonOperation.setAutoExclusive(false);
	ButtonOperation.setCheckable(true);
	ButtonOperation.setChecked(true);

	connect(&ButtonSelected		,SIGNAL(ClickRight())					,this,SLOT(SlotSelectedButtonRightClicked()));
	connect(&ButtonSelected		,SIGNAL(clicked())						,this,SLOT(SlotSelectedButtonClicked()));
	connect(&ButtonOperation	,SIGNAL(clicked())						,this,SLOT(SlotSelectedOperationalButtonClicked()));
	connect(&ComboBComposite	,SIGNAL(currentIndexChanged (int))		,this,SLOT(CompositeIndexChanged (int)));
	connect(&EditRemark			,SIGNAL(textChanged (const QString &))	,this,SLOT(EditFilenameChanged(const QString &)));

	SignalEnabled=true;
	ComboBComposite.clear();

	setAutoFillBackground(true);
	QPalette	P=palette();
	if((layerNo&1)==0)
		P.setColor(QPalette::Window,Qt::lightGray);
	else
		P.setColor(QPalette::Window,Qt::darkGray);
	setPalette(P);
}

GerberCompositeLayerListOnScreen::~GerberCompositeLayerListOnScreen(void)
{
	if(DataInPhase!=NULL){
		delete	[]DataInPhase;
		DataInPhase=NULL;
	}
}

int	GerberCompositeLayerListOnScreen::ShowPosition(int Y)
{
	int	TopGap=3;
	int	ItemHeight=20;
	int	LineHeight=ItemHeight+TopGap*2+TopGap;
	int	X=1;
	ButtonSelected		.move(X,TopGap);
	ButtonSelected		.resize(24,ItemHeight);
	X+=24;
	X+=4;
	ButtonOperation		.move(X,TopGap);
	ButtonOperation		.resize(16,ItemHeight);
	X+=16;
	X+=4;
	ComboBComposite		.move(X,TopGap);
	ComboBComposite		.resize(270,ItemHeight);
	X+=200;
	X+=4;

	X=49;
	EditRemark			.move(X,LineHeight);
	EditRemark			.resize(300,ItemHeight);
	X+=300;
	X+=4;

	PosY=Y;
	move(0,Y);
	int	YLen=(ItemHeight+TopGap*2)*2;
	if(parentWidget()!=NULL){
		resize((parentWidget())->width(),YLen);
	}
	return YLen;
}
void	GerberCompositeLayerListOnScreen::Resize(void)
{
	int	TopGap=3;
	int	ItemHeight=20;
	int	YLen=(ItemHeight + TopGap * 2) * 2;
	if(parentWidget() != NULL) {
		resize((parentWidget())->width(), YLen);
	}
}

void	GerberCompositeLayerListOnScreen::resizeEvent(QResizeEvent *event)
{
	int	ItemHeight=20;
	int	W=width();

	ComboBComposite	.resize(W-49-4-32, ItemHeight);
	EditRemark		.resize(W-49-4-32, ItemHeight);
}
void	GerberCompositeLayerListOnScreen::SlotSelectedButtonClicked()
{
	emit	ClickedSelected(LayerNo);
}
void	GerberCompositeLayerListOnScreen::SlotSelectedButtonRightClicked(void)
{
	QColor Col=QColorDialog::getColor ( ButtonSelected.color());
	SetColor(Col);
}

void		GerberCompositeLayerListOnScreen::SetColor(QColor &Col)
{
	if(Col.isValid()==true){
		ButtonSelected.setColor(Col);
		emit ChangedColor(LayerNo ,Col);
	}
}

void	GerberCompositeLayerListOnScreen::SlotSelectedOperationalButtonClicked()
{
	emit	DataChanged(LayerNo); 
}

void	GerberCompositeLayerListOnScreen::CompositeIndexChanged (int)
{
	if(SignalEnabled==true){
		emit	DataChanged(LayerNo); 
	}
}

void	GerberCompositeLayerListOnScreen::StoreFromWindow(void)
{
	//DataInPhase[LastCurrentPhase].LibID		=ui->EditLibID.();
	DataInPhase[LastCurrentPhase].Selected	=ButtonSelected.isChecked();
	DataInPhase[LastCurrentPhase].Operation	=ButtonOperation.isChecked();
	DataInPhase[LastCurrentPhase].Remark	=EditRemark.text();
	int	r=ComboBComposite.currentIndex();
	if(r>=0)
		DataInPhase[LastCurrentPhase].CompositeID	=ComboBComposite.itemData(r).toInt();
	else
		DataInPhase[LastCurrentPhase].CompositeID	=-1;

}
void	GerberCompositeLayerListOnScreen::StoreToWindow(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	ButtonSelected		.setChecked(DataInPhase[CurrentPhase].Selected);
	ButtonOperation	.setChecked(DataInPhase[CurrentPhase].Operation);
	EditRemark.setText(DataInPhase[CurrentPhase].Remark);

	ComboBComposite.setUpdatesEnabled(false);
	SignalEnabled=false;
	for(int i=0;i<ComboBComposite.count();i++){
		if(ComboBComposite.itemData(i).toInt()==DataInPhase[CurrentPhase].CompositeID){
			ComboBComposite.setCurrentIndex(i);
			break;
		}
	}
	SignalEnabled=true;
	ComboBComposite.setUpdatesEnabled(true);

	LastCurrentPhase=CurrentPhase;
	ReEntrant=false;
}

/*
void	GerberCompositeLayerListOnScreen::SetData(GerberCompositeLayer &Data)
{
	ButtonSelected.setColor(Data.LayerColor);
	ButtonSelected.setText(QString::number(LayerNo));
	int	Index=ComboBComposite.findData((int)Data.CompositeIndexID);
	ComboBComposite.setCurrentIndex(Index);
	EditRemark.setText(Data.Remark);
}
void	GerberCompositeLayerListOnScreen::GetData(GerberCompositeLayer &Data)
{
	Data.LayerColor	=ButtonSelected.color();
	int	r=ComboBComposite.currentIndex();
	if(r>=0){
		int	d=ComboBComposite.itemData(r).toInt();
		Data.CompositeIndexID	=d;
	}
	else{
		Data.CompositeIndexID	=-1;
	}
	Data.Remark				=EditRemark.text();
	Data.Operational		=ButtonOperation.isChecked();
}
*/
QString		GerberCompositeLayerListOnScreen::GetLibName(void)
{
	int	r=ComboBComposite.currentIndex()-1;
	if(r>=0){
		GerberCompositeDefLayer	*a=FormParent->GetGerberFastBase()->CompositeDef[r];
		if(a!=NULL){
			if(FormParent->GetGerberFastBase()->GetLibraryContainer()!=NULL){
				return FormParent->GetGerberFastBase()->GetLibraryContainer()->GetLibraryName(a->LibID);
			}
			return /**/"";
		}
	}
	return /**/"----";
}
QColor	GerberCompositeLayerListOnScreen::GetColor(void)
{
	return ButtonSelected.pressedColor();
}
	
bool		GerberCompositeLayerListOnScreen::IsValidLine(void)
{
	if(ComboBComposite.currentIndex()<0)
		return false;
	return true;
}

QString		GerberCompositeLayerListOnScreen::GetCompositeName(void)
{
	int	Index=ComboBComposite.currentIndex();
	if(Index>=1){
		int	CompositeID=ComboBComposite.itemData(Index).toInt();
		if(CompositeID>=0){
			GerberCompositeDefLayer	*a=FormParent->GetGerberFastBase()->CompositeDef.Search(CompositeID);
			if(a!=NULL){
				return a->Name;
			}
		}
	}
	return /**/"";
}
bool		GerberCompositeLayerListOnScreen::IsOperational(void)
{
	return ButtonOperation.isChecked();
}
void		GerberCompositeLayerListOnScreen::SetOperational(bool b)
{
	ButtonOperation.setChecked(b);
}
bool	GerberCompositeLayerListOnScreen::SaveContent(QIODevice *f)
{
	int	Ver=-9998000;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LayerNo)==false)
		return false;
	QString	ComboBCompositeStr=ComboBComposite.currentText();
	if(::Save(f,ComboBCompositeStr)==false)
		return false;
	QString	Remark=EditRemark.text();
	if(::Save(f,Remark)==false)
		return false;
	if(::Save(f,AllocatedPhaseCount)==false)
		return false;
	for(int i=0;i<AllocatedPhaseCount;i++){
		DataInPhase[i].Save(f);
	}
	return true;

}
bool	GerberCompositeLayerListOnScreen::LoadContent(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(Ver>=-1){
		LayerNo=Ver;
		QString	ComboBCompositeStr;
		if(::Load(f,ComboBCompositeStr)==false)
			return false;
		for(int i=0;i<ComboBComposite.count();i++){
			if(ComboBComposite.itemText(i)==ComboBCompositeStr){
				ComboBComposite.setCurrentIndex(i);
				break;
			}
		}

		QString	Remark;
		if(::Load(f,Remark)==false)
			return false;
		EditRemark.setText(Remark);
	}
	else if(Ver==-9998000){
		int		iLayerNo;
		if(::Load(f,iLayerNo)==false)
			return false;
		QString	ComboBCompositeStr;
		if(::Load(f,ComboBCompositeStr)==false)
			return false;
		for(int i=0;i<ComboBComposite.count();i++){
			if(ComboBComposite.itemText(i)==ComboBCompositeStr){
				ComboBComposite.setCurrentIndex(i);
				break;
			}
		}

		QString	Remark;
		if(::Load(f,Remark)==false)
			return false;

		int	iAllocatedPhaseCount;
		if(::Load(f,iAllocatedPhaseCount)==false)
			return false;
		for(int i=0;i<iAllocatedPhaseCount && i<AllocatedPhaseCount;i++){
			if(DataInPhase[i].Load(f)==false){
				return false;
			}
		}
		for(int i=AllocatedPhaseCount;i<iAllocatedPhaseCount;i++){
			ScreenDataInPhase	Dummy;
			if(Dummy.Load(f)==false){
				return false;
			}
		}
		StoreToWindow();
	}
	else{
		int		iLayerNo;
		if(::Load(f,iLayerNo)==false)
			return false;
		QString	ComboBCompositeStr;
		if(::Load(f,ComboBCompositeStr)==false)
			return false;
		for(int i=0;i<ComboBComposite.count();i++){
			if(ComboBComposite.itemText(i)==ComboBCompositeStr){
				ComboBComposite.setCurrentIndex(i);
				break;
			}
		}

		QString	Remark;
		if(::Load(f,Remark)==false)
			return false;

		int	iAllocatedPhaseCount=AllocatedPhaseCount;
		//if(::Load(f,iAllocatedPhaseCount)==false)
		//	return false;
		for(int i=0;i<iAllocatedPhaseCount && i<AllocatedPhaseCount;i++){
			if(DataInPhase[i].Load(f)==false){
				return false;
			}
		}
		for(int i=AllocatedPhaseCount;i<iAllocatedPhaseCount;i++){
			ScreenDataInPhase	Dummy;
			if(Dummy.Load(f)==false){
				return false;
			}
		}
		StoreToWindow();
	}
	return true;
}

void	GerberCompositeLayerListOnScreen::EditFilenameChanged(const QString &str)
{
	if(SignalEnabled==true){
		emit	DataChanged(LayerNo);
	}
}

//===========================================================================================
AutoMatchShiftableLayerOnScreen::AutoMatchShiftableLayerOnScreen(int layerNo,PropertyGerberFastForm *formbase ,QWidget *parent)
:QWidget(parent)
,ServiceForLayers(formbase->GetLayersBase())
,FormParent(formbase)
{
	LayerNo	=layerNo;
	ButtonOperation		.setParent(this);
	BLayerType			.setParent(this);
	EditName			.setParent(this);

	ButtonOperation.setAutoExclusive(false);
	ButtonOperation.setCheckable(true);
	ButtonOperation.setChecked(false);

	setAutoFillBackground(true);
	QPalette	P=palette();
	if((layerNo&1)==0)
		P.setColor(QPalette::Window,Qt::lightGray);
	else
		P.setColor(QPalette::Window,Qt::darkGray);
	setPalette(P);
}
int	AutoMatchShiftableLayerOnScreen::ShowPosition(int Y)
{
	int	TopGap=3;
	int	ItemHeight=20;

	int	X=1;
	ButtonOperation		.move(X,TopGap);
	ButtonOperation		.resize(24,ItemHeight);
	X+=24;
	X+=2;
	BLayerType			.move(X,TopGap);
	BLayerType			.resize(100,ItemHeight);
	X+=100;
	X+=4;
	EditName			.move(X,TopGap);
	EditName			.resize(240,ItemHeight);
	X+=240;
	move(0,Y);
	int	YLen=(ItemHeight+TopGap*2);
	if(parentWidget()!=NULL){
		resize((parentWidget())->width(),YLen);
	}
	return YLen;
}

bool	AutoMatchShiftableLayerOnScreen::SaveContent(QIODevice *f)
{
	bool	Check=ButtonOperation.isChecked();
	if(::Save(f,Check)==false)
		return false;
	return true;
}

bool	AutoMatchShiftableLayerOnScreen::LoadContent(QIODevice *f)
{
	bool	Check;
	if(::Load(f,Check)==false)
		return false;
	ButtonOperation.setChecked(Check);
	return true;
}

