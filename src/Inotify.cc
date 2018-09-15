#include "Inotify.h"

#include <unistd.h>
#include <stddef.h>     /* offsetof */

#include <iostream>

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

Inotify::Inotify()
{
}

Inotify::~Inotify()
{
}

bool Inotify::Init()
{
    inotify_fd_ = inotify_init();
    if (inotify_fd_ < 0) {
        return false;
    } else {
        return true;
    }
}

bool Inotify::AddWatchEvent(const std::string& path, uint32_t event)
{
    int watch_fd = inotify_add_watch(inotify_fd_, path.c_str(), event);
    if (watch_fd < 0) {
        return false;
    } else {
        watch_dir_event_map_[path] = event;
        watch_fd_vec_.push_back(watch_fd);
        return true;
    }
}

void Inotify::Run()
{
    char buffer[4096] = {0};
    ssize_t read_num = 0, event_size = 0;
    struct inotify_event* current_event = nullptr;

    while (!stop_ && (read_num = read(inotify_fd_, buffer, 4096)) > 0) {
        size_t handled_num = 0;
        while (handled_num < read_num) {
            current_event = (struct inotify_event *)&buffer[handled_num];
            event_size = offsetof (struct inotify_event, name) + current_event->len;
            for (int i=0; i < 12; i++) {
                if ((current_event->mask >> i) & 1) {
                    if (current_event->len > 0)
                        std::cout << current_event->name <<  " --- " << EVENT_NAME[i] << std::endl;
                    else
                        std::cout << "  --- " << EVENT_NAME[i] << std::endl;
                }
            }
            handled_num += event_size;
        }
    }
}
