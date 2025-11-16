#include "CopyMultiple.h"
#include <QFileDialog>
#include "IndicatorWindow.h"
#include "XGeneralFunc.h"

char	*CopyMultiple::DefaultFileName="CopyMultiple.dat";


FolderListButton::FolderListButton(QWidget *parent): QPushButton(parent)
{
	connect(this,SIGNAL(clicked()),this,SLOT(ButtonClick()));
}
FolderListButton::~FolderListButton()
{
}

void FolderListButton::ButtonClick()
{
#if	defined(ModeEditGUI)
	ImageDialog	D(SImage);
	D.exec();
	SImage=D.SImage;
#endif
}

DestinationList::DestinationList(CopyMultiple *parent)
	: WMultiGrid(NULL)
{
	Parent=parent;
}

void	DestinationList::ChangeValue(int row ,int col,const QVariant &value)
{
	if(Parent!=NULL){
		int	N=Parent->Data.Destinations.count();
		if(N>row){
			if(col==0){
				Parent->Data.Destinations[row]=value.toString();
			}
		}
		else{
			Parent->Data.Destinations.append(value.toString());
		}
	}
}

void	DestinationList::GetValue(int row ,int col,QVariant &value)
{
	if(Parent!=NULL){
		int	N=Parent->Data.Destinations.count();
		if(N>row){
			if(col==0){
				value=Parent->Data.Destinations[row];
			}
		}
	}
}

//=====================================================================================

CopyMultiple::CopyMultiple(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),dGrid(this)
{
	ui.setupUi(this);

	ui.pushButtonStopCopy->setVisible(false);

	Indicator=NULL;
	int	dGridCount=100;
	dGrid.setParent(ui.frameDestination);
	dGrid.SetRowCount(dGridCount);
	dGrid.SetColumnCount(2);
	dGrid.move(0,0);
	dGrid.resize(ui.frameDestination->width(),ui.frameDestination->height());
	for(int r=0;r<dGridCount;r++){
		WMultiGrid::CellData *L=dGrid.GetData(r ,0);
		L->Value	=QString("");
		L->CType	=WMultiGrid::_CType_LineEdit;
		L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;

		WMultiGrid::CellData *M=dGrid.GetData(r ,1);
		M->Value	=QString("...");
		M->CType	=WMultiGrid::_CType_PushButton;
	}
	dGrid.InitialGrid();
	dGrid.setColumnWidth(0,370);
	dGrid.SetTopHeader(0, "Destination path");
	dGrid.setColumnWidth(1,32);
	dGrid.SetTopHeader(1, "");

	connect(&dGrid,SIGNAL(SignalClickedXYButton( int ,int )),this,SLOT(SlotClickedXYButton( int ,int )));
	connect(&Data,SIGNAL(SignalFinishCopy()),this,SLOT(SlotFinishCopy()));
}

CopyMultiple::~CopyMultiple()
{

}

void CopyMultiple::showEvent ( QShowEvent * event )
{
	QString	filename=QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefaultFileName);
	QFile	File(filename);
	if(File.open(QIODevice::ReadOnly)==true){
		Data.Load(&File);
		ui.lineEditSourcePath->setText(Data.SourcePath);
		StoreFilterToWindow();
	}
	dGrid.ShowGrid();
}

void CopyMultiple::closeEvent ( QCloseEvent * event )
{
	QString	filename=QCoreApplication::applicationDirPath ()+::GetSeparator()+QString(DefaultFileName);
	QFile	File(filename);
	if(File.open(QIODevice::WriteOnly)==true){
		Data.SourcePath=ui.lineEditSourcePath->text();
		LoadFilterFromWindow();
		Data.Save(&File);
	}
	if(Indicator!=NULL){
		delete	Indicator;
		Indicator=NULL;
	}
}

void	CopyMultiple::SlotClickedXYButton( int row ,int col)
{
	int	n=Data.GetDestCount();
	if(row<(n+1)){
		QString		DirStr=QFileDialog::getExistingDirectory( 0
											, "Destination  Path"
											, QString());
		if(DirStr.isEmpty()==false){
			if(row<n){
				Data.Destinations[row]=DirStr;
			}
			else{
				Data.Destinations.append(DirStr);
			}
		}
		dGrid.ShowGrid();
	}
}

void	CopyMultiple::setDestination()
{
	dGrid.ShowGrid();
}


