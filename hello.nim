import std/tempfiles
{.compile: "logic.c".}
proc interop_msgget(a: cint): cint {.importc.}



proc createQueue() =

  let (cfile, path) = createTempFile("imrefs", ".tmp")
  cfile.writeLine("alfiankan")
  echo path
  echo interop_msgget(121)

createQueue()
