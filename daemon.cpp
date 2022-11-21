#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>

int startFsSubscriber(void)
{
    pid_t pid, sid;

    pid = fork();
    if (pid > 0)
    {
        return pid;
    }
    else if (pid < 0)
    {
        return -1;
    }
    printf("Started with pid %d", pid);

    sleep(10);

    return pid;
}