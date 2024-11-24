
// Tomography.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTomographyApp:
// Сведения о реализации этого класса: Tomography.cpp
//

class CTomographyApp : public CWinApp
{
public:
	CTomographyApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CTomographyApp theApp;
