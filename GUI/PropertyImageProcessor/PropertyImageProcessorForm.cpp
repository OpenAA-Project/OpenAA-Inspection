#include "AddProgramFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\PropertyImageProcessorForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QScrollArea>
#include <QMenu>
#include "PropertyImageProcessorForm.h"
#include "AddProgramForm.h"
#include "ImageProcessorPanel.h"


ImageProcessorScrollPanel::ImageProcessorScrollPanel(QWidget *parent, Qt::WindowFlags flag)
:QWidget(parent,flag)
{
	setMouseTracking(true);
}
void ImageProcessorScrollPanel::mousePressEvent ( QMouseEvent * event )
{
	if(event->button()==Qt::LeftButton){
		emit	SignalMouseLClickPanel(event->x() ,event->y());
	}
	else if(event->button()==Qt::RightButton){
		emit	SignalMouseRClickPanel(event->x() ,event->y());
	}
}
void ImageProcessorScrollPanel::mouseMoveEvent ( QMouseEvent * event )
{
	emit	SignalMouseMovePanel(event->x() ,event->y());
}


void ImageProcessorScrollPanel::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	ImageProcessorPaint	Cmd(Form->GetLayersBase());
	Cmd.Pnt=&Pnt;
	ImageProcessBase	*Ab=Form->GetAlgorithmBase();
	if(Ab!=NULL)
		Ab->TransmitDirectly(&Cmd);
}



PropertyImageProcessorForm::PropertyImageProcessorForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	QScrollArea	*a=new QScrollArea(ui.frameScrollPanel);
	a->move(0,0);
	a->resize(ui.frameScrollPanel->width(),ui.frameScrollPanel->height());
	ScrollPanel=new ImageProcessorScrollPanel(0,Qt::Widget);
	ScrollPanel->Form=this;

	connect(ScrollPanel,SIGNAL(SignalMouseLClickPanel(int,int)),this,SLOT(SlotMouseLClickPanel(int,int)));
	connect(ScrollPanel,SIGNAL(SignalMouseRClickPanel(int,int)),this,SLOT(SlotMouseRClickPanel(int,int)));
	connect(ScrollPanel,SIGNAL(SignalMouseMovePanel	 (int,int)),this,SLOT(SlotMouseMovePanel  (int,int)));
	a->setWidget(ScrollPanel);
	ScrollPanel->resize(ui.frameScrollPanel->width(),ui.frameScrollPanel->height());
	ItemMode=_Nothing;
	TempFilter=NULL;
}

PropertyImageProcessorForm::~PropertyImageProcessorForm()
{

}

void	PropertyImageProcessorForm::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	PropertyImageProcessorForm::BuildForShow(void)
{
	ShowProgramList();
	ScrollPanel->repaint();
	CreatePanelArea();
}

void PropertyImageProcessorForm::on_ButtonAddProgram_clicked()
{
	AddProgramForm	Q(GetLayersBase(),this);
	if(Q.exec()==(int)true){
		ImageProcessBase	*Ab=GetAlgorithmBase();
		ImageProcessorAddProgram	Cmd(GetLayersBase());
		Cmd.ProgName=Q.ProgName;
		if(Ab!=NULL){
			Ab->TransmitDirectly(&Cmd);
			ShowProgramList();
		}
	}
}

void PropertyImageProcessorForm::ShowProgramList(void)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	ImageProcessorEnumProgram	Cmd(GetLayersBase());
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
	}
	ui.listWidgetProgram->clear();
	for(int i=0;i<Cmd.ProgNameList.count();i++){
		QString	v=Cmd.ProgNameList.value(i);
		ui.listWidgetProgram->addItem(v);
	}
}

void PropertyImageProcessorForm::on_ButtonDelProgram_clicked()
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	ImageProcessorDelProgram	Cmd(GetLayersBase());
	Cmd.Row=ui.listWidgetProgram->currentRow();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		ShowProgramList();
	}
}

