#ifndef FSSTAT
#define FSSTAT
#include <string>

struct FsStat
{
    std::string fsName;
    int pid;
    std::string tempFilePath;
    int msqid;
};

#endif
