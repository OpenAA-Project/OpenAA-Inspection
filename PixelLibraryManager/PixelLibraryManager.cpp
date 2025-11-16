#include "PixelLibraryManager.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"

PixelLibraryManager::PixelLibraryManager(LayersBase *Base,QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);

	cmbPixelLibraryNameList	=NULL;
	cmbAlgorithmNameList	=NULL;
	cmbLibraryNameList		=NULL;
	cmbUniqueNameList		=NULL;
	sbPriority				=NULL;

	CreateTable();

	connect(ui.twPixelLibraryList,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(twPixelLibraryListDoubleClicked(const QModelIndex &)));
	connect(ui.twPixelLibraryList,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(twPixelLibraryListCurrentCellChanged(int,int,int,int)));

	connect(ui.pbSave		,SIGNAL(clicked()),this,SLOT(pbSaveClicked()));
	connect(ui.pbUpdate		,SIGNAL(clicked()),this,SLOT(pbUpdateClicked()));
	connect(ui.pbLoad		,SIGNAL(clicked()),this,SLOT(pbLoadClicked()));
	connect(ui.pbAddRow		,SIGNAL(clicked()),this,SLOT(pbAddRowClicked()));
	connect(ui.pbDeleteRow	,SIGNAL(clicked()),this,SLOT(pbDeleteRowClicked()));
	connect(ui.pbClose		,SIGNAL(clicked()),this,SLOT(pbCloseClicked()));
}

PixelLibraryManager::~PixelLibraryManager()
{
}

void	PixelLibraryManager::twPixelLibraryListDoubleClicked(const QModelIndex &Index)
{
	QString	Value;
	if(Index.column()==TableColHeader.indexOf(/**/"PixelLibrary")){
		CreatePixelLibraryNameList();
		if(ui.twPixelLibraryList->item(Index.row(),Index.column())!=NULL){
			Value=ui.twPixelLibraryList->item(Index.row(),Index.column())->text();
			//disconnect
			disconnect(cmbPixelLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbPixelLibraryNameListCurrentIndexChanged(int)));
			cmbPixelLibraryNameList->setCurrentIndex(cmbPixelLibraryNameList->findText(Value));
			//connect
			connect(cmbPixelLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbPixelLibraryNameListCurrentIndexChanged(int)));
		}
		ui.twPixelLibraryList->setCellWidget(Index.row(),Index.column(),cmbPixelLibraryNameList);
	}
	else if(Index.column()==TableColHeader.indexOf(/**/"Algorithm")){
		CreateAlgorithmNameList();
		if(ui.twPixelLibraryList->item(Index.row(),Index.column())!=NULL){
			Value=ui.twPixelLibraryList->item(Index.row(),Index.column())->text();
			cmbAlgorithmNameList->setCurrentIndex(cmbAlgorithmNameList->findText(Value));
		}
		ui.twPixelLibraryList->setCellWidget(Index.row(),Index.column(),cmbAlgorithmNameList);
	}
	else if(Index.column()==TableColHeader.indexOf(/**/"Library")){
		if(CreateLibraryNameList(Index.row())==false){
			return;
		}
		if(ui.twPixelLibraryList->item(Index.row(),Index.column())!=NULL){
			Value=ui.twPixelLibraryList->item(Index.row(),Index.column())->text();
			//disconnect
			disconnect(cmbLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbLibraryNameListCurrentIndexChanged(int)));
			cmbLibraryNameList->setCurrentIndex(cmbLibraryNameList->findText(Value));
			//connect
			connect(cmbLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbLibraryNameListCurrentIndexChanged(int)));
		}
		ui.twPixelLibraryList->setCellWidget(Index.row(),Index.column(),cmbLibraryNameList);
	}
	else if(Index.column()==TableColHeader.indexOf(/**/"Unique")){
		if(CreateUniqueNameList(Index.row())==false){
			return;
		}
		if(ui.twPixelLibraryList->item(Index.row(),Index.column())!=NULL){
			Value=ui.twPixelLibraryList->item(Index.row(),Index.column())->text();
			//disconnect
			disconnect(cmbUniqueNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbUniqueNameListCurrentIndexChanged(int)));
			cmbUniqueNameList->setCurrentIndex(cmbUniqueNameList->findText(Value));
			//connect
			connect(cmbUniqueNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbUniqueNameListCurrentIndexChanged(int)));
		}
		ui.twPixelLibraryList->setCellWidget(Index.row(),Index.column(),cmbUniqueNameList);
	}
	else if(Index.column()==TableColHeader.indexOf(/**/"Priority")){
		CreatePriority();
		if(ui.twPixelLibraryList->item(Index.row(),Index.column())!=NULL){
			Value=ui.twPixelLibraryList->item(Index.row(),Index.column())->text();
			sbPriority->setValue(Value.toInt());
		}
		ui.twPixelLibraryList->setCellWidget(Index.row(),Index.column(),sbPriority);
	}
	NowRow=Index.row();
}

