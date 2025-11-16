#include "AutoSaveImageViewListResource.h"
#include "AutoSaveImageViewListForm.h"
#include "FormSelectFolders.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGeneralStocker.h"
#include "ButtonLoadAlgorithm.h"
#include "ButtonLoadMatrixCell.h"
#include <omp.h>

extern	const	char	*sRoot;
extern	const	char	*sName;

bool makeAutoSaveImageList(QStringList &PathList, QVariantList &lst);

AutoSaveImageViewListForm::AutoSaveImageViewListForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	defFnam = /**/"AutoSaveImageView.dat";
	CurrentMachineID=-1;
}

AutoSaveImageViewListForm::~AutoSaveImageViewListForm()
{

}

AutoSaveImageBase	*AutoSaveImageViewListForm::GetAutoSaveImageBase(void)
{
	return (AutoSaveImageBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
}

void AutoSaveImageViewListForm::BuildForShow()
{	
	static	bool	ReEntrant=false;
	/*
	AlgorithmBase *GAlg=GetAutoSaveImageBase();
	if ( GAlg == NULL ) return;

	mkDrvList();
	if ( Drv1 == "" ) return;
	CmdImageFileList Da;
	Da.strDir1 = Drv1;
	Da.strDir2 = Drv2;
	GAlg->TransmitDirectly(&Da);

	itmLst = Da.SaveImageList;
	itmCnt = itmLst.GetNumber();
	*/

	/*
	if(LastMachineID!=GetLayersBase()->GetMachineID()){
		if ( mkFileList(itmLst) == false ) {
			return;
		}
		RawItmLst=itmLst;
		LastMachineID=GetLayersBase()->GetMachineID();
	}
	*/

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	dbgFileListPrt();
	GeneralStockerContainer *p = GetLayersBase()->GetGeneralStocker();

	if(CurrentMachineID!=-1 && CurrentMachineID!=GetLayersBase()->GetMachineID()){
		if(LotFilter!=/**/""){
			CmdSetLotString	SCmd(GetLayersBase());
			SCmd.LotString=LotFilter;
			TransmitDirectly(&SCmd);
		}
	}
	CurrentMachineID=GetLayersBase()->GetMachineID();

	SaveImageFileListContainer tmpL;
	if(LotFilter==/**/""){
		for(SaveImageFileList *a=itmLst.GetFirst();a!=NULL;a=a->GetNext()){
			QVariantList	ArgV;
			ArgV << a->FilePath;
			QVariantList	RetV;
			if(p->GetData(/**/"AutoSaveImage_MatchList",RetV,ArgV)==true && RetV.at(0).toBool()==true) {
				SaveImageFileList *b=NULL;
				for(b = tmpL.GetFirst();b!=NULL;b=b->GetNext()){
		//			if(b->FileDate == a->FileDate
					if(b->LotNo == a->LotNo
					&& b->BaseNoInt == a->BaseNoInt ){
							break;
					}
				}
				if(b==NULL){
					SaveImageFileList *rec = new SaveImageFileList();
					*rec = *a;
					tmpL.AppendList(rec);
				}
			}
		}
	}
	else{
		for(SaveImageFileList *a=itmLst.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->LotNo!=LotFilter){
				continue;
			}
			QVariantList	ArgV;
			ArgV << a->FilePath;
			QVariantList	RetV;
			if(p->GetData(/**/"AutoSaveImage_MatchList",RetV,ArgV)==true && RetV.at(0).toBool()==true) {
				SaveImageFileList *b=NULL;
				for(b = tmpL.GetFirst();b!=NULL;b=b->GetNext()){
					//if(b->LotNo == a->LotNo
					//&& b->BaseNoInt == a->BaseNoInt ){
					if(b->BaseNoInt == a->BaseNoInt ){
							break;
					}
				}
				if(b==NULL){
					SaveImageFileList *rec = new SaveImageFileList();
					*rec = *a;
					tmpL.AppendList(rec);
				}
			}
		}
	}
	SaveImageFileList **Tbl=new SaveImageFileList *[tmpL.GetNumber()];
	int	N=0;
	for(SaveImageFileList *a = tmpL.GetFirst();a!=NULL;a=a->GetNext(),N++){
		Tbl[N]=a;
	}
	bool	Changed;
	do{
		Changed=false;
		for(int i=0;i<N-1;i++){
			if(Tbl[i]->FileDate>Tbl[i+1]->FileDate){
				SaveImageFileList *k=Tbl[i];
				Tbl[i]=Tbl[i+1];
				Tbl[i+1]=k;
				Changed=true;
			}
		}
	}while(Changed==true);

	SaveImageFileListContainer lst;
	for(int i=0;i<N;i++){
		SaveImageFileList *c=Tbl[i];
		tmpL.RemoveList(c);
		lst.AppendList(c);
	}
	delete	[]Tbl;

	int cnt = lst.GetNumber();
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->setColumnWidth(0,86);
	ui.tableWidget->setColumnWidth(1,50);
	//ui.tableWidget->setColumnWidth(2,86);
	ui.tableWidget->setRowCount(cnt);
	SaveImageFileList *recItm = lst.GetFirst();
	for( int i=0; i<cnt; i++ ) {
		QTableWidgetItem *w;
		w = ui.tableWidget->item(i,0);
		if ( w == NULL ) {
			ui.tableWidget->setItem(i,0,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		}
		w->setText(recItm->LotNo);
		w = ui.tableWidget->item(i,1);
		if ( w == NULL ) {
			ui.tableWidget->setItem(i,1,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		}
		w->setText(recItm->BaseNoStr);
		/*
		w = ui.tableWidget->item(i,2);
		if ( w == NULL ) {
			ui.tableWidget->setItem(i,2,(w=new QTableWidgetItem()));
			w->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		}
		w->setText(recItm->FileDate);
		*/
		recItm = recItm->GetNext();
	}
	ReEntrant=false;
}

void	AutoSaveImageViewListForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetLotStringList	*CmdGetLotStringListVar=dynamic_cast<CmdGetLotStringList *>(packet);
	if(CmdGetLotStringListVar!=NULL){
		for(SaveImageFileList *recItm = RawItmLst.GetFirst();recItm!=NULL;recItm=recItm->GetNext()){
			int i;
			for(i=0;i<CmdGetLotStringListVar->LotList.count();i++){
				if(recItm->LotNo==CmdGetLotStringListVar->LotList[i]){
					break;
				}
			}
			if(i>=CmdGetLotStringListVar->LotList.count()){
				CmdGetLotStringListVar->LotList.append(recItm->LotNo);
			}
		}
	}
	CmdSetLotString	*CmdSetLotStringVar=dynamic_cast<CmdSetLotString *>(packet);
	if(CmdSetLotStringVar!=NULL){
		LotFilter=CmdSetLotStringVar->LotString;

		QVariantList	ArgV;
		ArgV<<QVariant(LotFilter);
		QVariantList	RetV;
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(AutoSaveImageViewListForm_LS,LID_0)/*"Set Lot string"*/);
		GetLayersBase()->SetMaxProcessing(2);
		QCoreApplication::processEvents();

		if(GetLayersBase()->GetGeneralStocker()->GetData(/**/"SelectedLotOnViewer",RetV,ArgV)==true){
			QString	AlgFile=RetV[0].toString();
			QString	McfFile=RetV[1].toString();

			GetLayersBase()->StepProcessing(-1);
			GUIFormBase	*GUILoadAlgorithm=GetLayersBase()->FindByName(/**/"Button",/**/"LoadAlgorithm",/**/"");
			if(GUILoadAlgorithm!=NULL){
				ExecuteLoadAlgorithm	ECmd(GetLayersBase());
				ECmd.AlgorithmRoot=/**/"Basic";
				ECmd.AlgorithmName=/**/"Naming";
				ECmd.FileName=AlgFile;
				GUILoadAlgorithm->TransmitDirectly(&ECmd);
			}
			GetLayersBase()->StepProcessing(-1);
			GUIFormBase	*GUILoadMatrix=GetLayersBase()->FindByName(/**/"Review",/**/"LoadMatrixCell",/**/"");
			if(GUILoadMatrix!=NULL){
				ExecuteLoadMatrix	ECmd(GetLayersBase());
				ECmd.FileName=McfFile;
				GUILoadMatrix->TransmitDirectly(&ECmd);
			}
		}
		GetLayersBase()->CloseProcessingForm ();
		BuildForShow();
	}
}


