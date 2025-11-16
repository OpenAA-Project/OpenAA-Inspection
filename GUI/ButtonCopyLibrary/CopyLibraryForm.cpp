#include "ButtonCopyLibraryResource.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "CopyLibraryForm.h"
#include "XGeneralFunc.h"
#include "InputNameForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CopyLibraryForm::CopyLibraryForm(const QString &_AlgoRoot , const QString &_AlgoName
								 ,LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	AlgoRoot=_AlgoRoot;
	AlgoName=_AlgoName;
	ABase=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);

	LibType=-1;
	if(ABase!=NULL)	
		LibType=ABase->GetLibType();
	pLibFolderFormSrc=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameFolderSrc);
	connect(pLibFolderFormSrc,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderSrc(int,QString)));
	pLibFolderFormSrc->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	pLibFolderFormDst=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameFolderDst);
	connect(pLibFolderFormDst,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolderDst(int,QString)));
	pLibFolderFormDst->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	InstallOperationLog(this);
}

CopyLibraryForm::~CopyLibraryForm()
{

}

void	CopyLibraryForm::SlotSelectLibFolderSrc(int libFolderID ,QString)
{
	LibFolderIDSrc=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibListSrc->setRowCount(0);

	if(ABase!=NULL){
		AlgorithmLibraryContainer	*AContainer=ABase->GetLibraryContainer();
		LibIDListSrc.RemoveAll();
		AContainer->EnumLibrary(LibType,LibFolderIDSrc ,LibIDListSrc);
		
		int	row=0;
		ui.tableWidgetLibListSrc->setRowCount(LibIDListSrc.GetNumber());
		for(AlgorithmLibraryList *a=LibIDListSrc.GetFirst();a!=NULL;a=a->GetNext(),row++){
			SetDataToTable(ui.tableWidgetLibListSrc ,0 ,row ,QString::number(a->GetLibID()));
			SetDataToTable(ui.tableWidgetLibListSrc ,1 ,row ,a->GetLibName());
		}
	}
}

void	CopyLibraryForm::SlotSelectLibFolderDst(int libFolderID ,QString)
{
	LibFolderIDDst=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibListDst->setRowCount(0);

	if(ABase!=NULL){
		AlgorithmLibraryContainer	*AContainer=ABase->GetLibraryContainer();
		LibIDListDst.RemoveAll();
		AContainer->EnumLibrary(LibType,LibFolderIDDst ,LibIDListDst);
		
		int	row=0;
		ui.tableWidgetLibListDst->setRowCount(LibIDListDst.GetNumber());
		for(AlgorithmLibraryList *a=LibIDListDst.GetFirst();a!=NULL;a=a->GetNext(),row++){
			SetDataToTable(ui.tableWidgetLibListDst ,0 ,row ,QString::number(a->GetLibID()));
			SetDataToTable(ui.tableWidgetLibListDst ,1 ,row ,a->GetLibName());
		}
	}
}

void CopyLibraryForm::on_pushButtonCopy_clicked()
{
	int	R=ui.tableWidgetLibListSrc->currentRow();
	if(R<0){
		return;
	}
	AlgorithmLibraryList *a=LibIDListSrc.GetItem(R);
	if(a!=NULL){
		InputNameForm	D(GetLayersBase(),a->GetLibName(),this);
		if(D.exec()==(int)true){
			QSqlDatabase	&DBase=GetLayersBase()->GetDatabase();

			QString	S=QString(/**/"SELECT max(LIBID) FROM INSPECTLIB where LIBTYPE=")
						+QString::number(LibType);

			QSqlQuery queryLibID(S,DBase);
			queryLibID.next();
			int	LibID= queryLibID.value(0).toInt()+1;


			QString	S2=QString(/**/"SELECT * FROM INSPECTLIB where LIBTYPE=")
						+QString::number(LibType)
						+QString(/**/" and LIBID=")
						+QString::number(a->GetLibID());

			QSqlQuery query(S2,DBase);
			if(query.next ()==false){
				return;
			}

			int	LastWorker	=query.value(query.record().indexOf(/**/"LASTWORKER")).toInt();
			int	DataVersion	=query.value(query.record().indexOf(/**/"DATAVERSION")).toInt();
			QByteArray	Ld	=query.value(query.record().indexOf(/**/"LIBDATA")).toByteArray();
			QByteArray	Ad	=query.value(query.record().indexOf(/**/"ANYDATA")).toByteArray();
			QByteArray	Yd	=query.value(query.record().indexOf(/**/"ADAPTEDLAYERS")).toByteArray();

			QSqlQuery queryInsrt(DBase);
			queryInsrt.prepare(/**/"INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ANYDATA,ADAPTEDLAYERS) "
				/**/"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ANYDATA,:ADAPTEDLAYERS);");		
			queryInsrt.bindValue(0	, LibType);
			queryInsrt.bindValue(1	, LibID);
			queryInsrt.bindValue(2	, LibFolderIDDst);
			queryInsrt.bindValue(3	, D.LibName);
			queryInsrt.bindValue(4	, LastWorker);
			queryInsrt.bindValue(5	, XDateTime::currentDateTime().GetQDateTime());
			queryInsrt.bindValue(6	, DataVersion);
			queryInsrt.bindValue(7	, Ld);
			queryInsrt.bindValue(8	, Ad);
			queryInsrt.bindValue(9	, Yd);
			if(queryInsrt.exec()==false){
				return;
			}
			SlotSelectLibFolderSrc(LibFolderIDSrc,/**/"");
			SlotSelectLibFolderDst(LibFolderIDDst,/**/"");
			return;
		}
	}
}

