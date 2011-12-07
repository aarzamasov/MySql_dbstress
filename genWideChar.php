<?php

/* This module is used for generating ID for multiple clients
*/

$tableName = "wide";
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
  echo "=== preload table has been started ====\n";


    if (!$mysqli->real_query("SELECT char_1 FROM $tableName"))
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
      $tableUUID[]=$myrow["char_1"];
    }

   $result->free_result();

  $mysqli->close();
  
  echo "=== table has been loaded ====\n";
  $tableUUID = array_unique($tableUUID);
  echo count($tableUUID)." elements\n";
}


$key_t = msg_get_queue(786554, 0666 | IPC_CREAT);


msg_remove_queue($key_t);

$key_t  = msg_get_queue(78654, 0666 | IPC_CREAT);

preloadTable();

$sizeTable = count($tableUUID);

while(true)
{
  $i = mt_rand(0, $sizeTable-1);
  //echo $tableUUID[$i]."\n";
  msg_send($key_t, 1, $tableUUID[$i]);
}
