#!/usr/bin/perl -w

use strict;
use warnings;

#use IO::Handle;
use IPC::Open2;
use Board;

my ($command) = shift;
my ($chld_out,$chld_in);

my $pid = open2($chld_out, $chld_in, $command);

#my $symbol = 'O';
my $symbol = <STDIN>;
chomp($symbol);


open my $stdin, "<&STDIN";
close STDIN;
my $board = Board->new(20,20,$stdin);
print $chld_in "START 20\n";
print $chld_in "INFO timeout_turn 2500\n";
print $chld_in "BOARD\n";
			
for (my $x=0; $x<20; $x++) {
	for (my $y=0; $y<20; $y++) {
		my $ch = $board->get($x,$y);
		if ('X' eq $ch || 'O' eq $ch) {
			my $num;
			if ($ch eq $symbol) {
				$num = 1;
			} else {
				$num = 2;
			}
			print STDERR "$x,$y,$num\n";
			$chld_in->printflush("$x,$y,$num\n");
		}
	}
}


	
$chld_in->printflush("DONE\n");

my ($ox, $oy);

#muze tady uviznout, ale snad ne
while (<$chld_out>) {
	print STDERR $_;
	chomp($_);
	if($_ =~ /^\d*,\d*/) {
		my @m = $_ =~ /(^\d*),(\d*)/;
		$ox = $m[0];
		$oy = $m[1];
		last;
	}
}

$chld_in->printflush("END\n");

die "nedalo tah, koncim" unless defined $ox;


$board->put($ox, $oy, $symbol);
if ($symbol eq 'X') {
	$symbol = 'O';
} else {
	$symbol = 'X';
}
print $symbol."\n";
$board->print();
STDOUT->printflush("\n");

END { close(STDOUT) || die "can't close stdout: $!" }
