
// SampleDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"


// CSampleDlg ダイアログ
class CSampleDlg : public CDialogEx
{
// コンストラクション
public:
	CSampleDlg(CWnd* pParent = NULL);	// 標準コンストラクター

// ダイアログ データ
	enum { IDD = IDD_SAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedBtnTest();
	CListBox m_List1;
	afx_msg void OnBnClickedBtnTest2();
	void AddLog( CString csMessage );
};
