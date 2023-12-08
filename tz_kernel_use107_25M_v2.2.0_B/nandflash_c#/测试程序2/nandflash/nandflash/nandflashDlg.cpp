// nandflashDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "nandflash.h"
#include "nandflashDlg.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <Cdir.h>
//#include <io.h>

int flagStart=0;
int flagRemove=0;
HANDLE	hCommWatchThread; //辅助线程的全局函数
DWORD dwTreadID; //线程ID

HANDLE RemoveThread;
DWORD  RemoveID;

int kk = 1;
int mm = 1;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//jing wen yi add

#define MAX_FILE_LENGTH	64  //最大txt文件大小，单位M
#define PERSEND_WIDTH 50

/*TCHAR *CnandflashDlg::CString2TCHAR(CString &str)
{
	int iLen = str.GetLength();
	TCHAR* szRs = new TCHAR[iLen];
	lstrcpy(szRs,str.GetBuffer(iLen));
	str.ReleaseBuffer();
	return szRs;
}*/

char buf[50]={0};

size_t myfwrite(const void* buffer, size_t size, size_t count, FILE* stream)
{
	size_t res;
	res=fwrite( buffer,  size, count,  stream);
	fflush(stream);
	return res;

}
//日志文件
class LogFile
{
public:
	static LogFile &instance();
	operator FILE *() const { return m_file; }
	private
		:LogFile(const char *filename)
	{
		m_file = fopen(filename, "w+");
	}
	~LogFile()
	{
		fclose(m_file);
	}
	FILE *m_file;
};

LogFile &LogFile::instance()
{
	static LogFile log("AppLog.txt");
	return log;
}

//获得时间
long int  gettime()
{
	long int res=0;
	SYSTEMTIME sys;  
	GetLocalTime( &sys );  
	sprintf(buf,"%02d:%02d:%02d\r\n",sys.wHour,sys.wMinute, sys.wSecond);
	res = sys.wHour*3600+sys.wMinute*60+sys.wSecond;
	return res;
}

void CnandflashDlg::RemoveFunction()
{
	CString number_string;
	unsigned int number,i;
	CString string;
	int jishu;
	char err_string[50];
	m_control.GetWindowText(number_string);
	number = _ttoi(number_string);
	for(i=1; i<(number+1); i++)
	{
		jishu++;
		string.Format(L"%dM.txt",i);
		TCHAR* pFileName =string.GetBuffer();
		try
		{
			CFile::Remove(pFileName);
		}

		catch (CFileException* e)
		{
			myfwrite("删除文件失败\r\n", 1, 14, LogFile::instance());
			sprintf(err_string,"第%d个文件\r\n",jishu);
			myfwrite(err_string,strlen(err_string),1,LogFile::instance());
			TRACE(_T("File %20s cannot be removed \r\n"),pFileName);
			e->Delete();
		}

	}
}

void CnandflashDlg::comparefile(char * str1,int jishu)
{	
	int size_buffer = 2*1024*1024;
	char *comp_buf = new char[size_buffer];
	char *str_buf  = new char[size_buffer]; 
	char *p_comp = comp_buf;
	char *p_str = str_buf;
	char err_string[50];
	size_t comp_size,comp_str;
	char *compfile = "comparetestfile.txt";
	FILE * fp1;
	FILE * fp2;
	fp1 = fopen(compfile, "r");
	
	if(fp1==NULL)
	{
		myfwrite("打开comparetestfile文件失败\r\n", 1, 29, LogFile::instance());
		sprintf(err_string,"第%d个文件\r\n",jishu);
		myfwrite(err_string,strlen(err_string),1,LogFile::instance());
		return ;
	}
	else
	{
		comp_size = fread(comp_buf,1,size_buffer,fp1);
	}
	fp2 = fopen(str1,"r");
	if(fp2==NULL)
	{
		myfwrite("打开要比较的文件失败\r\n", 1, 22, LogFile::instance());
		sprintf(err_string,"第%d个文件\r\n",jishu);
		myfwrite(err_string,strlen(err_string),1,LogFile::instance());
		return;
	}
	else
	{
		comp_str = fread(str_buf,1,size_buffer,fp2);
	}
	if(comp_size != comp_str)
	{
		myfwrite("字节数不一样\r\n", 1, 14, LogFile::instance());
		sprintf(err_string,"comp_size = %d\r\n",comp_size);
		myfwrite(err_string,strlen(err_string),1,LogFile::instance());
		sprintf(err_string,"comp_str = %d\r\n",comp_str);
		myfwrite(err_string,strlen(err_string),1,LogFile::instance());
		sprintf(err_string,"第%d几个\r\n",jishu);
		myfwrite(err_string,strlen(err_string),1,LogFile::instance());

	}
	int i=0;
	while(*p_comp!='\0')
	{
		i++;
		if(*p_str!= *p_comp)
		{
			//myfwrite("打开comparetestfile文件失败\r\n", 1, 29, LogFile::instance());
			sprintf(err_string,"第%d个文件",jishu);
			myfwrite(err_string,strlen(err_string),1,LogFile::instance());
			sprintf(err_string,"第%d个字节不同",i);
			myfwrite(err_string,strlen(err_string),1,LogFile::instance());
			myfwrite(p_comp,1,1,LogFile::instance());
			myfwrite(" 变成了 ", 1, 8, LogFile::instance());
			myfwrite(p_str,1,1,LogFile::instance());
			myfwrite("\r\n", 1, 2, LogFile::instance());
		}
		
		
		p_comp++;
		p_str++;
	}
	fclose(fp1);
	fclose(fp2);
	delete []comp_buf;
	delete []str_buf;
}

