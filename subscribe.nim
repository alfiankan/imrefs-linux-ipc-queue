{.compile: "logic.c".}
proc interop_msgrcv(a: cint): cstring {.importc.}

proc subscribeQueue() =
  while true:
    echo interop_msgrcv(1)

subscribeQueue()