void	PixelLibraryManager::twPixelLibraryListCurrentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn)
{
	//値のセット
	QVariant Value;
	if(previousColumn==TableColHeader.indexOf(/**/"PixelLibrary")){
		if(cmbPixelLibraryNameList==NULL){
			return;
		}
		Value=cmbPixelLibraryNameList->currentText();
		delete cmbPixelLibraryNameList;
		cmbPixelLibraryNameList=NULL;
	}
	else if(previousColumn==TableColHeader.indexOf(/**/"Algorithm")){
		if(cmbAlgorithmNameList==NULL){
			return;
		}
		//CombBoxからの取得
		Value=cmbAlgorithmNameList->currentText();
		delete cmbAlgorithmNameList;
		cmbAlgorithmNameList=NULL;
		//TableWidgetからの取得
		QTableWidgetItem *Item;
		if((Item=ui.twPixelLibraryList->item(previousRow,previousColumn))!=NULL){
			if(Value!=Item->text()){
				//Libraryの列をクリアする
				SetDataToTable(ui.twPixelLibraryList,previousRow,TableColHeader.indexOf(/**/"Library"),/**/"");
			}
		}
	}
	else if(previousColumn==TableColHeader.indexOf(/**/"Library")){
		if(cmbLibraryNameList==NULL){
			return;
		}
		Value=cmbLibraryNameList->currentText();
		delete cmbLibraryNameList;
		cmbLibraryNameList=NULL;
	}
	else if(previousColumn==TableColHeader.indexOf(/**/"Unique")){
		if(cmbUniqueNameList==NULL){
			return;
		}
		Value=cmbUniqueNameList->currentText();
		delete cmbUniqueNameList;
		cmbUniqueNameList=NULL;
	}
	else if(previousColumn==TableColHeader.indexOf(/**/"Priority")){
		if(sbPriority==NULL){
			return;
		}
		Value=sbPriority->value();
		delete sbPriority;
		sbPriority=NULL;
	}
	else{
		return;
	}
	SetDataToTable(ui.twPixelLibraryList,previousRow,previousColumn,Value);
}

void	PixelLibraryManager::cmbPixelLibraryNameListCurrentIndexChanged(int Index)
{
	SetDataToTable(ui.twPixelLibraryList,NowRow,TableColHeader.indexOf(/**/"PixelLibraryID"),PixelLibraryIDList.at(Index));
}

void	PixelLibraryManager::cmbLibraryNameListCurrentIndexChanged(int Index)
{
	SetDataToTable(ui.twPixelLibraryList,NowRow,TableColHeader.indexOf(/**/"LibraryID"),LibraryIDList.at(Index));
}

void	PixelLibraryManager::cmbUniqueNameListCurrentIndexChanged(int Index)
{
	SetDataToTable(ui.twPixelLibraryList,NowRow,TableColHeader.indexOf(/**/"UniqueID"),UniqueNameList[0].indexOf(UniqueNameList[0].at(Index)));
}

void	PixelLibraryManager::pbSaveClicked()
{
	//設定の保存
	QString SettingFilePath=QFileDialog::getSaveFileName(
							this,"Please save a setting file.",/**/"PixelLibrarySetting.dat","Pixel library setting file (*.dat)");
	if(SettingFilePath.isEmpty()){
		return;
	}

	if(SaveFile(SettingFilePath)==true){
		NowFileName=SettingFilePath;
	}
}

void	PixelLibraryManager::pbUpdateClicked()
{
	if(SaveFile(NowFileName)==true){
		QMessageBox::information(this,"information",QString("Save to %1").arg(NowFileName),QMessageBox::Ok,QMessageBox::Ok);
	}
}

