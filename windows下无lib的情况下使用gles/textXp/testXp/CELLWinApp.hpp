#pragma once

#include <Windows.h>
#include <tchar.h>
#include <math.h>

#include <EGL/egl.h>
#include <gles2/gl2.h>

#include "freeImage/FreeImage.h"

#include "CELLMath.hpp"
#include "CELLShader.hpp"
#include "CGLESAdapter.hpp"

void  getResourcePath(HINSTANCE hInstance, char pPath[1024])
{
	char    szPathName[1024];
	char    szDriver[64];
	char    szPath[1024];
	GetModuleFileNameA(hInstance, szPathName, sizeof(szPathName));
	_splitpath(szPathName, szDriver, szPath, 0, 0);
	sprintf(pPath, "%s%s", szDriver, szPath);
}

namespace   CELL
{
    class   CELLWinApp
    {
    public:
        //! ʵ�����
        HINSTANCE   _hInstance;
        //! ���ھ��
        HWND        _hWnd;
        //! ���ڵĸ߶�
        int         _width;
        //! ���ڵĿ��
        int         _height;
        /// for gles2.0
        EGLConfig   _config;
        EGLSurface  _surface;
        EGLContext  _context;
        EGLDisplay  _display;
        //! ����shader
        PROGRAM_P2_UV_AC4  _shader;
		//PROGRAM_P2_C4 _shader;
        unsigned        _textureId;
    public:
        CELLWinApp(HINSTANCE hInstance)
            :_hInstance(hInstance)
        {
            WNDCLASSEX  winClass;
            winClass.lpszClassName  =   _T("CELLWinApp");
            winClass.cbSize         =   sizeof(winClass);
            winClass.style          =   CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
            winClass.lpfnWndProc    =   wndProc;
            winClass.hInstance      =   hInstance;
            winClass.hIcon	        =   0;
            winClass.hIconSm	    =   0;
            winClass.hCursor        =   LoadCursor(hInstance, IDC_ARROW);
            winClass.hbrBackground  =   (HBRUSH)GetStockObject(BLACK_BRUSH);
            winClass.lpszMenuName   =   NULL;
            winClass.cbClsExtra     =   0;
            winClass.cbWndExtra     =   0;
            RegisterClassEx(&winClass);

            _textureId              =   0;
        }
        virtual ~CELLWinApp()
        {
            UnregisterClass(_T("CELLWinApp"),_hInstance);
        }

        /**
        *   ��ʼ�� OpenGLES2.0
        */
        bool    initOpenGLES20()
        {
            const EGLint attribs[] =
            {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_DEPTH_SIZE,24,
                EGL_NONE
            };
            EGLint 	format(0);
            EGLint	numConfigs(0);
            EGLint  major;
            EGLint  minor;

            //! 1
            _display	    =	 GLESAdapter::Instance()->call_eglGetDisplay(EGL_DEFAULT_DISPLAY);

            //! 2init
             GLESAdapter::Instance()->call_eglInitialize(_display, &major, &minor);

            //! 3
             GLESAdapter::Instance()->call_eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);

             GLESAdapter::Instance()->call_eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);
            //! 4 
            _surface	    = 	 GLESAdapter::Instance()->call_eglCreateWindowSurface(_display, _config, _hWnd, NULL);

