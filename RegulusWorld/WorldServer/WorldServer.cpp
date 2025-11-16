#include "WorldServer.h"

WorldServer::WorldServer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    WorldBase   =new RegulusWorld(true);
}

WorldServer::~WorldServer()
{}
