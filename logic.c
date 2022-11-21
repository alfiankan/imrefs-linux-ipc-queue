#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct Message
{
    long mtype;
    int payloadLength;
    char payload[1000];
};

int interop_msgget(int key)
{
    key = key + 80;
    int msqid;
    msgget(key, 0600 | IPC_CREAT);
    return msgget(key, 0600 | IPC_CREAT);
}

int interop_msgsnd(const char payload[], int payloadLength, int msqid)
{
    struct Message msgp;
    msgp.mtype = 1;
    msgp.payloadLength = payloadLength;

    for (size_t i = 0; i < payloadLength; i++)
    {
        msgp.payload[i] = payload[i];
    }
    return msgsnd(msqid, &msgp, sizeof(msgp) - sizeof(long), 0);
}

char *interop_msgrcv(int msqid)
{
    struct Message msgp;
    msgrcv(msqid, &msgp, sizeof(msgp) - sizeof(long), 1, 0);
    char *payload = malloc(msgp.payloadLength);
    for (size_t i = 0; i < msgp.payloadLength; i++)
    {
        payload[i] = msgp.payload[i];
    }
    return payload;
}
