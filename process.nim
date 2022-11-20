import std/osproc
import os


const opts = {poUsePath, poDaemon, poStdErrToStdOut}

var p = startProcess("sleep", "", ["10"], nil, opts)

echo p.processID()