bool AutoSaveImageViewListForm::mkFileList(QStringList &PathList
										   ,SaveImageFileListContainer &ItmLst) 
{
	QVariantList	ArgV;
	ArgV << /**/"0";
	ArgV << PathList;
	QVariantList	RetV;
	QString	FileName;
	GeneralStockerContainer *p = GetLayersBase()->GetGeneralStocker();
	if(p->GetData(/**/"AutoSaveImage_FileList",RetV,ArgV)==false) {
		makeAutoSaveImageList(PathList,RetV);
		if(RetV.count()==0){
			return false;
		}
	}

	ItmLst.RemoveAll();
	for( int i=0; i<RetV.size(); i++ ) {
		SaveImageFileList *rec = new SaveImageFileList();
		QString tmp = RetV.at(i).toString();
		int	AddPathNo=1;
		QStringList arr0 = tmp.split(/**/".");
		QString tmp0 = arr0.at(0);
		QStringList arr  = tmp0.split(/**/"/");
		//QStringList arr  = tmp.split(/**/"/");
		QStringList arr2 = arr[4+AddPathNo].split(/**/"_");
		rec->FileDrv = arr[0+AddPathNo];
		rec->FileDate = arr[1+AddPathNo]+/**/" "+arr2[4].mid(0,2);
		rec->FileName = arr[4+AddPathNo];
		rec->LotNo    = arr[2+AddPathNo];
		rec->BaseNoStr= arr[3+AddPathNo];
		rec->BaseNoInt=rec->BaseNoStr.toInt();
		rec->Page     = arr2[3].toInt();
		rec->FileTime = arr2[4];
		//rec->FileTime = arr2[4].toInt();
		rec->FilePath = tmp;
		/*
		for(SaveImageFileList *r=ItmLst.GetFirst();r!=NULL;r=r->GetNext()){
			if(rec->BaseNoInt==r->BaseNoInt){
				if(r->FileDrv==rec->FileDrv && rec->LotNo==r->LotNo && rec->Page==r->Page){
					if(r->FileTime<rec->FileTime){
						*r=*rec;
						delete	rec;
						goto	NextP;
					}
					else{
						delete	rec;
						goto	NextP;
					}
				}
			}
		}
		*/
		ItmLst.AppendList(rec);
NextP:;
	}

	ItmLst.sort();
	//itmCnt = ItmLst.GetNumber();
	return true;
}

