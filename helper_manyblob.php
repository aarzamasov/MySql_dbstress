<?php

/* This module is used for generating ID for multiple clients
*/

include('db.inc');

$tableName = "manyblob";
$databaseName = "testsuite";
$fieldName = "name";

function preloadTable()
{
  global $tableUUID;
  global $tableName;
  global $databaseName;
  global $fieldName;
  
  $mysqli = new mysqli(MYSQLHOST, MYSQLUSER, MYSQLPWD);
  $mysqli->query("use $databaseName");

  /* check connection */
  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }
  echo "=== preload table has been started ====\n";


    if (!$mysqli->real_query("SELECT $fieldName FROM $tableName"))
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
      $tableUUID[]=$myrow[$fieldName];
    }

   $result->free_result();

  $mysqli->close();
  
  echo "=== table has been loaded ====\n";
  $tableUUID = array_unique($tableUUID);
  echo count($tableUUID)." elements\n";
}

$MSG_ID = 78654;
$key_t = msg_get_queue($MSG_ID, 0666 | IPC_CREAT);
msg_remove_queue($key_t);
$key_t = msg_get_queue($MSG_ID, 0666 | IPC_CREAT);


preloadTable();

$sizeTable = count($tableUUID);

echo "starting loop\n";
while(true)
{
  $i = mt_rand(0, $sizeTable-1);
  //echo $tableUUID[$i]."\n";
  msg_send($key_t, 1, $tableUUID[$i]);
}
