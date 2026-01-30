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

#ifndef CLSPARAM_H
#define CLSPARAM_H

#include <QWidget>
#include <QDialog>
#include "ui_clsParam.h"

#include "clsLog.h"
#include "clsDb.h"

/**
 * @brief �p�����[�^�ݒ�
 */
class clsParam : public QDialog
{
    Q_OBJECT

public:
    clsParam(QWidget *parent = 0);
    ~clsParam();

private slots:
	void closeWin();
	void selFolder();
	void selDbFile();
	void createDbFile();
	void saveParam();

	void addTag();
	void delTag();
	void chgTag(int,int);
	void addAttr();
	void delAttr();

	void selDbFolder();

private:
    Ui::clsParamClass ui;

    clsParamDef *prm;

    void putParam();
    void getParam();

    int nTagCnt;
    int nCurTagRow;
    int nAttrCnt;
    int nCurAttrRow;

    void setInitTag();
    void setTagAttr(int row);
};

#endif // CLSPARAM_H