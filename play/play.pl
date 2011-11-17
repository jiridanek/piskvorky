#!/usr/bin/perl -w

use strict;

`cp startovni_plan tmp_plan`;

my @hrac;
$hrac[0] = shift;
$hrac[1] = shift;

my $h = 0;
my $res = '-';

while ($res eq '-') {
    my $cmd = "./$hrac[$h] <tmp_plan >tmp_plan2";
    print $cmd,"\n";
    `$cmd`;
    `mv tmp_plan2 tmp_plan`;
    print `cat tmp_plan`;
#    my $foo='';	$foo = <>; # zakomentovat/odkomentovat tento radek, aby hra probehla bez cekani/s cekanim
    $h = 1 - $h;
    print `./piskvorky_decide <tmp_plan >tmp_res`;
    $res = `cat tmp_res`;
    chomp $res;
}

print "Vitez: ", ($res eq 'X'?$hrac[1]:$hrac[0]),"\n";
