<?php

function rand_string($length=64)
{
  $nps = "";
  for($i=0;$i<$length;$i++)
  {
    $nps .= chr( (mt_rand(1, 36) <= 26) ? mt_rand(97, 122) : mt_rand(48, 57 ));
  }
  return $nps;
}

function rand_varchar($maxlen=64)
{
  $len = mt_rand(5, $maxlen);
  return "'".rand_string($len)."'";
}

function rand_email()
{
   return "'".rand_string(10).'@'.rand_string(20).'.com'."'";
}


function rand_mediumblob()
{
  global $blobcont;
  if (!$blobcont)
  {
    $blobcont = rand_string(16000000);
    $blobcont = str_replace("'","d",$blobcont);
  }
  
  $idx  = mt_rand(1,1000000);
  $char = chr(mt_rand(30,127));
  if ($char==="'") $char = "d";
  $blobcont[$idx] = $char;
  return "'".$blobcont."'";

}


function get_autoinc()
{
  global $autoid;
  if (!$autoid) $autoid= 0;
  $autoid++;
  return $autoid;
}

$randtable = array();

function get_randomid($max)
{
  global $randtable; 
  $idx= mt_rand(1, $max);
  while ($randtable[$idx])
  {
	$idx++;
	if ($idx > $max) $idx=1;
  }
  $randtable[$idx] = 1;
  return $idx;
}

/* prepare message queue */

/* 

$MSG_ID = 78654;
if (function_exists('msg_get_queue'))
$key_t = msg_get_queue($MSG_ID, 0666 | IPC_CREAT);


function get_msg()
{
  global $key_t;
  msg_receive($key_t, 1, $realtype, 16384, $msg);
  return $msg; 
}
*/
/* get_id() / get_revid() are used for INSERT threads */
/*
function get_id()
{
  global $key_t;
  msg_receive($key_t, 1, $realtype, 16384, $msg);
  return $msg; 
}  

function get_revid()
{
  global $key_t;
  msg_receive($key_t, 1, $realtype, 16384, $msg);
  return 100000000 - $msg; 
}  

function get_char()
{
  global $key_t;
  msg_receive($key_t, 1, $realtype, 16384, $msg);
  return addslashes($msg); 
}  


$MSG_ID1 = 78655;

if (function_exists('msg_get_queue')) {
$key_t1 = msg_get_queue($MSG_ID1, 0666 | IPC_CREAT);
$key_t2 = msg_get_queue(78656, 0666 | IPC_CREAT);
}

function get_uuid()
{
  global $key_t1;
  global $key_t2;
  msg_receive($key_t1, 1, $realtype, 16384, $msg1);
  msg_receive($key_t2, 1, $realtype, 16384, $msg2);
 // echo "got $msg\n";
  return $msg1; 
}  

function get_uuid_pair()
{
  global $key_t1;
  global $key_t2;
  msg_receive($key_t1, 1, $realtype, 16384, $msg1);
  msg_receive($key_t2, 1, $realtype, 16384, $msg2);
  return array($msg1,$msg2); 
}  

*/

?>
