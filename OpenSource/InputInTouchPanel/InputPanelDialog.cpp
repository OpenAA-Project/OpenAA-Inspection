#include "XTypeDef.h"
#include "InputPanelDialog.h"
#include "ui_InputPanelDialog.h"
#include <QTextCodec>

InputPanelDialog::InputPanelDialog(int type ,const QString &LastStr,QWidget *parent) :
    QDialog(parent)
	,Type(type)
    ,ui(new Ui::InputPanelDialog)
{
    ui->setupUi(this);

	if((Type&IPD_Number)!=0)
		ui->stackedWidget	->setCurrentIndex(0);
	else if((Type&IPD_Alpha)!=0)
		ui->stackedWidget	->setCurrentIndex(1);
	else if((Type&IPD_Sign)!=0)
		ui->stackedWidget	->setCurrentIndex(3);
	else if((Type&IPD_Hira)!=0)
		ui->stackedWidget	->setCurrentIndex(4);
	else if((Type&IPD_Kata)!=0)
		ui->stackedWidget	->setCurrentIndex(5);

#if	QT_VERSION<0x050000
	CodecCString	=QTextCodec::codecForCStrings();
	CodecLocale		=QTextCodec::codecForLocale();
	CodecTr			=QTextCodec::codecForTr();
#else
	CodecCString= QTextCodec::codecForLocale();
	CodecLocale = QTextCodec::codecForLocale();
	CodecTr		= QTextCodec::codecForLocale();
#endif

	if((Type&IPD_Hira)!=0 || (Type&IPD_Kata)!=0){
		QTextCodec *c=QTextCodec::codecForName ( /**/"Shift-JIS" );

#if	QT_VERSION<0x050000
		QTextCodec::setCodecForCStrings(c);
		QTextCodec::setCodecForLocale (c);
		QTextCodec::setCodecForTr (c);
#else
		QTextCodec::setCodecForLocale(c);
#endif
	}
	ShowCpntrolPanel();

	ui->lineEdit->setText(LastStr);
}

InputPanelDialog::~InputPanelDialog()
{
    delete ui;
}

void InputPanelDialog::closeEvent ( QCloseEvent * e )
{
#if	QT_VERSION<0x050000
	QTextCodec::setCodecForCStrings	(CodecCString);
	QTextCodec::setCodecForLocale	(CodecLocale);
	QTextCodec::setCodecForTr		(CodecTr);
#else
	QTextCodec::setCodecForLocale(CodecLocale);
#endif
}

void InputPanelDialog::ShowCpntrolPanel(void)
{
	switch(ui->stackedWidget->currentIndex()){
	case 0:	ui->frame	->move(460,50);	break;
	case 1:	ui->frame	->move(460,50);	break;
	case 2:	ui->frame	->move(460,50);	break;
	case 3:	ui->frame	->move(460,50);	break;
	case 4:	ui->frame	->move(820,50);	break;
	case 5:	ui->frame	->move(820,50);	break;
	}
	resize(ui->frame->geometry().left()+ui->frame->width()+4,height());
}

void InputPanelDialog::on_BNext_clicked()
{
	int	R=ui->stackedWidget->currentIndex();

	for(int t=R+1;t!=R;t++){
		if(t>=6)
			t=0;
		if(t==0 && (Type&IPD_Number)!=0){
			ui->stackedWidget	->setCurrentIndex(0);
			break;
		}
		else if((t==1 || t==2) && (Type&IPD_Alpha)!=0){
			ui->stackedWidget	->setCurrentIndex(t);
			break;
		}
		else if(t==3 && (Type&IPD_Sign)!=0){
			ui->stackedWidget	->setCurrentIndex(3);
			break;
		}
		else if(t==4 && (Type&IPD_Hira)!=0){
			ui->stackedWidget	->setCurrentIndex(4);
			break;
		}
		else if(t==5 && (Type&IPD_Kata)!=0){
			ui->stackedWidget	->setCurrentIndex(5);
			break;
		}
	}
	ShowCpntrolPanel();
}