void AutoSaveImageViewListForm::dbgFileListPrt()
{
	QFile file(/**/"C:/Tmp/filelist.dat");
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) return;
	QTextStream out(&file);

	SaveImageFileList *cur = itmLst.GetFirst();
	while( cur != NULL ) {
		QString tmp = cur->FileDrv+cur->FileName;
		out << tmp << /**/"\n";
		cur = cur->GetNext();
	}

	file.close();

}

void AutoSaveImageViewListForm::ResizeAction()
{
	int	H=ui.frame->height();
	ui.frame->move(0,height()-H);
	ui.frame->resize(width(),H);
	ui.tableWidget->resize(ui.tableWidget->width(),ui.frame->geometry().top()-ui.tableWidget->geometry().top()-2);
	//BuildForShow();
	//ui.pushButtonUpdate->resize(width(),ui.pushButtonUpdate->height());
	//ui.tableWidget->resize(width(),height()-ui.pushButtonUpdate->height());
}


void AutoSaveImageViewListForm::on_tableWidget_clicked(const QModelIndex &)
{
	setPanelParam();

	int Idx = ui.tableWidget->currentRow();
	QString LotNo    = ui.tableWidget->item(Idx,0)->text();
	int		BaseNoInt= ui.tableWidget->item(Idx,1)->text().toInt();
	//QString FileDate = ui.tableWidget->item(Idx,2)->text();
	SaveImageFileListContainer lstView;

	GeneralStockerContainer *p = GetLayersBase()->GetGeneralStocker();
	for(SaveImageFileList *a = itmLst.GetFirst(); a != NULL ;a = a->GetNext()) {
//		if ( LotNo == a->LotNo && BaseNo == a->BaseNo && FileDate == a->FileDate ) {
		if ( (BaseNoInt == a->BaseNoInt) && (LotNo == a->LotNo)) {
			QVariantList	ArgV;
			ArgV << a->FilePath;
			QVariantList	RetV;
			if(p->GetData(/**/"AutoSaveImage_MatchList",RetV,ArgV)==true && RetV.at(0).toBool()==true) {
				SaveImageFileList *rec = new SaveImageFileList();
				*rec = *a;
				lstView.AppendList(*rec);
			}
		}
	}

	int	BoardNumber=BaseNoInt;
	GetLayersBase()->SetLatchedInspectionNumber(BoardNumber);

	int cnt = lstView.GetNumber();
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(AutoSaveImageViewListForm_LS,LID_1)/*"Loading image"*/);
	GetLayersBase()->SetMaxProcessing(cnt);
	QCoreApplication::processEvents();

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for( int i=0; i<cnt; i++ ) {
			GUICmdReqLoad	RCmd(GetLayersBase(),sRoot,sName,i);
			GUICmdAckLoad	ACmd(GetLayersBase(),sRoot,sName,i);
			for(SaveImageFileList *a = lstView.GetFirst();a!=NULL;a=a->GetNext()){
				if(a->Page==(i+1)){
					RCmd.FileName = a->FilePath;
					break;
				}
			}
			RCmd.Send(i,0,ACmd);
		}
	}
	GetLayersBase()->CloseProcessingForm();
	XDateTime	C=XDateTime::currentDateTime();
	GetLayersBase()->SetStartInspectTime(C);
	GetLayersBase()->SetEndInspectionTime(C);

	//BroadcastShow(BoardNumber);
	BroadcastShowInEdit();
}

