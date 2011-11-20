package Board;

use strict;
use warnings;

use constant TRUE => 1;
use constant FALSE => 0;

my $UNDEF = 'F';
my $BOARD_EMPTY = '.';

sub new {
	my ($class, $x, $y, $filedesc) = @_;
	my $board;
	if (defined $filedesc) {
		$board = Board->init_board_from_filedesc($x, $y, $filedesc);
		
	} else {
		$board = Board->init_board_empty($x, $y);
	}
	my $self = {
		WIDTH => $x,
		HEIGHT => $y,
		BOARD => $board,
		MOVES => []
	};
	return bless($self, $class);
}

sub list_diffs {
	my ($class, $insta, $instb) = @_;
	my $h_a = $insta->{HEIGHT};
	my $w_a = $insta->{WIDTH};
	my $h_b = $instb->{HEIGHT};
	my $w_b = $instb->{WIDTH};
	
	return undef if $h_a != $h_b;
	return undef if $w_a != $w_b;
	
	my @diffs;
	
	for (my $y=0; $y < $h_a; $y++) {
		for (my $x=0; $x<$w_a; $x++){	
			if ($insta->get($x,$y) ne $instb->get($x, $y)) {
				push(@diffs, [$x, $y]);
			}
		}
	}
	return \@diffs;
	
}

sub init_board_empty {
	my ($class, $x, $y) = @_;
	my @board;
	for ($a=0; $a < $x; $a++) {
		my @column;
		for ($b=0; $b < $y; $b++) {
			push(@column, $BOARD_EMPTY);
		}
		push(@board, \@column);
	}
	return \@board;
}

sub init_board_from_filedesc {
	my ($class, $x, $y, $filedesc) = @_;
	my $board = Board->init_board_empty($x, $y);
	my $a = 0;
	my $b = 0;
	while (<$filedesc>) {
		my $line_length = length($_);
		for(my $i=0; $i<$line_length-1; $i++) {
			my $ch = substr($_, $i, 1);
			if ('.' ne $ch) {
				$board->[$a][$b] = $ch;
			}
			$a++;
			if ($a >= $x) {
				$a = 0;
				$b++;
				if ($b >= $y) {
					return $board;
				}
			}
		}
	}
	return $board;
}

sub can_get {
	my ($self, $x, $y) = @_;
	return $x >= 0 && $x < $self->{WIDTH}
		&& $y >= 0 && $y < $self->{HEIGHT};
}

sub get {
	my ($self, $x, $y) = @_;
	if (! $self->can_get($x, $y)) {
		return $UNDEF;
	} else {
		return $self->{BOARD}->[$x][$y];
		my $board = $self->{BOARD};
		my $column = @{$board}[$x];
		return ${$column}[$y];
	}
}

sub put {
	my ($self, $x, $y, $val) = @_;
	unless ($self->can_get($x, $y)) {
		return FALSE;
	} else {
		$self->{BOARD}->[$x][$y] = $val;
		return TRUE;
	}
}

sub print {
	my ($self) = @_;
	
	for (my $y=0; $y < $self->{HEIGHT}; $y++) {
		for (my $x=0; $x<$self->{WIDTH}; $x++){	
			my $ch = $self->get($x, $y);
			print $ch;
		}
		print("\n");
	}
}

sub pretty_print {
	my ($self, $last, $outstream) = @_;
	
	my $PRETTY_BOARD_EMPTY = '•';
	
	## http://forums.fedoraforum.org/archive/index.php/t-5467.html
	my $ESC = "\033";
	my $fmagenta = $ESC . '[35m';
	my $fcyan = $ESC. '[36m';
	my $bold = $ESC . '[1m'; #$ESC . '[1;40m' .
	my $fgray = $ESC . '[1;30m';
	my $reset = $ESC . '[0m';
	
	my $lastx = -1;
	my $lasty = -1;
	$outstream = *STDOUT unless defined $outstream;
	if (defined $last) {
		 $lastx = $last->[0];
		 $lasty = $last->[1];
	}
	
	print $outstream "  ";
	for (my $j=0; $j<$self->{WIDTH}; $j++){
	printf $outstream ("%2s", $j);
	}
	print $outstream "\n";
	for (my $y=0; $y < $self->{HEIGHT}; $y++) {
		printf $outstream ("%2s ", $y);
		for (my $x=0; $x<$self->{WIDTH}; $x++){	
			if ($x == $lastx && $y == $lasty) {
				print $outstream $bold;
			}
			my $ch = $self->get($x, $y);
			$ch = $PRETTY_BOARD_EMPTY if $ch eq $BOARD_EMPTY;
			if ($ch eq "X")  {
				print $outstream $fmagenta;
			}
			if ($ch eq 'O') { 
				print $outstream $fcyan;
			}
			if ($ch eq $BOARD_EMPTY) {
				print $outstream $fgray;
			}
			print $outstream $ch . " " . $reset;
		}
		print $outstream "\n";
	}
}
			

sub validate {
	my $self = shift;
	for (my $x=0; $x<$self->{WIDTH}; $x++) {
		for (my $y=0; $y < $self->{HEIGHT}; $y++) {
			my $char = $self->get($x, $y);
			if ('OX.' !~ /$char/) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

# E, SE, S, SW
my $DIRX = [1, 1, 0, -1];
my $DIRY = [0, -1, -1, -1];

sub winner {
	return;
}

sub count {
	return;
}

sub printer_apply {
	my ($val) = @_;
	print($val);
}

sub validator_apply {
	my ($val) = @_;
	return $val =~ m/OX./;
}

sub validator_fold {
	my ($sum, $new) = @_;
	return $new if $sum == undef;
	return $sum && $new;
}

sub apply_fold {
	my ($self, $apply, $fold) = @_;
	my $sum = undef;
	for (my $x=0; $x<$self->{WIDTH}; $x++) {
		for (my $y=0; $y < $self->{HEIGHT}; $y++) {
			$sum = $fold->($sum, $apply->($self->get($x, $y), $x, $y));
		}
	}
}



TRUE;
