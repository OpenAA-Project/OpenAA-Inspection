#ifndef INPUTPANELDIALOG_H
#define INPUTPANELDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class InputPanelDialog;
}

class	QTextCodec;

class InputPanelDialog : public QDialog
{
    Q_OBJECT
    
	int	Type;
	QString	Result;
	QTextCodec	*CodecCString;
	QTextCodec	*CodecLocale;
	QTextCodec	*CodecTr;
public:
	
#define	IPD_Number	1
#define	IPD_Alpha	2
#define	IPD_Sign	4
#define	IPD_Hira	8
#define	IPD_Kata	16

    explicit InputPanelDialog(int type=-1,const QString &LastStr=QString(),QWidget *parent = 0);
    ~InputPanelDialog();
    
	QString	GetResult(void)	{	return Result;	}

private slots:
    void on_BNext_clicked();
    void on_BBS_clicked();
    void on_BDel_clicked();
    void on_BLeft_clicked();
    void on_BRight_clicked();
    void on_BEnter_clicked();
    void on_B0_clicked();
    void on_B1_clicked();
    void on_B2_clicked();
    void on_B3_clicked();
    void on_B4_clicked();
    void on_B5_clicked();
    void on_B6_clicked();
    void on_B7_clicked();
    void on_B8_clicked();
    void on_B9_clicked();
    void on_BDot_clicked();
    void on_BMul_clicked();
    void on_BPlus_clicked();
    void on_BMinus_clicked();
    void on_BDiv_clicked();
    void on_Ba_clicked();
    void on_Bb_clicked();
    void on_Bc_clicked();
    void on_Bd_clicked();
    void on_Be_clicked();
    void on_Bf_clicked();
    void on_Bg_clicked();
    void on_Bh_clicked();
    void on_Bi_clicked();
    void on_Bj_clicked();
    void on_Bk_clicked();
    void on_Bl_clicked();
    void on_Bm_clicked();
    void on_Bn_clicked();
    void on_Bo_clicked();
    void on_Bp_clicked();
    void on_Bq_clicked();
    void on_Br_clicked();
    void on_Bs_clicked();
    void on_Bt_clicked();
    void on_Bu_clicked();
    void on_Bv_clicked();
    void on_Bw_clicked();
    void on_Bx_clicked();
    void on_By_clicked();
    void on_Bz_clicked();
    void on_BA_clicked();
    void on_BB_clicked();
    void on_BC_clicked();
    void on_BD_clicked();
    void on_BE_clicked();
    void on_BF_clicked();
    void on_BG_clicked();
    void on_BH_clicked();
    void on_BI_clicked();
    void on_BJ_clicked();
    void on_BK_clicked();
    void on_BL_clicked();
    void on_BM_clicked();
    void on_BN_clicked();
    void on_BO_clicked();
    void on_BP_clicked();
    void on_BQ_clicked();
    void on_BR_clicked();
    void on_BS_clicked();
    void on_BT_clicked();
    void on_BU_clicked();
    void on_BV_clicked();
    void on_BW_clicked();
    void on_BX_clicked();
    void on_BY_clicked();
    void on_BZ_clicked();
    void on_BExclamation_clicked();
    void on_BDQuotation_clicked();
    void on_BSharp_clicked();
    void on_BDollar_clicked();
    void on_BPercent_clicked();
    void on_BAnd_clicked();
    void on_BSQuotation_clicked();
    void on_BYen_clicked();
    void on_BLParenthesis_clicked();
    void on_BRParenthesis_clicked();
    void on_BEqual_clicked();
    void on_BXor_clicked();
    void on_BLBracket_clicked();
    void on_BRBracket_clicked();
    void on_BLBrace_clicked();
    void on_BRBrace_clicked();
    void on_BLessThan_clicked();
    void on_BGreaterThan_clicked();
    void on_BQuestion_clicked();
    void on_BAtmark_clicked();
    void on_BSemicolon_clicked();
    void on_BColon_clicked();
    void on_BUnderbar_clicked();
    void on_BComma_clicked();
    void on_BTilde_clicked();
    void on_BOr_clicked();
    void on_BSpace_clicked();