void	PixelLibraryManager::pbLoadClicked()
{
	NowFileName=QFileDialog::getOpenFileName(this,"Open file name");
	if(NowFileName.isEmpty()==true){
		return;
	}
	QFile	File(NowFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&File);

		QStringList myStringList;
		int Row=0;
		while (!mystream.atEnd()){
			ui.twPixelLibraryList->setRowCount(Row+1);
			myStringList=mystream.readLine().split(',');
			if(myStringList.count()!=ui.twPixelLibraryList->columnCount()){
				QMessageBox::StandardButton Btn=QMessageBox::warning(this,"Warning","Wrong format!",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
				if(Btn==QMessageBox::Cancel){
					break;
				}
			}
			int Col;
			for(Col=0;Col<myStringList.count();Col++){
				//値のチェック
				QString Msg;
				if(CheckLoadData(Row,Col,myStringList,Msg)==false){
					QMessageBox::StandardButton Btn=QMessageBox::warning(this,"Warning",Msg,QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
					if(Btn==QMessageBox::Cancel){
						break;
					}
				}
				SetDataToTable(ui.twPixelLibraryList,Row,Col,myStringList.at(Col));
			}
			if(Col<myStringList.count()){
				break;
			}
			Row++;
		}
		File.close();
	}
}

void	PixelLibraryManager::pbAddRowClicked()
{
	QMessageBox::StandardButton Btn=QMessageBox::information(this,"Message","Do you add row?",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Cancel);
	if(Btn==QMessageBox::Yes){
		ui.twPixelLibraryList->setRowCount(ui.twPixelLibraryList->rowCount()+1);
	}
}

void	PixelLibraryManager::pbDeleteRowClicked()
{
	QMessageBox::StandardButton Btn=QMessageBox::information(this,"Message","Do you delete current row?",QMessageBox::Yes | QMessageBox::Cancel,QMessageBox::Cancel);
	if(Btn==QMessageBox::Yes){
		ui.twPixelLibraryList->removeRow(ui.twPixelLibraryList->currentRow());
	}
}

void	PixelLibraryManager::pbCloseClicked()
{
	close();
}

void	PixelLibraryManager::CreateTable()
{
	//ColHeader
	TableColHeader << /**/"PixelLibraryID" << /**/"PixelLibrary" << /**/"Algorithm" << /**/"LibraryID" << /**/"Library" << /**/"UniqueID" << /**/"Unique" << /**/"Priority";
	ui.twPixelLibraryList->setColumnCount(TableColHeader.count());
	ui.twPixelLibraryList->setHorizontalHeaderLabels(TableColHeader);
	ui.twPixelLibraryList->setFont(QFont(/**/"Helvetica",10));
	ui.twPixelLibraryList->setColumnWidth(TableColHeader.indexOf(/**/"PixelLibrary"),170);
	ui.twPixelLibraryList->setColumnWidth(TableColHeader.indexOf(/**/"Algorithm")	,170);
	ui.twPixelLibraryList->setColumnWidth(TableColHeader.indexOf(/**/"Library")		,170);
	ui.twPixelLibraryList->setColumnWidth(TableColHeader.indexOf(/**/"Unique")		,170);
	ui.twPixelLibraryList->setColumnWidth(TableColHeader.indexOf(/**/"Priority")	,70);
	ui.twPixelLibraryList->horizontalHeader()->setSectionResizeMode(TableColHeader.indexOf(/**/"PixelLibrary")	,QHeaderView::Stretch);
	ui.twPixelLibraryList->horizontalHeader()->setSectionResizeMode(TableColHeader.indexOf(/**/"Algorithm")	,QHeaderView::Stretch);
	ui.twPixelLibraryList->horizontalHeader()->setSectionResizeMode(TableColHeader.indexOf(/**/"Library")		,QHeaderView::Stretch);
	ui.twPixelLibraryList->horizontalHeader()->setSectionResizeMode(TableColHeader.indexOf(/**/"Unique")		,QHeaderView::Stretch);
	ui.twPixelLibraryList->hideColumn(TableColHeader.indexOf(/**/"PixelLibraryID"));
	ui.twPixelLibraryList->hideColumn(TableColHeader.indexOf(/**/"LibraryID"));
	ui.twPixelLibraryList->hideColumn(TableColHeader.indexOf(/**/"UniqueID"));

	//PixelLibraryの取得
	PixelLibraryIDList.clear();
	PixelLibraryNameList.clear();
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==/**/"PixelInspection"){
			AlgorithmLibraryContainer  *AL=L->GetInstance()->GetLibraryContainer();
			if(AL!=NULL){
				AlgorithmLibraryListContainer	AList;
				AL->EnumLibrary(L->GetInstance()->GetLibType(),AList);
				if(AList.GetFirst()!=NULL){
					PixelLibraryIDList.append(/**/"");
					PixelLibraryNameList.append(/**/"");
				}
				for(AlgorithmLibraryList *p=AList.GetFirst();p!=NULL;p=p->GetNext()){
					PixelLibraryIDList.append(QString::number(p->GetLibID()));
					PixelLibraryNameList.append(p->GetLibName());
				}
			}
		}
	}

	//Algorithmの取得
	AlgorithmListName.clear();
	AlgorithmListName.append(/**/"");
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmListName.append(L->GetDLLName());
	}

	//UniqueNameList
	UniqueNameList[_DynamicClassify] << /**/"" << /**/"Core Area" << /**/"MaxZone Area" << /**/"Base Area" << /**/"Inside Area" << /**/"Outline-O Area" << /**/"Outline-T Area" << /**/"Outline-I Area";
}

