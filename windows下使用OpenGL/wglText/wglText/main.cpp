#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "glew/glew.h"
#include "GLContext.h"
#include "Thread.hpp"
#include "Timestamp.hpp"
#include "CELLShader.hpp"
#include "CELLMath.hpp"
#include "freeImage/FreeImage.h"

#define WM_UPDATE_VIDEO WM_USER + 100
bool g_flag = 0;

#ifndef _TAG_LOADINGBUFFER
#define _TAG_LOADINGBUFFER
typedef struct _tagLoadingBuffer
{
	char	pData[1024 * 1024 * 2];
	int		nWidth;
	int		nHeight;
}LoadingBuffer;
#endif

LoadingBuffer m_LoadingBuffer[3];

static void    loadImgBuffer(const char* fileName, void* pPixelBuffer, int& width, int& height)
{
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
	FIBITMAP    *dib = FreeImage_Load(fifmt, fileName, 0);
	FreeImage_FlipVertical(dib);//旋转
	dib = FreeImage_ConvertTo16Bits565(dib);
	//dib = FreeImage_ConvertTo24Bits(dib);
	BYTE    *pixels = (BYTE*)FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	memcpy(pPixelBuffer, pixels, width*height * 2);

	FreeImage_Unload(dib);
}

void  getResourcePath(HINSTANCE hInstance,char pPath[1024])
{
    char    szPathName[1024];
    char    szDriver[64];
    char    szPath[1024];
    GetModuleFileNameA(hInstance,szPathName,sizeof(szPathName));
    _splitpath( szPathName, szDriver, szPath, 0, 0 );
    sprintf(pPath,"%s%s",szDriver,szPath);
}

class   DecodeThread :public Thread
{
public:
	HWND            _hWnd;
	bool            _exitFlag;
	Timestamp       _timestamp;
	GLContext       _glContext;
	unsigned        _textureId;
	PROGRAM_P2_UV2  _shaderTex;
	int LoadIndex;
public:
	DecodeThread()
	{
		_exitFlag = false;
		_hWnd = 0;
	}

	virtual void    setup(HWND hwnd)
	{
		LoadIndex = 0;
		_hWnd = hwnd;
		_glContext.setup(hwnd, GetDC(hwnd));
		glewInit();
		glEnable(GL_TEXTURE_2D);
		_textureId = createTexture(m_LoadingBuffer[0].nWidth, m_LoadingBuffer[0].nHeight);
		_shaderTex.initialize();
	}
	/**
	*   加载文件
	*/
	virtual void    load(const char* fileName)
	{

	}

	virtual void    shutdown()
	{
		_exitFlag = true;
		Thread::join();
		_glContext.shutdown();
	}

	/**
	*   线程执行函数
	*/
	virtual bool    run()
	{
		_timestamp.update();
		while (!_exitFlag)
		{
			//! 这里需要通知窗口进行重绘制更新，显示更新数据
			//InvalidateRect(_hWnd, 0, 0);
			PostMessage(_hWnd, WM_UPDATE_VIDEO, 0, 0);

			double      elsped = _timestamp.getElapsedTimeInMilliSec();
			double      sleeps = 100;// (tims - elsped);
			g_flag = !g_flag;
			if (sleeps > 1)
			{
				Sleep((DWORD)sleeps);
			}
		}

		return  true;
	}

	void    updateTexture()
	{
		glBindTexture(GL_TEXTURE_2D, _textureId);
		if (LoadIndex == 3) LoadIndex = 0;
		LoadingBuffer* pLoadBuffer = &(m_LoadingBuffer[LoadIndex]);
		LoadIndex++;
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pLoadBuffer->nWidth, pLoadBuffer->nHeight, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, pLoadBuffer->pData);
	}


	void    render()
	{
		struct  Vertex
		{
			float   x, y;
			float   u, v;
		};

		RECT    rt;
		GetClientRect(_hWnd, &rt);
		int     w = rt.right - rt.left;
		int     h = rt.bottom - rt.top;
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 0, 0, 1);

		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, w, h, 0, -100, 100);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glBindTexture(GL_TEXTURE_2D, _textureId);

		Vertex  vertexs[] =
		{
			{ 0,  0,  0,  0 },
			{ 0,  h,  0,  1 },
			{ w,  0,  1,  0 },

			{ 0,  h,  0,  1 },
			{ w,  0,  1,  0 },
			{ w,  h,  1,  1 },
		};

		CELL::matrix4   matMVP = CELL::ortho<float>(0, w, h, 0, -100, 100);
		_shaderTex.begin();
		glUniformMatrix4fv(_shaderTex._MVP, 1, GL_FALSE, matMVP.data());

		glUniform1i(_shaderTex._texture, 0);
		{
			glVertexAttribPointer(_shaderTex._position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertexs[0].x);
			glVertexAttribPointer(_shaderTex._uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertexs[0].u);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		_shaderTex.end();

		_glContext.swapBuffer();
	}

protected:

	unsigned    createTexture(int w, int h)
	{
		unsigned    texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);

		return  texId;
	}
};

DecodeThread    g_decode;

LRESULT CALLBACK    windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
	case WM_UPDATE_VIDEO:
	{
		g_decode.updateTexture();
		g_decode.render();
	}
	break;
 //   case WM_PAINT:
	//{
	//	g_decode.render();
	//}
        break;
    case WM_SIZE:
        break;
    case WM_CLOSE:
    case WM_DESTROY:
		g_decode.shutdown();
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return  DefWindowProc( hWnd, msg, wParam, lParam );
}

int     WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    //  1   注册窗口类
    ::WNDCLASSEXA winClass;
    winClass.lpszClassName  =   "wgl-gl";
    winClass.cbSize         =   sizeof(::WNDCLASSEX);
    winClass.style          =   CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    winClass.lpfnWndProc    =   windowProc;
    winClass.hInstance      =   hInstance;
    winClass.hIcon	        =   0;
    winClass.hIconSm	    =   0;
    winClass.hCursor        =   LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground  =   (HBRUSH)(WHITE_BRUSH);
    winClass.lpszMenuName   =   NULL;
    winClass.cbClsExtra     =   0;
    winClass.cbWndExtra     =   0;
    RegisterClassExA(&winClass);

    //  2 创建窗口
    HWND    hWnd   =   CreateWindowExA(
        NULL,
        "wgl-gl",
        "wgl-gl",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        0,
        0,
        800,
        600, 
        0, 
        0,
        hInstance, 
        0
        );

    UpdateWindow( hWnd );
    ShowWindow(hWnd,SW_SHOW);

    char    szPath[1024];
    char    szPathName[1024];

	{
		char strLoadImg[512];
		getResourcePath(hInstance, szPath);
		for (int i = 0; i < 3; i++)
		{
			sprintf(strLoadImg, "%sloading%d.png", szPath, i);
			LoadingBuffer* pBuffer = nullptr;
			pBuffer = &m_LoadingBuffer[i];
			loadImgBuffer(strLoadImg, pBuffer->pData, pBuffer->nWidth, pBuffer->nHeight);
			printf("loading--- %s %d %d\n", strLoadImg, pBuffer->nWidth, pBuffer->nHeight);
		}
	}

	g_decode.setup(hWnd);
	g_decode.start();

    MSG     msg =   {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    

	g_decode.shutdown();
    return  0;
}