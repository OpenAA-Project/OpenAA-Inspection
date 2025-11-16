#include <QtGui>
#include "LightingManager.h"
#include "XShowVersion.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
	if(	(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);
	LightingManager w;

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

//	w.show();
//	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	a.connect(&a, SIGNAL(commitDataRequest(QSessionManager &)),&w,SLOT(SlotCommitDataRequest(QSessionManager &)));
	return a.exec();
}
