import os
{.compile: "logic.c".}
proc interop_msgget(a: cint): cint {.importc.}

proc createQueue() =
  echo interop_msgget(12345)
  sleep(300000)

createQueue()