void InputPanelDialog::on_BBS_clicked()
{
	ui->lineEdit->backspace();
}

void InputPanelDialog::on_BDel_clicked()
{
	ui->lineEdit->del();
}

void InputPanelDialog::on_BLeft_clicked()
{
	ui->lineEdit->cursorForward(false);
}

void InputPanelDialog::on_BRight_clicked()
{
	ui->lineEdit->cursorBackward(false);
}

void InputPanelDialog::on_BEnter_clicked()
{
	Result=ui->lineEdit->text();
	accept();
}

void	InputPanelDialog::Add(const QString &c)
{
	ui->lineEdit->insert(c);
}

void InputPanelDialog::on_B0_clicked()
{
	Add(/**/"0");
}

void InputPanelDialog::on_B1_clicked()
{
	Add(/**/"1");
}

void InputPanelDialog::on_B2_clicked()
{
	Add(/**/"2");
}

void InputPanelDialog::on_B3_clicked()
{
	Add(/**/"3");
}

void InputPanelDialog::on_B4_clicked()
{
	Add(/**/"4");
}

void InputPanelDialog::on_B5_clicked()
{
	Add(/**/"5");
}

void InputPanelDialog::on_B6_clicked()
{
	Add(/**/"6");
}

void InputPanelDialog::on_B7_clicked()
{
	Add(/**/"7");
}

void InputPanelDialog::on_B8_clicked()
{
	Add(/**/"8");
}

void InputPanelDialog::on_B9_clicked()
{
	Add(/**/"9");
}

void InputPanelDialog::on_BDot_clicked()
{
	Add(/**/".");
}

void InputPanelDialog::on_BMul_clicked()
{
	Add(/**/"*");
}

void InputPanelDialog::on_BPlus_clicked()
{
	Add(/**/"+");
}

void InputPanelDialog::on_BMinus_clicked()
{
	Add(/**/"-");
}

void InputPanelDialog::on_BDiv_clicked()
{
	Add(/**/"/");
}

void InputPanelDialog::on_Ba_clicked()
{
	Add(/**/"a");
}

void InputPanelDialog::on_Bb_clicked()
{
	Add(/**/"b");
}

void InputPanelDialog::on_Bc_clicked()
{
	Add(/**/"c");
}

void InputPanelDialog::on_Bd_clicked()
{
	Add(/**/"d");
}

void InputPanelDialog::on_Be_clicked()
{
	Add(/**/"e");
}

void InputPanelDialog::on_Bf_clicked()
{
	Add(/**/"f");
}

void InputPanelDialog::on_Bg_clicked()
{
	Add(/**/"g");
}

void InputPanelDialog::on_Bh_clicked()
{
	Add(/**/"h");
}

void InputPanelDialog::on_Bi_clicked()
{
	Add(/**/"i");
}

void InputPanelDialog::on_Bj_clicked()
{
	Add(/**/"j");
}

void InputPanelDialog::on_Bk_clicked()
{
	Add(/**/"k");
}

void InputPanelDialog::on_Bl_clicked()
{
	Add(/**/"l");
}

void InputPanelDialog::on_Bm_clicked()
{
	Add(/**/"m");
}

void InputPanelDialog::on_Bn_clicked()
{
	Add(/**/"n");
}

void InputPanelDialog::on_Bo_clicked()
{
	Add(/**/"o");
}

void InputPanelDialog::on_Bp_clicked()
{
	Add(/**/"p");
}

void InputPanelDialog::on_Bq_clicked()
{
	Add(/**/"q");
}

void InputPanelDialog::on_Br_clicked()
{
	Add(/**/"r");
}

void InputPanelDialog::on_Bs_clicked()
{
	Add(/**/"s");
}

void InputPanelDialog::on_Bt_clicked()
{
	Add(/**/"t");
}

void InputPanelDialog::on_Bu_clicked()
{
	Add(/**/"u");
}

void InputPanelDialog::on_Bv_clicked()
{
	Add(/**/"v");
}

void InputPanelDialog::on_Bw_clicked()
{
	Add(/**/"w");
}

