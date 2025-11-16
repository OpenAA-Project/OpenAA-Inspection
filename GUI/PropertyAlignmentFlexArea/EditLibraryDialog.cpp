#include "EditLibraryDialogResource.h"
#include "EditLibraryDialog.h"
#include "ui_EditLibraryDialog.h"
#include <QMessageBox>
#include <QDrag>
#include <QMimeData>
#include "XGeneralDialog.h"

LibListWidget::LibListWidget(void)
	:QTableWidget(NULL)
{
}
LibListWidget::LibListWidget(QWidget *obj)
	:QTableWidget(obj)
{
	Parent=(EditLibraryDialog*)obj;
}

void	LibListWidget::mouseMoveEvent ( QMouseEvent *event )
{
     if (!(event->buttons() & Qt::LeftButton))
         return;

     QDrag *drag = new QDrag(this);
     QMimeData *mimeData = new QMimeData;

     mimeData->setData(/**/"LibID", 0);
     drag->setMimeData(mimeData);

     //Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
	 drag->exec();
}
void	LibListWidget::mousePressEvent ( QMouseEvent *event )
{
	if (event->button() == Qt::LeftButton)
		dragStartPosition = event->pos();
	Parent->ShowCurrentList();
	QTableWidget::mousePressEvent ( event );
}

//==========================================================================================

EditLibraryDialog::EditLibraryDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::EditLibraryDialog)
{
    ui->setupUi(this);

	LangSolver.SetUI(this);
	
	bool	Ret;

	LibFolderID =-1;
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	LLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	LibListW = new LibListWidget(this);
	LibListW->setParent(this);
	LibListW->setEnabled(true);
	LibListW->setObjectName(QString::fromUtf8(/**/"tableWidgetLibListW"));
	LibListW->setGeometry(ui->tableWidgetLibList->geometry());
	LibListW->setColumnCount(ui->tableWidgetLibList->columnCount());
	LibListW->setColumnWidth ( 0, 32);
	LibListW->setColumnWidth ( 1, 120);
	LibListW->setDragEnabled(true);
	LibListW->setDragDropOverwriteMode(true);
	LibListW->setSelectionMode(QAbstractItemView::SingleSelection);
	LibListW->setSelectionBehavior(QAbstractItemView::SelectRows);
	LibListW->setDragDropMode(QAbstractItemView::DragDrop);
    QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
    LibListW->setHorizontalHeaderItem(0, __qtablewidgetitem);
    QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
    LibListW->setHorizontalHeaderItem(1, __qtablewidgetitem1);
	LibListW->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui->frameLibFolder);
	Ret=(connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString))))?true:false;
	Ret=(connect(pLibFolderForm,SIGNAL(SignalDrop(int ,int , QWidget *)),this,SLOT(SlotDrop(int ,int , QWidget *))))?true:false;
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	QStringList	HeaderList;
	HeaderList.append(LangSolver.GetString(EditLibraryDialog_LS,LID_1)/*"ID"*/);
	HeaderList.append(LangSolver.GetString(EditLibraryDialog_LS,LID_14)/*"Name"*/);
	LibListW->setHorizontalHeaderLabels(HeaderList);
	Ret=connect(LibListW,SIGNAL(clicked(const QModelIndex &)),this,SLOT(on_tableWidgetLibList_clicked(const QModelIndex &)));
	if(Ret==true){
		delete	ui->tableWidgetLibList;
		ui->tableWidgetLibList=NULL;
	}
	int	Page=0;
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->framePickLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerPickButtons.append(LayerButton);
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		QToolButton	*LayerButton=new QToolButton(ui->frameGenLayer);
		LayerButton->move(Layer*90,0);
		LayerButton->resize(88,20);
		LayerButton->setCheckable(true);
		LayerButton->setAutoExclusive(true);
		LayerButton->setText(GetParamGlobal()->GetLayerName(Layer));
		QPalette	PL=LayerButton->palette();
		PL.setColor(QPalette::Button,GetParamGlobal()->GetOneGraphLayerColor(Layer));
		LayerButton->setPalette(PL);
		LayerGenButtons.append(LayerButton);
	}
	ui->tabWidget->setCurrentIndex(0);

	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
	InstallOperationLog(this);
}

