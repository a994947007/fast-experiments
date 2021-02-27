﻿
// fast-experimentsDlg.h: 头文件
//

#pragma once

#include "UserConfig.h"


// CfastexperimentsDlg 对话框
class CfastexperimentsDlg : public CDialogEx
{
// 构造
public:
	CfastexperimentsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FASTEXPERIMENTS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	UserConfig userConfig;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	virtual void initData();
	virtual void initUserConfig();

	template <typename T>
	inline T getValueByControID(const ULONG controID);
	inline void setDefaultValue(const ULONG controID, LPCTSTR value);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};