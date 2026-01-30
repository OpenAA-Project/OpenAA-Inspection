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

#ifndef EDITCOMPOSITEDEFDIALOG_H
#define EDITCOMPOSITEDEFDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QScrollArea>
#include "XServiceForLayers.h"
#include <QLabel>
#include <QFrame>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QRadioButton>
#include "XGerberAperture.h"
#include "XGerberFast.h"

namespace Ui {
class EditCompositeDefDialog;
}
class	GeneralLibFolderForm;
class	GerberFastBase;
class	LayerItemFrame;
class	GerberFastBase;
class	GerberFastLibrary;


class	GerberCompositeDefLayerPointerList : public NPList<GerberCompositeDefLayerPointerList>
{
public:
	GerberCompositeDefLayer	*Point;

	GerberCompositeDefLayerPointerList(GerberCompositeDefLayer *g):Point(g){}
};

class EditCompositeDefDialog : public QDialog , public ServiceForLayers
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	int		LibType;
	NPListPack<GerberCompositeDefLayerPointerList>	GerberCompositeDefLayerPointerContainer;
	GerberCompositeDefPack	CompositeDef;

public:
    explicit EditCompositeDefDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditCompositeDefDialog();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_listComposite_clicked(const QModelIndex &index);
    void on_ButtonPlus_clicked();
    void on_ButtonMinus_clicked();

    void on_pushButtonSelectLib_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::EditCompositeDefDialog *ui;
	GerberFastBase	*GetGerberFastBase(void);
	GerberCompositeDefLayer *DefLine;

	QScrollArea	FrameArea;
	QWidget		FrameAreaInside;
	LayerItemFrame	*FrameDim[100];
	//GerberFastLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;

	void	ShowCompositeList(void);
	void	ShowCompositeLayer(int Row);
	void	ShowDataToWindow(GerberCompositeDefLayer *Attr);

private slots:
	void	SlotRemoveLine(int);
	void	SlotUpper(int);
	void	SlotLower(int);
    void on_pushButtonSaveFile_clicked();
    void on_pushButtonLoadFile_clicked();
    void on_pushButtonAppendFile_clicked();
};


class	ItemFrame : public QObject
{
	Q_OBJECT
public:
	QFrame		FrameItem;
	QLabel		LabelNo;
	QLabel		LabelLayerType;
	QLabel		LabelDot;
	QLineEdit	LayerTypeLibID;
	QLineEdit	LayerTypeLibName;
	QPushButton	ButtonLayerType;
	QCheckBox	checkBoxNegMode;
	QSpinBox	SBoxDotSpr;
	QToolButton	ButtonRemoveLine;
	QToolButton	ButtonUpper;
	QToolButton	ButtonLower;
	GerberCompositeDefLayerItem	*Point;
	GerberFastBase	*Base;

	ItemFrame(int turn ,GerberFastBase *gBase ,QWidget *parent);
	void	SetPosition(int Y ,int turn);
	void	SetVisible(bool flag);
	void	SetLibID(int LibID);
private:
	void	PointNullMessage(void);
private slots:
	void	on_spinBox_valueChanged(int);
	void	SlotButtonLayerType_Clicked();
	void	SlotCheckBoxNegMode_Clicked();
	void	SlotButtonRemoveLine_Clicked();
	void	SlotButtonUpper_Clicked();
	void	SlotButtonLower_Clicked();
signals:
	void	SignalRemoveLine();
	void	SignalUpper();
	void	SignalLower();
};

class	ConnectionFrame : public QObject
{
	Q_OBJECT
public:
	QGroupBox		GBox;
	QRadioButton	ButtonOr;
	QRadioButton	ButtonAnd;
	QRadioButton	ButtonNotAnd;
	QRadioButton	ButtonNotOr;
	GerberCompositeDefLayerItem	*Point;

	ConnectionFrame(QWidget *parent);
	void	SetPosition(int Y);
	void	SetVisible(bool flag);
private:
	void	PointNullMessage(void);
private slots:
	void on_radioButtonOr_toggled(bool);
	void on_radioButtonAnd_toggled(bool);
	void on_radioButtonNotAnd_toggled(bool);
	void on_radioButtonNotOr_toggled(bool);
};

class	LayerItemFrame : public QObject
{
	Q_OBJECT
public:
	ItemFrame		ItemWindows;
	ConnectionFrame	ConnWindows;
	int				Turn;
	GerberFastBase		*Base;

	LayerItemFrame(int turn ,GerberFastBase *gBase ,QWidget *parent);
	int		SetPosition(int Y);

	void	Show(GerberCompositeDefLayerItem *G);
	void	SetVisible(bool flag);
signals:
	void	SignalRemoveLine(int);
	void	SignalUpper(int);
	void	SignalLower(int);
private slots:
	void	SlotRemoveLine();
	void	SlotUpper();
	void	SlotLower();
};



#endif // EDITCOMPOSITEDEFDIALOG_H