void InputPanelDialog::on_Bx_clicked()
{
	Add(/**/"x");
}

void InputPanelDialog::on_By_clicked()
{
	Add(/**/"y");
}

void InputPanelDialog::on_Bz_clicked()
{
	Add(/**/"z");
}

void InputPanelDialog::on_BA_clicked()
{
	Add(/**/"A");
}

void InputPanelDialog::on_BB_clicked()
{
	Add(/**/"B");
}

void InputPanelDialog::on_BC_clicked()
{
	Add(/**/"C");
}

void InputPanelDialog::on_BD_clicked()
{
	Add(/**/"D");
}

void InputPanelDialog::on_BE_clicked()
{
	Add(/**/"E");
}

void InputPanelDialog::on_BF_clicked()
{
	Add(/**/"F");
}

void InputPanelDialog::on_BG_clicked()
{
	Add(/**/"G");
}

void InputPanelDialog::on_BH_clicked()
{
	Add(/**/"H");
}

void InputPanelDialog::on_BI_clicked()
{
	Add(/**/"I");
}

void InputPanelDialog::on_BJ_clicked()
{
	Add(/**/"J");
}

void InputPanelDialog::on_BK_clicked()
{
	Add(/**/"K");
}

void InputPanelDialog::on_BL_clicked()
{
	Add(/**/"L");
}

void InputPanelDialog::on_BM_clicked()
{
	Add(/**/"M");
}

void InputPanelDialog::on_BN_clicked()
{
	Add(/**/"N");
}

void InputPanelDialog::on_BO_clicked()
{
	Add(/**/"O");
}

void InputPanelDialog::on_BP_clicked()
{
	Add(/**/"P");
}

void InputPanelDialog::on_BQ_clicked()
{
	Add(/**/"Q");
}

void InputPanelDialog::on_BR_clicked()
{
	Add(/**/"R");
}

void InputPanelDialog::on_BS_clicked()
{
	Add(/**/"S");
}

void InputPanelDialog::on_BT_clicked()
{
	Add(/**/"T");
}

void InputPanelDialog::on_BU_clicked()
{
	Add(/**/"U");
}

void InputPanelDialog::on_BV_clicked()
{
	Add(/**/"V");
}

void InputPanelDialog::on_BW_clicked()
{
	Add(/**/"W");
}

void InputPanelDialog::on_BX_clicked()
{
	Add(/**/"X");
}

void InputPanelDialog::on_BY_clicked()
{
	Add(/**/"Y");
}

void InputPanelDialog::on_BZ_clicked()
{
	Add(/**/"Z");
}

void InputPanelDialog::on_BExclamation_clicked()
{
	Add(/**/"!");
}

void InputPanelDialog::on_BDQuotation_clicked()
{
	Add(/**/"\"");
}

void InputPanelDialog::on_BSharp_clicked()
{
	Add(/**/"#");
}

void InputPanelDialog::on_BDollar_clicked()
{
	Add(/**/"$");
}

void InputPanelDialog::on_BPercent_clicked()
{
	Add(/**/"%");
}

void InputPanelDialog::on_BAnd_clicked()
{
	Add(/**/"&");
}

void InputPanelDialog::on_BSQuotation_clicked()
{
	Add(/**/"\'");
}

void InputPanelDialog::on_BYen_clicked()
{
	Add(/**/"\\");
}

void InputPanelDialog::on_BLParenthesis_clicked()
{
	Add(/**/"(");
}

void InputPanelDialog::on_BRParenthesis_clicked()
{
	Add(/**/")");
}

void InputPanelDialog::on_BEqual_clicked()
{
	Add(/**/"=");
}

void InputPanelDialog::on_BXor_clicked()
{
	Add(/**/"^");
}

void InputPanelDialog::on_BLBracket_clicked()
{
	Add(/**/"[");
}

void InputPanelDialog::on_BRBracket_clicked()
{
	Add(/**/"]");
}

void InputPanelDialog::on_BLBrace_clicked()
{
	Add(/**/"{");
}

