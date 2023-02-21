#!/usr/bin/perl
#
# Splits the list of files and outputs for makefile type files
# wrapped at 80 chars
#
# Tom St Denis
use strict;
use warnings;

my @a = split ' ', $ARGV[1];
my $b = $ARGV[0] . '=';
my $len = length $b;
print $b;
foreach my $obj (@a) {
   $len = $len + length $obj;
   $obj =~ s/\*/\$/;
   if ($len > 100) {
      printf "\\\n";
      $len = length $obj;
   }
   print $obj . ' ';
}

print "\n\n";

# ref:         HEAD -> master, tag: v1.0.1
# git commit:  5953f62e42b24af93748b1ee5e1d062e242c2546
# commit time: 2017-08-29 22:27:36 +0200
