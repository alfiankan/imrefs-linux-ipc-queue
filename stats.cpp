#include <string>
#include <fstream>
#include <iostream>

struct FsStat
{
    int pid;
    std::string fsName;
    std::string tempFilePath;
    int msqid;
};

bool saveStat(std::string fsName, int pid, std::string tempFilePath, int msqid)
{
    std::ofstream ofs("/tmp/imrefs_stat.tmp", std::ofstream::app);
    ofs << fsName << "@" << pid << "@" << tempFilePath << "@" << msqid << "@" << std::endl;
    ofs.close();
}

bool isStatExist(std::string fsName)
{
}

bool deleteStat(std::string fsName)
{
}

FsStat getStat(std::string fsName)
{
}
