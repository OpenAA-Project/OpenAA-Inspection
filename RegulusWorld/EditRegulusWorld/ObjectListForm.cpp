#include "ObjectListForm.h"
#include "ui_ObjectListForm.h"
#include "EditRegulusWorld.h"

ObjectListForm::ObjectListForm(EditRegulusWorld *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::ObjectListForm)
{
    ui->setupUi(this);

    Splitter= new QSplitter(this);
    Splitter->setOrientation(Qt::Vertical);
    Splitter->addWidget(ui->treeWidget);
    Splitter->addWidget(ui->tableWidgetProperty);
}

ObjectListForm::~ObjectListForm()
{
    delete ui;
}

void ObjectListForm::resizeEvent(QResizeEvent *event)
{
    Splitter->setGeometry(0,0,width(),height());
}
