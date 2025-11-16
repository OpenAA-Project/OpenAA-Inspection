#include "ConvertPixImage.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include <QFileInfo>
#include "XIntClass.h"

ConvertPixImage::ConvertPixImage(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	ui.tableWidgetPixFile->setColumnWidth(0,500);
	ui.tableWidgetPixFile->setColumnWidth(1,200);
}

ConvertPixImage::~ConvertPixImage()
{

}

void	ConvertPixImage::ShowList(void)
{
	int	N=PixFileContainer.GetCount();

	ui.tableWidgetPixFile->setRowCount(N);
	int	row=0;
	for(PixFileList *a=PixFileContainer.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui.tableWidgetPixFile ,0,row ,a->Path);
		::SetDataToTable(ui.tableWidgetPixFile ,1,row ,a->FileName);
	}
}
void ConvertPixImage::on_pushButtonAddPixFile_clicked()
{
	QStringList	FileNames=QFileDialog::getOpenFileNames ( NULL, "Add PIX file", LastDir, "Pix file (*.pix)");
	for(int i=0;i<FileNames.count();i++){
		QString	FileName=FileNames[i];
		QFileInfo	Info(FileName);
		PixFileList	*a=new PixFileList();
		a->Path		=Info.path();
		LastDir		=Info.path();
		a->FileName	=Info.fileName();
		PixFileContainer.AppendList(a);
	}
	ShowList();
}

void ConvertPixImage::on_pushButtonAddPixFolder_clicked()
{
	QString FolderName=QFileDialog::getExistingDirectory (NULL, "Pix folder", LastDir);
	if(FolderName.isEmpty()==false){
		LastDir=FolderName;
		QDir	Dir(FolderName);
		QStringList	List;
		List.append("*.pix");
		QFileInfoList	InfoList=Dir.entryInfoList(List,QDir::Files);
		for(int i=0;i<InfoList.count();i++){
			PixFileList	*a=new PixFileList();
			a->Path		=InfoList[i].path();
			a->FileName	=InfoList[i].fileName();
			PixFileContainer.AppendList(a);
		}
		ShowList();
	}
}

void ConvertPixImage::on_pushButtonFindPath_clicked()
{
	QString FolderName=QFileDialog::getExistingDirectory (NULL, "Output folder", LastDir);
	if(FolderName.isEmpty()==false){
		ui.lineEditOutputPath	->setText(FolderName);
	}
}	

void ConvertPixImage::on_pushButtonExecuteConvert_clicked()
{
	for(PixFileList *a=PixFileContainer.GetFirst();a!=NULL;a=a->GetNext()){
		ConvertToImage(a,ui.lineEditOutputPath->text(),ui.comboBoxExtension->currentText());
	}
}

void ConvertPixImage::on_pushButtonClose_clicked()
{
	close();
}

void ConvertPixImage::on_pushButtonDeleteList_clicked()
{
	IntList Rows;
	::GetSelectedRows(ui.tableWidgetPixFile ,Rows);

	int	N=Rows.GetCount();
	PixFileList	**Selected=new PixFileList	*[N];
	int	i=0;
	for(IntClass *a=Rows.GetFirst();a!=NULL;a=a->GetNext(),i++){
		Selected[i]=PixFileContainer[a->GetValue()];
	}
	for(int i=0;i<N;i++){
		PixFileContainer.RemoveList(Selected[i]);
		delete	Selected[i];
	}
	delete	[]Selected;

	ShowList();
}

//==============================================================================================

bool	ConvertPixImage::ConvertToImage(PixFileList	*PixFile,const QString &OutPath,const QString &ImgFormat)
{
	QFile	RFile(PixFile->Path+::GetSeparator()+PixFile->FileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	if(Ver>=2){
		if(::Load(&RFile,iPhaseNumb)==false)
			return false;
	}
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;


	QImage	Img(iDotPerLine,iMaxLines,QImage::Format_RGB32);

	for(int phase=0;phase<iPhaseNumb;phase++){
		for(int page=0;page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<iLayerNumb;Layer++){
					QByteArray	Data=RFile.read(YCount*iDotPerLine);
					BYTE	*Src=(BYTE *)Data.data();

					for(int yn=0;yn<YCount;yn++){
						BYTE	*d=Img.scanLine(TopY+yn);
						*(d+3)=0xFF;
						if(Layer==0){
							for(int x=0;x<iDotPerLine;x++){
								*(d+2)=*Src;
								*(d+1)=*Src;
								*(d+0)=*Src;
								d+=4;
								Src++;
							}
						}
						else if(Layer==1){
							for(int x=0;x<iDotPerLine;x++){
								*(d+1)=*Src;
								*(d+0)=*Src;
								d+=4;
								Src++;
							}
						}
						else if(Layer==2){
							for(int x=0;x<iDotPerLine;x++){
								*(d+0)=*Src;
								d+=4;
								Src++;
							}
						}
					}
				}
			}
			QFileInfo	Info(PixFile->FileName);
			QString	OFileName=OutPath+::GetSeparator()+Info.baseName()
				+QString("-Page")+QString::number(page)
				+QString("-Phase")+QString::number(phase)
				+QString(".")+ImgFormat;
			char	Buff[100];
			::QString2Char(ImgFormat, Buff, sizeof(Buff));
			Img.save(OFileName, Buff);
		}
	}
	return true;

}
