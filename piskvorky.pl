#!/usr/bin/perl -w

use strict;
use Gtk2;

use constant TRUE  => 1;
use constant FALSE => 0;

Gtk2->init();

my $window = Gtk2::Window->new;
$window->signal_connect (destroy => sub { Gtk2->main_quit; });

use vars qw($window);

my $vbox = Gtk2::VBox->new(FALSE, 0);
$window->add($vbox);

my $table = Gtk2::Table->new(20, 20, FALSE);
$vbox->pack_start_defaults($table);

my $Ocko = Gtk2::Gdk::Pixbuf->new_from_file("tic.xpm");
my $iXko = Gtk2::Gdk::Pixbuf->new_from_file("tac.xpm");

my @buttons = [];
for my $y (0..19) {
	my @row = [];
	for my $x (0..19) {
		my $button = Gtk2::Button->new(); #("Tlacitko $x $y");
		my $obrazek = Gtk2::Image->new_from_pixbuf($Ocko->scale_simple(16,16,'bilinear'));
		$button->set_image($obrazek);
		#$button->set_size_request(32,32);
		my @arr = [1,2];
		$button->signal_connect(clicked => \&button_clicked, \@arr);
		$table->attach_defaults($button, $x, $x+1, $y, $y+1);
		push(@row, $button);
	}
	push(@buttons, \@row);
}

my $button1 = Gtk2::Button->new("Tlacitko");


$window->show_all;
Gtk2->main;

sub button_clicked {
	my ($widget, $data) = @_;
	my $iXko = Gtk2::Gdk::Pixbuf->new_from_file("tac.xpm");
	my $obrazek = Gtk2::Image->new_from_pixbuf($iXko->scale_simple(16,16,'bilinear'));
		
	my @arr = @$data;

	my $v = $arr[0][0];
	my $dialog = Gtk2::Dialog->new ("A cool $v dialog",
                              $window,
                              [qw/modal destroy-with-parent/],
                              'gtk-ok'     => 'accept',
                              'gtk-cancel' => 'reject');
	$dialog->show;

	$widget->set_image($obrazek);
	
#	print "Clicked $x , $y\n";
}