EditLibraryDialog::~EditLibraryDialog()
{
    delete ui;
}
AlignmentFlexAreaBase	*EditLibraryDialog::GetAlignmentFlexAreaBase(void)
{
	return (AlignmentFlexAreaBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
}
void	EditLibraryDialog::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	LibListW->setRowCount(0);
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		CmdGetAlignmentFlexAreaLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		LibListW->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=LibListW->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				LibListW->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=LibListW->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				LibListW->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
void	EditLibraryDialog::Initial(AlgorithmBase *InstBase)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);
}

void EditLibraryDialog::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	ShowCurrentList();
}

void EditLibraryDialog::ShowCurrentList(void)
{
	int	r=LibListW->currentRow();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		LLib->SetLibID(a->GetLibID());

		CmdLoadAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
				ui->ButtonLibSave	->setEnabled(true);
				ui->ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,/**/"Library error"
											,/**/"Not loaded this library record");
			}
		}
	}
}

void EditLibraryDialog::on_ButtonLibNew_clicked()
{
	if(LLib==NULL)
		return;
	LLib->Reset();
	CmdClearAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*LLib);
	ui->ButtonLibSave	->setEnabled(false);
	ui->ButtonLibDelete	->setEnabled(false);
}

void EditLibraryDialog::on_ButtonLibDelete_clicked()
{
	if(LLib==NULL)
		return;
	if(LLib->GetLibID()<0)
		return;
	QString  msg=QString(/**/"Delete OK?");
	int	ret=QMessageBox::question(NULL, /**/"Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAlignmentFlexAreaLibraryPacket 	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditLibraryDialog::on_ButtonLibSaveNew_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);

	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	LLib->SetLibFolderID(LibFolderID);
	CmdInsertAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
	Packet.Point=LLib;
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*LLib);
		ui->ButtonLibSave	->setEnabled(true);
		ui->ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_ButtonLibSave_clicked()
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()<0){
		LLib->SetLibFolderID(LibFolderID);

		CmdInsertAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*LLib);
			ui->ButtonLibSave	->setEnabled(true);
			ui->ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditLibraryDialog::on_pushButtonClose_clicked()
{
	close();
}

void	EditLibraryDialog::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	AlignmentFlexAreaLibrary	*ALib=dynamic_cast<AlignmentFlexAreaLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	ui->EditPickupL				->setValue	(ALib->PickupL			);
	ui->EditPickupH				->setValue	(ALib->PickupH			);
	ui->EditMinAreaSize			->setValue	(ALib->MinAreaSize		);
	ui->EditMaxAreaSize			->setValue	(ALib->MaxAreaSize		);
	ui->EditMinAreaDots			->setValue	(ALib->MinAreaDots		);
	ui->EditMaxAreaDots			->setValue	(ALib->MaxAreaDots		);
	ui->EditExpansionDot		->setValue	(ALib->ExpansionDot		);
	ui->EditLimitSize			->setValue	(ALib->LimitSize		);
	ui->checkBoxPickUpEdge		->setChecked(ALib->PickUpEdge		);
	ui->EditPickUpEdgeMinDiff	->setValue	(ALib->PickUpEdgeMinDiff);
	ui->spinBoxGlobalSearchDot	->setValue	(ALib->GlobalSearchDot	);
	ui->EditSearchDot			->setValue	(ALib->SearchDot		);
	ui->EditGroupAreaSize		->setValue	(ALib->GroupAreaSize	);
	ui->checkBoxKeepBW			->setChecked(ALib->KeepBW			);
	ui->doubleSpinBoxCloserRate	->setValue	(ALib->CloserRate		);
	ui->EditSmallSearch			->setValue	(ALib->SmallSearch		);
	ui->EditMaxCoeffInNeighbor	->setValue	(ALib->MaxCoeffInNeighbor);

	switch(ALib->AdaptedPriority){
		case -1:	ui->comboBoxAdaptedPriority->setCurrentIndex(0);	break;
		case 4:		ui->comboBoxAdaptedPriority->setCurrentIndex(1);	break;
		case 1:		ui->comboBoxAdaptedPriority->setCurrentIndex(2);	break;
		case 2:		ui->comboBoxAdaptedPriority->setCurrentIndex(3);	break;
		case 3:		ui->comboBoxAdaptedPriority->setCurrentIndex(4);	break;
	}
	int	Page=0;
	for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerPickButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedPickLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerPickButtons[Layer]->setChecked(false);
		}
	}
	for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
		int	Layer=a->GetValue();
		if(0<=Layer && Layer<GetLayerNumb(Page)){
			LayerGenButtons[Layer]->setChecked(true);
		}
	}
	for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
		bool	Found=false;
		for(IntClass *a=data.GetAdaptedGenLayers().GetFirst();a!=NULL;a=a->GetNext()){
			if(Layer==a->GetValue()){
				Found=true;
				break;
			}
		}
		if(Found==false){
			LayerGenButtons[Layer]->setChecked(false);
		}
	}
}

