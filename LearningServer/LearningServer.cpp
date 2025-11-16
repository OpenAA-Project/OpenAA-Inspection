#include "LearningServer.h"
#include "WEditParameterTab.h"
#include "XGeneralDialog.h"
#include "XLearningServer.h"
#include <QSqlQuery>
#include <QBuffer>
#include <QSqlRecord>
#include <QMenu>
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "LearningSettingDialog.h"
#include "XDatabaseLoader.h"
#include "XGUI.h"
#include "XDLLType.h"
#include "XDataAlgorithmList.h"
#include "XLearningRegist.h"
#include "XLearningServerComm.h"
#include "EditLineDialog.h"
#include "XDataAlgorithm.h"
#include "XResult.h"
#include "XAlgorithmBase.h"
#include "ConfirmForm.h"
#include "XGUIComponent.h"

QSqlLearningModel::QSqlLearningModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
}
QString QSqlLearningModel::selectStatement () const
{
	QString	ret;
	ret=QString(/**/"SELECT LEARNINGID,MACHINEID,UPDATETIME,SAMPLETYPE,PRIORITY FROM LEARNING ORDER BY UPDATETIME;");
	return ret;
}
	
LabelWithRightButton::LabelWithRightButton(QWidget *parent)
	:QLabel(parent)
{}

void LabelWithRightButton::mouseReleaseEvent(QMouseEvent *Ev)
{
	bool	LeftClicked		= ((Ev->button() & Qt::LeftButton)!=0) ? true : false;
	bool	RightClicked	= ((Ev->button() & Qt::RightButton)!=0) ? true : false;

	int x=Ev->x();
	int y=Ev->y();
	if(LeftClicked==true){
		emit	SignalLClicked(x,y);
	}
	else
	if(RightClicked==true){
		emit	SignalRClicked(x,y);
	}
}

