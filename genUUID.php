<?php

/* This module is used for generating ID for multiple clients
*/

$tableName = "uuid";
$databaseName = "testsuite";

define('MYSQLUSER', 'root');
define('MYSQLPWD' , '');
define('MYSQLHOST', 'localhost');

function preloadTable()
{
  global $tableUUID;
  global $tableName;
  global $databaseName;
  
  $mysqli = new mysqli(MYSQLHOST, MYSQLUSER, MYSQLPWD);
  $mysqli->query("use $databaseName");

  /* check connection */
  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

    if (!$mysqli->real_query("SELECT uuid FROM $tableName"))
    {
         printf("Query %s error: %s (%s)\n", $query, $mysqli->error, $mysqli->errno);
         return;
    }

    
    $result = $mysqli->store_result();
    if ($result === FALSE)
    {
       printf("Query error: %s\n", $mysqli->error);
    }
   
    while ($myrow = $result->fetch_array(MYSQLI_ASSOC))
    {
      $tableUUID[]=$myrow["uuid"];
    }

   $result->free_result();

  $mysqli->close();
  
  echo "=== table has been loaded ====\n";
  echo count($tableUUID)." elements\n";
}


$key_t = msg_get_queue(78655, 0666 | IPC_CREAT);
$key_t1 = msg_get_queue(78656, 0666 | IPC_CREAT);

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
msg_remove_queue($key_t1);

$key_t  = msg_get_queue(78655, 0666 | IPC_CREAT);
$key_t1 = msg_get_queue(78656, 0666 | IPC_CREAT);

preloadTable();

$sizeTable = count($tableUUID);

while(true)
{
  $i = mt_rand(0, $sizeTable-101);
  //echo $tableUUID[$i]."\n";
  msg_send($key_t, 1, $tableUUID[$i]);
  msg_send($key_t1, 1, $tableUUID[$i+100]);
}
