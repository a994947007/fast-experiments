
// fast-experimentsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "fast-experiments.h"
#include "fast-experimentsDlg.h"
#include "afxdialogex.h"
#include "FastExperiment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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


// CfastexperimentsDlg 对话框



CfastexperimentsDlg::CfastexperimentsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FASTEXPERIMENTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfastexperimentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CfastexperimentsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CfastexperimentsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CfastexperimentsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CfastexperimentsDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CfastexperimentsDlg 消息处理程序

BOOL CfastexperimentsDlg::OnInitDialog()
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

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	initData();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CfastexperimentsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CfastexperimentsDlg::OnPaint()
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
HCURSOR CfastexperimentsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

inline void CfastexperimentsDlg::setDefaultValue(const ULONG controID, LPCTSTR value)
{
	((CEdit*)GetDlgItem(controID))->SetWindowTextW(value);
}

template<typename T>
inline T CfastexperimentsDlg::getValueByControID(const ULONG controID)
{
	CString m_str;
	GetDlgItem(controID)->GetWindowTextW(m_str);
	CStringA m_strA(m_str);
	if (std::is_same<T, ULONG>::value)
	{
		UINT value = atoi(m_strA);
		return value;
	}
	else if ((std::is_same<T, double>::value))
	{
		double value = atof(m_strA);
		return value;
	}
	return T();
}

void CfastexperimentsDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (userConfig.fileList.empty()) {
		CString msg("您还没有选择数据源文件！");
		AfxMessageBox(msg);
		return;
	}
	if (userConfig.resultPath.length() == 0) {
		CString msg("您还没有选择结果保存目录！");
		AfxMessageBox(msg);
		return;
	}

	initUserConfig();

	FastExperiment * experiment = createFastExperiment();
	experiment->run();
	delete experiment;

	CString msg("运行完毕！");
	AfxMessageBox(msg);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CfastexperimentsDlg::OnBnClickedButton1()
{
	CString strFile = _T("");
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT;
	CFileDialog dlgFile(TRUE, _T("cap"), NULL, dwFlags, _T("Ip trace(*.hsn;*.txt)|*.hsn;*.txt||"), NULL);
	if (dlgFile.DoModal() != IDOK)
	{
		return;
	}

	POSITION pos = dlgFile.GetStartPosition();
	while (NULL != pos) {
		CString strFileName = dlgFile.GetNextPathName(pos);
		string fileName = CT2A(strFileName);
		userConfig.fileList.push_back(fileName);

		CString oldMessage;
		GetDlgItem(IDC_MSG_AREA)->GetWindowTextW(oldMessage);
		GetDlgItem(IDC_MSG_AREA)->SetWindowTextW(oldMessage + strFileName + "\r\n");
	}
}

void CfastexperimentsDlg::OnBnClickedButton2()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = NULL;
	bi.pszDisplayName = szBuffer;
	bi.lpszTitle = _T("选择需要保存的路径");
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if (NULL == idl) {
		return;
	}
	SHGetPathFromIDList(idl, szBuffer);
	userConfig.resultPath = CT2A(szBuffer);
}

// 初始化组件中的参数
void CfastexperimentsDlg::initData()
{

}

// 解析组件中的配置信息，将其设置到UserConfig中
void CfastexperimentsDlg::initUserConfig()
{
	
}

// 设置当前实验
FastExperiment * CfastexperimentsDlg::createFastExperiment()
{
	return new FastExperiment(userConfig);
}


