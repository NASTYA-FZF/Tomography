
// TomographyDlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include "Model.h"
#include "MyGraph.h"

// Диалоговое окно CTomographyDlg
class CTomographyDlg : public CDialogEx
{
// Создание
public:
	CTomographyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOMOGRAPHY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Drawer pic_first;
	CSliderCtrl slid_angle;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton1();
	MyGraph gr_proj;
	Gdiplus::Color col;
	Drawer pic_sinogramma;
	double minAngle;
	double maxAngle;
	double stepAngle;
	sinogramma sinog;
	afx_msg void OnBnClickedButton2();
	Drawer pic_restore;
	afx_msg void OnBnClickedButton3();
	restore res_restore;
};
