{.compile: "logic.c".}
proc interop_msgsnd(a: cint, b: cint): cint {.importc.}

proc publishQueue() =
  echo interop_msgsnd(1, 2022)

publishQueue()
