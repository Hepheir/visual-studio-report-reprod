// UpSampleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "UpSampleDlg.h"
#include "afxdialogex.h"


// CUpSampleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUpSampleDlg, CDialog)

CUpSampleDlg::CUpSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ID_UP_SAMPLE_DLG, pParent)
	, m_UpSampleRate(0)
{

}

CUpSampleDlg::~CUpSampleDlg()
{
}

void CUpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_UP_SAMPLE_EDIT, m_UpSampleRate);
}


BEGIN_MESSAGE_MAP(CUpSampleDlg, CDialog)
END_MESSAGE_MAP()


// CUpSampleDlg 메시지 처리기입니다.
