{.compile: "logic.c".}
proc interop_msgrcv(a: cint) {.importc.}

proc subscribeQueue() =
  while true:
    interop_msgrcv(1)

subscribeQueue()
