// Win32EGL.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32EGL.h"


#include "CELLWinApp.hpp"



int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);


	CELL::CELLWinApp  app(hInstance);
	app.main(800, 600);

	return 0;
}