void InputPanelDialog::on_BRBrace_clicked()
{
	Add(/**/"}");
}

void InputPanelDialog::on_BLessThan_clicked()
{
	Add(/**/"<");
}

void InputPanelDialog::on_BGreaterThan_clicked()
{
	Add(/**/">");
}

void InputPanelDialog::on_BQuestion_clicked()
{
	Add(/**/"?");
}

void InputPanelDialog::on_BAtmark_clicked()
{
	Add(/**/"@");
}

void InputPanelDialog::on_BSemicolon_clicked()
{
	Add(/**/";");
}

void InputPanelDialog::on_BColon_clicked()
{
	Add(/**/":");
}

void InputPanelDialog::on_BUnderbar_clicked()
{
	Add(/**/"_");
}

void InputPanelDialog::on_BComma_clicked()
{
	Add(/**/",");
}

void InputPanelDialog::on_BTilde_clicked()
{
	Add(/**/"~");
}

void InputPanelDialog::on_BOr_clicked()
{
	Add(/**/"|");
}

void InputPanelDialog::on_BSpace_clicked()
{
	Add(/**/" ");
}

void InputPanelDialog::on_BHiraA_clicked()
{
	Add(/**/"あ");
}

void InputPanelDialog::on_BHiraI_clicked()
{
	Add(/**/"い");
}

void InputPanelDialog::on_BHiraU_clicked()
{
	Add(/**/"う");
}

void InputPanelDialog::on_BHiraE_clicked()
{
	Add(/**/"え");
}

void InputPanelDialog::on_BHiraO_clicked()
{
	Add(/**/"お");
}

void InputPanelDialog::on_BHiraKA_clicked()
{
	Add(/**/"か");
}

void InputPanelDialog::on_BHiraKI_clicked()
{
	Add(/**/"き");
}

void InputPanelDialog::on_BHiraKU_clicked()
{
	Add(/**/"く");
}

void InputPanelDialog::on_BHiraKE_clicked()
{
	Add(/**/"け");
}

void InputPanelDialog::on_BHiraKO_clicked()
{
	Add(/**/"こ");
}

void InputPanelDialog::on_BHiraGA_clicked()
{
	Add(/**/"が");
}

void InputPanelDialog::on_BHiraGI_clicked()
{
	Add(/**/"ぎ");
}

void InputPanelDialog::on_BHiraGU_clicked()
{
	Add(/**/"ぐ");
}

void InputPanelDialog::on_BHiraGE_clicked()
{
	Add(/**/"げ");
}

void InputPanelDialog::on_BHiraGO_clicked()
{
	Add(/**/"ご");
}

void InputPanelDialog::on_BHiraSA_clicked()
{
	Add(/**/"さ");
}

void InputPanelDialog::on_BHiraSI_clicked()
{
	Add(/**/"し");
}

void InputPanelDialog::on_BHiraSU_clicked()
{
	Add(/**/"す");
}

void InputPanelDialog::on_BHiraSE_clicked()
{
	Add(/**/"せ");
}

void InputPanelDialog::on_BHiraSO_clicked()
{
	Add(/**/"そ");
}

void InputPanelDialog::on_BHiraZA_clicked()
{
	Add(/**/"ざ");
}

void InputPanelDialog::on_BHiraZI_clicked()
{
	Add(/**/"じ");
}

void InputPanelDialog::on_BHiraZU_clicked()
{
	Add(/**/"ず");
}

void InputPanelDialog::on_BHiraZE_clicked()
{
	Add(/**/"ぜ");
}

void InputPanelDialog::on_BHiraZO_clicked()
{
	Add(/**/"ぞ");
}

void InputPanelDialog::on_BHiraTA_clicked()
{
	Add(/**/"た");
}

void InputPanelDialog::on_BHiraTI_clicked()
{
	Add(/**/"ち");
}

void InputPanelDialog::on_BHiraTU_clicked()
{
	Add(/**/"つ");
}

void InputPanelDialog::on_BHiraTE_clicked()
{
	Add(/**/"て");
}

