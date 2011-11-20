#!/usr/bin/perl -w

use strict;
use warnings;

#use IO::Handle;
use IPC::Open2;
use Board;

my ($command) = shift;

my $symbol = <STDIN>;
chomp($symbol);

open my $stdin, "<&STDIN";
my $board = Board->new(20,20,$stdin);
print STDERR "Zadej souradnice, kam chces hrat\n>:";

my ($ox, $oy);

#close STDIN;

while(1) {
	open(STDIN, "zenity --entry |");
	#muze tady uviznout, ale snad ne
	$_ = <STDIN>;
	print STDERR $_;
	chomp($_);
	if($_ =~ /^\d*,\d*/) {
		my @m = $_ =~ /(^\d*),(\d*)/;
		$ox = $m[0];
		$oy = $m[1];
		last;
	}
}

die "nedals tah, koncim" unless defined $ox;


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
