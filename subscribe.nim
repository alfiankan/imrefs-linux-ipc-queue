{.compile: "logic.c".}
proc interop_msgrcv(a: cint) {.importc.}

proc subscribeQueue() =
  interop_msgrcv(1)

subscribeQueue()