void InputPanelDialog::on_BHiraTO_clicked()
{
	Add(/**/"と");
}

void InputPanelDialog::on_BHiraXTU_clicked()
{
	Add(/**/"っ");
}

void InputPanelDialog::on_BHiraDA_clicked()
{
	Add(/**/"だ");
}

void InputPanelDialog::on_BHiraDI_clicked()
{
	Add(/**/"ぢ");
}

void InputPanelDialog::on_BHiraDU_clicked()
{
	Add(/**/"づ");
}

void InputPanelDialog::on_BHiraDE_clicked()
{
	Add(/**/"で");
}

void InputPanelDialog::on_BHiraDO_clicked()
{
	Add(/**/"ど");
}

void InputPanelDialog::on_BHiraNA_clicked()
{
	Add(/**/"な");
}

void InputPanelDialog::on_BHiraNI_clicked()
{
	Add(/**/"に");
}

void InputPanelDialog::on_BHiraNU_clicked()
{
	Add(/**/"ぬ");
}

void InputPanelDialog::on_BHiraNE_clicked()
{
	Add(/**/"ね");
}

void InputPanelDialog::on_BHiraNO_clicked()
{
	Add(/**/"の");
}

void InputPanelDialog::on_BHiraHA_clicked()
{
	Add(/**/"は");
}

void InputPanelDialog::on_BHiraHI_clicked()
{
	Add(/**/"ひ");
}

void InputPanelDialog::on_BHiraHU_clicked()
{
	Add(/**/"ふ");
}

void InputPanelDialog::on_BHiraHE_clicked()
{
	Add(/**/"へ");
}

void InputPanelDialog::on_BHiraHO_clicked()
{
	Add(/**/"ほ");
}

void InputPanelDialog::on_BHiraBA_clicked()
{
	Add(/**/"ば");
}

void InputPanelDialog::on_BHiraBI_clicked()
{
	Add(/**/"び");
}

void InputPanelDialog::on_BHiraBU_clicked()
{
	Add(/**/"ぶ");
}

void InputPanelDialog::on_BHiraBE_clicked()
{
	Add(/**/"べ");
}

void InputPanelDialog::on_BHiraBO_clicked()
{
	Add(/**/"ぼ");
}

void InputPanelDialog::on_BHiraPA_clicked()
{
	Add(/**/"ぱ");
}

void InputPanelDialog::on_BHiraPI_clicked()
{
	Add(/**/"ぴ");
}

void InputPanelDialog::on_BHiraPU_clicked()
{
	Add(/**/"ぷ");
}

void InputPanelDialog::on_BHiraPE_clicked()
{
	Add(/**/"ぺ");
}

void InputPanelDialog::on_BHiraPO_clicked()
{
	Add(/**/"ぽ");
}

void InputPanelDialog::on_BHiraMA_clicked()
{
	Add(/**/"ま");
}

void InputPanelDialog::on_BHiraMI_clicked()
{
	Add(/**/"み");
}

void InputPanelDialog::on_BHiraMU_clicked()
{
	Add(/**/"む");
}

void InputPanelDialog::on_BHiraME_clicked()
{
	Add(/**/"め");
}

void InputPanelDialog::on_BHiraMO_clicked()
{
	Add(/**/"も");
}

void InputPanelDialog::on_BHiraYA_clicked()
{
	Add(/**/"や");
}

void InputPanelDialog::on_BHiraYU_clicked()
{
	Add(/**/"ゆ");
}

void InputPanelDialog::on_BHiraYO_clicked()
{
	Add(/**/"よ");
}

void InputPanelDialog::on_BHiraXYA_clicked()
{
	Add(/**/"ゃ");
}

void InputPanelDialog::on_BHiraXYU_clicked()
{
	Add(/**/"ゅ");
}

void InputPanelDialog::on_BHiraXYO_clicked()
{
	Add(/**/"ょ");
}

void InputPanelDialog::on_BHiraRA_clicked()
{
	Add(/**/"ら");
}

void InputPanelDialog::on_BHiraRI_clicked()
{
	Add(/**/"り");
}

