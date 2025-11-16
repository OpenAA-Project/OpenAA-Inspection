#include "EditRegulusWorld.h"
#include "ObjectDesignerForm.h"
#include "ObjectListForm.h"
#include "World3DForm.h"

EditRegulusWorld::EditRegulusWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    WorldBase=new RegulusWorld();

    ObjectDesigner  =new ObjectDesignerForm(this);
    ObjectDesigner->show();
    ObjectList      =new ObjectListForm(this);
    ObjectList->show();
    World3D         =new World3DForm(this);
    World3D->show();
}

EditRegulusWorld::~EditRegulusWorld()
{}
