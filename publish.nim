import os, strutils
{.compile: "logic.c".}
proc interop_msgsnd*(payload: cstring, payloadLength: int,
    msqid: int): cint {.importc.}

proc publishQueue() =
  let greeting: cstring = paramStr(2)
  echo interop_msgsnd(greeting, len(greeting), parseInt(paramStr(1)))

publishQueue()
