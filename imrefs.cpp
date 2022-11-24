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
#include "daemon.cpp"
#include "stats.cpp"

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
    std::cout << argv[1] << std::endl;

    if (argv[1] == std::string("init"))
    {
        std::string tempFileName;
        if (createTempFile(&tempFileName) == 0)
        {
            printf("fail creating tempfile");
        }

        saveStat(std::string(argv[2]), 0, tempFileName, 0);

        printf("Filesystem myfs1 successfully created at %s with PID 123 \n", tempFileName.c_str());
    }
    else if (argv[1] == std::string("send"))
    {
        getStat("myfs");
        printf("Data successfully written at /tmp/file1234.tmp \n");
    }
    else if (argv[1] == std::string("stop"))
    {
        printf("Filesystem myfs1 stopped \n");
    }
    return 0;
    // int pid = startFsSubscriber();
    // std::cout << "PID : " << pid;
}