void AutoSaveImageViewListForm::on_pushButtonUpdate_clicked()
{
	FormSelectFolders	Q(GetLayersBase());
	if(Q.exec()==(int)true){
		PathLists=Q.PathLists;
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(AutoSaveImageViewListForm_LS,LID_2)/*"Updating list"*/);
		QCoreApplication::processEvents();
		LastMachineID=-1;
		if ( mkFileList(PathLists,itmLst) == false ) {
			GetLayersBase()->CloseProcessingForm();
			return;
		}
		RawItmLst=itmLst;
		BuildForShow();
		GetLayersBase()->CloseProcessingForm();
	}
}

void AutoSaveImageViewListForm::mkDrvList() {
	QFileInfoList lstDrv = QDir::drives();
	int cnt = lstDrv.size();
	QString drvNam;
	
	Drv1 = /**/"";
	Drv2 = /**/"";
	for( int i=0; i<cnt; i++ ) {
		drvNam = lstDrv[i].filePath();
		if ( drvNam == /**/"C:/" || drvNam == /**/"c:/" ) continue;
		if ( drvNam == /**/"A:/" || drvNam == /**/"A:/" ) continue;
		if ( chkImageExist(drvNam) == true ) {
			if ( Drv1 == /**/"" ) Drv1 = drvNam;
			else Drv2 = drvNam;
		}
		if ( Drv2 != /**/"" ) break;
	}
}
bool AutoSaveImageViewListForm::chkImageExist(QString drv) {
	QString fnam = /**/"";
	QDir dir(drv);
	QStringList filter;
	filter << /**/"Image";
	dir.setNameFilters(filter);
	QFileInfoList lstFile = dir.entryInfoList();
	if ( lstFile.size() > 0 ) {
		QFileInfo finfo = lstFile[0];
		fnam = finfo.filePath();
		QDir dir2(finfo.filePath());
		QStringList filter2;
		filter2 << /**/"??????????";
		dir2.setNameFilters(filter2);
		QFileInfoList lstFile2 = dir2.entryInfoList();
		if ( lstFile2.size() > 0 ) {
			return true;
		}
	}
	/*
	if ( lstFile.size() > 0 ) {

		QDir dir2(drv);
		QFileInfoList lst2 = dir2.entryInfoList();
		for( int i=0; i<lst2.size(); i++ ) {
			QFileInfo fInfo = lst2[i];
			fnam = fInfo.filePath();
			int c=0;
		}
		return true;
	}*/
	return false;
}

