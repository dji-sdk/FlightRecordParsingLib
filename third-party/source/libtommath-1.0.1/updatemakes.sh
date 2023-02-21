#!/bin/bash

bash genlist.sh > tmplist

perl filter.pl makefile tmplist
sed -e 's/ *$//' < tmp.delme > makefile
rm -f tmp.delme

perl filter.pl makefile.icc tmplist
sed -e 's/ *$//' < tmp.delme > makefile.icc
rm -f tmp.delme

perl filter.pl makefile.shared tmplist
sed -e 's/ *$//' < tmp.delme > makefile.shared
rm -f tmp.delme

perl filter.pl makefile.cygwin_dll tmplist
sed -e 's/ *$//' < tmp.delme > makefile.cygwin_dll
rm -f tmp.delme

perl filter.pl makefile.bcc tmplist
sed -e 's/\.o /.obj /g' -e 's/ *$//' < tmp.delme > makefile.bcc
rm -f tmp.delme

perl filter.pl makefile.msvc tmplist
sed -e 's/\.o /.obj /g' -e 's/ *$//' < tmp.delme > makefile.msvc
rm -f tmp.delme

rm -f tmplist

# ref:         HEAD -> master, tag: v1.0.1
# git commit:  5953f62e42b24af93748b1ee5e1d062e242c2546
# commit time: 2017-08-29 22:27:36 +0200
