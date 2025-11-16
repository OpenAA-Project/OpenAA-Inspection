#include "ShowResultImageCheckerResource.h"
#include "ShowResultImageCheckerForm.h"
#include "XImageChecker.h"
#include "XGeneralFunc.h"
#include "XCSV.h"

ShowResultImageCheckerForm::ShowResultImageCheckerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnCount(GetPageNumb());

	ModeSaveCSV=false;
	QStringList	Labels;
	for(int page=0;page<GetPageNumb();page++){
		Labels.append(LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_0)/*"Cam/Page"*/);
		ui.tableWidget->setColumnWidth(page,130);
	}
	ui.tableWidget->setHorizontalHeaderLabels(Labels);
	GetParamGUI()->SetParam(&ModeSaveCSV, /**/"ShowResultImageChecker",/**/"ModeSaveCSV",LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_1)/*"Mode of Saving CSV"*/	);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowResultImageCheckerForm::~ShowResultImageCheckerForm()
{

}

void	ShowResultImageCheckerForm::Prepare(void)
{
	ResizeAction();
}
void	ShowResultImageCheckerForm::ResizeAction(void)
{
	ui.tableWidget->resize(width(),ui.tableWidget->height());
}

void ShowResultImageCheckerForm::on_pushButtonUpdate_clicked()
{
	XDateTime	Q=XDateTime::currentDateTime();
	QString		FileName=QString(/**/"ImageCheckerData")
						+Q.toString(/**/"yyMMdd-hhmmss")
						+QString(/**/".csv");
	QStringListListCSV	CsvFile;

	CsvFile.Set(0, 0,LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_2)/*"Page"*/);
	CsvFile.Set(1, 0,ui.tableWidget->verticalHeaderItem(0)->text());
	
	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_3)/*"Update Result image check in CSV"*/);
	QCoreApplication::processEvents();

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyImageChecker" ,/**/"");
	if(GProp!=NULL){
		int	CsvRow=1;

		CmdGetResultPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);

		for(int page=0;page<GetPageNumb();page++){
			if(Da.Effective[page]==true){
				struct	ImageCheckerRegData	*r=&Da.RegData[page];

				ui.tableWidget->setColumnWidth(page,150);
				CsvFile.Set(0,CsvRow,QString::number(page));
				QString	V;
				QString	V1,V2;
				QString	R;

				QString	LightStr;
				if(GetLayerNumb(page)>=1){
					if(r->RegCalcLightWhole[0].Value!=0){
						V=QString(/**/"L0:")+QString::number(r->RegCalcLightWhole[0].Value,'f',1);
						R=V+::GetSeparator();
						if(r->RegCalcLightWhole[0].Ok==true)
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_4)/*"OK"*/;
						else
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_5)/*"NG"*/;
						if(GetLayerNumb(page)<=1){
							R=R+QString(/**/" / Req ");
							R=R+QString::number(r->RegParamEntry.Value[0],'f',1);
						}
						LightStr+=R;
						LightStr+=QString(/**/" ");
					}
				}
				if(GetLayerNumb(page)>=2){
					if(r->RegCalcLightWhole[1].Value!=0){
						V=QString(/**/"L1:")+QString::number(r->RegCalcLightWhole[1].Value,'f',1);
						R=V+::GetSeparator();
						if(r->RegCalcLightWhole[1].Ok==true)
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_6)/*"OK"*/;
						else
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_7)/*"NG"*/;
						LightStr+=R;
						LightStr+=QString(/**/" ");
					}
				}
				if(GetLayerNumb(page)>=3){
					if(r->RegCalcLightWhole[2].Value!=0){
						V=QString(/**/"L2:")+QString::number(r->RegCalcLightWhole[2].Value,'f',1);
						R=V+::GetSeparator();
						if(r->RegCalcLightWhole[2].Ok==true)
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_8)/*"OK"*/;
						else
							R=R+LangSolver.GetString(ShowResultImageCheckerForm_LS,LID_9)/*"NG"*/;
						LightStr+=R;
						LightStr+=QString(/**/" ");
					}
				}
				ui.tableWidget->setColumnWidth(page,70*GetLayerNumb(page));
				SetDataToTable(ui.tableWidget,page,0,LightStr);

				CsvRow++;
			}
			else{
				ui.tableWidget->setColumnWidth(page,60);
				SetDataToTable(ui.tableWidget,page,0,/**/"");
			}
		}
	}
	if(ModeSaveCSV==true){
		CsvFile.SaveFromCSVFile(FileName);
	}
	GetLayersBase()->CloseProcessingForm ();
}

void ShowResultImageCheckerForm::on_tableWidget_clicked(const QModelIndex &)
{

}