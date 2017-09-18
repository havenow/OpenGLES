#pragma once

#include <windows.h>

class   Thread
{
public:
    DWORD           _threadId;
    HANDLE          _thread;
protected:
   
    /**
    *   �߳���ں���
    */
    static  DWORD    CALLBACK threadEnter(void* pVoid)
    {
        Thread* pThis   =   (Thread*)pVoid;
        if (pThis)
        {
            pThis->run();
        }
        return  0;
    }
public:
    Thread()
    {
        _thread     =   0;
        _threadId   =   0;
    }
    virtual ~Thread()
    {
        join();
    }
   
    virtual bool    run()
    {
        return  true;
    }
    /**
    *   �����̺߳���
    */
    virtual bool    start()
    {
        if (_thread != 0)
        {
            return  false;
        }
        else
        {
            //HIGH_PRIORITY_CLASS
            _thread     =   CreateThread(0,0,&Thread::threadEnter,this,0,&_threadId);
            return  true;
        }
    }
    /**
    *   �ȴ��˳�����
    */
    virtual void    join()
    {
        if (_thread)
        {
            WaitForSingleObject(_thread,0xFFFFFFFF);
            CloseHandle(_thread);
            _thread     =   0;
        }
    }
};