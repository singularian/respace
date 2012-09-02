#!/usr/bin/perl

   use IO::Dir;
   use Switch;
   use POSIX qw (ceil floor);

   my $filename;
   my $numArgs;
   my $var, $rng_num;
   my %dictionary;
   local %matchstack;

   $filename = $ARGV[0];
   $numArgs = $#ARGV + 1;
   # display number of args
   # print "thanks, you gave me $numArgs command-line arguments.\n";
   # foreach $argnum (0 .. $#ARGV) {
   #    print "$ARGV[$argnum]\n";
   # }

   #%dictionary = load_dictionary();
   %dictionary = load_dictionary2();
   # display_dictionary(%dictionary);
   # display_dictionary_size(%dictionary);
   # interpreter();
   # test_interpreter($line_test, %dictionary);
   # test_fetch_dictionary(%dictionary);
   # print "$filename\n";

   if ($filename ne "") { 
       process_file($filename, %dictionary);
       # process_fileb($filename, %dictionary);
      }

#
# process a script file line by line
#
sub process_file {
    my ($filename, %dictionary) = @_;
    # print "$filename\n";
    open(INPUT, $filename) or die "Can't open $filename";
     while ($line = <INPUT>) {
       # print $line;
       # $line =~ s/\n//;
       # if ($line ne "") {
          test_interpreter($line, %dictionary);
       #   }
      }
    close(INPUT);

}

#
# load the entire file into a string
# process a script file in memory
#
sub process_fileb {
    my ($filename, %dictionary) = @_;
    my $file;
    # print "$filename\n";
    open(INPUT, "< $filename") or die "Can't open $filename";
       local $/ = undef;
       $file = <INPUT>;
       # print $file;
       test_interpreter($file, %dictionary);
    close(INPUT);
                                                                                                                                               
}

#
# load the file into an array
#
sub load_file_array {
    my ($filename, %dictionary) = @_;
    my @file;
    # print "$filename\n";
    open(INPUT, "< $filename") or die "Can't open $filename";
       @file = <INPUT>;
       print @file;
    close(INPUT);
                                                                                                                                               
}

#
# Complex tag interpreter -- test version
#
sub test_interpreter {
my ($line, %dictionary) = @_;
my $val;
my $token;
my $i, $j, $k, $beg, $end, $word;

chop($line);
$val = $line;

print "\nString $val line $line\n";
# $val =~ s/\n/ /g;
#     while ($val) {
#     }
	for ($i = 0; $i <= length($val); $i++)
	{
	    for ($j = 0; $j <= length($val); $j++)
	    {
	    	$k = $j - $i;
		$word = substr($val, $i, $k);
		print "substring $i $j $word\n";	
		# print "$word\n";
		# $dictionary{"vb1"},
		#if ($j >= $i) {
		if ($j >= $i) {	
			if ($word ne "") {
			isword2($i, $j, $word, %dictionary);
			ispun($i, $j, $word, %dictionary);
			}
		}
	    }
	}
	print "\n";
	foreach $key (sort keys %matchstack)
	{
		print "matchstack (", $matchstack{$key}{"s"};
		print ",", $matchstack{$key}{"e"}, ") ";
		print $matchstack{$key}{"num"}, " ";
		print $matchstack{$key}{"word"};
		print "\n";
	}
	#print  "matchstack", %matchstack, "\n"; 
	delete @matchstack{keys %matchstack};	
}

#
## Test Fetch a word from the dictionary
##
sub isword {
    my ($i, $j, $word, %dictionary) = @_;
    my $result = 0;
    my $low = 0;
    my $middle = 0;
    # my $high = keys(%dictionary) - 1;
    my $high = keys(%dictionary);
    my $found = 0;
    my $key;


    while ($low <= $high)
    {
	$middle = floor(($low + $high) / 2);
	 print "isword $high $middle $low ";
	$result = (lc($word) cmp lc($dictionary{"$middle"}));
	#if ($word eq $dictionary{"$middle"}) {
 	if ($result == 0) { 	
		print "Found $word: " . $dictionary{"$middle"} . "\n";
		$found = $middle;
		$key = "$i" . "," . "$j";
		if (!exists $matchstack{$key}) {
		$matchstack{$key}{"s"} = $i;
		$matchstack{$key}{"e"} = $j;
		$matchstack{$key}{"num"} = $middle;
		$matchstack{$key}{"word"} = $word;
		}
		return ($middle);
		$low = $high +1;	
	}
	elsif ( $result < 0) {
	# elsif ($word lt $dictionary{"$middle"}) {	
		$high = $middle - 1;
		 print "Not found A $word: " . $dictionary{"$middle"} . " \n";
	}
	elsif ( $result > 0) {
	 print "Not found B $word: " . $dictionary{"$middle"} . " \n";
		$low = $middle + 1;
	}
    }
    return($found);
}

sub isword2 {
 my ($i, $j, $word, %dictionary) = @_;
  $key = "$i" . "," . "$j";
	if (exists $dictionary{lc($word)}) {
	print "Found $word\n";
		if (!exists $matchstack{$key}) {
                $matchstack{$key}{"s"} = $i;
		$matchstack{$key}{"e"} = $j;
                $matchstack{$key}{"num"} = 0;
		$matchstack{$key}{"word"} = $word;
		}
	}
}

sub ispun {
   my ($i, $j, $word, %dictionary) = @_;
   my $key;
	 if ( $word =~ /^[\.\!]/ )
	 {
         print "Found punctuation $word\n";
	 $key = "$i" . "," . "$j";
	 if (!exists $matchstack{$key}) { 
	 	$matchstack{$key}{"s"} = $i;
	 	$matchstack{$key}{"e"} = $j;
	 	$matchstack{$key}{"num"} = 0;
	 	$matchstack{$key}{"word"} = $word;
	 	}
	 }


}

#
# Test Fetch a word from the dictionary
#
sub test_fetch_dictionary {
    my (%dictionary) = @_;
    print "\ntest fetch from dictionary function ", $dictionary{"vb1"}, " \n"; 
}

#
# display the dictionary
#
sub display_dictionary {
   my (%dictionary) = @_;
   my $key;

   print "\nDisplaying Dictionary!";

   foreach $key (sort keys %dictionary)
   {
     print "\nitem $key ", $dictionary{$key};
   }
   print "\n";

}

#
# display size of the dictionary
#
sub display_dictionary_size {
      my (%dictionary) = @_;
      print "\nDictionary Size = " . keys(%dictionary) . "\n";

}


#
# Load the dictionary
#
sub load_dictionary {
     my $line;
     my $file;
     $file = "dictionary.txt";
     open (NEWFILE, "$file") or die "Can't open filename";

     while ($line = <NEWFILE>) {
       # print $line;
       $line =~ s/\n//;
       if ($line ne "") {
           # $key = 
           $key .= $j;
           # print "keys $key\n"; 
           $dict{$key} = $line;
           $key = "";
           $j++; # increment word count
          }
          $dict{$token} = $j;
      }
      # increment total dictionary word count
     close(NEWFILE);
     $j = 0;
 #   }
 # }

  return(%dict);
}

sub load_dictionary2 {
     my $line;
     my $file;
     $file = "dictionary.txt";
     open (NEWFILE, "$file") or die "Can't open filename";

     while ($line = <NEWFILE>) {
      # print $line;
        $line =~ s/\n//;
        if ($line ne "") {
	$key = lc($line);
      $dict{$key} = $line;
     }

     }
	close(NEWFILE);
	                                                                                                                          return(%dict);
}
