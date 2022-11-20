{.compile: "logic.c".}
proc interop_msgsnd*(payload: cstring, payloadLength: int,
    msqid: cint): cint {.importc.}

proc publishQueue() =
  let greeting: cstring = "Alfiankan nur fathoni"
  echo interop_msgsnd(greeting, len(greeting), 1)

publishQueue()