void PropertyImageProcessorForm::on_ButtonAddFile_clicked()
{

	QStringList FileNames=GetLayersBase()->LGetOpenFileNames (0
											, LangSolver.GetString(PropertyImageProcessorForm_LS,LID_0)/*"Image files"*/
											, QString()
											, /**/"Images (*.png *.xpm *.jpg *.bmp)");
	if(FileNames.isEmpty()==false){
		ImageProcessBase	*Ab=GetAlgorithmBase();
		ImageProcessorAddFiles	Cmd(GetLayersBase());
		Cmd.ProgRow=ui.listWidgetProgram->currentRow();
		Cmd.FileNames=FileNames;
		if(Ab!=NULL){
			Ab->TransmitDirectly(&Cmd);
			ShowFileNames();
		}
	}
}

void PropertyImageProcessorForm::on_ButtonDelFile_clicked()
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	ImageProcessorDelFile	Cmd(GetLayersBase());
	Cmd.ProgRow=ui.listWidgetProgram->currentRow();
	Cmd.FileRow=ui.listWidgetFileName->currentRow();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		ShowFileNames();
	}
}

void PropertyImageProcessorForm::on_FilterMonoButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_1)/*"モノクロ"*/;
}

void PropertyImageProcessorForm::on_ButtonOpposite_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_2)/*"明暗反転"*/;
}

void PropertyImageProcessorForm::on_FilterAddButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_3)/*"加算"*/;
}

void PropertyImageProcessorForm::on_FilterSubButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_4)/*"減算"*/;
}

void PropertyImageProcessorForm::on_FilterMulButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_5)/*"実数倍"*/;
}

void PropertyImageProcessorForm::on_FilterCoefButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_6)/*"相関"*/;
}

void PropertyImageProcessorForm::on_ButtonFilterLineEmphasis_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_7)/*"線強調"*/;
}

void PropertyImageProcessorForm::on_ButtonLaplace_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_8)/*"ﾗﾌﾟﾗｼｱﾝ"*/;
}

void PropertyImageProcessorForm::on_ButtonGradiant_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_9)/*"勾配"*/;
}

void PropertyImageProcessorForm::on_ButtonTransLog_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_10)/*"対数変換"*/;
}

void PropertyImageProcessorForm::on_ButtonDiverse_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_11)/*"差分"*/;
}

void PropertyImageProcessorForm::on_FilterBinarizeButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_12)/*"２値化"*/;
}

void PropertyImageProcessorForm::on_FilterEnfatButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_13)/*"膨張"*/;
}

void PropertyImageProcessorForm::on_FilterShrinkButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_14)/*"収縮"*/;
}

void PropertyImageProcessorForm::on_FilterRelativeBinarizeButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_15)/*"相対２値"*/;
}

void PropertyImageProcessorForm::on_FilterAndButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_16)/*"AND"*/;
}

void PropertyImageProcessorForm::on_FilterOrButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_17)/*"OR"*/;
}

void PropertyImageProcessorForm::on_FilterXorButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_18)/*"XOR"*/;
}

void PropertyImageProcessorForm::on_FilterNotButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_19)/*"NOT"*/;
}

void PropertyImageProcessorForm::on_FilterThresholdButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_20)/*"しきい値"*/;
}

void PropertyImageProcessorForm::on_FilterAllocButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_21)/*"結果割当"*/;
}

