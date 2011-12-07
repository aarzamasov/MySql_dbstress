<?php


$tableName = 'normal_no_part';
if (isset($tableNm))
    $tableName = $tableNm;


$countrySize= 200;
$stateSize= 50;

$createTable = "CREATE TABLE IF NOT EXISTS `$tableName` (
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
    PRIMARY KEY  (`id`),
    KEY `email` (`email`),
    KEY `country_id` (`country_id`,`state_id`,`city`)
    )";

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
    );


$testQueries = array(
    'READ_PK_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_PK_POINT_JOIN' => 
       array(
	'query' =>
    	    "select $tableName.name from joinhelp JOIN $tableName ON ($tableName.id=joinhelp.pid) WHERE joinhelp.id=%d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,17680064));'),
	),
    'READ_PK_POINT_JOIN2' => 
       array(
	'query' =>
    	    "select $tableName.name from joinhelp JOIN $tableName ON ($tableName.id=joinhelp.pid) WHERE joinhelp.id BETWEEN %d AND %d",
	'params' =>  create_function('','global $tableSize; $t1=mt_rand(1,17680064); return array($t1,$t1+1000);'),
	),
    'READ_PK_POINT_JOIN3' => 
       array(
	'query' =>
    	    "select $tableName.name from joinhelp JOIN $tableName ON ($tableName.id=joinhelp.pid) WHERE joinhelp.id BETWEEN 1000 AND 2000",
	'params' =>  create_function('','global $tableSize; return array();'),
	),
    'READ_PK_POINT_JOIN4' => 
       array(
	'query' =>
    	    "select $tableName.name from joinhelp2 JOIN $tableName ON ($tableName.id=joinhelp2.pid) WHERE joinhelp2.id BETWEEN 1000 AND 2000",
	'params' =>  create_function('','global $tableSize; return array();'),
	),
    'READ_PK_POINT_JOIN5' => 
       array(
	'query' =>
    	    "select $tableName.name from joinhelp JOIN $tableName ON ($tableName.country_id=joinhelp.cid) WHERE joinhelp.id BETWEEN 100 AND 200",
	'params' =>  create_function('','global $tableSize; return array();'),
	),
    'READ_KEY_POINT' => 
       array(
	'query' =>
    	    "SELECT name FROM $tableName WHERE country_id = %d limit 5",
	'params' =>  create_function('','return array(mt_rand(1,'.$countrySize.'));'),
	),
    'READ_KEY_POINT_CALC' => 
       array(
	'query' =>
    	    "SELECT SQL_CALC_FOUND_ROWS name FROM $tableName WHERE country_id = %d limit 5",
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
    	    "SELECT id FROM $tableName WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,$tableSize));'),
	),
    'READ_PK_RANGE' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName WHERE id between %d and %d",
	'params' =>  create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array($p1, $p1+$rangeDiapason);'),
	),
    'READ_PK_RANGE_1' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName WHERE id between %d and %d",
	'params' =>  create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,900000); return array($p1, $p1+$rangeDiapason);'),
	),
    'READ_PK_RANGE_2' => 
       array(
	'query' =>
    	    "SELECT min(dob) FROM $tableName WHERE (id between %d and %d) or ((id between %d and %d))",
	'params' =>  create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); $p2=mt_rand(1,$tableSize-$rangeDiapason); return array($p1, $p1+$rangeDiapason, $p2, $p2+$rangeDiapason);'),
	),
    'READ_KEY_RANGE_1' => 
       array(
	'query' =>
    	    "SELECT name  FROM $tableName WHERE country_id = %d and state_id=%d",
	'params' => create_function('',' $p1=mt_rand(1,'.$countrySize.'); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2);'),
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
    	    "UPDATE $tableName SET name=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_varchar(64), mt_rand(1,$tableSize));'),
	),
    'UPDATE_POINT_INDEX' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET email=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_email(), mt_rand(1,$tableSize));'),
	),
    'UPDATE_RANGE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET name=%s WHERE id between %d and %d",
	'params' => create_function('','global $tableSize, $rangeDiapason; $p1=mt_rand(1,$tableSize-$rangeDiapason); return array(rand_varchar(64), $p1, $p1+$rangeDiapason);'),
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
