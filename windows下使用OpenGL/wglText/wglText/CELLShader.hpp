#pragma once

#include <assert.h>

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
                _vertex._shaderId   = glCreateShader( GL_VERTEX_SHADER );
                glShaderSource( _vertex._shaderId, 1, &vertex, 0 );
                glCompileShader( _vertex._shaderId );

                GLint   compileStatus;
                glGetShaderiv( _vertex._shaderId, GL_COMPILE_STATUS, &compileStatus );
                error   =   compileStatus == GL_FALSE;
                if( error )
                {
                    GLchar messages[256];
                    glGetShaderInfoLog( _vertex._shaderId, sizeof(messages), 0,messages);
                    assert( messages && 0 != 0);
                    break;
                }
            }
            if (fragment)
            {
                _fragment._shaderId   = glCreateShader( GL_FRAGMENT_SHADER );
                glShaderSource( _fragment._shaderId, 1, &fragment, 0 );
                glCompileShader( _fragment._shaderId );

                GLint   compileStatus;
                glGetShaderiv( _fragment._shaderId, GL_COMPILE_STATUS, &compileStatus );
                error   =   compileStatus == GL_FALSE;

                if( error )
                {
                    GLchar messages[256];
                    glGetShaderInfoLog( _fragment._shaderId, sizeof(messages), 0,messages);
                    assert( messages && 0 != 0);
                    break;
                }
            }
            _programId  =   glCreateProgram( );

            if (_vertex._shaderId)
            {
                glAttachShader( _programId, _vertex._shaderId);
            }
            if (_fragment._shaderId)
            {
                glAttachShader( _programId, _fragment._shaderId);
            }

            glLinkProgram( _programId );

            GLint linkStatus;
            glGetProgramiv( _programId, GL_LINK_STATUS, &linkStatus );
            if (linkStatus == GL_FALSE)
            {
                GLchar messages[256];
                glGetProgramInfoLog( _programId, sizeof(messages), 0, messages);
                break;
            }
            glUseProgram(_programId);

        } while(false);

        if (error)
        {
            if (_fragment._shaderId)
            {
                glDeleteShader(_fragment._shaderId);
                _fragment._shaderId =   0;
            }
            if (_vertex._shaderId)
            {
                glDeleteShader(_vertex._shaderId);
                _vertex._shaderId   =   0;
            }
            if (_programId)
            {
                glDeleteProgram(_programId);
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
        glUseProgram(_programId);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
        glUseProgram(0);
    }
};








class   PROGRAM_P2_UV2 :public ProgramId
{
public:
    typedef int attribute; 
    typedef int uniform;
public:
    attribute   _position;
    attribute   _uv;
    uniform     _MVP;
    uniform     _texture;
public:
    PROGRAM_P2_UV2()
    {
        _position   =   -1;
        _uv         =   -1;
        _MVP        =   -1;
        _texture    =   -1;
    }
    ~PROGRAM_P2_UV2()
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
            "varying   vec2 _outUV;"

            "void main()"
            "{"
            "   _outUV  =   _uv;"
            "   vec4    pos =   vec4(_position,0,1);"
            "   gl_Position =   _MVP * pos;"
            "}"
        };
        const char* ps  =   
        {
            "precision  lowp float; "
            "uniform    sampler2D   _texture;"
            "varying    vec2        _outUV;"
            "void main()"
            "{"
            "   vec4   color   =   texture2D(_texture,_outUV);"
            "   gl_FragColor   =   color;"
            "}"
        };
        
        bool    res =   createProgram(vs,ps);
        if(res)
        {
            _position   =   glGetAttribLocation(_programId,"_position");
            _uv         =   glGetAttribLocation(_programId,"_uv");
            _texture    =   glGetUniformLocation(_programId,"_texture");
            _MVP        =   glGetUniformLocation(_programId,"_MVP");
        }
        return  res;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
        glUseProgram(_programId);
        glEnableVertexAttribArray(_position);
        glEnableVertexAttribArray(_uv);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
        glDisableVertexAttribArray(_position);
        glDisableVertexAttribArray(_uv);
        glUseProgram(0);
    }
};




class   PROGRAM_YUV :public ProgramId
{
public:
    typedef int attribute; 
    typedef int uniform;
public:
    attribute   _position;
    attribute   _uv;
    uniform     _MVP;
    uniform     _textureY;
    uniform     _textureU;
    uniform     _textureV;
public:
    PROGRAM_YUV()
    {
        _position   =   -1;
        _uv         =   -1;
        _MVP        =   -1;
        _textureY   =   -1;
        _textureU   =   -1;
        _textureV   =   -1;
    }
    ~PROGRAM_YUV()
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
            "varying   vec2 _outUV;"

            "void main()"
            "{"
            "   _outUV  =   _uv;"
            "   vec4    pos =   vec4(_position,0,1);"
            "   gl_Position =   _MVP * pos;"
            "}"
        };
        const char* ps  =   
        {
            "precision  lowp float; "
            "uniform    sampler2D   _textureY;"
            "uniform    sampler2D   _textureU;"
            "uniform    sampler2D   _textureV;"
            "varying    vec2        _outUV;"
            "void main()"
            "{"
            "   vec3    yuv;"
            "   vec3    rgb;  "  
            "   yuv.x   =   texture2D(_textureY, _outUV).a;"
            "   yuv.y   =   texture2D(_textureU, _outUV).a - 0.5;"
            "   yuv.z   =   texture2D(_textureV, _outUV).a - 0.5;"
            "   rgb     =   mat3(   1,       1,         1,"
            "                       0,       -0.39465,  2.03210,"
            "                       1.13983, -0.58060,  0) * yuv;" 
            "   gl_FragColor = vec4(rgb, 1);"
            "}"
        };
        
        bool    res =   createProgram(vs,ps);
        if(res)
        {
            _position   =   glGetAttribLocation(_programId,"_position");
            _uv         =   glGetAttribLocation(_programId,"_uv");
            _textureY   =   glGetUniformLocation(_programId,"_textureY");
            _textureU   =   glGetUniformLocation(_programId,"_textureU");
            _textureV   =   glGetUniformLocation(_programId,"_textureV");
            _MVP        =   glGetUniformLocation(_programId,"_MVP");
        }
        return  res;
    }

    /**
    *   使用程序
    */
    virtual void    begin()
    {
        glUseProgram(_programId);
        glEnableVertexAttribArray(_position);
        glEnableVertexAttribArray(_uv);
        
    }
    /**
    *   使用完成
    */
    virtual void    end()
    {
        glDisableVertexAttribArray(_position);
        glDisableVertexAttribArray(_uv);
        glUseProgram(0);
    }
};

