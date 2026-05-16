/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "IntegrationShowTotalResource.h"
#include "IntegrationShowTotalForm.h"
#include "ui_IntegrationShowTotalForm.h"
#include "XIntegrationBasePacket.h"
#include "XDatabaseLoader.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XGeneralFunc.h"
#include "XDLLType.h"
#include <QTemporaryFile>
#include <QFileDialog>
#include <QBuffer>


IntegrationShowTotalForm::IntegrationShowTotalForm(LayersBase *Base ,QWidget *parent) :
	GUIFormBase(Base,parent),
    ui(new Ui::IntegrationShowTotalForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	ModeShowTotal		=true;
	ModeShowAllResult	=true;
	ModeShowEachResult	=true;

	InfoOkNgDim		=NULL;
	InfoOkNgDimCount=0;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationShowTotalForm::~IntegrationShowTotalForm()
{
    delete ui;
	if(InfoOkNgDim!=NULL){
		delete	[]InfoOkNgDim;
		InfoOkNgDim=NULL;
	}
	InfoOkNgDimCount=0;
}
	
void	IntegrationShowTotalForm::ReadyParam(void)
{
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalDoneLoadResult(InspectionList *)),this,SLOT(SlotDoneLoadResult(InspectionList *)));
	InfoOkNgDimCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	InfoOkNgDim=new struct	InfoOkNg[InfoOkNgDimCount];

	QStringList	VLabels;
	if(ModeShowTotal==true){
		VLabels.append(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_1)/*"総検査数"*/);
	}
	if(ModeShowAllResult==true){
		VLabels.append(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_2)/*"総OK数"*/);
		VLabels.append(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_3)/*"総NG数"*/);
	}
	if(ModeShowEachResult==true){
		int	OkNgRowCount=0;
		for(int i=0;i<InfoOkNgDimCount;i++){
			EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(M!=NULL && M->IsDependent()==false){
				QString	Str=M->GetMachineName();
				VLabels.append(Str+QString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_4)/*"OK"*/));
				OkNgRowCount++;
			}
		}
		for(int i=0;i<InfoOkNgDimCount;i++){
			EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(M!=NULL && M->IsDependent()==false){
				QString	Str=M->GetMachineName();
				VLabels.append(Str+QString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_5)/*"NG"*/));
				OkNgRowCount++;
			}
		}
	}
	ui->tableWidget->setRowCount(VLabels.count());
	ui->tableWidget->setVerticalHeaderLabels(VLabels);
	on_PushButtonReset_clicked();
}

void	IntegrationShowTotalForm::ResizeAction()
{
	ui->frame->move(0,height()-ui->frame->height());
	ui->frame->resize(width(),ui->frame->height());
	int	Space=(width()-ui->PushButtonReset->width()-ui->pushButtonExcelSave->width())/3;
	ui->PushButtonReset->move(Space,ui->PushButtonReset->geometry().top());
	ui->pushButtonExcelSave->move(2*Space+ui->PushButtonReset->width(),ui->PushButtonReset->geometry().top());
	ui->tableWidget->resize(width(),height()-ui->frame->height());
	int	VWidth=ui->tableWidget->verticalHeader()->width();
	ui->tableWidget->setColumnWidth(0,width()-VWidth);
}

