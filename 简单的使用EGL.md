
```c++
  // for gles2.0
	EGLConfig   _config;
	EGLSurface  _surface;
	EGLContext  _context;
	EGLDisplay  _display;
  
  	//! 窗口句柄
	HWND        _hWnd;
	//! 窗口的高度
	int         _width;
	//! 窗口的宽度
	int         _height;
  
  
  
    /**
	*   初始化 OpenGLES2.0
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
		_display	    =	eglGetDisplay(EGL_DEFAULT_DISPLAY);

		//! 2init
		eglInitialize(_display, &major, &minor);

		//! 3
		eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);

		eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);
		//! 4 
		_surface	    = 	eglCreateWindowSurface(_display, _config, _hWnd, NULL);

		//! 5
		EGLint attr[]   =   { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
		_context 	    = 	eglCreateContext(_display, _config, 0, attr);
		//! 6
		if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
		{
			return false;
		}

		eglQuerySurface(_display, _surface, EGL_WIDTH,  &_width);
		eglQuerySurface(_display, _surface, EGL_HEIGHT, &_height);

		return  true;

	}
  
  
  
	/**
	*   销毁OpenGLES2.0
	*/
	void    destroyOpenGLES20()
	{
		if (_display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if (_context != EGL_NO_CONTEXT) 
			{
				eglDestroyContext(_display, _context);
			}
			if (_surface != EGL_NO_SURFACE) 
			{
				eglDestroySurface(_display, _surface);
			}
			eglTerminate(_display);
		}
		_display    =   EGL_NO_DISPLAY;
		_context    =   EGL_NO_CONTEXT;
		_surface    =   EGL_NO_SURFACE;
	}
```

- # eglGetDisplay函数
```
A display can be obtained by calling
EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id);

The type and format of display_id are implementation-specific, 
and it describes a specific display provided by the system EGL is running on. 
For example, an EGL implementation under X windows could define display_id to be an X Display,
while an implementation under Microsoft Windows could define display_id to be a Windows Device Context. 
If display id is EGL_DEFAULT_DISPLAY , a default display is returned. 
Multiple calls made to eglGetDisplay with the same display_id will all return the same EGLDisplay handle.

If no display matching display_id is available, EGL_NO_DISPLAY is returned; no error condition is raised in this case.

调用函数EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id);可以获取一个display;

display_id的类型和格式取决于具体实现，描述了EGL系统提上运行的特定display。
比如，X windows的EGL实现定义display_id是一个X Display，微软的Windows实现定义display_id是一个Windows设备上下文。
如果display是EGL_DEFAULT_DISPLAY，会返回一个默认的dispaly.
使用相同的display_id多次调用eglGetDisplay将会返回相同的EGLDisplay句柄。

如果没有匹配display_id的display，将返回EGL_NO_DISPLAY；这种情况下不会报错。
```
