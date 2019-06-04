
// accessTFDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "accessTF.h"
#include "accessTFDlg.h"
#include "afxdialogex.h"
#include "CDiskReadWrite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define COLOR_RED		0xFF0000
#define COLOR_GREEN		0x00FF00
#define COLOR_BLUE		0x0000FF
#define COLOR_BLACK		0x000000
#define COLOR_WHITE		0xFFFFFF









// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CaccessTFDlg 对话框



CaccessTFDlg::CaccessTFDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACCESSTF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CaccessTFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRIVE, m_cb_drive);
	DDX_Control(pDX, IDC_RICHEDIT_RECEIVE_DATA, m_re_receivedata);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_e_senddata);
}

BEGIN_MESSAGE_MAP(CaccessTFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_SEND, &CaccessTFDlg::OnBnClickedButtonSend)
ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CaccessTFDlg::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CaccessTFDlg 消息处理程序

BOOL CaccessTFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CaccessTFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CaccessTFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CaccessTFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




/*************************** 自定义方法区域    开始 ***************************/

void CaccessTFDlg::ShowMessageString(CString Message, int color)
{
	CHARFORMAT	cf;
	int r, g, b;
	int len;

	r = ((color >> 16) & 0xFF);
	g = ((color >> 8) & 0xFF);
	b = ((color >> 0) & 0xFF);

	memset(&cf, 0, sizeof(cf));

	m_re_receivedata.GetDefaultCharFormat(cf);


	cf.dwMask = CFM_COLOR;
	cf.dwEffects &= ~CFE_AUTOCOLOR;

	cf.crTextColor = RGB(r, g, b);

	m_re_receivedata.SetSel(-1, -1);
	m_re_receivedata.SetSelectionCharFormat(cf);

	len = m_re_receivedata.GetWindowTextLength();

	if ((len + Message.GetLength()) > (m_re_receivedata.GetLimitText()))
	{
		m_re_receivedata.SetWindowText(_T("Clear Screen ...\r\n"));
	}

	Message += "\r\n";


	m_re_receivedata.SetSel(-1, -1);
	m_re_receivedata.ReplaceSel(Message);

	m_re_receivedata.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

}



void CaccessTFDlg::CstringToByte(CString sInput, BYTE bOutput[])
{
	BYTE srcBuf[1024] = { 0 };	// The Bigger the better     by Huihh 2016.9.12
	BYTE desBuf[1024] = { 0 };
	int srcLen = 0;


	strcpy((char*)srcBuf, sInput);
	srcLen = strlen(sInput);


	AsciiToHex(srcBuf, desBuf, srcLen);   //这里输入长度为字符的个数   by Huihh 2016.11.11

	for (int i = 0; i < (srcLen / 2); i++)
	{
		bOutput[i] = desBuf[i];
	}

}



BOOL CaccessTFDlg::AsciiToHex(BYTE pAsciiArray[], BYTE pHexArray[], int Len)
{
	BYTE tempBuf[2] = { 0 };

	if (Len % 2 != 0)
	{
		AfxMessageBox(_T("Ascii Convert Hex Failed, Please input Convert Length in even numbers, Try Again Later"));
		return FALSE;
	}

	int HexLen = Len / 2;   // 2 Character Convert 1 Hex  by Huihh 2016.9.8

	for (int i = 0; i < HexLen; i++)
	{
		tempBuf[0] = *pAsciiArray++;
		tempBuf[1] = *pAsciiArray++;

		for (int j = 0; j < 2; j++)
		{
			if (tempBuf[j] <= 'F' && tempBuf[j] >= 'A')
			{
				tempBuf[j] = tempBuf[j] - 'A' + 10;
			}
			else if (tempBuf[j] <= 'f' && tempBuf[j] >= 'a')
			{
				tempBuf[j] = tempBuf[j] - 'a' + 10;
			}
			else if (tempBuf[j] >= '0' && tempBuf[j] <= '9')
			{
				tempBuf[j] = tempBuf[j] - '0';
			}
			else
			{
				AfxMessageBox(_T("pAsciiArray Contain illegality Character, Please Try Again after Check "));
				return FALSE;
			}
		}

		pHexArray[i] = tempBuf[0] << 4;
		pHexArray[i] |= tempBuf[1];
	}

	return TRUE;
}







/*************************** 自定义方法区域    结束 ***************************/























void CaccessTFDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码

	CString str_drive;
	m_cb_drive.GetWindowTextA(str_drive);

	UINT uType = GetDriveType(str_drive);
	if (uType != DRIVE_REMOVABLE) {
		AfxMessageBox(CString(str_drive + " 不是移动磁盘"));
		return;
	}

	CDiskReadWrite diskReadWrite;
	CHAR chDrive = str_drive.GetAt(0);
	DWORD start_sector = 0x1;
	BOOL ret = false;
	BYTE dataBuf[20*512] = { 0 };

	for (int i = 0; i < 512; i++)
		dataBuf[i] = 511-i;


	//ShowMessageString(_T("写入数据为: "), COLOR_BLACK);
	CString strDisp, strTmp;
	//for (int i = 0; i < 512; i++)
	//{
	//	strTmp.Format(_T("%02x "), dataBuf[i]);
	//	strDisp += strTmp;
	//}
	//ShowMessageString(strDisp, COLOR_GREEN);
	//ret = diskReadWrite.WriteSectors(BYTE(chDrive - 'A' + 1), 3, 1, dataBuf);
	//if (ret == 0) {
	//	ShowMessageString(_T("写入失败"), COLOR_RED);
	//	return;
	//}


	memset(dataBuf, 0x00, 512);
	ret = diskReadWrite.ReadSectors(BYTE(chDrive - 'A' + 1), 0, 20, dataBuf);
	if (ret == 0) {
		ShowMessageString(_T("读取失败"), COLOR_RED);
		return;
	}

	ShowMessageString(_T("读取数据为: "), COLOR_BLACK);
	strDisp = "";
	for (int i = 0; i < 512*20; i++)
	{
		strTmp.Format(_T("%02x "), dataBuf[i]);
		strDisp += strTmp;
	}
	ShowMessageString(strDisp, COLOR_GREEN);
}


void CaccessTFDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR buf[128] = { 0 };
	CString str;
	DWORD len = GetLogicalDriveStrings(sizeof(buf) / sizeof(TCHAR), buf);
	UINT uType= 0, exist = 0;
	TCHAR* p = NULL;

	for (p = buf; *p; p += (_tcslen(p) + 1)) {
		LPCTSTR sDrivePath = p;
		str = sDrivePath;
		str.Delete(2, 1);
		uType = GetDriveType(str);
		if (uType == DRIVE_REMOVABLE) {
			m_cb_drive.AddString(str);
			exist = 1;
		}
	}

	if (exist == 0) {
		AfxMessageBox(_T("没有检测到 SD 卡, 请重新插拔"));
	}

	m_cb_drive.SetCurSel(0);
}

