- # windows下无lib时调用OpenGLES2.0的接口

```c++

//1、加载dll  
	HINSTANCE hDll_EGL;
	HINSTANCE hDll_GLES;
	hDll_EGL=LoadLibrary(L"libEGL.dll");
	hDll_GLES=LoadLibrary(L"libGLESv2.dll");

//2、定义函数指针
typedef void	(GL_APIENTRY* fun_glUseProgram) (GLuint program);


//3、定义函数实现
	void	GL_APIENTRY call_glUseProgram(GLuint program)
	{
		fun_glUseProgram function =  (fun_glUseProgram)GetProcAddress(m_hDll_GLES, "glUseProgram");
		function(program);
	}
  
//4、调用封装的函数  
  调用 call_glUseProgram()函数即可
```
