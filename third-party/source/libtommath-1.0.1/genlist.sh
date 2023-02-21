#!/bin/bash

export a=`find . -maxdepth 1 -type f -name '*.c' | sort | sed -e 'sE\./EE' | sed -e 's/\.c/\.o/' | xargs`
perl ./parsenames.pl OBJECTS "$a"

# ref:         HEAD -> master, tag: v1.0.1
# git commit:  5953f62e42b24af93748b1ee5e1d062e242c2546
# commit time: 2017-08-29 22:27:36 +0200