            //! 5
            EGLint attr[]   =   { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
            _context 	    = 	 GLESAdapter::Instance()->call_eglCreateContext(_display, _config, 0, attr);
            //! 6
            if ( GLESAdapter::Instance()->call_eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
            {
                return false;
            }

             GLESAdapter::Instance()->call_eglQuerySurface(_display, _surface, EGL_WIDTH,  &_width);
             GLESAdapter::Instance()->call_eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

            return  true;

        }
        /**
        *   ����OpenGLES2.0
        */
        void    destroyOpenGLES20()
        {
            if (_display != EGL_NO_DISPLAY)
            {
                 GLESAdapter::Instance()->call_eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                if (_context != EGL_NO_CONTEXT) 
                {
                     GLESAdapter::Instance()->call_eglDestroyContext(_display, _context);
                }
                if (_surface != EGL_NO_SURFACE) 
                {
                     GLESAdapter::Instance()->call_eglDestroySurface(_display, _surface);
                }
                 GLESAdapter::Instance()->call_eglTerminate(_display);
            }
            _display    =   EGL_NO_DISPLAY;
            _context    =   EGL_NO_CONTEXT;
            _surface    =   EGL_NO_SURFACE;
        }

        virtual unsigned    loadTexture(const char* fileName)
        {
            unsigned    textureId   =   0;
            //1 ��ȡͼƬ��ʽ
            FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);

            //2 ����ͼƬ
            FIBITMAP    *dib = FreeImage_Load(fifmt, fileName,0);

            //3 ת��Ϊrgb 24ɫ
            dib     =   FreeImage_ConvertTo24Bits(dib);

            

            //4 ��ȡ����ָ��
            BYTE    *pixels =   (BYTE*)FreeImage_GetBits(dib);

            int     width   =   FreeImage_GetWidth(dib);
            int     height  =   FreeImage_GetHeight(dib);

            for (size_t i = 0 ;i < width * height * 3 ; i+=3 )
            {
                BYTE temp       =   pixels[i];
                pixels[i]       =   pixels[i + 2];
                pixels[i + 2]   =   temp;
            }

            /**
            *   ����һ������Id,������Ϊ��������������Ĳ����������������id
            */
             GLESAdapter::Instance()->call_glGenTextures( 1, &textureId );

            /**
            *   ʹ���������id,���߽а�(����)
            */
             GLESAdapter::Instance()->call_glBindTexture( GL_TEXTURE_2D, textureId );
            /**
            *   ָ������ķŴ�,��С�˲���ʹ�����Է�ʽ������ͼƬ�Ŵ��ʱ���ֵ��ʽ 
            */
            GLESAdapter::Instance()->call_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            
             GLESAdapter::Instance()->call_glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            /**
            *   ��ͼƬ��rgb�����ϴ���opengl.
            */
             GLESAdapter::Instance()->call_glTexImage2D( 
                GL_TEXTURE_2D,      //! ָ���Ƕ�άͼƬ
                0,                  //! ָ��Ϊ��һ�������������mipmap,��lod,����ľͲ��ü����ģ�Զ��ʹ�ý�С������
                GL_RGB,             //! �����ʹ�õĴ洢��ʽ
                width,              //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
                height,             //! ��ȣ���һ����Կ�����֧�ֲ��������������Ⱥ͸߶Ȳ���2^n��
                0,                  //! �Ƿ�ı�
                GL_RGB,             //! ���ݵĸ�ʽ��bmp�У�windows,����ϵͳ�д洢��������bgr��ʽ
                GL_UNSIGNED_BYTE,   //! ������8bit����
                pixels
                );
            /**
            *   �ͷ��ڴ�
            */
            FreeImage_Unload(dib);

            return  textureId;
        }



    protected:
        static  LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            
            CELLWinApp*  pThis   =   (CELLWinApp*)GetWindowLong(hWnd,GWL_USERDATA);
            if (pThis)
            {
                return  pThis->onEvent(hWnd,msg,wParam,lParam);
            }
            if (WM_CREATE == msg)
            {
                CREATESTRUCT*   pCreate =   (CREATESTRUCT*)lParam;
                SetWindowLong(hWnd,GWL_USERDATA,(DWORD_PTR)pCreate->lpCreateParams);
            }
            return  DefWindowProc( hWnd, msg, wParam, lParam );
        }
    public:
        /**
        *   �¼�����
        */
        virtual LRESULT onEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            switch (msg)
            {
            case WM_CLOSE:
            case WM_DESTROY:
                {
                    ::PostQuitMessage(0);
                }
                break;
            case WM_MOUSEMOVE:
                break;
            default:
                return  DefWindowProc( hWnd, msg, wParam, lParam ); 
            }
            return  S_OK;
            
        }

        virtual void    render()
        {

            struct  Vertex
            {
                CELL::float2    pos;
                CELL::float2    uv;
                CELL::Rgba4Byte color;
            };
            //! ��ջ�����
             GLESAdapter::Instance()->call_glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            //! �ӿڣ���Windows����ָ����λ�úʹ�С�ϻ���OpenGL����
             GLESAdapter::Instance()->call_glViewport(0,0,_width,_height);

            //! ����һ��ͶӰ����

            CELL::matrix4   screenProj  =   CELL::ortho<float>(0,float(_width),float(_height),0,-100.0f,100);
            _shader.begin();
            {
                float   x   =   100;
                float   y   =   100;
                float   w   =   400;
                float   h   =   400;
                Vertex  vertex[]   =   
                {
                    CELL::float2(x,y),          CELL::float2(0,0),      CELL::Rgba4Byte(255,255,255,255),
                    CELL::float2(x + w,y),      CELL::float2(1,0),      CELL::Rgba4Byte(255,255,255,255),
                    CELL::float2(x,y + h),      CELL::float2(0,1),      CELL::Rgba4Byte(255,255,255,255),
                    CELL::float2(x + w, y + h), CELL::float2(1,1),      CELL::Rgba4Byte(255,255,255,255),
                };

                CELL::matrix4       matMVP  =   screenProj;

                 GLESAdapter::Instance()->call_glBindTexture(GL_TEXTURE_2D,_textureId);

                 GLESAdapter::Instance()->call_glUniformMatrix4fv(_shader._MVP, 1, false, matMVP.data());
                 GLESAdapter::Instance()->call_glUniform1i(_shader._texture, 0);
                 GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._position,2,  GL_FLOAT,         false,  sizeof(Vertex),vertex);
                 GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._uv,2,        GL_FLOAT,         false,  sizeof(Vertex),&vertex[0].uv);
                 GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._color,   4,  GL_UNSIGNED_BYTE, true,   sizeof(Vertex),&vertex[0].color);
                 GLESAdapter::Instance()->call_glDrawArrays(GL_TRIANGLE_STRIP,0,4);

