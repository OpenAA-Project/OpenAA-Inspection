/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionEditor\InspectionEditor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "InspectionEditorResource.h"
#include "InspectionEditor.h"

InspectionEditor::InspectionEditor(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	QTranslator Translator;
	Translator.load(/**/"/Regulus64v2/InspectionEditor/inspectioneditor_ja");
	qApp->installTranslator(&Translator);
	ui.setupUi(this);
}

InspectionEditor::~InspectionEditor()
{

}