void	IntegrationShowTotalForm::ShowData(void)
{
	int	TotalCount	=GetLayersBase()->GetIntegrationBasePointer()->TotalCount;
	int	NGCount		=GetLayersBase()->GetIntegrationBasePointer()->NGCount;

	int	CRow=0;
	if(ModeShowTotal==true){
		::SetDataToTable(ui->tableWidget,0 ,CRow ,QString::number(TotalCount));
		CRow++;
	}
	if(ModeShowAllResult==true){
		::SetDataToTable(ui->tableWidget,0 ,CRow ,QString::number(TotalCount-NGCount));
		CRow++;
		::SetDataToTable(ui->tableWidget,0 ,CRow ,QString::number(NGCount));
		CRow++;
	}

	for(int i=0;i<InfoOkNgDimCount;i++){
		EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(M!=NULL && M->IsDependent()==false){
			int	MachineID=M->GetMachineCode();
			int	NGCount		=0;
			int	TotalCount	=0;
			EachMaster *Pointer[10];
			int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
			for(int m=0;m<MasterCount;m++){
				NGCount		+=Pointer[m]->GetCurrentInspection().NGCount;
				TotalCount	+=Pointer[m]->GetCurrentInspection().TotalCount;
			}
			if(ModeShowEachResult==true){
				::SetDataToTable(ui->tableWidget,0 ,CRow  ,QString::number(TotalCount-NGCount));
				CRow++;
			}
		}
	}
	for(int i=0;i<InfoOkNgDimCount;i++){
		EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(M!=NULL && M->IsDependent()==false){
			int	MachineID=M->GetMachineCode();
			int	NGCount		=0;
			int	TotalCount	=0;
			EachMaster *Pointer[10];
			int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
			for(int m=0;m<MasterCount;m++){
				NGCount		+=Pointer[m]->GetCurrentInspection().NGCount;
				TotalCount	+=Pointer[m]->GetCurrentInspection().TotalCount;
			}
			if(ModeShowEachResult==true){
				::SetDataToTable(ui->tableWidget,0 ,CRow,QString::number(NGCount));
				CRow++;
			}
		}
	}
}
void	IntegrationShowTotalForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	if(CmdChangeLotIDVar!=NULL || CmdUpdatedMasterImageVar!=NULL || CmdChangeNewLotIDVar!=NULL){
		for(int i=0;i<InfoOkNgDimCount;i++){
			InfoOkNgDim[i].NGCount=0;
			InfoOkNgDim[i].OKCount=0;
		}
		ShowData();
		return;
	}
}

void	IntegrationShowTotalForm::SlotDoneLoadResult(InspectionList *n)
{
	ShowData();
	emit	SignalUpdated();
}


void	IntegrationShowTotalForm::WriteCell(int Row, int Col ,const QString &Str)
{
	// xlsxwriterはUTF-8を使用する
	worksheet_write_string(XLSXSheet, Row, Col, Str.toUtf8().constData(), Lang);
}

void	IntegrationShowTotalForm::WriteCellV(int Row, int Col ,const QVariant &Data)
{
	if(Data.type()==QVariant::Bool){
		if(Data.toBool()==true){
			worksheet_write_boolean(XLSXSheet, Row, Col, 1, Lang);
		}
		else{
			worksheet_write_boolean(XLSXSheet, Row, Col, 0, Lang);
		}
	}
	else if(Data.type()==QVariant::Char){
		QString	s(Data.toChar());
		worksheet_write_string(XLSXSheet, Row, Col, s.toUtf8().constData(), Lang);
	}
	else if(Data.type()==QVariant::Date){
		QString	s(Data.toDate().toString());
		worksheet_write_string(XLSXSheet, Row, Col, s.toUtf8().constData(), Lang);
	}
	else if(Data.type()==QVariant::DateTime){
		QString	s(Data.toDateTime().toString());
		worksheet_write_string(XLSXSheet, Row, Col, s.toUtf8().constData(), Lang);
	}
	else if(Data.type()==QVariant::Double){
		worksheet_write_number(XLSXSheet, Row, Col, Data.toDouble(), Lang);
	}
	else if(Data.type()==QVariant::Int){
		worksheet_write_number(XLSXSheet, Row, Col, Data.toDouble(), Lang);
	}
	else if(Data.type()==QVariant::String){
		QString	s=Data.toString();
		worksheet_write_string(XLSXSheet, Row, Col, s.toUtf8().constData(), Lang);
	}
	else if(Data.type()==QVariant::Time){
		QString	s(Data.toTime().toString());
		worksheet_write_string(XLSXSheet, Row, Col, s.toUtf8().constData(), Lang);
	}
	else if(Data.type()==QVariant::UInt){
		worksheet_write_number(XLSXSheet, Row, Col, Data.toDouble(), Lang);
	}
	else{
		worksheet_write_string(XLSXSheet, Row, Col, "Error", Lang);
	}
}

