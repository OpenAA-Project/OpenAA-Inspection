#include "PropertyAlignmentBlockForm.h"
#include "ui_PropertyAlignmentBlockForm.h"
#include "PropertyAlignmentBlockPacket.h"
#include "AddEditItemDialog.h"
#include "EditAlignmentBlockLibraryDialog.h"
#include "XRememberer.h"
#include "XDisplayImagePacket.h"

extern  const	char	*sRoot;
extern  const	char	*sName;

PropertyAlignmentBlockForm::PropertyAlignmentBlockForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyAlignmentBlockForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);
	LibFolderID		=-1;

	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();


	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);

	if(BBase!=NULL){
		CmdCreateTempAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	LLib->SetLibID(-1);

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}

	::SetColumnWidthInTable(ui->tableWidget ,0, 15);
	::SetColumnWidthInTable(ui->tableWidget ,1, 45);
	::SetColumnWidthInTable(ui->tableWidget ,2, 30);
}

PropertyAlignmentBlockForm::~PropertyAlignmentBlockForm()
{
    delete ui;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

AlignmentBlockBase	*PropertyAlignmentBlockForm::GetAlignmentBlockBase(void)
{
	return (AlignmentBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentBlock");
}

void	PropertyAlignmentBlockForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	PropertyAlignmentBlockForm::BuildForShow(void)
{
	ShowItemList();
}

void PropertyAlignmentBlockForm::on_pushButtonEditLibFolder_clicked()
{
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyAlignmentBlockForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyAlignmentBlockForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	if(BBase!=NULL){
		CmdGetAlignmentBlockLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}



struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
	int						Priority;
};

int	DDimFunc(const void *a ,const void *b)
{
	if(((struct AlgorithmLibraryListClass *)a)->Priority>((struct AlgorithmLibraryListClass *)b)->Priority)
		return 1;
	if(((struct AlgorithmLibraryListClass *)a)->Priority<((struct AlgorithmLibraryListClass *)b)->Priority)
		return -1;
	return 0;
}

QColor	GetTableColor(int n)
{
	switch(n&7){
		case 0 :	return QColor(255,255,0);
		case 1 :	return QColor(235,255,0);
		case 2 :	return QColor(235,235,0);
		case 3 :	return QColor(215,235,0);
		case 4 :	return QColor(215,215,0);
		case 5 :	return QColor(195,215,0);
		case 6 :	return QColor(195,195,0);
		case 7 :	return QColor(175,195,0);
	}
	return Qt::white;
}

void	PropertyAlignmentBlockForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	if(BBase!=NULL){
		CmdCreateTempAlignmentBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		if(LLib!=NULL){
			delete	LLib;
		}
		LLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			LLib->SetLibID(a->GetLibID());
			CmdLoadAlignmentBlockLibraryPacket	Packet(GetLayersBase());
			Packet.Point=LLib;
			BBase->TransmitDirectly(&Packet);
			DDim[row].Priority=((AlignmentBlockLibrary *)(LLib->GetLibrary()))->GetLibID();
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		QSort(DDim,row,sizeof(DDim[0]),DDimFunc);
		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}
	
	bool	HasChanged;
	int		LCounter=0;
	do{
		HasChanged=false;
		LCounter++;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
			AlgorithmLibraryList *b=a->GetNext();
			if(b!=NULL){
				CmdCreateTempAlignmentBlockLibraryPacket	ACreateCmd(GetLayersBase());
				CmdCreateTempAlignmentBlockLibraryPacket	BCreateCmd(GetLayersBase());
				BBase->TransmitDirectly(&ACreateCmd);
				BBase->TransmitDirectly(&BCreateCmd);

				CmdLoadAlignmentBlockLibraryPacket	ALoadLibCmd(GetLayersBase());
				CmdLoadAlignmentBlockLibraryPacket	BLoadLibCmd(GetLayersBase());
				ALoadLibCmd.Point=ACreateCmd.Point;
				ALoadLibCmd.Point->SetLibID(a->GetLibID());
				BLoadLibCmd.Point=BCreateCmd.Point;
				BLoadLibCmd.Point->SetLibID(b->GetLibID());
				BBase->TransmitDirectly(&ALoadLibCmd);
				BBase->TransmitDirectly(&BLoadLibCmd);
				AlignmentBlockLibrary	*ALib=(AlignmentBlockLibrary	*)ALoadLibCmd.Point;
				AlignmentBlockLibrary	*BLib=(AlignmentBlockLibrary	*)BLoadLibCmd.Point;
				if(ALib->GetLibID()>BLib->GetLibID()){
					delete	ALib;
					delete	BLib;
					SelectedLibList.Swap(a,b);
					HasChanged=true;
					goto	TryNext;
				}
				delete	ALib;
				delete	BLib;
			}
		}
TryNext:;
	}while(HasChanged==true && LCounter<30);

	int	row=0;
	int	CuPriority=-1;
	int	ColNum=-1;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(CuPriority!=DDim[row].Priority){
			CuPriority=DDim[row].Priority;
			ColNum++;
		}
		QColor	Col=GetTableColor(ColNum);

		QTableWidgetItem *W;
		W=ui->tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W->setBackground(Col);
		W=ui->tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
		W->setBackground(Col);
	}
}

void PropertyAlignmentBlockForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}


void PropertyAlignmentBlockForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}


void PropertyAlignmentBlockForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui->tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyAlignmentBlockForm::on_pushButtonGetBack_clicked()
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void PropertyAlignmentBlockForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyAlignmentBlockForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}


void PropertyAlignmentBlockForm::on_pushButtonEditLibrary_clicked()
{
	EditAlignmentBlockLibraryDialog	D(GetLayersBase(),this);
	D.exec();
	
	ShowLibList();
}


void PropertyAlignmentBlockForm::on_pushButtonAutoGenerate_clicked()
{
	int	Row=ui->tableWidgetGeneratedLibList->currentRow();
	if(Row<0)
		return;
	AlgorithmLibraryList	*L=SelectedLibList[Row];
	if(L==NULL)
		return;
	//AlignmentBlockBase	*BBase=GetAlignmentBlockBase();
	//
	//CmdLoadAlignmentBlockLibraryPacket	Packet(GetLayersBase());
	//LLib->SetLibID(L->GetLibID());
	//Packet.Point=LLib;
	//BBase->TransmitDirectly(&Packet);

	//AddEditItemDialog	D(GetLayersBase());
	//D.Initial(Packet.Point->GetLibrary());
	//if(D.exec()==true){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdAutoGenerateAlignmentBlock	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.LibID	=L->GetLibID()	;
			Cmd.Send(NULL,GlobalPage,0);
		}
	//}
	ShowItemList();
}

void	PropertyAlignmentBlockForm::SetTargetPage(int page)
{
	ShowItemList();
}

void PropertyAlignmentBlockForm::ShowItemList(void)
{
	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection",/**/"AlignmentBlockImagePanel",/**/"");
	if(ImagePanel!=NULL){
		int	Page=ImagePanel->GetTargetPage();
		if(0<=Page && Page<GetPageNumb()){
			BlockItems.RemoveAll();
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
			GUICmdReqAlignmentBlockItemList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			GUICmdAckAlignmentBlockItemList	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			if(RCmd.Send(GlobalPage,0,SCmd)==true){
				BlockItems+=SCmd.Items;
			}
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdReqAlignmentBlockItemList	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				GUICmdAckAlignmentBlockItemList	SCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
				if(RCmd.Send(GlobalPage,0,SCmd)==true){
					BlockItems+=SCmd.Items;
				}
			}
		}
		ui->tableWidget->setRowCount(BlockItems.GetCount());
		int	Row=0;
		for(AlignmentBlockItemList *a=BlockItems.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			::SetDataToTable(ui->tableWidget, 0, Row,QString::number(a->ItemID));
			::SetDataToTable(ui->tableWidget, 1, Row,QString("(")
													+QString::number(a->X1)
													+QString(",")
													+QString::number(a->Y1)
													+QString(")-(")
													+QString::number(a->X2)
													+QString(",")
													+QString::number(a->Y2)
													+QString(","));
			::SetDataToTable(ui->tableWidget, 2, Row,QString::number(a->ResultDx)
													+QString(",")
													+QString::number(a->ResultDy));
		}
	}
}

void PropertyAlignmentBlockForm::on_tableWidget_itemSelectionChanged()
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	int	Row=ui->tableWidget->currentRow();
	if(Row<0){
		ReEntrant=false;
		return;
	}
	AlignmentBlockItemList *L=BlockItems[Row];
	if(L==NULL){
		ReEntrant=false;
		return;
	}
	GUIFormBase	*ImagePanel=GetLayersBase()->FindByName(/**/"Inspection",/**/"AlignmentBlockImagePanel",/**/"");
	if(ImagePanel==NULL){
		ReEntrant=false;
		return;
	}
	int	Page=ImagePanel->GetTargetPage();
	if(Page>=0){
		DataInPage	*P=GetLayersBase()->GetPageData(Page);
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,L->X1+P->GetOutlineOffset()->x,L->Y1+P->GetOutlineOffset()->y
										,L->X2+P->GetOutlineOffset()->x,L->Y2+P->GetOutlineOffset()->y);
			ImagePanel->TransmitDirectly(&Cmd);

			CmdDrawImageActivate	ACmd(GetLayersBase(),Page,0,L->ItemID);
			ImagePanel->TransmitDirectly(&ACmd);
		}
	}
	ReEntrant=false;
}

