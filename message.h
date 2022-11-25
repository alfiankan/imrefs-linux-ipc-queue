#ifndef MESSAGE
#define MESSAGE
#include <string>

struct Message
{
    long mtype;
    int payloadLength;
    char payload[1000];
};

#endif
