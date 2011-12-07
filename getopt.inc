<?php
function bgetop($opAr=array(),$unknown=true) {

  $argv = $_SERVER['argv'];
  $argc = $_SERVER['argc'];
  $argPos = 1; // zero is program running

  // foreach arg
  while ($argPos<$argc) {
    $arg = $argv[$argPos];
    if ($arg{0}=="-") {
      if ($arg{1}=="-") {
        $var = substr($arg,2,strlen($arg));
      } else { $var = $arg{1}; }
      foreach ($opAr as $opk => $opv) {
        if (!isset($return[$var])) {
          if (strpos($opv,$arg) !== FALSE) {
            // this is where the -f -foo fix needs to be,
            // the partial string exists in this record,
            // but we need to determine if it's accurate
            // somehow (i'm thinking: eregi?)
            if ($accurate=1) {
              // we foudn the key
              if (strpos($opv,':') !== FALSE) {
                // next value is the one to use,
                // then skip it in the parser.
                if (isset($argv[$argPos+1])) {
                  $return[$var] = $argv[++$argPos];
                } else {
                  $return[$var] = FALSE;
                }
              } else {
                // just set the toggle
                $return[$var] = TRUE;
              }
              // don't check this opAr value again
              unset($opAr[$opk]);
            }
          } // if accurate
        } // !isset already
      } // foreach opAr
    } else { // we weren't expecting a non-hyphened argument, possibly just a filename, or whatnot
      if ($unknown) { $return['unknown'][]=$arg; }
    }
    $argPos++;
  } // while argPos < argc

  if (is_array($return)) {
    return $return;
  } else { return 0; }

} // end function bgetop

?>
