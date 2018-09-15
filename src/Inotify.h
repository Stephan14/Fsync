#ifndef _INOTIFY_H_
#define _INOTIFY_H_

#include <sys/inotify.h>

#include <vector>
#include <string>
#include <map>

#include "Thread.h"

extern std::string EVENT_NAME[12];

class Inotify: public Thread
{
    public:
    Inotify();
    ~Inotify();

    bool Init();
    bool AddWatchEvent(const std::string& path, uint32_t event);
    virtual void Run();
    private:
    std::map<std::string, uint32_t> watch_dir_event_map_;
    //TODO 防止事件丢失
    //std::queue<inotify_event> InotifyEventQue;
    std::vector<int> watch_fd_vec_;
    int inotify_fd_;
    bool stop_;
};

#endif
