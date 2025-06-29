
#!/usr/bin/env bash
export DYLD_INSERT_LIBRARIES=/usr/lib/libgmalloc.dylib
export MallocStackLogging=1

leaks --atExit -- ./miniRT "$@"
