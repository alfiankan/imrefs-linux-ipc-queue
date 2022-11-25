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
#include <fstream>
#include <vector>
#include <sys/msg.h>
#include "fsstat.h"
#include "message.h"

int save(const char *temFilePath, std::string content)
{
    std::ofstream ofs(temFilePath, std::ios::trunc);
    ofs << content.c_str() << std::endl;
    ofs.close();
}

int startFsSubscriber(std::string fsName, std::string temFilePath, int msqid)
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

    while (true)
    {
        struct Message msgp;
        msgrcv(msqid, &msgp, sizeof(msgp) - sizeof(long), 1, 0);

        std::string result;
        for (size_t i = 0; i < msgp.payloadLength; i++)
        {
            result.push_back(msgp.payload[i]);
        }
        save(temFilePath.c_str(), result);
    }

    return pid;
}