
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "DownSampleDlg.h"
#include "UpSampleDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
	: m_width(0)
	, m_height(0)
	, m_InputImage(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

	m_Re_width = 0;
	m_Re_height = 0;
	m_Re_size = 0;
}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName)) {
		return FALSE;
	}

	CFile File;

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	switch (File.GetLength())
	{
	case 256 * 256:
		m_height = 256;
		m_width = 256;
		break;

	case 512 * 512:
		m_height = 512;
		m_width = 512;
		break;

	case 640 * 480:
		m_height = 480;
		m_width = 640;
		break;

	default:
		AfxMessageBox("Not Supported Image Size");
		return FALSE;
	}

	m_size = m_height * m_width;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i < m_size; i++) {
		m_InputImage[i] = 255;
	}

	File.Read(m_InputImage, m_size);
	File.Close();

	return TRUE;
}


BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File;
	CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		File.Write(m_InputImage, m_size);
		File.Close();
	}

	return TRUE;
}


void CImageProcessingDoc::OnDownSampling()
{
	int y, x;
	CDownSampleDlg dlg;

	if (dlg.DoModal() == IDOK) {
		m_Re_height = m_height / dlg.m_DownSampleRate;
		m_Re_width = m_width / dlg.m_DownSampleRate;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		for (y = 0; y < m_Re_height; y++) {
			for (x = 0; x < m_Re_width; x++) {
				m_OutputImage[y*m_Re_width + x] = m_InputImage[(y*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*x];
			}
		}
	}
}


void CImageProcessingDoc::OnUpSampling()
{
	int i;
	int x, y;
	CUpSampleDlg dlg;

	if (dlg.DoModal() != IDOK) {
		return;
	}

	m_Re_height = m_height * dlg.m_UpSampleRate;
	m_Re_width = m_width * dlg.m_UpSampleRate;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_Re_size; i++) {
		m_OutputImage[i] = 0;
	}

	for (y = 0; y < m_height; y++) {
		for (x = 0; x < m_width; x++) {
			m_OutputImage[(y * m_Re_width + x) * dlg.m_UpSampleRate] = m_InputImage[y * m_width + x];
		}
	}
}
