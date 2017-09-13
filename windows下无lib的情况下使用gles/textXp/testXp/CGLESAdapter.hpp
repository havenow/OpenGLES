#pragma  once
#include "egl/egl.h"

typedef void	(GL_APIENTRY* fun_glUseProgram) (GLuint program);
typedef int		(GL_APIENTRY* fun_glGetUniformLocation) (GLuint program, const GLchar* name);
typedef int		(GL_APIENTRY* fun_glGetAttribLocation) (GLuint program, const GLchar* name);
typedef void	(GL_APIENTRY* fun_glDeleteProgram) (GLuint program);
typedef void	(GL_APIENTRY* fun_glDeleteShader) (GLuint shader);
typedef void	(GL_APIENTRY* fun_glGetProgramInfoLog) (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void	(GL_APIENTRY* fun_glGetProgramiv) (GLuint program, GLenum pname, GLint* params);
typedef void	(GL_APIENTRY* fun_glLinkProgram) (GLuint program);
typedef void	(GL_APIENTRY* fun_glAttachShader) (GLuint program, GLuint shader);
typedef GLuint	(GL_APIENTRY* fun_glCreateProgram) (void);
typedef void	(GL_APIENTRY* fun_glGetShaderInfoLog) (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
typedef void	(GL_APIENTRY* fun_glGetShaderiv) (GLuint shader, GLenum pname, GLint* params);
typedef void	(GL_APIENTRY* fun_glCompileShader) (GLuint shader);
typedef void	(GL_APIENTRY* fun_glShaderSource) (GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
typedef GLuint	(GL_APIENTRY* fun_glCreateShader) (GLenum type);
typedef void	(GL_APIENTRY* fun_glEnableVertexAttribArray) (GLuint index);
typedef void	(GL_APIENTRY* fun_glDisableVertexAttribArray) (GLuint index);
typedef void	(GL_APIENTRY* fun_glTexImage2D) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
typedef void	(GL_APIENTRY* fun_glTexParameteri) (GLenum target, GLenum pname, GLint param);
typedef void	(GL_APIENTRY* fun_glBindTexture) (GLenum target, GLuint texture);
typedef void	(GL_APIENTRY* fun_glGenTextures) (GLsizei n, GLuint* textures);
typedef void	(GL_APIENTRY* fun_glDrawArrays) (GLenum mode, GLint first, GLsizei count);
typedef void	(GL_APIENTRY* fun_glVertexAttribPointer) (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
typedef void	(GL_APIENTRY* fun_glUniform1i) (GLint location, GLint x);
typedef void	(GL_APIENTRY* fun_glUniformMatrix4fv) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void	(GL_APIENTRY* fun_glViewport) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void	(GL_APIENTRY* fun_glClear) (GLbitfield mask);
typedef void	(GL_APIENTRY* fun_glUniform4f) (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

typedef EGLBoolean	(EGLAPIENTRY* fun_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean	(EGLAPIENTRY* fun_eglQuerySurface)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value);
typedef EGLBoolean	(EGLAPIENTRY* fun_eglMakeCurrent)(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLContext	(EGLAPIENTRY* fun_eglCreateContext)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
typedef EGLSurface	(EGLAPIENTRY* fun_eglCreateWindowSurface)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
typedef EGLBoolean	(EGLAPIENTRY* fun_eglGetConfigAttrib)(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);
typedef EGLBoolean	(EGLAPIENTRY* fun_eglChooseConfig)(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);
typedef	EGLBoolean	(EGLAPIENTRY* fun_eglInitialize)(EGLDisplay dpy, EGLint *major, EGLint *minor);
typedef EGLDisplay	(EGLAPIENTRY* fun_eglGetDisplay)(EGLNativeDisplayType display_id);
typedef	EGLBoolean	(EGLAPIENTRY* fun_eglTerminate)(EGLDisplay dpy);
typedef	EGLBoolean	(EGLAPIENTRY* fun_eglDestroySurface)(EGLDisplay dpy, EGLSurface surface);
typedef	EGLBoolean	(EGLAPIENTRY* fun_eglDestroyContext)(EGLDisplay dpy, EGLContext ctx);


class GLESAdapter
{
public:
	static GLESAdapter* Instance()
	{
		static GLESAdapter instance;
		return &instance;
	}

	void SetHinstance(	HINSTANCE hDll_EGL, HINSTANCE hDll_GLES)
	{
		m_hDll_EGL = hDll_EGL;
		m_hDll_GLES = hDll_GLES;
	}

	void	GL_APIENTRY call_glUseProgram(GLuint program)
	{
		fun_glUseProgram function =  (fun_glUseProgram)GetProcAddress(m_hDll_GLES, "glUseProgram");
		function(program);
	}
	int		GL_APIENTRY call_glGetUniformLocation(GLuint program, const GLchar* name)
	{
		fun_glGetUniformLocation function =  (fun_glGetUniformLocation)GetProcAddress(m_hDll_GLES, "glGetUniformLocation");
		return function(program, name);
	}
	int		GL_APIENTRY call_glGetAttribLocation(GLuint program, const GLchar* name)
	{
		fun_glGetAttribLocation function =  (fun_glGetAttribLocation)GetProcAddress(m_hDll_GLES, "glGetAttribLocation");
		return function(program, name);
	}
	void	GL_APIENTRY call_glDeleteProgram(GLuint program)
	{
		fun_glDeleteProgram function =  (fun_glDeleteProgram)GetProcAddress(m_hDll_GLES, "glDeleteProgram");
		function(program);
	}
	void	GL_APIENTRY call_glDeleteShader(GLuint shader)
	{
		fun_glDeleteShader function =  (fun_glDeleteShader)GetProcAddress(m_hDll_GLES, "glDeleteShader");
		function(shader);
	}
	void	GL_APIENTRY call_glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
	{
		fun_glGetProgramInfoLog function =  (fun_glGetProgramInfoLog)GetProcAddress(m_hDll_GLES, "glGetProgramInfoLog");
		function(program, bufsize, length, infolog);
	}
	void	GL_APIENTRY call_glGetProgramiv(GLuint program, GLenum pname, GLint* params)
	{
		fun_glGetProgramiv function =  (fun_glGetProgramiv)GetProcAddress(m_hDll_GLES, "glGetProgramiv");
		function(program, pname, params);
	}
	void	GL_APIENTRY call_glLinkProgram(GLuint program)
	{
		fun_glLinkProgram function =  (fun_glLinkProgram)GetProcAddress(m_hDll_GLES, "glLinkProgram");
		function(program);
	}
	void	GL_APIENTRY call_glAttachShader(GLuint program, GLuint shader)
	{
		fun_glAttachShader function =  (fun_glAttachShader)GetProcAddress(m_hDll_GLES, "glAttachShader");
		function(program, shader);
	}
	GLuint	GL_APIENTRY call_glCreateProgram(void)
	{
		fun_glCreateProgram function =  (fun_glCreateProgram)GetProcAddress(m_hDll_GLES, "glCreateProgram");
		return function();
	}
	void	GL_APIENTRY call_glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
	{
		fun_glGetShaderInfoLog function =  (fun_glGetShaderInfoLog)GetProcAddress(m_hDll_GLES, "glGetShaderInfoLog");
		function(shader, bufsize, length, infolog);
	}
	void	GL_APIENTRY call_glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
	{
		fun_glGetShaderiv function =  (fun_glGetShaderiv)GetProcAddress(m_hDll_GLES, "glGetShaderiv");
		function(shader, pname, params);
	}
	void	GL_APIENTRY call_glCompileShader(GLuint shader)
	{
		fun_glCompileShader function =  (fun_glCompileShader)GetProcAddress(m_hDll_GLES, "glCompileShader");
		function(shader);
	}
	void	GL_APIENTRY call_glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length)
	{
		fun_glShaderSource function =  (fun_glShaderSource)GetProcAddress(m_hDll_GLES, "glShaderSource");
		function(shader, count, string, length);
	}
	GLuint	GL_APIENTRY call_glCreateShader(GLenum type)
	{
		fun_glCreateShader function =  (fun_glCreateShader)GetProcAddress(m_hDll_GLES, "glCreateShader");
		return function(type);
	}
	void	GL_APIENTRY call_glEnableVertexAttribArray(GLuint index)
	{
		fun_glEnableVertexAttribArray function =  (fun_glEnableVertexAttribArray)GetProcAddress(m_hDll_GLES, "glEnableVertexAttribArray");
		function(index);
	}
	void	GL_APIENTRY call_glDisableVertexAttribArray(GLuint index)
	{
		fun_glDisableVertexAttribArray function =  (fun_glDisableVertexAttribArray)GetProcAddress(m_hDll_GLES, "glDisableVertexAttribArray");
		function(index);
	}
	void	GL_APIENTRY call_glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
	{
		fun_glTexImage2D function =  (fun_glTexImage2D)GetProcAddress(m_hDll_GLES, "glTexImage2D");
		function(target, level, internalformat, width, height, border, format, type, pixels);
	}
	void	GL_APIENTRY call_glTexParameteri(GLenum target, GLenum pname, GLint param)
	{
		fun_glTexParameteri function =  (fun_glTexParameteri)GetProcAddress(m_hDll_GLES, "glTexParameteri");
		function(target, pname, param);
	}
	void	GL_APIENTRY call_glBindTexture(GLenum target, GLuint texture)
	{
		fun_glBindTexture function =  (fun_glBindTexture)GetProcAddress(m_hDll_GLES, "glBindTexture");
		function(target, texture);
	}
	void	GL_APIENTRY call_glGenTextures(GLsizei n, GLuint* textures)
	{
		fun_glGenTextures function =  (fun_glGenTextures)GetProcAddress(m_hDll_GLES, "glGenTextures");
		function(n, textures);
	}
	void	GL_APIENTRY call_glDrawArrays(GLenum mode, GLint first, GLsizei count)
	{
		fun_glDrawArrays function =  (fun_glDrawArrays)GetProcAddress(m_hDll_GLES, "glDrawArrays");
		function(mode, first, count);
	}
	void	GL_APIENTRY call_glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
	{
		fun_glVertexAttribPointer function =  (fun_glVertexAttribPointer)GetProcAddress(m_hDll_GLES, "glVertexAttribPointer");
		function(indx, size, type, normalized, stride, ptr);
	}
	void	GL_APIENTRY call_glUniform1i(GLint location, GLint x)
	{
		fun_glUniform1i function =  (fun_glUniform1i)GetProcAddress(m_hDll_GLES, "glUniform1i");
		function(location, x);
	}
	void	GL_APIENTRY call_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		fun_glUniformMatrix4fv function =  (fun_glUniformMatrix4fv)GetProcAddress(m_hDll_GLES, "glUniformMatrix4fv");
		function(location, count, transpose, value);
	}
	void	GL_APIENTRY call_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		fun_glViewport function =  (fun_glViewport)GetProcAddress(m_hDll_GLES, "glViewport");
		function(x, y, width, height);
	}
	void	GL_APIENTRY call_glClear(GLbitfield mask)
	{
		fun_glClear function =  (fun_glClear)GetProcAddress(m_hDll_GLES, "glClear");
		function(mask);
	}

	void	GL_APIENTRY call_glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		fun_glUniform4f function =  (fun_glUniform4f)GetProcAddress(m_hDll_GLES, "glUniform4f");
		function(location, x, y, z, w);
	}

	EGLBoolean	EGLAPIENTRY call_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
	{
		fun_eglSwapBuffers function =  (fun_eglSwapBuffers)GetProcAddress(m_hDll_EGL, "eglSwapBuffers");
		return function(dpy, surface);
	}
	EGLBoolean	EGLAPIENTRY call_eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
	{
		fun_eglQuerySurface function =  (fun_eglQuerySurface)GetProcAddress(m_hDll_EGL, "eglQuerySurface");
		return function(dpy, surface, attribute, value);
	}
	EGLBoolean	EGLAPIENTRY call_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
	{
		fun_eglMakeCurrent function =  (fun_eglMakeCurrent)GetProcAddress(m_hDll_EGL, "eglMakeCurrent");
		return function(dpy, draw, read, ctx);
	}
	EGLContext	EGLAPIENTRY call_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
	{
		fun_eglCreateContext function =  (fun_eglCreateContext)GetProcAddress(m_hDll_EGL, "eglCreateContext");
		return function(dpy, config, share_context, attrib_list);
	}
	EGLSurface	EGLAPIENTRY call_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
	{
		fun_eglCreateWindowSurface function =  (fun_eglCreateWindowSurface)GetProcAddress(m_hDll_EGL, "eglCreateWindowSurface");
		return function(dpy, config, win, attrib_list);
	}
	EGLBoolean	EGLAPIENTRY call_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
	{
		fun_eglGetConfigAttrib function =  (fun_eglGetConfigAttrib)GetProcAddress(m_hDll_EGL, "eglGetConfigAttrib");
		return function(dpy, config, attribute, value);
	}
	EGLBoolean	EGLAPIENTRY call_eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
	{
		fun_eglChooseConfig function =  (fun_eglChooseConfig)GetProcAddress(m_hDll_EGL, "eglChooseConfig");
		return function(dpy, attrib_list, configs, config_size, num_config);
	}
	EGLBoolean	EGLAPIENTRY call_eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
	{
		fun_eglInitialize function =  (fun_eglInitialize)GetProcAddress(m_hDll_EGL, "eglInitialize");
		return function(dpy, major, minor);
	}
	EGLDisplay EGLAPIENTRY call_eglGetDisplay(EGLNativeDisplayType display_id)
	{
		fun_eglGetDisplay function =  (fun_eglGetDisplay)GetProcAddress(m_hDll_EGL, "eglGetDisplay");
		return function(display_id);
	}
	EGLBoolean	EGLAPIENTRY call_eglTerminate(EGLDisplay dpy)
	{
		fun_eglTerminate function =  (fun_eglTerminate)GetProcAddress(m_hDll_EGL, "eglTerminate");
		return function(dpy);
	}
	EGLBoolean	EGLAPIENTRY call_eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
	{
		fun_eglDestroySurface function =  (fun_eglDestroySurface)GetProcAddress(m_hDll_EGL, "eglDestroySurface");
		return function(dpy, surface);
	}
	EGLBoolean	EGLAPIENTRY call_eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
	{
		fun_eglDestroyContext function =  (fun_eglDestroyContext)GetProcAddress(m_hDll_EGL, "eglDestroyContext");
		return function(dpy, ctx);
	}



private:
	GLESAdapter(){};
	~GLESAdapter(){};
	GLESAdapter(const GLESAdapter&){};
	GLESAdapter& operator=(const GLESAdapter&){};

	HINSTANCE m_hDll_EGL;
	HINSTANCE m_hDll_GLES;
};