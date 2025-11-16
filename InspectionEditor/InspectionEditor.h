/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionEditor\InspectionEditor.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef INSPECTIONEDITOR_H
#define INSPECTIONEDITOR_H

#include <QMainWindow>
#include <QTranslator>
#include "ui_InspectionEditor.h"

class InspectionEditor : public QMainWindow
{
    Q_OBJECT

public:
    InspectionEditor(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
    ~InspectionEditor();

private:
    Ui::InspectionEditorClass ui;
};

#endif // INSPECTIONEDITOR_H
