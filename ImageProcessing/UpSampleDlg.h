#pragma once


// CUpSampleDlg ��ȭ �����Դϴ�.

class CUpSampleDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpSampleDlg)

public:
	CUpSampleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUpSampleDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_UP_SAMPLE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_UpSampleRate;
};
