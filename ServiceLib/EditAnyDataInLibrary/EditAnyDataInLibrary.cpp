#include "EditAnyDataInLibraryResource.h"
#include "EditAnyDataInLibrary.h"
#include <QSqlQuery>
#include "XDataInLayer.h"
#include <QSqlRecord>
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibNGType.h"
#include "XAlgorithmLibrary.h"
#include <QColorDialog>
#include "XGeneralDialog.h"

EditAnyDataInLibrary::EditAnyDataInLibrary(LayersBase *Base 
										  ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);
	SelectedItem=NULL;

	ShowListLibType();
	pLibFolderForm=new GeneralLibFolderForm(-1,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	ui.tableWidgetLibList->setColumnWidth(0, 30);
	ui.tableWidgetLibList->setColumnWidth(1,150);
	ui.tableWidgetAnyData->setColumnWidth(0, 30);
	ui.tableWidgetAnyData->setColumnWidth(1,150);
}

EditAnyDataInLibrary::~EditAnyDataInLibrary()
{

}

void	EditAnyDataInLibrary::ShowListLibType(void)
{
	LibTypeIDList.RemoveAll();
	ui.tableWidgetLibType->setColumnWidth(0,30);
	ui.tableWidgetLibType->setColumnWidth(1,150);
	ui.tableWidgetLibType->setRowCount(0);
	QString	S=QString(/**/"SELECT LIBTYPE,TYPENAME FROM INSPECTLIBTYPE");
	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	int	L=0;
	while(query.next ()==true){
		int		TypeID	=query.value(query.record().indexOf(/**/"LIBTYPE"	)).toInt();
		QString	TypeName=query.value(query.record().indexOf(/**/"TYPENAME"	)).toString();
		LibTypeIDList.Add(TypeID);
		ui.tableWidgetLibType->setRowCount(L+1);
		SetDataToTable(ui.tableWidgetLibType ,0,L,TypeID);
		SetDataToTable(ui.tableWidgetLibType ,1,L,TypeName);
		L++;
	}
}


void EditAnyDataInLibrary::on_tableWidgetLibType_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetLibType->currentRow();
	if(Row<0)
		return;
	LibTypeID=LibTypeIDList[Row];

	pLibFolderForm->SetLibType(LibTypeID);
	ui.tableWidgetLibList->setRowCount(0);
	ui.tableWidgetAnyData->setRowCount(0);

	LogicDLL	*LDLL=GetLayersBase()->GetLogicDLLBase()->SearchByLibType(LibTypeID);
	if(LDLL!=NULL){
		if(SelectedItem!=NULL){
			delete	SelectedItem;
		}
		SelectedItem=LDLL->GetInstance()->GetLibraryContainer()->CreateLibNGTypeItem(GetLayersBase());
	}
}

void	EditAnyDataInLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	LibraryIDList.RemoveAll();

	QString	S	=QString(/**/"SELECT LIBID,LIBNAME FROM INSPECTLIB WHERE LIBTYPE=")
				+QString::number(LibTypeID)
				+QString(/**/" and LIBFOLDERID=")
				+QString::number(LibFolderID);

	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	int	L=0;
	while(query.next ()==true){
		int		LibID	=query.value(query.record().indexOf(/**/"LIBID"		)).toInt();
		QString	LibName	=query.value(query.record().indexOf(/**/"LIBNAME"	)).toString();

		ui.tableWidgetLibList->setRowCount(L+1);
		SetDataToTable(ui.tableWidgetLibList ,0,L,LibID);
		SetDataToTable(ui.tableWidgetLibList ,1,L,LibName);
		LibraryIDList.Add(LibID);
		L++;
	}
}


void EditAnyDataInLibrary::on_tableWidgetLibList_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetLibList->currentRow();
	if(Row<0)
		return;
	SelectedLibID=LibraryIDList[Row];
	
	ui.tableWidgetAnyData->setRowCount(0);
	AnyDataList.RemoveAll();

	QString	S	=QString(/**/"SELECT NGTYPEID,DATANAME FROM ANYDATAINLIB WHERE LIBTYPE=")
				+QString::number(LibTypeID)
				+QString(/**/" and LIBID=")
				+QString::number(SelectedLibID);

	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	int	L=0;
	while(query.next ()==true){
		int		NGTypeID=query.value(query.record().indexOf(/**/"NGTYPEID"	)).toInt();
		QString	DataName=query.value(query.record().indexOf(/**/"DATANAME"	)).toString();

		ui.tableWidgetAnyData->setRowCount(L+1);
		SetDataToTable(ui.tableWidgetAnyData ,0,L,NGTypeID);
		SetDataToTable(ui.tableWidgetAnyData ,1,L,DataName);
		AnyDataList.Add(NGTypeID);
		L++;
	}
}

