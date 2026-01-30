/*
 * Copyright (C) 2023
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

#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "InputRotate.h"
#include "ui_InputRotate.h"
#include "XDataInLayer.h"
#include "XRememberer.h"


InputRotate::InputRotate(LayersBase *Base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputRotate)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    Base->InstallOperationLog(this);

    Angle=0;
}

InputRotate::~InputRotate()
{
    delete ui;
}

void InputRotate::on_pushButtonCancel_clicked()
{
    done(false);
}

void InputRotate::on_pushButtonSetDegree_clicked()
{
    Angle=ui->spinBoxAngle->value();
    done(true);
}

void InputRotate::on_pushButton90Degree_clicked()
{
    Angle=90;
    done(true);
}

void InputRotate::on_pushButton180Degree_clicked()
{
    Angle=180;
    done(true);
}

void InputRotate::on_pushButton270Degree_clicked()
{
    Angle=270;
    done(true);
}