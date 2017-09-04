
[微软的angle工程，有sln工程文件](https://github.com/Microsoft/angle)

[Using ANGLE for Windows and using the OpenGLES2.0 API](http://gpupowered.org/node/29/)

- # 原文

```
Using ANGLE for Windows and using the OpenGLES2.0 API

Submitted by prabindh on Fri, 01/15/2016 - 20:40 / / 

Introduction 
ANGLE (Almost Native Graphics Layer Engine) is a software wrapper, that provides a Khronos certified OpenGLES2.0 implementation on Windows platforms. This is a good tool to understand how 3D Graphics APIs work internally. Qt5 also uses ANGLE internally on windows builds, to be able to run the SceneGraph framework using OpenGLES2.0 across all platforms, including windows, in all versions from Qt5.1, Qt5.2 and further. 
Note: For a quick way to use EGL and develop OpenGLES2 natively on Windows using your favorite tools, refer to the article - http://gpupowered.org/node/33 
Note: This article is for using and building the ANGLE project source files directly from Google repository. With NuGet packaging, Microsoft provides its own source patches for building ANGLE projects for Windows10/Phone platforms. But note that this method needs the latest VIsual Studio tools (Visual studio 2015). 

Need 
Microsoft does not provide a native OpenGLES2.0 API on its platforms. The OpenGL version available by default on Windows is outdated. Hence ANGLE was created to satisfy the needs from browser vendors, applications, and various content providers to be able to run same content on mobile platforms, and Windows. However, by last quarter of 2013, Microsoft released its own WebGL implementation running in IE11, which indicates that internally there exists an OpenGLES2.0 like implementation on Windows (WebGL very closely resembles OpenGLES2.0). It remains to be seen how/if Microsoft will provide its own implementation along with its platforms. 

ANGLE is not a pure software renderer for OpenGL ES2.0 API, and therefore is unlike Mesa. To be reasonably fast, it uses the underlying DirectX API on Windows itself, to render using OpenGLES2.0. Hence ANGLE can be considered an API translator, that runs on native Graphics HW accelerated API on Windows. 

Obtaining the code 
To get the code, git can be used, as below. Note that ANGLE is a part of Chromium repository at this time (2014). 
git clone https://chromium.googlesource.com/angle/angle 


Code organisation 
ANGLE is written in c++, and there are 4 main sub projects in ANGLE. These are listed below: 
libEGL
libGLESv2
preprocessor
translator The libEGL.lib, and libGLESv2.lib are linked in every application, just like regular OpenGL ES2 builds. The preprocessor and translator library outputs, are a part of libGLESv2.lib itself, and are used for Shader source compilation. 

Building 
There are 2 solution (.sln) files provided for building on Windows platforms. These are 
angle/src/ANGLE.sln
angle/samples/samples.sln These need to be built, in the same order as above. When using Visual Studio 2012 for Desktop, the below additional steps are needed: 
Add the below path to the "Include Directories" option for both projects (under C/C++ properties), and also separately for libGLESv2.rc file (note that this is not a C/C++ file) 
C:\Program Files (x86)\Windows Kits\8.0\Include\um;C:\Program Files (x86)\Windows Kits\8.0\Include\shared 

Build logs 
Below is the build log for the core ANGLE solution. 

1>------ Build started: Project: translator, Configuration: Debug Win32 ------
2>------ Build started: Project: preprocessor, Configuration: Debug Win32 ------
2> Tokenizer.cpp 1> VersionGLSL.cpp 2> Token.cpp 1> ArrayBoundsClamper.cpp 2> Preprocessor.cpp 1> RestrictVertexShaderTiming.cpp 2> MacroExpander.cpp 1> RestrictFragmentShaderTiming.cpp 2> Macro.cpp 2> Lexer.cpp 2> Input.cpp 1> DependencyGraphTraverse.cpp 2> ExpressionParser.cpp 2> DirectiveParser.cpp 1> DependencyGraphOutput.cpp 2> DirectiveHandlerBase.cpp 1> DependencyGraphBuilder.cpp 2> DiagnosticsBase.cpp 1> DependencyGraph.cpp 2> Generating Code... 2> preprocessor.vcxproj -> D:\angle\src\Debug\preprocessor.lib 1> glslang_tab.cpp 1> glslang_lex.cpp 1> VariablePacker.cpp 1> VariableInfo.cpp 1> ValidateLimitations.cpp 1> util.cpp 1> Uniform.cpp 1> UnfoldShortCircuitAST.cpp 1> UnfoldShortCircuit.cpp 1> TranslatorHLSL.cpp 1> TranslatorGLSL.cpp 1> TranslatorESSL.cpp 1> Generating Code... 1> Compiling... 1> SymbolTable.cpp 1> ShaderLang.cpp 1> SearchSymbol.cpp 1> RemoveTree.cpp 1> QualifierAlive.cpp 1> PoolAlloc.cpp 1> ParseContext.cpp 1> parseConst.cpp 1> OutputHLSL.cpp 1> OutputGLSLBase.cpp 1> OutputGLSL.cpp 1> OutputESSL.cpp 1> ossource_win.cpp 1> MapLongVariableNames.cpp 1> IntermTraverse.cpp 1> intermOut.cpp 1> Intermediate.cpp 1> InitializeParseContext.cpp 1> InitializeGLPosition.cpp 1> InitializeDll.cpp 1> Generating Code... 1> Compiling... 1> Initialize.cpp 1> InfoSink.cpp 1> ForLoopUnroll.cpp 1> DirectiveHandler.cpp 1> Diagnostics.cpp 1> DetectDiscontinuity.cpp 1> DetectCallDepth.cpp 1> debug.cpp 1> Compiler.cpp 1> CodeGen.cpp 1> BuiltInFunctionEmulator.cpp 1> Generating Code... 1> translator.vcxproj -> D:\angle\src\Debug\translator.lib

3>------ Build started: Project: libGLESv2, Configuration: Debug Win32 ------
3> precompiled.cpp 3> event_tracer.cpp 3> debug.cpp 3> MurmurHash3.cpp 3> Generating Code... 3> utilities.cpp 3> Uniform.cpp 3> Texture.cpp 3> Shader.cpp 3> ResourceManager.cpp 3> VertexDeclarationCache.cpp 3> VertexDataManager.cpp 3> VertexBuffer9.cpp 3> VertexBuffer11.cpp 3> VertexBuffer.cpp 3> TextureStorage9.cpp 3> TextureStorage11.cpp 3> TextureStorage.cpp 3> SwapChain9.cpp 3> SwapChain11.cpp 3> ShaderExecutable9.cpp 3> ShaderExecutable11.cpp 3> RenderStateCache.cpp 3> RenderTarget9.cpp 3> RenderTarget11.cpp 3> Generating Code... 3> Compiling... 3> renderer9_utils.cpp 3> Renderer9.cpp 3> renderer11_utils.cpp 3> Renderer11.cpp 3> Renderer.cpp 3> Query9.cpp 3> Query11.cpp 3> InputLayoutCache.cpp 3> IndexRangeCache.cpp 3> Image11.cpp 3> ImageSSE2.cpp 3> IndexDataManager.cpp 3> IndexBuffer9.cpp 3> IndexBuffer11.cpp 3> IndexBuffer.cpp 3> Image9.cpp 3> Image.cpp 3> BufferStorage9.cpp 3> BufferStorage11.cpp 3> BufferStorage.cpp 3> Generating Code... 3> Compiling... 3> Fence9.cpp 3> Fence11.cpp 3> Blit.cpp 3> Renderbuffer.cpp 3> RefCountObject.cpp 3> Query.cpp 3> ProgramBinary.cpp 3> Program.cpp 3> main.cpp 3> libGLESv2.cpp 3> HandleAllocator.cpp 3> Framebuffer.cpp 3> Float16ToFloat32.cpp 3> Fence.cpp 3> Context.cpp 3> Buffer.cpp 3> Generating Code...
3>MurmurHash3.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification
3> Creating library D:\angle\src\Debug\libGLESv2.lib and object D:\angle\src\Debug\libGLESv2.exp
3> libGLESv2.vcxproj -> D:\angle\src\Debug\libGLESv2.dll 3> A subdirectory or file D:\angle\src\libGLESv2\..\..\lib\Debug\ already exists.
3> 1 file(s) copied.
3> 1 file(s) copied.
4>------ Build started: Project: libEGL, Configuration: Debug Win32 ------
4> Surface.cpp 4> main.cpp 4> libEGL.cpp 4> Display.cpp 4> debug.cpp 4> Config.cpp 4> Generating Code... 4>Config.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 4> Creating library D:\angle\src\Debug\libEGL.lib and object D:\angle\src\Debug\libEGL.exp 4> libEGL.vcxproj -> D:\angle\src\Debug\libEGL.dll 4> A subdirectory or file D:\angle\src\libEGL\..\..\lib\Debug\ already exists.
4> 1 file(s) copied. 4> 1 file(s) copied. ========== Build: 4 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========


Below is the log for the samples solution. 1>------ Build started: Project: preprocessor, Configuration: Debug Win32 ------ 2>------ Build started: Project: translator, Configuration: Debug Win32 ------ 1> Tokenizer.cpp 2> VersionGLSL.cpp 1> Token.cpp 2> ArrayBoundsClamper.cpp 1> Preprocessor.cpp 2> RestrictVertexShaderTiming.cpp 1> MacroExpander.cpp 2> RestrictFragmentShaderTiming.cpp 1> Macro.cpp 1> Lexer.cpp 1> Input.cpp 1> ExpressionParser.cpp 2> DependencyGraphTraverse.cpp 1> DirectiveParser.cpp 2> DependencyGraphOutput.cpp 1> DirectiveHandlerBase.cpp 2> DependencyGraphBuilder.cpp 1> DiagnosticsBase.cpp 1> Generating Code... 2> DependencyGraph.cpp 1> preprocessor.vcxproj -> D:\angle\samples\Debug\preprocessor.lib 2> glslang_tab.cpp 2> glslang_lex.cpp 2> VariablePacker.cpp 2> VariableInfo.cpp 2> ValidateLimitations.cpp 2> util.cpp 2> Uniform.cpp 2> UnfoldShortCircuitAST.cpp 2> UnfoldShortCircuit.cpp 2> TranslatorHLSL.cpp 2> TranslatorGLSL.cpp 2> TranslatorESSL.cpp 2> Generating Code... 2> Compiling... 2> SymbolTable.cpp 2> ShaderLang.cpp 2> SearchSymbol.cpp 2> RemoveTree.cpp 2> QualifierAlive.cpp 2> PoolAlloc.cpp 2> ParseContext.cpp 2> parseConst.cpp 2> OutputHLSL.cpp 2> OutputGLSLBase.cpp 2> OutputGLSL.cpp 2> OutputESSL.cpp 2> ossource_win.cpp 2> MapLongVariableNames.cpp 2> IntermTraverse.cpp 2> intermOut.cpp 2> Intermediate.cpp 2> InitializeParseContext.cpp 2> InitializeGLPosition.cpp 2> InitializeDll.cpp 2> Generating Code... 2> Compiling... 2> Initialize.cpp 2> InfoSink.cpp 2> ForLoopUnroll.cpp 2> DirectiveHandler.cpp 2> Diagnostics.cpp 2> DetectDiscontinuity.cpp 2> DetectCallDepth.cpp 2> debug.cpp 2> Compiler.cpp 2> CodeGen.cpp 2> BuiltInFunctionEmulator.cpp 2> Generating Code... 2> translator.vcxproj -> D:\angle\samples\Debug\translator.lib
3>------ Build started: Project: libGLESv2, Configuration: Debug Win32 ------ 4>------ Build started: Project: essl_to_hlsl, Configuration: Debug Win32 ------ 4> translator.cpp 3> precompiled.cpp 4> debug.cpp 4> Generating Code... 4>debug.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 3> event_tracer.cpp 3> debug.cpp 4> essl_to_hlsl.vcxproj -> D:\angle\samples\Debug\essl_to_hlsl.exe 3> MurmurHash3.cpp 3> Generating Code... 3> utilities.cpp 3> Uniform.cpp 3> Texture.cpp 3> Shader.cpp 3> ResourceManager.cpp 3> VertexDeclarationCache.cpp 3> VertexDataManager.cpp 3> VertexBuffer9.cpp 3> VertexBuffer11.cpp 3> VertexBuffer.cpp 3> TextureStorage9.cpp 3> TextureStorage11.cpp 3> TextureStorage.cpp 3> SwapChain9.cpp 3> SwapChain11.cpp 3> ShaderExecutable9.cpp 3> ShaderExecutable11.cpp 3> RenderStateCache.cpp 3> RenderTarget9.cpp 3> RenderTarget11.cpp 3> Generating Code... 3> Compiling... 3> renderer9_utils.cpp 3> Renderer9.cpp 3> renderer11_utils.cpp 3> Renderer11.cpp 3> Renderer.cpp 3> Query9.cpp 3> Query11.cpp 3> InputLayoutCache.cpp 3> IndexRangeCache.cpp 3> Image11.cpp 3> ImageSSE2.cpp 3> IndexDataManager.cpp 3> IndexBuffer9.cpp 3> IndexBuffer11.cpp 3> IndexBuffer.cpp 3> Image9.cpp 3> Image.cpp 3> BufferStorage9.cpp 3> BufferStorage11.cpp 3> BufferStorage.cpp 3> Generating Code... 3> Compiling... 3> Fence9.cpp 3> Fence11.cpp 3> Blit.cpp 3> Renderbuffer.cpp 3> RefCountObject.cpp 3> Query.cpp 3> ProgramBinary.cpp 3> Program.cpp 3> main.cpp 3> libGLESv2.cpp 3> HandleAllocator.cpp 3> Framebuffer.cpp 3> Float16ToFloat32.cpp 3> Fence.cpp 3> Context.cpp 3> Buffer.cpp 3> Generating Code... 3>MurmurHash3.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 3> Creating library D:\angle\samples\Debug\libGLESv2.lib and object D:\angle\samples\Debug\libGLESv2.exp
3> libGLESv2.vcxproj -> D:\angle\samples\Debug\libGLESv2.dll
3> A subdirectory or file D:\angle\src\libGLESv2\..\..\lib\Debug\ already exists. 3> 1 file(s) copied. 3> 1 file(s) copied. 5>------ Build started: Project: libEGL, Configuration: Debug Win32 ------ 5> Surface.cpp 5> main.cpp 5> libEGL.cpp 5> Display.cpp 5> debug.cpp 5> Config.cpp 5> Generating Code... 5>Config.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 5> Creating library D:\angle\samples\Debug\libEGL.lib and object D:\angle\samples\Debug\libEGL.exp
5> libEGL.vcxproj -> D:\angle\samples\Debug\libEGL.dll
5> A subdirectory or file D:\angle\src\libEGL\..\..\lib\Debug\ already exists. 5> 1 file(s) copied. 5> 1 file(s) copied. 6>------ Build started: Project: esUtil, Configuration: Debug Win32 ------ 6> esUtil.c 6> esTransform.c 6> esShapes.c 6> esShader.c 6> esUtil_win32.c 6> esUtil_TGA.c 6> Generating Code... 6>libGLESv2.lib(libGLESv2.dll) : warning LNK4006: __NULL_IMPORT_DESCRIPTOR already defined in libEGL.lib(libEGL.dll); second definition ignored 6>libGLESv2.lib(libGLESv2.dll) : warning LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library 6> esUtil.vcxproj -> D:\angle\samples\Debug\esUtil.lib 7>------ Build started: Project: Hello_Triangle, Configuration: Debug Win32 ------ 8>------ Build started: Project: MipMap2D, Configuration: Debug Win32 ------ 9>------ Build started: Project: MultiTexture, Configuration: Debug Win32 ------ 10>------ Build started: Project: ParticleSystem, Configuration: Debug Win32 ------ 9> MultiTexture.c 8> MipMap2D.c 7> Hello_Triangle.c 10> ParticleSystem.c 9>MultiTexture.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 8>MipMap2D.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 7>Hello_Triangle.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 10>ParticleSystem.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 9> MultiTexture.vcxproj -> D:\angle\samples\Debug\MultiTexture.exe 7> Hello_Triangle.vcxproj -> D:\angle\samples\Debug\Hello_Triangle.exe 8> MipMap2D.vcxproj -> D:\angle\samples\Debug\MipMap2D.exe 9> 0 File(s) copied 9> 0 File(s) copied 11>------ Build started: Project: Simple_Texture2D, Configuration: Debug Win32 ------ 11> Simple_Texture2D.c 10> ParticleSystem.vcxproj -> D:\angle\samples\Debug\ParticleSystem.exe 12>------ Build started: Project: Simple_TextureCubemap, Configuration: Debug Win32 ------ 12> Simple_TextureCubemap.c 10> 0 File(s) copied 13>------ Build started: Project: Simple_VertexShader, Configuration: Debug Win32 ------ 14>------ Build started: Project: Stencil_Test, Configuration: Debug Win32 ------ 13> Simple_VertexShader.c 14> Stencil_Test.c 11>Simple_Texture2D.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 12>Simple_TextureCubemap.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 14>Stencil_Test.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 13>Simple_VertexShader.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 11> Simple_Texture2D.vcxproj -> D:\angle\samples\Debug\Simple_Texture2D.exe 15>------ Build started: Project: TextureWrap, Configuration: Debug Win32 ------ 15> TextureWrap.c 12> Simple_TextureCubemap.vcxproj -> D:\angle\samples\Debug\Simple_TextureCubemap.exe 13> Simple_VertexShader.vcxproj -> D:\angle\samples\Debug\Simple_VertexShader.exe 14> Stencil_Test.vcxproj -> D:\angle\samples\Debug\Stencil_Test.exe 16>------ Build started: Project: PostSubBuffer, Configuration: Debug Win32 ------ 17>------ Build started: Project: Simple_Instancing, Configuration: Debug Win32 ------ 18>------ Build started: Project: MultipleRenderTargets, Configuration: Debug Win32 ------ 16> PostSubBuffer.c 17> Simple_Instancing.c 18> MultipleRenderTargets.c 15>TextureWrap.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 16>PostSubBuffer.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 18>MultipleRenderTargets.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 17>Simple_Instancing.obj : warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification 15> TextureWrap.vcxproj -> D:\angle\samples\Debug\TextureWrap.exe 17> Simple_Instancing.vcxproj -> D:\angle\samples\Debug\Simple_Instancing.exe 16> PostSubBuffer.vcxproj -> D:\angle\samples\Debug\PostSubBuffer.exe 18> MultipleRenderTargets.vcxproj -> D:\angle\samples\Debug\MultipleRenderTargets.exe ========== Build: 18 succeeded, 0 failed, 0 up-to-date, 0 skipped ========== 

After this step, all ANGLE sample projects can be run from Visual Studio itself. For example, "Hello Triangle" will show a red triangle with black background. 

References: 
Since the original article written in 2013, an introduction to ANGLE from Shannon Woods available below: 
https://docs.google.com/presentation/d/1vN_KTFDaKjFlIgx1vM3ZFA4Rkf723onAAhIfKR7kmgA/edit?pli=1#slide=id.gda2d11de0_0_58 
-Prabindh Sundareson, 2015
```

- # 翻译

```
介绍
ANGLE (Almost Native Graphics Layer Engine)是一个软件包，在Windows平台上，提供了一个Khronos认证的OpenGLES2.0实现。这是一个了解3D图形API如何在内部工作的好工具。Qt5内部也使用ANGLE创建窗口，能够运行在所有平台上运行OpenGLES2.0场景框架，包括Windows平台，在所有qt5.2 Qt5.1版本，并进一步。

注意：使用您最喜爱的工具，快速使用EGL并且在Windows平台开发OpenGLES2.0程序，请参阅文章- http://gpupowered.org/node/33
。
注意：本文是为了说明Google仓储中ANGLE工程源代码的使用和编译，用NuGet打包，微软为windows10 /手机平台提供了它自己的源代码补丁编译ANGLE项目。但是请注意，该方法需要最新的Visual Studio工具（Visual Studio 2015）。

需要

微软并没有提供一个本地的OpenGLES2.0 API实现。在Windows默认情况下可用的OpenGL版本已经过时。因此，为满足浏览器厂商、应用程序和各种内容提供商的需求，创建了能够在移动平台和Windows上运行相同内容的ANGLE。然而，由2013上季度，微软发布了自己的WebGL运行IE11，这表明Windows内部存在一个OpenGLES2.0的类似实现（WebGL非常类似OpenGLES2.0）。微软将如何提供其自己的实现及其平台，还有待观察。
ANGLE不是OpenGL ES2.0 API纯软件渲染，因此不像Mesa，是相当快的，它使用Windows底层的DirectX API，使用OpenGLES2.0。因此，
ANGLE可以被看作是一个API翻译程序，它运行在Windows上的本地图形硬加速API上。  

获取代码

要获得代码，可以使用Git，如下所示。注意，ANGLE是Chromium项目的一部分（2014）。
git clone https://chromium.googlesource.com/angle/angle


代码组织

ANGLE是用C++写的，有主要有4个子项目。下面列出这些：

libEGL
libGLESv2
preprocessor

translator the libEGL.lib，和libGLESv2.lib链接在每一个应用程序，就像普通的OpenGLES2建立。preprocessor and translator library outputs，是libGLESv2.lib本身的一部分，和用于Shader代码编译。

Build
在Windows平台上提供了2个解决方案（SLN）文件。这些是

angle/src/ANGLE.sln
angle/samples/samples.sln
这些需要建立在相同的顺序上。在使用Visual Studio 2012进行桌面操作时，需要下面的其他步骤：

两个工程的 "Include Directories" 添加下面的路径，（under C/C++ properties），同时分别添加libGLESv2.rc 文件（注意，这不是一个C / C++文件）
C:\Program Files (x86)\Windows Kits\8.0\Include\um;
C:\Program Files (x86)\Windows Kits\8.0\Include\shared 

Build日志

```
