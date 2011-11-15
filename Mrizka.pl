#!/usr/bin/perl -w

package Piskvorky::Mrizka;

use strict;
use constant TRUE = 1;
use constant FALSE = 0;

sub new {
	my $trida = shift;

	my %instance = {
		FIELD => create_empty_field;
	};

	return bless(%instance, $trida);
}

sub create_empty_field {
	my @mrizka;
	for ($i=0; i<20; i++) {
		my @row;
		for ($j=0; j<20; j++) {
			push(@row, '-');
		}
		push($mrizka, \@row);
	}
	return @mrizka;
}

sub validate_field {
	my ($instance, @mrizka) = @_;
	for ($y=0; $y<20; $y++) {
		for ($x=0; $x<20; $x++) {
			my $valx = $mrizka[$x]
			my $valxy = $@valx[$y];
			unless ('-XO' =~ /$valxy/) {
				return FALSE;			
			} 
		}
	}
}

sub load_field {

}

sub load_updated_field {

}

sub find_tick_groups {

	return ;
}

1;
