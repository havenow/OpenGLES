//
//  ViewUsingEAGL.h
//  IOS_OPENGLES_EGL
//
//  Created by wangf on 16/8/31.
//  Copyright © 2016年 wangf. All rights reserved.
//参考 http://blog.csdn.net/kesalin/article/details/8221393
//    http://blog.db-in.com/khronos-egl-and-apple-eagl/
//oc语法：
//http://blog.csdn.net/yuhailong626/article/details/9081815
//http://blog.csdn.net/cherry609195946/article/details/19609485
//http://www.cnblogs.com/QianChia/p/5780653.html

#ifndef ViewUsingEAGL_h
#define ViewUsingEAGL_h

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface ViewUsingEAGL : UIView {
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
    GLuint _frameBuffer;
}

@end

#endif /* ViewUsingEAGL_h */
