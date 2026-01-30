/*
 * Copyright (C) 2025
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



#ifndef REPAIRSTATION_H
#define REPAIRSTATION_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QToolBar>
#include <QThread>
#include <QSplitter>
#include <QListWidget>
#include "RepairBase.h"

#include "MainWidget.h"
#include "DockMasterWhole.h"
#include "DockMasterWhole1.h"
#include "DockMasterWhole2.h"
#include "DockMasterPiece.h"
#include "DockNGPiece.h"
#include "DockHistoryList.h"
#include "DockNGList.h"
#include "ProcessingForm.h"
class ImageDataUnit;
class MasterImage;
class MasterImg;
class NGImagePiece;
class LotSelectForm;
class GeneralSettingForm;
class WorkerSelectForm;
//class RepairBase;
//class ClientMain;

//class RepairStation : public QWidget
//class RepairStation : public QMainWindow, public RepairBase, public WindowBase
//class OutlineOffsetWriter;
class RepairStation : public QMainWindow, public RepairBase
{
	Q_OBJECT

public:
	RepairStation(QString XmlConnect_DotFileName, QString RepairSetting_DotFileName, QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~RepairStation();

	//OutlineOffsetInBlob	*OutlineOffsetWriter;

	QCheckBox		   *chEditEnable;
	QCheckBox		   *chNotShowHalt;
	int					NGCountInBoard;

	QList<QPair<QString, QString> > citemList;//�A���S���Y���ʃG���[�̊ە\���̐F�ݒ�

	virtual bool	Save(QIODevice *file);
	virtual bool	Load(QIODevice *file);

	void UpdateExec	();
	void SetParam	(bool ShowSequence);

	virtual void SetCheckEditEnable			(bool Check)	{	chEditEnable->setChecked(Check);	};
	virtual void SetWaitTime				(int Time);
	virtual void LoadLocation				();
	virtual void SaveLocation				();
	virtual void WindowDefault				();
	virtual void MainFrameDefault			();
	virtual void dwMasterImageDefault		();
	virtual void dwMasterImage1Default		();
	virtual void dwMasterImage2Default		();
	virtual void dwNGMasterPixDefault		();
	virtual void dwNGInspectionPixDefault	();
	virtual void dwHistoryListDefault		();
	virtual void dwNGListDefault			();

protected:
	virtual	void closeEvent(QCloseEvent *event)		override;
	virtual	void keyPressEvent(QKeyEvent *event)	override;

signals:
	void SignalFMMouseLDown		(int X,int Y,int W,int H);
	void SignalBMMouseLDown		(int X,int Y,int W,int H);

private slots:
	void pbSearchClicked			();
	void pbMasterSelectClicked		(int BackMasterCode=-1,bool IsBackLot=false);
	void chNGPointToggled			(bool Tog);
	void chShowPieceLineToggled		(bool Tog);
	void pbUpdateClicked			();
	void pbChangeLotClicked			();
	void pbGeneralSettingClicked	();
	void pbSimulateSequenceClicked	();
	void pbCloseClicked				();
	void pbShutdownClicked			();
	void chEditEnableToggled		(bool toggled);
	void chNotShowHaltToggled		(bool toggled);
	void chReverseOrderDisplayToggled(bool toggled);
	void MasterTreeRowChanged		(QTreeWidgetItem *CIndex);		//�}�X�^�[�c���[��RowChanged�C�x���g
	void MasterListRowChanged		(const QModelIndex &CIndex);		//�}�X�^�[���X�g��RowChanged�C�x���g
	void HistoryListRowChanged		(const QModelIndex &CIndex);		//�������X�g��RowChanged�C�x���g
	void NGListRowChanged			(const QModelIndex &CIndex,const QModelIndex &PIndex);		//NG���X�g��RowChanged�C�x���g
	void Next						();
	void Previous					();
	void SlotKeyLeft				();
	void SlotKeyRight				();
	void SlotKeyEnter				();
	void SlotKeyInsert				();
	void SlotKeyInsertAll			();
	void FMasterSlotOnPaint			(QPainter &Pnt);
	void BMasterSlotOnPaint			(QPainter &Pnt);
	void SlotOnMouseLDown			(int X,int Y,MasterImage *MImageClass);
	void SlotOnMPiecePaint			(QPainter &Pnt);
	void SlotOnNGPiecePaint			(QPainter &Pnt);
	void SlotOnMouseLDrag			(int X,int Y,int W,int H,MasterImage *MImageClass);
	void SlotOnMouseRClick			(MasterImage *MImageClass);
	void SlotOnMouseLClick			(int x, int y, MasterImage* MImageClass);
	void SlotNGRepaint				(bool NGEnabled);
//	void SlotOKRepaint				(int r,int g,int b);
	void SlotOKRepaint				(QColor RGB);
	void SlotIsChanged				();
	void SlotClient_Update			(QString strXML);
	void PieceListEditorTextChanged	(const QString &Text);

	void SlotError					(int Index);
	void SlotProcessCheck			(QString ProcessName);

private:
	//Widget
	MainWidget			*MainFrame;
	QSplitter			*MasterImageSplitter;
	DockMasterWhole		*dwMasterImage;
	DockMasterWhole1	*dwMasterImage1;
	DockMasterWhole2	*dwMasterImage2;
	DockMasterPiece		*dwNGMasterPix;
	DockNGPiece			*dwNGInspectionPix;
	DockHistoryList		*dwHistoryList;
	DockNGList			*dwNGList;
	QPushButton			*pbGeneralSetting;
	QPushButton			*pbSimulateSequence;
	QPushButton			*pbClose;
	QDockWidget			*dwWorker;
	QLineEdit			*leWorker;
	QDockWidget			*dwBoardName;
	QListWidget			*lwBoardName;
	QDockWidget			*dwLotName;
	QListWidget			*lwLotName;
	QToolBar			*MainToolBar;
	ProcessingForm		*MainProcessing;
	QPushButton			*pbShutdown;

	//Select,Insert,Update
	enum	SQLType{
				 Select	=0
				,Insert	=1
				,Update	=2
	};
	SQLType	QueryType;

	QPalette palette;
	QPalette MainPalette;

	MasterImg *FrontMImage,*BackMImage;

	QString	ErrMsg;
	QString	FileName;
	QStringList MTFieldNames,MFieldNames,HFieldNames,NGFieldNames;
	bool	UpdateFlg;
	bool	NoNGFlg;

	int		DotPerLine,MaxLines,PageNumb,LayerNumb;
	int		DotPerLineInPage,MaxLinesInPage,LayerNumbInPage;
///	QString MachineID;
	double	Exp;
	int		Side;
	int		FKey;
	int		MX,MY,HX,HY;
	int		InitW,InitH;

	QString	MCode;
	QString	MName;

	int		ImageX,ImageY,ImageW,ImageH;
	bool	SaveImageFlag;
	bool	NGListFlag;

	QStringList	NGAreaNameList[2];
	QString		*HistoryNGColList;

///////////////////PluginDLL///////////////////
	int		SlotIsChangedCounter;
	char	SlotIsChangedIndex;
	bool	FlagPreNextDoubleOK;
	bool	FlagPreNextDoubleNG;
	//OK�f�[�^�������݃t���O
	bool	OKWaitFlag;
///////////////////PluginDLL///////////////////

	void Init					(QString XmlConnect_DotFileName);
	void SetParameter			();
	void MakeFrontMaster		();
	void MakeBackMaster			();
	int  GetRelationCode		();
	bool ShowMasterImage		(int BackMasterCode=-1);
	bool maybeClose				();
	int  ShowMasterTree			(bool UpdatesEnabled=true);
	void AddChildTree			(QTreeWidgetItem *ParentItem,QVariant *value);
	void SetRetXMLData			(SQLType Type,QString *UpXML,QString *strUpTag=0,QString *strDelTag=0);
	void SetWindowColor			(QColor color);
	void SetWindowColorDefault	();
	void ExecFunction			(int KeyName);
	void SetRowHeaderLabel		(bool Tog);
	void ShowNGArea				(bool Tog,int Cnt);

	void NGPiecePaint(QPainter &Pnt);

	void ShowCheckXMLData(int Ret);

	void ShowNGAreaNameList();
};

#endif // REPAIRSTATION_H