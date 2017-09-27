
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

- # eglInitialize函数
```
EGL may be initialized on a display by calling
EGLBoolean eglInitialize(EGLDisplay dpy, EGLint * major, EGLint * minor);

EGL_TRUE is returned on success, and major and minor are updated with the major and minor version numbers of 
the EGL implementation (for example, in an EGL 1.2 implementation, the values of *major and *minor would be 1 and 2, 
respectively). major and minor are not updated if they are specified as NULL.

EGL_FALSE is returned on failure and major and minor are not updated. 
An EGL_BAD_DISPLAY error is generated if the dpy argument does not refer to a valid EGLDisplay. 
An EGL_NOT_INITIALIZED error is generated if EGL cannot be initialized for an otherwise valid dpy.

Initializing an already-initialized display is allowed, but the only effect of such
a call is to return EGL_TRUE and update the EGL version numbers. An initialized
display may be used from other threads in the same address space without being
initialized again in those threads.

EGL可能调用EGLBoolean eglInitialize(EGLDisplay dpy, EGLint * major, EGLint * minor)初始化一个display;

成功返回EGL_TRUE，同时更新EGL实现的major和minor版本号（比如，EGL 1.2的实现，major和minor将会是 1 和 2），
如果他们被指定为NULL，major和minor将不会更新。

失败返回EGL_FALSE，同时major和minor将不会被更新。如果参数dpy是一个无效的EGLDisplay，将产生EGL_BAD_DISPLAY错误。
如果EGL不能初始化一个有效的dpy，将会产生EGL_NOT_INITIALIZED错误。

允许初始化一个已经初始化过的displa，但是效果只是返回EGL_TRUE，同时更新EGL版本号。一个初始化过的display可用于
其他线程，在相同的地址空间空间中不用被再次初始化。

```

- # eglChooseConfig函数   

```
An EGLConfig describes the format, type and size of the color buffers and ancillary buffers for an EGLSurface. 
If the EGLSurface is a window, then the EGLConfig describing it may have an associated native visual type.

Names of EGLConfig attributes are shown in Table 3.1. These names may be passed to eglChooseConfig to 
specify required attribute properties. 

EGL_CONFIG_ID is a unique integer identifying different EGLConfigs. 
Configuration IDs must be small positive integers starting at 1 and ID assignment
should be compact; that is, if there are N EGLConfigs defined by the EGL implementation, 
their configuration IDs should be in the range [1,N]. Small gaps in the sequence are allowed, 
but should only occur when removing configurations defined in previous revisions of an EGL implementation.

Buffer Descriptions and Attributes
The various buffers that may be contained by an EGLSurface, and the EGLConfig attributes controlling their creation, 
are described below. Attribute values include the depth of these buffers, expressed in bits/pixel component. 
If the depth of a buffer in an EGLConfig is zero, then an EGLSurface created with respect to that EGLConfig will 
not contain the corresponding buffer.

Not all buffers are used or required by all client APIs . To conserve resources, implementations may delay creation 
of buffers until they are needed by EGL or a client API . For example, if an EGLConfig describes an alpha mask buffer with
depth greater than zero, that buffer need not be allocated by a surface until an OpenVG context is bound to that surface.

The Color Buffer
The color buffer contains pixel color values, and is shared by all client APIs rendering to a surface.

EGL_COLOR_BUFFER_TYPE indicates the color buffer type, and must be either EGL_RGB_BUFFER for an RGB color buffer, 
or EGL_LUMINANCE_BUFFER for a luminance color buffer. For an RGB buffer, EGL_RED_SIZE , EGL_GREEN_SIZE ,
EGL_BLUE_SIZE must be non-zero, and EGL_LUMINANCE_SIZE must be zero. For a luminance buffer, EGL_RED_SIZE , EGL_GREEN_SIZE , EGL_BLUE_SIZE must be zero, and EGL_LUMINANCE_SIZE must be non-zero. For both RGB and luminance color buffers, 
EGL_ALPHA_SIZE may be zero or non-zero (the latter indicates the existence of a destination alpha buffer).

If OpenGL or OpenGL ES rendering is supported for a luminance color buffer(as described by the value of the 
EGL_RENDERABLE_TYPE attribute, described below), it is treated as RGB rendering with the value of GL_RED_BITS 
equal to EGL_LUMINANCE_SIZE and the values of GL_GREEN_BITS and GL_BLUE_BITS equal to zero. 
The red component of fragments is written to the luminance channel of the color buffer, the green and blue 
components are discarded, and the alpha component is written to the alpha channel of the color buffer (if present).

EGL_BUFFER_SIZE gives the total of the color component bits of the color buffer 4 For an RGB color buffer, the total is 
the sum of EGL_RED_SIZE , EGL_GREEN_SIZE , EGL_BLUE_SIZE , and EGL_ALPHA_SIZE . For a luminance color
buffer, the total is the sum of EGL_LUMINANCE_SIZE and EGL_ALPHA_SIZE. 

EGLConfig描述了EGLSurface的color buffers和辅助 buffers的格式、类型和大小。如果EGLSurface是一个window，
EGLConfig描述可能有一个关联的本地虚拟类型。

EGLConfig属性的名称如表3.1，这些名称可能传给eglChooseConfig去指定需要的属性。

EGL_CONFIG_ID是一个唯一的整数标识用来区分不同的EGLConfigs。Configuration IDs必须是一个从1开始的小正数，
ID分配应该紧凑；如果EGL的实现有N个EGLConfigs，configuration IDs应该在[1,N]之间。系列中小的间隙是允许的，
但是应该只在删除之前的配置定义时发生。
```
