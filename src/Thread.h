#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include <pthread.h>

//放到类外公共使用
enum ThreadState {
    THREAD_STATUS_NEW,
    THREAD_STATUS_RUNNING,
    THREAD_STATUS_EXIT
};

class Thread
{
public:

    //构造函数
    Thread();
    //析构函数
    virtual ~Thread();
    //线程的运行实体
    virtual void Run()=0;
    //开始执行线程
    bool Start();
    //获取线程ID
    pthread_t GetThreadID();
    //获取线程状态
    ThreadState GetState();
    //等待线程直至退出
    void Join();

    private:
    //当前线程的线程ID
    pthread_t pid_;
    //线程的状态
    ThreadState state_;
    //获取执行方法的指针
    static void * ThreadProxyFunc(void * args);
};

#endif