    void on_BHiraA_clicked();
    void on_BHiraI_clicked();
    void on_BHiraU_clicked();
    void on_BHiraE_clicked();
    void on_BHiraO_clicked();
    void on_BHiraKA_clicked();
    void on_BHiraKI_clicked();
    void on_BHiraKU_clicked();
    void on_BHiraKE_clicked();
    void on_BHiraKO_clicked();
    void on_BHiraGA_clicked();
    void on_BHiraGI_clicked();
    void on_BHiraGU_clicked();
    void on_BHiraGE_clicked();
    void on_BHiraGO_clicked();
    void on_BHiraSA_clicked();
    void on_BHiraSI_clicked();
    void on_BHiraSU_clicked();
    void on_BHiraSE_clicked();
    void on_BHiraSO_clicked();
    void on_BHiraZA_clicked();
    void on_BHiraZI_clicked();
    void on_BHiraZU_clicked();
    void on_BHiraZE_clicked();
	void on_BHiraZO_clicked();
    void on_BHiraTA_clicked();
    void on_BHiraTI_clicked();
    void on_BHiraTU_clicked();
    void on_BHiraTE_clicked();
    void on_BHiraTO_clicked();
    void on_BHiraXTU_clicked();
    void on_BHiraDA_clicked();
    void on_BHiraDI_clicked();
    void on_BHiraDU_clicked();
    void on_BHiraDE_clicked();
    void on_BHiraDO_clicked();
    void on_BHiraNA_clicked();
    void on_BHiraNI_clicked();
    void on_BHiraNU_clicked();
    void on_BHiraNE_clicked();
    void on_BHiraNO_clicked();
    void on_BHiraHA_clicked();
    void on_BHiraHI_clicked();
    void on_BHiraHU_clicked();
    void on_BHiraHE_clicked();
    void on_BHiraHO_clicked();
    void on_BHiraBA_clicked();
    void on_BHiraBI_clicked();
    void on_BHiraBU_clicked();
    void on_BHiraBE_clicked();
    void on_BHiraBO_clicked();
    void on_BHiraPA_clicked();
    void on_BHiraPI_clicked();
    void on_BHiraPU_clicked();
    void on_BHiraPE_clicked();
    void on_BHiraPO_clicked();
    void on_BHiraMA_clicked();
    void on_BHiraMI_clicked();
    void on_BHiraMU_clicked();
    void on_BHiraME_clicked();
    void on_BHiraMO_clicked();
    void on_BHiraYA_clicked();
    void on_BHiraYU_clicked();
    void on_BHiraYO_clicked();
    void on_BHiraXYA_clicked();
    void on_BHiraXYU_clicked();
    void on_BHiraXYO_clicked();
    void on_BHiraRA_clicked();
    void on_BHiraRI_clicked();
    void on_BHiraRU_clicked();
    void on_BHiraRE_clicked();
    void on_BHiraRO_clicked();
    void on_BHiraWA_clicked();
    void on_BHiraWO_clicked();
    void on_BHiraN_clicked();

    void on_BKataA_clicked();
    void on_BKataI_clicked();
    void on_BKataU_clicked();
    void on_BKataE_clicked();
    void on_BKataO_clicked();
    void on_BKataKA_clicked();
    void on_BKataKI_clicked();
    void on_BKataKU_clicked();
    void on_BKataKE_clicked();
    void on_BKataKO_clicked();
    void on_BKataGA_clicked();
    void on_BKataGI_clicked();
    void on_BKataGU_clicked();
    void on_BKataGE_clicked();
    void on_BKataGO_clicked();
    void on_BKataSA_clicked();
    void on_BKataSI_clicked();
    void on_BKataSU_clicked();
    void on_BKataSE_clicked();
    void on_BKataSO_clicked();
    void on_BKataZA_clicked();
    void on_BKataZI_clicked();
    void on_BKataZU_clicked();
    void on_BKataZE_clicked();
    void on_BKataZO_clicked();
    void on_BKataTA_clicked();
    void on_BKataTI_clicked();
    void on_BKataTU_clicked();
    void on_BKataTE_clicked();
    void on_BKataTO_clicked();
    void on_BKataXTU_clicked();
    void on_BKataDA_clicked();
    void on_BKataDI_clicked();
    void on_BKataDU_clicked();
    void on_BKataDE_clicked();
    void on_BKataDO_clicked();
    void on_BKataNA_clicked();
    void on_BKataNI_clicked();
    void on_BKataNU_clicked();
    void on_BKataNE_clicked();
    void on_BKataNO_clicked();
    void on_BKataHA_clicked();
    void on_BKataHI_clicked();
    void on_BKataHU_clicked();
    void on_BKataHE_clicked();
    void on_BKataHO_clicked();
    void on_BKataBA_clicked();
    void on_BKataBI_clicked();
    void on_BKataBU_clicked();
    void on_BKataBE_clicked();
    void on_BKataBO_clicked();
    void on_BKataPA_clicked();
    void on_BKataPI_clicked();
    void on_BKataPU_clicked();
    void on_BKataPE_clicked();
    void on_BKataPO_clicked();
    void on_BKataMA_clicked();
    void on_BKataMI_clicked();
    void on_BKataMU_clicked();
    void on_BKataME_clicked();
    void on_BKataMO_clicked();
    void on_BKataYA_clicked();
    void on_BKataYU_clicked();
    void on_BKataYO_clicked();
    void on_BKataXYA_clicked();
    void on_BKataXYU_clicked();
    void on_BKataXYO_clicked();
    void on_BKataRA_clicked();
    void on_BKataRI_clicked();
    void on_BKataRU_clicked();
    void on_BKataRE_clicked();
    void on_BKataRO_clicked();
    void on_BKataWA_clicked();
    void on_BKataWO_clicked();
    void on_BKataN_clicked();

private:
    Ui::InputPanelDialog *ui;

	void	Add(const QString &c);
	void	ShowCpntrolPanel(void);
	virtual	void	closeEvent ( QCloseEvent * e )	override;
};

#endif // INPUTPANELDIALOG_H
