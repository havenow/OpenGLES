#pragma once

#include <assert.h>

#include "CGLESAdapter.hpp"

class    ShaderId
{
public:
    ShaderId()
    {
        _shaderId   =   -1;
    }
    int _shaderId;
};


/**
*   程序
*/
class   ProgramId
{
public:
    int         _programId;
    ShaderId    _vertex;
    ShaderId    _fragment;
public:
    ProgramId()
    {
        _programId  =   -1;
    }
public:
    /**
    *   加载函数
    */
    bool    createProgram( const char* vertex,const char* fragment )
    {
        bool        error   =   false;
        do 
        {
            if (vertex)
            {
                _vertex._shaderId   = GLESAdapter::Instance()->call_glCreateShader( GL_VERTEX_SHADER );
                GLESAdapter::Instance()->call_glShaderSource( _vertex._shaderId, 1, &vertex, 0 );
                 GLESAdapter::Instance()->call_glCompileShader( _vertex._shaderId );

                GLint   compileStatus;
                GLESAdapter::Instance()->call_glGetShaderiv( _vertex._shaderId, GL_COMPILE_STATUS, &compileStatus );
                error   =   compileStatus == GL_FALSE;
                if( error )
                {
                    GLchar messages[256];
                     GLESAdapter::Instance()->call_glGetShaderInfoLog( _vertex._shaderId, sizeof(messages), 0,messages);
                    assert( messages && 0 != 0);
                    break;
                }
            }
            if (fragment)
            {
                _fragment._shaderId   =  GLESAdapter::Instance()->call_glCreateShader( GL_FRAGMENT_SHADER );
                 GLESAdapter::Instance()->call_glShaderSource( _fragment._shaderId, 1, &fragment, 0 );
                 GLESAdapter::Instance()->call_glCompileShader( _fragment._shaderId );

                GLint   compileStatus;
                GLESAdapter::Instance()->call_glGetShaderiv( _fragment._shaderId, GL_COMPILE_STATUS, &compileStatus );
                error   =   compileStatus == GL_FALSE;

                if( error )
                {
                    GLchar messages[256];
                     GLESAdapter::Instance()->call_glGetShaderInfoLog( _fragment._shaderId, sizeof(messages), 0,messages);
                    assert( messages && 0 != 0);
                    break;
                }
            }
            _programId  =    GLESAdapter::Instance()->call_glCreateProgram( );

            if (_vertex._shaderId)
            {
                 GLESAdapter::Instance()->call_glAttachShader( _programId, _vertex._shaderId);
            }
            if (_fragment._shaderId)
            {
                 GLESAdapter::Instance()->call_glAttachShader( _programId, _fragment._shaderId);
            }

             GLESAdapter::Instance()->call_glLinkProgram( _programId );

            GLint linkStatus;
             GLESAdapter::Instance()->call_glGetProgramiv( _programId, GL_LINK_STATUS, &linkStatus );
            if (linkStatus == GL_FALSE)
            {
                GLchar messages[256];
                 GLESAdapter::Instance()->call_glGetProgramInfoLog( _programId, sizeof(messages), 0, messages);
                break;
            }
             GLESAdapter::Instance()->call_glUseProgram(_programId);

        } while(false);

        if (error)
        {
            if (_fragment._shaderId)
            {
                 GLESAdapter::Instance()->call_glDeleteShader(_fragment._shaderId);
                _fragment._shaderId =   0;
            }
            if (_vertex._shaderId)
            {
                 GLESAdapter::Instance()->call_glDeleteShader(_vertex._shaderId);
                _vertex._shaderId   =   0;
            }
            if (_programId)
            {
                 GLESAdapter::Instance()->call_glDeleteProgram(_programId);
                _programId          =   0;
            }
        }
        return  true;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
         GLESAdapter::Instance()->call_glUseProgram(_programId);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
         GLESAdapter::Instance()->call_glUseProgram(0);
    }
};



class   PROGRAM_P2_C4 :public ProgramId
{
public:
    typedef int attribute; 
    typedef int uniform;
public:
    attribute   _position;
    uniform     _color;
    uniform     _MVP;
public:
    PROGRAM_P2_C4()
    {
        _position   =   -1;
        _color      =   -1;
        _MVP        =   -1;
    }
    ~PROGRAM_P2_C4()
    {
    }
   