void	EditLibraryDialog::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	AlignmentFlexAreaLibrary	*d=dynamic_cast<AlignmentFlexAreaLibrary *>(data.GetLibrary());
	data.SetLibName(ui->EditLibName	->text());

	d->PickupL			=ui->EditPickupL			->value();
	d->PickupH			=ui->EditPickupH			->value();
	d->MinAreaSize		=ui->EditMinAreaSize		->value();
	d->MaxAreaSize		=ui->EditMaxAreaSize		->value();
	d->MinAreaDots		=ui->EditMinAreaDots		->value();
	d->MaxAreaDots		=ui->EditMaxAreaDots		->value();
	d->ExpansionDot		=ui->EditExpansionDot		->value();
	d->LimitSize		=ui->EditLimitSize			->value();
	d->PickUpEdge		=ui->checkBoxPickUpEdge		->isChecked();
	d->PickUpEdgeMinDiff=ui->EditPickUpEdgeMinDiff	->value();
	d->GlobalSearchDot	=ui->spinBoxGlobalSearchDot	->value();
	d->SearchDot		=ui->EditSearchDot			->value();
	d->GroupAreaSize	=ui->EditGroupAreaSize		->value();
	d->KeepBW			=ui->checkBoxKeepBW			->isChecked();
	d->CloserRate		=ui->doubleSpinBoxCloserRate->value();
	d->SmallSearch		=ui->EditSmallSearch		->value();
	d->MaxCoeffInNeighbor	=ui->EditMaxCoeffInNeighbor	->value();

	switch(ui->comboBoxAdaptedPriority->currentIndex()){
		case 0:	d->AdaptedPriority	=-1;	break;
		case 1:	d->AdaptedPriority	=4;		break;
		case 2:	d->AdaptedPriority	=1;		break;
		case 3:	d->AdaptedPriority	=2;		break;
		case 4:	d->AdaptedPriority	=3;		break;
	}

	IntList	LayersPickList;
	for(int Layer=0;Layer<LayerPickButtons.count();Layer++){
		if(LayerPickButtons[Layer]->isChecked()==true){
			LayersPickList.Add(Layer);
		}
	}
	data.SetAdaptedPickLayers(LayersPickList);

	IntList	LayersGenList;
	for(int Layer=0;Layer<LayerGenButtons.count();Layer++){
		if(LayerGenButtons[Layer]->isChecked()==true){
			LayersGenList.Add(Layer);
		}
	}
	data.SetAdaptedGenLayers(LayersGenList);
}

void	EditLibraryDialog::SlotDrop(int FolderParentID ,int LibFolderID , QWidget *w)
{
	if(LLib==NULL)
		return;
	GetLibraryFromWindow(*LLib);
	if(LLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL
			, /**/"Warning"
			, /**/"No Library Name"
			, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(LLib->GetLibID()>=0){
		LLib->SetLibFolderID(LibFolderID);
		CmdUpdateAlignmentFlexAreaLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}
