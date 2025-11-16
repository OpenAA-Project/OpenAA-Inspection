#include "RobotRegulusWorld.h"

RobotRegulusWorld::RobotRegulusWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    WorldBase=new RegulusWorld(); 

	SplitterH	=new QSplitter(this);
	SplitterH	->setOrientation(Qt::Horizontal);
	SplitterH	->addWidget(ui.openGLWidget);
	SplitterH	->addWidget(ui.frame);
	SplitterH	->setGeometry(0,0,width(),height());

	SplitterV	=new QSplitter(ui.frame);
	SplitterV	->setOrientation(Qt::Vertical);
	SplitterV	->addWidget(ui.treeWidgetObject);
	SplitterV	->addWidget(ui.tableWidgetProperty);
	SplitterV	->addWidget(ui.listWidgetCommand);
	SplitterV	->addWidget(ui.widgetExecutePanel);
}

RobotRegulusWorld::~RobotRegulusWorld()
{}

void RobotRegulusWorld::resizeEvent(QResizeEvent *event)
{
	SplitterH->setGeometry(0,0,width(),height());

	SplitterV->setGeometry(0,0,ui.frame->width(),ui.frame->height()-ui.widgetExecutePanel->height());
}

void RobotRegulusWorld::on_toolButtonExecute_clicked()
{

}

void RobotRegulusWorld::on_toolButtonOrigin_clicked()
{

}

