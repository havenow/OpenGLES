//
//  AppDelegate.h
//  IOS_OPENGLES_EGL
//
//  Created by wangf on 16/8/31.
//  Copyright © 2016年 wangf. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ViewUsingEAGL.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    ViewUsingEAGL* _glView;
}


@property (strong, nonatomic) UIWindow *window;//等价于EGLDispaly
@property (strong, retain) IBOutlet ViewUsingEAGL *glView;//等价于EGLSurface

@end