LearningServer::LearningServer(LayersBase *base ,bool StartRun ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,ButtonR(false),ButtonG(false),ButtonB(false)
	,TargetPanel(this)
{
	ui.setupUi(this);

	EPointForDraw		=NULL;
	LayerForDraw		=NULL;
	EPointForCalc		=NULL;
	LayerForCalc		=NULL;
	SelectedLearningID	=-1;
	IndependentPackData	=NULL;
	ConfirmFormInst		=NULL;
	CurrentAlgoWindow	=NULL;

	QSqlLearningModel *MModel = new QSqlLearningModel(this,ServerBaseData->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID
	MModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
	MModel->setHeaderData(1, Qt::Horizontal, tr("MachineID"));
	MModel->setHeaderData(2, Qt::Horizontal, tr("Update Time"));
	MModel->setHeaderData(3, Qt::Horizontal, tr("Type"));
	MModel->setHeaderData(4, Qt::Horizontal, tr("Priority"));

	ui.tableViewRegisteredData->setModel(MModel);
	ui.tableViewRegisteredData->setColumnWidth (0, 40);
	ui.tableViewRegisteredData->setColumnWidth (1, 64);
	ui.tableViewRegisteredData->setColumnWidth (2, 140);
	ui.tableViewRegisteredData->setColumnWidth (3, 40);
	ui.tableViewRegisteredData->setColumnWidth (4, 64);

	ui.tableWidgetLibrary->setColumnWidth (0, 64);
	ui.tableWidgetLibrary->setColumnWidth (1, 120);
	ui.tableWidgetLibrary->setColumnWidth (2, 64);
	ui.tableWidgetLibrary->setColumnWidth (3, 160);

	LastY	=height();

	LastLearningID	=-1;
	LastLibType		=-1;
	LastLibID		=-1;

	TargetPanel.setParent(ui.frame);
	TargetPanel.setGeometry(ui.label_TargetImage->geometry());
	connect(&TargetPanel,SIGNAL(SignalRClicked(int,int)),this,SLOT(SlotRClickedTargetPanel(int,int)));

	connect(&Server,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
	Server.listen(QHostAddress::Any,LearningServerPort);

	::SetColumnWidthInTable(ui.tableWidgetConnection ,0, 50);
	::SetColumnWidthInTable(ui.tableWidgetConnection ,1, 50);

	delete	ui.label_TargetImage;

	ButtonR.setParent(ui.frameColorButton);
	ButtonG.setParent(ui.frameColorButton);
	ButtonB.setParent(ui.frameColorButton);
	ButtonR.setGeometry(0  ,0,80,ui.frameColorButton->height()-2);
	ButtonG.setGeometry(100,0,80,ui.frameColorButton->height()-2);
	ButtonB.setGeometry(200,0,80,ui.frameColorButton->height()-2);
	ButtonR.setColor(Qt::darkRed);
	ButtonG.setColor(Qt::darkGreen);
	ButtonB.setColor(Qt::darkBlue);
	ButtonR.setPressedColor(Qt::red);
	ButtonG.setPressedColor(Qt::green);
	ButtonB.setPressedColor(Qt::blue);
	ButtonR.setChecked(true);
	ButtonG.setChecked(true);
	ButtonB.setChecked(true);
	connect(&ButtonR,SIGNAL(clicked()),this,SLOT(SlotShowImage()));
	connect(&ButtonG,SIGNAL(clicked()),this,SLOT(SlotShowImage()));
	connect(&ButtonB,SIGNAL(clicked()),this,SLOT(SlotShowImage()));

	::SetColumnWidthInTable(ui.tableWidgetExecuter,0, 12);
	::SetColumnWidthInTable(ui.tableWidgetExecuter,1, 28);
	::SetColumnWidthInTable(ui.tableWidgetExecuter,2, 12);
	::SetColumnWidthInTable(ui.tableWidgetExecuter,3, 20);
	::SetColumnWidthInTable(ui.tableWidgetExecuter,4, 12);

	::SetColumnWidthInTable(ui.tableWidgetAlgorithmThreshold,0, 13);
	::SetColumnWidthInTable(ui.tableWidgetAlgorithmThreshold,1, 28);
	::SetColumnWidthInTable(ui.tableWidgetAlgorithmThreshold,2, 13);
	::SetColumnWidthInTable(ui.tableWidgetAlgorithmThreshold,3, 18);
	::SetColumnWidthInTable(ui.tableWidgetAlgorithmThreshold,4, 18);

	::SetColumnWidthInTable(ui.tableWidgetThresholdProperty,0,65);
	::SetColumnWidthInTable(ui.tableWidgetThresholdProperty,1,25);

	Executer=new ThreadServer(this,GetLayersBase());
	connect(Executer,SIGNAL(SignalShowList())	,this,SLOT(SlotShowList())	,Qt::QueuedConnection);
	connect(Executer,SIGNAL(SignalUpdateList())	,this,SLOT(SlotUpdateList()),Qt::QueuedConnection);
	Executer->start();

	ui.tabWidget->setCurrentIndex(0);
	if(StartRun==true){
		ui.pushButtonExecute->setChecked(true);
		on_pushButtonExecute_clicked();
	}
}

LearningServer::~LearningServer()
{
	Executer->StopExecute();
	Executer->Terminated=true;
	Executer->deleteLater();
}

void LearningServer::on_pushButtonClose_clicked()
{
	close();
}

void LearningServer::resizeEvent ( QResizeEvent * event )
{
	ui.frameBottom->setGeometry(0,height()-ui.frameBottom->height(),width(),ui.frameBottom->height());
	int	dy=height()-LastY;
	ui.tableViewRegisteredData->resize(ui.tableViewRegisteredData->width(),ui.tableViewRegisteredData->height()+dy);
	ui.label				->move(ui.label->geometry().left(),ui.label->geometry().top()+dy);
	ui.tableWidgetLibrary	->move(ui.tableWidgetLibrary->geometry().left(),ui.tableWidgetLibrary->geometry().top()+dy);
	ui.tabWidget			->resize(ui.tabWidget->width()			,ui.tabWidget->height()+dy);
	ui.tableWidgetExecuter	->resize(ui.tableWidgetExecuter->width(),ui.tableWidgetExecuter->height()+dy);
	ui.tableWidgetThresholdProperty	->resize(ui.tableWidgetThresholdProperty->width(),ui.tableWidgetThresholdProperty->height()+dy);
	ui.progressBar			->move(ui.progressBar->geometry().left(),ui.progressBar->geometry().top()+dy);
	LastY+=dy;
}

void LearningServer::SlotRClickedTargetPanel(int x ,int y)
{
	SlotSaveImage();
	//QMenu	Menu(this);
	//Menu.addAction ("Save image"	, this, SLOT(SlotSaveImage()));
	//
	//QPoint	R=TargetPanel.mapToGlobal(QPoint(x,y));
	//Menu.exec(R);
}

void	LearningServer::SlotSaveImage()
{
	if(SelectedLearningID>=0){
		QString	FileName=QFileDialog::getSaveFileName(NULL
													,"Save image"
													,QString()
													,/**/"PNG file(*.png)");
		if(FileName.isEmpty()==false){
			TargetImage.save(FileName);
		}
	}
}

void LearningServer::on_pushButtonSetting_clicked()
{
	LearningSettingDialog	D(GetLayersBase(),ServerBaseData->GetParamGlobal());	
	//GeneralDialog	D(NULL,new WEditParameterTab(ServerBaseData->GetParamGlobal(),-1),NULL);
	D.exec();
}

void LearningServer::on_tableViewRegisteredData_clicked(const QModelIndex &)
{
	SlotShowImage();
}

void	LearningServer::SlotShowImage()
{
	QModelIndex Index=ui.tableViewRegisteredData->currentIndex();
	QSqlLearningModel	*M=dynamic_cast<QSqlLearningModel	 *>(ui.tableViewRegisteredData->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		SelectedLearningID=M->data(RIndex).toInt();
		ShowLearning(SelectedLearningID);
		//_heapchk();
	}
}

QImage	LearningServer::MakeImage(ImageBuffer *Buff[] ,LayersBase *Base ,int LayerNumb ,int Width ,int Height)
{
	QImage	Img(Width,Height,QImage::Format_RGB32);

	double	Zx=(Buff[0]->GetWidth())/((double)Width);
	double	Zy=(Buff[0]->GetHeight())/((double)Height);
	ZoomRate=(Zx<Zy)?Zx:Zy;
	bool	bR=ButtonR.isChecked();
	bool	bG=ButtonG.isChecked();
	bool	bB=ButtonB.isChecked();

	for(int y=0;y<Height;y++){
		QRgb	*d=(QRgb *)Img.scanLine(y);
		BYTE	*s[3];
		int	Y=y*ZoomRate;
		if(0<=Y && Y<Buff[0]->GetHeight()){
			for(int Layer=0;Layer<LayerNumb && Layer<3;Layer++){
				s[Layer]=Buff[Layer]->GetY(Y);
			}
			if(LayerNumb==3){
				for(int x=0;x<Width;x++){
					int	X=x*ZoomRate;
					if(0<=X && X<Buff[0]->GetWidth()){
						*d=qRgb((bR==true)?s[0][X]:0,(bG==true)?s[1][X]:0,(bB==true)?s[2][X]:0);
					}
					d++;
				}
			}
			else
			if(LayerNumb==2 && Base->GetParamGlobal()->EnableToColorizeFor3Layers==true){
				for(int x=0;x<Width;x++){
					int	X=x*ZoomRate;
					if(0<=X && X<Buff[0]->GetWidth()){
						*d=qRgb((bR==true)?s[0][X]:0,(bG==true)?s[1][X]:0,(bG==true)?s[1][X]:0);
					}
					d++;
				}
			}
			else
			if(LayerNumb==2 && Base->GetParamGlobal()->EnableToColorizeFor3Layers==false){
				for(int x=0;x<Width;x++){
					int	X=x*ZoomRate;
					if(0<=X && X<Buff[0]->GetWidth()){
						*d=qRgb((bR==true)?s[0][X]:0,(bR==true)?s[0][X]:0,(bR==true)?s[0][X]:0);
					}
					d++;
				}
			}
			else
			if(LayerNumb==1){
				for(int x=0;x<Width;x++){
					int	X=x*ZoomRate;
					if(0<=X && X<Buff[0]->GetWidth()){
						*d=qRgb((bR==true)?s[0][X]:0,(bR==true)?s[0][X]:0,(bR==true)?s[0][X]:0);
					}
					d++;
				}
			}
		}
	}
	return Img;
}

QString	GetLibTypeName(QSqlDatabase &DB ,int LibType)
{
	QString	S=QString(/**/"SELECT LIBTYPE ,TYPENAME FROM INSPECTLIBTYPE WHERE LIBTYPE=")
			+QString::number(LibType);
	QSqlQuery query(S ,DB);
	if(query.next ()==false){
		return /**/"";
	}
	QString	LibName=query.value(query.record().indexOf(/**/"TYPENAME")).toString();
	return LibName;
}

void LearningServer::ShowLearning(int LearningID)
{
	QString	S=QString(	/**/"SELECT "
						/**/"SAMPLETYPE,XSIZE ,YSIZE ,LAYER ,MASTERIMAGE ,TARGETIMAGE ,POINTDATA,MASTERCODE "
						/**/"FROM LEARNING WHERE LEARNINGID=")
			+QString::number(LearningID);
	int	SampleType	;
	int	XSize		;
	int	YSize		;
	int	LayerNumb	;
	QByteArray	MasterImageArray	;
	QByteArray	TargetImageArray	;
	QByteArray	PointDataArray		;
	int	MasterID;
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery query(S ,ServerBaseData->GetDatabase());
		if(query.next ()==false){
			GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
			return;
		}

		SampleType	=query.value(query.record().indexOf(/**/"SAMPLETYPE")	).toInt();
		XSize		=query.value(query.record().indexOf(/**/"XSIZE"	)		).toInt();
		YSize		=query.value(query.record().indexOf(/**/"YSIZE"	)		).toInt();
		LayerNumb	=query.value(query.record().indexOf(/**/"LAYER"	)		).toInt();
		MasterImageArray	=query.value(query.record().indexOf(/**/"MASTERIMAGE"	)).toByteArray();
		TargetImageArray	=query.value(query.record().indexOf(/**/"TARGETIMAGE"	)).toByteArray();
		PointDataArray		=query.value(query.record().indexOf(/**/"POINTDATA"		)).toByteArray();
		MasterID	=query.value(query.record().indexOf(/**/"MASTERCODE"	)		).toInt();
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();

	QBuffer	MasterImageBuff(&MasterImageArray);
	MasterImageBuff.open(QIODevice::ReadOnly);
	QBuffer	TargetImageBuff(&TargetImageArray);
	TargetImageBuff.open(QIODevice::ReadOnly);

	if(XSize!=0 && YSize!=0){
		if(LayerForDraw!=NULL){
			//_heapchk();
			delete	LayerForDraw;
			//_heapchk();
			LayerForDraw=NULL;
		}
		if(EPointForDraw!=NULL){
			//_heapchk();
			delete	EPointForDraw;
			//_heapchk();
			EPointForDraw=NULL;
		}
		//_heapchk();

		LayerForDraw=new ServerLayerBase(GetLayersBase(),GetLayersBase()->GetEntryPoint());
		EPointForDraw	=new ServerEntryPoint(LayerForDraw);

		LayerForDraw->SetEntryPoint(EPointForDraw);


		LayerForDraw->InitialForServer(XSize ,YSize ,LayerNumb);

		//delete	LayerForDraw;
		//_heapchk();

		LayerForDraw->Reallocate(1,1,LayerNumb);
		LayerForDraw->ReallocXYPixels(XSize,YSize);

		ImageBuffer *MasterBuffDim[100];
		ImageBuffer *TargetBuffDim[100];
		for(int Layer=0;Layer<LayerNumb;Layer++){
			DataInLayer	*Ly=LayerForDraw->GetPageData(0)->GetLayerData(Layer);

			MasterBuffDim[Layer]=&Ly->GetMasterBuff();
			MasterBuffDim[Layer]->Load(&MasterImageBuff);

			TargetBuffDim[Layer]=&Ly->GetTargetBuff();
			TargetBuffDim[Layer]->Load(&TargetImageBuff);
		}

		QBuffer	PBuff(&PointDataArray);
		PBuff.open(QIODevice::ReadOnly);

		FlexArea	PointArea;
		PointArea.Load(&PBuff);

		LayerForDraw->SampleType	=SampleType;
		LayerForDraw->PointArea		=PointArea;

		MasterImage=MakeImage(MasterBuffDim ,GetLayersBase(),LayerNumb ,ui.label_MasterImage->width(),ui.label_MasterImage->height());
		TargetImage=MakeImage(TargetBuffDim ,GetLayersBase(),LayerNumb ,TargetPanel.width(),TargetPanel.height());

		ui.label_MasterImage->setPixmap(QPixmap::fromImage(MasterImage));
		TargetPanel.setPixmap(QPixmap::fromImage(TargetImage));
	}
	ui.lineEditXSize	->setText(QString::number(XSize));
	ui.lineEditYSize	->setText(QString::number(YSize));
	ui.lineEditLayer	->setText(QString::number(LayerNumb));
	ui.lineEditMasterID	->setText(QString::number(MasterID));

	QString	S2=QString(	/**/"SELECT "
						/**/"MASTERNAME "
						/**/"FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterID);

	{
		GetLayersBase()->GetDatabaseLoader()->G_LockDB();
		QSqlQuery query2(S2 ,ServerBaseData->GetDatabase());
		if(query2.next ()==true){
			QString	MasterName=query2.value(query2.record().indexOf(/**/"MASTERNAME")	).toString();
			ui.lineEditMasterName	->setText(MasterName);
		}
		else{
			ui.lineEditMasterName	->setText(/**/"");
		}
		GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
	}
	ShowLibrary(LearningID);
}
void	LearningServer::ShowLibrary(int LearningID)
{
	QString	SParam=QString(/**/"SELECT PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM WHERE LEARNINGID=")
			+QString::number(LearningID);

	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery QueryParam(SParam ,ServerBaseData->GetDatabase());
		int	Row=0;
		ui.tableWidgetLibrary->setRowCount(Row);
		while(QueryParam.next ()==true){
			ui.tableWidgetLibrary->setRowCount(Row+1);
			int	LibType	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBTYPE")).toInt();
			int	LibID	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBID")	).toInt();
			QByteArray	ParamData	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMDATA")).toByteArray();

			::SetDataToTable(ui.tableWidgetLibrary ,0 ,Row ,QString::number(LibType));
			QString	LibTypeName=GetLibTypeName(ServerBaseData->GetDatabase(),LibType);
			GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
			QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(ServerBaseData->GetDatabase(), LibType ,LibID);
			::SetDataToTable(ui.tableWidgetLibrary ,1 ,Row ,LibTypeName);
			::SetDataToTable(ui.tableWidgetLibrary ,2 ,Row ,QString::number(LibID));
			::SetDataToTable(ui.tableWidgetLibrary ,3 ,Row ,LibName);

			LayerForDraw->LoadItemParamData(LibType , LibID ,ParamData);
			Row++;
			GetLayersBase()->GetDatabaseLoader()->G_LockDB();
		}
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
}


void LearningServer::on_tableViewRegisteredData_doubleClicked(const QModelIndex &index)
{
	QMenu	Menu(this);
	Menu.addAction ("Edit"				, this, SLOT(SlotEditLine()));
	Menu.addAction ("Delete line"		, this, SLOT(SlotDeleteLine()));
	//Menu.addAction ("Try execution"		, this, SLOT(SlotExecuteLine()));

	QPoint	Q=ui.tableViewRegisteredData->cursor().pos();
	Menu.exec(Q);
}

void LearningServer::on_tableWidgetLibrary_doubleClicked(const QModelIndex &index)
{
	QMenu	Menu(this);
	Menu.addAction ("Delete item"			, this, SLOT(SlotDeleteItem()));
	//Menu.addAction ("Try execution in item"	, this, SLOT(SlotExecuteItem()));

	QPoint	Q=ui.tableWidgetLibrary->cursor().pos();
	Menu.exec(Q);
}

void	LearningServer::SlotEditLine()
{
	QModelIndex Index=ui.tableViewRegisteredData->currentIndex();
	QSqlLearningModel	*M=dynamic_cast<QSqlLearningModel	 *>(ui.tableViewRegisteredData->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	CurrentLearningID=M->data(RIndex).toInt();
		EditItem(CurrentLearningID);
	}
}

void	LearningServer::EditItem(int LearningID)
{
	QString	S=QString(/**/"SELECT SAMPLETYPE,PRIORITY FROM LEARNING WHERE LEARNINGID=")
			+QString::number(LearningID);
	int	SampleType	;
	int	Priority	;
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery query(S ,ServerBaseData->GetDatabase());
		if(query.next ()==false){
			GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
			return;
		}

		SampleType	=query.value(query.record().indexOf(/**/"SAMPLETYPE")	).toInt();
		Priority	=query.value(query.record().indexOf(/**/"PRIORITY"	)	).toInt();
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();

	EditLineDialog	D(SampleType,Priority);
	if(D.exec()==true){
		GetLayersBase()->GetDatabaseLoader()->G_LockDB();
		{
			QSqlQuery queryUpdate(ServerBaseData->GetDatabase());
			QString	Str =QString("UPDATE LEARNING ")
						+QString("SET SAMPLETYPE=")		+QString::number(D.SampleType)
						+QString(",PRIORITY=")			+QString::number(D.Priority)
						+QString(" WHERE LEARNINGID=")	+QString::number(LearningID);

			queryUpdate.prepare(Str);
			bool	ret1=queryUpdate.exec();
		}
		GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
		on_pushButtonUpdate_clicked();
	}
}

void	LearningServer::SlotDeleteLine()
{
	QModelIndex Index=ui.tableViewRegisteredData->currentIndex();
	QSqlLearningModel	*M=dynamic_cast<QSqlLearningModel	 *>(ui.tableViewRegisteredData->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	CurrentLearningID=M->data(RIndex).toInt();

		RemoveItem(CurrentLearningID);
	}
}
void    LearningServer::RemoveItem(int LearningID)
{
	if(QMessageBox::question(NULL
							,"Delete"
							,"Delete ok?")==QMessageBox::Yes){

		GetLayersBase()->GetDatabaseLoader()->G_LockDB();
		{
			QSqlQuery queryDelete(ServerBaseData->GetDatabase());
			queryDelete.prepare("DELETE FROM LEARNING WHERE LEARNINGID=:LEARNINGID");
			queryDelete.bindValue(0	, LearningID);
			if(queryDelete.exec()==false){
				GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
				return ;
			}
			QSqlQuery queryDeleteParam(ServerBaseData->GetDatabase());
			queryDeleteParam.prepare("DELETE FROM LEARNINGPARAM WHERE LEARNINGID=:LEARNINGID");
			queryDeleteParam.bindValue(0	, LearningID);
			if(queryDeleteParam.exec()==false){
				GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
				return ;
			}
		}
		GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
		ui.tableWidgetLibrary->setRowCount(0);

		QSqlLearningModel *MModel=(QSqlLearningModel *)ui.tableViewRegisteredData->model();
		MModel->select();
		ui.tableViewRegisteredData->update();
		ui.tableWidgetLibrary->update();
	}
}

void	LearningServer::SlotExecuteLine()
{
	QModelIndex Index=ui.tableViewRegisteredData->currentIndex();
	QSqlLearningModel	*M=dynamic_cast<QSqlLearningModel	 *>(ui.tableViewRegisteredData->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	CurrentLearningID=M->data(RIndex).toInt();
		ExecuteLine(CurrentLearningID);
	}
}
void	LearningServer::SlotDeleteItem()
{
	int	CurrentRow=ui.tableWidgetLibrary->currentRow();

	QString	SParam=QString(/**/"SELECT PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM WHERE LEARNINGID=")
			+QString::number(SelectedLearningID);
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery QueryParam(SParam ,ServerBaseData->GetDatabase());
		int	Row=0;
		while(QueryParam.next ()==true){
			if(Row==CurrentRow){
				int	ParamID	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMID")).toInt();
			
				QSqlQuery queryDeleteParam(ServerBaseData->GetDatabase());
				queryDeleteParam.prepare("DELETE FROM LEARNINGPARAM WHERE LEARNINGID=:LEARNINGID AND PARAMID==:PARAMID");
				queryDeleteParam.bindValue(0	, SelectedLearningID);
				queryDeleteParam.bindValue(1	, ParamID);
				if(queryDeleteParam.exec()==false){
					break ;
				}
				break;
			}
			Row++;
		}
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
	ShowLibrary(SelectedLearningID);
}
void	LearningServer::SlotExecuteItem()
{
	int	CurrentRow=ui.tableWidgetLibrary->currentRow();

	QString	SParam=QString(/**/"SELECT PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM WHERE LEARNINGID=")
			+QString::number(SelectedLearningID);
	QSqlQuery QueryParam(SParam ,ServerBaseData->GetDatabase());
	int	Row=0;
	while(QueryParam.next ()==true){
		if(Row==CurrentRow){
			int	ParamID	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMID")).toInt();
			int	LibType	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBTYPE")).toInt();
			int	LibID	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBID")	).toInt();
			QByteArray	ParamData	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMDATA")).toByteArray();
			ExecuteItem(SelectedLearningID,LibType,LibID,ParamData);
			break;
		}
	}
}

void	LearningServer::ExecuteLine(int LearningID)
{
	int	CurrentRow=ui.tableWidgetLibrary->currentRow();

	QString	SParam=QString(/**/"SELECT PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM WHERE LEARNINGID=")
			+QString::number(SelectedLearningID);
	QSqlQuery QueryParam(SParam ,ServerBaseData->GetDatabase());
	while(QueryParam.next ()==true){
		int	ParamID	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMID")).toInt();
		int	LibType	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBTYPE")).toInt();
		int	LibID	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBID")	).toInt();
		QByteArray	ParamData	=QueryParam.value(QueryParam.record().indexOf(/**/"PARAMDATA")).toByteArray();
		ExecuteItem(SelectedLearningID,LibType,LibID,ParamData);
	}
}

void	LearningServer::ExecuteItem(int LearningID ,int LibType,int LibID,QByteArray &ParamData)
{
	if(LastLearningID!=LearningID || LastLibType!=LibType || LastLibID!=LibID){
		QString	S=QString(/**/"SELECT SAMPLETYPE,XSIZE ,YSIZE ,LAYER ,MASTERIMAGE ,TARGETIMAGE ,POINTDATA FROM LEARNING WHERE LEARNINGID=")
				+QString::number(LearningID);
		QSqlQuery query(S ,ServerBaseData->GetDatabase());
		if(query.next ()==false)
			return;

		LastLearningID	=LearningID;
		LastLibType		=LibType;
		LastLibID		=LibID;
		int	SampleType	=query.value(query.record().indexOf(/**/"SAMPLETYPE")	).toInt();
		int	XSize		=query.value(query.record().indexOf(/**/"XSIZE"	)		).toInt();
		int	YSize		=query.value(query.record().indexOf(/**/"YSIZE"	)		).toInt();
		int	LayerNumb	=query.value(query.record().indexOf(/**/"LAYER"	)		).toInt();
		QByteArray	MasterImageArray	=query.value(query.record().indexOf(/**/"MASTERIMAGE"	)).toByteArray();
		QByteArray	TargetImageArray	=query.value(query.record().indexOf(/**/"TARGETIMAGE"	)).toByteArray();
		QByteArray	PointDataArray		=query.value(query.record().indexOf(/**/"POINTDATA"		)).toByteArray();

		QBuffer	MasterImageBuff(&MasterImageArray);
		MasterImageBuff.open(QIODevice::ReadOnly);
		QBuffer	TargetImageBuff(&TargetImageArray);
		TargetImageBuff.open(QIODevice::ReadOnly);

		if(XSize!=0 && YSize!=0){
			if(LayerForCalc!=NULL){
				delete	LayerForCalc;
			}
			if(EPointForCalc!=NULL){
				delete	EPointForCalc;
			}
			LayerForCalc=new ServerLayerBase(GetLayersBase(),GetLayersBase()->GetEntryPoint());
			EPointForCalc=new ServerEntryPoint(LayerForCalc);
			LayerForCalc->SetEntryPoint(EPointForCalc);

			LayerForCalc->InitialForServer(XSize ,YSize ,LayerNumb);
			ImageBuffer *MasterBuffDim[100];
			ImageBuffer *TargetBuffDim[100];
			for(int Layer=0;Layer<LayerNumb;Layer++){
				DataInLayer	*Ly=LayerForCalc->GetPageData(0)->GetLayerData(Layer);

				MasterBuffDim[Layer]=&Ly->GetMasterBuff();
				MasterBuffDim[Layer]->Load(&MasterImageBuff);

				TargetBuffDim[Layer]=&Ly->GetTargetBuff();
				TargetBuffDim[Layer]->Load(&TargetImageBuff);
			}

			QBuffer	PBuff(&PointDataArray);
			PBuff.open(QIODevice::ReadOnly);

			FlexArea	PointArea;
			PointArea.Load(&PBuff);

			LayerForCalc->SampleType	=SampleType;
			LayerForCalc->PointArea		=PointArea;

			LayerForCalc->LoadItemParamData(LibType , LibID ,ParamData);

			ListPhasePageLayerPack	CapturedList;
			LayerForCalc->MakeCapturedAllList(CapturedList);

			ExecuteInitialAfterEditInfo EInfo;
			LayerForCalc->ExecuteInitialAfterEdit	(EInfo,false);
			LayerForCalc->ExecuteStartByInspection	(false);
			LayerForCalc->ExecuteCaptured			(CapturedList,false);
			LayerForCalc->ExecutePreAlignment		(false);
			LayerForCalc->ExecuteAlignment			(false);
			LayerForCalc->ExecutePreProcessing		(false);
			LayerForCalc->ExecuteProcessing			(false);
			LayerForCalc->ExecuteProcessingRevived	(false);
			LayerForCalc->ExecutePostProcessing		(false);

		}
	}
}

void LearningServer::on_tableWidgetLibrary_clicked(const QModelIndex &index)
{
	int	CurrentRow=ui.tableWidgetLibrary->currentRow();

	QString	SParam=QString(/**/"SELECT PARAMID,LEARNINGID,LIBTYPE,LIBID,PARAMDATA FROM LEARNINGPARAM WHERE LEARNINGID=")
			+QString::number(SelectedLearningID);
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlQuery QueryParam(SParam ,ServerBaseData->GetDatabase());
		int	Row=0;
		//ui.tableWidgetLibrary->setRowCount(Row);
		while(QueryParam.next ()==true){
			if(Row==CurrentRow){
				int	LibType	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBTYPE")).toInt();
				int	LibID	=QueryParam.value(QueryParam.record().indexOf(/**/"LIBID")	).toInt();
				ShowLibraryMap(LibType,LibID);
				break;
			}
			Row++;
		}
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
}

void	LearningServer::ShowLibraryMap(int LibType,int LibID)
{
	QImage	Img(TargetPanel.width(),TargetPanel.height(),QImage::Format_RGB32);
	Img.fill(Qt::black);
	AlgorithmBase	*Ab=LayerForDraw->GetAlgorithmBase(LibType);
	for(int page=0;page<Ab->GetPageNumb();page++){
		AlgorithmInPageRoot	*Ap=Ab->GetPageData(page);
		if(Ap==NULL){
			continue;
		}
		AlgorithmItemPointerListContainer ItemPointers;
		IntList	LibIDs;
		LibIDs.Add(LibID);
		Ap->EnumItemsByLib(LibIDs,ItemPointers);
		for(AlgorithmItemPointerList *L=ItemPointers.GetFirst();L!=NULL;L=L->GetNext()){
			if(ZoomRate>0){
				L->GetItem()->GetArea();
				L->GetItem()->DrawAlpha(Img,0,0,ZoomRate,NULL);
			}
		}
	}
	QPainter	Pnt(&TargetImage);
	Pnt.drawImage(0,0,Img);
	TargetPanel.setPixmap(QPixmap::fromImage(TargetImage));
	TargetPanel.repaint();
}

void	LearningServer::ShowConnection(void)
{
	ui.tableWidgetConnection->setRowCount(SocketPack.GetCount());
	int	Row=0;
	for(LearningServerSocket *L=SocketPack.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		QString	Addr=L->GetSocket()->localAddress().toString();
		::SetDataToTable(ui.tableWidgetConnection, 0, Row, Addr);
	}
}

void	LearningServer::SlotNewConnection()
{
	QTcpSocket *s=Server.nextPendingConnection();
	LearningServerSocket	*v=new LearningServerSocket(s,this);
	SocketPack.AppendList(v);

	ShowConnection();
}

void	LearningServer::RemoveSocket(LearningServerSocket *s)
{
	SocketPack.RemoveList(s);
	s->deleteLater();
	ShowConnection();
}

void LearningServer::on_pushButtonSaveImage_clicked()
{
	QString Path=QFileDialog::getExistingDirectory(nullptr
												,"Directory for all target images"
												, QString());
	if(Path.isEmpty()==false){
		QString	S=QString(	/**/"SELECT "
							/**/"LEARNINGID,UPDATETIME,XSIZE,YSIZE,LAYER,TARGETIMAGE,MASTERCODE "
							/**/"FROM LEARNING");
		QSqlQuery query(S ,ServerBaseData->GetDatabase());
		while(query.next ()==true){
			int	LearningID	=query.value(query.record().indexOf(/**/"LEARNINGID")	).toInt();
			QDateTime	tm	=query.value(query.record().indexOf(/**/"UPDATETIME")	).toDateTime();
			int	XSize		=query.value(query.record().indexOf(/**/"XSIZE"	)		).toInt();
			int	YSize		=query.value(query.record().indexOf(/**/"YSIZE"	)		).toInt();
			int	LayerNumb	=query.value(query.record().indexOf(/**/"LAYER"	)		).toInt();
			QByteArray	TargetImageArray	=query.value(query.record().indexOf(/**/"TARGETIMAGE"	)).toByteArray();

			QBuffer	TargetImageBuff(&TargetImageArray);
			TargetImageBuff.open(QIODevice::ReadOnly);

			if(XSize!=0 && YSize!=0){
				if(LayerForDraw!=NULL){
					//_heapchk();
					delete	LayerForDraw;
					//_heapchk();
					LayerForDraw=NULL;
				}

				LayerForDraw=new ServerLayerBase(GetLayersBase(),GetLayersBase()->GetEntryPoint());
				EPointForDraw	=new ServerEntryPoint(LayerForDraw);

				LayerForDraw->SetEntryPoint(EPointForDraw);


				LayerForDraw->InitialForServer(XSize ,YSize ,LayerNumb);

				//delete	LayerForDraw;
				//_heapchk();

				LayerForDraw->Reallocate(1,1,LayerNumb);
				LayerForDraw->ReallocXYPixels(XSize,YSize);

				ImageBuffer *TargetBuffDim[100];
				for(int Layer=0;Layer<LayerNumb;Layer++){
					DataInLayer	*Ly=LayerForDraw->GetPageData(0)->GetLayerData(Layer);

					TargetBuffDim[Layer]=&Ly->GetTargetBuff();
					TargetBuffDim[Layer]->Load(&TargetImageBuff);
				}
				QImage	Img=MakeImage(TargetBuffDim ,GetLayersBase(),LayerNumb ,TargetPanel.width(),TargetPanel.height());

				QString	FileName=QString::number(LearningID)
								+QString(/**/"-")
								+tm.toString(/**/"yyMMdd-hhmmss")
								+QString(/**/".png");
				Img.save(Path+::GetSeparator()+FileName);
			}
		}
	}
}


void LearningServer::on_pushButtonBackup_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL,"Backup file name"
												,QString()
												,/**/"BackUp(*.BackUp);;All file(*.*)");
	if(FileName.isEmpty()==true)
		return;

	LearningInDBAll	LearningList;
	QString	S=QString(	/**/"SELECT "
						/**/"LEARNINGID FROM LEARNING");
	QSqlQuery query(S ,ServerBaseData->GetDatabase());
	while(query.next ()==true){
		int	LearningID	=query.value(query.record().indexOf(/**/"LEARNINGID")	).toInt();
		LearningInDB	*d=new LearningInDB();
		d->LearningID=LearningID;
		LearningList.AppendList(d);
	}
	for(LearningInDB *c=LearningList.GetFirst();c!=NULL;c=c->GetNext()){
		GetLayersBase()->GetDatabaseLoader()->G_LoadLearningInDB(ServerBaseData->GetDatabase(),c->LearningID,*c);
	}
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(LearningList.Save(&File)==false){
			QMessageBox::warning(NULL,"Error"
									,"Can not backup in file");
		}
	}
}


void LearningServer::on_pushButtonRestore_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL,"Restore file name"
												,QString()
												,/**/"BackUp(*.BackUp);;All file(*.*)");
	if(FileName.isEmpty()==true)
		return;

	LearningInDBAll	LearningList;
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LearningList.Load(&File)==false){
			QMessageBox::warning(NULL,"Error"
									,"Can not load in file");
		}
	}
	IntList	ErrorLearningID;
	for(LearningInDB *c=LearningList.GetFirst();c!=NULL;c=c->GetNext()){
		int	LearinigID=c->LearningID;
		if(GetLayersBase()->GetDatabaseLoader()->G_UpdateLearningInDB(ServerBaseData->GetDatabase(),*c)==false){
			if(GetLayersBase()->GetDatabaseLoader()->G_InsertLearningInDB(ServerBaseData->GetDatabase(),*c)==false){
				ErrorLearningID.Add(LearinigID);
			}
		}
	}
	on_pushButtonUpdate_clicked();
}