void CopyLibraryForm::on_pushButtonClose_clicked()
{
	close();
}

void CopyLibraryForm::on_pushButtonAll_clicked()
{
	if(QMessageBox::question(NULL
							,LangSolver.GetString(CopyLibraryForm_LS,LID_0)/*"Select"*/
							,LangSolver.GetString(CopyLibraryForm_LS,LID_1)/*"Copy all in this folder?"*/
							,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
		QSqlDatabase	&DBase=GetLayersBase()->GetDatabase();

		QString	S=QString(/**/"SELECT max(LIBID) FROM INSPECTLIB where LIBTYPE=")
					+QString::number(LibType);

		QSqlQuery queryLibID(S,DBase);
		queryLibID.next();
		int	LibID= queryLibID.value(0).toInt()+1;
		for(AlgorithmLibraryList *a=LibIDListSrc.GetFirst();a!=NULL;a=a->GetNext()){

			QString	S2=QString(/**/"SELECT * FROM INSPECTLIB where LIBTYPE=")
						+QString::number(LibType)
						+QString(/**/" and LIBID=")
						+QString::number(a->GetLibID());

			QSqlQuery query(S2,DBase);
			if(query.next ()==false){
				return;
			}

			int	LastWorker	=query.value(query.record().indexOf(/**/"LASTWORKER")).toInt();
			int	DataVersion	=query.value(query.record().indexOf(/**/"DATAVERSION")).toInt();
			QByteArray	Ld	=query.value(query.record().indexOf(/**/"LIBDATA")).toByteArray();
			QByteArray	Ad	=query.value(query.record().indexOf(/**/"ANYDATA")).toByteArray();
			QByteArray	Yd	=query.value(query.record().indexOf(/**/"ADAPTEDLAYERS")).toByteArray();

			QSqlQuery queryInsrt(DBase);
			queryInsrt.prepare(/**/"INSERT INTO INSPECTLIB(LIBTYPE,LIBID,LIBFOLDERID,LIBNAME,LASTWORKER,LASTUPDATED,DATAVERSION,LIBDATA,ANYDATA,ADAPTEDLAYERS) "
				/**/"VALUES(:LIBTYPE,:LIBID,:LIBFOLDERID,:LIBNAME,:LASTWORKER,:LASTUPDATED,:DATAVERSION,:LIBDATA,:ANYDATA,:ADAPTEDLAYERS);");		
			queryInsrt.bindValue(0	, LibType);
			queryInsrt.bindValue(1	, LibID);
			queryInsrt.bindValue(2	, LibFolderIDDst);
			queryInsrt.bindValue(3	, a->GetLibName());
			queryInsrt.bindValue(4	, LastWorker);
			queryInsrt.bindValue(5	, XDateTime::currentDateTime().GetQDateTime());
			queryInsrt.bindValue(6	, DataVersion);
			queryInsrt.bindValue(7	, Ld);
			queryInsrt.bindValue(8	, Ad);
			queryInsrt.bindValue(9	, Yd);
			if(queryInsrt.exec()==false){
				return;
			}
			LibID++;
		}
		SlotSelectLibFolderSrc(LibFolderIDSrc,/**/"");
		SlotSelectLibFolderDst(LibFolderIDDst,/**/"");
	}

}