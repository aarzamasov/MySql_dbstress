<?php

$tableName = 'manykeys';

$countrySize= 200;
$stateSize= 50;

$createTable = "CREATE TABLE `$tableName` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(64) NOT NULL default '',
  `email` varchar(64) NOT NULL default '',
  `password` varchar(64) NOT NULL default '',
  `dob` date default NULL,
  `address` varchar(128) NOT NULL default '',
  `city` varchar(64) NOT NULL default '',
  `state_id` tinyint(3) unsigned NOT NULL default '0',
  `zip` varchar(8) NOT NULL default '',
  `country_id` smallint(5) unsigned NOT NULL default '0',
  `gender` enum('M','F') NOT NULL default 'M',
  `account_type` varchar(32) NOT NULL default '',
  `verified` tinyint(4) NOT NULL default '0',
  `allow_mail` tinyint(3) unsigned NOT NULL default '0',
  `parrent_account` int(10) unsigned NOT NULL default '0',
  `closest_airport` varchar(3) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `email` (`email`),
  KEY `country_id` (`country_id`,`state_id`,`city`),
  KEY `name` (`name`),
  KEY `dob` (`dob`),
  KEY `gender` (`gender`,`dob`),
  KEY `verified` (`verified`),
  KEY `country_id_2` (`country_id`,`gender`),
  KEY `account_type` (`account_type`,`verified`),
  KEY `zip` (`zip`),
  KEY `city` (`city`,`address`(30)),
  KEY `allow_mail` (`allow_mail`),
  KEY `parrent_account` (`parrent_account`),
  KEY `closest_airport` (`closest_airport`)
)";

$arrGender[1]='M';
$arrGender[2]='F';

$populateData = array(
    'id' => create_function('', 'return get_autoinc();'),
    'name'     =>  create_function('', 'return rand_varchar(64);'),
    'password' =>  create_function('', 'return rand_varchar(64);'),
    'email'    =>  create_function('', 'return rand_email();'),
    'city'     =>  create_function('', 'return rand_varchar(64);'),
    'zip'      =>  create_function('', 'return rand_varchar(8);'),
    'dob'      =>   create_function('', 'return \'NOW()\';'),
    'country_id' => create_function('', 'return mt_rand(1,'.$countrySize.');'),
    'state_id' => create_function('',   'return mt_rand(1,'.$stateSize.');'),
    'gender' => create_function('',   'global $arrGender; return "\'".$arrGender[mt_rand(1,2)]."\'";'),
    'account_type'     =>  create_function('', 'return rand_varchar(10);'),
    'verified' => create_function('', 'return mt_rand(0,1);'),
    'allow_mail' => create_function('', 'return mt_rand(0,1);'),
    'parrent_account' => create_function('', 'global $tableSize; return mt_rand(1,$tableSize);'),
    'closest_airport' =>  create_function('', 'return rand_varchar(3);'),
    );


$testQueries = array(
    'READ_PK_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_KEY_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE country_id = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$countrySize.'));'),
	),
    'UPDATE_NO_KEY_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET name=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_varchar(64), mt_rand(1,$tableSize));'),
	),
    'UPDATE_ONE_KEY_PK' => 
       array(
	'query' =>
    	    "update $tableName set dob=NOW() where id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'UPDATE_MANY_KEY_PK' => 
       array(
	'query' =>
    	    "update $tableName set email=%s, country_id=%d, name=%s, dob=NOW(),
gender='%s', verified=%d, account_type=%s, zip=%s, city=%s,
allow_mail=%d, parrent_account=%d, closest_airport=%s where id = %d",
	'params' =>  create_function('','global $tableSize; global $arrGender; 
			return array(
				 rand_email(),
				 mt_rand(1,'.$countrySize.'),
				 rand_varchar(64),
				 $arrGender[mt_rand(1,2)], 
				 mt_rand(0,1),
				 rand_varchar(10),
				 rand_varchar(8),
				 rand_varchar(64),
				 mt_rand(0,1),
				 mt_rand(1,$tableSize),
				 rand_varchar(3),		
				 mt_rand(1,$tableSize),
			);'),
	),
    'UPDATE_RANGE_KEY' => 
       array(
	'query' =>
    	    "update $tableName  set verified=1-verified where country_id=%d limit 100",
	'params' => create_function('','$p1=mt_rand(1,'.$countrySize.'); return array($p1);'),
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
/*
    'id' => '',
    'name'     =>  create_function('', 'return rand_varchar(64);'),
    'password' =>  create_function('', 'return rand_varchar(64);'),
    'email'    =>  create_function('', 'return rand_email();'),
    'city'     =>  create_function('', 'return rand_varchar(64);'),
    'zip'      =>  create_function('', 'return rand_varchar(8);'),
    'dob'      =>   create_function('', 'return \'NOW()\';'),
    'country_id' => create_function('', 'return mt_rand(1,'.$countrySize.');'),
    'state_id' => create_function('',   'return mt_rand(1,'.$stateSize.');'),
*/	    

?>
