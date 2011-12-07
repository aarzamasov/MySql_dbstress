<?
//var_dump($argv);
/* Arguments:
  1 - count of threads
  2 - max_time
  3 - table name
  */

require('getopt.inc');
require('utils.inc');

echo "Starting...\n";

define('DEBUG', 0);


/* Important constants */
define('MYSQLUSER', 'root');
define('MYSQLPWD' , '');
$MYSQLHOST='localhost';
$MYSQL_BATCH_INSERT = 500;
//define('MYSQL_BATCH_INSERT',1);

$opAr = array(
	      "-d|--max-time:",
	      "-e|--engine:",
	      "-h|--host:",
	      "-f|--file:",
	      "-n|--test-name:",
	      "-o|--operation:",
	      "-q|--query:",
	      "-s|--table-size:",
	      "-t|--num-threads:",
	      "-w|--table-name:",
	      );
	      
/* possible operations:

   prepare	      
   run 
   cleanup
   help

*/
   	      
$op = bgetop($opAr);
//var_dump($op);

$testDuration= 60;
$threads= 1;
$insert_threads=0;
$operation = 'help';
$test= 'normal';
$tableSize = 10000;
$rangeDiapason = 100;
$runQuery = 'READ_PK_POINT';
$dumptoFile = 0;
$chunkFileSize = 10000000;
$showProgress = 100000;

$mysqluser = MYSQLUSER;
$mysqlpwd  = MYSQLPWD;
$databaseName = 'testsuite';
$engine = "INNODB";


if (isset($op['d']))
{
  $testDuration= $op['d'];
  echo "Test duration: $testDuration\n";
}
if (isset($op['h']))
{
  $MYSQLHOST= $op['h'];
  echo "HOST: $MYSQLHOST\n";
}


if (isset($op['t']))
{
  $threads= $op['t'];
  echo "THREADS: $threads\n";
}

if (isset($op['o']))
{
  $operation= $op['o'];
  echo "Operation: $operation\n";
}

if (isset($op['q']))
{
  $runQuery= $op['q'];
  echo "runQuery: $runQuery\n";
}

if (isset($op['f']))
{
  $dumptoFile= 1;
  echo "dumptoFile\n";
}

if (isset($op['w']))
{
  $tableNm= $op['w'];
  echo "Table name: $tableNm\n";
}

if (isset($op['n']))
{
  $test= $op['n'];
  echo "Test: $test\n";
  include("t/$test.inc");
}

if (isset($op['e']))
{
  $engine= $op['e'];
  echo "Engine: $engine\n";
} else {
  unset($engine);
}

if (isset($op['s']))
{
  $tableSize= $op['s'];
  echo "Table size: $tableSize\n";
}


/************ PREPARE stage ********************/
if ($operation == 'prepare') {
  $mysqli = new mysqli($MYSQLHOST, $mysqluser, $mysqlpwd);

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

/* create database */
  if (!$mysqli->query("CREATE DATABASE IF NOT EXISTS $databaseName"))
  {
    printf("Create database error: %s\n", $mysqli->error);
  }
 
  
/* create table */
  $mysqli->query("use $databaseName");
  if (!$mysqli->query("DROP TABLE IF EXISTS $tableName"))
  {
    printf("Create table error: %s\n", $mysqli->error);
  }

  $queryCreateTable = $createTable;

  if ($engine)
    $queryCreateTable = $createTable." Engine=$engine";
 
  if (!$mysqli->query($queryCreateTable))
  {
    printf("Create table error: %s\n", $mysqli->error);
  }
      if ($dumptoFile)
      { 
        $chunkNum = 1;
        $fdumpFile=fopen("dump.$tableName.sql","w");
      }
/* insert data */

/* prepare column string */
  $columns= array();
  foreach ($populateData as $column => $value)
  {
    if ($value)
    {
      $columns[] = $column;
      $values[]  = $value();
    }
  }   
print_r($columns);
  $columnStr = implode(',', $columns);
  $valueStrs = array();
  for($i= 0; $i < $tableSize; $i++)
  {
    /* create columns and values strings for insert */
    
    $values=  array();
    
    foreach ($populateData as $column => $value)
    {
       if ($value)
       {
	 $values[]  = $value();
       }
    }   
    
    $valueStrs[]  = '('.implode(',', $values).')';
    if ( ( ($i+1) % $MYSQL_BATCH_INSERT ) == 0 )
    {
      $valueStr = implode(',', $valueStrs);
      $query = "INSERT INTO $tableName ($columnStr) VALUES $valueStr";
      if ($dumptoFile)
        fprintf($fdumpFile,$query.";\n");
      else	
      if (!$mysqli->query($query))
      {
        printf("Insert error: %s\n", $mysqli->error);
      }    
      $valueStrs = array();

    }
    if ((($i + 1) % $showProgress) == 0)
	printf("Processed %d, %.2f\n", $i, $i/$tableSize*100);     
   
    if ( ( ($i + 1) % $chunkFileSize) == 0)  	
    {
      fclose($fdumpFile);
        $chunkNum++;
        $fdumpFile=fopen("dump.$chunkNum.sql","w");
    }	
  }

  if (count($valueStrs) > 0)
  {
      $valueStr = implode(',', $valueStrs);

      $query = "INSERT INTO $test ($columnStr) VALUES $valueStr";

      if ($dumptoFile)
        fprintf($fdumpFile,$query.";\n");
      else	
      if (!$mysqli->query($query))
      {
        printf("Insert error: %s\n", $mysqli->error);
      }    
  }

// temporary ... test queries 
 


  $mysqli->close();
      if ($dumptoFile)
        fclose($fdumpFile);

  return 0;
}

