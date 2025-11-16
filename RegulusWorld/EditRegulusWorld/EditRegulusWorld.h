#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EditRegulusWorld.h"
#include "XRegulusWorld.h"

class ObjectDesignerForm;
class ObjectListForm;
class World3DForm;

class EditRegulusWorld : public QMainWindow
{
    Q_OBJECT

    RegulusWorld    *WorldBase;
    ObjectDesignerForm  *ObjectDesigner;
    ObjectListForm      *ObjectList;
    World3DForm         *World3D;

public:
    EditRegulusWorld(QWidget *parent = nullptr);
    ~EditRegulusWorld();

    RegulusWorld    *GetWorldBase(void) {   return WorldBase;   }
private:
    Ui::EditRegulusWorldClass ui;
};
