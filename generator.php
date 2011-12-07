<?php

/* This module is used for generating ID for multiple clients
*/




$key_t = msg_get_queue(78654, 0666 | IPC_CREAT);

if ($argv[1] == "remove")
{
  msg_remove_queue($key_t);
  exit;
}  

if ($argv[1] == "get")
{
  while (true)
  {
   msg_receive($key_t, 1, $realtype, 16384, $msg);
   echo $msg."\n";
  }
  exit;
}  

msg_remove_queue($key_t);
$key_t = msg_get_queue(78654, 0666 | IPC_CREAT);


for($i= 1 ; $i< 10000000; $i++)
{
   msg_send($key_t, 1, $i);
}