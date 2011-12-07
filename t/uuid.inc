<?php

$tableName = 'uuid';

$countrySize= 200;
$stateSize= 50;

$createTable = "CREATE TABLE IF NOT EXISTS `$tableName` (
    `uuid` varchar(36) NOT NULL default '',
    `name` varchar(64) NOT NULL default '',
    `email` varchar(64) NOT NULL default '',
    `password` varchar(64) NOT NULL default '',
    `dob` date default NULL,
    `address` varchar(128) NOT NULL default '',
    `city` varchar(64) NOT NULL default '',
    `state_id` tinyint(3) unsigned NOT NULL default '0',
    `zip` varchar(8) NOT NULL default '',
    `country_id` smallint(5) unsigned NOT NULL default '0',
    PRIMARY KEY  (`uuid`),
    UNIQUE KEY `email` (`email`),
    KEY `country_id` (`country_id`,`state_id`,`city`)
    )";

$populateData = array(
    'uuid' => create_function('', 'return \'uuid()\';'),
    'name'     =>  create_function('', 'return rand_varchar(64);'),
    'password' =>  create_function('', 'return rand_varchar(64);'),
    'email'    =>  create_function('', 'return rand_email();'),
    'city'     =>  create_function('', 'return rand_varchar(64);'),
    'zip'      =>  create_function('', 'return rand_varchar(8);'),
    'dob'      =>   create_function('', 'return \'NOW()\';'),
    'country_id' => create_function('', 'return mt_rand(1,'.$countrySize.');'),
    'state_id' => create_function('',   'return mt_rand(1,'.$stateSize.');'),
    );


$testQueries = array(
    'READ_PK_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE uuid = '%s'",
	'params' =>  create_function('','global $tableSize; return array(get_uuid());'),
	),
    'READ_KEY_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE country_id = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$countrySize.'));'),
	),
    'READ_KEY_POINT_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT state_id FROM $tableName WHERE country_id = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$countrySize.'));'),
	),
    'READ_PK_POINT_INDEX' => 
       array(
	'query' =>
    	    "SELECT uuid FROM $tableName WHERE uuid = '%s'",
	'params' =>  create_function('','global $tableSize; return array(get_uuid());'),
	),
    'READ_PK_RANGE' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName WHERE uuid between '%s' and '%s'",
	'params' =>  create_function('','return get_uuid_pair();'),
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
    	    "SELECT count(uuid) FROM $tableName WHERE uuid between '%s' and '%s'",
	'params' =>  create_function('','return get_uuid_pair();'),
	),
    'READ_KEY_RANGE' => 
       array(
	'query' =>
    	    "SELECT name  FROM $tableName WHERE country_id = %d and state_id between %d and %d LIMIT 50",
	'params' => create_function('',' $p1=mt_rand(1,'.$countrySize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'READ_KEY_RANGE_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT city  FROM $tableName WHERE country_id = %d and state_id between %d and %d LIMIT 50",
	'params' => create_function('',' $p1=mt_rand(1,'.$countrySize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+10);'),
	),
    'UPDATE_POINT_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET name=%s WHERE uuid = '%s'",
	'params' =>  create_function('','global $tableSize; return array(rand_varchar(64), get_uuid());'),
	),
    'UPDATE_POINT_INDEX' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET email=%s WHERE uuid = '%s'",
	'params' =>  create_function('','global $tableSize; return array(rand_email(), get_uuid());'),
	),
    'UPDATE_RANGE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET name=%s WHERE uuid between '%s' and '%s'",
	'params' =>  create_function('','return array_merge(array(rand_varchar(64)), get_uuid_pair());'),
	),
    'UPDATE_RANGE_KEY' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET name=%s WHERE country_id = %d LIMIT 5",
	'params' => create_function('','$p1=mt_rand(1,'.$countrySize.'); return array(rand_varchar(64), $p1);'),
	),
    'DELETE_POINT_PK' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE uuid = '%s'",
	'params' =>  create_function('','global $tableSize; return array(get_uuid());'),
	),
    'DELETE_RANGE_PK' => 
       array(
	'query' =>
    	    "DELETE FROM $tableName WHERE uuid between '%s' and '%s'",
	'params' =>  create_function('','return get_uuid_pair();'),
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
    	    "INSERT INTO $tableName (uuid, name, password, email, city, zip, dob, country_id, state_id) VALUES (%d, %s, %s, %s, %s, %s, NOW(), %d, %d)",
	'params' => create_function('',
	         'return array(get_id(), rand_varchar(64), rand_varchar(64), rand_email(), rand_varchar(64), rand_varchar(8), mt_rand(1,'.$countrySize.'), mt_rand(1,'.$stateSize.'));'),
	),
    );



?>
