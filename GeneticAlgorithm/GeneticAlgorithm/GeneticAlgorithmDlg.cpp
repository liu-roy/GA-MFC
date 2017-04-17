
// mfcdemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include "GeneticAlgorithmDlg.h"
#include "afxdialogex.h"
//#include"GA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
 

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcdemoDlg 对话框




CmfcdemoDlg::CmfcdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmfcdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_origImage=NULL;
	m_origImage2=NULL;
	//origMat=Mat();
	//  m_SIZE = 0;
	//  m_pCROSS = 0.0;
	m_pCROSS = 0.0;
	m_pVARIATION = 0.0;
	//  p_SELECT = 0.0;
	memset(m_Histogram,0,sizeof(m_Histogram));
	memset(m_Statistic,0,sizeof(m_Statistic));
	m_SIZE =1;
}

void CmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_pSelect);
	//  DDV_MinMaxUInt(pDX, m_pSelect, 0, 1);
	//  DDX_Text(pDX, IDC_EDIT2, m_pCross);
	//  DDV_MinMaxUInt(pDX, m_pCross, 0, 1);
	//  DDX_Text(pDX, IDC_EDIT3, m_pVariation);
	//  DDV_MinMaxUInt(pDX, m_pVariation, 0, 1);
	//  DDX_Text(pDX, IDC_EDIT1, m_SIZE);
	//  DDV_MinMaxDouble(pDX, m_SIZE, 0, 1);
	//  DDX_Text(pDX, IDC_EDIT3, m_pCROSS);
	//  DDV_MinMaxDouble(pDX, m_pCROSS, 0, 1);
	DDX_Text(pDX, IDC_EDIT2, m_pCROSS);
	DDV_MinMaxDouble(pDX, m_pCROSS, 0, 1);
	DDX_Text(pDX, IDC_EDIT3, m_pVARIATION);
	DDV_MinMaxDouble(pDX, m_pVARIATION, 0, 1);
	DDX_Text(pDX, IDC_EDIT1, m_SIZE);
	DDV_MinMaxInt(pDX, m_SIZE, 1, 1000);
}

BEGIN_MESSAGE_MAP(CmfcdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcdemoDlg::OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC2, &CmfcdemoDlg::OnStnClickedStatic2)
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcdemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcdemoDlg::OnBnClickedButton3)
	ON_STN_CLICKED(IDC_STATIC5, &CmfcdemoDlg::OnStnClickedStatic5)
	ON_BN_CLICKED(IDC_BUTTON4, &CmfcdemoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CmfcdemoDlg 消息处理程序

BOOL CmfcdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcdemoDlg::OnPaint()
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
HCURSOR CmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//绘图
void CmfcdemoDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );

}


void CmfcdemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName; 
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if(dlg.DoModal()==IDOK)  
		FilePathName=dlg.GetPathName();
	if(m_origImage) cvReleaseImage(&m_origImage);
	if(m_origImage2) cvReleaseImage(&m_origImage2);
	m_origImage=cvLoadImage(FilePathName,1); //显示图片
	m_origImage2=cvLoadImage(FilePathName,1);
	DrawPicToHDC(m_origImage, IDC_STATIC1);

	//获取直方图
	Size size;
	uchar tmp; 
	size.height=m_origImage->height;
	size.width=m_origImage->width;
	int n=size.height*size.width;
	int z=m_origImage->widthStep;
	uchar* data=(uchar *)m_origImage->imageData;  
	int channels = m_origImage->nChannels;  
	for(int i=0;i<size.height;i++)
	{	for(int j=0;j<size.width;j++)
		{	tmp=data[i*z+j*channels+0];  
			m_Histogram[tmp]++;
			m_Statistic[tmp]++;
		}
	}
	for(int i=0;i<256;i++){
		
		m_Histogram[i]/=n;
	}

}


