
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
	, minAngle(0)
	, maxAngle(180)
	, stepAngle(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTomographyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICFIRST, pic_first);
	DDX_Control(pDX, IDC_SLIDER1, slid_angle);
	DDX_Control(pDX, IDC_PICPROJ, gr_proj);
	DDX_Control(pDX, IDC_PICSINOG, pic_sinogramma);
	DDX_Text(pDX, IDC_EDIT1, minAngle);
	DDX_Text(pDX, IDC_EDIT2, maxAngle);
	DDX_Text(pDX, IDC_EDIT3, stepAngle);
	DDX_Control(pDX, IDC_PICFIRST2, pic_restore);
}

BEGIN_MESSAGE_MAP(CTomographyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CTomographyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTomographyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTomographyDlg::OnBnClickedButton3)
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
	col = Gdiplus::Color::Blue;
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
	std::vector<double> proj;
	GetProjection(pic_first.GetMatr(), proj, pic_first.angle_rotate);
	gr_proj.SetParam(std::vector<std::vector<double>>({ proj }), true, std::vector<Gdiplus::Color>({ col }));
	pic_first.Invalidate(FALSE);
	gr_proj.Invalidate(FALSE);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CTomographyDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	CFileDialog change_image(TRUE);
	change_image.DoModal();
	auto path = change_image.GetPathName();
	pic_first.LoadImage_(path); //СДЕЛАТЬ ОБЛАСТЬ ВЫВОДА КРАТНЫМ СТЕПЕНИ ДВОЙКИ
	pic_first.Invalidate(FALSE);
}


void CTomographyDlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	sinog.Main(pic_first.GetMatr(), minAngle, maxAngle, stepAngle);
	pic_sinogramma.SetMatr(sinog.GetSinogramma(), 0, 0, 0, false);
	pic_sinogramma.Invalidate(FALSE);
}


void CTomographyDlg::OnBnClickedButton3()
{
	// TODO: добавьте свой код обработчика уведомлений
	res_restore.Main(sinog);
	pic_restore.SetMatr(res_restore.GetRes(), 0, 0, 0, false);
	pic_restore.Invalidate(FALSE);
}