void InputPanelDialog::on_BHiraRU_clicked()
{
	Add(/**/"る");
}

void InputPanelDialog::on_BHiraRE_clicked()
{
	Add(/**/"れ");
}

void InputPanelDialog::on_BHiraRO_clicked()
{
	Add(/**/"ろ");
}

void InputPanelDialog::on_BHiraWA_clicked()
{
	Add(/**/"わ");
}

void InputPanelDialog::on_BHiraWO_clicked()
{
	Add(/**/"を");
}

void InputPanelDialog::on_BHiraN_clicked()
{
	Add(/**/"ん");
}

void InputPanelDialog::on_BKataA_clicked()
{
	Add(/**/"ア");
}

void InputPanelDialog::on_BKataI_clicked()
{
	Add(/**/"イ");
}

void InputPanelDialog::on_BKataU_clicked()
{
	Add(/**/"ウ");
}

void InputPanelDialog::on_BKataE_clicked()
{
	Add(/**/"エ");
}

void InputPanelDialog::on_BKataO_clicked()
{
	Add(/**/"オ");
}

void InputPanelDialog::on_BKataKA_clicked()
{
	Add(/**/"カ");
}

void InputPanelDialog::on_BKataKI_clicked()
{
	Add(/**/"キ");
}

void InputPanelDialog::on_BKataKU_clicked()
{
	Add(/**/"ク");
}

void InputPanelDialog::on_BKataKE_clicked()
{
	Add(/**/"ケ");
}

void InputPanelDialog::on_BKataKO_clicked()
{
	Add(/**/"コ");
}

void InputPanelDialog::on_BKataGA_clicked()
{
	Add(/**/"ガ");
}

void InputPanelDialog::on_BKataGI_clicked()
{
	Add(/**/"ギ");
}

void InputPanelDialog::on_BKataGU_clicked()
{
	Add(/**/"グ");
}

void InputPanelDialog::on_BKataGE_clicked()
{
	Add(/**/"ゲ");
}

void InputPanelDialog::on_BKataGO_clicked()
{
	Add(/**/"ゴ");
}

void InputPanelDialog::on_BKataSA_clicked()
{
	Add(/**/"サ");
}

void InputPanelDialog::on_BKataSI_clicked()
{
	Add(/**/"シ");
}

void InputPanelDialog::on_BKataSU_clicked()
{
	Add(/**/"ス");
}

void InputPanelDialog::on_BKataSE_clicked()
{
	Add(/**/"セ");
}

void InputPanelDialog::on_BKataSO_clicked()
{
	Add(/**/"ソ");
}

void InputPanelDialog::on_BKataZA_clicked()
{
	Add(/**/"ザ");
}

void InputPanelDialog::on_BKataZI_clicked()
{
	Add(/**/"ジ");
}

void InputPanelDialog::on_BKataZU_clicked()
{
	Add(/**/"ズ");
}

void InputPanelDialog::on_BKataZE_clicked()
{
	Add(/**/"ゼ");
}

void InputPanelDialog::on_BKataZO_clicked()
{
	Add(/**/"ゾ");
}

void InputPanelDialog::on_BKataTA_clicked()
{
	Add(/**/"タ");
}

void InputPanelDialog::on_BKataTI_clicked()
{
	Add(/**/"チ");
}

void InputPanelDialog::on_BKataTU_clicked()
{
	Add(/**/"ツ");
}

void InputPanelDialog::on_BKataTE_clicked()
{
	Add(/**/"テ");
}

void InputPanelDialog::on_BKataTO_clicked()
{
	Add(/**/"ト");
}

void InputPanelDialog::on_BKataXTU_clicked()
{
	Add(/**/"ッ");
}

void InputPanelDialog::on_BKataDA_clicked()
{
	Add(/**/"ダ");
}

void InputPanelDialog::on_BKataDI_clicked()
{
	Add(/**/"ヂ");
}

void InputPanelDialog::on_BKataDU_clicked()
{
	Add(/**/"ヅ");
}

void InputPanelDialog::on_BKataDE_clicked()
{
	Add(/**/"デ");
}

