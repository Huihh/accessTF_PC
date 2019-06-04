
// accessTFDlg.h: 头文件
//

#pragma once


// CaccessTFDlg 对话框
class CaccessTFDlg : public CDialogEx
{
// 构造
public:
	CaccessTFDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCESSTF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


	//Show the message
	void ShowMessageString(CString Message, int color);

	//CString convert to BYTE
	void CstringToByte(CString sInput, BYTE bOutput[]);

	//Ascii convert to Hex
	BOOL AsciiToHex(BYTE pAsciiArray[], BYTE pHexArray[], int Len);




	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonSearch();
	CComboBox m_cb_drive;
	CRichEditCtrl m_re_receivedata;
	CEdit m_e_senddata;

};