void	PropertyImageProcessorForm::SlotMouseLClickPanel(int x ,int y)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		if(ItemMode==_Nothing){
			ImageProcessorSelectItem	PCmd(GetLayersBase());
			PCmd.x=x;
			PCmd.y=y;
			Ab->TransmitDirectly(&PCmd);
			if(PCmd.Item==NULL){
				ImageProcessorAddInstance	Cmd(GetLayersBase());
				Cmd.ParamTitle=CurrentTitle;
				Cmd.x=x;
				Cmd.y=y;
				Ab->TransmitDirectly(&Cmd);
				CreatePanelArea();
			}
			else{
				TempFilter=PCmd.Item;
				ClickSelectItem(PCmd.Item);
			}
		}
		else if(ItemMode==_OnSelectSourceItem && TempFilter!=NULL){
			ImageProcessorAddTargetFromSource	Cmd(GetLayersBase());
			Cmd.CurrentItem=TempFilter;
			Cmd.x=x;
			Cmd.y=y;
			Ab->TransmitDirectly(&Cmd);
			if(Cmd.CurrentItem==NULL){
				ItemMode=_Nothing;
				TempFilter=NULL;
			}
		}
		else if(ItemMode==_OnMove && TempFilter!=NULL){
			ItemMode=_Nothing;
			TempFilter=NULL;
			CreatePanelArea();
		}
	}
	ScrollPanel->repaint();
}

void	PropertyImageProcessorForm::SlotMouseRClickPanel(int x ,int y)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		ImageProcessorSelectItem	Cmd(GetLayersBase());
		Cmd.x=x;
		Cmd.y=y;
		ItemMode=_Nothing;
		Ab->TransmitDirectly(&Cmd);
		if(Cmd.Item!=NULL){
			TempFilter=Cmd.Item;
			QMenu	PopupMenu(LangSolver.GetString(PropertyImageProcessorForm_LS,LID_22)/*"Operation"*/);
			QPoint	P(x,y);
			QPoint	Rp=ScrollPanel->mapToGlobal(P);
			PopupMenu.move(Rp.x(),Rp.y());
			PopupMenu.addAction(LangSolver.GetString(PropertyImageProcessorForm_LS,LID_23)/*"Move"*/					,this,SLOT(SlotMoveItem()));
			PopupMenu.addAction(LangSolver.GetString(PropertyImageProcessorForm_LS,LID_24)/*"Delete"*/				,this,SLOT(SlotDeleteItem()));
			PopupMenu.addAction(LangSolver.GetString(PropertyImageProcessorForm_LS,LID_25)/*"Select source"*/			,this,SLOT(SlotSelectSource()));
			PopupMenu.addAction(LangSolver.GetString(PropertyImageProcessorForm_LS,LID_26)/*"Delete target chain"*/	,this,SLOT(SlotDeleteTargetChain()));
			PopupMenu.exec();
		}
	}
}

void	PropertyImageProcessorForm::ClickSelectItem(FilterBase *Item)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab==NULL)
		return;

	ImageProcessorGetParam	Cmd(GetLayersBase());
	Cmd.ItemID=Item->GetID();
	Ab->TransmitDirectly(&Cmd);

	ui.tableWidgetItem->setRowCount(Cmd.ParamCount);
	for(int row=0;row<Cmd.ParamCount && row<Cmd.ParamName.count();row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetItem->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetItem->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
		W->setText(Cmd.ParamName.value(row));

		W=ui.tableWidgetItem->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetItem->setItem ( row, 1,W);
			//W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
		W->setText(QString::number(Cmd.Param[row]));
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ImageProcessorPanel" ,/**/"");
	if(GProp!=NULL){
		ImageProcessorPanel	*Panel=dynamic_cast<ImageProcessorPanel *>(GProp);
		if(Panel!=NULL){
			Panel->CurrentItem=Item;
			Panel->Repaint();
		}
	}
}

void	PropertyImageProcessorForm::CreatePanelArea(void)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab==NULL)
		return;
	ImageProcessorGetMinMaxArea	Cmd(GetLayersBase());
	Ab->TransmitDirectly(&Cmd);

	int	RX=Cmd.MaxX+ui.frameScrollPanel->width()/4;
	int	RY=Cmd.MaxY+ui.frameScrollPanel->height()/4;
	if(RX<ui.frameScrollPanel->width())
		RX=ui.frameScrollPanel->width();
	if(RY<ui.frameScrollPanel->height())
		RY=ui.frameScrollPanel->height();
	ScrollPanel->resize(RX,RY);
}


