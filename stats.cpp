#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "fsstat.h"

FsStat tokenizer(const char *s, char *delim)
{
    char *ptr = strtok((char *)s, delim);

    std::vector<std::string> token;
    while (ptr != NULL)
    {
        token.push_back(ptr);
        ptr = strtok(NULL, delim);
    }
    struct FsStat fsStat;
    // std::cout << token.size() << std::endl;
    if (token.size() > 0)
    {
        fsStat.fsName = token[0];
        fsStat.msqid = std::stoi(token[1]);
        fsStat.tempFilePath = token[2];
        fsStat.pid = std::stoi(token[3]);
    }

    return fsStat;
}

bool saveStat(std::string fsName, int pid, std::string tempFilePath, int msqid)
{
    std::ofstream ofs("/tmp/imrefs_stat.tmp", std::ofstream::app);
    ofs << fsName << "@" << pid << "@" << tempFilePath << "@" << msqid << "@" << std::endl;
    ofs.close();
}

bool isStatExist(std::string fsName)
{
    std::ifstream statFile;
    statFile.open("/tmp/imrefs_stat.tmp");
    std::string line;
    if (statFile.is_open())
    {
        while (statFile)
        {
            const char *s;
            std::getline(statFile, line);
            s = line.c_str();
            struct FsStat fsStat = tokenizer(s, "@");
            if (fsStat.fsName.compare(fsName) == 0)
            {
                return true;
            }
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }
    return false;
}

bool deleteStat(std::string fsName)
{
    std::vector<FsStat> newLines;
    std::ifstream statFile;
    statFile.open("/tmp/imrefs_stat.tmp");
    std::string line;
    if (statFile.is_open())
    {
        while (statFile)
        {
            const char *s;
            std::getline(statFile, line);
            s = line.c_str();
            struct FsStat fsStat = tokenizer(s, "@");
            if (fsStat.fsName.compare(fsName) != 0)
            {
                newLines.push_back(fsStat);
            }
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }

    // trunct
    std::ofstream ofs("/tmp/imrefs_stat.tmp", std::ios::trunc);
    ofs << "";
    ofs.close();
    if (newLines.size() > 0)
    {
        for (size_t i = 0; i < newLines.size(); i++)
        {
            if (!newLines[i].fsName.empty())
            {
                saveStat(newLines[i].fsName, newLines[i].pid, newLines[i].tempFilePath, newLines[i].msqid);
            }
        }
    }
}

FsStat getStat(const std::string fsName)
{
    std::ifstream statFile;
    statFile.open("/tmp/imrefs_stat.tmp");
    std::string line;
    if (statFile.is_open())
    {
        while (statFile)
        {
            const char *s;
            std::getline(statFile, line);
            s = line.c_str();
            struct FsStat fsStat = tokenizer(s, "@");
            if (fsStat.fsName.compare(fsName) == 0)
            {
                return fsStat;
            }
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }
    return FsStat();
}