void AutoSaveImageViewListForm::on_pushButton_Save_clicked()
{
	QString fnam = QFileDialog::getSaveFileName(this
												,LangSolver.GetString(AutoSaveImageViewListForm_LS,LID_3)/*"SaveParam File Select"*/
												,/**/"./"+defFnam
												,/**/"*.dat");
	if ( fnam == /**/"" ) {
		return;
	}
	QString buf = /**/"";
	buf += ui.txtStartX->text()+/**/",";
	buf += ui.txtStartY->text()+/**/",";
	buf += ui.txtWidth->text() +/**/",";
	buf += ui.txtHeight->text()+/**/",";

	QFile file(fnam);
	if ( !file.open(QIODevice::WriteOnly|QIODevice::Text) ) {
		return;
	}
	QTextStream out(&file);
	out << buf << /**/"\n";
	file.close();

	setPanelParam();
}


void AutoSaveImageViewListForm::on_pushButton_Load_clicked()
{
	QString fnam = QFileDialog::getOpenFileName(this
												,LangSolver.GetString(AutoSaveImageViewListForm_LS,LID_4)/*"LoadParam File Select"*/
												,/**/"./",/**/"*.dat");
	if ( fnam == /**/"" ) {
		return;
	}
	QFile file(fnam);
	if ( file.exists() == false ) {
		return;
	}
	if ( !file.open(QIODevice::ReadOnly|QIODevice::Text) ) {
		return;
	}
	QTextStream in(&file);
	QString buf = in.readLine();
	QStringList lst = buf.split(/**/",");
	if ( lst.size() < 4 ) return;
	ui.txtStartX->setValue(lst.at(0).toInt());
	ui.txtStartY->setValue(lst.at(1).toInt());
	ui.txtWidth->setValue(lst.at(2).toInt());
	ui.txtHeight->setValue(lst.at(3).toInt());
	setPanelParam();
}

void AutoSaveImageViewListForm::setPanelParam() {
	CmdPanelParam cmd(GetLayersBase());
	cmd.nStartX = ui.txtStartX->text().toInt();
	cmd.nStartY = ui.txtStartY->text().toInt();
	cmd.nWidth  = ui.txtWidth->text().toInt();
	cmd.nHeight = ui.txtHeight->text().toInt();

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoSaveImageViewPanel" ,/**/"");
	if ( GProp == NULL ) return;
	//GProp->TransmitDirectly(&cmd);

}

