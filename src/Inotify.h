#ifndef _INOTIFY_H_
#define _INOTIFY_H_

#include <sys/inotify.h>

#include <vector>
#include <string>
#include <map>

std::string EVENT_NAME[12] =
{
    "IN_ACCESS",
    "IN_MODIFY",        //文件修改
    "IN_ATTRIB",
    "IN_CLOSE_WRITE",
    "IN_CLOSE_NOWRITE",
    "IN_OPEN",
    "IN_MOVED_FROM",    //文件移动from
    "IN_MOVED_TO",      //文件移动to
    "IN_CREATE",        //文件创建
    "IN_DELETE",        //文件删除
    "IN_DELETE_SELF",
    "IN_MOVE_SELF"
};

class Inotify
{
    public:
    Inotify();
    ~Inotify();

    bool Init();
    bool AddWatchEvent(const std::string& path, uint32_t event);
    bool HandleEvent();
    private:
    std::map<std::string, uint32_t> watch_dir_event_map_;
    //TODO 防止事件丢失
    //std::queue<inotify_event> InotifyEventQue;
    std::vector<int> watch_fd_vec_;
    int inotify_fd_;
    bool stop_; 
};

#endif
