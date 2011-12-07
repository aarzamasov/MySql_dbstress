<?php

$tableName = 'manyblob';

$countrySize= 200;
$stateSize= 50;
$rangeBlobDiapason=10;

$MYSQL_BATCH_INSERT = 1;
$blobSize = 32000;
	  
$createTable = "CREATE TABLE IF NOT EXISTS `$tableName` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(64) default NULL,
  `skills` text NOT NULL,
  `experience` text NOT NULL,
  `education` text NOT NULL,
  `resume` mediumblob NOT NULL,
  `image` mediumblob NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `name` (`name`)
  )";

$populateData = array(
    'id' => create_function('', 'return get_autoinc();'),
    'name'     =>  create_function('', 'return rand_varchar(60);'),
    'skills'  =>  create_function('', '$size=mt_rand(5000,8000); return "REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),$size)";'),
    'experience'  =>  create_function('', '$size=mt_rand(5000,8000); return "REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),$size)";'),
    'education'  =>  create_function('', '$size=mt_rand(5000,8000); return "REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),$size)";'),
    'resume'  =>  create_function('', '$size=mt_rand(5000,8000); return "REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),$size)";'),
    'image'  =>  create_function('', '$size=mt_rand(5000,8000); return "REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),$size)";'),
/*    'content'  =>  create_function('', 'return rand_mediumblob();'), */
    );


$testQueries = array(
    'READ_NO_BLOB_PK' => 
       array(
	'query' =>
    	    "select name from $tableName where id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_ONE_BLOB_PK' => 
       array(
	'query' =>
    	    "select education from $tableName where id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_ALL_BLOB_PK' => 
       array(
	'query' =>
    	    "select * from $tableName where id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_ALL_BLOB_KEY' => 
       array(
	'query' =>
    	    "select * from $tableName where name = '%s' LIMIT 5",
	'params' =>  create_function('','global $tableSize; return array(get_msg());'),
	),
    'UPDATE_BLOB_SAME_SIZE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET content = REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),".$blobSize.") WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'UPDATE_BLOB_RESIZE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET content = REPEAT(CHAR(FLOOR(100 + (RAND() * 32))),FLOOR(1+(RAND()*".$blobSize."))) WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'UPDATE_NOBLOB_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET num_downloads = num_downloads + 1 WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
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
    	    "DELETE FROM $tableName WHERE country_id = %d LIMIT 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$countrySize.'));'),
	),
    'DELETE_RANGE_KEY' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE country_id = %d and state_id between %d and %d LIMIT 5",
	'params' => create_function('',' $p1=mt_rand(1,'.$countrySize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'INSERT_SEQ' => 
       array(
	'query' =>
    	    "INSERT INTO $tableName (id, name, password, email, city, zip, dob, country_id, state_id) VALUES (%d, %s, %s, %s, %s, %s, NOW(), %d, %d)",
	'params' => create_function('',
	         'return array(get_id(), rand_varchar(64), rand_varchar(64), rand_email(), rand_varchar(64), rand_varchar(8), mt_rand(1,'.$countrySize.'), mt_rand(1,'.$stateSize.'));'),
	),
    'INSERT_REVSEQ' => 
       array(
	'query' =>
    	    "INSERT INTO $tableName (id, name, password, email, city, zip, dob, country_id, state_id) VALUES (%d, %s, %s, %s, %s, %s, NOW(), %d, %d)",
	'params' => create_function('',
	         'return array(get_revid(), rand_varchar(64), rand_varchar(64), rand_email(), rand_varchar(64), rand_varchar(8), mt_rand(1,'.$countrySize.'), mt_rand(1,'.$stateSize.'));'),
	),
    'INSERT_RANDOM' => 
       array(
	'query' =>
    	    "INSERT IGNORE INTO $tableName (id, name, password, email, city, zip, dob, country_id, state_id) VALUES (%d, %s, %s, %s, %s, %s, NOW(), %d, %d)",
	'params' => create_function('',
	         'return array(mt_rand(1,100000000), rand_varchar(64), rand_varchar(64), rand_email(), rand_varchar(64), rand_varchar(8), mt_rand(1,'.$countrySize.'), mt_rand(1,'.$stateSize.'));'),
	),
    );

?>
