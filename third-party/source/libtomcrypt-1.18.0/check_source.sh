#!/bin/bash

# output version
bash printinfo.sh

make clean > /dev/null

echo "checking..."
./helper.pl --check-source --check-makefiles --check-defines|| exit 1

exit 0

# ref:         HEAD -> master, tag: v1.18.0
# git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f
# commit time: 2017-10-10 15:51:36 +0200