    /// 初始化函数
    virtual bool    initialize()
    {
        const char* vs  =   
        {
            "precision lowp float; "
            "uniform   mat4 _MVP;"
            "attribute vec2 _position;"

            "void main()"
            "{"
            "   vec4    pos =   vec4(_position,0,1);"
            "   gl_Position =   _MVP * pos;"
            "}"
        };
        const char* ps  =   
        {
            "precision  lowp float; "
            "uniform    vec4 _color;"
            "void main()"
            "{"
            "   gl_FragColor   =   _color;"
            "}"
        };
        
        bool    res =   createProgram(vs,ps);
        if(res)
        {
            _position   =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId,"_position");
            _color      =    GLESAdapter::Instance()->call_glGetUniformLocation(_programId,"_color");
            _MVP        =    GLESAdapter::Instance()->call_glGetUniformLocation(_programId,"_MVP");
        }
        return  res;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
         GLESAdapter::Instance()->call_glUseProgram(_programId);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_position);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_position);
         GLESAdapter::Instance()->call_glUseProgram(0);
    }
};
class   PROGRAM_P2_AC4 :public ProgramId
{
public:
    typedef int attribute; 
    typedef int uniform;
public:
    attribute   _position;
    attribute   _color;
    uniform     _MVP;
public:
    PROGRAM_P2_AC4()
    {
        _position   =   -1;
        _color      =   -1;
        _MVP        =   -1;
    }
    ~PROGRAM_P2_AC4()
    {
    }
   
    /// 初始化函数
    virtual bool    initialize()
    {
        const char* vs  =   
        {
            "precision lowp float; "
            "uniform   mat4 _MVP;"
            "attribute vec2 _position;"
            "attribute vec4 _color;"
            "varying   vec4 _outColor;"

            "void main()"
            "{"
            "   vec4    pos =   vec4(_position,0,1);"
            "   _outColor   =   _color;"
            "   gl_Position =   _MVP * pos;"
            "}"
        };
        const char* ps  =   
        {
            "precision  lowp float; "
            "varying   vec4 _outColor;"
            "void main()"
            "{"
            "   gl_FragColor   =   _outColor;"
            "}"
        };
        
        bool    res =   createProgram(vs,ps);
        if(res)
        {
            _position   =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId, "_position");
            _color      =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId, "_color");
            _MVP        =    GLESAdapter::Instance()->call_glGetUniformLocation(_programId,"_MVP");
        }
        return  res;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
        GLESAdapter::Instance()->call_glUseProgram(_programId);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_position);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_color);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_position);
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_color);
         GLESAdapter::Instance()->call_glUseProgram(0);
    }
};



class   PROGRAM_P2_UV_AC4 :public ProgramId
{
public:
    typedef int attribute; 
    typedef int uniform;
public:
    attribute   _position;
    attribute   _color;
    attribute   _uv;
    uniform     _MVP;
    uniform     _texture;
public:
    PROGRAM_P2_UV_AC4()
    {
        _position   =   -1;
        _color      =   -1;
        _uv         =   -1;
        _texture    =   -1;
        _MVP        =   -1;
    }
    ~PROGRAM_P2_UV_AC4()
    {
    }
   
    /// 初始化函数
    virtual bool    initialize()
    {
        const char* vs  =   
        {
            "precision lowp float; "
            "uniform   mat4 _MVP;"
            "attribute vec2 _position;"
            "attribute vec2 _uv;"
            "attribute vec4 _color;"
            "varying   vec4 _outColor;"
            "varying   vec2 _outUV;"

            "void main()"
            "{"
            "   vec4    pos =   vec4(_position,0,1);"
            "   _outColor   =   _color;"
            "   _outUV      =   _uv;"
            "   gl_Position =   _MVP * pos;"
            "}"
        };
        const char* ps  =   
        {
            "precision  lowp float; "
            "uniform   sampler2D _texture;\n"
            "varying   vec4      _outColor;\n"
            "varying   vec2      _outUV;\n"
            "void main()"
            "{"
            "   vec4    tColor  =   texture2D(_texture,_outUV);\n"
            "   gl_FragColor    =   tColor * _outColor;\n"
            "}"
        };
        
        bool    res =   createProgram(vs,ps);
        if(res)
        {
            _position   =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId, "_position");
            _color      =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId, "_color");
            _uv         =    GLESAdapter::Instance()->call_glGetAttribLocation(_programId, "_uv");
            _texture    =    GLESAdapter::Instance()->call_glGetUniformLocation(_programId,"_texture");
            _MVP        =    GLESAdapter::Instance()->call_glGetUniformLocation(_programId,"_MVP");
        }
        return  res;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
         GLESAdapter::Instance()->call_glUseProgram(_programId);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_position);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_uv);
         GLESAdapter::Instance()->call_glEnableVertexAttribArray(_color);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_position);
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_uv);
         GLESAdapter::Instance()->call_glDisableVertexAttribArray(_color);
         GLESAdapter::Instance()->call_glUseProgram(0);
    }
};