void LearningServer::on_pushButtonUpdate_clicked()
{
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QSqlLearningModel *MModel = (QSqlLearningModel *)ui.tableViewRegisteredData->model();
		MModel->select();
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
}

void	LearningServer::SlotUpdateList()
{
	on_pushButtonUpdate_clicked();
}

void LearningServer::on_pushButtonExecute_clicked()
{
	if(ui.pushButtonExecute->isChecked()==true){
		Executer->Halted=false;
	}
	else{
		Executer->Halted=true;
	}
}

void	LearningServer::StopExecute(void)
{
	Executer->StopExecute();
}
void	LearningServer::StartExecute(void)
{
	Executer->StartExecute();
}

void LearningServer::SlotShowList()
{
	Executer->AccessData.lockForRead();
	ui.tableWidgetExecuter->setRowCount(Executer->LearningList.GetCount());
	int	Row=0;
	for(LearningInDB *a=Executer->LearningList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetExecuter, 0, Row, QString::number(a->LearningID));
		::SetDataToTable(ui.tableWidgetExecuter, 1, Row, a->UpdateTime.toString(/**/"yyMMdd hhmmss"));
		if(a->SampleType==1)
			::SetDataToTable(ui.tableWidgetExecuter,2,Row,QString(/**/"OK"));
		else
			::SetDataToTable(ui.tableWidgetExecuter,2,Row,QString(/**/"NG"));
		::SetDataToTable(ui.tableWidgetExecuter, 3, Row, QString::number(a->Priority));
		if(a->Result==0)
			::SetDataToTable(ui.tableWidgetExecuter,4,Row,QString(/**/"--"));
		else
		if(a->Result==1)
			::SetDataToTable(ui.tableWidgetExecuter,4,Row,QString(/**/"OK"));
		else
		if(a->Result==2)
			::SetDataToTable(ui.tableWidgetExecuter,4,Row,QString(/**/"NG"));
	}

	AlgorithmThresholdPP.RemoveAll();
	for(AlgorithmThresholdPointer *a=Executer->AThrContainer.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmThresholdPP.Merge(a);
	}
	int	ARow=0;
	ui.tableWidgetAlgorithmThreshold->setRowCount(AlgorithmThresholdPP.GetCount());
	for(AlgorithmThresholdPointerPointer *a=AlgorithmThresholdPP.GetFirst();a!=NULL;a=a->GetNext(),ARow++){
		::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 0, ARow, QString::number(a->GetLibType()));
		::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 1, ARow, GetLayersBase()->GetLibTypeName(a->GetLibType()));
		::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 2, ARow, QString::number(a->GetLibID()));
		::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 3, ARow, GetLayersBase()->GetLibraryName(a->GetLibType(),a->GetLibID()));
		
		double	Value=0;
		LibTypeIDResult	*R=Executer->GetLibTypeIDResultData(a->GetLibType(), a->GetLibID());
		if(R!=NULL){
			Value=R->EnStrength;
			::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 4, ARow, QString::number(Value,'f',3));
		}
		else{
			::SetDataToTable(ui.tableWidgetAlgorithmThreshold, 4, ARow, /**/"");
		}
	}

	Executer->AccessData.unlock();
	int	v=ui.progressBar->value()+1;
	if(v>ui.progressBar->maximum()){
		v=0;
	}
	ui.progressBar->setValue(v);
}
QByteArray	LearningServer::GetLibData(int LibType, int LibID)
{
	if(Executer!=NULL){
		for(AlgorithmThresholdPointer *a=Executer->AThrContainer.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetLibType()==LibType && a->GetLibID()==LibID){
				LearnigAlgorithmThresholdPointer	*Lp=dynamic_cast<LearnigAlgorithmThresholdPointer *>(a);
				AlgorithmThreshold	*Thr=Lp->GetThreshold();
				QBuffer	Buff;
				Buff.open(QIODevice::WriteOnly);
				Thr->Save(&Buff);
				return Buff.buffer();
			}
		}
	}
	return QByteArray();
}
void LearningServer::on_tableWidgetAlgorithmThreshold_clicked(const QModelIndex &index)
{
	int	ARow=ui.tableWidgetAlgorithmThreshold->currentRow();
	AlgorithmThresholdPointerPointer *a=AlgorithmThresholdPP.GetItem(ARow);
	if(a==NULL)
		return;
	ReportedTopicContainer RetContainer;
	a->GetThreshold()->MakeReportedTopics(RetContainer);

	ui.tableWidgetThresholdProperty->setRowCount(RetContainer.GetCount());
	int	Row=0;
	for(ReportedTopic *L=RetContainer.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui.tableWidgetThresholdProperty, 0, Row, L->Title);
		::SetDataToTable(ui.tableWidgetThresholdProperty, 1, Row, L->Data);
	}
}