void IntegrationShowTotalForm::on_pushButtonExcelSave_clicked()
{
	QString	ExcelFileName=QFileDialog::getSaveFileName(NULL
													,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_6)/*"Save EXCEL"*/
													,QString()
													,/**/"Excel(*.xlsx);;All files(*.*)");
	if(ExcelFileName.isEmpty()==true)
		return;

	IntegrationBase	*MBase=GetLayersBase()->GetIntegrationBasePointer();
	EachMaster		*M0=MBase->GetMaster(0);
	if(M0==NULL)
		return;

	QString	RetRelationNumber;
	QString	RetRelationName;
	QString	RetRemark;
	int		RetRelationType;
	QByteArray	CommonData;
	int32	ThresholdLevelID;
	if(MBase->GetInformation(RetRelationNumber
							,RetRelationName
							,RetRemark
							,RetRelationType
							,CommonData
							,ThresholdLevelID)==false){
		return;
	}

	XLSXBook = workbook_new(ExcelFileName.toUtf8().constData());
	XLSXSheet = workbook_add_worksheet(XLSXBook, "Master");

	Lang = workbook_add_format(XLSXBook);
	QString	FontName;
	switch(GetLayersBase()->GetLanguageCode()){
		case 0:	FontName= /**/"ＭＳ Ｐゴシック";	break;
		case 1:	FontName= /**/"Arial";				break;
		case 2:	FontName= /**/"SimSun";				break;
		case 3:	FontName= /**/"MingLiU";			break;
		case 4:	FontName= /**/"Gulim";				break;
	}
	format_set_font_name(Lang, FontName.toUtf8().constData());

	WriteCell(0, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_12)/*"作成日時"*/);	
	WriteCell(0, 1,QDateTime::currentDateTime().toString());

	WriteCell(1, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_13)/*"マスター"*/);
	WriteCell(1, 1,QString::number(MBase->GetMasterRelationCode()));
	WriteCell(2, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_14)/*"名称"*/);
	WriteCell(2, 1,RetRelationNumber);
	WriteCell(2, 2,RetRelationName);
	WriteCell(3, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_15)/*"備考"*/);
	WriteCell(3, 1,RetRemark);

	WriteCell(4, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_16)/*"ロット"*/);
	if(M0->GetCurrentLot()!=NULL){
		WriteCell(4,1,M0->GetCurrentLot()->LotName);
	}
	else{
		WriteCell(4,1,"ロット無し");
	}
	int	Row=5;

	for(EachMaster *m=MBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		if(m->IsDependent()==true){
			int	MachineID=m->GetMachineCode();
			EachMaster *Pointer[10];
			int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);

			WriteCell(Row, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_17)/*"検査ユニット"*/);
			WriteCell(Row, 1,m->GetMachineName());

			worksheet_set_row(XLSXSheet, Row, 256, NULL);

			QTemporaryFile	TmpImageFile;
			TmpImageFile.setAutoRemove(true);
			if(TmpImageFile.open()==true){
				QString	TmpImageFileName=TmpImageFile.fileName();
				QImage	TopView=LoadDataFromMaster(m->GetMasterCode());
				TopView.save(&TmpImageFile,/**/"PNG");
				TmpImageFile.flush();
				TmpImageFile.close();
				
				// スケール計算（画像を256x256のセル枠に合わせる）
				lxw_image_options options;
				memset(&options, 0, sizeof(lxw_image_options));
				if (!TopView.isNull() && TopView.width() > 0 && TopView.height() > 0) {
					options.x_scale = 256.0 / TopView.width();
					options.y_scale = 256.0 / TopView.height();
				} else {
					options.x_scale = 1.0;
					options.y_scale = 1.0;
				}
				worksheet_insert_image_opt(XLSXSheet, Row, 2, TmpImageFileName.toUtf8().constData(), &options);
			}

			Row++;

			for(int t=0;t<MasterCount;t++){
				int	SlaveNo=Pointer[t]->GetIntegrationSlaveNo();

				IntegrationReqUsageAlgorithm	RCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
				IntegrationAckUsageAlgorithm	ACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
				if(RCmd.Send(SlaveNo,0,ACmd)==true){
					for(AlgorithmRootNameList *a=ACmd.Datas.GetFirst();a!=NULL;a=a->GetNext()){
						IntegrationReqReportedTopics	ItemRCmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);
						IntegrationAckReportedTopics	ItemACmd(GetLayersBase(),/**/"ANY",/**/"ANY",SlaveNo);

						ItemRCmd.DLLRoot=a->DLLRoot;
						ItemRCmd.DLLName=a->DLLName;

						QStringList	TopicTitleList;

						if(ItemRCmd.Send(SlaveNo,0,ItemACmd)==true){
							for(ReportedTopicsInItem *Item=ItemACmd.Datas.GetFirst();Item!=NULL;Item=Item->GetNext()){
								QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(),a->LibType,Item->LibID);
								WriteCell(Row, 0,QString::number(Item->LibID));
								WriteCell(Row, 1,LibName);
								int	Col=2;
								for(ReportedTopic *t=Item->TopicsContainer.GetFirst();t!=NULL;t=t->GetNext(),Col++){
									WriteCell(Row, Col,t->Title);
								}
								Row++;
								Col=2;
								for(ReportedTopic *t=Item->TopicsContainer.GetFirst();t!=NULL;t=t->GetNext(),Col++){
									WriteCellV(Row, Col,t->Data);
								}
								Row++;
							}
						}
					}
				}
			}
		}
	}

	WriteCell(Row, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_19)/*"全体検査数"*/);
	WriteCell(Row, 1,QString::number(GetLayersBase()->GetIntegrationBasePointer()->TotalCount));
	Row++;
	WriteCell(Row, 0,LangSolver.GetString(IntegrationShowTotalForm_LS,LID_20)/*"全体NG数"*/);
	WriteCell(Row, 1,QString::number(GetLayersBase()->GetIntegrationBasePointer()->NGCount));
	Row++;


	InspectionList	*L[10000];
	for(int i=0;i<InfoOkNgDimCount;i++){
		EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(M!=NULL && M->IsDependent()==false){
			int	MachineID=M->GetMachineCode();
			int	NGCount		=0;
			int	TotalCount	=0;
			EachMaster *Pointer[10];
			int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
			for(int m=0;m<MasterCount;m++){
				NGCount		+=Pointer[m]->GetCurrentInspection().NGCount;
				TotalCount	+=Pointer[m]->GetCurrentInspection().TotalCount;
			}

			QString	Str=M->GetMachineName();

			WriteCell(Row, 0,Str+QString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_21)/*"NG数"*/));
			WriteCell(Row, 1,QString::number(NGCount));
			L[i]=M->GetCurrentInspection().GetLast();
			Row++;
		}
		else
		if(M!=NULL){
			L[i]=M->GetCurrentInspection().GetLast();
		}
		else{
			L[i]=NULL;
		}
	}

	int	Printout_MaxCountfNGImage=10000;
	int	N=0;
	while(N<Printout_MaxCountfNGImage){
		int	EffectiveNumb=0;
		for(int i=0;i<InfoOkNgDimCount;i++){
			if(L[i]!=NULL){
				N=SetNGImageToExcel(L[i],Printout_MaxCountfNGImage,N,Row);
				L[i]=L[i]->GetPrev();
				EffectiveNumb++;
			}
		}
		if(EffectiveNumb==0){
			break;
		}
	}

	workbook_close(XLSXBook);
	XLSXBook = NULL;
	return;
}

