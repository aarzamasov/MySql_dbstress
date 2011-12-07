<?php

$exit = 1;

$pid = pcntl_fork();


if ($pid == -1) {
       die('could not fork');
} else if ($pid) {
       // we are the parent
       echo "parent, $pid\n";
       posix_kill($pid, SIGKILL);
       echo "parent, exit\n";
} else {
       // we are the child
       while ($exit)
       {
         $i=$i+1;
       }
}


?>