bool	LearningServer::CheckLearningListInDB(void)
{
	bool	ModeChangeList=false;
	GetLayersBase()->GetDatabaseLoader()->G_LockDB();
	{
		QString	S=QString(	/**/"SELECT LEARNINGID,MACHINEID,SAMPLETYPE,PRIORITY FROM LEARNING ORDER BY UPDATETIME;");
		QSqlQuery query(S,ServerBaseData->GetDatabase());
		while(query.next ()==true){
			int	LearningID	=query.value(query.record().indexOf(/**/"LEARNINGID")	).toInt();
			int	MachineID	=query.value(query.record().indexOf(/**/"MACHINEID")	).toInt();
			int	SampleType	=query.value(query.record().indexOf(/**/"SAMPLETYPE")	).toInt();
			int	Priority	=query.value(query.record().indexOf(/**/"PRIORITY"	)	).toInt();

			bool	Found=false;
			for(LearningInDB *d=Executer->LearningList.GetFirst();d!=NULL;d=d->GetNext()){
				if(d->LearningID==LearningID){
					d->MachineID	=MachineID;
					d->SampleType	=SampleType;
					d->Priority		=Priority;
					Found=true;
					break;
				}
			}
			if(Found==false){
				LearningInDB	*d=new LearningInDB();
				d->LearningID=LearningID;
				d->SampleType	=SampleType;
				d->Priority		=Priority;
				GetLayersBase()->GetDatabaseLoader()->G_LoadLearningInDB(ServerBaseData->GetDatabase(),LearningID,*d);
				Executer->LearningList.AppendList(d);
				ModeChangeList=true;
			}
		}
		for(LearningInDB *d=Executer->LearningList.GetFirst();d!=NULL;){
			LearningInDB *DNext=d->GetNext();
			int	LearningID	=d->LearningID;
			QString	S=QString(	/**/"SELECT "
							/**/"SAMPLETYPE,XSIZE ,YSIZE ,LAYER ,MASTERIMAGE ,TARGETIMAGE ,POINTDATA,MASTERCODE "
							/**/"FROM LEARNING WHERE LEARNINGID=")
							+QString::number(LearningID);
		
			QSqlQuery query(S ,ServerBaseData->GetDatabase());
			if(query.next ()==false){
				Executer->LearningList.RemoveList(d);
				delete	d;
				ModeChangeList=true;
			}
			d=DNext;
		}
	}
	GetLayersBase()->GetDatabaseLoader()->G_UnlockDB();
	return ModeChangeList;
}
void LearningServer::on_tableWidgetExecuter_doubleClicked(const QModelIndex &index)
{
	int	Row=ui.tableWidgetExecuter->currentRow();
	LearningInDB *a=Executer->LearningList.GetItem(Row);
	if(a!=NULL){
		ui.tabWidget->setCurrentIndex(0);

		QSqlLearningModel	*M=dynamic_cast<QSqlLearningModel	 *>(ui.tableViewRegisteredData->model());
		if(M!=NULL){
			M->select();
			for(int row=0;;row++){
				bool	ok;
				int LearningID = M->record(row).value("LEARNINGID").toInt(&ok);
				if(ok==false){
					break;
				}
				if(LearningID==a->LearningID){
					ui.tableViewRegisteredData->selectRow(row);
					break;
				}
			}
		}
		SelectedLearningID=a->LearningID;
		ShowLearning(SelectedLearningID);
	}
}
	
