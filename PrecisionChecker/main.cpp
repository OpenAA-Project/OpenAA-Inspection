#include <QApplication>
#include <QTranslator>
#include "PrecisionChecker.h"

#include "XDataInLayer.h"
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

	EntryPointBase	*e	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(e);
	e->SetLayersBase(Layers);

	Layers->GetParamGlobal()->AllocateMasterBuff=true;
	Layers->GetParamGlobal()->AllocateTargetBuff=false;

	Layers->InitialCreatePages(NULL);


	QLocale::setDefault(QLocale::Japanese);
	QTranslator Translator;
	bool ret = Translator.load("precisionchecker_ja");
	qApp->installTranslator(&Translator);

	PrecisionChecker w(Layers);
	w.move(0,0);
	w.show();

	return a.exec();
}
