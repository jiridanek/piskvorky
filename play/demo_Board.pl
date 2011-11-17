#!/usr/bin/perl -w

use strict;
use warnings;
use Board;

open(my $infile, "<", "testovaci_mapy/ab_debilne_prohraje.txt");

#my $board = Board->init_board_from_filedesc(20, 20, $infile);
#print $board->[5][5];

my $b = Board->new(20,20, $infile);
print $b->can_get(19,19) . "\n";
$b->put(10,10,'X');
print $b->get(10,10) . "\n";
$b->pretty_print();
print $b->validate();