int		LearningServer::ExecuteProcess(LearningInDB *LearningInDBPoint,LearningParamInDB *Param
									,DetailResultInfoListContainer &RetList)
{
	AlgorithmThreshold	*AThr=AlgorithmThresholdPP.FindAlgorithmThreshold(Param->LibType , Param->LibID);
	if(AThr!=NULL){
		bool Ret;
		//if(LearningInDBPoint->LayerForCalc!=NULL){
		//	delete	LearningInDBPoint->LayerForCalc;
		//	LearningInDBPoint->LayerForCalc=NULL;
		//}
		//if(LearningInDBPoint->EPointForCalc!=NULL){
		//	delete	LearningInDBPoint->EPointForCalc;
		//	LearningInDBPoint->EPointForCalc=NULL;
		//}
		Executer->CalcProcess(LearningInDBPoint,Param
							,AThr
							,Ret);
		
		if(Ret==true){
			return 1;
		}
		else{
			RetList=Param->ResultList;
			return 2;
		}
	}

	return -1;
}
bool	LearningServer::SetThreshold(int LibType,int LibID,QByteArray &ItemData)
{
	AlgorithmThreshold	*Thr=AlgorithmThresholdPP.FindAlgorithmThreshold(LibType,LibID);
	if(Thr!=NULL){
		AlgorithmItemRoot	*sItem=Thr->GetParentItem();
		if(sItem!=NULL){
			AlgorithmItemRoot	*Item=sItem->Clone();
			LayersBase	*LBase=Thr->GetLayersBase();
			QBuffer	Buff(&ItemData);
			Buff.open(QIODevice::ReadOnly);
			if(Item->Load(&Buff,LBase)==true){
				Thr->CopyFrom(*Item->GetThresholdBaseReadable());
			}
			delete	Item;
		}
	}
	return false;
}

