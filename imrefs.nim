import std/tempfiles
import os, osproc, strformat
{.compile: "logic.c".}
proc interop_msgget(a: cint): cint {.importc.}



proc createQueue() =

  let (cfile, path) = createTempFile("imrefs", ".tmp")
  cfile.writeLine("alfiankan")
  echo path
  echo interop_msgget(121)

proc initFs() =
  echo 0

proc createNewFs(fsName: string): (int, string) =

  # create temp file
  let (cfile, tempFilePath) = createTempFile("imrefs", ".tmp")
  discard cfile
  const opts = {poUsePath, poDaemon, poStdErrToStdOut}
  var p = startProcess("./imrefs", "", ["start"], nil, opts)

  let pid = p.processID()

  # save pid
  let tmpDir = getTempDir()
  let pidsFileName = fmt"{tmpDir}imrefs.pids";
  echo pidsFileName
  if not fileExists(pidsFileName):
    writeFile(pidsFileName, "")
  let f = open(pidsFileName, fmAppend)
  f.write(fmt"{fsName}@{pid}@{tempFilePath}|")
  f.close()
  return (pid, tempFilePath)


proc cli(): int =

  if paramCount() == 0:
    echo "command not found"
    return -1;

  case paramStr(1):
    of "init":
      # imrefs init <fsname>
      let fsname: string = paramStr(2)
      let (pid, tempFilePath) = createNewFs(fsname)
      echo fmt"Filesystem {fsName} successfully created at {tempFilePath} with PID {pid}"
    of "send":
      # imrefs send <fsname> <payload>
      echo "send"
    of "stop":
      # imrefs stop <fsname>
      echo "send"
    of "start":
      # internal start process
      sleep(10000)
      echo "started"
    else:
      echo "command not found"
  return 1;

discard cli()
