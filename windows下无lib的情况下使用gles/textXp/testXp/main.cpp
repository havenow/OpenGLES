#include "stdafx.h"
#include "CELLWinApp.hpp"
#include "CGLESAdapter.hpp"


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

	HINSTANCE hDll_EGL;
	HINSTANCE hDll_GLES;
	hDll_EGL=LoadLibrary(L"libEGL.dll");
	hDll_GLES=LoadLibrary(L"libGLESv2.dll");
	//fun1 f1 =  (fun1)GetProcAddress(hdll, "eglGetDisplay");
	//EGLDisplay  _display = f1(EGL_DEFAULT_DISPLAY);
	GLESAdapter::Instance()->SetHinstance(hDll_EGL, hDll_GLES);
	 
    CELL::CELLWinApp  app(hInstance);
    app.main(800,600);

    return 0;
}

//class a
//{
//public:
//	EGLDisplay EGLAPIENTRY fun1(EGLNativeDisplayType display_id)
//	{
//		fun1 f1 =  (fun1)GetProcAddress(hdll, "eglGetDisplay");
//		return f1(display_id);
//
//	}
//
//};