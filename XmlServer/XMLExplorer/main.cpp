#include "XMLExplorer.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);
	XMLExplorer w;
	w.show();
	return a.exec();
}
