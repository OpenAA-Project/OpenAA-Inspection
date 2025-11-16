#include "ShowResultInformationForm.h"
#include "ListHistoryButtonPacket.h"
#include "XLotInformation.h"
#include "XResult.h"

ShowResultInformationForm::ShowResultInformationForm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ui.setupUi(this);
//	LangSolver.SetUI(this);

	ShowInspectCount	=true;
	ShowOKCount			=true;
	ShowNGCount			=true;
	ShowReInspectCount	=true;

	TitleInspectCount	=ui.labelHeadInspectCount	->text();
	TitleOKCount		=ui.labelHeadOKCount		->text();
	TitleNGCount		=ui.labelHeadNGCount		->text();
	TitleReInspectCount	=ui.labelHeadReInspectCount	->text();

	ShowHeadInspectCount	=true;
	ShowHeadOKCount			=true;
	ShowHeadNGCount			=true;
	ShowHeadReInspectCount	=true;

	AlignAttr				="AlignLeft";
	TransparentBackColor	=true;
	BorderWidth				=1;
	BorderStyle				="Solid";

	HeadAlignAttr			="AlignLeft";
	HeadTransparentBackColor=true;
	HeadBorderWidth			=1;
	HeadBorderStyle			="Solid";

	HeadWidth	=ui.labelHeadInspectCount->width();
}

ShowResultInformationForm::~ShowResultInformationForm()
{
}