void EditAnyDataInLibrary::on_tableWidgetAnyData_clicked(const QModelIndex &)
{
	int	Row=ui.tableWidgetAnyData->currentRow();
	if(Row<0)
		return;
	SelectedNGTypeID=AnyDataList[Row];

	LogicDLL	*LDLL=GetLayersBase()->GetLogicDLLBase()->SearchByLibType(LibTypeID);
	if(LDLL!=NULL){
		if(SelectedItem!=NULL){
			delete	SelectedItem;
		}
		SelectedItem=LDLL->GetInstance()->GetLibraryContainer()->GetNGTypeItem(SelectedLibID,SelectedNGTypeID);

		ui.lineEditTypeUniqueCode	->setText(QString::number(SelectedItem->TypeUniqueCode));
		ui.lineEditTypeCode			->setText(QString::number(SelectedItem->TypeCode));
		ui.lineEditDataName			->setText(SelectedItem->NGName);
		QPalette	PL=ui.pushButtonColor->palette();
		PL.setColor(QPalette::Button,SelectedItem->NGColor);
		ui.pushButtonColor			->setPalette(PL);
		ui.comboBoxNGShape			->setCurrentIndex((int)SelectedItem->NGShape);
		ui.checkBoxBlink			->setChecked(SelectedItem->Blink);
		ui.spinBoxNextJumpMilisec	->setValue(SelectedItem->NextJumpMilisec);
		ui.spinBoxPriority			->setValue(SelectedItem->Priority);
	}
}

void EditAnyDataInLibrary::on_pushButtonClose_clicked()
{
	close();
}

void EditAnyDataInLibrary::on_pushButtonColor_clicked()
{
	if(SelectedItem!=NULL){
		QColor Col=QColorDialog::getColor ( SelectedItem->NGColor);
		if(Col.isValid()==true){
			SelectedItem->NGColor=Col;
			QPalette	PL=ui.pushButtonColor->palette();
			PL.setColor(QPalette::Button,SelectedItem->NGColor);
			ui.pushButtonColor->setPalette(PL);
		}
	}
}

void EditAnyDataInLibrary::on_pushButtonUpdate_clicked()
{
	if(SelectedItem!=NULL){
		SelectedItem->NGName	=ui.lineEditDataName->text();
		SelectedItem->NGShape	=(LibNGTypeItem::NGShapeType)ui.comboBoxNGShape->currentIndex();
		SelectedItem->NextJumpMilisec	=ui.spinBoxNextJumpMilisec	->value();
		SelectedItem->Priority			=ui.spinBoxPriority			->value();
		SelectedItem->Blink				=ui.checkBoxBlink			->isChecked();

		LogicDLL	*LDLL=GetLayersBase()->GetLogicDLLBase()->SearchByLibType(LibTypeID);
		if(LDLL!=NULL){
			LDLL->GetInstance()->GetLibraryContainer()->UpdateNGTypeItem(SelectedLibID,SelectedItem);
		}
		QModelIndex		IDX;
		on_tableWidgetLibList_clicked(IDX);
	}
}

void EditAnyDataInLibrary::on_pushButtonSpecifiedData_clicked()
{
	if(SelectedItem!=NULL){
		SelectedItem->ShowSetting();
	}
}

void EditAnyDataInLibrary::on_pushButtonCopyToCB_clicked()
{

}

void EditAnyDataInLibrary::on_pushButtonPasteFromCB_clicked()
{

}

void EditAnyDataInLibrary::on_pushButtonCreateNew_clicked()
{
	if(SelectedItem!=NULL){
		SelectedItem->NGName	=ui.lineEditDataName->text();
		SelectedItem->NGShape	=(LibNGTypeItem::NGShapeType)ui.comboBoxNGShape->currentIndex();
		SelectedItem->NextJumpMilisec	=ui.spinBoxNextJumpMilisec	->value();
		SelectedItem->Priority			=ui.spinBoxPriority			->value();
		SelectedItem->Blink				=ui.checkBoxBlink			->isChecked();

		LogicDLL	*LDLL=GetLayersBase()->GetLogicDLLBase()->SearchByLibType(LibTypeID);
		if(LDLL!=NULL){
			LDLL->GetInstance()->GetLibraryContainer()->SaveNewNGTypeItem(SelectedLibID,SelectedItem);
		}
		QModelIndex		IDX;
		on_tableWidgetLibList_clicked(IDX);
	}
}

void EditAnyDataInLibrary::on_pushButtonDelete_clicked()
{
	if(SelectedItem!=NULL){
		LogicDLL	*LDLL=GetLayersBase()->GetLogicDLLBase()->SearchByLibType(LibTypeID);
		if(LDLL!=NULL){
			LDLL->GetInstance()->GetLibraryContainer()->DeleteNGTypeItem(SelectedLibID,SelectedItem);
		}
		delete	SelectedItem;
		SelectedItem=NULL;

		QModelIndex		IDX;
		on_tableWidgetLibList_clicked(IDX);
	}
}