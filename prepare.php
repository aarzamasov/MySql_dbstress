<?php

$databaseName = "test";

define('MYSQLUSER', 'root');
define('MYSQLPWD' , '');
define('MYSQLHOST', 'localhost');

$mysqli = new mysqli(MYSQLHOST, MYSQLUSER, MYSQLPWD);
$mysqli->query("use $databaseName");

$mysqli->real_query("create table if not exists testdos (id int, id2 int);");

while(true)
{
 $stmt[$i++] = $mysqli->prepare("SELECT id2 FROM testdos WHERE id=?");
}
 
$mysqli->close();

?>