void	ShowResultInformationForm::Prepare(void)
{
	if(ShowInspectCount==true){
		ui.labelInspectCount->setVisible(true);
		ui.labelInspectCount->resize(width()-ui.labelHeadInspectCount->width()-1,ui.labelInspectCount->height());
	}
	else{
		ui.labelInspectCount->setVisible(false);
	}
	if(ShowOKCount==true){
		ui.labelOKCount->setVisible(true);
		ui.labelOKCount->resize(width()-ui.labelHeadOKCount->width()-1,ui.labelOKCount->height());
	}
	else{
		ui.labelOKCount	->setVisible(false);
	}
	if(ShowNGCount==true){
		ui.labelNGCount->setVisible(true);
		ui.labelNGCount->resize(width()-ui.labelHeadNGCount->width()-1,ui.labelNGCount->height());
	}
	else{
		ui.labelNGCount->setVisible(false);
	}
	if(ShowReInspectCount==true){
		ui.labelReInspectCount->setVisible(true);
		ui.labelReInspectCount->resize(width()-ui.labelHeadReInspectCount->width()-1,ui.labelReInspectCount->height());
	}
	else{
		ui.labelReInspectCount->setVisible(false);
	}
	ui.labelHeadInspectCount	->setText(TitleInspectCount);
	ui.labelHeadOKCount			->setText(TitleOKCount);
	ui.labelHeadNGCount			->setText(TitleNGCount);
	ui.labelHeadReInspectCount	->setText(TitleReInspectCount);

	if(ShowInspectCount==true){
		ui.labelHeadInspectCount->setVisible(true);
	}
	else{
		ui.labelHeadInspectCount->setVisible(false);
	}
	if(ShowOKCount==true){
		ui.labelHeadOKCount->setVisible(true);
	}
	else{
		ui.labelHeadOKCount->setVisible(false);
	}
	if(ShowNGCount==true){
		ui.labelHeadNGCount->setVisible(true);
	}
	else{
		ui.labelHeadNGCount->setVisible(false);
	}
	if(ShowReInspectCount==true){
		ui.labelHeadReInspectCount->setVisible(true);
	}
	else{
		ui.labelHeadReInspectCount->setVisible(false);
	}

	//HeadWidth
	ui.labelHeadInspectCount	->setMaximumWidth(HeadWidth);
	ui.labelHeadInspectCount	->setMinimumWidth(HeadWidth);
	ui.labelHeadOKCount			->setMaximumWidth(HeadWidth);
	ui.labelHeadOKCount			->setMinimumWidth(HeadWidth);
	ui.labelHeadNGCount			->setMaximumWidth(HeadWidth);
	ui.labelHeadNGCount			->setMinimumWidth(HeadWidth);
	ui.labelHeadReInspectCount	->setMaximumWidth(HeadWidth);
	ui.labelHeadReInspectCount	->setMinimumWidth(HeadWidth);

	//[Style Sheet]
	//Alignment
	if(AlignAttr=="AlignLeft"){
		ui.labelInspectCount	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelOKCount			->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelNGCount			->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelReInspectCount	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(AlignAttr=="AlignRight"){
		ui.labelInspectCount	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelOKCount			->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelNGCount			->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelReInspectCount	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelInspectCount	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelOKCount			->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelNGCount			->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelReInspectCount	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	}
	//Background
	QString strBackgroundStyleSheet;
	if(TransparentBackColor==true){
		strBackgroundStyleSheet="background: none;";
	}
	else{
		strBackgroundStyleSheet	= "background-color: "
								+ BackColor.name() + ";";
	}
	//Font
	QString strFont="";
	if(CFont.bold()==true){
		strFont	+="font-weight: bold;";
	}
	if(CFont.style()==QFont::StyleItalic){
		strFont	+="font-style: italic;";
	}
	else if(CFont.style()==QFont::StyleOblique){
		strFont	+="font-style: oblique;";
	}
	QString strFontStyleSheet	= "font-family: "
								+ CFont.family() + ";"
								+ "font-size: "
								+ QString::number(CFont.pointSize()) + "pt;"
								+ strFont;
	//StyleSheet
	QString strStyleSheet	= "color: "
							+ CharColor.name() + ";"
							+ "border-width: "
							+ QString::number(BorderWidth) + "px;"
							+ "border-color: "
							+ BorderColor.name() + ";"
							+ "border-style: "
							+ BorderStyle + ";"
							+ strBackgroundStyleSheet
							+ strFontStyleSheet;
	ui.labelInspectCount	->setStyleSheet(strStyleSheet);
	ui.labelOKCount			->setStyleSheet(strStyleSheet);
	ui.labelNGCount			->setStyleSheet(strStyleSheet);
	ui.labelReInspectCount	->setStyleSheet(strStyleSheet);

	//Alignment
	if(HeadAlignAttr=="AlignLeft"){
		ui.labelHeadInspectCount	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadOKCount			->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadNGCount			->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		ui.labelHeadReInspectCount	->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(HeadAlignAttr=="AlignRight"){
		ui.labelHeadInspectCount	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadOKCount			->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadNGCount			->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
		ui.labelHeadReInspectCount	->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		ui.labelHeadInspectCount	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadOKCount			->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadNGCount			->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		ui.labelHeadReInspectCount	->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	}
	//Background
	if(HeadTransparentBackColor==true){
		strBackgroundStyleSheet="background: none;";
	}
	else{
		strBackgroundStyleSheet	= "background-color: "
								+ HeadBackColor.name() + ";";
	}
	//Font
	strFont="";
	if(HeadCFont.bold()==true){
		strFont	+="font-weight: bold;";
	}
	if(HeadCFont.style()==QFont::StyleItalic){
		strFont	+="font-style: italic;";
	}
	else if(HeadCFont.style()==QFont::StyleOblique){
		strFont	+="font-style: oblique;";
	}
	strFontStyleSheet	= "font-family: "
						+ HeadCFont.family() + ";"
						+ "font-size: "
						+ QString::number(HeadCFont.pointSize()) + "pt;"
						+ strFont;
	//StyleSheet
	strStyleSheet	= "color: "
					+ HeadCharColor.name() + ";"
					+ "border-width: "
					+ QString::number(HeadBorderWidth) + "px;"
					+ "border-color: "
					+ HeadBorderColor.name() + ";"
					+ "border-style: "
					+ HeadBorderStyle + ";"
					+ strBackgroundStyleSheet
					+ strFontStyleSheet;
	ui.labelHeadInspectCount	->setStyleSheet(strStyleSheet);
	ui.labelHeadOKCount			->setStyleSheet(strStyleSheet);
	ui.labelHeadNGCount			->setStyleSheet(strStyleSheet);
	ui.labelHeadReInspectCount	->setStyleSheet(strStyleSheet);
}

void	ShowResultInformationForm::ResizeAction()
{
	Prepare();
}

void	ShowResultInformationForm::ShowInPlayer(int64 shownInspectionID)
{
	if(ShowInspectCount==true){
		ui.labelInspectCount	->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetAllCount()));
	}
	if(ShowOKCount==true){
		ui.labelOKCount			->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(1)));
	}
	if(ShowNGCount==true){
		ui.labelNGCount			->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(2)));
	}
	if(ShowReInspectCount==true){
		ui.labelReInspectCount	->setText(GetLayersBase()->GetLot(0)->GetLotName());
	}
/*
	ui.labelOK ->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(1)));
	ui.labelNG ->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(2)));
	ui.labelSUM->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetAllCount()));
*/
}

void	ShowResultInformationForm::BuildForShow(void)
{
/*
	if(ShowInspectCount==true){
		ui.labelInspectCount	->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetAllCount()));
	}
	if(ShowOKCount==true){
		ui.labelOKCount			->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(1)));
	}
	if(ShowNGCount==true){
		ui.labelNGCount			->setText(QString::number(GetLayersBase()->GetResultHistryData()->GetCount(2)));
	}
	if(ShowReInspectCount==true){
		ui.labelReInspectCount	->setText(GetLayersBase()->GetLotName());
	}
*/
}

void	ShowResultInformationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdListHistoryButtonUpdate	*CmdListHistoryButtonUpdateVar=dynamic_cast<CmdListHistoryButtonUpdate *>(packet);
	if(CmdListHistoryButtonUpdateVar!=NULL){
		//ï\é¶çXêV
		ShowInPlayer(-1);
	}
}