void InputPanelDialog::on_BKataDO_clicked()
{
	Add(/**/"ド");
}

void InputPanelDialog::on_BKataNA_clicked()
{
	Add(/**/"ナ");
}

void InputPanelDialog::on_BKataNI_clicked()
{
	Add(/**/"二");
}

void InputPanelDialog::on_BKataNU_clicked()
{
	Add(/**/"ヌ");
}

void InputPanelDialog::on_BKataNE_clicked()
{
	Add(/**/"ネ");
}

void InputPanelDialog::on_BKataNO_clicked()
{
	Add(/**/"ノ");
}

void InputPanelDialog::on_BKataHA_clicked()
{
	Add(/**/"ハ");
}

void InputPanelDialog::on_BKataHI_clicked()
{
	Add(/**/"ヒ");
}

void InputPanelDialog::on_BKataHU_clicked()
{
	Add(/**/"フ");
}

void InputPanelDialog::on_BKataHE_clicked()
{
	Add(/**/"ヘ");
}

void InputPanelDialog::on_BKataHO_clicked()
{
	Add(/**/"ホ");
}

void InputPanelDialog::on_BKataBA_clicked()
{
	Add(/**/"バ");
}

void InputPanelDialog::on_BKataBI_clicked()
{
	Add(/**/"ビ");
}

void InputPanelDialog::on_BKataBU_clicked()
{
	Add(/**/"ブ");
}

void InputPanelDialog::on_BKataBE_clicked()
{
	Add(/**/"ベ");
}

void InputPanelDialog::on_BKataBO_clicked()
{
	Add(/**/"ボ");
}

void InputPanelDialog::on_BKataPA_clicked()
{
	Add(/**/"パ");
}

void InputPanelDialog::on_BKataPI_clicked()
{
	Add(/**/"ピ");
}

void InputPanelDialog::on_BKataPU_clicked()
{
	Add(/**/"プ");
}

void InputPanelDialog::on_BKataPE_clicked()
{
	Add(/**/"ペ");
}

void InputPanelDialog::on_BKataPO_clicked()
{
	Add(/**/"ポ");
}

void InputPanelDialog::on_BKataMA_clicked()
{
	Add(/**/"マ");
}

void InputPanelDialog::on_BKataMI_clicked()
{
	Add(/**/"ミ");
}

void InputPanelDialog::on_BKataMU_clicked()
{
	Add(/**/"ム");
}

void InputPanelDialog::on_BKataME_clicked()
{
	Add(/**/"メ");
}

void InputPanelDialog::on_BKataMO_clicked()
{
	Add(/**/"モ");
}

void InputPanelDialog::on_BKataYA_clicked()
{
	Add(/**/"ヤ");
}

void InputPanelDialog::on_BKataYU_clicked()
{
	Add(/**/"ユ");
}

void InputPanelDialog::on_BKataYO_clicked()
{
	Add(/**/"ヨ");
}

void InputPanelDialog::on_BKataXYA_clicked()
{
	Add(/**/"ャ");
}

void InputPanelDialog::on_BKataXYU_clicked()
{
	Add(/**/"ュ");
}

void InputPanelDialog::on_BKataXYO_clicked()
{
	Add(/**/"ョ");
}

void InputPanelDialog::on_BKataRA_clicked()
{
	Add(/**/"ラ");
}

void InputPanelDialog::on_BKataRI_clicked()
{
	Add(/**/"リ");
}

void InputPanelDialog::on_BKataRU_clicked()
{
	Add(/**/"ル");
}

void InputPanelDialog::on_BKataRE_clicked()
{
	Add(/**/"レ");
}

void InputPanelDialog::on_BKataRO_clicked()
{
	Add(/**/"ロ");
}

void InputPanelDialog::on_BKataWA_clicked()
{
	Add(/**/"ワ");
}

void InputPanelDialog::on_BKataWO_clicked()
{
	Add(/**/"ヲ");
}

void InputPanelDialog::on_BKataN_clicked()
{
	Add(/**/"ン");
}
