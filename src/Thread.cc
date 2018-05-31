#include "Thread.h"  
  
#include <assert.h>
  
Thread::Thread()  
{  
    pid_ = 0;  
    state_ = THREAD_STATUS_NEW;  
}  
  
bool Thread::Start()  
{  
    if (pthread_create(&pid_, nullptr, ThreadProxyFunc, this) == 0) {
        state_ = THREAD_STATUS_RUNNING;
        return true;
    } else {
        return false;
    }
}  
  
pthread_t Thread::GetThreadID()  
{  
    return pid_;  
}  
  
ThreadState Thread::GetState()  
{  
    return state_;  
}  
  
void Thread::Join()  
{  
    if (pid_ > 0)  
    {  
        pthread_join(pid_, nullptr);  
    }  
}  

void * Thread::ThreadProxyFunc(void * args)  
{  
    Thread * pthread = static_cast<Thread *>(args);   
    assert(pthread != nullptr);
    pthread->Run();   
    return nullptr;   
}  
  
Thread::~Thread()
{
}