#if 0


                Vertex  circle[362];
                float   xCenter =   200;
                float   yCenter =   200;
                float   radius  =   200;

                circle[0].pos   =   CELL::float2(xCenter,yCenter);
                circle[0].color =   CELL::Rgba4Byte(255,0,0);
                for (size_t i= 0 ;i <= 360 ; ++ i )
                {
                    float   x   =   xCenter + radius * cos(float(i) * PI/180.0f);
                    float   y   =   yCenter + radius * sin(float(i) * PI/180.0f);
                    circle[i + 1].pos   =   CELL::float2(x,y);
                }

                 GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._position,2,GL_FLOAT,         false,  sizeof(Vertex),circle);
                 GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._color,   4,GL_UNSIGNED_BYTE, true,   sizeof(Vertex),&circle[0].color);
                 GLESAdapter::Instance()->call_glDrawArrays(GL_TRIANGLE_FAN,0,362);
#endif
            }
            _shader.end();

        }

		//virtual void    render()
		//{
		//	//! ��ջ�����
		//	GLESAdapter::Instance()->call_glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//	//! �ӿڣ���Windows����ָ����λ�úʹ�С�ϻ���OpenGL����
		//	GLESAdapter::Instance()->call_glViewport(0,0,_width,_height);

		//	//! ����һ��ͶӰ����

		//	CELL::matrix4   screenProj  =   CELL::ortho<float>(0,float(_width),float(_height),0,-100.0f,100);
		//	_shader.begin();
		//	{
		//		float   x   =   100;
		//		float   y   =   100;
		//		float   w   =   100;
		//		float   h   =   100;
		//		CELL::float2  pos[]   =   
		//		{
		//			CELL::float2(x,y),
		//			CELL::float2(x + w,y),
		//			CELL::float2(y,y + h),
		//			CELL::float2(x + w, y + h),
		//		};
		//		GLESAdapter::Instance()->call_glUniformMatrix4fv(_shader._MVP, 1, false, screenProj.data());
		//		GLESAdapter::Instance()->call_glUniform4f(_shader._color,1,0,0,1);
		//		GLESAdapter::Instance()->call_glVertexAttribPointer(_shader._position,2,GL_FLOAT,false,sizeof(CELL::float2),pos);
		//		GLESAdapter::Instance()->call_glDrawArrays(GL_TRIANGLE_STRIP,0,4);
		//	}
		//	_shader.end();

		//}
        /**
        *   ������
        */
        int     main(int width,int height)
        {
            _hWnd   =   CreateWindowEx( NULL,
                                        _T("CELLWinApp"),
                                        _T("CELLWinApp"),
                                        WS_OVERLAPPEDWINDOW,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        width,
                                        height, 
                                        NULL, 
                                        NULL,
                                        _hInstance, 
                                        this
                                        );

            if (_hWnd == 0)
            {
                return  -1;
            }
            UpdateWindow(_hWnd);

            ShowWindow(_hWnd,SW_SHOW);

            if (!initOpenGLES20())
            {
                return  false;
            }
            _shader.initialize();


			char    szPath[1024];
			char    szPathName[1024];

			char strLoadImg[512];
			getResourcePath(_hInstance, szPath);
			sprintf(strLoadImg, "%smain.jpg", szPath);

            _textureId =   loadTexture(strLoadImg);
            MSG msg =   {0};
            while(msg.message != WM_QUIT)
            {
                if (msg.message == WM_DESTROY || 
                    msg.message == WM_CLOSE)
                {
                    break;
                }
                /**
                *   ����Ϣ��������Ϣ������Ϣ���������Ⱦ����
                */
                if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
                { 
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                {
                    render();
                     GLESAdapter::Instance()->call_eglSwapBuffers(_display,_surface);
                }
            }
            /**
            *   ����OpenGLES20
            */
            destroyOpenGLES20();

            return  0;
        }
    };
}