QStringList	IntegrationShowTotalForm::GetInformation(InspectionList *L,NGPoint *Rp)
{
	QString	CauseStr;
	QString	LibName;
	DetailResultInfoListContainer ItemDetailList;
	if(Rp->LibType!=0){
		if(Rp->LibID>=0){
			LibName=GetLayersBase()->GetIntegrationBasePointer()->GetLibraryName(Rp->LibType ,Rp->LibID);
		}
		if(Rp->ResultType==_ResultDouble){
			CauseStr=QString::number(Rp->DoubleCause,'f',2)
					+QString('[')
					+QString::number(L->GetMaster()->TransformPixelToUnit(Rp->Cause[0]),'f',2)
					+QString(']');
		}
		else{
			if((Rp->PosResult&0xFF)==2){
				CauseStr=QString::number(Rp->Cause[1])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnit(Rp->Cause[1]),'f',2)
						+QString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_22)/*"mm]"*/);
			}
			else{
				CauseStr=QString::number(Rp->Cause[0])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnitSquare(Rp->Cause[0]),'f',2)
						+QString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_23)/*"mm2]"*/);
			}
		}
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Rp->LibType);
		if(ABase!=NULL){
			QRgb		NGColor;

			ResultPosList	RPos;
			RPos.result		=Rp->PosResult;
			if(Rp->ResultType==_ResultDouble){
				RPos.SetResult(Rp->DoubleCause);
			}
			else
			if(Rp->ResultType==_ResultDWORD){
				RPos.SetResult1(Rp->Cause[0]);
				RPos.SetResult2(Rp->Cause[1]);
			}
			RPos.Px			=Rp->MasterX;
			RPos.Py			=Rp->MasterY;
			RPos.Rx			=Rp->HX;
			RPos.Ry			=Rp->HY;

			ABase->GetDrawResultDetail(NULL ,&RPos ,ItemDetailList);
		}
	}
	else{
		LibName=Rp->Message;
		if(Rp->ResultType==_ResultDouble){
			CauseStr=QString::number(Rp->DoubleCause,'f',2);
		}
	}

	QStringList	Ret;
	if(LibName.isEmpty()==false){
		Ret.append(LibName
					+QString(/**/",")
					+CauseStr);
	}
	else{
		Ret.append(CauseStr);
	}
	Ret.append(L->InspectionTime.toString(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_24)/*"hh:mm:ss"*/)
				+QString(/**/" (")
				+QString::number(L->ID)
				+QString(/**/")"));
	if(ItemDetailList.count()>0){
		DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
		Ret.append(L->GetInfoString());
	}

	return Ret;
}
QImage IntegrationShowTotalForm::LoadDataFromMaster(int masterCode)
{
	QString	S=QString(/**/"SELECT"
							/**/" TOPVIEW"
							/**/" from MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		QByteArray	STopview=query.value(query.record().indexOf(LangSolver.GetString(IntegrationShowTotalForm_LS,LID_25)/*"TOPVIEW"*/)).toByteArray();
		QBuffer	TopviewBuff;
		TopviewBuff.setData(STopview);
		if(TopviewBuff.open(QIODevice::ReadOnly)==true){
			QImage	TopView;
			if(TopView.load(&TopviewBuff,/**/"PNG")==true){
				return TopView;
			}
		}
	}
	return QImage();
}