bool makeAutoSaveImageList(QStringList &PathList, QVariantList &lst)
{
	QFileInfoList lstDrv = QDir::drives();
	int cnt = lstDrv.size();
	QVariantList TmpLst[100];

	if(PathList.count()==0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for( int i=0; i<cnt; i++ ) {
				QString	LotPathName;
				QString	BoardPathName;
				QString	Dir2Path;
				QString drvNam;
				drvNam = lstDrv[i].filePath();
				if(drvNam.compare("C:/", Qt::CaseInsensitive) != 0 
				&& drvNam.compare("A:/", Qt::CaseInsensitive) != 0 ){
	
					QDir dir1(drvNam+QString("Image"));
					QStringList filters1;
					filters1 << "*";//"????????";
					dir1.setNameFilters(filters1);
					QFileInfoList lstDate = dir1.entryInfoList();
					for( int j=0; j<lstDate.size(); j++ ) {
						QFileInfo fDate = lstDate[j];
						Dir2Path=fDate.filePath();
						QDir dir2(Dir2Path);
						QStringList filters2;
						filters2 << "*";
						dir2.setNameFilters(filters2);
						QFileInfoList lstLot = dir2.entryInfoList();
						for( int k=0; k<lstLot.size(); k++ ) {
							LotPathName=lstLot[k].fileName();
							QDir dir3(lstLot[k].filePath());
							QStringList filters3;
							filters3 << "*";
							dir3.setNameFilters(filters2);
							QFileInfoList lstBoard = dir3.entryInfoList();
							for( int l=0; l<lstBoard.size(); l++ ) {
								BoardPathName=lstBoard[l].fileName();
								QDir dir4(lstBoard[l].filePath());
								QStringList filters4;
								filters4 << "*_*_*_*_*.piy";
								dir4.setNameFilters(filters4);
								QFileInfoList lstPiy = dir4.entryInfoList();
								for( int m=0; m<lstPiy.size(); m++ ) {
									QStringList arr = lstPiy[m].fileName().split("_");
									TmpLst[i] << lstPiy[m].filePath();
								}
							}
						}
					}
				}
			}	
		}
		for( int i=0; i<cnt; i++ ) {
			for(int j=0;j<TmpLst[i].count();j++){
				lst<<(TmpLst[i])[j];
			}
		}

		if ( lst.size() <= 0 ) {
			return false;
		}
	}
	else{
		int cnt=PathList.count();
		QString	PathDim[100];
		for( int i=0; i<cnt; i++ ) {
			PathDim[i]=PathList[i];
		}

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for( int i=0; i<cnt; i++ ) {
				QString	LotPathName;
				QString	BoardPathName;
				QString	Dir2Path;
				QString drvNam;
				drvNam = PathDim[i];
	
				QDir dir1(drvNam);
				QStringList filters1;
				filters1 << "*.piy";//"????????";
				dir1.setNameFilters(filters1);
				QFileInfoList lstDate = dir1.entryInfoList();
				for( int j=0; j<lstDate.size(); j++ ) {
					TmpLst[i] << lstDate[j].filePath();
				}
				
				QDir dir2(drvNam);
				QStringList filters2;
				filters1 << "*";//"????????";
				dir2.setNameFilters(filters1);
				dir2.setFilter(QDir::Dirs);
				lstDate = dir2.entryInfoList();
				for( int j=0; j<lstDate.size(); j++ ) {
					QDir dir4(lstDate[j].filePath());
					QStringList filters4;
					filters4 << "*.piy";
					dir4.setNameFilters(filters4);
					QFileInfoList lstPiy = dir4.entryInfoList();
					for( int m=0; m<lstPiy.size(); m++ ) {
						QStringList arr = lstPiy[m].fileName().split("_");
						TmpLst[i] << lstPiy[m].filePath();
					}
				}
			}
		}	
		for( int i=0; i<cnt; i++ ) {
			for(int j=0;j<TmpLst[i].count();j++){
				lst<<(TmpLst[i])[j];
			}
		}

		if ( lst.size() <= 0 ) {
			return false;
		}
	}
	return true;
}


GUICmdReqLoad::GUICmdReqLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqLoad::Load(QIODevice *f)
{
	if(::Load(f,FileName)==false)
		return false;
	return true;
}
bool	GUICmdReqLoad::Save(QIODevice *f)
{
	if(::Save(f,FileName)==false)
		return false;
	return true;
}

void	GUICmdReqLoad::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckLoad	*SendBack=GetSendBack(GUICmdAckLoad,GetLayersBase(),EmitterRoot,EmitterName,localPage);

	AutoSaveImageBase	*ABase=(AutoSaveImageBase	*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(ABase!=NULL){
		CmdImageLoadFile Cmd(GetLayersBase());
		Cmd.FileName = FileName;
		Cmd.LocalPage = localPage;
		ABase->TransmitDirectly(&Cmd);
	}
	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckLoad::GUICmdAckLoad(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
