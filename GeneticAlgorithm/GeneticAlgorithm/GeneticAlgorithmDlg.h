
// mfcdemoDlg.h : 头文件
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
#include "GA.h"
using namespace cv;

// CmfcdemoDlg 对话框
class CmfcdemoDlg : public CDialogEx
{
// 构造
public:
	CmfcdemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCDEMO_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	void DrawPicToHDC(IplImage *img, UINT ID);
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
public:
	IplImage* m_origImage;
public:
//	int m_SIZE;
	double m_pCROSS;
	double m_pVARIATION;
//	afx_msg void OnEnChangeEdit1();

//	double p_SELECT;
	double m_Histogram[256];
	int m_Statistic[256];
public:
	afx_msg void OnStnClickedStatic5();
	int m_SIZE;
public:
	chromosome *Goriginal;
	chromosome *Gbackup;
	IplImage* m_origImage2;
public:

	afx_msg void OnBnClickedButton4();
};
