#include <QFile>
#include <QBitmap>
#include <QImageReader>
#include <stdlib.h>
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XDataInLayerCommander.h"
#include "XResultDLLManager.h"
#include "XDatabase.h"
#include <omp.h>
#include "XCrossObj.h"
#include "XLanguageClass.h"
#include "ShowThresholdHistgramForm.h"
#include "XHistgramByParam.h"
#include <iostream>
#include "XImageProcess.h"

extern	LangSolverNew	LangLibSolver;

bool	AlgorithmItemRoot::TF_ShowHistgramGraph(int HistID)
{
	int	localPage	=GetPage();
	int	GlobalPage	=GetLayersBase()->GetGlobalPageFromLocal(localPage);
	QString	AlgoRoot;
	QString	AlgoName;
	AlgorithmBase	*ABase=GetParentBase();

	if(ABase!=NULL){
		ABase->GetAlgorithmRootName(AlgoRoot,AlgoName);

		ShowThresholdHistgramForm	*HForm=new ShowThresholdHistgramForm(GetLayersBase());
		HForm->Initial(GetPhaseCode(),GlobalPage,GetLayer() ,GetID(),HistID
					   ,AlgoRoot ,AlgoName );
		HForm->show();
	}

	return false;
}