void CmfcdemoDlg::OnStnClickedStatic2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CmfcdemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName; 
	CFileDialog dlg(false,"*.bmp","Test.bmp",OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"保存为(*.bmp)|*.bmp|所有文件(*.*)|*.*||"); 
	if(dlg.DoModal()==IDOK) 
	{ 
		FilePathName=dlg.GetPathName(); 
		cvSaveImage(FilePathName,m_origImage); 
		 
	}
}


void CmfcdemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//
	double newfitness=0;
	double oldfitness=0;
	int bestyuzhi=0;
	Goriginal=(chromosome*)malloc(sizeof(chromosome)*m_SIZE);
	Gbackup=(chromosome*)malloc(sizeof(chromosome)*m_SIZE);;
	
	InitializePopulation(Goriginal, m_SIZE);
	GetFitness(Goriginal,m_Histogram,m_Statistic,m_SIZE);
	for(int i=0;i<m_SIZE;i++)
		Gbackup[i]=Goriginal[i];
	int p=10;
	do
	{
		oldfitness=newfitness;
		FucSelect(Goriginal,m_SIZE);
		FucCross(Goriginal,m_SIZE,m_pCROSS);
		FucVariation(Goriginal,m_SIZE,m_pVARIATION);
		FucReproduct(Goriginal,Gbackup,m_Histogram,m_Statistic,m_SIZE,newfitness,bestyuzhi);
	}while(abs((newfitness-oldfitness))>0.0001);
	delete []Gbackup;
	delete []Goriginal;
	Size size;
	size.height=m_origImage->height;
	size.width=m_origImage->width;
	int z=m_origImage->widthStep;
	uchar* data=(uchar *)m_origImage->imageData;  
	int channels = m_origImage->nChannels;  
	for(int i=0;i<size.height;i++)  
	{
		 for(int j=0;j<size.width;j++)
		 {  
			 if(data[i*z+j*channels+0]>=bestyuzhi)
			 {
				data[i*z+j*channels+0]=255;  
				data[i*z+j*channels+1]=255;  
            	data[i*z+j*channels+2]=255;  
			 }
			 else
			 {
				 data[i*z+j*channels+0]=0	;  
				data[i*z+j*channels+1]=0;  
            	data[i*z+j*channels+2]=0;  
			 }
		 }  
	}


	/*
	int z=m_origImage->widthStep;
	for(int i=0;i<size.height;i++)
	{	for(int j=0;j<size.width;j++)
		{	if(((uchar *)(m_origImage->imageData + i*z))[j]>=bestyuzhi)
				((uchar *)(m_origImage->imageData + i*z))[j]=255;
			else
				((uchar *)(m_origImage->imageData + i*z))[j]=0;
		}
	
	}*/
	DrawPicToHDC(m_origImage, IDC_STATIC2);
	
	
}


void CmfcdemoDlg::OnStnClickedStatic5()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CmfcdemoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	IplImage*pCannyImg=cvCreateImage(cvGetSize(m_origImage2),IPL_DEPTH_8U,1);
     cvCanny(m_origImage2,pCannyImg,50,150,3);
	/*Size size;
	size.height=pCannyImg->height;
	size.width=pCannyImg->width;
	int z=pCannyImg->widthStep;
	uchar* data=(uchar *)pCannyImg->imageData;  
	int channels = pCannyImg->nChannels;  
	int jstart=0;int jend=0;int flag=0;
	for(int i=0;i<size.height;i++) 
	{
		 for(int j=0;j<size.width;j++)
		 {  
			 if(data[i*z+j*channels]>=200&&flag==0)
			 {
				jstart= j; 
				flag=1;
			 }
			 if(data[i*z+j*channels]>=200&&flag==1)
				 jend=j;
		} 
		 for(int j=jstart+1;j<jend;j++)
		 {  
			 
			data[i*z+j*channels]=0;
				 
		} 

		 flag=0;

	}*/
	DrawPicToHDC(pCannyImg, IDC_STATIC3);


}
