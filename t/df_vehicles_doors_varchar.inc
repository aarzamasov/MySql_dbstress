<?php

/**
 * Description of df_varchar
 *
 * @author Sorok7
 * date 23/11/2011
 */

$tableName = 'df_vehicles_doors_varchar';

$activeSize = 2;
$roleIdSize = 20000000; 
$stateSize = 1000;

$createTable = "CREATE TABLE IF NOT EXISTS `$tableName` (
`id` int(10) unsigned NOT NULL AUTO_INCREMENT,
`DealerID` varchar(100) CHARACTER SET latin1 NOT NULL DEFAULT '',
`StockNumber` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`NewUsed` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`Year` int(10) unsigned NOT NULL DEFAULT '0',
`Make` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`Model` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`ModelNumber` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULt '',
`Body` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`Trim` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`StyleDescription` varchar(45) CHARACTER SET latin1 NOT NULL DEfault '',
`Doors` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`VIN` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`SellingPrice` int(10) unsigned NOT NULL DEFAULT '0',
`InvoiceAmount` int(10) unsigned NOT NULL DEFAULT '0',
`BlueBook` int(10) unsigned NOT NULL DEFAULT '0',
`MSRP` int(10) unsigned NOT NULL DEFAULT '0',
`MiscPrice1` int(10) unsigned NOT NULL DEFAULT '0',
`MiscPrice2` int(10) unsigned NOT NULL DEFAULT '0',
`MiscPrice3` int(10) unsigned NOT NULL DEFAULT '0',
`InternetPrice` int(10) unsigned NOT NULL DEFAULT '0',
`NADARetailPrice` int(10) unsigned NOT NULL DEFAULT '0',
`Miles` int(10) unsigned NOT NULL DEFAULT '0',
`Transmission` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`TransmissionDescription` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`TransmissionSpeed` varchar(45) CHARACTER SET latin1 DEFAULT '',
`EngineCylinders` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EngineDisplacement` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EngineDescription` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EngineAspirationType` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EngineBlockType` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`InteriorColor` varchar(250) DEFAULT NULL,
`IntUpholstery` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`IntColorGeneric` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`ExteriorColor` varchar(250) DEFAULT NULL,
`ExtColorGeneric` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`PhotoCount` int(10) unsigned NOT NULL DEFAULT '0',
`DateInStock` varchar(45) CHARACTER SET latin1 DEFAULT NULL,
`DaysInStock` int(10) unsigned NOT NULL DEFAULT '0',
`VehicleDescription` text CHARACTER SET latin1,
`Certified` int(10) unsigned NOT NULL DEFAULT '0',
`StandardBody` varchar(250) NOT NULL,
`SpecialsPrice` int(10) unsigned NOT NULL DEFAULT '0',
`SpecialsStartDate` varchar(45) CHARACTER SET latin1 DEFAULT NULL,
`SpecialsEndDate` varchar(45) CHARACTER SET latin1 DEFAULT NULL,
`SpecialsMonthlyPayment` int(10) unsigned NOT NULL DEFAULT '0',
`SpecialsDisclaimer` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`MakeStandard` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`ModelStandard` varchar(250) CHARACTER SET latin1 NOT NULL DEFAULT '',
`WheelbaseCode` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EPAHighway` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`EPACity` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`FuelType` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`Drivetrain` varchar(45) CHARACTER SET latin1 NOT NULL DEFAULT '',
`Active` int(10) unsigned NOT NULL DEFAULT '0',
`FirstImported` int(11) DEFAULT NULL,
`LastImported` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
`LastUpdated` timestamp NULL DEFAULT NULL,
`IsSpecial` tinyint(1) NOT NULL DEFAULT '0',
`ColorMatchedImage` varchar(200) CHARACTER SET latin1 DEFAULT NULL,
`CertificationWarranty` int(10) DEFAULT NULL,
`HasWarranty` int(11) DEFAULT NULL,
`VideoLink` varchar(200) CHARACTER SET latin1 DEFAULT NULL,
`Comment1` text CHARACTER SET latin1,
`Comment2` varchar(400) CHARACTER SET latin1 DEFAULT NULL,
`Comment3` varchar(100) CHARACTER SET latin1 DEFAULT NULL,
`Comment4` varchar(100) CHARACTER SET latin1 DEFAULT NULL,
`Comment5` varchar(100) CHARACTER SET latin1 DEFAULT NULL,
`website_id` int(11) NOT NULL,
`owner_id` int(11) NOT NULL,
`is_locked` tinyint(1) NOT NULL DEFAULT '0',
`is_sold` tinyint(1) NOT NULL DEFAULT '0',
`car_id` int(11) NOT NULL DEFAULT '0',
`evox_colorcode` varchar(10) CHARACTER SET latin1 DEFAULT NULL,
`use_evox_images` tinyint(4) NOT NULL DEFAULT '0',
`Down2000` int(10) unsigned DEFAULT NULL,
`Down1000` int(10) unsigned DEFAULT NULL,
`Down0` int(10) unsigned DEFAULT NULL,
`attachment` varchar(60) CHARACTER SET latin1 DEFAULT NULL,
`CertificationId` int(10) DEFAULT NULL,
`CertificationProgram` varchar(20) DEFAULT NULL,
`SeriesSupplement` varchar(128) DEFAULT NULL,
`StyleId` int(11) DEFAULT NULL,
`PackageCodes` varchar(128) DEFAULT NULL,
`SalesCost` int(10) DEFAULT NULL,
`StickerPrice` int(10) DEFAULT NULL,
`Series` varchar(128) DEFAULT NULL,
`ModelSupplement` varchar(256) DEFAULT NULL,
`ExteriorColorCode` varchar(12) DEFAULT NULL,
`InteriorColorCode` varchar(12) DEFAULT NULL,
`SpanishComments` varchar(256) DEFAULT NULL,
`DealerComments` varchar(256) DEFAULT NULL,
`TitleStatus` tinyint(1) unsigned DEFAULT NULL,
`Inspection` tinyint(1) unsigned DEFAULT NULL,
PRIMARY KEY (`id`),
KEY `Index_DealerID` (`DealerID`),
KEY `VIN_ACTIVE_DEALER` (`DealerID`,`VIN`,`Active`),
KEY `ACTIVE_NEWUSED_MAKE_DEALERID` (`Active`,`NewUsed`,`Make`,`DealerID`),
KEY `SellingPrice` (`Make`,`SellingPrice`,`MSRP`),
KEY `ind_dealer_id` (`DealerID`),
KEY `ind_make_model` (`Make`,`Model`),
KEY `index_vin` (`VIN`),
KEY `ind_make_model_dealerid` (`Make`,`Model`,`DealerID`),
KEY `ind_make` (`Make`),
KEY `ind_exterior_color` (`ExteriorColor`),
KEY `new_used` (`NewUsed`),
KEY `IndxPhotoCount` (`PhotoCount`)
) ";

$populateData = array(
    'id' => create_function('', 'return get_autoinc();'),
'DealerID' => create_function('', 'return rand_varchar(100);'),
'StockNumber' => create_function('', 'return rand_varchar(250);'),
'NewUsed' => create_function('', 'return rand_varchar(2);'), 
'Year' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Make' => create_function('', 'return rand_varchar(250);'),
'Model'=> create_function('', 'return rand_varchar(250);'),
'ModelNumber' => create_function('', 'return rand_varchar(250);'),
'Body' => create_function('', 'return rand_varchar(250);'),
'Trim' => create_function('', 'return rand_varchar(250);'),
'StyleDescription' => create_function('', 'return rand_varchar(45);'),
'Doors' => create_function('', 'return mt_rand(1,5);'),
'VIN' => create_function('', 'return rand_varchar(45);'),
'SellingPrice' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'InvoiceAmount' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'BlueBook' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'MSRP' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'MiscPrice1' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'MiscPrice2' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'MiscPrice3' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'InternetPrice' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'NADARetailPrice' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Miles' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Transmission' => create_function('', 'return rand_varchar(250);'),
'TransmissionDescription' => create_function('', 'return rand_varchar(45);'),
'TransmissionSpeed' => create_function('', 'return rand_varchar(45);'),
'EngineCylinders' => create_function('', 'return rand_varchar(250);'),
'EngineDisplacement' => create_function('', 'return rand_varchar(250);'),
'EngineDescription' => create_function('', 'return rand_varchar(45);'),
'EngineAspirationType' => create_function('', 'return rand_varchar(45);'),
'EngineBlockType' => create_function('', 'return rand_varchar(45);'),
'InteriorColor' => create_function('', 'return rand_varchar(250);'),
'IntUpholstery' => create_function('', 'return rand_varchar(45);'),
'IntColorGeneric' => create_function('', 'return rand_varchar(45);'),
'ExteriorColor' => create_function('', 'return rand_varchar(250);'),
'ExtColorGeneric' => create_function('', 'return rand_varchar(45);'),
'PhotoCount' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'DateInStock' => create_function('', 'return rand_varchar(45);'),
'DaysInStock' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'VehicleDescription' => create_function('', 'return rand_varchar(1500);'),
'Certified' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'StandardBody'=> create_function('', 'return rand_varchar(250);'),
'SpecialsPrice' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'SpecialsStartDate' => create_function('', 'return rand_varchar(45);'),
'SpecialsEndDate' => create_function('', 'return rand_varchar(45);'),
'SpecialsMonthlyPayment' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'SpecialsDisclaimer' => create_function('', 'return rand_varchar(250);'),
'MakeStandard' => create_function('', 'return rand_varchar(250);'),
'ModelStandard' => create_function('', 'return rand_varchar(250);'),
'WheelbaseCode' => create_function('', 'return rand_varchar(45);'),
'EPAHighway' => create_function('', 'return rand_varchar(45);'),
'EPACity' => create_function('', 'return rand_varchar(45);'),
'FuelType' => create_function('', 'return rand_varchar(45);'),
'Drivetrain' => create_function('', 'return rand_varchar(45);'),
'Active' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'FirstImported' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'LastImported' =>   create_function('', 'return \'NOW()\';'),
'LastUpdated' =>   create_function('', 'return \'NOW()\';'),
'IsSpecial' => create_function('', 'return mt_rand(1,100);'),
'ColorMatchedImage' => create_function('', 'return rand_varchar(200);'),
'CertificationWarranty' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'HasWarranty' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'VideoLink' => create_function('', 'return rand_varchar(200);'),
'Comment1' => create_function('', 'return rand_varchar(1500);'),
'Comment2' => create_function('', 'return rand_varchar(400);'),
'Comment3' => create_function('', 'return rand_varchar(100);'),
'Comment4' => create_function('', 'return rand_varchar(100);'),
'Comment5' => create_function('', 'return rand_varchar(100);'),
'website_id' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'owner_id' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'is_locked' => create_function('', 'return mt_rand(1,100);'),
'is_sold' => create_function('', 'return mt_rand(1,100);'),
'car_id' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'evox_colorcode' => create_function('', 'return rand_varchar(10);'),
'use_evox_images' => create_function('', 'return mt_rand(1,100);'),
'Down2000' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Down1000' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Down0' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'attachment' => create_function('', 'return rand_varchar(60);'),
'CertificationId' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'CertificationProgram' => create_function('', 'return rand_varchar(20);'),
'SeriesSupplement' => create_function('', 'return rand_varchar(128);'),
'StyleId' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'PackageCodes' => create_function('', 'return rand_varchar(128);'),
'SalesCost' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'StickerPrice' => create_function('', 'return mt_rand(1,'.$roleIdSize.');'),
'Series' => create_function('', 'return rand_varchar(128);'),
'ModelSupplement' => create_function('', 'return rand_varchar(256);'),
'ExteriorColorCode' => create_function('', 'return rand_varchar(12);'),
'InteriorColorCode' => create_function('', 'return rand_varchar(12);'),
'SpanishComments' => create_function('', 'return rand_varchar(256);'),
'DealerComments' => create_function('', 'return rand_varchar(256);'),
'TitleStatus' => create_function('', 'return mt_rand(1,100);'),
'Inspection' => create_function('', 'return mt_rand(1,100);'),);

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
    	    "SELECT VIN FROM $tableName WHERE Doors = %s",
	'params' =>  create_function('','return array(mt_rand(1,5));'),
	),
    'READ_KEY_POINT_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT NewUsed FROM $tableName WHERE Doors = %s",
	'params' =>  create_function('','return array(mt_rand(1,5));'),
	),
    'READ_KEY_POINT_LIMIT' => 
       array(
	'query' =>
    	    "SELECT VIN FROM $tableName WHERE Doors = %s limit 5",
	'params' =>  create_function('','return array(mt_rand(1,5));'),
	),
    'READ_KEY_POINT_NO_DATA_LIMIT' => 
       array(
	'query' =>
    	    "SELECT NewUsed FROM $tableName WHERE Doors = %s limit 5",
	'params' =>  create_function('','return array(mt_rand(1,5));'),
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
    	    "SELECT VIN  FROM $tableName WHERE Doors = %s and id between %d and %d",
	'params' => create_function('',' $p1=mt_rand(1,5); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+100);'),
	),
    'READ_KEY_RANGE_NO_DATA' => 
       array(
	'query' =>
    	    "SELECT VIN  FROM $tableName WHERE Doors = %s and id between %d and %d",
	'params' => create_function('',' $p1=mt_rand(1,5); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+100);'),
	),
    'READ_KEY_RANGE_LIMIT' => 
       array(
	'query' =>
    	    "SELECT VIN  FROM $tableName WHERE Doors = %s and id between %d and %d LIMIT 25",
	'params' => create_function('',' $p1=mt_rand(1,5); $p2=mt_rand(1,'.$stateSize.'); return array($p1, $p2, $p2+100);'),
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
    	    "UPDATE $tableName SET Doors=%s WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(mt_rand(1,5), mt_rand(1,$tableSize));'),
	),
    'UPDATE_POINT_INDEX' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET Login=%d WHERE id = %d",
	'params' =>  create_function('','global $tableSize; return array(rand_email(), mt_rand(1,$tableSize));'),
	),
    'UPDATE_RANGE_PK' => 
       array(
	'query' =>
    	    "UPDATE $tableName SET Doors=%s WHERE id between %d and %d",
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