void	PixelLibraryManager::CreatePixelLibraryNameList()
{
	//cmbPixelLibraryNameList
	if(cmbPixelLibraryNameList!=NULL){
		delete cmbPixelLibraryNameList;
	}
	cmbPixelLibraryNameList=new QComboBox();
	for(int i=0;i<PixelLibraryNameList.count();i++){
		cmbPixelLibraryNameList->insertItem(i,PixelLibraryNameList.at(i));
	}
	connect(cmbPixelLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbPixelLibraryNameListCurrentIndexChanged(int)));
}

void	PixelLibraryManager::CreateAlgorithmNameList()
{
	//cmbAlgorithmNameList
	if(cmbAlgorithmNameList!=NULL){
		delete cmbAlgorithmNameList;
	}
	cmbAlgorithmNameList=new QComboBox();
	for(int i=0;i<AlgorithmListName.count();i++){
		cmbAlgorithmNameList->insertItem(i,AlgorithmListName.at(i));
	}
}

bool	PixelLibraryManager::CreateLibraryNameList(int Row)
{
	QTableWidgetItem *Item;
	if((Item=ui.twPixelLibraryList->item(Row,TableColHeader.indexOf(/**/"Algorithm")))==NULL){
		return false;
	}
	QString Value;
	if((Value=Item->text()).isEmpty()==true){
		return false;
	}

	LibraryIDList.clear();
	LibraryNameList.clear();
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLName()==Value){
			AlgorithmLibraryContainer  *AL=L->GetInstance()->GetLibraryContainer();
			if(AL!=NULL){
				AlgorithmLibraryListContainer	AList;
				AL->EnumLibrary(L->GetInstance()->GetLibType(),AList);
				if(AList.GetFirst()!=NULL){
					LibraryIDList.append(/**/"");
					LibraryNameList.append(/**/"");
				}
				for(AlgorithmLibraryList *p=AList.GetFirst();p!=NULL;p=p->GetNext()){
					LibraryIDList.append(QString::number(p->GetLibID()));
					LibraryNameList.append(p->GetLibName());
				}
			}
		}
	}

	//cmbLibraryNameList
	if(cmbLibraryNameList!=NULL){
		delete cmbLibraryNameList;
	}
	cmbLibraryNameList=new QComboBox();
	for(int i=0;i<LibraryNameList.count();i++){
		cmbLibraryNameList->insertItem(i,LibraryNameList.at(i));
	}

	connect(cmbLibraryNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbLibraryNameListCurrentIndexChanged(int)));
	return true;
}

bool	PixelLibraryManager::CreateUniqueNameList(int Row)
{
	UniqueType UniType;
	QTableWidgetItem *Item;
	if((Item=ui.twPixelLibraryList->item(Row,TableColHeader.indexOf(/**/"Algorithm")))==NULL){
		return false;
	}
	QString Value;
	if((Value=Item->text())==/**/"DynamicClassify"){
		UniType=_DynamicClassify;
	}
	else{
		return false;
	}

	//cmbUniqueNameList
	if(cmbUniqueNameList!=NULL){
		delete cmbUniqueNameList;
	}
	cmbUniqueNameList=new QComboBox();
	for(int i=0;i<UniqueNameList[UniType].count();i++){
		cmbUniqueNameList->insertItem(i,UniqueNameList[UniType].at(i));
	}
	connect(cmbUniqueNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(cmbUniqueNameListCurrentIndexChanged(int)));
	return true;
}