int	IntegrationShowTotalForm::SetNGImageToExcel(InspectionList *L, int Printout_MaxCountfNGImage ,int N,int &Row)
{
	if(N>=Printout_MaxCountfNGImage){
		return N;
	}
	for(NGPointInAllPage *Ph=L->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
		for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
			for(IntegNGImage *g=Pg->NGImages.GetFirst();g!=NULL;g=g->GetNext()){
				WriteCell(Row, 0,L->GetMaster()->GetMachineName());
				WriteCell(Row, 1,L->InspectionTime.toString(/**/"yyyy/MM/dd-hh:mm:ss"));

				QTemporaryFile	TmpImageFile;
				TmpImageFile.setAutoRemove(true);
				if(TmpImageFile.open()==true){
					worksheet_set_row(XLSXSheet, Row, 256, NULL);
					QString	TmpImageFileName=TmpImageFile.fileName();
					g->GetImage().save(&TmpImageFile,/**/"PNG");
					TmpImageFile.flush();
					TmpImageFile.close();
					
					// 倍率は等倍（1.0）としてオリジナルサイズで貼り付け
					worksheet_insert_image(XLSXSheet, Row, 2, TmpImageFileName.toUtf8().constData());
				}
				for(NGPoint *Rp=Pg->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
					int	TargetCx,TargetCy;
					Rp->GetTargetCenter(TargetCx,TargetCy);
					if(Rp->IsNG()==true
					&& g->x1 <=TargetCx && TargetCx<g->x2
					&& g->y1 <=TargetCy && TargetCy<g->y2){
						QString	LibName=GetLayersBase()->GetDatabaseLoader()->G_GetLibraryName2(*GetLayersBase()->GetDataBase(), Rp->LibType,Rp->LibID);
						WriteCell(Row, 3,QString::number(Rp->LibID));
						QStringList	List=GetInformation(L,Rp);
						for(int e=0;e<List.count();e++){
							QString	Str=List[e];
							WriteCell(Row, 4+e,Str);
						}
						break;
					}
				}
				Row++;
				N++;
				if(N>=Printout_MaxCountfNGImage){
					return N;
				}
			}
		}
	}
	return N;
}
void IntegrationShowTotalForm::on_PushButtonReset_clicked()
{
	GetLayersBase()->GetIntegrationBasePointer()->TotalCount	=0;
	GetLayersBase()->GetIntegrationBasePointer()->NGCount		=0;

	for(int i=0;i<InfoOkNgDimCount;i++){
		InfoOkNgDim[i].NGCount=0;
		InfoOkNgDim[i].OKCount=0;

		EachMaster	*M		=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(M!=NULL){
			M->ResetCounterCurrentInspection();
		}
	}
	ShowData();

	CmdClearCounter	ICmd;
	BroadcastSpecifiedDirectly(&ICmd);
}