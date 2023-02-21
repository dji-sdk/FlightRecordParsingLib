#!/usr/bin/perl

# we want to filter every between START_INS and END_INS out and then insert crap from another file (this is fun)

use strict;
use warnings;

open(my $src, '<', shift);
open(my $ins, '<', shift);
open(my $tmp, '>', 'tmp.delme');

my $l = 0;
while (<$src>) {
   if ($_ =~ /START_INS/) {
      print {$tmp} $_;
      $l = 1;
      while (<$ins>) {
         print {$tmp} $_;
      }
      close $ins;
   } elsif ($_ =~ /END_INS/) {
      print {$tmp} $_;
      $l = 0;
   } elsif ($l == 0) {
      print {$tmp} $_;
   }
}

close $tmp;
close $src;

# ref:         HEAD -> master, tag: v1.0.1
# git commit:  5953f62e42b24af93748b1ee5e1d062e242c2546
# commit time: 2017-08-29 22:27:36 +0200
