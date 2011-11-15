#!/usr/bin/perl -w

package Piskvorky::Hra;

use strict;

sub new {
	my $class = shift;
	# jak se dělá proměnný počet atributů?
	my ($natahu, $polex, $poley, $field) = @_;
	validate_field($field);
	my %instance = {
		NA_TAHU => $natahu,
		POLE_X => $polex,
		POLE_Y => $poley,
		HERNI_POLE => create_field($polex,$poley)
	};
	return bless($instance, $class);
}

sub view_update {
	my $instance_ = shift;
	
}

sub model_updated {
	my $instance_ = shift;

}