ImageProcessBase	*PropertyImageProcessorForm::GetAlgorithmBase(void)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageProcess");
	if(Ab!=NULL){
		ImageProcessBase	*L=dynamic_cast<ImageProcessBase *>(Ab);
		return L;
	}
	return NULL;
}

void PropertyImageProcessorForm::on_listWidgetProgram_clicked(const QModelIndex &)
{
	ShowFileNames();
}
void PropertyImageProcessorForm::ShowFileNames(void)
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	ImageProcessorEnumImages	Cmd(GetLayersBase());
	Cmd.Row=ui.listWidgetProgram->currentRow();
	ui.listWidgetFileName->clear();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		for(int i=0;i<Cmd.FileNameList.count();i++){
			QString	v=Cmd.FileNameList.value(i);
			ui.listWidgetFileName->addItem(v);
		}
	}
}

void	PropertyImageProcessorForm::SlotMoveItem()
{
	ItemMode=_OnMove;
}
void	PropertyImageProcessorForm::SlotDeleteItem()
{
	ImageProcessorDeleteItem	Cmd(GetLayersBase());
	Cmd.Item=TempFilter;
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		TempFilter=NULL;
		ItemMode=_Nothing;

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"ImageProcessorPanel" ,/**/"");
		if(GProp!=NULL){
			ImageProcessorPanel	*Panel=dynamic_cast<ImageProcessorPanel *>(GProp);
			if(Panel!=NULL){
				Panel->CurrentItem=NULL;
			}
		}
	}
	CreatePanelArea();
	ScrollPanel->repaint();
}

void	PropertyImageProcessorForm::SlotSelectSource()
{
	ItemMode=_OnSelectSourceItem;
}
void	PropertyImageProcessorForm::SlotDeleteTargetChain()
{
	ImageProcessorDeleteAllTargetInItem	Cmd(GetLayersBase());
	Cmd.Item=TempFilter;
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		TempFilter=NULL;
		ItemMode=_Nothing;
	}
	ScrollPanel->repaint();
}

void	PropertyImageProcessorForm::SlotMouseMovePanel(int x ,int y)
{
	if(ItemMode==_OnMove && TempFilter!=NULL){
		ImageProcessorMoveItem	Cmd(GetLayersBase());
		Cmd.Item=TempFilter;
		Cmd.x=x;
		Cmd.y=y;
		ImageProcessBase	*Ab=GetAlgorithmBase();
		if(Ab!=NULL){
			Ab->TransmitDirectly(&Cmd);
		}
		ScrollPanel->repaint();
	}
}


void PropertyImageProcessorForm::on_tableWidgetItem_cellChanged(int row, int column)
{
	if(column==1 && TempFilter!=NULL){
		ImageProcessBase	*Ab=GetAlgorithmBase();
		if(Ab!=NULL){
			ImageProcessorGetParam	Cmd(GetLayersBase());
			Cmd.ItemID=TempFilter->GetID();
			Ab->TransmitDirectly(&Cmd);

			QTableWidgetItem *W=ui.tableWidgetItem->item (row, 1);
			if(W!=NULL){
				bool	ok;
				Cmd.Param[row]=W->text().toDouble(&ok);
				if(ok==true){
					ImageProcessorSetParam	SCmd(GetLayersBase());
					SCmd.ItemID=Cmd.ItemID;
					for(int i=0;i<Cmd.ParamCount;i++){
						SCmd.Param[i]=Cmd.Param[i];
					}
					Ab->TransmitDirectly(&SCmd);
				}
			}
		}
	}
}

void PropertyImageProcessorForm::on_pushButtonUpArrowFile_clicked()
{
	ImageProcessorUpperFile	Cmd(GetLayersBase());
	Cmd.ProgRow=ui.listWidgetProgram->currentRow();
	Cmd.FileRow=ui.listWidgetFileName->currentRow();
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		ShowFileNames();
	}
}