void CnandflashDlg::P_ReadPortThread(void)
{
	if(!kk)
	{
		return;
	}
	kk=0;
	myfwrite("开始测试\r\n", 1, 10, LogFile::instance());
	CString number_string;
	CString size_string;
	//CString err_string;
	
	unsigned int size,i,j,count,number,n;
	int jishu=0;
	char string[50]; 
	char err_string[50];
	FILE* fp;
	m_control.GetWindowText(number_string);
	m_size_control.GetWindowText(size_string);

	size = _ttoi(size_string);
	number = _ttoi(number_string);

	for(n=0; n<300; n++)
	{

		for(i=1; i<(number+1); i++)
		{	
			jishu++;
			sprintf(string,"\\%dM.txt",i);
			fp = fopen(string, "w+");
			if(fp==NULL)
			{
				myfwrite("打开文件失败\r\n", 1, 14, LogFile::instance());
				sprintf(err_string,"第几个%d文件\r\n",jishu);
				myfwrite(err_string,strlen(err_string),1,LogFile::instance());
				//MessageBox(L"打开文件失败！！");
				//return;
			}
			count = size*1024*1024/10;
			for(j=0; j<count; j++)
			{
				sprintf(string, "%08d\r\n",j);
				fwrite(string ,10,1,fp);
			}
			fclose(fp);
			
			sprintf(string,"\\%dM.txt",i);
			
			
			number_string.Format(L"%d",jishu);
			m_num_control.SetWindowText(number_string);
			comparefile(string,jishu);
		
		}
		RemoveFunction();
		if(n==299)
		{
			myfwrite("测试结束\r\n", 1, 10, LogFile::instance());
			MessageBox(L"测试结束！！");
			return;
		}
	}
}

DWORD WINAPI CnandflashDlg::G_ReadThread(LPVOID lpParameter)
{
	CnandflashDlg *p = (CnandflashDlg *)lpParameter;

	p->P_ReadPortThread();	

	return true;
}



void CnandflashDlg::P_RemovePortThread(void)
{
	if(!mm)
	{
		return;
	}
	mm=0;
	RemoveFunction();
	/*CString number_string;
	unsigned int number,i;
	CString string;
	m_control.GetWindowText(number_string);
	number = _ttoi(number_string);
	for(i=0; i<number; i++)
	{
		string.Format(L"%dM.txt",i);
		TCHAR* pFileName =string.GetBuffer();
		try
		{
			CFile::Remove(pFileName);
		}
		
		catch (CFileException* e)
		{
			TRACE(_T("File %20s cannot be removed \r\n"),pFileName);
			e->Delete();
		}

		if(i==(number-1))
		{
			MessageBox(L"删除文件成功！！");
			return;
		}
		
		
	}*/
}

DWORD WINAPI CnandflashDlg::G_RemoveThread(LPVOID lpParameter)
{
	CnandflashDlg *p = (CnandflashDlg *)lpParameter;

	p->P_RemovePortThread();	

	return true;
}

// CnandflashDlg 对话框

CnandflashDlg::CnandflashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CnandflashDlg::IDD, pParent)
	, m_value(_T(""))
	, m_size_value(_T(""))
	, m_num_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnandflashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_control);
	DDX_Text(pDX, IDC_EDIT2, m_value);
	DDX_Control(pDX, IDC_EDIT3, m_size_control);
	DDX_Text(pDX, IDC_EDIT3, m_size_value);
	DDX_Control(pDX, IDC_EDIT4, m_num_control);
	DDX_Text(pDX, IDC_EDIT4, m_num_value);
}

BEGIN_MESSAGE_MAP(CnandflashDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	//ON_STN_CLICKED(IDC_STATIC_1, &CnandflashDlg::OnStnClickedStatic1)
	ON_BN_CLICKED(IDC_start, &CnandflashDlg::OnBnClickedstart)
	ON_BN_CLICKED(IDC_remove, &CnandflashDlg::OnBnClickedremove)
END_MESSAGE_MAP()


// CnandflashDlg 消息处理程序

BOOL CnandflashDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CnandflashDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_NANDFLASH_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_NANDFLASH_DIALOG));
	}
}
#endif




void CnandflashDlg::OnBnClickedstart()
{
	// TODO: 在此添加控件通知处理程序代码
	flagStart=1;
	//建立一个读线程
	hCommWatchThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)G_ReadThread,
		this,
		0,
		&dwTreadID);
	ASSERT(hCommWatchThread!=NULL);

}

void CnandflashDlg::OnBnClickedremove()
{
	// TODO: 在此添加控件通知处理程序代码
	flagRemove = 1;
	RemoveThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL,
		0,
		(LPTHREAD_START_ROUTINE)G_RemoveThread,
		this,
		0,
		&RemoveID);
	ASSERT(RemoveThread!=NULL);
}
