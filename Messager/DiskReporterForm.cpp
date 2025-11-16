#include "DiskReporterForm.h"

extern	const	char	*MessagerRegFile;

DiskReporterForm::DiskReporterForm(QWidget *parent)
	: QWidget(parent),FRegistry(MessagerRegFile)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	QRect	r=FRegistry.LoadRegRect("DiskReporter");
	if(r.width()>0 && r.height()>0){
		setGeometry(r);
	}
}

DiskReporterForm::~DiskReporterForm()
{

}

void	DiskReporterForm::resizeEvent( QResizeEvent * event )
{
	ui.listWidget->resize(width()-2,height()-2);
	FRegistry.Save("DiskReporter",geometry());
}

void	DiskReporterForm::SetList(QString Str)
{
	QString	Tag	=Str.section('+',0,0);
	QString	Data=Str.section('+',1);
	XDateTime	BNow=XDateTime::currentDateTime();
	DiskReportList *c;
	for(c=DiskReportData.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Tag==Tag){
			c->FTime=BNow;
			c->Data	=Data;
			break;
		}
	}
	if(c==NULL){
		c=new DiskReportList();
		c->Tag=Tag;
		c->FTime=BNow;
		c->Data=Data;
		DiskReportData.AppendList(c);
	}
PNext:;
	for(DiskReportList *d=DiskReportData.GetFirst();d!=NULL;d=d->GetNext()){
		if(BNow.secsTo(d->FTime)>600){
			DiskReportData.RemoveList(d);
			delete	d;
			goto	PNext;
		}
	}
	ShowList();
}
void	DiskReporterForm::ShowList(void)
{
	ui.listWidget->clear();
	for(DiskReportList *c=DiskReportData.GetFirst();c!=NULL;c=c->GetNext()){
		ui.listWidget->addItem(c->Tag+QString(" ")+c->Data);
	}
}