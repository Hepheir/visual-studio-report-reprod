// DownSampleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DownSampleDlg.h"
#include "afxdialogex.h"


// CDownSampleDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDownSampleDlg, CDialog)

CDownSampleDlg::CDownSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ID_DOWN_SAMPLE_DLG, pParent)
	, m_DownSampleRate(0)
{

}

CDownSampleDlg::~CDownSampleDlg()
{
}

void CDownSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_DOWN_SAMPLE_EDIT, m_DownSampleRate);
	DDV_MinMaxInt(pDX, m_DownSampleRate, 1, 32);
}


BEGIN_MESSAGE_MAP(CDownSampleDlg, CDialog)
	ON_EN_CHANGE(ID_DOWN_SAMPLE_EDIT, &CDownSampleDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDownSampleDlg 메시지 처리기입니다.


void CDownSampleDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
