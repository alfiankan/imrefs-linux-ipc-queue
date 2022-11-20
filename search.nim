import os, strutils

proc search(fsName: string): (string, int, int, string) =
    let f = open("/tmp/imrefs.pids", fmRead)
    let all = f.readAll()

    var pid = 0;
    var msqid = 0;
    var path = "";

    let rows: seq[string] = split(all, "|")
    for row in rows:
        echo row
        let cols: seq[string] = split(row, "@")
        if cols[0] == fsName:
            pid = parseInt(cols[1])
            msqid = parseInt(cols[2])
            path = cols[3]
            break

    f.close()

    return (fsname, pid, msqid, path)

let (fsname, pid, msqid, path) = search("book")

echo fsname, pid, msqid, path
