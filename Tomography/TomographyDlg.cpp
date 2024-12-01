﻿
// TomographyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Tomography.h"
#include "TomographyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CTomographyDlg



CTomographyDlg::CTomographyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOMOGRAPHY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTomographyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICFIRST, pic_first);
	DDX_Control(pDX, IDC_SLIDER1, slid_angle);
}

BEGIN_MESSAGE_MAP(CTomographyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CTomographyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CTomographyDlg

BOOL CTomographyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	slid_angle.SetRange(0, 179);
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTomographyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTomographyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTomographyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	pic_first.angle_rotate = slid_angle.GetPos();
	pic_first.Invalidate(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CTomographyDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CFileDialog change_image(TRUE);
	change_image.DoModal();
	auto path = change_image.GetPathName();
	pic_first.LoadImage_(path);
	pic_first.Invalidate(FALSE);
}
