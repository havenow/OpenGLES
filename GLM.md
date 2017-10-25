OpenGl中在进行图形变换的时候需要使用几何数学库，这里使用第三方数学库GLM。  
github地址：https://github.com/g-truc/glm  

```
OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.

GLM provides classes and functions designed and implemented with the same naming conventions and functionality than GLSL so that anyone who knows GLSL, can use GLM as well in C++.

This project isn't limited to GLSL features. An extension system, based on the GLSL extension conventions, provides extended capabilities: matrix transformations, quaternions, data packing, random numbers, noise, etc...

This library works perfectly with OpenGL but it also ensures interoperability with other third party libraries and SDK. It is a good candidate for software rendering (raytracing / rasterisation), image processing, physic simulations and any development context that requires a simple and convenient mathematics library.

GLM is written in C++98 but can take advantage of C++11 when supported by the compiler. It is a platform independent library with no dependence and it officially supports the following compilers:

Apple Clang 6.0 and higher
GCC 4.7 and higher
Intel C++ Composer XE 2013 and higher
LLVM 3.4 and higher
Visual C++ 2013 and higher
CUDA 7.0 and higher (experimental)
Any C++11 compiler
For more information about GLM, please have a look at the manual and the API reference documentation. The source code and the documentation are licensed under both the Happy Bunny License (Modified MIT) or the MIT License.

Thanks for contributing to the project by submitting issues for bug reports and feature requests. Any feedback is welcome at glm@g-truc.net.
```

```
OpenGL Mathematics (GLM) 是基于OpenGL着色语言（GLSL）规范的图形软件的头文件C ++数学库。

GLM提供的类和函数使用与GLSL相同的命名约定和功能设计和实现，因此任何知道GLSL的人都可以在C ++中使用GLM。

这个项目不限于GLSL的功能。基于GLSL扩展约定的扩展系统提供扩展能力：矩阵变换，四元数，数据打包，随机数，噪声等等。

这个库与OpenGL完美地工作，但它也确保与其他第三方库和SDK的互操作性。它是软件渲染（光线追踪/光栅化），图像处理，物理模拟和任何需要简单方便的数学库的开发上下文的良好候选。

GLM是用C ++ 98编写的，但是当编译器支持时可以利用C ++ 11。它是一个没有依赖的平台独立库，它正式支持以下编译器：
    ● 苹果Clang 6.0及更高版本
    ● GCC 4.7及以上
    ● 英特尔C ++ Composer XE 2013及更高版本
    ● LLVM 3.4及更高版本
    ● Visual C ++ 2013及更高版本
    ● CUDA 7.0及更高版本（实验版）
    ● 任何C ++ 11编译器

有关GLM的更多信息，请查看手册和API参考文档。 源代码和文档根据Happy Bunny License (Modified MIT)或MIT许可证授权。

感谢您通过提交错误报告和功能请求的问题为项目做出贡献。 欢迎任何反馈在glm@g-truc.net。

```
```c++
使用案例:

#include <glm/vec3.hpp> // glm::vec3  
#include <glm/vec4.hpp> // glm::vec4  
#include <glm/mat4x4.hpp> // glm::mat4  
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective  
#include <glm/gtc/constants.hpp> // glm::pi  
  
glm::mat4 camera(float Translate, glm::vec2 const & Rotate)  
{  
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);  
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));  
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));  
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));  
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));  
    return Projection * View * Model;  
} 
```