void CopyMultiple::on_pushButtonSourcePath_clicked()
{	
	QString		DirStr=QFileDialog::getExistingDirectory( 0
										, "Source  Path"
										, QString());
	if(DirStr.isEmpty()==false){
		ui.lineEditSourcePath->setText(DirStr);
	}
}

void CopyMultiple::on_pushButtonLoadFilter_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName ( 0
										, "Load Filter list"
										, ""
										, "Filter(*.flt);;All Files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			Data.LoadFilter(&File);
			StoreFilterToWindow();
		}
	}
}

void CopyMultiple::StoreFilterToWindow(void)
{
	int	row;
	for(row=0;row<Data.SearchFilter.count() && row<ui.tableWidgetSearchFilter->rowCount();row++){
		::SetDataToTable(ui.tableWidgetSearchFilter,0,row ,Data.SearchFilter[row],Qt::ItemIsEditable);
	}
	while(row<ui.tableWidgetSearchFilter->rowCount()){
		::SetDataToTable(ui.tableWidgetSearchFilter,0,row ,/**/"",Qt::ItemIsEditable);
		row++;
	}
	for(row=0;row<Data.ExcludedFilter.count() && row<ui.tableWidgetExcludedFilter->rowCount();row++){
		::SetDataToTable(ui.tableWidgetExcludedFilter,0,row ,Data.ExcludedFilter[row],Qt::ItemIsEditable);
	}
	while(row<ui.tableWidgetExcludedFilter->rowCount()){
		::SetDataToTable(ui.tableWidgetExcludedFilter,0,row ,/**/"",Qt::ItemIsEditable);
		row++;
	}
}

void CopyMultiple::on_pushButtonSaveFilter_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName ( 0
										, "Save Filter list"
										, ""
										, "Filter(*.flt);;All Files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			LoadFilterFromWindow();
			Data.SaveFilter(&File);
		}
	}
}

void CopyMultiple::LoadFilterFromWindow(void)
{
	Data.SearchFilter.clear();
	for(int row=0;row<ui.tableWidgetSearchFilter->rowCount();row++){
		QString	s=::GetDataToTable(ui.tableWidgetSearchFilter,0,row);
		if(s.isEmpty()==false){
			Data.SearchFilter.append(s);
		}
	}
	Data.ExcludedFilter.clear();
	for(int row=0;row<ui.tableWidgetExcludedFilter->rowCount();row++){
		QString	s=::GetDataToTable(ui.tableWidgetExcludedFilter,0,row);
		if(s.isEmpty()==false){
			Data.ExcludedFilter.append(s);
		}
	}
}

void CopyMultiple::on_pushButtonStartCopy_clicked()
{
	Data.SourcePath=ui.lineEditSourcePath->text();
	LoadFilterFromWindow();
	Data.MakeFoundList();

	if(Indicator!=NULL){
		delete	Indicator;
	}
	Indicator=new IndicatorWindow(this);
	Indicator->show();

	ui.pushButtonStopCopy->setVisible(true);
	ui.pushButtonStartCopy->setVisible(false);

	Data.StartCopy(this);
}

void	CopyMultiple::SlotFinishCopy()
{
	ui.pushButtonStartCopy->setVisible(true);
	ui.pushButtonStopCopy->setVisible(false);
}


void CopyMultiple::on_pushButtonAllFiles_clicked()
{
	ui.tableWidgetSearchFilter->clearContents();
	ui.tableWidgetSearchFilter->setItem(0,0,new QTableWidgetItem("*"));
}

void CopyMultiple::on_pushButtonForRelease_clicked()
{
	ui.tableWidgetSearchFilter->clearContents();
	QStringList FileList;
	FileList << "*.exe" << "*.dll" << "*.dat" << "*.gui" << "*.xlsx" << "*.lsn" << "*.lng" << "*.sql" << "*.fmt" 
			 << "*.pcf" << "*.msg" << "*.manifest" << "*.ini"; 
	for(int i=0;i<FileList.size();i++){
		ui.tableWidgetSearchFilter->setItem(i,0,new QTableWidgetItem(FileList.at(i)));
	}
}

void CopyMultiple::on_pushButtonAllClear_clicked()
{
	ui.tableWidgetSearchFilter->clearContents();
	ui.tableWidgetExcludedFilter->clearContents();
}

void CopyMultiple::on_pushButtonStopCopy_clicked()
{
	Data.TerminateCopy=true;
	return;
}