void	PixelLibraryManager::CreatePriority()
{
	//sbPriority
	if(sbPriority!=NULL){
		delete sbPriority;
	}
	sbPriority=new QSpinBox();
}

//設定内容をファイルに保存
bool	PixelLibraryManager::SaveFile(const QString &FileName)
{
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		QTextStream mystream(&File);

		QTableWidgetItem *Item;
		for(int Row=0;Row<ui.twPixelLibraryList->rowCount();Row++){
			for(int Col=0;Col<ui.twPixelLibraryList->columnCount();Col++){
				if((Item=ui.twPixelLibraryList->item(Row,Col))!=NULL){
					mystream << Item->text();
				}
				if(Col<ui.twPixelLibraryList->columnCount()-1){
					mystream << /**/",";
				}
			}
			mystream << endl;
		}
		File.close();
	}
	else{
		QMessageBox::warning(this,"Warning",QString("Save error to %1").arg(FileName),QMessageBox::Ok,QMessageBox::Ok);
		return false;
	}
	return true;
}

//ファイルから読み込んだデータの整合性チェック
bool	PixelLibraryManager::CheckLoadData(int Row,int Col,const QStringList &myStringList,QString &Msg)
{
	if(Col==TableColHeader.indexOf(/**/"PixelLibraryID")){
		for(int i=0;i<PixelLibraryIDList.count();i++){
			if(myStringList.at(Col)==PixelLibraryIDList.at(i)){
				return true;
			}
		}
		Msg="Not found PixelLibrary ID.";
	}
	else if(Col==TableColHeader.indexOf(/**/"PixelLibrary")){
		int Index=TableColHeader.indexOf(/**/"PixelLibraryID");
		int i;
		for(i=0;i<PixelLibraryIDList.count();i++){
			if(myStringList.at(Index)==PixelLibraryIDList.at(i)){
				break;
			}
		}
		if(i<PixelLibraryIDList.count()){
			if(myStringList.at(Col)==PixelLibraryNameList.at(i)){
				return true;
			}
		}
		Msg="Not found PixelLibrary Name.";
	}
	else if(Col==TableColHeader.indexOf(/**/"Algorithm")){
		for(int i=0;i<AlgorithmListName.count();i++){
			if(myStringList.at(Col)==AlgorithmListName.at(i)){
				return true;
			}
		}
		Msg="Not found Algorithm Name.";
	}
	else if(Col==TableColHeader.indexOf(/**/"LibraryID")){
		//Libraryの取得
		CreateLibraryNameList(Row);
		//cmbLibraryNameList
		if(cmbLibraryNameList!=NULL){
			delete cmbLibraryNameList;
			cmbLibraryNameList=NULL;
		}
		for(int i=0;i<LibraryIDList.count();i++){
			if(myStringList.at(Col)==LibraryIDList.at(i)){
				return true;
			}
		}
		Msg="Not found Library ID.";
	}
	else if(Col==TableColHeader.indexOf(/**/"Library")){
		int Index=TableColHeader.indexOf(/**/"LibraryID");
		int i;
		for(i=0;i<LibraryIDList.count();i++){
			if(myStringList.at(Index)==LibraryIDList.at(i)){
				break;
			}
		}
		if(i<LibraryIDList.count()){
			if(myStringList.at(Col)==LibraryNameList.at(i)){
				return true;
			}
		}
		Msg="Not found Library Name.";
	}
	else if(Col==TableColHeader.indexOf(/**/"UniqueID")){
		if(myStringList.at(TableColHeader.indexOf(/**/"Algorithm"))==/**/"DynamicClassify"){
			if(UniqueNameList[_DynamicClassify].indexOf(myStringList.at(Col+1))==myStringList.at(Col).toInt()){
				return true;
			}
			Msg="Defference Unique Name.";
		}
		else{
			return true;
		}
	}
	else if(Col==TableColHeader.indexOf(/**/"Unique")){
		return true;
	}
	else if(Col==TableColHeader.indexOf(/**/"Priority")){
		bool IsOK;
		myStringList.at(Col).toInt(&IsOK);
		if(IsOK==true){
			return true;
		}
		Msg="Not correct Priority.";
	}
	return false;
}

//テーブルリスト１項目にデータをセット
void	PixelLibraryManager::SetDataToTable(QTableWidget *W,int row,int col,QVariant value)
{
	if(value.isNull())
		value=/**/"";
	W->model()->setData(W->model()->index(row,col),value);
}
