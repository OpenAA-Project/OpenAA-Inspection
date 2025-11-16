/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\CodecListSelecterForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CODECLISTSELECTERFORM_H
#define CODECLISTSELECTERFORM_H

#include <QDialog>
#include "ui_CodecListSelecterForm.h"
#include "XLanguageClass.h"

class CodecListSelecterForm : public QDialog
{
	Q_OBJECT

public:
	CodecListSelecterForm(QWidget *parent);
	~CodecListSelecterForm();

private:
	Ui::CodecListSelecterFormClass ui;

	QComboBox	*ComboListPointer[MAXLANGUAGECOUNT];

private slots:
	void on_pushButtonOK_clicked();
};

#endif // CODECLISTSELECTERFORM_H
