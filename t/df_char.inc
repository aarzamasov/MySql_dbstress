<?php

/**
 * Description of df_varchar
 *
 * @author Sorok7
 * date 23/11/2011
 */

$tableName = 'df_char';

$activeSize = 2;
$roleIdSize = 20000; 
$stateSize = 1000;

$createTable = "CREATE TABLE IF NOT EXISTS `$tableName` (
  `Id` int(10) NOT NULL AUTO_INCREMENT,
  `Login` char(32) NOT NULL,
  `Password` char(32) NOT NULL,
  `RoleId` int(11) NOT NULL,
  `Email` char(50) NOT NULL,
  `Active` tinyint(4) NOT NULL DEFAULT '1',
  `FirstName` char(30) NOT NULL,
  `LastName` CHAR(30) NOT NULL,
  `Phone` char(30) NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Login` (`Login`),
  KEY `RoleId` (`RoleId`)
) ";

$populateData = array(
    'id' => create_function('', 'return get_autoinc();'),
    'Login'      =>  create_function('', 'return rand_varchar(32);'),
    'Password'   =>  create_function('', 'return rand_varchar(32);'),
    'RoleId'     =>  create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
    'Email'      =>  create_function('', 'return rand_email();'),
    'Active'     =>  create_function('', 'return mt_rand(1,'.$activeSize.');'),
    'FirstName'  =>  create_function('', 'return rand_varchar(30);'),
    'LastName'   =>  create_function('', 'return rand_varchar(30);'),
    'Phone'      =>  create_function('', 'return rand_varchar(30);'),
    );

$testQueries = array(
    'READ_PK_POINT' => 
       array(
	'query' =>
    	    "SELECT FirstName FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_KEY_POINT' => 
       array(
	'query' =>
    	    "SELECT FirstName FROM $tableName WHERE RoleId = %d",
	'params' =>  create_function('','return array(mt_rand(1,'.$roleIdSize.'));'),
	),
    'READ_KEY_POINT_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT Active FROM $tableName WHERE RoleId = %d",
	'params' =>  create_function('','return array(mt_rand(1,'.$roleIdSize.'));'),
	),
    'READ_KEY_POINT_LIMIT' => 
       array(
	'query' =>
    	    "SELECT FirstName FROM $tableName WHERE RoleId = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$roleIdSize.'));'),
	),
    'READ_KEY_POINT_NO_DATA_LIMIT' => 
       array(
	'query' =>
    	    "SELECT Active FROM $tableName WHERE RoleId = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$roleIdSize.'));'),
	),
    'READ_PK_POINT_INDEX' => 
       array(
	'query' =>
    	    "SELECT id FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_PK_RANGE' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName WHERE id between %d and %d",
	'params' =>  create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array($p1, $p1+$rangeDiapason);'),
	),
    'READ_FTS' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName",
	'params' =>  create_function('','return array();'),
	),
    'READ_PK_RANGE_INDEX' => 
       array(
	'query' =>
    	    "SELECT count(id) FROM $tableName WHERE id between %d and %d",
	'params' => create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array($p1, $p1+$rangeDiapason);'),
	),
    'READ_KEY_RANGE' => 
       array(
	'query' =>
    	    "SELECT FirstName  FROM $tableName WHERE RoleId = %d and state_id between %d and %d",
	'params' => create_function('',' $p1=mt_rand(1,'.$roleIdSize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'READ_KEY_RANGE_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT FirstName  FROM $tableName WHERE RoleId = %d and state_id between %d and %d",
	'params' => create_function('',' $p1=mt_rand(1,'.$roleIdSize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'READ_KEY_RANGE_LIMIT' => 
       array(
	'query' =>
    	    "SELECT FirstName  FROM $tableName WHERE RoleId = %d and state_id between %d and %d LIMIT 50",
	'params' => create_function('',' $p1=mt_rand(1,'.$roleIdSize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'READ_KEY_RANGE_NO_DATA_LIMIT' => 
       array(
	'query' =>
    	    "SELECT city  FROM $tableName WHERE RoleId = %d and state_id between %d and %d LIMIT 50",
	'params' => create_function('',' $p1=mt_rand(1,'.$roleIdSize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'UPDATE_POINT_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET FirstName=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_varchar(64), mt_rand(1,$tableSize));'),
	),
    'UPDATE_POINT_INDEX' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET Login=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_email(), mt_rand(1,$tableSize));'),
	),
    'UPDATE_RANGE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET FirstName=%s WHERE id between %d and %d",
	'params' => create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array(rand_varchar(64), $p1, $p1+$rangeDiapason);'),
	),
    'UPDATE_RANGE_KEY' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET FirstName=%s WHERE RoleId = %d LIMIT 5",
	'params' => create_function('','$p1=mt_rand(1,'.$roleIdSize.'); return array(rand_varchar(64), $p1);'),
	),
    'DELETE_POINT_PK' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'DELETE_RANGE_PK' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE id between %d and %d",
	'params' => create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array($p1, $p1+$rangeDiapason);'),
	),
    'DELETE_POINT_KEY' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE RoleId = %d LIMIT 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$roleIdSize.'));'),
	),
    'DELETE_RANGE_KEY' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE RoleId = %d and state_id between %d and %d LIMIT 5",
	'params' => create_function('',' $p1=mt_rand(1,'.$roleIdSize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'INSERT_SEQ' => 
       array(
	'query' =>
    	    "INSERT INTO $tableName (id, name, password, email, city, zip, dob, country_id, state_id) VALUES (%d, %s, %s, %s, %s, %s, NOW(), %d, %d)",
	'params' => create_function('',
	         'return array(get_id(), rand_varchar(64), rand_varchar(64), rand_email(), rand_varchar(64), rand_varchar(8), mt_rand(1,'.$roleIdSize.'), mt_rand(1,'.$stateSize.'));'),
	),
    'INSERT_REVSEQ' => 
       array(
	'query' =>
    	    "INSERT INTO $tableName (id, Login, Password, RoleId, Email, Active, FirstName, LastName, Phone) VALUES (%d, %s, %s, %s, %s, %s, %s, %s, %s)",
	'params' => create_function('',
	         'return array(get_revid(), rand_varchar(32), rand_varchar(32), mt_rand(1,'.$roleIdSize.'), rand_email(), mt_rand(1,'.$activeSize.'), rand_varchar(30) );'),
	),
    'INSERT_RANDOM' => 
       array(
	'query' =>
    	    "INSERT IGNORE INTO $tableName (id, Login, Password, RoleId, Email, Active, FirstName, LastName, Phone) VALUES (%d, %s, %s, %s, %s, %s, %s, %s, %s)",
	'params' => create_function('',
	         'return array(mt_rand(1,4294967295), rand_varchar(32), rand_varchar(32), mt_rand(1,'.$roleIdSize.'), rand_email(), mt_rand(1,'.$activeSize.'), rand_varchar(30) );'),
	),
    );
/*
    'id' => create_function('', 'return get_autoinc();'),
    'Login'      =>  create_function('', 'return rand_varchar(32);'),
    'Password'   =>  create_function('', 'return rand_varchar(32);'),
    'RoleId'     =>  create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
    'Email'      =>  create_function('', 'return rand_email();'),
    'Active'     =>  create_function('', 'return mt_rand(1,'.$activeSize.');'),
    'FirstName'  =>  create_function('', 'return rand_varchar(30)'),
    'LastName'   =>  create_function('', 'return rand_varchar(30)'),
    'Phone'      =>  create_function('', 'return rand_varchar(30)')
*/	    

?>



