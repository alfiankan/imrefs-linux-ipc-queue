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
#include <cstdio>
#include <signal.h>
#include "daemon.cpp"
#include "stats.cpp"
#include "fsstat.h"

bool createTempFile(std::string *tempName)
{
    char temp[] = "/tmp/imrefsXXXXXX";
    int stat = mkstemp(temp);
    if (stat < 0)
    {
        return false;
    }
    *tempName = temp;

    return true;
}

int main(int argc, char *argv[])
{

    if (argv[1] == std::string("init"))
    {
        std::string tempFileName;
        if (createTempFile(&tempFileName) == 0)
        {
            printf("fail creating tempfile");
        }

        struct FsStat fsStat;
        fsStat.tempFilePath = tempFileName;
        fsStat.fsName = std::string(argv[2]);

        // create que
        const int key = 100;
        int msqid;
        msqid = msgget(key, 0600 | IPC_CREAT);
        if (msqid < 0)
        {
            return -1;
        }
        fsStat.msqid = msqid;

        // start que listener
        int pidn = startFsSubscriber(fsStat.fsName, fsStat.tempFilePath, fsStat.msqid);

        saveStat(fsStat.fsName, fsStat.msqid, fsStat.tempFilePath, pidn);

        printf("Filesystem %s successfully created at %s with PID %d \n", fsStat.fsName.c_str(), fsStat.tempFilePath.c_str(), pidn);
    }
    else if (argv[1] == std::string("send"))
    {

        const FsStat fsStat = getStat(std::string(argv[2]));
        std::string messages = std::string(argv[3]);

        struct Message msg;
        msg.mtype = 1;
        msg.payloadLength = messages.length();

        for (size_t i = 0; i < msg.payloadLength; i++)
        {
            msg.payload[i] = messages.at(i);
        }

        if (msgsnd(fsStat.msqid, &msg, sizeof(msg) - sizeof(long), 0) < 0)
        {
            printf("Failed write data to %s \n", fsStat.tempFilePath.c_str());
        }
        else
        {
            printf("Data successfully written at %s \n", fsStat.tempFilePath.c_str());
        }
    }
    else if (argv[1] == std::string("stop"))
    {
        std::string fsName = std::string(argv[2]);
        if (isStatExist(fsName))
        {
            const FsStat fsStat = getStat(fsName);
            deleteStat(fsName);
            kill(fsStat.pid, SIGTERM);
            printf("Filesystem %s stopped \n", fsStat.fsName.c_str());
        }
        else
        {
            printf("Filesystem %s doesnt exist \n", fsName.c_str());
        }
    }

    return 0;
}