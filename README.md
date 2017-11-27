# OpenGLES2.0在windows平台的实现

接口是OpenGLES的，真正的实现是d3d    
windows平台最后调用的是：    
xp:   d3dcompiler_43.dll    
win7: d3dcompiler_46.dll/d3dcompiler_47.dll

- # Version 1.0
```
EGL version 1.0, approved on July 23, 2003, is the original version of EGL. EGL
was loosely based on GLX 1.3, generalized to be implementable on many different 
operating systems and window systems and simplified to reflect the needs of
embedded devices running OpenGL ES .
```

- # Version 1.1
```
EGL version 1.1, approved on August 5, 2004, is the second release of EGL. It
adds power management and swap control functionality based on vendor extensions 
from Imagination Technologies, and optional render-to-texture functionality
based on the WGL_ARB_render_texture extension defined by the OpenGL
ARB for desktop OpenGL.
B.1 Revision 1.1.2
EGL version 1.1.2 (revision 2 of EGL 1.1), approved on November 10, 2004, clarified 
that vertex buffer objects are shared among contexts in the same fashion as
texture objects
```

- # Version 1.2
```
EGL version 1.2, approved on July 8, 2005, is the third release of EGL. It adds
support for the OpenVG 2D client API, in addition to support for OpenGL ES, and
generalizes EGL concepts to enable supporting other client APIs in the future.
```

- # Version 1.3
```
EGL version 1.3 was voted out of the OpenKODE Working Group on December
4, 2006, and formally approval by the Khronos Board of Promoters on February 8,
2007. EGL 1.3 is the fourth release of EGL.
```

- # Version 1.4
```
EGL version 1.4 was voted out of the Khronos Technical Working Group on March
25, 2008, and formally approved by the Khronos Board of Promoters on May 29,
2008.
```

- # Version 1.5
```
EGL version 1.5 was voted out of the Khronos Technical Working Group on January 31, 2014, 
and formally approved by the Khronos Board of Promoters on
March 14, 2014.
```

- # 老显卡，opengl es2.0 映射非2^n宽高的纹理  
部分xp win7系统用户游戏没有画面，后来发现是显卡太老，不支持不规则纹理     
解决方案：    
在绑定纹理后，添加下面四行代码  
```c++
		unsigned    textureId   =   0;
		glGenTextures( 1, &textureId );
		glBindTexture( GL_TEXTURE_2D, textureId );
    
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//用边缘的像素填充
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
```

- # vs2015 Community  
vs2015社区版，功能全但是不能是商业用途。  
URL:   
https://www.visualstudio.com/downloads/download-visual-studio-vs  

Visual Studio 2015 Community ISO 文件实际的下载地址为：  
http://download.microsoft.com/download/0/B/C/0BC321A4-013F-479C-84E6-4A2F90B11269/vs2015.com_enu.iso  

新建项目（控制台应用程序）时，新建空项目，就不会生成一些和windows平台相关的代码，更利于跨平台的开发。

- # pdb文件  
PDB文件是“程序数据库”Program Data Base的简称，包含的程序的代码信息    
通过这个文件我们可以查看对应断点的位置，堆栈信息等内容     
使用PDB使得我们无需代码也可以掌握程序的堆栈运行状态。   
通常当我们编译代码后会自动生成一个PDB文件。     
在VS的工程属性面板中选择“链接器”-》“调试”，则可以设置是否对pdb进行输出，并指定pdb的输出路径。    

- # dump文件  
dump文件是附加堆栈信息的存储文件的简称，文件扩展名是”.dmp”，通过dump文件我们可以得到程序运行某一时刻的堆栈数据。  
当我们程序意外崩溃后，通常程序会立即中断运行，此时我们生成这一时刻的dump文件就可以通过此时的堆栈进行分析，找到崩溃的代码并分析原因。

如何得到dump文件  
在vs中进入调试状态后中断，在菜单中选择“调试”-》“将转储另存为”即可生成dump文件     
如何写代码生成dump文件    

如何加载pdb文件  
在VS中我们选择“菜单”-》工具-》选项，选项窗口中选择调试-》符号   
设置pdb所在目录，当调试时vs会自动加载模块对应的pdb文件。   

- # 利用PDB和dump进行调试
收集输出dmp文件  
设置程序pdb文件目录  
打开dmp文件，运行dmp  
通过堆栈定位问题函数  
通过代码定位问题函数具体代码位置  

- # FreeType    
https://www.freetype.org/freetype2/docs/tutorial/step2.html#section-1  

