#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct Message
{
    long mtype;
    int year;
};

int interop_msgget(int key)
{
    key = key + 80;
    int msqid;
    msgget(key, 0600 | IPC_CREAT);
    return msgget(key, 0600 | IPC_CREAT);
}

int interop_msgsnd(int msqid, int year)
{
    struct Message msgp;
    msgp.year = year;
    msgp.mtype = 1;
    return msgsnd(msqid, &msgp, sizeof(msgp) - sizeof(long), 0);
}

void interop_msgrcv(int msqid)
{
    struct Message msgp;
    msgrcv(msqid, &msgp, sizeof(msgp) - sizeof(long), 1, 0);
    printf("Hurray getting %d from queue", msgp.year);
}