void LearningServer::on_tableWidgetAlgorithmThreshold_cellDoubleClicked(int row, int column)
{
	int	ARow=ui.tableWidgetAlgorithmThreshold->currentRow();

	ui.pushButtonExecute->setChecked(false);
	on_pushButtonExecute_clicked();

	GetLayersBase()->ShowProcessingForm("Stop processing...");
	while(Executer->Running==true){
		GSleep(100);
		GetLayersBase()->StepProcessing(0);
	}
	GetLayersBase()->CloseProcessingForm();

	AlgorithmThresholdPointerPointer *a=AlgorithmThresholdPP.GetItem(ARow);
	if(a==NULL)
		return;

	if(CurrentAlgoWindow!=NULL){
		CurrentAlgoWindow->close();
		CurrentAlgoWindow=NULL;
	}
	AlgorithmThreshold	*Thr=a->GetThreshold();
	AlgorithmItemRoot	*Item=Thr->GetParentItem();
	LayersBase	*LBase=Thr->GetLayersBase();
	AlgorithmBase	*ABase=LBase->GetAlgorithmBase(a->GetLibType());
	LogicDLL		*L=ABase->GetLogicDLL();

	if(IndependentPackData!=NULL){
		delete	IndependentPackData;
	}
	IndependentPackData=new AlgorithmItemIndependentPack(LBase);

	AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(LBase);
	A->Data=Item->Clone();
	//((AlgorithmItemPI *)(A->Data))->SetParent(this);
	//*A->Data	=*Item;
	A->Data->GetThresholdBaseWritable()->CopyFrom(*Thr);
	A->PhaseCode=Item->GetPhaseCode();
	A->Layer	=0;
	A->ItemID	=Item->GetID();
	A->LibID	=Item->GetLibID();
	A->ItemClassType=Item->GetItemClassType();
	A->Result	=(Item->GetCurrentResult()!=NULL)?Item->GetCurrentResult()->GetError():-1;
	A->GlobalPage=0;
	ABase->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
	IndependentPackData->Items.AppendList(A);

	int		x1,y1,x2,y2;
	if(Item->GetXY(x1,y1,x2,y2)==false){
		x1=0;
		y1=0;
		IndependentPackData->LocalX=Item->GetDotPerLine()/2;
		IndependentPackData->LocalY=Item->GetMaxLines()  /2;
	}
	else{
		IndependentPackData->LocalX	=(x1+x2)/2;
		IndependentPackData->LocalY	=(y1+y2)/2;
	}
	L->ShowAndSetItems(this, 0,ABase ,*IndependentPackData,NULL);

	if(ConfirmFormInst!=NULL){
		ConfirmFormInst->close();
		ConfirmFormInst->deleteLater();
	}
	CurrentAlgoWindow	=dynamic_cast<AlgorithmComponentWindow *>(L->GetShowAndSetItemsForm());
	ConfirmFormInst=new ConfirmForm(Item->GetPage(),this,L,CurrentAlgoWindow);
	ConfirmFormInst->SetLibrary(Item->GetLibType(),Item->GetLibID());
	ConfirmFormInst->show();
}

