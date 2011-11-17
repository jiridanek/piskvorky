#!/usr/bin/perl -w

use strict;
use warnings;

use Board;

`cp startovni_plan tmp_plan`;

my @hrac;
$hrac[0] = shift;
$hrac[1] = shift;

my @hrac_s = ('O', 'X');

my $h = 0;
my $res = '-';

while ($res eq '-') {
    open my $fold_board, '<', 'tmp_plan' or die "Chybi soubor tmp_plan";
    
    my $turn = <$fold_board>;
    chomp($turn);
    if($turn ne $hrac_s[$h]) {
    	die "Spatny symbol, ma byt '$hrac_s[$h]', bylo '$turn'\n";
    }
    
    my $old_board = Board->new(20,20,$fold_board);
    
    my $cmd = "./$hrac[$h] <tmp_plan >tmp_plan2";
    print $cmd,"\n";
    `$cmd`;
    
    open my $fnew_board, '<', 'tmp_plan2';
    my $nturn = <$fnew_board>;
    chomp($nturn);
    if($nturn ne $hrac_s[1-$h]) {
    	my $op = $hrac_s[1-$h];
    	die "Spatny symbol, ma byt '$op', bylo '$nturn'\n";
    }
    
    my $new_board = Board->new(20,20,$fnew_board);
    
    my $diffs = Board->list_diffs($old_board, $new_board);
    
    my $podvodnik = undef;
    my $num = @$diffs;

    if(@$diffs > 1) {
    	$podvodnik = "Hrac $hrac_s[$h] hraje vicekrat:\n";
    }
    
    $new_board->pretty_print($diffs->[0]);
    
    if (defined $podvodnik) {
    	die $podvodnik;
    }
    
    `mv tmp_plan2 tmp_plan`;
#    my $foo='';	$foo = <>; # zakomentovat/odkomentovat tento radek, aby hra probehla bez cekani/s cekanim
    $h = 1 - $h;
    print `./piskvorky_decide <tmp_plan >tmp_res`;
    $res = `cat tmp_res`;
    chomp $res;
}

print "Vitez: ", ($res eq 'X'?$hrac[1]:$hrac[0]),"\n";
