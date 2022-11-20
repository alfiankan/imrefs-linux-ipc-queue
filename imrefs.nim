import std/tempfiles
import os, osproc, strformat, strutils, cstrutils
{.compile: "logic.c".}
proc interop_msgget(a: int): int {.importc.}
proc interop_msgrcv(a: int): cstring {.importc.}


proc createQueue(pid: int): int =
  return interop_msgget(pid)

proc initFs() =
  echo 0

proc createNewFs(fsName: string): (int, string) =

  # create temp file
  let (cfile, tempFilePath) = createTempFile("imrefs", ".tmp")
  discard cfile
  const opts = {poUsePath, poDaemon, poStdErrToStdOut}
  var p = startProcess("./imrefs", "", ["start", fsName], nil, opts)

  let pid = p.processID()

  # save pid
  let tmpDir = getTempDir()
  let pidsFileName = fmt"{tmpDir}imrefs.pids";
  echo pidsFileName

  let msqid = createQueue(pid)

  if not fileExists(pidsFileName):
    writeFile(pidsFileName, "")
  let f = open(pidsFileName, fmAppend)
  f.write(fmt"{fsName}@{pid}@{msqid}@{tempFilePath}|")
  f.close()
  return (pid, tempFilePath)

proc getFsObj(fsName: string): (string, int, int, string) =
  let f = open("/tmp/imrefs.pids", fmRead)
  let all = f.readAll()

  var pid = 0;
  var msqid = 0;
  var path = "";

  let rows: seq[string] = split(all, "|")
  for row in rows:
    let cols: seq[string] = split(row, "@")
    if cols[0] == fsName:
      pid = parseInt(cols[1])
      msqid = parseInt(cols[2])
      path = cols[3]
      break

  f.close()

  return (fsname, pid, msqid, path)

proc subscribeQue(fsName: string) =
  # start long running process subscribe and write to tmp file
  let (fsname, pid, msqid, path) = getFsObj(fsName)

  while true:
    let payload: cstring = interop_msgrcv(msqid)
    echo payload
    let f = open(path, fmWrite)
    f.write(payload)
    f.close()

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
      subscribeQue(paramStr(2))
    else:
      echo "command not found"
  return 1;

discard cli()