void	LearningServer::SetItemDataInWindow(LearningInDB *LearningInDBPoint,LearningParamInDB *From)
{
	AlgorithmThreshold	*Thr=AlgorithmThresholdPP.FindAlgorithmThreshold(From->LibType,From->LibID);
	LayersBase	*LBase=LearningInDBPoint->LayerForCalc;
	AlgorithmBase	*ABase=LBase->GetAlgorithmBase(From->LibType);
	LogicDLL		*L=ABase->GetLogicDLL();

	if(ABase==NULL){
		return;
	}
	AlgorithmInPageInOnePhase	*Ah=ABase->GetPageDataPhase(0);
	if(Ah==NULL){
		return;
	}
	AlgorithmInPageRoot		*Ap=Ah->GetPageData(0);
	if(Ap==NULL){
		return;
	}
	QPoint	CurrentPosition;
	if(CurrentAlgoWindow!=NULL){
		CurrentPosition=CurrentAlgoWindow->geometry().topLeft();
		CurrentAlgoWindow->close();
		CurrentAlgoWindow=NULL;
	}
	AlgorithmItemRoot	*Item=NULL;
	AlgorithmItemPointerListContainer ItemPointers;
	Ap->EnumAllItems(ItemPointers);
	for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*AItem=a->GetItem();
		if(AItem->GetLibID()==From->LibID){
			Item=AItem;
			break;
		}
	}
	if(Item==NULL)
		return;

	if(IndependentPackData!=NULL){
		delete	IndependentPackData;
	}
	IndependentPackData=new AlgorithmItemIndependentPack(LBase);

	AlgorithmItemIndependent	*A=new AlgorithmItemIndependent(LBase);
	A->Data=Item->Clone();
	//((AlgorithmItemPI *)(A->Data))->SetParent(this);
	//*A->Data	=*Item;
	A->Data->GetThresholdBaseWritable()->CopyFrom(*Thr);
	A->PhaseCode=Item->GetPhaseCode();
	A->Layer	=0;
	A->ItemID	=Item->GetID();
	A->LibID	=Item->GetLibID();
	A->ItemClassType=Item->GetItemClassType();
	A->Result	=(Item->GetCurrentResult()!=NULL)?Item->GetCurrentResult()->GetError():-1;
	A->GlobalPage=0;
	ABase->GetDLLName(A->AlgorithmRoot,A->AlgorithmName);
	IndependentPackData->Items.AppendList(A);

	int		x1,y1,x2,y2;
	if(Item->GetXY(x1,y1,x2,y2)==false){
		x1=0;
		y1=0;
		IndependentPackData->LocalX=Item->GetDotPerLine()/2;
		IndependentPackData->LocalY=Item->GetMaxLines()  /2;
	}
	else{
		IndependentPackData->LocalX	=(x1+x2)/2;
		IndependentPackData->LocalY	=(y1+y2)/2;
	}
	L->ShowAndSetItems(this, 0,ABase ,*IndependentPackData,NULL);
	CurrentAlgoWindow	=dynamic_cast<AlgorithmComponentWindow *>(L->GetShowAndSetItemsForm());
	if(CurrentPosition.isNull()==false){
		CurrentAlgoWindow->move(CurrentPosition);
	}
	ConfirmFormInst->SetShowAndSetItems(CurrentAlgoWindow);
}