void PropertyImageProcessorForm::on_pushButtonDownArrowFile_clicked()
{
	ImageProcessorLowerFile	Cmd(GetLayersBase());
	Cmd.ProgRow=ui.listWidgetProgram->currentRow();
	Cmd.FileRow=ui.listWidgetFileName->currentRow();
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		ShowFileNames();
	}
}

void PropertyImageProcessorForm::on_ButtonStartOne_clicked()
{
	ImageProcessorExecuteOne	Cmd(GetLayersBase());
	Cmd.ProgRow=ui.listWidgetProgram->currentRow();
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
	}
}

void PropertyImageProcessorForm::on_ButtonExecuteAll_clicked()
{
	ImageProcessorExecuteAll	Cmd(GetLayersBase());
	ImageProcessBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
	}
}

void PropertyImageProcessorForm::on_LoadImageButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_27)/*"Root"*/;
}

void PropertyImageProcessorForm::on_DigitalFilterLineNotchButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_28)/*"周期線除去"*/;
}

void PropertyImageProcessorForm::on_FractalDimButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_29)/*"フラクタル次元"*/;
}

void PropertyImageProcessorForm::on_StatisticButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_30)/*"長さ統計"*/;
}

void PropertyImageProcessorForm::on_LinearizeButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_31)/*"細線化"*/;
}

void PropertyImageProcessorForm::on_ButtonRemoveNoise_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_32)/*"ノイズ除去"*/;	
}

void PropertyImageProcessorForm::on_MatchLearnButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_33)/*"学習マッチ"*/;
}

void PropertyImageProcessorForm::on_ButtonRemoveStandalone_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_34)/*"孤立点除去"*/;	
}

void PropertyImageProcessorForm::on_ButtonDisorderRegular_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_35)/*"正規分布乖離"*/;
}

void PropertyImageProcessorForm::on_ButtonErgod_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_36)/*"エルゴード性"*/;
}

void PropertyImageProcessorForm::on_ButtonRemoveSpot_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_37)/*"輝点除去"*/;	
}

void PropertyImageProcessorForm::on_ButtonConnectNearBy_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_38)/*"近傍接続"*/;
}

void PropertyImageProcessorForm::on_ButtonMakeMaxPath_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_39)/*"最長パス"*/;
}

void PropertyImageProcessorForm::on_ButtonLoadDef_clicked()
{
	QString FileName=GetLayersBase()->LGetOpenFileName (0
										, LangSolver.GetString(PropertyImageProcessorForm_LS,LID_40)/*"Load def files"*/
										, QString()
										, /**/"DefFile (*.def *.txt)");
	if(FileName.isEmpty()==false){
		ImageProcessBase	*Ab=GetAlgorithmBase();
		ImageProcessorLoadDefFile	Cmd(GetLayersBase());
		Cmd.DefFileName=FileName;
		if(Ab!=NULL){
			Ab->TransmitDirectly(&Cmd);
			ShowProgramList();
			ShowFileNames();
		}
	}
}

void PropertyImageProcessorForm::on_ButtonDelAllProgram_clicked()
{
	ImageProcessBase	*Ab=GetAlgorithmBase();
	ImageProcessorDelAllProgram	Cmd(GetLayersBase());
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Cmd);
		ShowProgramList();
		ShowFileNames();
	}
}

void PropertyImageProcessorForm::on_AverageBinarizeButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_41)/*"平均２値化"*/;
}

void PropertyImageProcessorForm::on_FilterMedianButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_42)/*"中央平均化"*/;
}

void PropertyImageProcessorForm::on_FilterMosaicButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_43)/*"モザイク化"*/;
}

void PropertyImageProcessorForm::on_FilterLineEmphasizerButton_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_44)/*"線強調"*/;
}

void PropertyImageProcessorForm::on_ButtonPickupWeb_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_45)/*"網目検出"*/;
}

void PropertyImageProcessorForm::on_ButtonConnectPartial_clicked()
{
	CurrentTitle=LangSolver.GetString(PropertyImageProcessorForm_LS,LID_46)/*"途切接続"*/;
}