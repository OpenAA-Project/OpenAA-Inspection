/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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