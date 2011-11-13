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

#my $menu = Gtk2::VBox->new(0,0);
#$vbox->pack_start_defaults($menu);

my $menu_hra = Gtk2::Menu->new;
$menu_hra->append(Gtk2::TearoffMenuItem->new);

my $hra_polozka = Gtk2::MenuItem->new("AAA");
$menu_hra->append($hra_polozka);

my $hra = Gtk2::MenuItem->new("_Hra");
$hra->set_submenu($menu_hra);

my $menubar = Gtk2::MenuBar->new;
$menubar->append($hra);

$vbox->pack_start_defaults($menubar);

my $table = Gtk2::Table->new(20, 20, FALSE);
$vbox->pack_start_defaults($table);

my $ctverecek = Gtk2::Gdk::Pixbuf->new_from_file("toe.xpm");
my $Ocko = Gtk2::Gdk::Pixbuf->new_from_file("tic.xpm");
my $iXko = Gtk2::Gdk::Pixbuf->new_from_file("tac.xpm");

my $maly_ctverecek = $ctverecek->scale_simple(16,16,'bilinear');
my $male_Ocko = $Ocko->scale_simple(16,16,'bilinear');
my $male_iXko = $iXko->scale_simple(16,16,'bilinear');

my @buttons = [];
for my $y (0..19) {
	my @row = [];
	for my $x (0..19) {
		my $button = Gtk2::Button->new(); #("Tlacitko $x 
		my $image = Gtk2::Image->new_from_pixbuf($maly_ctverecek);
		$button->set_image($image);
		#$button->set_size_request(32,32);
		my @arr = 1,2;
		$button->signal_connect(clicked => \&button_clicked, \@arr);
		$table->attach_defaults($button, $x, $x+1, $y, $y+1);
		push(@row, $button);
	}
	push(@buttons, \@row);
}

$window->show_all;
Gtk2->main;

sub button_clicked {
	my ($widget, $data) = @_;
	my $iXko = Gtk2::Gdk::Pixbuf->new_from_file("tac.xpm");
	my $obrazek = Gtk2::Image->new_from_pixbuf($iXko->scale_simple(16,16,'bilinear'));
		
	my @arr = @$data;

	my $v = $arr[0];
	my $dialog = Gtk2::Dialog->new ("A cool $v dialog",
                              $window,
                              [qw/modal destroy-with-parent/],
                              'gtk-ok'     => 'accept',
                              'gtk-cancel' => 'reject');
	$dialog->show;

	$widget->set_image($obrazek);
	
#	print "Clicked $x , $y\n";
}