/************ CLEANUP stage ********************/
if ($operation == 'cleanup') {
  $mysqli = new mysqli($MYSQLHOST, $mysqluser, $mysqlpwd);

  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\n", mysqli_connect_error());
    exit();
  }

/* drop table */
  $mysqli->query("use $databaseName");
  if (!$mysqli->query("DROP TABLE IF EXISTS $test"))
  {
    printf("Create database error: %s", $mysqli->error);
  }
 

  $mysqli->close();

  return 0;
}


$main_thread= 0;

$iterations= 500000/$threads;

/* ============== MAIN stage =======================*/


/* temporary code, helper thread 
$descr= $testQueries[$runQuery];

if ($descr['backthread']) {
     echo "starting background thread\n";
     $helperPID = pcntl_fork();
     if ($helperPID == -1) {
       die ("could not fork helper thread\n");
     } else if ($helperPID) {
        $main_thread = 1; // do nothing really
	$waithelper = get_msg();
     } else {
       include ('helperthd.inc');
       return ;
     }
}

*/

echo "Threads are being started...\n";

$mysqlmain = new mysqli($MYSQLHOST, MYSQLUSER, MYSQLPWD);

/* check connection */
if (mysqli_connect_errno()) {
   printf("Connect failed: %s\n", mysqli_connect_error());
   exit();
}

$mysqlmain->query("use test");
$mysqlmain->query('SELECT get_lock("init", 3600)');
       

for ($i=0; $i<$threads; $i++) {

  if ($i < $insert_threads) $thread_type = 'insert';
       else $thread_type = 'select';

  $pid = pcntl_fork();
  if ($pid == -1) {
    die('could not fork');
  } else if ($pid) {
    // we are the parent

    //    echo "child pid= $pid\n";
    $main_thread = 1;
    $arpids[]= $pid;
    continue;
    pcntl_wait($status); //Protect against Zombie children
  } else {
    // we are the child
    $main_thread=0;
    break;

  }

}


/***** parent process ************/



if ($main_thread){
	$res = $mysqlmain->query('SELECT release_lock("init")');
//var_dump($res);
  $time_start = microtime(true);

  foreach($arpids as $key){
    pcntl_waitpid($key, $status);
  }
  
/*
  if ($helperPID) {
   echo "Kill helper $helperPID\n";
   posix_kill($helperPID, SIGKILL);
  }
*/
  
  $time_stop = microtime(true);
  echo "Threads: $threads\n";

  $summary_result = array('i'=>0, 's' => 0);
  $summaryiters = array('i'=>0, 's' => 0 );
  $markthr = array('i'=>'insert','s'=>'select');
  for ($j= 0; $j< $threads; $j++)
  {
    $data[$j]= @unserialize(@file_get_contents("thr$j"));
    @unlink("thr$j");
    $idx = ($j < $insert_threads) ? 'i' : 's';
    #printf("Thread %d: %d queries, %.3f q/s\n", $j, $data[$j]['iters'],$data[$j]['average']);
    $summary_result[$idx] += $data[$j]['average'];
    $summaryiters[$idx]   += $data[$j]['iters'];
  }
  /* calculate standard deviation */
  if (($threads - $insert_threads) > 0)
    $averageiters['s'] = $summary_result['s'] / ($threads - $insert_threads);

  $sumstd = array('i'=>0, 's' => 0 );
  for ($j= 0; $j< $threads; $j++)
  {
    $idx = ($j < $insert_threads) ? 'i' : 's';
    $sumstd[$idx] += pow($data[$j]['average']- $averageiters[$idx], 2);
  }

  if (($threads - $insert_threads) > 0)
    $stdvar['s']=sqrt($sumstd['s'] / ($threads - $insert_threads));
  
  printf("Total: %.3f q/s, deviation=%.4f\n", $summary_result['s'],
      $stdvar['s']);
  /* Finalyze */
  exit;
}

/*************** Child is here ***************/

if (DEBUG)
    echo "Thread $i started\n";

$mysqli = new mysqli($MYSQLHOST, MYSQLUSER, MYSQLPWD);

/* check connection */
if (mysqli_connect_errno()) {
   printf("Connect failed: %s\n", mysqli_connect_error());
   exit();
}
       

$mysqli->query("use $databaseName");
$mysqli->query('SELECT get_lock("init", 3600)');
$mysqli->query('SELECT release_lock("init")');

/* starting loops */
$starttime = microtime(true);
$j= 0;

$descr= $testQueries[$runQuery];

$isSelect = (strpos($runQuery, 'READ') !== FALSE);


while(true)
{
  $j++;

    $query = vsprintf($descr['query'], $descr['params']());

    $repeatDeadlock = true;
    
    while($repeatDeadlock)
    {
      $repeatDeadlock = false;

    // echo "query = $query\n";
    if (!$mysqli->real_query($query))
    {
       if ($mysqli->errno == 1213)
       {
         $repeatDeadlock = true;
         continue;
       } else {	 
         printf("Query %s error: %s (%s)\n", $query, $mysqli->error, $mysqli->errno);
         continue;
       }
    }

    }
    
    if ($isSelect)
    {
    $result = $mysqli->store_result();
    if ($result === FALSE)
    {
       printf("Query error: %s\n", $mysqli->error);
    }
    $result->free_result();
    }

    $currtime = microtime(true);
    if ($currtime - $starttime > $testDuration)
      break;

}
  if (DEBUG)
    echo "Thread $i finished\n";


$mysqli->close();

$data['time']    = $currtime - $starttime;
$data['iters']   = $j;
$data['average'] = $j / ($currtime - $starttime); 

file_put_contents("thr$i",serialize($data));
//echo "Thread $i finished\n"


?>
